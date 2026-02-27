#pragma warning (disable : 4996)
#include  <iostream>
#include "clsMainScreen.h"
#include "clsLoginScreen.h"

using namespace std;


int main()

{ 
   
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }

   

    return 0;
}