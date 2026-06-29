/* === バトル処理のソースファイル === */

#include <string.h>
#include <time.h>
#include "GameManager.h"
#include "Color.h"
#include "Font.h"
#include "Key.h"
#include "Mouse.h"
#include "Geometry.h"
#include "Image.h"
#include "BattleScene.h"
#include "Character.h"
#include "Robbot.h"
#include "Human.h"
#include "Dragon.h"
#include "Dightmare.h"
#include "Noname.h"
#include "Shepp.h"
#include "RectParameter.h"
#include "Message.h"
#include "Sound.h"

int playerSpeed, enemySpeed;	// プレイヤーと敵キャラの速さを格納する変数
int probability;				// 乱数を格納する変数
int gameEndMode;				// ゲーム終了のモードを管理する変数(0:ゲームオーバー　1:ゲームを継続　2:ゲームクリア)

char battleMessage1[128];	// 1行目のメッセージを格納するクラス
char battleMessage2[128];	// 2行目のメッセージを格納するクラス
char battleMessage3[128];	// 3行目のメッセージを格納するクラス
char battleMessage4[128];	// 4行目のメッセージを格納するクラス

Fase NowFase, NextFase;		// フェイズを管理する列挙型の変数

/* --- シーンの初期化関数 --- */
int BattleScene_Init()
{
	Sound_Play(BGM_Battle);

	gameEndMode = 1;	// ゲーム終了のモードを1(ゲームを継続)に設定

	NowFase = MainFase;	// 現在のフェイズにメインフェイズを設定

	settingMessagePattern = Message1Line;
	displayMessagePattern = Message1Line;


	/* +++ 変数に格納された種類に応じて敵キャラを決定 +++ */
	switch (enemyKindNumber)
	{
	case 1:
		/* +++ ロボットの場合 +++ */

		Enemy = &EnRobot;	// 敵キャラをロボットに設定
		break;
	case 2:
		/* +++ 人間の場合 +++*/

		Enemy = &EnHuman;	// 敵キャラを人間に設定
		break;
	case 3:
		/* +++ ドラゴンの場合 +++ */

		Enemy = &EnDragon;	// 敵キャラをドラゴンに設定
		break;
	case 4:
		/* +++ ダイトメアの場合 +++ */

		Enemy = &EnDightmare;	// 敵キャラをダイトメアに設定
		break;
	case 5:
		/* +++ キューの場合 +++ */

		Enemy = &EnNoname;	// 敵キャラをキューに設定
		break;
	case 99:
		/* +++ Shrppの場合 +++ */

		Enemy = &EnShepp;	// 敵キャラをSheppに設定
		break;
	default:
		break;
	}

	/* +++ 変数に格納された種類に応じて自キャラを決定 +++ */
	switch (playerKindNumber)
	{
	case 1:
		/* +++ ロボットの場合 +++ */

		Player = &PlRobot;		// 自キャラをロボットに設定
		break;
	case 2:
		/* +++ 人間の場合 +++*/

		Player = &PlHuman;		// 自キャラを人間に設定
		break;
	case 3:
		/* +++ ドラゴンの場合 +++ */

		Player = &PlDragon;		// 自キャラをドラゴンに設定
		break;
	case 4:
		/* +++ ダイトメアの場合 +++ */

		Player = &PlDightmare;		// 自キャラをダイトメアに設定
		break;
	case 5:
		/* +++ キューの場合 +++ */

		Player = &PlNoname;		// 自キャラをキューに設定
		break;
	case 99:
		/* +++ Shrppの場合 +++ */

		Player = &PlShepp;		// 自キャラをSheppに設定
		break;
	default:
		break;
	}

	SRand(time(NULL));	// 現在の時刻を用いて乱数のシード値を設定

	Enemy->Character_Init(ISENEMY);		// 敵キャラの初期化関数を実行
	Player->Character_Init(ISPLAYER);	// プレイヤーキャラの初期化関数を実行

	return 0;	// バトルシーンの初期化の終了(0を返す)
}

/* --- バトルシーンの処理の管理関数 ---- */
void BattleScene_Manage()
{
	BattleScene_Process();	// バトルシーンの処理
	BattleScene_Draw();		// バトルシーンの初期化

	return;
}

