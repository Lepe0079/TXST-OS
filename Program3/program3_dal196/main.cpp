#include "pages.h"
#include <iostream>
#include <fstream>

using namespace std;

enum FrameAlgo{FIFO, LRU, OPT};
//metrics
int pagefault = 0;
int hit = 0;
//prototypes
void fifo(pFrame*, pFrame*);
void lru(pFrame*, pFrame*);
void opt(pFrame*, pFrame*);
void logger(string s);

int main(int argc, char* argv[])
{
   for(int i = 0; i < 4; ++i)
	{
		if(!argv[i])
		{
			std::cout << "please use the programs as follows"
			<< "\n./pageSim [type] [frame size] [seed]"
			<< "\neg:{ ./pageSim 0 30 1  }" << endl;
			return 0;
		}
	}

   int algo = atoi(argv[1]);
   int frameNum = atoi(argv[2]);
   int seed = atoi(argv[3]);

   pFrame* pageList = new pFrame(100, seed);
   pFrame* pageCont = new pFrame(frameNum, seed);
   pageList->fillFrame();

   //this is debug code to prove belady's anomaly occurs on FIFO
   //int belady[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
   // for(int i = 0; i < 12; ++i){
   //    pageList->pushBack(belady[i]);
   // }//3 frames = 9 faults, 4 frames = 10 faults   


   switch(FrameAlgo(algo)){
      case FIFO:
         fifo(pageList, pageCont);
         break;
      case LRU:
         lru(pageList, pageCont);
         break;
      case OPT:
         opt(pageList, pageCont);
         break;
      defaut:
         cout << "Please run the program with the correct parameters";
         break;
   } 
   
   cout << "There are ";
   logger(to_string(pagefault));
   cout << " Page Faults" << endl;
   return 0;
}

//declarations
void fifo(pFrame* pageList, pFrame* pageCont)//FIFO ALGO
{
   int temp;
   while(!pageList->isEmpty()){
      temp = pageList->popFront();
      if(pageCont->itemCount() < pageCont->getMax()){//fill first
         if(!pageCont->isEmpty() && pageCont->isHit(temp)){
            ++hit;
         }
         else{
            pageCont->pushBack(temp);
            ++pagefault;
         }
      }
      else{
         if(!pageCont->isHit(temp)){//find page fault and log it
            pageCont->pushBack(temp);
            pageCont->popFront();
            ++pagefault;
         }
         else{
            ++hit;
         }
      }
   };
}
void lru(pFrame* pageList, pFrame* pageCont){
   //last recently used. add to the counter in order of appearance
   //so that the oldest one is at the front
   //if it is a hit, remove from list and push to the back
   int temp, index; 
   while(!pageList->isEmpty()){
      temp = pageList->popFront();
      if(pageCont->itemCount() < pageCont->getMax()){
         if(!pageCont->isEmpty() && pageCont->isHit(temp)){
            //make sure to get hits to move to the back of the line
            index = pageCont->getIndex(temp);
            pageCont->removeAt(index);
            pageCont->pushBack(temp);
            ++hit;
         }
         else{
            pageCont->pushBack(temp);
            ++pagefault;
         }
      }
      else{
         if(!pageCont->isHit(temp)){
            pageCont->pushBack(temp);
            pageCont->popFront();
            ++pagefault;
         }
         else{
            index = pageCont->getIndex(temp);
            pageCont->removeAt(index);
            pageCont->pushBack(temp);
            ++hit;
         }
      }
   }   
}
void opt(pFrame* pageList, pFrame* pageCont){
   int temp, farIndex, frameIndex;
   //fill the frame
   while(!pageList->isEmpty()){
      temp = pageList->popFront();
      if(pageCont->itemCount() < pageCont->getMax()){
         if(!pageCont->isEmpty() && pageCont->isHit(temp)){
            ++hit;
         }
         else{
            pageCont->pushBack(temp);
            ++pagefault;
         }
      }
      else{//once filled look for the furthest index and replace
         if(!pageCont->isHit(temp)){
            //find furthest index
            farIndex = pageCont->furthestIndex(pageList);
            pageCont->removeAt(farIndex);
            pageCont->pushBack(temp);
            ++pagefault;
         }
         else{
            ++hit;
         }
      }
   }
}
void logger(string s)
{//write as CSV so the data can be easily imported to excel for the chart
    cout << s;
    ofstream fileOUT;
    fileOUT.open ("pagefault.csv",ios::app); // Append mode
    if (fileOUT.is_open()) {
        fileOUT << s << endl; // Writing data to file
    }
    fileOUT.close();
}