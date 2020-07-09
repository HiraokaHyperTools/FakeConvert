#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <string>
#include <vector>

int wmain(int argc, wchar_t **argv)
{
	if (argc <= 0) {
		return 1;
	}

	wchar_t exePath[MAX_PATH];
	{
		LPWSTR filePart = NULL;
		if (0 == SearchPathW(NULL, L"magick.exe", L".exe", MAX_PATH, exePath, &filePart)) {
			return 1;
		}
	}

	std::wstring exePathQuoted = std::wstring()
		.append(L"\"")
		.append(exePath)
		.append(L"\"")
		;

	std::vector<wchar_t *> newArgv;
	{
		int x = 0;
		for (int x = 0; x < argc; x++) {
			newArgv.push_back(argv[x]);
		}
		newArgv[0] = const_cast<wchar_t *>(exePathQuoted.c_str());
		newArgv.push_back(nullptr);
	}

	return _wspawnv(_P_WAIT, exePath, const_cast<wchar_t * const *>(&newArgv.at(0)));
}
