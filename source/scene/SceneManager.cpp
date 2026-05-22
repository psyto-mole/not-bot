/* === シーン管理のソースファイル === */

#include "SceneManager.h"
#include "GameManager.h"
#include "Color.h"
#include "Font.h"
#include "Key.h"
#include "Mouse.h"
#include "Geometry.h"
#include "FakeScene.h"
#include "Title.h"
#include "SelectScene.h"
#include "BattleScene.h"
#include "Result.h"
#include "GameOver.h"
#include "Message.h"
#include "Sound.h"
#include "SaveLoad.h"
#include "Menu.h"


GameScene NowGameScene;		// 現在のシーン
GameScene NextGameScene;	// 次のシーン

int SceneChangeFrameCount;	// シーン切換後からのゲームの経過フレーム
int elapseFrameCounter;		// ゲームの経過フレーム


/* --- シーンの初期化関数 --- */
int Scene_Init(GameScene sceneName)
{
	SceneChangeFrameCount = 0;		// シーン切り換え後からの経過フレームをリセット
	elapseFrameCounter = 0;		// 経過フレームをリセット

	/* +++ 指定したシーンの初期化関数を呼び出す +++ */
	switch (sceneName)
	{
	case Game_Start:
		/* +++ ゲーム起動直後の場合 +++ */

		if (initialized)	// 初期化済みだったら
		{
			if (Fake_Init() == -1)	// 偽のタイトルシーンの初期化に失敗したら
			{
				return -1;	// シーンの初期化失敗(-1を返す)
			}

			NowGameScene = Fake_Scene;
			NextGameScene = Fake_Scene;
		}
		else
		{
			if (Title_Init() == -1)
			{
				return -1;
			}

			NowGameScene = Title_Scene;
			NextGameScene = Title_Scene;
		}

		break;
	case Fake_Scene:
		/* +++ 偽のタイトルシーンの場合 +++ */

		if (Fake_Init() == -1)	// 偽のタイトルシーンの初期化に失敗したら
		{
			return -1;	// シーンの初期化失敗(-1を返す)
		}

		break;
	case Title_Scene:
		/* +++ タイトルシーンの場合 +++ */

		if (Title_Init() == -1)	// タイトルシーンの初期化に失敗したら
		{
			return -1;	// シーンの初期化失敗(-1を返す)
		}

		break;
	case Select_Scene:
		/* +++ キャラセレクトシーンの場合 +++ */

		if (SelectScene_Init() == -1)	// キャラセレクトシーンの初期化に失敗したら
		{
			return -1;	// シーンの初期化失敗(-1を返す)
		}

		break;
	case Battle_Scene:
		/* +++ バトルシーンの場合 +++ */

		// バトルシーンの初期化に失敗したら
		if (BattleScene_Init() == -1)
		{
			return -1;	// シーンの初期化失敗(-1を返す)
		}

		break;
	case Result_Scene:
		/* +++ リザルトシーンの場合 +++ */

		if (Result_Init() == -1)	// リザルトシーンの初期化に失敗したら
		{
			return -1;	// シーンの初期化失敗(-1を返す)
		}
		break;
	case GameOver_Scene:
		/* +++ ゲームオーバーシーンの場合 +++ */

		if (GameOver_Init() == -1)	// ゲームオーバーシーンの初期化に失敗したら
		{
			return -1;	// シーンの初期化失敗(-1を返す)
		}
		break;
	default:
		break;
	}

	return 0;
}

/* --- シーンの処理を管理する関数 --- */
int Scene_Manage()
{
	if (Scene_Process() == -1)
	{
		return -1;
	}

	Scene_Draw();

	return 0;	// シーン処理の管理関数の終了(0を返す)
}

