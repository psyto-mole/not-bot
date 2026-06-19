/* === キャラセレクトシーン処理のソースファイル === */

#include "GameManager.h"
#include "Color.h"
#include "Font.h"
#include "Key.h"
#include "Mouse.h"
#include "Character.h"
#include "SceneManager.h"
#include "SelectScene.h"
#include "Message.h"
#include "Sound.h"
#include "SaveLoad.h"
#include "RectParameter.h"


int questionNumber;		// 質問の番号を格納する変数

char CharacterKind[CharacterNameLength];	// メッセージ用のキャラクターの種類を格納する変数


/* --- キャラセレクトシーンの初期化関数 --- */
int SelectScene_Init()
{
	int i;

	questionNumber = 1;		// 質問番号の初期化
	enemyKindNumber = 0;	// 敵キャラの初期化
	playerKindNumber = 0;	// 自キャラの初期化

	/* +++ 敵キャラの種類を格納する配列の初期化 +++ */
	for (i = 0; i < CharacterNameLength; i++)
	{
		CharacterKind[i]	= '\0';
	}

	return 0;	// キャラセレクトシーンの初期化の終了(0を返す)
}

/* --- キャラセレクトシーンの処理の管理関数 ---- */
void SelectScene_Manage()
{
	SelectScene_Process();	// キャラセレクトシーンの処理
	SelectScene_Draw();		// キャラセレクトシーンの初期化

	return;
}

/* +++ キャラセレクトシーンの処理関数 +++ */
void SelectScene_Process()
{
	/* +++ 質問番号に応じ、キャラクターの種類の配列にキャラクター名を格納する +++ */
	if (enemyKindNumber == 0 || playerKindNumber == 0)	// 敵キャラまたは自キャラが決定していない
	{
		switch (questionNumber)
		{
		case 1:
			/* +++ 1問目の場合 +++ */

			// 文字列「ロボット」を格納
			sprintf_s(CharacterKind, sizeof(CharacterKind), CharacterNameRobot);
			break;
		case 2:
			/* +++ 2問目の場合 +++ */

			// 文字列「人間」を格納
			sprintf_s(CharacterKind, sizeof(CharacterKind), CharacterNameHuman);
			break;
		case 3:
			/* +++ 3問目の場合 +++ */

			// 文字列「ドラゴン」を格納
			sprintf_s(CharacterKind, sizeof(CharacterKind), CharacterNameDragon);
			break;
		default:
			break;
		}
	}
	else if (SceneChangeFrameCount >= GameFPS)	// シーン切換時間を超えているなら
	{
		NextGameScene = Battle_Scene;	// 次のシーンにバトルシーンを設定
	}

	/* +++ 敵キャラと自キャラを決定する一連の処理 +++ */
	if (elapseFrameCounter >= SelectBoxInterval)	// 経過時間がメッセージのインターバルを超えているなら
	{
		// 「はい」のボタンが押された
		if (CollisionRectToPoint(selectBoxYes, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Click);

			if (enemyKindNumber == 0)	// 敵キャラが決まっていないなら
			{
				questionNumber += 1;	// 質問番号を1増やす

				if (total_saveArray_Now < 5)
				{
					// 質問番号が3を超えたら
					if (questionNumber > 3)
					{
						questionNumber = 1;		// 質問番号を1にもどす
					}
				}
				else if (total_saveArray_Now < 10)
				{
					// 質問番号が4を超えたら
					if (questionNumber > 4)
					{
						questionNumber = 1;		// 質問番号を1にもどす
					}
				}
				else if (total_saveArray_Now < 25)
				{
					// 質問番号が5を超えたら
					if (questionNumber > 5)
					{
						questionNumber = 1;		// 質問番号を1にもどす
					}
				}
				else
				{
					// 質問番号がキャラクター数を超えたら
					if (questionNumber > CharacterNumber)
					{
						enemyKindNumber = 99;	// 敵キャラの識別番号を99に設定
						questionNumber = 1;		// 質問番号を1にもどす
					}
				}
			}
			else if (playerKindNumber == 0)	// 自キャラが決まっていないなら
			{
				playerKindNumber = questionNumber;	// 自キャラの識別番号に質問番号を設定
				questionNumber = 1;					// 質問番号を1に戻す
			}

			elapseFrameCounter = 0;	// 経過時間を0にする
		}
		// 「いいえ」のボタンを押された
		else if (CollisionRectToPoint(selectBoxNo, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))
		{
			Sound_Play(SE_Click);

			if (enemyKindNumber == 0)	// 敵キャラが決まっていない
			{
				enemyKindNumber = questionNumber;	// 敵キャラの識別番号に質問番号を設定
				questionNumber = 1;					// 質問番号を1に戻す
			}
			else if (playerKindNumber == 0)	// 自キャラが決まっていない
			{
				questionNumber += 1;	// 質問番号を1増やす

				if (total_saveArray_Now < 5)
				{
					// 質問番号が3を超えたら
					if (questionNumber > 3)
					{
						questionNumber = 1;		// 質問番号を1に戻す
					}
				}
				else if (total_saveArray_Now < 10)
				{
					// 質問番号が4を超えたら
					if (questionNumber > 4)
					{
						questionNumber = 1;		// 質問番号を1に戻す
					}
				}
				else if (total_saveArray_Now < 25)
				{
					// 質問番号が5を超えたら
					if (questionNumber > 5)
					{
						questionNumber = 1;		// 質問番号を1に戻す
					}
				}
				else
				{
					// 質問番号がキャラクターの種類を超えたら
					if (questionNumber > CharacterNumber)
					{
						playerKindNumber = 99;	// 自キャラの識別番号を99に設定
						questionNumber = 1;		// 質問番号を1に戻す
					}
				}
			}

			elapseFrameCounter = 0;	// 経過時間を0にする
		}
	}

	return;
}

