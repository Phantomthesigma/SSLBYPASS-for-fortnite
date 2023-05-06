#pragma once
#include <Windows.h>
#include <string>

using namespace std;

bool inject(HANDLE proc, string dllpath) {

	LPVOID space = VirtualAllocEx(proc, 0, dllpath.length() + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!space) return false;
	SIZE_T byteswritten;
	bool writemem = WriteProcessMemory(proc, space, dllpath.c_str(), dllpath.length() + 1, &byteswritten);
	if (!writemem) return false;
	CreateRemoteThread(proc, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"), space, 0, 0);
}
