/* === リザルト処理のソースファイル === */

#include "GameManager.h"
#include "Color.h"
#include "Image.h"
#include "Font.h"
#include "Key.h"
#include "Mouse.h"
#include "Character.h"
#include "SceneManager.h"
#include "Geometry.h"
#include "Result.h"
#include "Message.h"
#include "Sound.h"
#include "SaveLoad.h"
#include "Rectparameter.h"


/* --- シーンの初期化関数 --- */
int Result_Init()
{
	Sound_Play(BGM_Result);

	return 0;	// リザルトシーンの初期化の終了(0を返す)
}

/* --- リザルトシーンの処理の管理関数 ---- */
void Result_Manage()
{
	Result_Process();	// リザルトシーンの処理
	Result_Draw();		// リザルトシーンの初期化

	return;
}

/* +++ リザルトシーンの処理関数 +++ */
void Result_Process()
{
	if (alreadyConfirmedSave != true)
	{
		if (CollisionRectToPoint(resultDialogYes, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Click);

			Data_Update(playerKindNumber, enemyKindNumber);

			alreadyConfirmedSave = true;
		}
		else if(CollisionRectToPoint(resultDialogNo, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Click);

			alreadyConfirmedSave = true;
		}
	}

	if (SceneChangeFrameCount >= GameFPS && Key_Check_Click(KEY_INPUT_RETURN))
	{
		if (initialized)
		{
			NextGameScene = Fake_Scene;
		}
		else
		{
			NextGameScene = Title_Scene;
		}
	}

	return;
}

/* +++ リザルトシーンの描画関数 +++ */
void Result_Draw()
{
	if (GameDebug)
	{
		if (errorCode != 0)
		{
			DrawFormatStringToHandleAlign(0, 0, FAlign_Left, Color_Red, MSMincho_30_1, "Error Code: %d", errorCode);
		}
	}
	
	/* +++ 勝敗結果 +++ */
	DrawFormatStringToHandleAlign(GameWindowWidth / 2, GameWindowHeight / 2 - 300, FAlign_AllCenter, Color_White, MSMincho_300_9, "%s", ResultWinMessage);

	DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 3, GameWindowHeight / 2 + 297, FAlign_AllCenter, Color_switching_Light, MSMincho_100_9, PressEnter);
	DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 3, GameWindowHeight / 2 + 303, FAlign_AllCenter, Color_switching_Light, MSMincho_100_9, PressEnter);
	DrawFormatStringToHandleAlign(GameWindowWidth / 2, GameWindowHeight / 2 + 300, FAlign_AllCenter, Color_Black, MSMincho_100_9, PressEnter);

	DrawExtendGraphConditional(GameWindowWidth / 2 - 700, GameWindowHeight / 2 - 200, GameWindowWidth / 2 - 299, GameWindowHeight / 2 + 201, playerKindNumber, ISPLAYER);
	DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 500, GameWindowHeight / 2 + 250, FAlign_AllCenter, Color_Green, MSMincho_50_1, "%s", NamePlayer);
	DrawExtendGraphConditional(GameWindowWidth / 2 + 700, GameWindowHeight / 2 - 200, GameWindowWidth / 2 + 301, GameWindowHeight / 2 + 201, enemyKindNumber, ISENEMY);
	DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 500, GameWindowHeight / 2 + 250, FAlign_AllCenter, Color_Purple, MSMincho_50_1, "%s", NameEnemy);


	/* +++ セーブダイアログの表示 +++ */
	if (SceneChangeFrameCount >= GameFPS && alreadyConfirmedSave != true)
	{
		DrawRect(resultDialogBackGround, Color_White, true, 1);
	
		DrawFormatStringToHandleAlign(GameWindowWidth / 2, GameWindowHeight / 2 - 50, FAlign_AllCenter, Color_Black, MSMincho_20_1, "%s", ResultDialogMessage);
	
	
		if (CollisionRectToPoint(resultDialogYes, nowMousePoint))
		{
			DrawRect(resultDialogYes, Color_Green, true, 1);
			DrawRect(resultDialogNo, Color_Violet, false, 1);
	
			DrawFormatStringToHandleAlign(ResultDialogYesCenterX, ResultDialogButtonCenterY, FAlign_AllCenter, Color_White, MSMincho_20_1, "%s", ResponseYes);
			DrawFormatStringToHandleAlign(ResultDialogNoCenterX, ResultDialogButtonCenterY, FAlign_AllCenter, Color_Black, MSMincho_20_1, "%s", ResponseNo);
		}
		else if (CollisionRectToPoint(resultDialogNo, nowMousePoint))
		{
			DrawRect(resultDialogYes, Color_Green, false, 1);
			DrawRect(resultDialogNo, Color_Violet, true, 1);
	
			DrawFormatStringToHandleAlign(ResultDialogYesCenterX, ResultDialogButtonCenterY, FAlign_AllCenter, Color_Black, MSMincho_20_1, "%s", ResponseYes);
			DrawFormatStringToHandleAlign(ResultDialogNoCenterX, ResultDialogButtonCenterY, FAlign_AllCenter, Color_White, MSMincho_20_1, "%s", ResponseNo);
		}
		else
		{
			DrawRect(resultDialogYes, Color_Green, false, 1);
			DrawRect(resultDialogNo, Color_Violet, false, 1);
	
			DrawFormatStringToHandleAlign(ResultDialogYesCenterX, ResultDialogButtonCenterY, FAlign_AllCenter, Color_Black, MSMincho_20_1, "%s", ResponseYes);
			DrawFormatStringToHandleAlign(ResultDialogNoCenterX, ResultDialogButtonCenterY, FAlign_AllCenter, Color_Black, MSMincho_20_1, "%s", ResponseNo);
		}
	}

	return;
}

/* --- リザルトシーンの終了関数 --- */
int Result_End()
{
	Sound_Stop(&BGM_Result);

	return 0;
}