#include "d10.h"
#include <cstdlib>


int D10::roll(int dieCount, bool dblSuccess, int dblThreshold)
{

    int successes = 0;
    int dieValue = 0;
    for (int die = 0; die < dieCount; die++)
    {

        dieValue = (std::rand()%10)+1;
        if(dieValue > 6 )
        {
            successes++;
            if(dblSuccess)
            {
                if(dieValue >= dblThreshold)
                    successes++;
            }
        }
    }
    return successes;
}


