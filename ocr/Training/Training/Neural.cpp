#include "stdafx.h"
#include "Neural.h"
#include "receptors.h"

int solveOtsuThreshold(IplImage* );
void cvThin( IplImage*, IplImage*, int iterations = 8);


//宣告正規化的字元影像大小
int normalizedWidth = 30; 
int normalizedHeight = 40;

int saveFileNumber = 0;

int numReceptors = 300;

//隨機產生 receptors
Receptors receptors(numReceptors);
//Receptors receptors;


//建構子與參數設定
NeuralNetwork::NeuralNetwork()
{
	//ctor

	PreInputNum=0;
	InputNum=0;
	OutputNum=0;

	max_ImageHeight = 0;
	max_ImageWidth = 0;

	learningRate = 0.2;
	maximumError = 0.005;
	maximumIteration = 50000;
	PreInputLayer=NULL;
	InputLayer=NULL;
	OutputLayer=NULL;
	TrainingSetNow=NULL;

	NumOfPatterns=0;
	TrainingSet=NULL;
	TS=NULL;

	bstring="";

}

double* ToMatrix(IplImage *BM, int MatrixRowNumber, int MatrixColumnNumber)
{

	double HRate = ((double)MatrixRowNumber / BM->height);
	double WRate = ((double)MatrixColumnNumber / BM->width);
	double *Result = new double[MatrixColumnNumber * MatrixRowNumber + numReceptors];

	for (int r = 0; r < MatrixRowNumber; r++)
	{
		for (int c = 0; c < MatrixColumnNumber; c++)
		{
			Result[r * MatrixColumnNumber + c]=1-(*cvPtr2D(BM,(int)(r / HRate),(int)(c / WRate)))/255;
		}
	}

	return Result;

}
void NeuralNetwork::setBP2NNLayer(int preInputNum, int inputNum, int outputNum, int NumOfPatterns)
{

	PreInputNum = preInputNum;
	InputNum = inputNum;
	OutputNum = outputNum;

	PreInputLayer = new PreInput[PreInputNum];
	InputLayer = new Input[InputNum];
	OutputLayer = new Output[OutputNum];
	TrainingSetNow = new Dictionary[NumOfPatterns];
}

void NeuralNetwork::setTrainingSet(Dictionary *d)
{
	TrainingSetNow = d; 
}


void NeuralNetwork::setmaxErrAndIter(double err,int maxIter)
{
	maximumError = err;
	maximumIteration = maxIter;
}

int SearchDirectory(vector<string> &refvecFiles,
					const string &refcstrRootDirectory,
					const string &refcstrExtension,
					bool bSearchSubdirectories = true)
{
	string strFilePath; // Filepath
	string strPattern; // Pattern
	string strExtension; // Extension
	HANDLE hFile; // Handle to file
	WIN32_FIND_DATA FileInformation; // File information


	strPattern = refcstrRootDirectory + "\\*.*";


	hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FileInformation.cFileName[0] != '.')
			{
				strFilePath.erase();
				strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;
				//strFilePath=FileInformation.cFileName;

				if (FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (bSearchSubdirectories)
					{
						// Search subdirectory
						int iRC = SearchDirectory(refvecFiles,
							strFilePath,
							refcstrExtension,
							bSearchSubdirectories);
						if (iRC)
							return iRC;
					}
				}
				else
				{
					// Check extension
					strExtension = FileInformation.cFileName;
					strExtension = strExtension.substr(strExtension.rfind(".") + 1);

					if (strExtension == refcstrExtension)
					{
						// Save filename
						refvecFiles.push_back(strFilePath);
					}
				}
			}
		}
		while (::FindNextFile(hFile, &FileInformation) == TRUE);

		// Close handle
		::FindClose(hFile);

		DWORD dwError = ::GetLastError();
		if (dwError != ERROR_NO_MORE_FILES)
			return dwError;
	}

	return 0;
}

