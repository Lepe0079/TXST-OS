#ifndef PAGES_H
#define PAGES_H

#include<vector>
#include<deque>
#include<random>

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
        int itemCount()const;
        int popFront();
};

#endif