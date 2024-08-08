#include "graphics.h"
#include <fstream>
#include <windows.h>

int GetLanguage() {
	std::ifstream input("./_data/language.in");
	std::ofstream output("./_data/language.in");
	if(input.is_open()) {
		int x;
		input >> x;
		return x;
	}
	char str[100];
	inputbox_getline(
		(LPCTSTR)L"Set Language（设置语言）", 
		(LPCTSTR)L"检测到你未设置语言, 是否以中文继续？\nWe found that you have not set the language, do you want to continue in Chinese?\n请输入 Yes 或者 No\nPlease Press Yes or No",
		str, sizeof(str)/sizeof(*str));
	if(str[0] == 'Y' || str[0] == 'y') {
		output << 0;
		return 0;
	}
	else {
		output << 1;
		return 1;
	}
}
