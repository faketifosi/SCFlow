#ifndef _RECEPTORS_H_
#define _RECEPTORS_H_

#include <vector>

using namespace std;

class Receptor
{
	int		x1, y1, x2, y2;
	int		left, top, right, bottom;
	float	k, z;
	float	a, b, c, d;

public:
	// X1 property
	int X1();
	// Y1 property
	int Y1();
	// X2 property
	int X2();
	// Y2 property
	int Y2();

	// Constructor
	Receptor(int x1, int y1, int x2, int y2);
	
	// Check receptor state
	bool GetReceptorState(int x, int y);

};




class Receptors
{

public:
	
	int img_width;
	int img_height;

	vector<Receptor> InnerList;

	// Constructor
	Receptors();
	Receptors(int count);

	// Add new receptor to the sequence
	void Add(Receptor receptor);

	// Generate new receptors
	void Generate(int count);
	void Generate();
	
	
	// Get receptors state
	int* GetReceptorsState(IplImage *image);

};

#endif