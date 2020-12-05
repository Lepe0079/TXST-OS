#include "pages.h"

pFrame::pFrame(){srand(seed);}

pFrame::pFrame(int maximum, int newSeed):max(maximum){
    seed = newSeed;
    srand(seed);
}
void pFrame::fillFrame(){
    //fill the frame while respecting the maximum number of entries
    for(int i = 0; i < max; ++i)
        frame.push_front((rand()%numRange+1));
}

void pFrame::displayFrame(){//displays the frames
    std::string s = "|";
    for(int i = 0; i < frame.size(); ++i){
        s+= std::to_string(frame[i]) + "|";
    }
    std::cout << s << std::endl;
}
bool pFrame::isEmpty()const{return frame.empty();}

int pFrame::itemCount()const{return frame.size();}

int pFrame::getMax()const{return max;}

int pFrame::getIndex(int search)const{
    for(int i = 0; i < frame.size(); ++i){
        if(frame[i] == search)
            return i;
    }
    return -1;
}
//returns the index of the number at the back of the reference
int pFrame::furthestIndex(pFrame* ref)const{
    int back, curr, index; 
    for(int i = 0; i < max; ++i){
        if(!ref->isHit(frame[i]))
            return i;//short case
        else if(i == 0){//set the ref
            back = ref->getIndex(frame[i]);
            index = 0;
        }
        else{//check against the rest
            curr = ref->getIndex(frame[i]);
            if(back < curr){//update values
                back = curr;
                index = i;
            }
        }
    }
    return index;
}
bool pFrame::insertAt(int index, int value){//inserts into index
    frame.at(index) = value;
    return true;
}
int pFrame::removeAt(int index){//remove from specific index
    int temp;
    temp = frame.at(index);
    frame.erase(frame.begin()+index);
    return temp;
}
bool pFrame::pushBack(int value){//adds to the back of the list
    frame.push_back(value);
    return (frame.size() > max);
}
bool pFrame::isHit(int value)const{//is value found
    for(int i = 0; i < frame.size(); ++i)
    {
        if(frame[i] == value)
            return true;
    }
    return false;
}

int pFrame::popFront(){//takes the front number off the list
    int temp = frame.front();
    frame.pop_front();
    return temp;
}
