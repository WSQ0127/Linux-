#include "graphics.h"
#include "bin/cyfgame.h"
#include <iostream>
#include <windows.h>
#include <random>
#include <fstream>
#include "bin/gameInit.h"

int lang;

int main() {
	hide_cmd();
	system("chcp 65001");
	creat_window(-4, -4, "MiniLinux : Prologue《微机：序章》", -1, -1);
	setbkcolor(WHITE);
	mkImg("./img/background.jpg", 0, 0, getwidth(), getheight());
	mkImg("./img/logo.png")
	lang = GetLanguage();
	getch();
	closegraph();
    return 0;
}  
