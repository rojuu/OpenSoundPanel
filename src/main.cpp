#include <iostream>
#include <windows.h>
#include <algorithm>

int posX, posY;

WCHAR SEARCH_TITLE[1024];

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	WCHAR class_name[1024];
	WCHAR title[1024];
	GetClassNameW(hwnd, class_name, sizeof(class_name));
	GetWindowTextW(hwnd, title, sizeof(title));

	std::wstring wtitle = title;

	std::transform(
		wtitle.begin(), wtitle.end(),
		wtitle.begin(),
		towlower);

	if (wtitle == SEARCH_TITLE)
	{
		SetWindowPos(
			hwnd,
			HWND_BOTTOM,
			posX, posY,
			0, 0,
			SWP_NOSIZE
		);
	}

	return TRUE;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		printf("Usage %s [title to search] [position_x] [position_y]", argv[0]);
		return EXIT_FAILURE;
	}

	swprintf(SEARCH_TITLE, 100, L"%hs", argv[1]);
	posX = atoi(argv[2]);
	posY = atoi(argv[3]);

	std::cout << "Positions: " << posX << " " << posY << std::endl;

	system("control mmsys.cpl sounds");
	
	Sleep(1000);

	EnumWindows(EnumWindowsProc, NULL);
	
	return EXIT_SUCCESS;
}