void NeuralNetwork::GenerateTrainingSet()	//對train資料夾所有圖片做處理(轉灰階 , 大小)
{
	int iRC = 0;
	vector<string> vecBmpFilesP;


	// Search directories for '.bmp' files including subdirectories
	iRC = SearchDirectory(vecBmpFilesP, bstring, "bmp",false);
	if (iRC)
	{
		cout << "NeuralDemo.cpp: GenerateTrainingSet() Error " << iRC << endl;
		exit(0);
		return;

	}

	if (vecBmpFilesP.size() != NumOfPatterns)
	{
		cout <<"NeuralDemo.cpp: NumOfPatterns Error"<<endl;
		return;
	}

	TrainingSet=new Dictionary[NumOfPatterns];


	for (unsigned int i=0;i<NumOfPatterns;i++)
	{
		IplImage *imgSrc=cvLoadImage(vecBmpFilesP[i].c_str(), CV_LOAD_IMAGE_GRAYSCALE);

		if (imgSrc!=NULL)
		{
			TrainingSet[i].filename=vecBmpFilesP[i].substr(0,vecBmpFilesP[i].size()-4);//without extension

			/*---scale normalization---*/
			IplImage *normalizedImg = cvCreateImage( cvSize( normalizedWidth,normalizedHeight ) ,IPL_DEPTH_8U ,1); 
			cvSet( normalizedImg, CV_RGB(255,255,255) );

			float scaleFactorForWidth = normalizedWidth / (float)imgSrc->width;
			float scaleFactorForHeight = normalizedHeight / (float)imgSrc->height;

			float scaleFactor = scaleFactorForWidth < scaleFactorForHeight ? scaleFactorForWidth : scaleFactorForHeight;
			
			IplImage *resizedImage = cvCreateImage( cvSize( (int)(imgSrc->width*scaleFactor), (int)(imgSrc->height*scaleFactor) ) ,IPL_DEPTH_8U ,1);
			cvResize(imgSrc, resizedImage);

			if(scaleFactorForWidth <= scaleFactorForHeight)
			{
				cvSetImageROI( normalizedImg, cvRect(0, (normalizedHeight - resizedImage->height)/2, resizedImage->width, resizedImage->height) );
			}
			else if(scaleFactorForWidth > scaleFactorForHeight)
			{
				cvSetImageROI( normalizedImg, cvRect( (normalizedWidth - resizedImage->width)/2, 0, resizedImage->width, resizedImage->height) );
			}

			cvCopyImage(resizedImage, normalizedImg);
			cvResetImageROI( normalizedImg );

			cvReleaseImage(&resizedImage);
			cvReleaseImage(&imgSrc);
			imgSrc = normalizedImg;

			cvSmooth( imgSrc, imgSrc, CV_MEDIAN );
			cvThreshold(imgSrc,imgSrc,solveOtsuThreshold(imgSrc),1,CV_THRESH_BINARY_INV);   //CV_THRESH_BINARY_INV 為取反

			cvThin(imgSrc, imgSrc, 3);
			//cvDilate(imgSrc, imgSrc, NULL, 2);
		
			for(int j = 0 ; j < imgSrc->width ; j++) 
			{
				for(int k = 0 ; k < imgSrc->height ; k++)
				{
					if( ((uchar *)(imgSrc->imageData + k*imgSrc->widthStep))[j] == 0 )
						((uchar *)(imgSrc->imageData + k*imgSrc->widthStep))[j] = 255;
					else
						((uchar *)(imgSrc->imageData + k*imgSrc->widthStep))[j] = 0;
				}
			}

			char str[100];
			sprintf(str,"save/%d.bmp", saveFileNumber );
			saveFileNumber++;
			/****/
			/****/
			IplImage* resizeSaveImg = cvCreateImage(cvSize(normalizedWidth*10, normalizedHeight*10), 8, 1);
			cvResize(imgSrc, resizeSaveImg);
			cvThreshold(resizeSaveImg,resizeSaveImg,solveOtsuThreshold(resizeSaveImg),255,CV_THRESH_BINARY);
			//for(int j = 0 ; j < numReceptors ; j++)
			//	cvLine( resizeSaveImg, cvPoint(receptors.InnerList[j].X1()*10, receptors.InnerList[j].Y1()*10), cvPoint(receptors.InnerList[j].X2()*10, receptors.InnerList[j].Y2()*10), CV_RGB(128,128,128), 2  );
			/****/
			/****/
			cvSaveImage(str,resizeSaveImg);

			/*---end-------*/

			TrainingSet[i].matrix = new double[numReceptors];
			//TrainingSet[i].matrix = ToMatrix(imgSrc, normalizedHeight, normalizedWidth);

			/*
			double *ver_hist = new double[imgSrc->width];
			double *hor_hist = new double[imgSrc->height];
			int ver_hist_count, hor_hist_count;

			for(int k=0 ; k < imgSrc->width ; k++) 
			{
				ver_hist_count = 0;

				for(int j=0 ; j < imgSrc->height ; j++)
					if( ((uchar *)(imgSrc->imageData + j*imgSrc->widthStep))[k] == 0 )
						ver_hist_count++;
				
				ver_hist[k] = (float)ver_hist_count;
				TrainingSet[i].matrix[k] = (double)ver_hist_count;
			}

			for(int j=0 ; j < imgSrc->height ; j++)
			{
				hor_hist_count = 0;

				for(int k=0 ; k < imgSrc->width ; k++)
					if( ((uchar *)(imgSrc->imageData + j*imgSrc->widthStep))[k] == 0 )
						hor_hist_count++;
				
				hor_hist[j] = (float)hor_hist_count;
				TrainingSet[i].matrix[normalizedWidth + j] = (double)hor_hist_count;
			}
			*/

			//加入 receptors 求得的 discriptor
			int *state = receptors.GetReceptorsState(imgSrc);  
			
			for(int j = 0 ; j < numReceptors ; j++)
				TrainingSet[i].matrix[ j ] = state[j];
				//TrainingSet[i].matrix[ normalizedHeight + normalizedWidth + j ] = state[j];
			

			delete [] state; 
			cvReleaseImage(&imgSrc);
		}
	}
}