/* --- シーンの処理関数 --- */
int Scene_Process()
{
	SceneChangeFrameCount++;	// シーン切換後からの経過フレームを1増やす
	elapseFrameCounter++;		// 経過フレームを1増やす

	if (menuKind == MenuOFF)
	{
		if (NextGameScene != NowGameScene)	// 現在のシーンと次のシーンが異なる(シーンが切り換わる)
		{
			/* +++ 切り換わり先のシーンに応じて引数を変えてシーン初期化関数を実行 +++ */
			switch (NextGameScene)
			{
			case Fake_Scene:
				/* +++ タイトル画面の場合 +++ */

				if (Scene_Init(Fake_Scene) == -1)	// FakeSceneの初期化に失敗した
				{
					return -1;	// シーンの処理の失敗(-1を返す)
				}
				break;
			case Title_Scene:
				/* +++ タイトル画面の場合 +++ */

				switch (NowGameScene)
				{
				case GameOver_Scene:

					if (GameOver_End() == -1)
					{
						return -1;
					}
					break;
				case Result_Scene:

					if (Result_End() == -1)
					{
						return -1;
					}
					break;
				default:
					break;
				}

				if (Scene_Init(Title_Scene) == -1)	// TitleSceneの初期化に失敗した
				{
					return -1;	// シーンの処理の失敗(-1を返す)
				}
				break;
			case Select_Scene:
				/* +++ キャラセレクト画面の場合 +++ */

				switch (NowGameScene)
				{
				case Fake_Scene:

					if (Fake_End() == -1)
					{
						return -1;
					}
					break;
				case Title_Scene:

					if (Title_End() == -1)
					{
						return -1;
					}
					break;
				default:
					break;
				}

				if (Scene_Init(Select_Scene) == -1)	// SelectSceneの初期化に失敗した
				{
					return -1;	// シーンの処理の失敗(-1を返す)
				}
				break;
			case Battle_Scene:
				/* +++ バトル画面の場合 +++ */

				if (SelectScene_End() == -1)
				{
					return -1;
				}

				if (Scene_Init(Battle_Scene) == -1)	// BattleSceneの初期化に失敗した
				{
					return -1;	// シーンの処理の失敗(-1を返す)
				}
				break;
			case Result_Scene:
				/* +++ リザルト画面の場合 +++ */

				if (BattleScene_End() == -1)
				{
					return -1;
				}

				if (Scene_Init(Result_Scene) == -1)	// ResultSceneの初期化に失敗した
				{
					return -1;	// シーンの処理の失敗(-1を返す)
				}
				break;
			case GameOver_Scene:
				/* +++ ゲームオーバー画面の場合 +++ */

				if (BattleScene_End() == -1)
				{
					return -1;
				}

				if (Scene_Init(GameOver_Scene) == -1)	// GameOverSceneの初期化に失敗した
				{
					return -1;	// シーンの処理の失敗(-1を返す)
				}
				break;
			default:
				break;
			}

			NowGameScene = NextGameScene;	// 切換先のシーンを現在のシーンに設定
		}
		else
		{
			/* +++ 現在のシーンに応じて引数を変えてシーンの処理関数を実行 +++ */
			switch (NowGameScene)
			{
			case Fake_Scene:
				/* +++ 偽のタイトル画面の場合 +++ */

				Fake_Manage();	// 偽のタイトルシーンの処理関数を実行
				break;
			case Title_Scene:
				/* +++ タイトル画面の場合 +++ */

				Title_Manage();	// タイトルシーンの処理関数を実行
				break;
			case Select_Scene:
				/* +++ キャラセレクト画面の場合 +++ */

				SelectScene_Manage();	// キャラセレクトシーンの処理関数を実行
				break;
			case Battle_Scene:
				/* +++ バトル画面の場合 +++ */

				BattleScene_Manage();	// バトルシーンの処理関数を実行
				break;
			case Result_Scene:
				/* +++ リザルト画面の場合 +++ */

				Result_Manage();	// リザルトシーンの処理関数を実行
				break;
			case GameOver_Scene:
				/* +++ ゲームオーバー画面の場合 +++ */

				GameOver_Manage();	// ゲームオーバーシーンの処理関数を実行
				break;
			default:
				break;
			}
		}
	}


	if (Menu_Process() == -1)
	{
		return -1;
	}

	if(GameDebug)
	{
		if (Key_Check_Press(KEY_INPUT_B) && Key_Check_Press(KEY_INPUT_A)
			&& Key_Check_Press(KEY_INPUT_C) && Key_Check_Press(KEY_INPUT_K))
		{
			return -1;
		}
	}

	return 0;
}

/* --- シーンの描画関数 --- */
void Scene_Draw()
{
	Menu_Draw();

	if (GameDebug)
	{
		if (alreadySaved)
		{
			DrawFormatStringToHandleAlign(GameWindowWidth - 1, 45, FAlign_Right, Color_LightGreen, MSMincho_30_1, "Already Saved: %s" ,FlagStatusTrue);
		}
		else
		{
			DrawFormatStringToHandleAlign(GameWindowWidth - 1, 45, FAlign_Right, Color_LightGreen, MSMincho_30_1, "Already Saved: %s", FlagStatusFalse);
		}

		DrawFormatStringToHandleAlign(GameWindowWidth - 1, 75, FAlign_Right, Color_Green, MSMincho_20_1, "Round_Robin[%d]: %d", 1, round_robin[0]);
		DrawFormatStringToHandleAlign(GameWindowWidth - 1, 95, FAlign_Right, Color_Green, MSMincho_20_1, "Round_Robin[%d]: %d", 2, round_robin[1]);
		DrawFormatStringToHandleAlign(GameWindowWidth - 1, 115, FAlign_Right, Color_Green, MSMincho_20_1, "Round_Robin[%d]: %d", 3, round_robin[2]);
		DrawFormatStringToHandleAlign(GameWindowWidth - 1, 135, FAlign_Right, Color_Green, MSMincho_20_1, "Round_Robin[%d]: %d", 4, round_robin[3]);
		DrawFormatStringToHandleAlign(GameWindowWidth - 1, 155, FAlign_Right, Color_Green, MSMincho_20_1, "Round_Robin[%d]: %d", 5, round_robin[4]);
		DrawFormatStringToHandleAlign(GameWindowWidth - 1, 175, FAlign_Right, Color_Green, MSMincho_20_1, "Round_Robin[%d]: %d", 6, round_robin[5]);
		DrawFormatStringToHandleAlign(GameWindowWidth - 1, 195, FAlign_Right, Color_Green, MSMincho_20_1, "Round_Robin[%d]: %d", 7, round_robin[6]);
		DrawFormatStringToHandleAlign(GameWindowWidth - 1, 215, FAlign_Right, Color_Green, MSMincho_20_1, "Round_Robin[%d]: %d", 8, round_robin[7]);
		DrawFormatStringToHandleAlign(GameWindowWidth - 1, 235, FAlign_Right, Color_Green, MSMincho_20_1, "Round_Robin[%d]: %d", 9, round_robin[8]);

		if (initialized)
		{
			DrawFormatStringToHandleAlign(GameWindowWidth - 1, 260, FAlign_Right, Color_LightGreen, MSMincho_30_1, "Initialized: %s", FlagStatusTrue);
		}
		else
		{
			DrawFormatStringToHandleAlign(GameWindowWidth - 1, 260, FAlign_Right, Color_LightGreen, MSMincho_30_1, "Initialized: %s", FlagStatusFalse);
		}
	}

	if (RuledLine)
	{
		Draw_RuledLine();
	}

	return;
}