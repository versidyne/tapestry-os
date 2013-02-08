// string.c -- Defines string manipulation routines.
//            Built for Vexis OS

#include "../core/common.h"
#include "string.h"

// Finds a string within a string.
int contains(char MyChar[], char Search[]) {
  
	int LoopOne = 0;
	int LoopTwo;
	int LoopThree;
	int MyCharSize = strlen(MyChar);
	int SearchSize = strlen(Search);
	int Yes = 0;
	
	while(LoopOne < MyCharSize)
	{
		if(MyChar[LoopOne] == Search[0])
		{
			LoopTwo = 0;
			LoopThree = LoopOne;
			while(LoopTwo < SearchSize)
			{
				if(MyChar[LoopThree] == Search[LoopTwo])
					Yes++;
				
				LoopTwo++;
				LoopThree++;
			} 
			if(Yes == SearchSize)
				return true;
		}        
		LoopOne++;
	}
	return false;
}
