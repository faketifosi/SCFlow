#include <stdafx.h>
#include "cutting.h"


//global var area

int imgWidth;
int imgHeight;

int *count1;
int *count2;
int th = 127;

int xRU[100];//�̦h100�r�� , �O���k�W�y�� temp pic
int yRU[100];

int xLU[100];//���W
int yLU[100];

int xRD[100];//�k�U
int yRD[100];

int xLD[100];//���U
int yLD[100];


int rxRU[100];//to real pic
int ryRU[100];

int rxLU[100];//���W
int ryLU[100];

int rxRD[100];//�k�U
int ryRD[100];

int rxLD[100];//���U
int ryLD[100];

//function area

//�Ϥ����� func
IplImage *rotateImage(const IplImage *src, int width, int height, float angleDegrees)
{
	// Create a map_matrix, where the left 2x2 matrix
	// is the transform and the right 2x1 is the dimensions.
	float m[6];
	CvMat M = cvMat(2, 3, CV_32F, m);
	int w = src->width;
	int h = src->height;
	float angleRadians = angleDegrees * ((float)CV_PI / 180.0f);
	m[0] = (float)( cos(angleRadians) );
	m[1] = (float)( sin(angleRadians) );
	m[3] = -m[1];
	m[4] = m[0];
	m[2] = w*0.5f;  
	m[5] = h*0.5f;  

	// Make a spare image for the result
	CvSize sizeRotated;
	sizeRotated.width = cvRound(width);
	sizeRotated.height = cvRound(height);

	// Rotate
	IplImage *imageRotated = cvCreateImage( sizeRotated,
		src->depth, src->nChannels );

	// Transform the image
	cvGetQuadrangleSubPix( src, imageRotated, &M);

	return imageRotated;
}

//�p������B������v�Ȥ�� �^�ǭȬ��v�����Ҧ��r���Ҧ���pixel��
int countRoIarea(IplImage *imgSrc) {
	
    if( count1 )
		free( count1 );
	if( count2 )
		free( count2 );
	
	count1 = (int*) malloc( (imgSrc->width + 2) * sizeof(count1) ) ;
	count2 = (int*) malloc( (imgSrc->height + 2) * sizeof(count2) );

	for(int i=0 ; i< imgSrc->width +2 ; i++)
		count1[i] = 0;

	for(int i=0 ; i< imgSrc->height +2  ; i++)
		count2[i] = 0;

	int countallpixel = 0;
	for (int i = 0 ; i < imgSrc->width ;i++)
	{
		for (int j = 0 ; j < imgSrc->height ; j++)
		{
			if( ((uchar)imgSrc->imageData[j*imgSrc->widthStep + i*imgSrc->nChannels+0]) < th ) {
				count1[i]++;
			}
		}
	}

	for (int i = 0 ; i < imgSrc->height ;i++)
	{
		for (int j = 0 ; j < imgSrc->width ; j++)
		{
			if( ((uchar)imgSrc->imageData[i*imgSrc->widthStep + j*imgSrc->nChannels+0]) < th ) {
				count2[i]++;
			}
		}
	}
	for (int i = 0 ; i < imgSrc->height ; i++)
	{
		for (int j = 0 ; j < imgSrc->width ; j++)
		{
			if ( count1[j] > 1 &&
				count2[i] > 1 )
			{
				countallpixel++;
			}
		}
	}

	return countallpixel;
}

//�p��n����ե�������
float getAngle(float x1,float y1, float x2,float y2)  
{  
	float x,y,fHyp,cos,rad,deg;  
	x = x2 - x1;  
	y = y2 - y1;  

	fHyp = sqrt(pow(x,2) + pow(y,2));  

	cos = x / fHyp;  
	rad = acos(cos);  

	deg = (float) (180 / ( 3.14 / rad));  

	if(y < 0)  
	{  
		deg = -deg;  
	}  
	else if((y == 0) && (x <0))  
	{  
		deg = 180;  
	}  

	return deg;  
} 

//CONSTRUCTOR �̿ﶵ�ĥΤ��P���e�B�z �w�]�����`�ƦC
ImageAutoCut::ImageAutoCut(void)
{
	recognitionType = COMMON;
}

