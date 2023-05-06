#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <process.h>

#include "inject.h"

using namespace std;

#pragma warning (disable : 4996)


int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    char tcd[260];
    GetCurrentDirectoryA(260, tcd);

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);

    if (!CreateProcessA("FortniteClient-Win64-Shipping.exe", cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
        return 0;

    char filename[] = "PhantomFN.dll";
    char fullFilename[MAX_PATH];
    GetFullPathNameA(filename, MAX_PATH, fullFilename, nullptr);
    inject(OpenProcess(PROCESS_ALL_ACCESS, false, pi.dwProcessId), string(fullFilename));
    WaitForSingleObject(pi.hProcess, INFINITE);

    return 1;
}
