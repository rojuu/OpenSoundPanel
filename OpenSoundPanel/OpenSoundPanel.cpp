#include <iostream>
#include <windows.h>
#include <algorithm>

int posX, posY;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	WCHAR class_name[1024];
	WCHAR title[1024];
	GetClassName(hwnd, class_name, sizeof(class_name));
	GetWindowText(hwnd, title, sizeof(title));

	std::wstring wtitle = title;

	std::transform(
		wtitle.begin(), wtitle.end(),
		wtitle.begin(),
		towlower);

	if (wtitle == L"sound")
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
	if (argc != 3)
	{
		printf("Usage %s [position_x] [position_y]", argv[0]);
		return EXIT_FAILURE;
	}

	posX = atoi(argv[1]);
	posY = atoi(argv[2]);

	std::cout << "Positions: " << posX << " " << posY << std::endl;

	system("control mmsys.cpl sounds");
	
	Sleep(1000);

	EnumWindows(EnumWindowsProc, NULL);
	
	return EXIT_SUCCESS;
}
