// receptors.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "receptors.h"



#define   Max(a,b)   ((a)   >   (b)   ?   (a)   :   (b)) 
#define   min(a,b)   ((a)   <   (b)   ?   (a)   :   (b)) 



	int Receptor::X1()
	{
		return x1;
	}
	// Y1 property
	int Receptor::Y1()
	{
		return y1;
	}
	// X2 property
	int Receptor::X2()
	{
		return x2; 
	}
	// Y2 property
	int Receptor::Y2()
	{
		return y2; 
	}

	// Constructor
	Receptor::Receptor(int x1, int y1, int x2, int y2)
	{			
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;

		left	= min(x1, x2);
		right	= Max(x1, x2);
		top		= min(y1, y2);
		bottom	= Max(y1, y2);

		if (x1 != x2)
		{
			k = (float) (y2 - y1) / (float) (x2 - x1);
			z = (float) y1 - k * x1;

			a = (float) y1 - y2;
			b = (float) x2 - x1;
			c = (float) y1 * (x1 - x2) + x1 * (y2 - y1);
			d = (float) sqrt((float)a * a + b * b);
		}
	}

	// Check receptor state
	bool Receptor::GetReceptorState(int x, int y)
	{
		// check, if the point is in receptors bounds
		if ((x < left) || (y < top) || (x > right) || (y > bottom))
			return false;

		// check for horizontal and vertical receptors
		if ((x1 == x2) || (y1 == y2))
			return true;

		// check if the point is on the receptors line

		// more fast, but not very accurate
//			if ((int)(k * x + z - y) == 0)
//				return true;

		// more accurate version
		if (abs(a * x + b * y + c) / d < 1)
			return true;

		return false;
	}



	// Constructor
	Receptors::Receptors()
	{
		img_width = 30;
		img_height = 40;

		Generate();
	}

	Receptors::Receptors(int count)
	{
		img_width = 30;
		img_height = 40;

		Generate(count);
	}

	// Add new receptor to the sequence
	void Receptors::Add(Receptor receptor)
	{
		InnerList.push_back(receptor);
	}

	// Generate new receptors
	void Receptors::Generate(int count)
	{
		int	maxX = img_width;
		int maxY = img_height;
		int i = 0;

		while (i < count)
		{
			int x1 = rand() % maxX +1;
			int y1 = rand() % maxY +1;
			int x2 = rand() % maxX +1;
			int y2 = rand() % maxY +1;;

			int	dx = x1 - x2;
			int dy = y1 - y2;
			int length = (int) sqrt( (float) (dx * dx + dy * dy) );

			// avoid too short and too long receptors
			if ((length < 3) || (length > 8))
				continue;

			Receptor receptor(x1, y1, x2, y2);

			InnerList.push_back(receptor);
			i++;
		}
	}

	void Receptors::Generate()
	{
		int	maxX = img_width;
		int maxY = img_height;
		
		
		Receptor receptor1(2, 8, 2, 17);
		InnerList.push_back(receptor1);
		Receptor receptor2(13, 8, 13, 17);
		InnerList.push_back(receptor2);
		Receptor receptor3(4, 4, 12, 4);
		InnerList.push_back(receptor3);
		Receptor receptor4(4, 22, 12, 22);
		InnerList.push_back(receptor4);
		Receptor receptor5(4, 10, 7, 7);
		InnerList.push_back(receptor5);
		Receptor receptor6(4, 14, 7, 17);
		InnerList.push_back(receptor6);
		Receptor receptor7(4, 20, 7, 23);
		InnerList.push_back(receptor7);
		Receptor receptor8(8, 7, 11, 10);
		InnerList.push_back(receptor8);
		Receptor receptor9(8, 17, 11, 14);
		InnerList.push_back(receptor9);
		Receptor receptor10(8, 4, 11, 7);
		InnerList.push_back(receptor10);		
	}

	// Get receptors state
	int* Receptors::GetReceptorsState(IplImage *image)
	{
		int		width = img_width;
		int		height = img_height;
		int		n = InnerList.size();
		int*	state = new int[n];

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				// check for black pixel
				if (((uchar *)(image->imageData + y*image->widthStep))[x] == 0)
				{
					for (int i = 0; i < n; i++)
					{
						// skip already activated receptors
						if (state[i] == 1)
							continue;

						if ((InnerList[i].GetReceptorState(x, y)))
							state[i] = 1;
						else
							state[i] = 0;
					}
				}
			}
		}

		return state;
	}

