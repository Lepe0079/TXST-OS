#include "pages.h"

pFrame::pFrame(){srand(seed);}

pFrame::pFrame(int maximum, int newSeed):max(maximum)
{
    seed = newSeed;
    srand(seed);
}
void pFrame::fillFrame()
{
    //fill the frame while respecting the maximum number of entries
    for(int i = 0; i < max; ++i)
        frame.push_front((rand()%numRange+1));
}
int pFrame::itemCount()const{
    return frame.size();
}
int pFrame::popFront()
{
    int temp = frame.front();
    frame.pop_front();
    return temp;
}