void NeuralNetwork::CreateNeuralNetwork(int InputNum)
{

	if (TrainingSet==NULL)
		cerr<<"Unable to Create Neural Network As There is No Data to Train.."<<endl;

	setBP2NNLayer(numReceptors, InputNum, NumOfPatterns,NumOfPatterns);

	setTrainingSet(TrainingSet);

	InitializeNetworkBP2();

}


void NeuralNetwork::InitializeSettings()
{

	/**find *.bmp in the specific directory**/

	int iRC = 0;
	vector<string> vecBmpFiles;


	iRC = SearchDirectory(vecBmpFiles, bstring, "bmp", false);
	if (iRC)
	{
		cout << "NeuralDemo.cpp: InitializeSettings() Error " << iRC << endl;
		return;
	}

	NumOfPatterns=vecBmpFiles.size();
}



void NeuralNetwork::InitializeNetworkBP2()
{

	int i, j;
	//  Random rand = new Random();
	srand((unsigned)time(0));


	for (i = 0; i < PreInputNum; i++)
	{
		PreInputLayer[i].Weights = new double[InputNum];
		for (j = 0; j < InputNum; j++)
		{

			PreInputLayer[i].Weights[j] = 0.01 + ((double)(rand()%6) / 100);

		}
	}

	for (i = 0; i < InputNum; i++)
	{

		InputLayer[i].Weights = new double[OutputNum];
		for (j = 0; j < OutputNum; j++)
		{

			InputLayer[i].Weights[j] = 0.01 + ((double)(rand()%6) / 100);

		}
	}

	int k;

	for (k=0;k<OutputNum;k++)
	{

		OutputLayer[k].Value = TrainingSetNow[k].filename;

	}

}

void NeuralNetwork::ToTrain()
{

	setmaxErrAndIter(0.005,50000);

	if (!Train())
	{
		cerr<<"More than maximum iteration numbers"<<endl;
		return;
	}

}


void NeuralNetwork::Recognize(double *Inputs, string &MHigh, double &MHighVal, string &MLow, double &MLowVal)
{
	int i, j;
	double total = 0.0;
	double max = -1;


	//Apply input to the network
	for (i = 0; i < PreInputNum; i++)
	{

		PreInputLayer[i].Value = Inputs[i];

	}

	//Calculate Input Layer's Inputs and Outputs

	for (i = 0; i < InputNum; i++)
	{

		total = 0.0;
		for (j = 0; j < PreInputNum; j++)
		{
			total += PreInputLayer[j].Value * PreInputLayer[j].Weights[i];
		}

		InputLayer[i].InputSum = total;
		InputLayer[i].Output = F(total);

	}



	//Find the [Two] Highest Outputs

	for (i = 0; i < OutputNum; i++)
	{

		total = 0.0;
		for (j = 0; j < InputNum; j++)
		{

			total += InputLayer[j].Output * InputLayer[j].Weights[i];

		}

		OutputLayer[i].InputSum = total;
		OutputLayer[i].output = F(total);

		if (OutputLayer[i].output > max)
		{
			MLow= MHigh;
			MLowVal = max;
			max = OutputLayer[i].output;
			MHigh = OutputLayer[i].Value;
			MHighVal = max;
		}
	}
}


