#include "Timer.hpp"
#include <iostream>

using namespace std;


inline void pause() {
    cout << "Press ENTER to continue...";
    cin.get();
}


//**************************************************************************************************
int main() {
    Timer tmr;

    pause();
    tmr.start();

    pause();
    tmr.stop();

    cout << "Elapsed time: " << ( tmr.getTime() / 1000.0 ) << " s\n";

    return 0;
}
//**************************************************************************************************
