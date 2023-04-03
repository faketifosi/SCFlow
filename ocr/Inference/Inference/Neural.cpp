#include "stdafx.h"
#include "Neural.h"


NeuralNetwork::NeuralNetwork()
{
}

NeuralNetwork::NeuralNetwork(string dataPath, char *netFile)
{
	//ctor
	PreInputNum = 0;
	InputNum = 0;
	OutputNum = 0;

	nodeNumberOfInputLayer = 100;

	PreInputLayer = NULL;
	InputLayer = NULL;
	OutputLayer = NULL;

	NumOfPatterns = 0;

	bstring = dataPath;
	InitializeSettings();
	
	loadNetwork( netFile );

}

/*
void NeuralNetwork::operator =(const NeuralNetwork &net)
{
	this->PreInputNum = net.PreInputNum;
	this->InputNum = net.InputNum;
	this->OutputNum = net.OutputNum;

	this->nodeNumberOfInputLayer = net.nodeNumberOfInputLayer;

	this->PreInputLayer = net.PreInputLayer;
	this->InputLayer = net.InputLayer;
	this->OutputLayer = net.OutputLayer;

	this->NumOfPatterns = net.NumOfPatterns;

	this->bstring = net.bstring;
}
*/

//初始化每組類神經網路
void NeuralNetwork::set_member(string dataPath, char *netFile)
{
	//ctor
	PreInputNum = 0;
	InputNum = 0;
	OutputNum = 0;

	nodeNumberOfInputLayer = 100;

	PreInputLayer = NULL;
	InputLayer = NULL;
	OutputLayer = NULL;

	NumOfPatterns = 0;

	bstring = dataPath;
	InitializeSettings();
	
	loadNetwork( netFile );

}

//將影像排列成要輸入類神經網路的一維陣列
double* ToMatrix(IplImage *BM, int MatrixRowNumber, int MatrixColumnNumber)
{

	double HRate = ((double)MatrixRowNumber / BM->height);
	double WRate = ((double)MatrixColumnNumber / BM->width);
	double *Result = new double[MatrixColumnNumber * MatrixRowNumber + 600 ];
	//double *Result = new double[MatrixColumnNumber * MatrixRowNumber];

	for (int r = 0; r < MatrixRowNumber; r++)
	{
		for (int c = 0; c < MatrixColumnNumber; c++)
		{
			Result[r * MatrixColumnNumber + c]=1-(*cvPtr2D(BM,(int)(r / HRate),(int)(c / WRate)))/255;
		}
	}
	return Result;
}


/******************Create Neural Network begin********************/

void NeuralNetwork::InitializeSettings()
{
	/**find *.bmp in the specific directory**/

	int iRC = 0;
	vector<string> vecBmpFiles;

	// Search 'C:/Program Files/BitComet/Downloads' for '.avi' files including subdirectories
	iRC = SearchDirectory(vecBmpFiles, bstring, "bmp",false);
	if (iRC)
	{
		cout << "NeuralDemo.cpp: InitializeSettings() Error " << iRC << endl;
		return;
	}

	/**end find *.bmp**/

	NumOfPatterns = vecBmpFiles.size();

	//setBP2NNLayer( 100 , nodeNumberOfInputLayer, NumOfPatterns, NumOfPatterns );
	setBP2NNLayer( 300, nodeNumberOfInputLayer, NumOfPatterns, NumOfPatterns );

	for (int k=0;k<OutputNum;k++)
		OutputLayer[k].Value = vecBmpFiles[k].c_str();
}

/******************Create Neural Network end********************/

void NeuralNetwork::setBP2NNLayer(int preInputNum, int inputNum, int outputNum, int NumOfPatterns)
{
	PreInputNum = preInputNum;
	InputNum = inputNum;
	OutputNum = outputNum;

	PreInputLayer = new PreInput[PreInputNum];
	InputLayer = new Input[InputNum];
	OutputLayer = new Output[OutputNum];
}

/**********  load Neural Network begin  ***********/

void NeuralNetwork::loadNetwork(char* path)
{
	int i,j;
	fstream fin(path, ios::in);

	int PInum,Inum,Onum;
	fin>>PInum>>Inum>>Onum;

	for (i = 0; i < PreInputNum; i++)
	{
		PreInputLayer[i].Weights = new double[InputNum];
		for (j = 0; j < InputNum; j++)
			fin>>PreInputLayer[i].Weights[j];
	}

	for (i = 0; i < InputNum; i++)
	{
		InputLayer[i].Weights = new double[OutputNum];
		for (j = 0; j < OutputNum; j++)
			fin>>InputLayer[i].Weights[j];
	}

	fin.close();
}

/**********  load Neural Network end  ***********/



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
	return (1 / (1 + exp(-x)));
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


NeuralNetwork::~NeuralNetwork()
{
	//dtor

	if (PreInputLayer)
	{
		for (int i = 0; i < PreInputNum; i++)
		{
			delete[] PreInputLayer[i].Weights;

		}
		delete[] PreInputLayer;
	}

	if (InputLayer)
	{
		for (int i = 0; i < InputNum; i++)
		{
			delete[] InputLayer[i].Weights;

		}

		delete[] InputLayer;
	}

	if (OutputLayer)
	{
		delete[] OutputLayer;
	}
}