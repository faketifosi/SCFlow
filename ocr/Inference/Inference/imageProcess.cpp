#include "StdAfx.h"
#include "imageProcess.h"



//CONSTRUCTOR
imageProcess::imageProcess(void)
{
}

//過濾 connected component 的大小
int sizeFilter(CvSeq *contour)
{
    if (contour->total > 8) {
        return 1;
    }
    return 0;
}

//所有 pixel fitting 成拋物線當作球滾的基本路徑
CvMat* pixelCurveFitting(IplImage* Source)
{
	int PointCount = 0;
	CvMat *x, *A, *Y;

	for( int i = 0 ; i < Source->height ; i++ )
	{
		for( int j = 0 ; j < Source->width ; j++ )
		{
			if( ((uchar *)(Source->imageData+i*Source->widthStep))[j] == 0 )
				PointCount++;
		}
	}

	x = cvCreateMat( 3, 1, CV_32FC1 );
	A = cvCreateMat( PointCount, 3, CV_32FC1 );
	Y = cvCreateMat( PointCount, 1, CV_32FC1 );

	PointCount = 0;
	for( int i = 0 ; i < Source->height ; i++ )
	{
		for( int j = 0 ; j < Source->width ; j++ )
		{
			if( ((uchar *)(Source->imageData+i*Source->widthStep))[j] == 0 )
			{
				cvmSet( A, PointCount, 0, j*j );
				cvmSet( A, PointCount, 1, j );
				cvmSet( A, PointCount, 2, 1 );
				cvmSet( Y, PointCount, 0, i );
				PointCount++;
			}
		}
	}

	cvSolve( A, Y, x, CV_SVD );

	cvReleaseMat( &A );
	cvReleaseMat( &Y );

	return x;
}