//�r���䫫����v�B������v�涰�B����
void ImageAutoCut::autocut(char *path) {

	//�Ω�Ϥ��e�B�z
	imageProcess imageProcessing;

	IplImage *img1;
	img1 = cvLoadImage(path, 0);

	imgWidth = img1->width;
	imgHeight = img1->height;
	
	int beforepixel = 0 ;
	int flag = 1;
	float r = 0;
	int num = 0;
	int nowpixel = 0;
	
	float ang = 0;

	int iternum = 0;

	for (int i = 0 ; i < 100 ; i++)
	{
		xRU[i] = 0;
		yRU[i] = 0;

		xLU[i] = 0;
		yLU[i] = 0;

		xRD[i] = 0;
		yRD[i] = 0;

		xLD[i] = 0;
		yLD[i] = 0;


		rxRU[i] = 0;
		ryRU[i] = 0;
		rxLU[i] = 0;
		ryLU[i] = 0;

		rxRD[i] = 0;
		ryRD[i] = 0;

		rxLD[i] = 0;
		ryLD[i] = 0;
	}

	switch(recognitionType)
	{
		case COMMON:
				cvSmooth(img1,img1,CV_MEDIAN);
				img1 = imageProcessing.cuttingROItoOtsu( img1 );
			break;

		case CURVE_ALIGNMENT:
				cvSmooth(img1,img1,CV_MEDIAN);
				img1 = imageProcessing.curvedAlignAdjustment( img1 );
			break;

		case BRAILLE:
				imageProcessing.brailleWord(img1);
			break;
	}


	do
	{	
		beforepixel = countRoIarea( img1 );
		flag = 0;
		num = 0;
		for (int i = 1 ; i < img1->width;i++)
		{
			if (count1[i] > 0 && count1[i-1] == 0 && flag == 0)
			{
				xLU[num] = i;
				flag++;
			}
			else if (count1[i] > 0 && count1[i+1]==0 && flag == 1)
			{
				xRU[num] = i;
				flag++;
			}

			if (flag > 1)
			{
				flag = 0;
				num++;
			}

		}

		IplImage *textlineimg;
		for (int k = 0 ; k < num ; k++)
		{
			textlineimg = cvCreateImage(cvSize( abs(xLU[k] - xRU[k]),img1->height),IPL_DEPTH_8U,1);
			for (int i = 0 ; i < textlineimg->height ; i++)
			{
				for (int j = 0 ; j < textlineimg->width ; j++)
				{
					textlineimg->imageData[i*textlineimg->widthStep + j*textlineimg->nChannels] = img1->imageData[(i+yLU[k])*img1->widthStep + (j+xLU[k])*img1->nChannels];
				}
			}

			countRoIarea(textlineimg);
			for (int i = 0 ; i < textlineimg->height ; i++)
			{
				if (count2[i] > 0 && count2[i-1] == 0)
				{
					rxLU[k] = xLU[k];
					ryLU[k] = i;
				}

			}

			cvReleaseImage( &textlineimg );
		}

		int textLength = (int) sqrt( (float)(xRU[num-1]-xLU[0])*(xRU[num-1]-xLU[0]) + (float)(ryLU[num-1]-ryLU[0])*(ryLU[num-1]-ryLU[0]) );

		ang = getAngle( (float)rxLU[0], (float) ryLU[0], (float) xRU[num-1], (float) ryLU[num-1]);

		IplImage *img2;

		if( textLength + 50 >= img1->width )
			img2 = rotateImage(img1,textLength + 50, img1->height,-ang);
		else 
			img2 = rotateImage(img1,img1->width,img1->height,-ang);

		nowpixel = countRoIarea(img2);
		flag = 0;

		if (beforepixel > nowpixel)
		{
			cvReleaseImage( &img1 );
			img1 = img2;
			nowpixel = countRoIarea(img1);
		}
		else
			cvReleaseImage( &img2 );
		
		iternum++;
	}
	while(rxLU[0] != xRU[num-1] && iternum < 3);

	imageProcessing.OtsuThreshold(img1);

	imgWidth = img1->width;
	imgHeight = img1->height;

	//�x�s�r�����ɦW�s��
	int dataNum = 0;

	/********separating text region**********/
	
	bool aRegion = false;
	
	int startRegion = 0, endRegion = 0;

	
	for (int j = endRegion ; j < imgHeight ; j++)
	{
		countRoIarea(img1);

		if ( count2[j]  > 0 && !aRegion )
		{
			aRegion = true;
			startRegion = j;
		}
		else if( (count2[j]  == 0 && aRegion) || ( aRegion &&  j == imgHeight-1 ) )
		{
			aRegion = false;
			endRegion = j;
	
			int textRegionHeight = endRegion - startRegion +1;
			IplImage *imgSegment = cvCreateImage( cvSize(imgWidth+2, textRegionHeight+2 ) ,8 ,1 );
			cvSet( imgSegment, CV_RGB(255,255,255) );
			cvSetImageROI( img1,cvRect(0, startRegion, imgWidth, textRegionHeight) );
			cvSetImageROI( imgSegment ,cvRect(1, 1, imgWidth, textRegionHeight) );
			cvCopyImage( img1, imgSegment );
			
			cvResetImageROI( imgSegment );

			//���~�۳s����
			imgSegment = imageProcessing.cuttingErrorConnect( imgSegment );

			//���s�p��C�Ӧr���ϰ�
			countRoIarea(imgSegment);		

			int num1 = 0;
			int num2 = 0;
			for (int i = 0 ; i < imgSegment->height ; i++)
			{
				for (int j = 0 ; j < imgSegment->width ; j++)
				{
					if ( count1[j] > 0 &&	count2[i] > 0 )
					{
						if ( count1[j+1] < 1 && count2[i+1] < 1 )
						{
							xRD[num1] = j;
							yRD[num1] = i;
							num1++;
						}
						else if ( count1[j-1] < 1 && count2[i-1] < 1 )
						{
							xLU[num2] = j;
							yLU[num2] = i;
							num2++;
						}
					}
				}
			}

			IplImage *tempimg;
			IplImage *realimg;
 			int tempwidth;
 			int tempheight;
			int realwidth;
			int realheight;

			char newpath[100];

 			for (int k = 0 ; k < num1 ; k++)
 			{
 				stringstream savepath;
 				
 				tempwidth = xRD[k] - xLU[k] + 1;
 				tempheight = yRD[k] - yLU[k] + 1;
 				
				if (tempheight > 0 && tempwidth > 0)
				{
					tempimg = cvCreateImage(cvSize(tempwidth,tempheight),IPL_DEPTH_8U,1);
					for (int i = 0 ; i < tempheight ; i++)
					{
						for (int j = 0 ; j < tempwidth ; j++)
						{
							if ((uchar)imgSegment->imageData[(i+yLU[k])*imgSegment->widthStep + (j+xLU[k])*imgSegment->nChannels+0] == 0)
							{
								tempimg->imageData[i*tempimg->widthStep + j*tempimg->nChannels+0] = 0;
							}
							else
							{
								tempimg->imageData[i*tempimg->widthStep + j*tempimg->nChannels+0] = 255;
							}
						}
					}

					//�p������B������v
					countRoIarea(tempimg);	

					/******************** �N�r���h��ťյ��� start *******************/	

					int upperBound, lowerBound;

					for (int i = 0 ; i < tempimg->height  ; i++)
					{
						if( count2[i] > 0 )
						{
							upperBound = i;
							break;
						}
					}

					for (int i = tempimg->height -1 ; i > 0  ; i--)
					{
						if( count2[i] > 0 )
						{
							lowerBound = i;
							break;
						}
					}

					realwidth = tempimg -> width;
					realheight = lowerBound - upperBound +1;

					realimg = cvCreateImage( cvSize( realwidth, realheight  ),  tempimg->depth, tempimg->nChannels );

					cvSetImageROI ( tempimg, cvRect( 0, upperBound, realwidth, realheight ) );
					cvCopyImage( tempimg, realimg );

					/******************** �N�r���h��ťյ��� end *******************/		

					if(dataNum < 10)
						savepath << "temp/" << "data0" << dataNum << ".bmp";
					else
						savepath << "temp/" << "data"   << dataNum << ".bmp";
					savepath >> newpath;

					cvSaveImage(newpath,realimg);
					dataNum++;
				}
 			}
			
			cvReleaseImage(&tempimg);
			cvReleaseImage(&realimg);
			cvReleaseImage(&imgSegment);
		}
	}

	free(count1);
	free(count2);

	count1 = NULL;
	count2 = NULL;
	
	cvReleaseImage(&img1);
}