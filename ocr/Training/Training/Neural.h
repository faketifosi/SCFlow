#ifndef _NEURAL_H_
#define _NEURAL_H_


#include <string>
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <exception>

using namespace std;

//輸入層 struct (raw data + descriptor)
struct PreInput
{
	double Value;
	double *Weights;
};


//中間層 struct
struct Input
{
	double InputSum;
	double Output;
	double Error;
	double *Weights;
};

//輸出層 struct (訓練data對應的名稱)
struct Output
{

	double InputSum;
	double output;
	double Error;
	double Target;
	string Value;

};


struct Dictionary
{
	string filename;
	double *matrix;

};

struct TrainMatch
{
	string nameH;
	double MatchRateH;
	string nameL;
	double MatchRateL;
};


class NeuralNetwork
{
public:
	NeuralNetwork();
	//Receptors receptors();


	int PreInputNum;
	int InputNum;
	int OutputNum;


	PreInput *PreInputLayer;
	Input *InputLayer;
	Output *OutputLayer;

	Dictionary *TrainingSetNow;

	double learningRate;
	double maximumError;
	int maximumIteration;

	int max_ImageHeight;
	int max_ImageWidth;
	unsigned int NumOfPatterns;

	string bstring;
	Dictionary *TrainingSet;

	TrainMatch *TS;
	void classify();
	void setBP2NNLayer(int,int,int,int);
	void setTrainingSet(Dictionary *);
	void setmaxErrAndIter(double,int);
	void InitializeNetworkBP2();

	void Recognize(double *,string &, double &, string &,double &);
	double F(double);

	bool Train();
	void ForwardPropagate(double *, string);
	void BackPropagate();
	double GetError();
	void saveNetwork(char *);

	void InitializeSettings();

	void GenerateTrainingSet ();
	void CreateNeuralNetwork(int);

	void ToTrain();
	void RecognizeTS(char *);

	virtual ~NeuralNetwork();

protected:
private:


};

#endif