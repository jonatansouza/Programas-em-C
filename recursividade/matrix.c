/**
   *@author Jonatan Souza
 */

#include "matrix.h"

int flowers(int i){
	if (i==0)
		return 0;
	flowers(i-1);
	printf("teste %d\n", i);
	return 0;
}
