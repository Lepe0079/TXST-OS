#include "pages.h"

#include <iostream>

using namespace std;

int main()
{
   pFrame pageList(20, 1);
   pageList.fillFrame();

   for(int i = 0; i < 10; ++i)
      cout << pageList.itemCount() << " \n" << pageList.popFront();
   
   return 0;
}