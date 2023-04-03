#pragma once

class imageProcess
{
public:
	imageProcess(void);
	int imageProcess::cvSolveOtsuThreshold(IplImage*);
	IplImage *cvThresholdOtsu(IplImage *);
	IplImage *columnAverageHistogram(IplImage *,IplImage*);
	IplImage *scaleNormalization( IplImage *,int ,int );

	IplImage *cuttingROItoOtsu(IplImage *);
	IplImage *cuttingErrorConnect(IplImage *);
	IplImage *curvedAlignAdjustment (IplImage *);
	
	void OtsuThreshold(IplImage *);
	void brailleWord(IplImage *);
	void cvThin( IplImage*, IplImage*, int iterations = 1 ); 
};
