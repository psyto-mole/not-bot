/* === システムメニューの処理を管理するソースファイル === */

#include "Menu.h"
#include "GameManager.h"
#include "Mouse.h"
#include "Color.h"
#include "Font.h"
#include "Sound.h"
#include "Geometry.h"
#include "SaveLoad.h"
#include "Message.h"
#include "RectParameter.h"


SystemMenu menuKind;	// メニューの種類

/* --- システムメニューの初期化関数 --- */
void Menu_Init()
{
	menuKind = MenuOFF;

	return;
}

/* --- システムメニューの処理の管理関数 --- */
void Menu_Manage()
{
	return;
}

/* --- システムメニューの処理関数 --- */
int Menu_Process()
{
	switch (menuKind)
	{
	case MenuOFF:
		/* +++ システムメニューがオフの場合 +++ */

		if (CollisionRectToPoint(menuBox, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Menu);
			menuKind = MenuTop;
		}
		break;
	case MenuTop:
		/* +++ メニュートップの場合 +++ */

		if (CollisionRectToPoint(menuButton1, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Enter);
			menuKind = Achievement;
		}
		else if (CollisionRectToPoint(menuButton2, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Enter);
			menuKind = DeleteData;
		}
		else if (CollisionRectToPoint(menuButton3, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Enter);
			menuKind = GameEnd;
		}
		else if (CollisionRectToPoint(menuButton4, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Enter);
			menuKind = Credit;
		}
		else if(CollisionRectToPoint(menuButton5, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Back);
			menuKind = MenuOFF;
		}
		break;
	case Achievement:
		/* +++ アチーブメントの場合 +++ */

		if (CollisionRectToPoint(achievementBackButton, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Back);
			menuKind = MenuTop;
		}
		break;
	case DeleteData:
		/* +++ データ消去の場合 +++ */

		if (CollisionRectToPoint(menuButton1, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Enter);
			menuKind = Achievement;
		}
		else if (CollisionRectToPoint(menuButton2, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Unavilable);
		}
		else if (CollisionRectToPoint(menuButton3, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Enter);
			menuKind = GameEnd;
		}
		else if (CollisionRectToPoint(menuButton4, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Enter);
			menuKind = Credit;
		}
		else if (CollisionRectToPoint(menuButton5, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Back);
			menuKind = MenuOFF;
		}


		if (CollisionRectToPoint(menuYesButton, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Enter);
			Data_Delete();
		}
		else if (CollisionRectToPoint(menuNoButton, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Back);
			menuKind = MenuTop;
		}

		break;
	case GameEnd:
		/* +++ ゲーム終了の場合 +++ */

		if (CollisionRectToPoint(menuButton1, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Enter);
			menuKind = Achievement;
		}
		else if (CollisionRectToPoint(menuButton2, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Enter);
			menuKind = DeleteData;
		}
		else if (CollisionRectToPoint(menuButton3, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Unavilable);
		}
		else if (CollisionRectToPoint(menuButton4, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Enter);
			menuKind = Credit;
		}
		else if (CollisionRectToPoint(menuButton5, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Back);
			menuKind = MenuOFF;
		}


		if (CollisionRectToPoint(menuYesButton, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Enter);
			return -1;
		}
		else if (CollisionRectToPoint(menuNoButton, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Back);
			menuKind = MenuTop;
		}

		break;
	case Credit:
		/* +++ クレジットの場合 +++ */

		if (CollisionRectToPoint(achievementBackButton, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Back);
			menuKind = MenuTop;
		}

		break;
	default:
		break;
	}


	return 0;
}

