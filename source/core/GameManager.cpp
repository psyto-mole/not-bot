/* === ゲーム処理のソースファイル === */

#include "GameManager.h"
#include "Color.h"


/* --- 画面に罫線を引く関数 --- */
void Draw_RuledLine()
{
	DrawLine(GameWindowWidth / 2, 0, GameWindowWidth / 2, GameWindowHeight, Color_Red);
	DrawLine(0, GameWindowHeight / 2, GameWindowWidth, GameWindowHeight / 2, Color_LightBlue);

	DrawLine(GameWindowWidth / 2 - 100, 0, GameWindowWidth / 2 - 100, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 - 200, 0, GameWindowWidth / 2 - 200, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 - 300, 0, GameWindowWidth / 2 - 300, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 - 400, 0, GameWindowWidth / 2 - 400, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 - 500, 0, GameWindowWidth / 2 - 500, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 - 600, 0, GameWindowWidth / 2 - 600, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 - 700, 0, GameWindowWidth / 2 - 700, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 - 800, 0, GameWindowWidth / 2 - 800, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 - 900, 0, GameWindowWidth / 2 - 900, GameWindowHeight, Color_LightGreen);

	DrawLine(GameWindowWidth / 2 - 50, 0, GameWindowWidth / 2 - 50, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 - 150, 0, GameWindowWidth / 2 - 150, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 - 250, 0, GameWindowWidth / 2 - 250, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 - 350, 0, GameWindowWidth / 2 - 350, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 - 450, 0, GameWindowWidth / 2 - 450, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 - 550, 0, GameWindowWidth / 2 - 550, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 - 650, 0, GameWindowWidth / 2 - 650, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 - 750, 0, GameWindowWidth / 2 - 750, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 - 850, 0, GameWindowWidth / 2 - 850, GameWindowHeight, Color_DarkGreen);


	DrawLine(GameWindowWidth / 2 + 100, 0, GameWindowWidth / 2 + 100, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 + 200, 0, GameWindowWidth / 2 + 200, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 + 300, 0, GameWindowWidth / 2 + 300, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 + 400, 0, GameWindowWidth / 2 + 400, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 + 500, 0, GameWindowWidth / 2 + 500, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 + 600, 0, GameWindowWidth / 2 + 600, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 + 700, 0, GameWindowWidth / 2 + 700, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 + 800, 0, GameWindowWidth / 2 + 800, GameWindowHeight, Color_LightGreen);
	DrawLine(GameWindowWidth / 2 + 900, 0, GameWindowWidth / 2 + 900, GameWindowHeight, Color_LightGreen);

	DrawLine(GameWindowWidth / 2 + 50, 0, GameWindowWidth / 2 + 50, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 + 150, 0, GameWindowWidth / 2 + 150, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 + 250, 0, GameWindowWidth / 2 + 250, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 + 350, 0, GameWindowWidth / 2 + 350, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 + 450, 0, GameWindowWidth / 2 + 450, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 + 550, 0, GameWindowWidth / 2 + 550, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 + 650, 0, GameWindowWidth / 2 + 650, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 + 750, 0, GameWindowWidth / 2 + 750, GameWindowHeight, Color_DarkGreen);
	DrawLine(GameWindowWidth / 2 + 850, 0, GameWindowWidth / 2 + 850, GameWindowHeight, Color_DarkGreen);


	DrawLine(0, GameWindowHeight / 2 - 100, GameWindowWidth, GameWindowHeight / 2 - 100, Color_LightGreen);
	DrawLine(0, GameWindowHeight / 2 - 200, GameWindowWidth, GameWindowHeight / 2 - 200, Color_LightGreen);
	DrawLine(0, GameWindowHeight / 2 - 300, GameWindowWidth, GameWindowHeight / 2 - 300, Color_LightGreen);
	DrawLine(0, GameWindowHeight / 2 - 400, GameWindowWidth, GameWindowHeight / 2 - 400, Color_LightGreen);
	DrawLine(0, GameWindowHeight / 2 - 500, GameWindowWidth, GameWindowHeight / 2 - 500, Color_LightGreen);

	DrawLine(0, GameWindowHeight / 2 - 50, GameWindowWidth, GameWindowHeight / 2 - 50, Color_DarkGreen);
	DrawLine(0, GameWindowHeight / 2 - 150, GameWindowWidth, GameWindowHeight / 2 - 150, Color_DarkGreen);
	DrawLine(0, GameWindowHeight / 2 - 250, GameWindowWidth, GameWindowHeight / 2 - 250, Color_DarkGreen);
	DrawLine(0, GameWindowHeight / 2 - 350, GameWindowWidth, GameWindowHeight / 2 - 350, Color_DarkGreen);
	DrawLine(0, GameWindowHeight / 2 - 450, GameWindowWidth, GameWindowHeight / 2 - 450, Color_DarkGreen);


	DrawLine(0, GameWindowHeight / 2 + 100, GameWindowWidth, GameWindowHeight / 2 + 100, Color_LightGreen);
	DrawLine(0, GameWindowHeight / 2 + 200, GameWindowWidth, GameWindowHeight / 2 + 200, Color_LightGreen);
	DrawLine(0, GameWindowHeight / 2 + 300, GameWindowWidth, GameWindowHeight / 2 + 300, Color_LightGreen);
	DrawLine(0, GameWindowHeight / 2 + 400, GameWindowWidth, GameWindowHeight / 2 + 400, Color_LightGreen);
	DrawLine(0, GameWindowHeight / 2 + 500, GameWindowWidth, GameWindowHeight / 2 + 500, Color_LightGreen);

	DrawLine(0, GameWindowHeight / 2 + 50, GameWindowWidth, GameWindowHeight / 2 + 50, Color_DarkGreen);
	DrawLine(0, GameWindowHeight / 2 + 150, GameWindowWidth, GameWindowHeight / 2 + 150, Color_DarkGreen);
	DrawLine(0, GameWindowHeight / 2 + 250, GameWindowWidth, GameWindowHeight / 2 + 250, Color_DarkGreen);
	DrawLine(0, GameWindowHeight / 2 + 350, GameWindowWidth, GameWindowHeight / 2 + 350, Color_DarkGreen);
	DrawLine(0, GameWindowHeight / 2 + 450, GameWindowWidth, GameWindowHeight / 2 + 450, Color_DarkGreen);

	return;
}