/* +++ バトルシーンの処理関数 +++ */
void BattleScene_Process()
{
	if (Player->GetMyHP() == 0)		// プレイヤーのHPが0なら
	{
		if (elapseFrameCounter >= BattleSceneFPS)	// バトルシーンのフレーム数を経過しているなら
		{
			elapseFrameCounter = 0;		// 経過フレームをリセット

			if (gameEndMode == 0)	// ゲームモードが0(ゲームオーバー)になっている
			{
				NextGameScene = GameOver_Scene;		// ゲームオーバーでバトルシーンを終える
			}
			else	// ゲームモードが0ではない
			{
				gameEndMode = 0;	// ゲームモードを0(ゲームオーバーにする)

				settingMessagePattern = Message1Line;	// メッセージを書き込む行数を指定
				displayMessagePattern = Message1Line;	// メッセージを表示する行数を設定

				// 自キャラの種類に応じてメッセージの1行目に「プレイヤーの"キャラクター名"は倒れた」を設定
				switch (playerKindNumber)
				{
				case 1:
					/* +++ ロボットの場合 +++ */

					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, CharacterNameRobot, BattleEndMessage);
					break;
				case 2:
					/* +++ 勇者の場合 +++ */

					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, CharacterNameHuman, BattleEndMessage);
					break;
				case 3:
					/* +++ ドラゴンの場合 +++ */

					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, CharacterNameDragon, BattleEndMessage);
					break;
				case 4:
					/* +++ ダイトメアの場合 +++ */

					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, CharacterNameDightmare, BattleEndMessage);
					break;
				case 5:
					/* +++ キュー(仮)の場合 +++ */

					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, CharacterNameNoname, BattleEndMessage);
					break;
				case 99:
					/* +++ sheppの場合 +++ */

					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, CharacterNameShepp, BattleEndMessage);
					break;
				default:
					break;
				}
			}
		}
	}
	else if (Enemy->GetMyHP() == 0)		// 敵キャラのHPが0
	{
		if (elapseFrameCounter >= BattleSceneFPS)	// バトルシーンのフレーム数が経過している
		{
			elapseFrameCounter = 0;		// 経過フレームをリセット

			if (gameEndMode == 2)	// ゲームモードが2(ゲームクリア)なら
			{
				NextGameScene = Result_Scene;	// バトルシーンをゲームクリア(リザルトへ移行)で終わる
			}
			else	// ゲームモードが2以外
			{
				gameEndMode = 2;	// ゲームモードを2(ゲームクリア)に設定する

				settingMessagePattern = Message1Line;	// メッセージを書き込む行数を指定
				displayMessagePattern = Message1Line;	// メッセージを表示する行数を設定

				// メッセージの1行目に「敵の"キャラクター名"は倒れた」を設定
				switch (enemyKindNumber)
				{
				case 1:
					/* +++ ロボットの場合 +++ */

					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, CharacterNameRobot, BattleEndMessage);
					break;
				case 2:
					/* +++ 勇者の場合 +++ */

					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, CharacterNameHuman, BattleEndMessage);
					break;
				case 3:
					/* +++ ドラゴンの場合 +++ */

					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, CharacterNameDragon, BattleEndMessage);
					break;
				case 4:
					/* +++ ダイトメアの場合 +++ */

					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, CharacterNameDightmare, BattleEndMessage);
					break;
				case 5:
					/* +++ キュー(仮)の場合 +++ */

					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, CharacterNameNoname, BattleEndMessage);
					break;
				case 99:
					/* +++ sheppの場合 +++ */

					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, CharacterNameShepp, BattleEndMessage);
					break;
				default:
					break;
				}
			}
		}
	}
	else
	{
		/* +++ 現在のフェイズによって処理を変える +++ */
		switch (NowFase)
		{
		case MainFase:
			/* +++ メインフェイズの場合 +++ */

			if (settingMessagePattern != Message1Line)	// メッセージの書き込み先が1行目になっていない
			{
				settingMessagePattern = Message1Line;	// メッセージの書き込み先を1行目にする
			}

			if (displayMessagePattern != Message1Line)	// 表示するメッセージの行数が1行になっていない
			{
				displayMessagePattern = Message1Line;	// 表示するメッセージの行数を1行にする
			}

			// メッセージの1行目に「Main Fase」を設定
			sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", BattleSceneMain);

			Player->MainFase_Process();		// プレイヤーキャラのメインフェイズの処理を実行 
			Enemy->MainFase_Process();		// 敵キャラのメインフェイズの処理を実行 

			if (Player->GetMyActionFlag() && Enemy->GetMyActionFlag())	// プレイヤーと敵キャラのアクションフラグがtrueなら
			{
				NowFase = BattleFase;	// 現在のフェイズをバトルフェイズにする

				ActionFlagFalse();	// アクションフラグをfalseにする

				elapseFrameCounter = BattleSceneFPS - 1;	// バトルフェイズですぐ処理が始まるように経過フレームを調整
			}
			break;
		case BattleFase:
			/* +++ バトルフェイズの場合 +++ */

			if (elapseFrameCounter >= BattleSceneFPS)	// バトルシーンのフレーム数が経過した
			{
				elapseFrameCounter = 0;		// 経過フレームをリセット

				playerSpeed = Player->GetMySpeed();		// プレイヤーの速さを取得
				enemySpeed = Enemy->GetMySpeed();		// 敵キャラの速さを取得

				probability = GetRand(2);	// 乱数を生成

				if (settingMessagePattern != Message1Line)	// メッセージの書き込み先が1行目になっていない
				{
					settingMessagePattern = Message1Line;	// メッセージの書き込み先を1行目にする
				}

				if (displayMessagePattern != Message1Line)	// 表示するメッセージの行数が1行ではない
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージの行数を1行にする
				}

				if (Player->GetMyActionFlag() != true)	// プレイヤーが未行動である(actionFlagがfalse)
				{
					if (Enemy->GetMyActionFlag())	// 敵キャラが行動済み(actionFlagがtrue)
					{
						Player->BattleFase_Process();	// プレイヤーキャラのバトルフェイズの処理を実行
					}
					else
					{
						/* +++ 先制行動フラグや速さによって処理を変える +++ */
						if (Player->GetMyDefencePreemptive())	// プレイヤーの先制防御フラグがtrueである
						{
							Player->BattleFase_Process();	// プレイヤーキャラのバトルフェイズの処理を実行
						}
						else if (Enemy->GetMyDefencePreemptive())	// 敵キャラの先制防御フラグがtrueなら
						{
							Enemy->BattleFase_Process();	// 敵キャラのバトルフェイズの処理を実行
						}
						else if (Player->GetMyAttackPreemptive())	// プレイヤーの先制攻撃フラグがtrueなら
						{
							if (Enemy->GetMyAttackPreemptive())		// 敵キャラの先制攻撃フラグがtrueなら(互いに先制攻撃フラグがtrue)
							{
								/* +++ 確率によって行動順を変える +++ */
								if (probability % 2 == 0)
								{
									Player->BattleFase_Process();	// プレイヤーキャラのバトルフェイズの処理を実行
								}
								else
								{
									Enemy->BattleFase_Process();	// 敵キャラのバトルフェイズの処理を実行
								}
							}
							else	// プレイヤーキャラの先制攻撃フラグだけがtrueなら
							{
								Player->BattleFase_Process();	// プレイヤーキャラのバトルフェイズの処理を実行
							}
						}
						else if (Enemy->GetMyAttackPreemptive())	// 敵キャラの先制攻撃フラグ(だけ)がtrue
						{
							Enemy->BattleFase_Process();	// 敵キャラのバトルフェイズの処理を実行
						}
						else if (playerSpeed > enemySpeed)	// (互いに先制行動フラグがfalse)プレイヤーキャラの方が速さが速いなら
						{
							Player->BattleFase_Process();	// プレイヤーキャラのバトルフェイズの処理を実行
						}
						else if (playerSpeed < enemySpeed)	// (互いに先制行動フラグがfalse)敵キャラの方が速さが速いなら
						{
							Enemy->BattleFase_Process();	// 敵キャラのバトルフェイズの処理を実行
						}
						else	// (互いに先制行動フラグがfalse)互いの速さが同じである
						{
							/* +++ 確率によって行動順を変える +++ */
							if (probability % 2 == 0)
							{
								Player->BattleFase_Process();	// プレイヤーキャラのバトルフェイズの処理を実行
							}
							else
							{
								Enemy->BattleFase_Process();	// 敵キャラのバトルフェイズの処理を実行
							}
						}
					}
				}
				else if (Enemy->GetMyActionFlag() != true)	// (プレイヤーが行動済みで)敵キャラが未行動
				{
					Enemy->BattleFase_Process();	// 敵キャラのバトルフェイズの処理を実行
				}
				else	// プレイヤーと敵キャラのアクションフラグがtrueなら
				{
					NowFase = EndFase;	// 現在のフェイズをバトルフェイズにする

					ActionFlagFalse();	// アクションフラグをfalseにする
					PreemptiveFalse();	// 先制行動フラグをfalseにする

					elapseFrameCounter = BattleSceneFPS - 1;	// エンドフェイズですぐ処理が始まるように経過フレーム数を調整
				}
			}
			break;
		case EndFase:
			/* +++ エンドフェイズの場合 +++ */

			if (elapseFrameCounter >= BattleSceneFPS)	// バトルシーンのフレーム数が経過した
			{
				elapseFrameCounter = 0;		// 経過フレーム数をリセット

				if (settingMessagePattern != Message1Line)	// メッセージの書き込み先が1行目ではない
				{
					settingMessagePattern = Message1Line;	// メッセージの書き込み先を1行目にする
				}

				if (displayMessagePattern != Message1Line)	// 表示するメッセージが1行ではない
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行にする
				}

				if (Player->GetMyActionFlag() != true)	// プレイヤーが未行動
				{
					Player->EndFase_Process();	// プレイヤーキャラのエンドフェイズの処理を実行 
				}
				else if (Enemy->GetMyActionFlag() != true)	// 敵キャラが未行動
				{
					Enemy->EndFase_Process();	// 敵キャラのエンドフェイズの処理を実行 
				}
				else	// プレイヤーと敵キャラが共に行動済み
				{
					NowFase = MainFase;	// 現在のフェイズをメインフェイズにする

					ActionFlagFalse();	// アクションフラグをfalseにする

					elapseFrameCounter = BattleSceneFPS - 1;	// 経過フレーム数を調整
				}
			}
			break;
		default:
			break;
		}
	}


	if (GameDebug)
	{
		// シーン切換からの時間が1秒以上経過しエンターキーが押されたら
		if (SceneChangeFrameCount >= GameFPS
			&& Key_Check_Click(KEY_INPUT_RETURN))
		{
			NextGameScene = GameOver_Scene;	// 次のシーンにセレクトシーンを設定
		}

		// シーン切換からの時間が1秒以上経過しスペースキーが押されたら
		if (SceneChangeFrameCount >= GameFPS
			&& Key_Check_Click(KEY_INPUT_SPACE))
		{
			NextGameScene = Result_Scene;	// 次のシーンにセレクトシーンを設定
		}
	}

	return;
}

