#include <iostream>

using namespace std;

enum bool_3S {
  FALSE_3S = 0,
  TRUE_3S = 1,
  UNDEF_3S = -1
};

int main(void)
{
    bool_3S x=UNDEF_3S, y=TRUE_3S;




	if((x==TRUE_3S)&&(y==TRUE_3S))
    {
        cout << "TRUE";
    }
	else
	{
		if((x==FALSE_3S) || (y==FALSE_3S))
        {
            cout << "FALSE";
        }
		/*
		x AND 1 - x
		1 AND x - x
		x AND x	- x
		*/
		else
            {
            cout << "UNDEF";
            }

    }

}