//連通元件偵測及篩選
CvSeq *extract_and_filter_CC(IplImage *img, CvMemStorage **m, int (*criteria) (CvSeq *))
{
    CvSeq *contours, *ptr;
    *m = cvCreateMemStorage(0);
	cvFindContours(img, *m, &contours, sizeof(CvContour), CV_RETR_CCOMP,
				CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
    ptr = contours;

    while (ptr != NULL){
        if (criteria(ptr) == 0) {
            if (ptr == contours) {
                contours = ptr->h_next;
                ptr = contours;
                ptr->h_prev = NULL;
            } else {
                ptr->h_prev->h_next = ptr->h_next;
                if (ptr->h_next != NULL)
                    ptr->h_next->h_prev = ptr->h_prev;
                ptr = ptr->h_next;
            }
		}
		else {
            ptr = ptr->h_next;
        }
    }
    return contours;
}

//otsu method
int imageProcess::cvSolveOtsuThreshold(IplImage* src)  
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

//Otsu法對影像二值化
IplImage *imageProcess::cvThresholdOtsu(IplImage *imageSrc)
{
	IplImage* imageDst = cvCloneImage(imageSrc);

	//otsu method求二值化threshold
	cvThreshold( imageSrc, imageDst, cvSolveOtsuThreshold(imageSrc), 255, CV_THRESH_BINARY );
	
	return imageDst;
}

//字元相連偵測與切割
IplImage *imageProcess::cuttingErrorConnect(IplImage *imageSrc)
{
	IplImage *columnHistImage = cvCreateImage(cvGetSize(imageSrc),IPL_DEPTH_8U,1);
	cvSetZero(columnHistImage);

	//for estimate character width and height
	int maxHist = 0;

	int *columnHist = new int[columnHistImage->width];
	
	//依照Hist.計算字體最大高度用來設定將山峰山谷視為字母相連的參數
	for(int i=0;i<imageSrc->width;i++)
	{
		int blackPixelCount = 0;

	    for(int j=0;j<imageSrc->height;j++)
		{
			((uchar *)(imageSrc->imageData + j*imageSrc->widthStep))[i] <= 200 ? blackPixelCount++ : blackPixelCount;

		}   

		columnHist[i] = blackPixelCount;

		if(blackPixelCount > maxHist)
			maxHist = blackPixelCount;

	} //end for

	for(int i=0;i<columnHistImage->width;i++)
	{
		if(columnHist[i] > 0)
			cvLine( columnHistImage, cvPoint(i,columnHistImage->height), cvPoint(i,columnHistImage->height-columnHist[i]+1), CV_RGB(127,127,127));
	}

	// for claculate error connection
	int valleyBoundaryWidth  = maxHist / 6; 
	int valleyBoundaryHeight = maxHist / 4; 
	bool startSearch = false;
	bool findValley = false;

	int leftPeakHeight = 0,rightPeakHeight = 0 , theValleyHeight = 0;
	int  theValleyIndex;
	int theLeftPeakIndex = 0, theRightPeakIndex = 0;

	for(int i=0;i<columnHistImage->width;i++)
	{	
		bool findLeftPeak = false;
		bool findRightPeak = false;
		theValleyIndex = i;
		theValleyHeight = columnHist[i];
		
		//以i點開始向左查找至波峰參數的左邊界判斷是否全為由高至低的走勢
		for( int j = i ; j > i - valleyBoundaryWidth / 2 ; j-- )
		{
			if(j<=0) { break; }

			//遇到左邊高度大於右邊開始尋找波谷
			if(columnHist[j-1] - columnHist[j] >= 0)
			{
				leftPeakHeight = columnHist[j];
				theLeftPeakIndex = j;
				findLeftPeak = true;
			}
			else if(columnHist[j-1] - columnHist[j] < 0 && findLeftPeak)
			{
				leftPeakHeight = columnHist[j];
				break;
			}
			else if(columnHist[j-1] - columnHist[j] < 0 && !findLeftPeak)
			{
				leftPeakHeight = columnHist[j];
				findLeftPeak = false;
				break;
			}
		
		}
		
		//以i點開始向右查找至波峰參數的右邊界判斷是否全為由低至高的走勢
		for( int j=i ; j < i + valleyBoundaryWidth / 2 ; j++ )
		{
			if(j>=columnHistImage->width) { break; }

			if(columnHist[j+1] - columnHist[j] >= 0)
			{
				rightPeakHeight = columnHist[j];
				theRightPeakIndex = j;
				findRightPeak = true;
			}
			else if(columnHist[j+1] - columnHist[j] < 0 && findRightPeak)
			{
				rightPeakHeight = columnHist[j];
				break;
			}
			else if(columnHist[j+1] - columnHist[j] < 0 && !findRightPeak)
			{
				findRightPeak = false;
				break;
			}
		}

		//若找到的波峰波谷符合設定的大小則視為錯誤相連
		if(min(leftPeakHeight,rightPeakHeight) - theValleyHeight >= valleyBoundaryHeight && (theRightPeakIndex-theLeftPeakIndex) <= valleyBoundaryWidth && findRightPeak && findLeftPeak)
		{
			cvLine( imageSrc, cvPoint(theValleyIndex,columnHistImage->height), cvPoint(theValleyIndex,0), CV_RGB(255,255,255),1);
		}
	}

	//return columnHistImage;
	return imageSrc;
}

//每行平均的pixel值做Otsu法切出均勻分佈
IplImage *imageProcess::columnAverageHistogram(IplImage *imageSrc, IplImage* colorSrcImage)
{
	IplImage *columnHistImage = cvCreateImage(cvGetSize(imageSrc),IPL_DEPTH_8U,1);
	cvSetZero(columnHistImage);

	float *columnAverageHist = new float[columnHistImage->width];

	for(int i=0;i<imageSrc->width;i++)
	{
		int sumOfIntensity = 0;

		for(int j=0;j<imageSrc->height;j++)
		{
			sumOfIntensity += ((uchar *)(imageSrc->imageData + j*imageSrc->widthStep))[i];
		}

		columnAverageHist[i] = (float) ( sumOfIntensity / imageSrc->height ) ;

	} //end for

	for(int i=0;i<columnHistImage->width;i++) 
	{
		if(columnAverageHist[i] > 0)
			cvLine( columnHistImage, cvPoint(i,columnHistImage->height), cvPoint(i,columnHistImage->height - (int) columnAverageHist[i]/4), CV_RGB(127,127,127));
	} //end for
	

	 int height=imageSrc->height;  
     int width=imageSrc->width;  

     //normalize histogram  
     int size=height*width;  
     for(int i=0;i<width;i++) {  
         columnAverageHist[i]=columnAverageHist[i]/width;  
     }  
       
     //average pixel value  
     float avgValue=0;  
     for(int i=0;i<width;i++) {  
         avgValue += columnAverageHist[i];  
     }  
   
     int threshold;    
     float maxVariance=0;  
     float w=0,u=0;  
     for(int i=0;i<width;i++) {  
         w+=columnAverageHist[i];  
		 if (w == 0) continue;

         u+= columnAverageHist[i] * width ;  
   
         float t=avgValue-u/(i+1);  
         float variance=t*t*(u/avgValue*width);  
         if(variance>maxVariance) {  
             maxVariance=variance;  
             threshold = i;  
         }  
     }  
	cvLine( columnHistImage, cvPoint(threshold,columnHistImage->height-1), cvPoint(threshold,0), CV_RGB(255,255,255));
	int result = (int) columnAverageHist[ threshold ] * width;
	return columnHistImage;
}


//偵測影像亮度變化以水平方向切割為多個子區域分別做影像二值化
IplImage *imageProcess::cuttingROItoOtsu( IplImage *imageSrc )
{
	IplImage *resultImage = cvCreateImage( cvGetSize(imageSrc), imageSrc->depth, imageSrc->nChannels );
	cvSet( resultImage , CV_RGB(255,255,255) );

	float firstLineHist[256] = {0};

	//統計 first line 的intensity
	for(int i=0;i<imageSrc->width;i++)
	{
		for(int j=0;j<1;j++)
		{
			int p = ((uchar *)(imageSrc->imageData + j*imageSrc->widthStep))[i];
			firstLineHist[p]++;  
		}
	} //end for

	/******  Otsu method 找分析第一列光影變化的threshold  ******/
	//normalize histogram  
     int size=imageSrc->width;  
     for(int i=0;i<256;i++) {  
         firstLineHist[i]=firstLineHist[i]/size;  
     }  
       
     //average pixel value  
     float avgValue=0;  
     for(int i=0;i<256;i++) {  
         avgValue+=i*firstLineHist[i];  
     }  
   
     int threshold;    
     float maxVariance=0;  
     float w=0,u=0;  
     for(int i=0;i<256;i++) {  
         w+=firstLineHist[i];  
		 if (w == 0) continue;

         u+=i*firstLineHist[i];  
   
         float t=avgValue*w-u;  
         float variance=t*t/(w*(1-w));  
         if(variance>maxVariance) {  
             maxVariance=variance;  
             threshold = i;  
         }  
     }  
	 /******  Otsu method 找分析第一列光影變化的threshold  ******/
	 
	bool findingROI = false;
	int ROI_startIndex,ROI_endIndex;
	int NextROI_startIndex = 0;
	IplImage* ROI_temp; 

	for(int i=0;i<imageSrc->width;i++)
	{
		for(int j=0;j<1;j++)
		{
			//對圖片橫軸第一列取pixel值
			int p = ((uchar *)(imageSrc->imageData + j*imageSrc->widthStep))[i];
			//依圖片第一列依序取得pixel值 若與threshold大小相差15則開始尋找均勻亮度區域的ROI並定義ROI起始點
			if( p <= threshold && !findingROI && abs(p-threshold) > 15)
			{
				findingROI = true;
				ROI_startIndex = i;
			}
			//符合ROI條件則繼續往後尋找ROI範圍
			else if( p <= threshold && findingROI)
			{
				ROI_endIndex = i;
			}
			//不符合ROI條件時則定義ROI結束點並對ROI做Otsu二值化
			else 
			{
				findingROI = false;
				//如ROI大小符合設定的條件則進行分割做Otsu動作 這邊條件為ROI寬度大於圖片寬度1/10以上
				if( ROI_endIndex - ROI_startIndex >= imageSrc->width/10 )
				{	

					if(ROI_startIndex == 0)
					{
						cvSetImageROI( imageSrc, cvRect( 0, 0, ROI_endIndex, imageSrc->height ) );
						cvSetImageROI( resultImage, cvRect( 0, 0, ROI_endIndex, imageSrc->height ) );
						
						ROI_temp = cvCreateImage( cvGetSize( imageSrc ) , 8 , 1 );
						cvCopyImage(imageSrc,ROI_temp);
						OtsuThreshold(ROI_temp);
						cvCopyImage(ROI_temp,resultImage);

						NextROI_startIndex  = ROI_endIndex;					
				    }

					else
					{	
						if(NextROI_startIndex == 0)
						{
							cvSetImageROI( imageSrc, cvRect( 0, 0, ROI_startIndex, imageSrc->height ) );
							cvSetImageROI( resultImage, cvRect( 0, 0, ROI_startIndex, imageSrc->height ) );
							
							ROI_temp = cvCreateImage( cvGetSize( imageSrc ) , 8 , 1 );
							cvCopyImage(imageSrc,ROI_temp);
							OtsuThreshold(ROI_temp);
							cvCopyImage(ROI_temp,resultImage);

							NextROI_startIndex = ROI_startIndex + 1 ;
						}

						cvSetImageROI( imageSrc, cvRect( ROI_startIndex, 0, ROI_endIndex-ROI_startIndex+1, imageSrc->height ) );
						cvSetImageROI( resultImage, cvRect( ROI_startIndex, 0, ROI_endIndex-ROI_startIndex+1, imageSrc->height ) );

						ROI_temp = cvCreateImage( cvGetSize( imageSrc ) , 8 , 1 );
			     		
						NextROI_startIndex  = ROI_endIndex + 1;
			
						cvCopyImage( imageSrc , ROI_temp );
						OtsuThreshold( ROI_temp );
						cvCopyImage( ROI_temp , resultImage );

						cvResetImageROI( imageSrc );
					}
						
					ROI_startIndex = 0;
					ROI_endIndex = 0;
				}
			}	
		}

		//若尋找ROI過程至圖片結束未找到ROI結束點，則設為圖片第一列最後一點
		if(i == imageSrc->width-1 && findingROI)
		{
			findingROI = false;
			ROI_endIndex = imageSrc->width - 1;

			if(ROI_endIndex - ROI_startIndex >= imageSrc->width/10)
			{
				cvSetImageROI( imageSrc, cvRect( ROI_startIndex , 0, imageSrc->width - ROI_startIndex + 1 , imageSrc->height ) );
				cvSetImageROI( resultImage, cvRect( ROI_startIndex , 0, imageSrc->width - ROI_startIndex + 1 , imageSrc->height ) );

				ROI_temp = cvCreateImage( cvGetSize( imageSrc ) , 8 , 1 );
				cvCopyImage(imageSrc,ROI_temp);
				OtsuThreshold(ROI_temp);
				cvCopyImage(ROI_temp,resultImage);
			}
			else
			{
				cvSetImageROI( imageSrc, cvRect( NextROI_startIndex , 0, imageSrc->width - NextROI_startIndex + 1 , imageSrc->height ) );
				cvSetImageROI( resultImage, cvRect( NextROI_startIndex , 0, imageSrc->width - NextROI_startIndex + 1 , imageSrc->height ) );

				ROI_temp = cvCreateImage( cvGetSize( imageSrc ) , 8 , 1 );
				cvCopyImage(imageSrc,ROI_temp);
				OtsuThreshold(ROI_temp);
				cvCopyImage(ROI_temp,resultImage);
			}
		}
		//若尋找至圖片結束未再標示ROI，則將上一個ROI結束位置(或圖片起始處) 至 圖片結束處設為ROI做Otsu二值化
		else if(i == imageSrc->width-1 && !findingROI)
		{
			if(NextROI_startIndex < imageSrc->width-1)
			{
				cvSetImageROI( imageSrc, cvRect( NextROI_startIndex , 0, imageSrc->width - NextROI_startIndex  , imageSrc->height ) );
				cvSetImageROI( resultImage, cvRect( NextROI_startIndex , 0, imageSrc->width - NextROI_startIndex , imageSrc->height ) );
				
				ROI_temp = cvCreateImage( cvGetSize( imageSrc ) , 8 , 1 );
				cvCopyImage(imageSrc,ROI_temp);
				OtsuThreshold(ROI_temp);
				cvCopyImage(ROI_temp,resultImage);
			}
		} 
	} //end for

	cvResetImageROI( resultImage );
	cvReleaseImage( &ROI_temp );
	cvReleaseImage ( &imageSrc );
	imageSrc =  resultImage;

	return imageSrc;
}

//otsu method
void imageProcess::OtsuThreshold(IplImage* src)  
{  
	 CvRect ROI_info = cvGetImageROI(src);
     int height=ROI_info.height;  
     int width=ROI_info.width;   
 
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
	 
     cvThreshold(src,src,threshold,255,CV_THRESH_BINARY);  

}

//字元影像正規化
IplImage *imageProcess::scaleNormalization ( IplImage *imageSrc, int normalizedWidth,  int normalizedHeight)
{
	IplImage *normalizedImg = cvCreateImage( cvSize( normalizedWidth,normalizedHeight ) ,IPL_DEPTH_8U ,1); 
	cvSet( normalizedImg, CV_RGB(255,255,255) );

	float scaleFactorForWidth = normalizedWidth / (float)imageSrc->width;
	float scaleFactorForHeight = normalizedHeight / (float)imageSrc->height;

	float scaleFactor = scaleFactorForWidth < scaleFactorForHeight ? scaleFactorForWidth : scaleFactorForHeight;
	
	IplImage *resizedImage = cvCreateImage( cvSize( (int)(imageSrc->width*scaleFactor), (int)(imageSrc->height*scaleFactor) ) ,IPL_DEPTH_8U ,1);
	cvResize(imageSrc, resizedImage);

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
	cvReleaseImage(&imageSrc);
	imageSrc = normalizedImg;

	return imageSrc;
}

//點字影像校正處理
void imageProcess::brailleWord(IplImage *imgSrc)
{
	IplImage *imgSrc2 = cvCreateImage(cvGetSize(imgSrc) , IPL_DEPTH_16S, 1);

	IplConvKernel* strel = cvCreateStructuringElementEx( 3, 3, 1, 1, CV_SHAPE_ELLIPSE );

	cvLaplace( imgSrc, imgSrc2  );
	cvConvertScaleAbs(imgSrc2, imgSrc, 1, 0);
	cvNot( imgSrc, imgSrc );

	cvSmooth( imgSrc, imgSrc,  CV_GAUSSIAN, 3, 0, 0, 0 );

	cvThreshold(imgSrc,imgSrc,cvSolveOtsuThreshold(imgSrc),255,CV_THRESH_BINARY);

	cvNot(imgSrc, imgSrc);
	cvDilate(imgSrc, imgSrc, strel,1);
	cvErode(imgSrc, imgSrc, strel,1);
	cvNot(imgSrc, imgSrc);
}


//弧形排列校正
IplImage *imageProcess::curvedAlignAdjustment (IplImage *img)
{
	IplImage *cc_color, *cc_labeled, *cc_binary; /*IplImage is an image in OpenCV*/		//宣告各類使用到的圖片

	CvMemStorage *mem;
    CvSeq *contours, *ptr, *ptr2;
	CvMat* fittingCurve;
	
	cc_color = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	cc_labeled = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cc_binary = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);

	cvSet(cc_color,cvScalar(255,255,255));			/*設定初始為白色*/
	cvSet(cc_labeled,cvScalar(255,255,255));		/*設定初始為白色*/

	cvThreshold(img, img, cvSolveOtsuThreshold(img), 255, CV_THRESH_BINARY);
	cvThreshold(img, cc_binary, cvSolveOtsuThreshold(img), 255, CV_THRESH_BINARY);
	fittingCurve = pixelCurveFitting(img);

	cvNot(img, img);
    contours = extract_and_filter_CC(img, &mem, sizeFilter);    

	//計算連通元件個數
	int CC_count = 0;
	for (ptr = contours; ptr != NULL; ptr = ptr->h_next) 
		CC_count++;

	//宣告連通元件序列的陣列，用於設定及判斷存在狀態
	bool*CC_array;
	CC_array = ( bool* ) malloc( CC_count * sizeof CC_array );
	   
	int cc_id = 0;	//用於連通元件標籤的ID
	int maxAvgLength  = 0;    //connected comp onent 最大高寬平均(高加寬除以二) (用於設定球的直徑大小)

	for (ptr = contours; ptr != NULL; ptr = ptr->h_next) {
        
		CvScalar color = CV_RGB( 0, 0, 0 );
        cvDrawContours(cc_color, ptr, color, CV_RGB(0,0,0), -1, CV_FILLED, 8, cvPoint(0,0));

		CvRect rect;
		rect = cvBoundingRect(ptr,0);    
		int rectAvgLength  = ( rect.width + rect.height ) / 2;
		if( rectAvgLength > maxAvgLength)
			maxAvgLength = rectAvgLength;
/*
		//將connected component畫bounding box    
		cvLine( cc_color, cvPoint(rect.x,rect.y) , cvPoint(rect.x+rect.width, rect.y), CV_RGB(0,0,255), 1, 8 );
		cvLine( cc_color, cvPoint(rect.x,rect.y) , cvPoint(rect.x, rect.y+rect.height), CV_RGB(0,0,255), 1, 8 );
		cvLine( cc_color, cvPoint(rect.x+rect.width,rect.y) , cvPoint(rect.x+rect.width, rect.y+rect.height), CV_RGB(0,0,255), 1, 8 );
		cvLine( cc_color, cvPoint(rect.x,rect.y+rect.height) , cvPoint(rect.x+rect.width, rect.y+rect.height), CV_RGB(0,0,255), 1, 8 );
*/
		cvDrawContours(cc_labeled, ptr, CV_RGB(cc_id,cc_id,cc_id), color , -1, CV_FILLED, 8, cvPoint(0,0));
		CC_array[cc_id]  = true;
		cc_id++;
    }

	double a = cvmGet( fittingCurve, 0, 0 ),
		   b = cvmGet( fittingCurve, 1, 0 ),
		   c = cvmGet( fittingCurve, 2, 0 );
	
	bool moveDown = true;		/*決定是否將fitting出來的拋物線移到所有字下方作為球在字體底下滾的路徑*/
	
	while(moveDown)
	{
		moveDown = false;
		for( int j = 0 ; j < cc_labeled->width ; j++ )
		{	
			int i = (int) ( a*j*j+b*j+c );  

			if( i < 0  ||  i>= cc_labeled->height)
				continue;
			
			if ( ((uchar *)(cc_labeled->imageData+i*cc_labeled->widthStep))[j] != 255 )
			{
				moveDown = true;
				break;
			}
		}
		c += 5;	//下移5單位(為了減少次數)
	}

	int radius = maxAvgLength; 

	CvSeq *fittedPoint = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq) , sizeof(CvPoint) , mem);
	CvBox2D ellipse;

	/***************     球滾字體底邊找 fitting curve      ***************/
	
	for( int j = 0 ; j < cc_color->width ; j++ )
	{
		int i = (int)(a*j*j+b*j+c);    
		int touchValue1;
		bool touchOne = false;
		CvPoint pointOne;
		
		if( i >= 0 && i< cc_color->height)
		{	
			i += radius;

			while(!touchOne && i>=0) {

			for(int k = -radius; k <= radius ; k++)
			{
				int circleX = k+j;
				int circleY = cc_color->height - (int)( sqrt( (float)(radius*radius - (k)*(k))) + (cc_color->height-i) );
			
				if( circleY < 0 || circleY >=  cc_color->height || circleX  >= cc_color->width || circleX < 0 )
					continue;

				if ( ((uchar *)(cc_labeled->imageData+circleY*cc_labeled->widthStep))[circleX] != 255 )
				{
					if(!touchOne)
					{
						touchValue1 = ((uchar *)(cc_labeled->imageData+circleY*cc_labeled->widthStep))[circleX];
						pointOne.x = circleX;
						pointOne.y = circleY;
						touchOne = true;
						break;
					}
				}
			} // end for

			if(touchOne)
			{
				for(int k = -radius; k <= radius ; k++)
				{
					int circleX = k+j;
					int circleY = cc_color->height - (int)( sqrt( (float)(radius*radius - (k)*(k))) + (cc_color->height-i) );
					
					if( circleY < 0 || circleY >=  cc_color->height || circleX  >= cc_color->width || circleX < 0 )
						continue;

					for( int p = 0 ; p < 9 ; p++ )
					{
						int squarePosition_x = circleX + p%3-1;
						int squarePosition_y = circleY + p/3-1;

						if( squarePosition_y < 0 || squarePosition_y >=  cc_color->height || squarePosition_x  >= cc_color->width || squarePosition_x < 0 )
							continue;

						if( ((uchar *)(cc_labeled->imageData+(squarePosition_y)*cc_labeled->widthStep))[squarePosition_x] != touchValue1 && 
							((uchar *)(cc_labeled->imageData+(squarePosition_y)*cc_labeled->widthStep))[squarePosition_x] != 255 )
						{
							for(int g = -radius; g <= radius ; g++)
							{	
								int circle2_X = g+j;
								int circle2_Y = cc_color->height - (int)( sqrt( (float)(radius*radius - (g)*(g))) + (cc_color->height-i) );
							}

							cvSeqPush(fittedPoint, &cvPoint(pointOne.x,pointOne.y));
							cvSeqPush(fittedPoint, &cvPoint(squarePosition_x,squarePosition_y));

							break;
						}
					}

				}
			}

			i--;
			
			} // end while
		}	// end if
	}	//end for loop

	/***************     球滾字體底邊找 fitting curve      ***************/

	int fittedWidth;
	int fittedHeight = cc_labeled->height;
	
	if (fittedPoint->total >= 6) 
	{
		ellipse = cvFitEllipse2(fittedPoint); 
	}
	else
	{
		printf(" Can't not fitting. ");
		return 0;
	}

	fittedWidth =  ellipse.size.height > ellipse.size.width ? (int) ellipse.size.height : (int) ellipse.size.width ;

	IplImage *resultImage = cvCreateImage(cvSize( 2*fittedWidth, fittedHeight ), 8, 1);
	cvSet(resultImage,cvScalar(255,255,255));


	vector<int> *character_components = new vector<int>[CC_count];

	for(int i = 0 ; i < CC_count ; i++)
		character_components[i].push_back(i);

	//偵測一個字元是否有兩個以上的component，如有，將之相連
	for( float i = ellipse.angle ; i < ellipse.angle + 180 ; i += 0.25 )
	{
		double x0 = (ellipse.size.width/2)  * cos((float)i*(CV_PI/180.0));
		double y0 = (ellipse.size.height/2) * sin((float)i*(CV_PI/180.0));

		double x1 = ellipse.center.x + x0 * cos((float)ellipse.angle*(CV_PI/180.0)) - y0 * sin((float)ellipse.angle*(CV_PI/180.0));
		double y1 = ellipse.center.y + y0 * cos((float)ellipse.angle*(CV_PI/180.0)) + x0 * sin((float)ellipse.angle*(CV_PI/180.0));

		if(y1 < 0 || y1 >=  cc_color->height || x1  >= cc_color->width || x1 < 0 || x0 > 0 )
			continue;

		x0 = (ellipse.size.width/2)  * cos((float)(i+0.25)*(CV_PI/180.0));
		y0 = (ellipse.size.height/2) * sin((float)(i+0.25)*(CV_PI/180.0));

		double x2 = ellipse.center.x + x0 * cos((float)ellipse.angle*(CV_PI/180.0)) - y0 * sin((float)ellipse.angle*(CV_PI/180.0));
		double y2 = ellipse.center.y + y0 * cos((float)ellipse.angle*(CV_PI/180.0)) + x0 * sin((float)ellipse.angle*(CV_PI/180.0));
		
		if( y2 < 0 || y2 >=  cc_color->height || x2  >= cc_color->width || x2 < 0 || x0 > 0 )
			continue;


		((uchar *)(cc_binary->imageData+(int)y1*cc_binary->widthStep))[(int)x1] = 127;
		bool fineOneCC = false;
		int findingRecord[2] = {0};

		//計算橢圓切線斜率(為求計算簡單用鄰近兩點連成直線代替計算切線)
		double m = (y2-y1) / (x2-x1);		

		for(int j = 0 ; j< cc_labeled->height ; j++)
		{
			//y為參數帶入切線方程式求x
			double x = (j-y1)/m + x1;		
		}

		//橢圓切線垂直線的常數項
		double nb = x1 + m*y1;		

		//斜率小於1的用x當參數求y，以免斷續現象
		if( abs(-(1/m)) < 1 )
		{
			if(x1 - ellipse.center.x < 0)
			{
				for(int x = (int)x1 ; x >=  (int)x1 - (cc_labeled->height-1) ; x--)
				{
					if(x < 0)
						break;

					double y = (nb - x) / (m) ;

					if( (x1 - ellipse.center.x) * (x - x1) < 0 )
						continue;
					
					if( y<=y1 && (int)y < cc_color->height && (int)y >= 0)
					{
						if ( ((uchar *)(cc_labeled->imageData+(int)y*cc_labeled->widthStep))[x] != 255 )
						{
							if( !fineOneCC )
							{
								findingRecord[0] = ((uchar *)(cc_labeled->imageData+(int)y*cc_labeled->widthStep))[x] ;
								fineOneCC = true;
							}
							else if (fineOneCC && ((uchar *)(cc_labeled->imageData+(int)y*cc_labeled->widthStep))[x] != findingRecord[0])
							{
								findingRecord[1] = ((uchar *)(cc_labeled->imageData+(int)y*cc_labeled->widthStep))[x] ;
								fineOneCC = false;
								CvScalar holeColor = CV_RGB( 0, 0, 0 );
								CvScalar CC_Color = CV_RGB(findingRecord[0],findingRecord[0],findingRecord[0]);

								character_components[findingRecord[0]].push_back(findingRecord[1]);
								character_components[findingRecord[1]].pop_back();

								ptr2 = contours;
								for( int q=0; q<findingRecord[1] ; q++ )
								{	
									if( CC_array[q] ==true )
										ptr2 = ptr2->h_next;
								}

								cvDrawContours( cc_labeled, ptr2, CC_Color, holeColor, -1, CV_FILLED, 8, cvPoint(0,0) );
								break;
							}
						}
					}
				}
			}

			else if(x1 - ellipse.center.x >= 0)
			{
				for(int x = (int)x1 ; x <=  (int)x1 + (cc_labeled->height-1) ; x++)
				{
					if(x >= cc_labeled->width)
						break;

					double y = (nb - x) / (m) ;

					if( (x1 - ellipse.center.x) * (x - x1) < 0 )
						continue;
					
					if( y<=y1 && (int)y < cc_color->height && (int)y >= 0)
					{
						if ( ((uchar *)(cc_labeled->imageData+(int)y*cc_labeled->widthStep))[x] != 255 )
						{
							if( !fineOneCC )
							{
								findingRecord[0] = ((uchar *)(cc_labeled->imageData+(int)y*cc_labeled->widthStep))[x] ;
								fineOneCC = true;
							}
							else if (fineOneCC && ((uchar *)(cc_labeled->imageData+(int)y*cc_labeled->widthStep))[x] != findingRecord[0])
							{
								findingRecord[1] = ((uchar *)(cc_labeled->imageData+(int)y*cc_labeled->widthStep))[x] ;
								fineOneCC = false;
								CvScalar holeColor = CV_RGB( 0, 0, 0 );
								CvScalar CC_Color = CV_RGB(findingRecord[0],findingRecord[0],findingRecord[0]);

								character_components[findingRecord[0]].push_back(findingRecord[1]);
								character_components[findingRecord[1]].pop_back();

								ptr2 = contours;
								for( int q=0; q<findingRecord[1] ; q++ )
								{	
									if( CC_array[q] ==true )
										ptr2 = ptr2->h_next;
								}

								cvDrawContours( cc_labeled, ptr2, CC_Color, holeColor, -1, CV_FILLED, 8, cvPoint(0,0) );

								break;
							}
						}
						
					}
				}
			}
		}

		//斜率大於1用y當參數代入求x
		else
		{
			for(int y = cc_labeled->height-1 ; y >=  0 ; y--)
			{
				double x = nb - m*y;

				if( (y1 - ellipse.center.y) * (y - y1) < 0 )
					continue;
				
				if( (int)x < cc_color->width && (int)x >= 0)
				{
					if ( ((uchar *)(cc_labeled->imageData+y*cc_labeled->widthStep))[(int)x] != 255 )
						{
							if( !fineOneCC )
							{
								findingRecord[0] = ((uchar *)(cc_labeled->imageData+y*cc_labeled->widthStep))[(int)x] ;
								fineOneCC = true;
							}
							else if (fineOneCC && ((uchar *)(cc_labeled->imageData+y*cc_labeled->widthStep))[(int)x] != findingRecord[0])
							{
								findingRecord[1] = ((uchar *)(cc_labeled->imageData+y*cc_labeled->widthStep))[(int)x] ;
								fineOneCC = false;
								CvScalar holeColor = CV_RGB( 0, 0, 0 );
								CvScalar CC_Color  = CV_RGB(findingRecord[0],findingRecord[0],findingRecord[0]);

								character_components[findingRecord[0]].push_back(findingRecord[1]);
								character_components[findingRecord[1]].pop_back();

								ptr2 = contours;
								for( int q=0; q<findingRecord[1] ; q++ )
								{	
									if( CC_array[q] ==true )
										ptr2 = ptr2->h_next;
								}

								cvDrawContours( cc_labeled, ptr2, CC_Color, holeColor, -1, CV_FILLED, 8, cvPoint(0,0) );

								break;
							}
						}
					
				}
			}
		}

	}

	IplImage *copyDst;
	IplImage *dst;
	IplImage *paint = cvCreateImage(cvGetSize(cc_binary) , 8 , 1);
	CvSeq *lineFittingPoint = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq) , sizeof(CvPoint) , mem);
	int resultImageIndex = 0;

	CvSeq **component_temp = new CvSeq*[CC_count];

	ptr = contours;
	
	for ( int k = 0; k < CC_count ; k++ )
	{
		component_temp[k] = cvCloneSeq(ptr, mem);
		ptr =  ptr->h_next;
	}

	bool *component_exist = new bool[CC_count];

	for(int i = 0 ; i < CC_count ; i++)
		component_exist[i] = true;


	while ( contours != NULL )
	{
		cvClearSeq( lineFittingPoint );

		CvSeq * theLeft;
		int position_x = cc_labeled->width;

		int component_index;
		int i = 0,j = 0;

		for ( theLeft = contours;  theLeft != NULL;  theLeft =  theLeft->h_next)
		{
			CvRect box = cvBoundingRect( theLeft, 0 );
			
			if ( (box.x + box.width/2) < position_x )
			{
				position_x = box.x + box.width/2;
				ptr = theLeft;
				component_index = i;
			}

			i++;
		}

		for (i = 0 ; i < component_index ; i++)
		{
			

			while( !component_exist[j] )
				j++;

			j++;

			while( !component_exist[j] )
				j++;
		}

		component_exist[j] = false;

		if( character_components[j].size() > 0 )
		{

		cvSet( paint, CV_RGB(255, 255, 255) );
		CvRect rect;
		rect = cvBoundingRect(ptr,0); 
		
		if( character_components[j].size() == 1 )
		{
			rect = cvBoundingRect(ptr,0);
			cvDrawContours( paint, ptr, CV_RGB(0, 0, 0), CV_RGB(255, 255, 255) , -1, CV_FILLED, 8, cvPoint(0,0) );
		}

		if( character_components[j].size() == 2 )
		{
			CvRect rect2;
			rect2 = cvBoundingRect( component_temp[ character_components[j][1] ],1 );
			
			rect.width = max(rect.x + rect.width, rect2.x + rect2.width) - min(rect.x, rect2.x);
			rect.height = max(rect.y + rect.height, rect2.y + rect2.height) - min(rect.x, rect2.y);
			rect.x = min(rect.x, rect2.x);
			rect.y = min(rect.x, rect2.y);
			
			cvDrawContours( paint, ptr, CV_RGB(0, 0, 0), CV_RGB(255, 255, 255) , -1, CV_FILLED, 8, cvPoint(0,0) );	
			cvDrawContours( paint, component_temp[ character_components[j][1] ], CV_RGB(0, 0, 0), CV_RGB(255, 255, 255) , -1, CV_FILLED, 8, cvPoint(0,0) );
		}


		cvSetImageROI( paint, rect );
		cvSetImageROI( cc_binary, rect );
		
		int hypotenuse  =(int) sqrt( (float)(rect.width * rect.width + rect.height * rect.height)  );

		copyDst = cvCreateImage(cvSize(rect.width,rect.height),8,1);

		cvCopyImage(cc_binary,copyDst);
		cvResetImageROI(cc_binary ); 

		for( int i = 0 ; i < copyDst->height ; i++ )
		{
			for( int j = 0 ; j < copyDst->width ; j++ )
			{
				if( ((uchar *)(copyDst->imageData+i*copyDst->widthStep))[j] == 127 )
				{
					cvSeqPush(lineFittingPoint, &cvPoint(j,i));
				}
			}
		}

		cvCopyImage(paint,copyDst);
		cvResetImageROI( paint ); 

		dst = cvCreateImage( cvSize( hypotenuse, hypotenuse ), 8, 1 );

		if(lineFittingPoint->total >= 2)
		{
			float line[4];
			double angle;

			cvFitLine(lineFittingPoint,CV_DIST_L2,0,0.01,0.01,line);
			angle = atan(line[1]/line[0]) * 180 / CV_PI ;

			//printf("angle = %f", angle);

			float m[6];
			// Matrix m looks like:
			//
			// [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
			// [ m3  m4  m5 ]       [ A21  A22   b2 ]
			//
			CvMat M = cvMat (2, 3, CV_32F, m);
			int w = copyDst->width;
			int h = copyDst->height;

			// Rotation center needed for cv2DRotationMatrix
			CvPoint2D32f pt = cvPoint2D32f(w / 2, h / 2);
			cv2DRotationMatrix(pt, angle , 1.0, &M);

			/*
			m[0] = (float) ( cos (-angle  * CV_PI / 180.));
			m[1] = (float) ( sin (-angle  * CV_PI / 180.));
			m[3] = -m[1];
			m[4] = m[0];
			// 將旋轉中心移至圖像中間
			m[2] = w * 0.5f;
			m[5] = h * 0.5f;	
			*/
			//  dst(x,y) = A * src(x,y) + b

			m[2] += (dst->width  - w) / 2;
			m[5] += (dst->height - h) / 2;

			cvZero (dst);
			cvWarpAffine(
				  copyDst ,
				  dst,
				  &M,
				  CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS,
				  cvScalarAll(255)
			);
		}

		int baseLineIndex = 0;

		for( int i = dst->height - 1 ; i  >= 0 ; i-- )
		{
			for( int j = 0 ; j < dst->width ; j++ )
			{
				if(	 ( (uchar *)(dst->imageData + i * dst->widthStep) ) [ j ] == 0 )
				{
					baseLineIndex = i;
					cvSetImageROI (dst, cvRect(0, 0, dst->width,  baseLineIndex) );
					break;
				}
			}

			if( baseLineIndex != 0 )
				break;
		}

		cvSetImageROI( resultImage, cvRect(resultImageIndex,resultImage->height/2 - baseLineIndex, dst->width, baseLineIndex));

		cvCopyImage ( dst, resultImage ) ;
		cvResetImageROI ( resultImage );
		cvResetImageROI ( dst );
		resultImageIndex += hypotenuse-10;
		
		}

		 if (ptr == contours) {
				if(ptr->h_next == NULL)
				{
					contours = NULL;
					continue;
				}
				
                contours = ptr->h_next;
                ptr = contours;
                ptr->h_prev = NULL;
            } 
		 else {
			ptr->h_prev->h_next = ptr->h_next;
            if (ptr->h_next != NULL)
				ptr->h_next->h_prev = ptr->h_prev;
		 }
		 

	}	//end connected component while loop

	cvSmooth(resultImage, resultImage, CV_MEDIAN);

    cvReleaseImage(&img); 
    cvReleaseImage(&cc_color);
	cvReleaseImage(&cc_labeled);
	cvReleaseImage(&cc_binary);
	cvReleaseImage(&dst);
	
	return resultImage;
}


void imageProcess::cvThin( IplImage* src, IplImage* dst, int iterations ) 
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