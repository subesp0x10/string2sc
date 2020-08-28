// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

int main()
{
    std::cout << "Hello World!\n";

    char str[4] = { 0 };

    *((DWORD*)str + 0x00) = 0x5979791a;
    *((DWORD*)str + 0x00) += 0x22c702d0;
    *((DWORD*)str + 0x00) += 0x7d41a4f9;
    *((DWORD*)str + 0x00) += 0xb75486cd;
    *((DWORD*)str + 0x00) += 0x0e91dc51;
    *((DWORD*)str + 0x00) += 0x8e02cf83;
    *((DWORD*)str + 0x00) += 0x9ea4bd5a;
    *((DWORD*)str + 0x00) += 0xa55d5fcc;
    *((DWORD*)str + 0x00) += 0x7e3898e8;
    *((DWORD*)str + 0x00) += 0xf0bd58cf;








    std::cout << "[" << strlen(str) << "]" << str << std::endl;
    //std::wcout << L"[" << wcslen(str) << L"]"<< str << std::endl;

    

    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
