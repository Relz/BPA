// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "constant.h"
#include "GameView.h"

int main()
{
	try
	{
		CGameView gameView(SCREEN_SIZE);
		gameView.GameLoop();
	}
	catch (const std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}