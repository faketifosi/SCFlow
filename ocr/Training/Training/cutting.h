#pragma comment(lib,"cv210.lib")
#pragma comment(lib,"cxcore210.lib")
#pragma comment(lib,"highgui210.lib")

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <math.h>

using namespace std;



class ImageAutoCut {
public:

	void autocut(char *path);
};

