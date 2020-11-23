#ifndef PAGES_H
#define PAGES_H

#include<vector>
#include<deque>
#include<random>
#include<iostream>

class pFrame
{
    private:
        std::deque<int> frame;
        int max = 1;
        int seed = 1;
        int numRange = 49;

    public:
        pFrame();
        pFrame(int, int);

        void fillFrame();
        void displayFrame();
        bool isEmpty()const;
        int itemCount()const;
        int getMax()const;
        int getIndex(int)const;

        bool insertAt(int, int);
        int removeAt(int);
        bool pushBack(int);
        bool isHit(int)const;
        int popFront();
};

#endif