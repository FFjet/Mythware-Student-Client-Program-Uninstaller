
#include "stdafx.h"

int Kill(LPCSTR Name)
{
	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hProcess = 0;
	DWORD dwExitCode = 0;

	HANDLE hProessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProessSnap != INVALID_HANDLE_VALUE)
	{
		if (::Process32First(hProessSnap, &pe32))
		{
			do
			{
				if (strcmp(pe32.szExeFile, Name) == 0)
				{
					hProcess = ::OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_CREATE_THREAD, FALSE, pe32.th32ProcessID);
					CloseHandle(hProessSnap);
					break;
				}
			} while (::Process32Next(hProessSnap, &pe32));
		}
	}

	LPVOID Param = VirtualAllocEx(hProcess, NULL, sizeof(DWORD), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(hProcess, Param, (LPVOID)&dwExitCode, sizeof(DWORD), NULL);

	HANDLE hThread = CreateRemoteThread(hProcess,
		NULL,
		NULL,
		(LPTHREAD_START_ROUTINE)ExitProcess,
		Param,
		NULL,
		NULL);
	return 0;
}