/* +++ キャラセレクトシーンの描画関数 +++ */
void SelectScene_Draw()
{
	/* +++ メッセージボックスを描画する一連の処理 +++ */
	if (elapseFrameCounter >= SelectBoxInterval)	// メッセージ表示のインターバル以上の時間が経過した
	{
		if (enemyKindNumber == 0 || playerKindNumber == 0)	// 敵キャラまたは自キャラが決定していない
		{
			DrawRect(selectBoxBackGround, Color_White, true, 1);	// メッセージボックスの背景を描画

			if (enemyKindNumber == 0)	// 敵キャラが決まっていない
			{
				if (questionNumber <= 3)	// 質問番号が3以下なら
				{
					// 敵キャラについての質問の文章を組み合わせて描画
					DrawFormatStringToHandleAlign(
						GameWindowWidth / 2, GameWindowHeight / 2 - 40, FAlign_Center, Color_Black,
						MSMincho_20_1, "%s%s%s", EnemyQuestionHead, CharacterKind, EnemyQuestionBottom
					);
				}
				else if (questionNumber == 4)	// 質問番号が4なら
				{
					// ダイトメアについての質問の文章を組み合わせて描画
					DrawFormatStringToHandleAlign(
						GameWindowWidth / 2, GameWindowHeight / 2 - 40, FAlign_Center, Color_Black,
						MSMincho_20_1, "%s%s%s", EnemyQuestionHead, BothQuestionDightmare, EnemyQuestionBottom
					);
				}
				else if (questionNumber == 5)	// 質問番号が5なら
				{
					// キューについての質問の文章を組み合わせて描画
					DrawFormatStringToHandleAlign(
						GameWindowWidth / 2, GameWindowHeight / 2 - 40, FAlign_Center, Color_Black,
						MSMincho_20_1, "%s%s%s", EnemyQuestionHead, BothQuestionNoname, EnemyQuestionBottom
					);
				}
			}
			else if (playerKindNumber == 0)	// 自キャラが決まっていない
			{
				if (questionNumber <= 3)	// 質問番号が3以下なら
				{
					// 自キャラについての質問の文章を組み合わせて描画
					DrawFormatStringToHandleAlign(
						GameWindowWidth / 2, GameWindowHeight / 2 - 40, FAlign_Center, Color_Black,
						MSMincho_20_1, "%s%s%s", PlayerQuestionHead, CharacterKind, PlayerQuestionBottom
					);
				}
				else if (questionNumber == 4)
				{
					// ダイトメアについての質問の文章を組み合わせて描画
					DrawFormatStringToHandleAlign(
						GameWindowWidth / 2, GameWindowHeight / 2 - 40, FAlign_Center, Color_Black,
						MSMincho_20_1, "%s%s%s", PlayerQuestionHead, BothQuestionDightmare, PlayerQuestionBottom
					);
				}
				else if (questionNumber == 5)
				{
					// キューについての質問の文章を組み合わせて描画
					DrawFormatStringToHandleAlign(
						GameWindowWidth / 2, GameWindowHeight / 2 - 40, FAlign_Center, Color_Black,
						MSMincho_20_1, "%s%s%s", PlayerQuestionHead, BothQuestionNoname, PlayerQuestionBottom
					);
				}
			}

			/* +++ 「はい」ボタンの描画処理 +++ */
			if (CollisionRectToPoint(selectBoxYes, nowMousePoint))		// マウスカーソルがボタンに触れている
			{
				// ボタンを緑色に塗りつぶす
				DrawRect(selectBoxYes, Color_Green, true,1);

				// 「はい」文字を白で描画
				DrawFormatStringToHandleAlign(
					SelectBoxYesCenterX, SelectBoxButtonCenterY, FAlign_AllCenter,
					Color_White, MSMincho_20_1, ResponseYes
				);
			}
			else
			{
				// 枠が緑色のボタンを描画
				DrawRect(selectBoxYes, Color_Green, false,1);

				// 「はい」を黒で描画
				DrawFormatStringToHandleAlign(
					SelectBoxYesCenterX, SelectBoxButtonCenterY, FAlign_AllCenter,
					Color_Black, MSMincho_20_1, ResponseYes
				);
			}

			/* +++ 「いいえ」ボタンの描画処理 +++ */
			if (CollisionRectToPoint(selectBoxNo, nowMousePoint))	// マウスカーソルがボタンに触れている
			{
				// ボタンを紫色で塗りつぶす
				DrawRect(selectBoxNo, Color_Violet, true,1);

				// 「いいえ」の文字を白で描画
				DrawFormatStringToHandleAlign(
					SelectBoxNoCenterX, SelectBoxButtonCenterY, FAlign_AllCenter,
					Color_White, MSMincho_20_1, ResponseNo
				);
			}
			else
			{
				// 枠が紫のボタンを描画
				DrawRect(selectBoxNo, Color_Violet, false,1);

				// 「いいえ」の文字を黒で描画
				DrawFormatStringToHandleAlign(
					SelectBoxNoCenterX, SelectBoxButtonCenterY, FAlign_AllCenter,
					Color_Black, MSMincho_20_1, ResponseNo
				);
			}
		}
	}

	return;
}

/* --- セレクトシーンの終了関数 --- */
int SelectScene_End()
{
	return 0;
}