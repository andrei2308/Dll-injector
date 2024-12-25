#include <Windows.h>


BOOL APIENTRY DLLmain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		MessageBoxA(NULL, "DLL atached and executed !!!", "Warning", MB_ICONEXCLAMATION);
		break;
	case DLL_PROCESS_DETACH:
		MessageBoxA(NULL, "DLL detached", "Warning", MB_ICONEXCLAMATION);
		break;
	case DLL_THREAD_ATTACH:
		MessageBoxA(NULL, "Thread created", "Warning", MB_ICONEXCLAMATION);
		break;
	case DLL_THREAD_DETACH:
		MessageBoxA(NULL, "Thread terminated", "Warning", MB_ICONEXCLAMATION);
		break;
	}
	return TRUE;
}
