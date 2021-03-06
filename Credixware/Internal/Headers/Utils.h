// Created by Credix - Licence: https://creativecommons.org/licenses/by-nc-sa/4.0/ 
#ifndef UTILS_H
#define UTILS_H

#include "Common.h"
#include <iostream>
#include <map>

std::map<int, bool> bPreviousKey;

namespace Utils {
	template <class Fn>
	Fn* CaptureInterface(const char* szModule, const char* szInterface)
	{
		auto create_interface_fn = reinterpret_cast<Fn* (*)(const char *pName, int *pReturnCode)>(GetProcAddress(GetModuleHandleA(szModule), "CreateInterface"));
		Fn* result =  create_interface_fn(szInterface, nullptr);
		std::cout << szInterface << ": 0x" << std::hex << std::uppercase << (DWORD)result << "\n";
		return result;
	}

	template<typename Fn>
	Fn GetVFunc(const void *v, int i)
	{
		return (Fn) *(*(const void ***)v + i);
	}

	void CreateConsole(const char* consoleTitle) {
#ifdef DEBUG_DLL
		AllocConsole();
		SetConsoleTitle((LPCSTR)consoleTitle);
		// Requires _CRT_SECURE_NO_WARNINGS
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);
#endif
	}

	void CloseConsole() {
#ifdef DEBUG_DLL
		fclose(stdin);
		fclose(stdout);
		FreeConsole();
		SetConsoleCtrlHandler(NULL, true);
#endif
	}

	bool GetKey(int vKey) {
		bool bReturn = (bPreviousKey[vKey] && !GetAsyncKeyState(vKey));
		bPreviousKey[vKey] = GetAsyncKeyState(vKey);
		return bReturn;
	}

	bool GetKeyDown(int vKey) {
		bool bReturn = (!bPreviousKey[vKey] && GetAsyncKeyState(vKey));
		bPreviousKey[vKey] = GetAsyncKeyState(vKey);
		return bReturn;
	}
	
	bool Compare(const unsigned char* pData, const unsigned char* bMask, const char* szMask) {
		for (; *szMask; ++szMask, ++pData, ++bMask)
			if (*szMask == 'x' && *pData != *bMask)
				return false;

		return (*szMask) == 0;
	}

	uintptr_t FindPattern(uintptr_t dwAddress, uintptr_t dwLen, unsigned char* bMask, const char* szMask) {
		for (uintptr_t i = 0; i < dwLen; i++)
			if (Compare((unsigned char*)(dwAddress + i), bMask, szMask))
				return (uintptr_t)(dwAddress + i);

		return 0;
	}

}

#endif