/* +++ バトルシーンの描画関数 +++ */
void BattleScene_Draw()
{
	DrawExtendGraphConditional(0, 100, 769, 869, playerKindNumber, ISPLAYER);									// プレイヤーキャラクターの画像を描画
	DrawExtendGraphConditional(GameWindowWidth, 100, GameWindowWidth - 767, 869, enemyKindNumber, ISENEMY);		// 敵キャラの画像を描画

	DrawLineWithStruct(devideScreenLine, Color_White);	// 画面を左右に2分割する直線を描画

	DrawFormatStringToHandleAlign(GameWindowWidth/4 - 80, 0,FAlign_Center,Color_Green,MSMincho_100_1,"%s", NamePlayer);		// プレイヤーサイドの上部に「Player」の表示をする
	DrawFormatStringToHandleAlign(GameWindowWidth/4 * 3 + 30, 0,FAlign_Center,Color_Violet,MSMincho_100_1,"%s", NameEnemy);	// 敵キャラサイドの上部に「Enemy」の表示をする

	Enemy->DrawStatusUI(ISENEMY);	// 相手キャラのステータスのUI表示

	Player->DrawStatusUI(ISPLAYER);		// 自キャラのステータスのUI表示

	/* +++ メッセージウィンドウの表示 +++ */
	DrawRect(messageWindow, Color_White, false, 5);		// メッセージウィンドウの枠を描画
	DrawLineWithStruct(devideWindowLine, Color_White);	// メッセージウィンドウを分割する線を描画

	/* +++ フェイズに応じて処理を変える +++ */
	switch (NowFase)
	{
	case MainFase:
		/* +++ メインフェイズの場合 +++ */

		Player->MainFase_Draw();	// プレイヤーのメインフェイズの描画処理を実行
		Enemy->MainFase_Draw();		// 敵キャラのメインフェイズの描画処理を実行
		break;
	case BattleFase:
		/* +++ バトルフェイズの場合 +++ */

		/* +++ プレイヤーと敵キャラの速さによって処理を変える +++ */
		if (playerSpeed > enemySpeed)	// プレイヤーの方が速い
		{
			Player->BattleFase_Draw();	// プレイヤーのバトルフェイズの描画処理を実行
			Enemy->BattleFase_Draw();	// 敵キャラのバトルフェイズの描画処理を実行
		}
		else if (playerSpeed < enemySpeed)	// 敵キャラの方が速い
		{
			Enemy->BattleFase_Draw();	// 敵キャラのバトルフェイズの描画処理を実行
			Player->BattleFase_Draw();	// プレイヤーのバトルフェイズの描画処理を実行
		}
		else	// 互いの速さが同じ
		{
			/* +++ 確率によって処理を変える +++ */
			if (probability % 2 == 0)
			{
				Player->BattleFase_Draw();	// プレイヤーのバトルフェイズの描画処理を実行
				Enemy->BattleFase_Draw();	// 敵キャラのバトルフェイズの描画処理を実行
			}
			else
			{
				Enemy->BattleFase_Draw();	// 敵キャラのバトルフェイズの描画処理を実行
				Player->BattleFase_Draw();	// プレイヤーのバトルフェイズの描画処理を実行
			}
		}
		break;
	case EndFase:
		/* +++ エンドフェイズの場合 +++ */

		Player->EndFase_Draw();		// プレイヤーのエンドフェイズの描画処理を実行
		Enemy->EndFase_Draw();		// 敵キャラのエンドフェイズの描画処理を実行
		break;
	default:
		break;
	}

	/* +++ メッセージの表示パターンによって処理を変える +++ */
	switch (displayMessagePattern)
	{
	case Message1Line:
		/* +++ 1行表示の場合 +++ */

		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 550, 890,FAlign_Left,Color_White,MSMincho_40_1,"%s",battleMessage1);
		break;
	case Message2Line:
		/* +++ 2行表示の場合 +++ */

		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 550, 890, FAlign_Left, Color_White, MSMincho_40_1, "%s", battleMessage1);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 550, 930, FAlign_Left, Color_White, MSMincho_40_1, "%s", battleMessage2);
		break;
	case Message3Line:
		/* +++ 3行表示の場合 +++ */

		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 550, 890, FAlign_Left, Color_White, MSMincho_40_1, "%s", battleMessage1);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 550, 930, FAlign_Left, Color_White, MSMincho_40_1, "%s", battleMessage2);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 550, 970, FAlign_Left, Color_White, MSMincho_40_1, "%s", battleMessage3);
		break;
	case Message4Line:
		/* +++ 4行表示の場合 +++ */

		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 550, 890, FAlign_Left, Color_White, MSMincho_40_1, "%s", battleMessage1);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 550, 930, FAlign_Left, Color_White, MSMincho_40_1, "%s", battleMessage2);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 550, 970, FAlign_Left, Color_White, MSMincho_40_1, "%s", battleMessage3);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 550, 1010, FAlign_Left, Color_White, MSMincho_40_1, "%s", battleMessage4);
		break;
	default:
		break;
	}


	if (GameDebug)
	{
		Player->DrawActionNumber(GameWindowWidth / 2 - 300, 970, Color_Green, MSMincho_30_1);
		Enemy->DrawActionNumber(GameWindowWidth / 2 - 300, 1000, Color_Purple, MSMincho_30_1);

		DrawFormatStringToHandleAlign(GameWindowWidth / 2, GameWindowHeight / 2, FAlign_AllCenter, Color_switching_Rainbow, MSMincho_50_1, "GameEndMode: %d", gameEndMode);

		DrawPlayerEnemyNum();
	}

	return;
}

/* --- バトルシーンの終了関数 --- */
int BattleScene_End()
{
	Sound_Stop(&BGM_Battle);

	return 0;
}