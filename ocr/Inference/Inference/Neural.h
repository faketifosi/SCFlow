#pragma comment(lib,"cv210.lib")
#pragma comment(lib,"cxcore210.lib")
#pragma comment(lib,"highgui210.lib")


using namespace std;


static int normalizedWidth = 30;
static int normalizedHeight = 40;


double* ToMatrix(IplImage *BM, int MatrixRowNumber, int MatrixColumnNumber);
int SearchDirectory(vector<string> &, const string &, const string &, bool);


struct PreInput
{
	double Value;
	double *Weights;
};


struct Input
{
	double InputSum;
	double Output;
	double Error;
	double *Weights;
};

struct Output
{
	double InputSum;
	double output;
	double Error;
	double Target;
	string Value;
};

class NeuralNetwork
{
public:
	
	NeuralNetwork();
	NeuralNetwork( string, char * );
	void set_member(string , char *);

	unsigned int NumOfPatterns;

	string bstring;

	void setBP2NNLayer(int,int,int,int);
			
	void setmaxErrAndIter(double,int);

	void Recognize(double *,string &, double &, string &,double &);

	double F(double);
	
	void loadNetwork(char *);

	void InitializeSettings();

	virtual ~NeuralNetwork();

	void operator =(const NeuralNetwork &net);


protected:
private:
	int PreInputNum;
	int InputNum;
	int OutputNum;

	PreInput *PreInputLayer;
	Input *InputLayer;
	Output *OutputLayer;

	int nodeNumberOfInputLayer;

};

