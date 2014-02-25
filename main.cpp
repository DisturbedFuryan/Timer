#include "Timer.hpp"
#include <iostream>

using namespace std;


inline void Pause() {
    cout << "Press ENTER to continue...";
    cin.get();
}


//**************************************************************************************************
int main() {
    Timer tmr;

    Pause();
    tmr.Start();

    Pause();
    tmr.Stop();

    cout << "Elapsed time: " << ( tmr.GetTime() / 1000.0 ) << " s\n";

    return 0;
}
//**************************************************************************************************