double NeuralNetwork::F(double x)
{

	return ( 1 / (1 + exp(-x)) );

}

//辨識 training data
void NeuralNetwork::RecognizeTS(char *output)
{

	vector<string> baseImages;
	int iRC2=0;

	iRC2=SearchDirectory(baseImages,bstring,"bmp",true);
	if (iRC2)
	{
		cout << "NeuralDemo.cpp: RecognizeTS() Error " << iRC2 << endl;
		return;

	}

	TS=new TrainMatch[baseImages.size()];

	fstream fout(output, ios::out);
	for (unsigned int i=0;i<baseImages.size();i++)
	{
		IplImage *imgSrc=cvLoadImage(baseImages[i].c_str(), CV_LOAD_IMAGE_GRAYSCALE);

		if (imgSrc!=NULL)
		{
			/*---scale normalization---*/
			IplImage *normalizedImg = cvCreateImage( cvSize( normalizedWidth,normalizedHeight ) ,IPL_DEPTH_8U ,1); 
			cvSet( normalizedImg, CV_RGB(255,255,255) );

			float scaleFactorForWidth = normalizedWidth / (float)imgSrc->width;
			float scaleFactorForHeight = normalizedHeight / (float)imgSrc->height;

			float scaleFactor = scaleFactorForWidth < scaleFactorForHeight ? scaleFactorForWidth : scaleFactorForHeight;
			
			IplImage *resizedImage = cvCreateImage( cvSize( (int)(imgSrc->width*scaleFactor), (int)(imgSrc->height*scaleFactor) ) ,IPL_DEPTH_8U ,1);
			cvResize(imgSrc, resizedImage, CV_INTER_AREA);
			
			if(scaleFactorForWidth <= scaleFactorForHeight)
			{
				cvSetImageROI( normalizedImg, cvRect(0, (normalizedHeight - resizedImage->height)/2, resizedImage->width, resizedImage->height) );
			}
			else if(scaleFactorForWidth > scaleFactorForHeight)
			{
				cvSetImageROI( normalizedImg, cvRect( (normalizedWidth - resizedImage->width)/2, 0, resizedImage->width, resizedImage->height) );
			}

			cvCopyImage(resizedImage, normalizedImg);
			cvResetImageROI( normalizedImg );

			cvReleaseImage(&resizedImage);
			cvReleaseImage(&imgSrc);
			imgSrc = normalizedImg;
			/*---end-------*/

			cvSmooth( imgSrc, imgSrc, CV_MEDIAN );
			cvThreshold(imgSrc,imgSrc,solveOtsuThreshold(imgSrc),1,CV_THRESH_BINARY_INV);
			
			cvThin(imgSrc, imgSrc, 3);
			//cvDilate(imgSrc, imgSrc, NULL, 2);
		
			
			for(int j = 0 ; j < imgSrc->width ; j++) 
			{
				for(int k = 0 ; k < imgSrc->height ; k++)
				{
					if( ((uchar *)(imgSrc->imageData + k*imgSrc->widthStep))[j] == 0 )
						((uchar *)(imgSrc->imageData + k*imgSrc->widthStep))[j] = 255;
					else
						((uchar *)(imgSrc->imageData + k*imgSrc->widthStep))[j] = 0;
				}
			}

			double *input=new double[numReceptors];
			//double *input=new double[normalizedHeight + normalizedWidth + numReceptors];
			//input = ToMatrix(imgSrc, normalizedHeight, normalizedWidth);



/*
			double *ver_hist = new double[imgSrc->width];
			double *hor_hist = new double[imgSrc->height];
			int ver_hist_count, hor_hist_count;

			for(int k=0 ; k < imgSrc->width ; k++) 
			{
				ver_hist_count = 0;

				for(int j=0 ; j < imgSrc->height ; j++)
					if( ((uchar *)(imgSrc->imageData + j*imgSrc->widthStep))[k] == 0 )
						ver_hist_count++;
				
				ver_hist[k] = (float)ver_hist_count;
				input[k] = (double)ver_hist_count;
			}

			for(int j=0 ; j < imgSrc->height ; j++)
			{
				hor_hist_count = 0;

				for(int k=0 ; k < imgSrc->width ; k++)
					if( ((uchar *)(imgSrc->imageData + j*imgSrc->widthStep))[k] == 0 )
						hor_hist_count++;
				
				hor_hist[j] = (float)hor_hist_count;
				input[normalizedWidth + j] = (double)hor_hist_count;
			}
*/



			//加入 receptors 求得的 discriptor
			int *state = receptors.GetReceptorsState(imgSrc);  
			
			for(int j = 0 ; j < numReceptors ; j++)
				input[ j ] = state[j];

			delete [] state;
		

			string MatchedHigh;
			double OutputValueHight;
			string MatchedLow;
			double OutputValueLow;

			Recognize(input,MatchedHigh,OutputValueHight,MatchedLow,OutputValueLow);

			TS[i].nameH=MatchedHigh;
			TS[i].MatchRateH=OutputValueHight;
			TS[i].nameL=MatchedLow;
			TS[i].MatchRateL=OutputValueLow;

			fout<<"File:"<<baseImages[i].c_str()<<" ";
			fout<<i<<","<<TS[i].nameH<<","<<TS[i].MatchRateH<<endl;//<<";"<<TS[i].nameL<<","<<TS[i].MatchRateL<<endl;
			// fout<<endl;


			delete[] input;
			cvReleaseImage(&imgSrc);
		}

	}

	fout.close();


}

