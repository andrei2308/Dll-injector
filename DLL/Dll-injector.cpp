#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <string.h>
DWORD getPIDByName(const char* processName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		printf("Failed to take a process snapshot: %d\n", GetLastError());
		return 0;
	}
	PROCESSENTRY32W processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32W);

	if (Process32FirstW(hSnapshot, &processEntry))
	{
		do {
			WCHAR wideProcessName[MAX_PATH];
			MultiByteToWideChar(CP_ACP, 0, processName, -1, wideProcessName, MAX_PATH);

			if (wcscmp(wideProcessName, processEntry.szExeFile) == 0)
			{
				CloseHandle(hSnapshot);
				return processEntry.th32ProcessID;
			}
		} while (Process32NextW(hSnapshot, &processEntry));
	}
	CloseHandle(hSnapshot);
	printf("Process '%s' not found.\n", processName);
	return 0;
}
int main(int argc, char** argv)
{
	if (argc != 3) {
		printf("usage: dll-injector.exe <path-to-dll> <PID> \n");
		return 1;
	}
	PCSTR dll_path = argv[1];
	PCSTR process_name = argv[2];
	DWORD PID = getPIDByName(process_name);
	printf("PID returned from function: %d\n", PID);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if (hProcess == NULL) {
		printf("Failed to retrieve handle to remote process: %d\n",GetLastError());
		return 1;
	}
	LPVOID allocated_mem = VirtualAllocEx(hProcess, NULL, strlen(dll_path) + 1, (MEM_COMMIT | MEM_RESERVE), PAGE_READWRITE);
	if (allocated_mem == NULL) {
		printf("Failed to allocate memory in remote process: %d\n", GetLastError());
		return 1;
	}
	printf("memory allocated at: %p\n", allocated_mem);
	WriteProcessMemory(hProcess, allocated_mem, dll_path, strlen(dll_path) + 1, NULL);
	HMODULE kernel32Base = GetModuleHandleW(L"kernel32.dll");
	if (kernel32Base == NULL) {
		printf("Failed to retrieve handle to kernel32.dll: %d\n", GetLastError());
		return 1;
	}
	FARPROC load_library_address = GetProcAddress(kernel32Base, "LoadLibraryA");
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)load_library_address, allocated_mem, 0, NULL);
	if (hThread == NULL) {
		printf("Failed to create thread in remote process: %d\n", GetLastError());
		return 1;
	}
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hProcess);

	return 0;
}