/* --- システムメニューの描画関数 --- */
void Menu_Draw()
{
	switch (menuKind)
	{
	case MenuOFF:
		/* +++ システムメニューがオフの場合 +++ */

		/* +++ マウスカーソルがメニューボックスに触れているかを確認 +++ */
		if (CollisionRectToPoint(menuBox, nowMousePoint))	// 触れている
		{
			DrawRect(menuBox, Color_White, true, 1);		// ボタンを白色で描画
			DrawLineWithStruct(menuLine1, Color_Black);		// メニューボタンのラインを黒で描画
			DrawLineWithStruct(menuLine2, Color_Black);		// メニューボタンのラインを黒で描画
			DrawLineWithStruct(menuLine3, Color_Black);		// メニューボタンのラインを黒で描画
		}
		else	// 触れていない
		{
			DrawRect(menuBox, Color_White, false, 1);		// ボタンを白枠で描画
			DrawLineWithStruct(menuLine1, Color_White);		// メニューボタンのラインを白で描画
			DrawLineWithStruct(menuLine2, Color_White);		// メニューボタンのラインを白で描画
			DrawLineWithStruct(menuLine3, Color_White);		// メニューボタンのラインを白で描画
		}
		break;
	case MenuTop:
		/* +++ メニュートップの場合 +++ */

		DrawRect(menuWindow1, Color_White, false, 3);
		DrawLineWithStruct(devideMenuWindow, Color_White);

		if (CollisionRectToPoint(menuButton1, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, true, 3);
			DrawRect(menuButton2, Color_White, false, 3);
			DrawRect(menuButton3, Color_White, false, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);

			DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 150,GameWindowHeight / 2 - 375, FAlign_Left, Color_White, MSMincho_30_1, "%s", DetailAchievement);
		}
		else if (CollisionRectToPoint(menuButton2, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_White, true, 3);
			DrawRect(menuButton3, Color_White, false, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);

			DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 150, GameWindowHeight / 2 - 375, FAlign_Left, Color_White, MSMincho_30_1, "%s", DetailDeleteData);
		}
		else if (CollisionRectToPoint(menuButton3, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_White, false, 3);
			DrawRect(menuButton3, Color_White, true, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);

			DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 150, GameWindowHeight / 2 - 375, FAlign_Left, Color_White, MSMincho_30_1, "%s", DetailGameEnd);
		}
		else if (CollisionRectToPoint(menuButton4, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_White, false, 3);
			DrawRect(menuButton3, Color_White, false, 3);
			DrawRect(menuButton4, Color_White, true, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);

			DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 150, GameWindowHeight / 2 - 375, FAlign_Left, Color_White, MSMincho_30_1, "%s", DetailCredit);
		}
		else if (CollisionRectToPoint(menuButton5, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_White, false, 3);
			DrawRect(menuButton3, Color_White, false, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, true, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuBack);

			DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 150, GameWindowHeight / 2 - 375, FAlign_Left, Color_White, MSMincho_30_1, "%s", DetailBackMenu);
		}
		else
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_White, false, 3);
			DrawRect(menuButton3, Color_White, false, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);
		}

		break;
	case Achievement:
		/* +++ アチーブメントの場合 +++ */

		DrawRect(menuWindow1, Color_White, false, 3);
		DrawLineWithStruct(achieveDiagonalLine, Color_White);

		DrawRect(achievementTable, Color_White, false, 3);
		DrawLineWithStruct(enemyLine, Color_White);
		DrawLineWithStruct(playerLine, Color_White);
		DrawLineWithStruct(enemyEdgeLine, Color_White);
		DrawLineWithStruct(playerEdgeLine, Color_White);
		DrawLineWithStruct(enemyRobotLine, Color_White);
		DrawLineWithStruct(playerRobotLine, Color_White);
		DrawLineWithStruct(enemyHumanLine, Color_White);
		DrawLineWithStruct(playerHumanLine, Color_White);
		DrawLineWithStruct(enemyDragonLine, Color_White);
		DrawLineWithStruct(playerDragonLine, Color_White);

		DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 50, GameWindowHeight / 2 - 250, FAlign_AllCenter, Color_White,  MSMincho_50_1, "%s", NameEnemy);
		DrawFormatVStringToHandleAlign(GameWindowWidth / 2 - 250, GameWindowHeight / 2 + 50, FAlign_AllCenter, Color_White, VMSMincho_50_1, "%s", NamePlayer);

		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 100, GameWindowHeight / 2 + 25, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", CharacterNameRobot);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 100, GameWindowHeight / 2 + 75, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", CharacterNameHuman);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 100, GameWindowHeight / 2 + 125, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", CharacterNameDragon);

		DrawFormatVStringToHandleAlign(GameWindowWidth / 2 + 25, GameWindowHeight / 2 - 100, FAlign_AllCenter, Color_White, VMSMincho_30_1, "%s", CharacterNameRobot);
		DrawFormatVStringToHandleAlign(GameWindowWidth / 2 + 75, GameWindowHeight / 2 - 100, FAlign_AllCenter, Color_White, VMSMincho_30_1, "%s", CharacterNameHuman);
		DrawFormatVStringToHandleAlign(GameWindowWidth / 2 + 125, GameWindowHeight / 2 - 100, FAlign_AllCenter, Color_White, VMSMincho_30_1, "%s", CharacterNameDragon);


		if (CollisionRectToPoint(achievementBackButton, nowMousePoint))
		{
			DrawRect(achievementBackButton, Color_White, true, 3);
			DrawFormatStringToHandleAlign(AchievementBackCenterX, AchievementBackCenterY, FAlign_AllCenter, Color_Black, MSMincho_30_1, "%s", BackButtonText);
		}
		else
		{
			DrawRect(achievementBackButton, Color_White, false, 3);
			DrawFormatStringToHandleAlign(AchievementBackCenterX, AchievementBackCenterY, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", BackButtonText);
		}

		Show_WinLoseCircle(1);
		Show_WinLoseCircle(2);
		Show_WinLoseCircle(3);
		Show_WinLoseCircle(4);
		Show_WinLoseCircle(5);
		Show_WinLoseCircle(6);
		Show_WinLoseCircle(7);
		Show_WinLoseCircle(8);
		Show_WinLoseCircle(9);

		/*if (round_robin[0] == 1)
		{
			DrawCircleWithStruct(winLoseCircle1, Color_White, true, 1);
		}
		
		if (round_robin[1] == 1)
		{
			DrawCircleWithStruct(winLoseCircle2, Color_White, true, 1);
		}
		
		if (round_robin[2] == 1)
		{
			DrawCircleWithStruct(winLoseCircle3, Color_White, true, 1);
		}
		
		if (round_robin[3] == 1)
		{
			DrawCircleWithStruct(winLoseCircle4, Color_White, true, 1);
		}
		
		if (round_robin[4] == 1)
		{
			DrawCircleWithStruct(winLoseCircle5, Color_White, true, 1);
		}
		
		if (round_robin[5] == 1)
		{
			DrawCircleWithStruct(winLoseCircle6, Color_White, true, 1);
		}
		
		if (round_robin[6] == 1)
		{
			DrawCircleWithStruct(winLoseCircle7, Color_White, true, 1);
		}
		
		if (round_robin[7] == 1)
		{
			DrawCircleWithStruct(winLoseCircle8, Color_White, true, 1);
		}
		
		if (round_robin[8] == 1)
		{
			DrawCircleWithStruct(winLoseCircle9, Color_White, true, 1);
		}*/

		break;
	case DeleteData:
		/* +++ データ消去の場合 +++ */

		DrawRect(menuWindow1, Color_White, false, 3);
		DrawLineWithStruct(devideMenuWindow, Color_White);

		DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 150, GameWindowHeight / 2 -250, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", QuestionDeleteData1);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 150, GameWindowHeight / 2 -200, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", QuestionDeleteData2);

		if (CollisionRectToPoint(menuButton1, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, true, 3);
			DrawRect(menuButton2, Color_Gray, false, 3);
			DrawRect(menuButton3, Color_White, false, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_Gray, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);
		}
		else if (CollisionRectToPoint(menuButton3, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_Gray, false, 3);
			DrawRect(menuButton3, Color_White, true, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_Gray, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);
		}
		else if (CollisionRectToPoint(menuButton4, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_Gray, false, 3);
			DrawRect(menuButton3, Color_White, false, 3);
			DrawRect(menuButton4, Color_White, true, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_Gray, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);
		}
		else if (CollisionRectToPoint(menuButton5, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_Gray, false, 3);
			DrawRect(menuButton3, Color_White, false, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, true, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_Gray, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuBack);
		}
		else
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_Gray, false, 3);
			DrawRect(menuButton3, Color_White, false, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_Gray, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);
		}


		if (CollisionRectToPoint(menuYesButton, nowMousePoint))
		{
			DrawRect(menuYesButton, Color_White, true, 3);	// メニューウィンドウの「はい」ボタンを白で描画
			DrawRect(menuNoButton, Color_White, false, 3);	// メニューウィンドウの「いいえ」ボタンを白枠で描画

			DrawFormatStringToHandleAlign(MenuYesButtonCenterX, MenuYesNoButtonCenterY, FAlign_AllCenter, Color_Black, MSMincho_30_1, "%s", ResponseYes);
			DrawFormatStringToHandleAlign(MenuNoButtonCenterX, MenuYesNoButtonCenterY, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", ResponseNo);
		}
		else if (CollisionRectToPoint(menuNoButton, nowMousePoint))
		{
			DrawRect(menuYesButton, Color_White, false, 3);		// メニューウィンドウの「はい」ボタンを白枠で描画
			DrawRect(menuNoButton, Color_White, true, 3);		// メニューウィンドウの「いいえ」ボタンを白で描画

			DrawFormatStringToHandleAlign(MenuYesButtonCenterX, MenuYesNoButtonCenterY, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", ResponseYes);
			DrawFormatStringToHandleAlign(MenuNoButtonCenterX, MenuYesNoButtonCenterY, FAlign_AllCenter, Color_Black, MSMincho_30_1, "%s", ResponseNo);
		}
		else
		{
			DrawRect(menuYesButton, Color_White, false, 3);		// メニューウィンドウの「はい」ボタンを白枠で描画
			DrawRect(menuNoButton, Color_White, false, 3);		// メニューウィンドウの「いいえ」ボタンを白枠で描画

			DrawFormatStringToHandleAlign(MenuYesButtonCenterX, MenuYesNoButtonCenterY, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", ResponseYes);
			DrawFormatStringToHandleAlign(MenuNoButtonCenterX, MenuYesNoButtonCenterY, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", ResponseNo);
		}

		break;
	case GameEnd:
		/* +++ ゲーム終了の場合 +++*/

		DrawRect(menuWindow1, Color_White, false, 3);
		DrawLineWithStruct(devideMenuWindow, Color_White);

		DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 150, GameWindowHeight / 2 - 250, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", QuestionGameEnd);

		if (CollisionRectToPoint(menuButton1, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, true, 3);
			DrawRect(menuButton2, Color_White, false, 3);
			DrawRect(menuButton3, Color_Gray, false, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_Gray, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);
		}
		else if (CollisionRectToPoint(menuButton2, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_White, true, 3);
			DrawRect(menuButton3, Color_Gray, false, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_Gray, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);
		}
		else if (CollisionRectToPoint(menuButton4, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_White, false, 3);
			DrawRect(menuButton3, Color_Gray, false, 3);
			DrawRect(menuButton4, Color_White, true, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_Gray, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);
		}
		else if (CollisionRectToPoint(menuButton5, nowMousePoint))
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_White, false, 3);
			DrawRect(menuButton3, Color_Gray, false, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, true, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_Gray, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_Black, MSMincho_40_1, "%s", OptionSystemMenuBack);
		}
		else
		{
			DrawRect(menuButton1, Color_White, false, 3);
			DrawRect(menuButton2, Color_White, false, 3);
			DrawRect(menuButton3, Color_Gray, false, 3);
			DrawRect(menuButton4, Color_White, false, 3);
			DrawRect(menuButton5, Color_White, false, 3);

			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton1LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuAchievement);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton2LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuDelete);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton3LineY, FAlign_AllCenter, Color_Gray, MSMincho_40_1, "%s", OptionSystemMenuEndGame);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton4LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuCredit);
			DrawFormatStringToHandleAlign(MenuButtonCenterX, MenuButton5LineY, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", OptionSystemMenuBack);
		}

		if (CollisionRectToPoint(menuYesButton, nowMousePoint))
		{
			DrawRect(menuYesButton, Color_White, true, 3);	// メニューウィンドウの「はい」ボタンを白で描画
			DrawRect(menuNoButton, Color_White, false, 3);	// メニューウィンドウの「いいえ」ボタンを白枠で描画

			DrawFormatStringToHandleAlign(MenuYesButtonCenterX, MenuYesNoButtonCenterY, FAlign_AllCenter, Color_Black, MSMincho_30_1, "%s", ResponseYes);
			DrawFormatStringToHandleAlign(MenuNoButtonCenterX, MenuYesNoButtonCenterY, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", ResponseNo);
		}
		else if (CollisionRectToPoint(menuNoButton, nowMousePoint))
		{
			DrawRect(menuYesButton, Color_White, false, 3);		// メニューウィンドウの「はい」ボタンを白枠で描画
			DrawRect(menuNoButton, Color_White, true, 3);		// メニューウィンドウの「いいえ」ボタンを白で描画

			DrawFormatStringToHandleAlign(MenuYesButtonCenterX, MenuYesNoButtonCenterY, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", ResponseYes);
			DrawFormatStringToHandleAlign(MenuNoButtonCenterX, MenuYesNoButtonCenterY, FAlign_AllCenter, Color_Black, MSMincho_30_1, "%s", ResponseNo);
		}
		else
		{
			DrawRect(menuYesButton, Color_White, false, 3);		// メニューウィンドウの「はい」ボタンを白枠で描画
			DrawRect(menuNoButton, Color_White, false, 3);		// メニューウィンドウの「いいえ」ボタンを白枠で描画

			DrawFormatStringToHandleAlign(MenuYesButtonCenterX, MenuYesNoButtonCenterY, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", ResponseYes);
			DrawFormatStringToHandleAlign(MenuNoButtonCenterX, MenuYesNoButtonCenterY, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", ResponseNo);
		}

		break;
	case Credit: 
		/* +++ クレジットの場合 +++ */

		DrawRect(menuWindow1, Color_White, false, 3);

		if (CollisionRectToPoint(achievementBackButton, nowMousePoint))
		{
			DrawRect(achievementBackButton, Color_White, true, 3);
			DrawFormatStringToHandleAlign(AchievementBackCenterX, AchievementBackCenterY, FAlign_AllCenter, Color_Black, MSMincho_30_1, "%s", BackButtonText);
		}
		else
		{
			DrawRect(achievementBackButton, Color_White, false, 3);
			DrawFormatStringToHandleAlign(AchievementBackCenterX, AchievementBackCenterY, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", BackButtonText);
		}

		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 300, GameWindowHeight / 2 - 300, FAlign_AllCenter, Color_SkyBlue, MSMincho_30_1, "%s", MusicUsed);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 300, GameWindowHeight / 2 - 260, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", MaohDamashi);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 300, GameWindowHeight / 2 - 220, FAlign_AllCenter, Color_White, MSMincho_40_1, "%s", SoundEffectLab);

		break;
	default:
		break;
	}

	return;
}

/* --- 勝敗結果の円を描画する関数 --- */
void Show_WinLoseCircle(int circleNumber)
{
	int element;

	if (circleNumber <= 0 || circleNumber > CharacterNumber * CharacterNumber)
	{
		return;
	}
	else
	{
		element = circleNumber - 1;
	}

	if (round_robin[element] == 1)
	{
		DrawCircleWithStruct(winLoseCircle[element], Color_White, true, 1);
	}

	return;
}