bool NeuralNetwork::Train()
{
	double currentError = 0.0;
	int currentIteration = 0;

	do
	{

		currentError = 0.0;
		//  foreach (KeyValuePair<T, double[]> p in TrainingSet)

		for (int k=0;k<OutputNum;k++)
		{

			ForwardPropagate(TrainingSetNow[k].matrix,TrainingSetNow[k].filename);
			BackPropagate();
			currentError += GetError();

		}

		currentIteration++;

	}
	while (currentError > maximumError && currentIteration < maximumIteration );


	if (currentIteration >= maximumIteration)
		return false; //Training Not Successful

	return true;

}


void NeuralNetwork::ForwardPropagate(double *pattern, string output)
{
	int i, j;
	double total = 0.0;


	//Apply input to the network
	for (i = 0; i < PreInputNum; i++)
	{
		PreInputLayer[i].Value = pattern[i];
	}

	//Calculate The First(Input) Layer's Inputs and Outputs

	for (i = 0; i < InputNum; i++)
	{
		total = 0.0;
		for (j = 0; j < PreInputNum; j++)
		{

			total += PreInputLayer[j].Value * PreInputLayer[j].Weights[i];

		}

		InputLayer[i].InputSum = total;
		InputLayer[i].Output = F(total);
	}

	//Calculate The Second(Output) Layer's Inputs, Outputs, Targets and Errors

	for (i = 0; i < OutputNum; i++)
	{
		total = 0.0;
		for (j = 0; j < InputNum; j++)
		{

			total += InputLayer[j].Output * InputLayer[j].Weights[i];

		}

		OutputLayer[i].InputSum = total;
		OutputLayer[i].output = F(total);
		OutputLayer[i].Target = OutputLayer[i].Value.compare(output) == 0 ? 1.0 : 0.0;
		OutputLayer[i].Error = (OutputLayer[i].Target - OutputLayer[i].output) * (OutputLayer[i].output) * (1 - OutputLayer[i].output);
	}

}

//倒傳遞調整神經鏈權重
void NeuralNetwork::BackPropagate()
{
	int i, j;
	double total;

	//Fix Input Layer's Error

	for (i = 0; i < InputNum; i++)
	{

		total = 0.0;
		for (j = 0; j < OutputNum; j++)
		{
			total += InputLayer[i].Weights[j] * OutputLayer[j].Error;

		}

		InputLayer[i].Error = total;
	}



	//Update The First Layer's Weights
	for (i = 0; i < InputNum; i++)
	{
		for (j = 0; j < PreInputNum; j++)
		{
			PreInputLayer[j].Weights[i] += learningRate * InputLayer[i].Error * PreInputLayer[j].Value;
		}
	}



	//Update The Second Layer's Weights
	for (i = 0; i < OutputNum; i++)
	{
		for (j = 0; j < InputNum; j++)
		{
			InputLayer[j].Weights[i] += learningRate * OutputLayer[i].Error * InputLayer[j].Output;
		}
	}

}

