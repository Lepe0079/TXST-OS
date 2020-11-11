#include "pages.h"
#include <iostream>

using namespace std;

enum FrameAlgo{FIFO, LRU, OPT};
//metrics
int pagefault = 0;
//prototypes
void fifo(pFrame*, pFrame*);
void lru(pFrame*, pFrame*);
void opt(pFrame*, pFrame*);


int main(int argc, char* argv[])
{
   pFrame* pageList = new pFrame(30, 1);
   pFrame* pageCont = new pFrame(5, 1);
   pageList->fillFrame();


   fifo(pageList, pageCont);
   // switch(variable){
   //    case FIFO:
   //       fifo(pageList, pageCont);
   //       break;
   //    case LRU:
   //       lru(pageList, pageCont);
   //       break;
   //    case OPT:
   //       opt(pageList, pageCont);
   //       break;
   //    defaut:
   //       cout << "Please run the program with the correct parameters";
   //       break;
   // } 

   return 0;
}

//declarations
void fifo(pFrame* pageList, pFrame* pageCont)//FIFO ALGO
{
   int temp;
   //pageList->displayFrame();

   while(!pageList->isEmpty()){
      temp = pageList->popFront();
      if(pageCont->itemCount() < pageCont->getMax()){//fill first
         if(!pageCont->isEmpty() && pageCont->isHit(temp))
            cout << "HIT!" << endl;//make sure theres no hits on fill
         else{
            pageCont->pushBack(temp);
            ++pagefault;
         }
      }
      else{
         if(!pageCont->isHit(temp)){//find page fault and log it
            //pageCont->displayFrame();
            //cout << temp << " Fault Dropping Page: " << pageCont->popFront() << endl;
            pageCont->pushBack(temp);
            ++pagefault;
         }
         else
            cout << "HIT!" << endl;
      }
   };
   //pageCont->displayFrame();
   //cout << endl <<  pagefault << " Page Faults Found" << endl;
}

void lru(pFrame* pageList, pFrame* pageCont)
{

}

void opt(pFrame* pageList, pFrame* pageCont)
{

}