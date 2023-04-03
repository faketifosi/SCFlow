#define COMMON  1
#define CURVE_ALIGNMENT	2
#define BRAILLE 3

using namespace std;



class ImageAutoCut {
public:

	int recognitionType;

	ImageAutoCut(void);
	void autocut(char *path);
};