double NeuralNetwork::GetError()
{
	double total = 0.0;
	for (int j = 0; j < OutputNum; j++)
	{

		total += pow((OutputLayer[j].Target - OutputLayer[j].output), 2) / 2;

	}

	return total;
}


void NeuralNetwork::saveNetwork(char *path)
{
	int i,j;
	fstream fout(path, ios::out);

	fout<<PreInputNum<<" "<<InputNum<<" "<<OutputNum<<endl;


	for (i = 0; i < PreInputNum; i++)
	{
		for (j = 0; j < InputNum; j++)
		{
			fout<<PreInputLayer[i].Weights[j];
			if (j!=InputNum-1)
				fout<<" ";
		}
		fout<<endl;
	}

	fout<<endl;



	for (i = 0; i < InputNum; i++)
	{

		for (j = 0; j < OutputNum; j++)
		{

			fout<<InputLayer[i].Weights[j];
			if(j!=OutputNum-1)
				fout<<" ";

		}
		fout<<endl;
	}

	fout<<endl;

	fout.close();
}

void NeuralNetwork::classify()
{
	float symmetric_degree = 0.90f;

	float hor_symmetry = 0, ver_symmetry = 0;
	float H1_avg = 0, H2_avg = 0;
	float sumOfH1_prime = 0, sumOfH2_prime = 0;
	float correl_denominator = 0;

	int	iRC;
	vector<string> vecBmpFilesP;

	iRC = SearchDirectory(vecBmpFilesP, "trainingdata", "bmp",false);
	int NumOfPatterns = vecBmpFilesP.size();

	IplImage *imgSrc;

	for (int n = 0 ; n < NumOfPatterns ; n++)
	{
		char pathout[50];
		stringstream path;

		imgSrc = cvLoadImage(vecBmpFilesP[n].c_str(), CV_LOAD_IMAGE_GRAYSCALE );

		float *ver_hist = new float[imgSrc->width];
		float *hor_hist = new float[imgSrc->height];
		int ver_hist_count, hor_hist_count, pixel_count = 0;

		for(int i=0 ; i < imgSrc->width ; i++) 
		{
			ver_hist_count = 0;

			for(int j=0 ; j < imgSrc->height ; j++)
				if( ((uchar *)(imgSrc->imageData + j*imgSrc->widthStep))[i] == 0 )
					ver_hist_count++;
			
			ver_hist[i] = (float)ver_hist_count;
			pixel_count += ver_hist_count;
		}

		for(int j=0 ; j < imgSrc->height ; j++)
		{
			hor_hist_count = 0;

			for(int i=0 ; i < imgSrc->width ; i++)
				if( ((uchar *)(imgSrc->imageData + j*imgSrc->widthStep))[i] == 0 )
					hor_hist_count++;
			
			hor_hist[j] = (float)hor_hist_count;
		}

		/************   pure diff   ***********/

		for(int i = 0 ; i < ceil((float)imgSrc->width)/2 ; i++ )
		{
			if(ver_hist[i] == ver_hist[ imgSrc->width-i-1 ])
				continue;

			hor_symmetry += (float) abs(ver_hist[i] - ver_hist[ imgSrc->width-i-1 ]);
		}

		hor_symmetry = 1 - hor_symmetry / pixel_count; 

		for(int i = 0 ; i < ceil((float)imgSrc->height)/2 ; i++ )
		{
			if(hor_hist[i] == hor_hist[ imgSrc->height-i-1 ])
				continue;

			ver_symmetry += (float) abs(hor_hist[i] - hor_hist[ imgSrc->height-i-1 ]);
		}

		ver_symmetry = 1 - ver_symmetry / pixel_count;


		CvMemStorage *mem = cvCreateMemStorage(0);
		CvSeq *contours, *ptr;

		IplImage *imgTemp = cvCloneImage(imgSrc);

		cvNot(imgSrc, imgTemp);

		cvFindContours(imgTemp, mem, &contours, sizeof(CvContour), CV_RETR_CCOMP,
							CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
		
		int compCount = 0;
		int holeCount = 0;

		for (ptr = contours; ptr != NULL; ptr = ptr->h_next)
		{
			contours = ptr;

			for (;ptr != NULL; ptr = ptr->v_next)
				holeCount++;

			compCount++;

			ptr = contours;
		}	

		//以對稱程度依照條件分類
		if( ver_symmetry >= symmetric_degree && hor_symmetry >= symmetric_degree )
		{
			if( min(ver_symmetry, hor_symmetry) / max(ver_symmetry, hor_symmetry) < 0.97  ) // 0.97 為水平對稱與上下對稱的比例參數
			{
				if( ver_symmetry >= hor_symmetry )
				{
					if( compCount >= 2 || holeCount >= 2 )
						path << "train1/" << vecBmpFilesP[n].c_str();
					else
						path << "train0/" << vecBmpFilesP[n].c_str();
				}
				else
				{
					if( compCount >= 2 || holeCount >= 2 )
						path << "train3/" << vecBmpFilesP[n].c_str();
					else
						path << "train2/" << vecBmpFilesP[n].c_str();
				}
			}
			else 
			{
				if( compCount >= 2 || holeCount >= 2 )
					path << "train5/" << vecBmpFilesP[n].c_str();
				else
					path << "train4/" << vecBmpFilesP[n].c_str();
			}
		
		}
		else if( ver_symmetry >= symmetric_degree )
		{
			if( compCount >= 2 || holeCount >= 2 )
				path << "train1/" << vecBmpFilesP[n].c_str();
			else
				path << "train0/" << vecBmpFilesP[n].c_str();
		}
			
		else if( hor_symmetry >= symmetric_degree )
		{
			if( compCount >= 2 || holeCount >= 2 )
				path << "train3/" << vecBmpFilesP[n].c_str();
			else
				path << "train2/" << vecBmpFilesP[n].c_str();
		}
			
		else
		{
			if( compCount >= 2 || holeCount >= 2 )
				path << "train7/" << vecBmpFilesP[n].c_str();
			else
				path << "train6/" << vecBmpFilesP[n].c_str();
		}
		

		path >> pathout;
		cvSaveImage( pathout, imgSrc );

		cvReleaseImage( &imgSrc );
		cvReleaseImage( &imgTemp );
		free( ver_hist );
		free( hor_hist );
	}
}


NeuralNetwork::~NeuralNetwork()
{
	//dtor

	if (PreInputLayer!=NULL)
	{
		for (int i = 0; i < PreInputNum; i++)
		{
			delete[] PreInputLayer[i].Weights;

		}
		delete[] PreInputLayer;
	}

	if (InputLayer!=NULL)
	{
		for (int i = 0; i < InputNum; i++)
		{
			delete[] InputLayer[i].Weights;

		}

		delete[] InputLayer;
	}

	if (OutputLayer!=NULL)
		delete[] OutputLayer;

}







//Otsu method
int solveOtsuThreshold(IplImage* src)  
{  
     int height=src->height;  
     int width=src->width;   
 
     //histogram  
     float histogram[256]={0};  

     for(int i=0;i<height;i++) {  
         unsigned char* p=(unsigned char*)src->imageData+src->widthStep*i;
		 for(int j=0;j<width;j++) {  
		     histogram[*p++]++;  
         }  
     }  

     //normalize histogram  
     int size=height*width;  
     for(int i=0;i<256;i++) {  
         histogram[i]=histogram[i]/size;  
     }  
       
     //average pixel value  
     float avgValue=0;  
     for(int i=0;i<256;i++) {  
         avgValue+=i*histogram[i];  
     }  
   
     int threshold;    
     float maxVariance=0;  
     float w=0,u=0;  
     for(int i=0;i<256;i++) {  
         w+=histogram[i];  
		 if (w == 0) continue;

         u+=i*histogram[i];  
   
         float t=avgValue*w-u;  
         float variance=t*t/(w*(1-w));  
         if(variance>maxVariance) {  
             maxVariance=variance;  
             threshold = i;  
         }  
     }  
	 
	 return threshold;     
}


void cvThin( IplImage* src, IplImage* dst, int iterations) 
{ 
	CvSize size = cvGetSize(src); 
	cvCopy(src, dst); 
    int n = 0,i = 0,j = 0; 

	for(n=0; n<iterations; n++) 
	{ 
		IplImage* t_image = cvCloneImage(dst); 
		
		for(i=0; i<size.height;  i++) 
		{ 
			for(j=0; j<size.width; j++) 
			{ 
				if(CV_IMAGE_ELEM(t_image,byte,i,j)==1) 
				{ 
					int ap=0; 
					int p2 = (i==0)?0:CV_IMAGE_ELEM(t_image,byte, i-1, j); 
					int p3 = (i==0 || j==size.width-1)?0:CV_IMAGE_ELEM(t_image,byte, i-1, j+1); 
				 
					if (p2==0 && p3==1) 
					{ 
						ap++; 
					}

					int p4 = (j==size.width-1)?0:CV_IMAGE_ELEM(t_image,byte,i,j+1); 
					
					if(p3==0 && p4==1) 
					{ 
						ap++; 
					}

					int p5 = (i==size.height-1 || j==size.width-1)?0:CV_IMAGE_ELEM(t_image,byte,i+1,j+1); 

					if(p4==0 && p5==1) 
					{ 
						ap++; 
					} 
					int p6 = (i==size.height-1)?0:CV_IMAGE_ELEM(t_image,byte,i+1,j); 
					
					if(p5==0 && p6==1) 
					{ 
						ap++; 
					}

					int p7 = (i==size.height-1 || j==0)?0:CV_IMAGE_ELEM(t_image,byte,i+1,j-1); 
					
					if(p6==0 && p7==1) 
					{ 
						ap++; 
					} 
					int p8 = (j==0)?0:CV_IMAGE_ELEM(t_image,byte,i,j-1); 
					
					if(p7==0 && p8==1) 
					{ 
						ap++; 
					}

					int p9 = (i==0 || j==0)?0:CV_IMAGE_ELEM(t_image,byte,i-1,j-1); 

					if(p8==0 && p9==1) 
					{ 
						ap++; 
					}

					if(p9==0 && p2==1) 
					{ 
						ap++; 
					} 
					if((p2+p3+p4+p5+p6+p7+p8+p9)>1 && (p2+p3+p4+p5+p6+p7+p8+p9)<7) 
					{ 
						if(ap==1) 
						{ 
							if(!(p2 && p4 && p6)) 
							{	 
								if(!(p4 && p6 && p8))  
								{ 
									CV_IMAGE_ELEM(dst,byte,i,j)=0; 
								} 
							} 
						} 
					} 
				} 
			} 
		} 
  cvReleaseImage(&t_image); 
  t_image = cvCloneImage(dst); 
  for(i=0; i<size.height;  i++) 
  { 
   for(int j=0; j<size.width; j++) 
   { 
    if(CV_IMAGE_ELEM(t_image,byte,i,j)==1) 
    { 
     int ap=0; 
     int p2 = (i==0)?0:CV_IMAGE_ELEM(t_image,byte, i-1, j); 
     int p3 = (i==0 || j==size.width-1)?0:CV_IMAGE_ELEM(t_image,byte, i-1, j+1); 
     if (p2==0 && p3==1) 
     { 
      ap++; 
     } 
     int p4 = (j==size.width-1)?0:CV_IMAGE_ELEM(t_image,byte,i,j+1); 
     if(p3==0 && p4==1) 
     { 
      ap++; 
     } 
     int p5 = (i==size.height-1 || j==size.width-1)?0:CV_IMAGE_ELEM(t_image,byte,i+1,j+1); 
     if(p4==0 && p5==1) 
     { 
      ap++; 
     } 
     int p6 = (i==size.height-1)?0:CV_IMAGE_ELEM(t_image,byte,i+1,j); 
     if(p5==0 && p6==1) 
     { 
      ap++; 
     } 
     int p7 = (i==size.height-1 || j==0)?0:CV_IMAGE_ELEM(t_image,byte,i+1,j-1); 
     if(p6==0 && p7==1) 
     { 
      ap++; 
     } 
     int p8 = (j==0)?0:CV_IMAGE_ELEM(t_image,byte,i,j-1); 
     if(p7==0 && p8==1) 
     { 
      ap++; 
     } 
     int p9 = (i==0 || j==0)?0:CV_IMAGE_ELEM(t_image,byte,i-1,j-1); 
     if(p8==0 && p9==1) 
     { 
      ap++; 
     } 
     if(p9==0 && p2==1) 
     { 
      ap++; 
     } 
     if((p2+p3+p4+p5+p6+p7+p8+p9)>1 && (p2+p3+p4+p5+p6+p7+p8+p9)<7) 
     { 
      if(ap==1) 
      { 
       if(p2*p4*p8==0) 
       { 
        if(p2*p6*p8==0) 
        { 
         CV_IMAGE_ELEM(dst, byte,i,j)=0; 
        } 
       } 
      } 
     }                     
    } 
   } 
  }             
  cvReleaseImage(&t_image); 
 } 
} 