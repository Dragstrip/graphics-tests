
#include <iostream>
#include <windows.h>

int main()
{
    HANDLE hstdin;
    DWORD  mode;

    hstdin = GetStdHandle( STD_INPUT_HANDLE );
    GetConsoleMode( hstdin, &mode );//gets current mode
    SetConsoleMode( hstdin, 0/*ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT*/ );  // see note below

    std::cout << "Press any key..." << std::flush;
    int ch = std::cin.get();

    if (ch == 13) std::cout << "\nYou pressed ENTER\n";
    else          std::cout << "\n\nYou did not press ENTER\n";

    SetConsoleMode( hstdin, mode );//sets to previous mode
    return 0;
}
/*
BOOL WINAPI SetConsoleMode(
  _In_ HANDLE hConsoleHandle,
  _In_ DWORD  dwMode
);
*/
