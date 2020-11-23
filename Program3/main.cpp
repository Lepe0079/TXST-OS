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
   pFrame* pageList = new pFrame(40, 5);
   pFrame* pageCont = new pFrame(3, 1);
   pageList->fillFrame();
   //7 0 1 2 0 3 0 4 2 3 0 3 2
   // int arr[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
   // for(int i =0; i<20; ++i)
   //    pageList->pushBack(arr[i]);
   //pageList->displayFrame();

   //fifo(pageList, pageCont);
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
   
   lru(pageList, pageCont);
   cout << "There are " << pagefault << " pagefaults";
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
            pageCont->popFront();
            ++pagefault;
         }
         else
            cout << "HIT!" << endl;
      }
      pageCont->displayFrame();
      pageList->displayFrame();
   };
   //cout << endl <<  pagefault << " Page Faults Found" << endl;
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
            //cout << "HIT!" << endl;
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
            //cout << "HIT!" << endl;
         }
      }
   // pageCont->displayFrame();
   // pageList->displayFrame();
   }

   
}

void opt(pFrame* pageList, pFrame* pageCont){

}