/* === Sheppキャラクター関連のソースファイル === */

#include <string.h>
#include "Shepp.h"
#include "GameManager.h"
#include "Geometry.h"
#include "Color.h"
#include "Font.h"
#include "Key.h"
#include "Mouse.h"
#include "Message.h"
#include "Sound.h"
#include "Rectparameter.h"
#include "BattleScene.h"

Shepp PlShepp, EnShepp;			// Sheppクラスの変数

/* +++ Sheppクラスのオーバーライド +++ */
void Shepp::Character_Init(bool isThisPlayer)
{
	/* +++ 各種パラメータを設定 +++ */
	MaxHP			= SheppHP;
	MaxMP			= SheppMP;
	OriginAttack	= SheppAttack;
	OriginDefence	= SheppDefence;
	OriginMagic		= SheppMagic;
	OriginPrevent	= SheppPrevent;
	OriginSpeed		= SheppSpeed;

	/* +++ 最大HPと最大MP、元々のステータスを設定 +++ */
	HP		= MaxHP;
	MP		= MaxMP;
	TP		= 0;
	Attack	= OriginAttack;
	Defence = OriginDefence;
	Magic	= OriginMagic;
	Prevent = OriginPrevent;
	Speed	= OriginSpeed;

	/* +++ 行動関係の変数を初期化 +++ */
	actionFlag = false;
	actionNumber = 0;
	randomNumber = 0;
	attackPreemptive = false;
	defencePreemptive = false;

	defenceCoefficient = 1.0;	// 防御係数を初期化

	statusAilment = Fine;		// 状態を「異常なし」に設定
	ailmentTurn = 0;			// 状態異常の継続ターンを0にする
	ailmentPoisoning = false;	// 「毒」の状態異常を解除

	sprintf_s(characterName, sizeof(characterName),"%s", CharacterNameShepp);

	if (isThisPlayer)
	{
		isPlayer = true;
	}
	else
	{
		isPlayer = false;
	}

	return;
}

void Shepp::MainFase_Process()
{
	if (actionFlag)		// 行動済みなら(アクションフラグがtrueなら)
	{
		return;		// 何もせずに終了する
	}
	else	// 行動済みでないなら
	{
		if (isPlayer)	// プレイヤーキャラなら
		{
			/* +++ 押されたボタン(optionButton1～4,backButton)に応じて処理を変える +++ */
			if (CollisionRectToPoint(optionButton1, nowMousePoint))		// 選択肢1にカーソルが合っている
			{
				if (actionNumber < 10)	// アクションナンバーが10未満なら
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 通常攻撃の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfNormalAttack);
				}
				else if (actionNumber == 20)		// アクションナンバーが20なら
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// μの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicMu);
				}
				else if (actionNumber == 30)
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// ψの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfPsi);
				}

				if (Mouse_Check_Click(MOUSE_INPUT_LEFT))	// マウスがクリックされた
				{
					if (actionNumber < 10)	// アクションナンバーが10未満なら
					{
						Sound_Play(SE_Enter);

						actionNumber = 10;	// アクションナンバーに10を代入する

						MyActionFlagTrue();	// アクションフラグをtrueにする
					}
					else if (actionNumber == 20)		// アクションナンバーが20なら
					{
						if (MP >= MPofMagicMu)	// MPがμの消費MP以上なら
						{
							Sound_Play(SE_Enter);

							actionNumber += 1;	// アクションナンバーに1を加算する

							MyActionFlagTrue();	// アクションフラグをtrueにする
						}
						else
						{
							Sound_Play(SE_Unavilable);
						}
					}
					else if (actionNumber == 30)	// アクションナンバーが30なら
					{
						if (TP >= TPofPsi)	// TPがψの消費TP以上なら
						{
							Sound_Play(SE_Enter);

							actionNumber += 1;	// アクションナンバーに1を加算する

							MyActionFlagTrue();	// アクションフラグをtrueにする
						}
						else
						{
							Sound_Play(SE_Unavilable);
						}
					}
				}
			}
			else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2にカーソルがあっている
			{
				if (actionNumber < 10)	// アクションナンバーが10未満なら
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 魔法の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagic);
				}
				else if (actionNumber == 20)
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// νの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicNu);
				}
				else if (actionNumber == 30)
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// Ωの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfOmega);
				}

				if (Mouse_Check_Click(MOUSE_INPUT_LEFT))	// マウスがクリックされた
				{
					if (actionNumber < 10)	// アクションナンバーが10未満なら
					{
						Sound_Play(SE_Enter);

						actionNumber = 20;	// アクションナンバーに20を代入する
					}
					else if (actionNumber == 20)		// アクションナンバーが20なら
					{
						if (MP >= MPofMagicNu)		// MPがνの消費MP以上なら
						{
							Sound_Play(SE_Enter);

							actionNumber += 2;		// アクションナンバーに2を加える

							MyActionFlagTrue();		// アクションフラグをtrueにする
						}
						else
						{
							Sound_Play(SE_Unavilable);
						}
					}
					else if (actionNumber == 30)		// アクションナンバーが30なら
					{
						if (TP >= TPofOmega)		// TPがΩの消費TP以上なら
						{
							Sound_Play(SE_Enter);

							actionNumber += 2;		// アクションナンバーに2を加算する

							MyActionFlagTrue();		// アクションフラグをtrueにする
						}
						else
						{
							Sound_Play(SE_Unavilable);
						}
					}
				}
			}
			else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3にカーソルがあっている
			{
				if (actionNumber < 10)	// アクションナンバーが10未満なら
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 特技の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfSpecial);
				}
				else if (actionNumber == 20)		// アクションナンバーが20なら
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// Λの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicLambda);
				}
				else if (actionNumber == 30)
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// Σの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfSigma);
				}

				if (Mouse_Check_Click(MOUSE_INPUT_LEFT))	// マウスがクリックされた
				{
					if (actionNumber < 10)	// アクションナンバーが10未満なら
					{
						Sound_Play(SE_Enter);

						actionNumber = 30;	// アクションナンバーに30を代入
					}
					else if (actionNumber == 20)	// アクションナンバーが20なら
					{
						if (MP >= MPofMagicLambda)	// MPがΛの消費MP以上なら
						{
							Sound_Play(SE_Enter);

							actionNumber += 3;	// アクションナンバーに3を加算する

							MyActionFlagTrue();	// アクションフラグをtrueにする
						}
						else
						{
							Sound_Play(SE_Unavilable);
						}
					}
					else if (actionNumber == 30)	// アクションナンバーが30なら
					{
						if (TP >= TPofSigma)		// TPがΣの消費TP以上なら
						{
							Sound_Play(SE_Enter);

							actionNumber += 3;	// アクションナンバーに3を加算する

							MyActionFlagTrue();	// アクションフラグをtrueにする
						}
						else
						{
							Sound_Play(SE_Unavilable);
						}
					}
				}
			}
			else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4にカーソルがあっている
			{
				if (actionNumber < 10)	// アクションナンバーが10未満なら
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 通常防御の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfNormalDefence);
				}
				else if (actionNumber == 20)		// アクションナンバーが20なら
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// ξの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicXi);
				}
				else if (actionNumber == 30)		// アクションナンバーが30なら
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// ηの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfEta);
				}

				if (Mouse_Check_Click(MOUSE_INPUT_LEFT))	// マウスがクリックされた
				{
					if (actionNumber < 10)	// アクションナンバーが10未満なら
					{
						Sound_Play(SE_Enter);

						actionNumber = 40;	// アクションナンバーに40を代入

						MyDefencePreemptiveTrue();	// 自身の先制防御フラグをtrueにする

						MyActionFlagTrue();	// アクションフラグをtrueにする
					}
					else if (actionNumber == 20)	// アクションナンバーが20なら
					{
						if (MP >= MPofMagicXi)		// MPがξの消費MP以上なら
						{
							Sound_Play(SE_Enter);

							actionNumber += 4;	// アクションナンバーに4を加算する

							MyActionFlagTrue();		// アクションフラグをtrueにする
						}
						else
						{
							Sound_Play(SE_Unavilable);
						}
					}
					else if (actionNumber == 30)	// アクションナンバーが30なら
					{
						if (TP >= TPofEta)	// TPがηの消費TP以上なら
						{
							Sound_Play(SE_Enter);

							actionNumber += 4;	// アクションナンバーに4を加算する

							MyActionFlagTrue();	// アクションフラグをtrueにする
						}
						else
						{
							Sound_Play(SE_Unavilable);
						}
					}
				}
			}
			else if (CollisionRectToPoint(backButton, nowMousePoint) && Mouse_Check_Click(MOUSE_INPUT_LEFT))	// 「戻る」ボタンが押された
			{
				if (actionNumber == 20 || actionNumber == 30)	// アクションナンバーが20または30なら
				{
					Sound_Play(SE_Back);

					actionNumber = 0;	// アクションナンバーを0にする
				}
			}
		}
		else	// 敵キャラなら
		{
			randomNumber = GetRand(3) + 1;	// 1～4の乱数を生成

			/* +++ アクションナンバーと乱数の値によって処理を変更 +++ */
			if (actionNumber < 10)		// アクションナンバーが10未満
			{
				actionNumber = randomNumber * 10;	// アクションナンバーに乱数の10倍を代入
			}
			else if (actionNumber == 10 || actionNumber == 40)	// アクションナンバーが10または40
			{
				if (actionNumber == 40)
				{
					MyDefencePreemptiveTrue();
				}

				MyActionFlagTrue();	// アクションフラグをtrueにする
			}
			else if (actionNumber == 20)	// アクションナンバーが20
			{
				/* +++ 乱数の値によって処理を変更 ++ */
				switch (randomNumber)
				{
				case 1:
					/* +++ 乱数の値が1 +++ */

					if (MP < MPofMagicMu)	// MPがμの消費MP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 2:
					/* +++ 乱数の値が2 +++ */

					if (MP < MPofMagicNu)	// MPがνの消費MP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 3:
					/* +++ 乱数の値が3 +++ */

					if (MP < MPofMagicLambda)	// MPがΛの消費MP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 4:
					/* +++ 乱数の値が4 +++ */

					if (MP < MPofMagicXi)	// MPがξの消費MP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				default:
					break;
				}

				actionNumber += randomNumber;	// アクションナンバーに乱数を加算

				MyActionFlagTrue();	// アクションフラグをtrueにする
			}
			else if (actionNumber == 30)	// アクションナンバーが30
			{
				/* +++ 乱数の値によって処理を変更 ++ */
				switch (randomNumber)
				{
				case 1:
					/* +++ 乱数の値が1 +++ */

					if (TP < TPofPsi)	// TPがの消費TPψ未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 2:
					/* +++ 乱数の値が2 +++ */

					if (TP < TPofOmega)	// TPがΩの消費TP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 3:
					/* +++ 乱数の値が3 +++ */

					if (TP < TPofSigma)	// TPがΣの消費TP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 4:
					/* +++ 乱数の値が4 +++ */

					if (TP < TPofEta)	// TPがηの消費TP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				default:
					break;
				}

				actionNumber += randomNumber;	// アクションナンバーに乱数を加算

				MyActionFlagTrue();	// アクションフラグをtrueにする
			}
		}
	}

	return;
}

void Shepp::MainFase_Draw()
{
	if (isPlayer)	// プレイヤーキャラなら
	{
		if (actionNumber < 10)	// アクションナンバーが10未満なら
		{
			/* +++ 4つの選択肢のボタンを白枠で描画 +++ */
			DrawRect(optionButton1, Color_White, false, 3);
			DrawRect(optionButton2, Color_White, false, 3);
			DrawRect(optionButton3, Color_White, false, 3);
			DrawRect(optionButton4, Color_White, false, 3);

			/* +++ 4つの基本選択肢のテキストを白で描画 +++ */
			DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionAttack);
			DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagic);
			DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionSpecial);
			DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionDefence);

			/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
			if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
			{
				DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

				// 選択肢1のテキストを黒で描画
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionAttack);
			}
			else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
			{
				DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

				// 選択肢2のテキストを黒で描画
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagic);
			}
			else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
			{
				DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

				// 選択肢3のテキストを黒で描画
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionSpecial);
			}
			else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
			{
				DrawRect(optionButton4, Color_White, true, 3);		// 選択肢4ボタンを白で塗りつぶして描画

				// 選択肢4のテキストを黒で描画
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionDefence);
			}
		}
		else if (actionNumber == 20)
		{
			if (MP < MPofMagicMu)
			{
				/* +++ 4つの選択肢のボタンを灰色枠で描画 +++ */
				DrawRect(optionButton1, Color_Gray, false, 3);
				DrawRect(optionButton2, Color_Gray, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 魔法の選択肢のテキストを灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicMu);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicNu);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicLambda);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicXi);
			}
			else
			{
				/* +++ 4つの選択肢のボタンを白枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_White, false, 3);
				DrawRect(optionButton3, Color_White, false, 3);
				DrawRect(optionButton4, Color_White, false, 3);

				/* +++ 特技の選択肢のテキストを白で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicMu);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicNu);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicLambda);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicXi);

				/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicMu);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicNu);
				}
				else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3ボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

					// 選択肢3のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicLambda);
				}
				else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton4, Color_White, true, 3);		// 選択肢4ボタンを白で塗りつぶして描画

					// 選択肢4のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicXi);
				}
			}

			DrawBackBottun();
		}
		else if (actionNumber == 30)	// アクションナンバーが30である
		{
			if (TP < TPofPsi)
			{
				/* +++ 4つの選択肢のボタンを灰枠で描画 +++ */
				DrawRect(optionButton1, Color_Gray, false, 3);
				DrawRect(optionButton2, Color_Gray, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionPsi);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionOmega);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionSigma);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionEta);
			}
			else if (TP < TPofOmega)
			{
				/* +++ 3つの選択肢のボタンを灰色枠で描画 +++ */
				DrawRect(optionButton2, Color_Gray, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionOmega);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionSigma);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionEta);

				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionPsi);
				}
				else
				{
					DrawRect(optionButton1, Color_White, false, 3);		// 選択肢1ボタンを白枠で描画

					// 選択肢1のテキストを白で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionPsi);
				}
			}
			else if (TP < TPofSigma)
			{
				/* +++ 4つの選択肢のボタン白または灰色枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_White, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを白または灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionPsi);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionOmega);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionSigma);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionEta);

				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionPsi);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionOmega);
				}
			}
			else if (TP < TPofEta)
			{
				/* +++ 4つの選択肢のボタンを白枠または灰枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_White, false, 3);
				DrawRect(optionButton3, Color_White, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを白または灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionPsi);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionOmega);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionSigma);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionEta);

				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionPsi);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);	// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionOmega);
				}
				else if (CollisionRectToPoint(optionButton3, nowMousePoint))		// 選択肢3のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton3, Color_White, true, 3);	// 選択肢3のボタンを白で塗りつぶして描画

					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionSigma);
				}
			}
			else
			{
				/* +++ 4つの選択肢のボタンを白枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_White, false, 3);
				DrawRect(optionButton3, Color_White, false, 3);
				DrawRect(optionButton4, Color_White, false, 3);

				/* +++ 特技の選択肢のテキストを白で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionPsi);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionOmega);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionSigma);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionEta);

				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionPsi);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionOmega);
				}
				else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

					// 選択肢3のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionSigma);
				}
				else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton4, Color_White, true, 3);		// 選択肢4ボタンを白で塗りつぶして描画

					// 選択肢4のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionEta);
				}
			}

			DrawBackBottun();
		}
	}

	return;
}


void Shepp::BattleFase_Process()
{
	if (actionFlag == false)	// アクションフラグがfalseなら
	{
		/* +++ アクションナンバーによって処理を変える +++ */
		switch (actionNumber)
		{
		case 10:
			/* +++ アクションナンバーが10 +++ */

			NormalAttack();		// 通常攻撃を実行
			break;
		case 21:
			/* +++ アクションナンバーが21 +++ */

			MagicMu();	// μを実行
			break;
		case 22:
			/* +++ アクションナンバーが22 +++ */

			MagicNu();		// νを実行
			break;
		case 23:
			/* +++ アクションナンバーが23 +++ */

			MagicLambda();	// Λを実行
			break;
		case 24:
			/* +++ アクションナンバーが24 +++ */

			MagicXi();	// ξを実行
			break;
		case 31:
			/* +++ アクションナンバーが31 +++ */

			Psi();		// ψを実行
			break;
		case 32:
			/* +++ アクションナンバーが32 +++ */

			Omega();	// Ωを実行
			break;
		case 33:
			/* +++ アクションナンバーが33 +++ */

			Sigma();	// Σを実行
			break;
		case 34:
			/* +++ アクションナンバーが34 +++ */

			Eta();		// ηを実行
			break;
		case 40:
			/* +++ アクションナンバーが40 +++ */

			NormalDefence();	// 通常防御を実行
			break;
		default:
			break;
		}

		actionNumber = 0;	// アクションナンバーをリセット
		MyActionFlagTrue();		// アクションフラグをtrueにする
	}

	return;
}

void Shepp::BattleFase_Draw()
{


	return;
}

void Shepp::EndFase_Process()
{
	if (actionFlag == false)	// アクションフラグがfalseなら
	{
		if (HP < MaxHP)
		{
			HP_Calc(30, ISHEAL);
		}

		TP_Calc(10, ISENHANCE);

		if (defenceCoefficient != 1)
		{
			defenceCoefficient = 1;
		}

		MyActionFlagTrue();
	}

	return;
}

void Shepp::EndFase_Draw()
{


	return;
}

/* --- μ - TPを増加させる(MP:30) --- */
void Shepp::MagicMu()
{
	MP_Calc(MPofMagicMu, ISREDUCTION);

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message2Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicMu);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicMu);
	}

	TP_Calc(50, ISENHANCE);

	Sound_Play(SE_MagicMu);

	return;
}

/* --- ν - 最大HPを増加させる(MP:30) --- */
void Shepp::MagicNu()
{
	MP_Calc(MPofMagicNu, ISREDUCTION);

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message2Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicNu);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicNu);
	}

	MaxHP_Calc(500, ISENHANCE);
	HP_Calc(500, ISHEAL);

	Sound_Play(SE_MagicNu);

	return;
}

/* --- Λ - 魔力を増加させる(MP:30) --- */
void Shepp::MagicLambda()
{
	int calcResult;

	MP_Calc(MPofMagicLambda, ISREDUCTION);

	calcResult = (int)(Magic * 2);

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message1Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicLambda);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicLambda);
	}

	Magic_Calc(calcResult, ISENHANCE);

	Sound_Play(SE_MagicLambda);

	return;
}

/* --- ξ - 相手の守備力、魔法守備力、TPを減少させる(MP:30) --- */
void Shepp::MagicXi()
{
	MP_Calc(MPofMagicXi, ISREDUCTION);	// MPを消費MP分減らす

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message4Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicXi);

		Enemy->Defence_Calc(100, ISREDUCTION);
		Enemy->Prevent_Calc(100, ISREDUCTION);
		Enemy->TP_Calc(30, ISREDUCTION, ISDISPLAY);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicXi);

		Player->Defence_Calc(100, ISREDUCTION);
		Player->Prevent_Calc(100, ISREDUCTION);
		Player->TP_Calc(30, ISREDUCTION, ISDISPLAY);
	}

	Sound_Play(SE_MagicXi);

	return;
}

/* --- ψ - 攻撃力参照の物理攻撃(TP:20) --- */
void Shepp::Psi()
{
	int calcResult;		// 計算結果の格納変数

	TP_Calc(TPofPsi, ISREDUCTION);	// TPを消費TP分減らす

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message2Line;

	calcResult = (int)(Attack * 2.5);	// 攻撃力に補正をのせる

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionPsi);

		Enemy->Damage_Calc(calcResult, Physical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionPsi);

		Player->Damage_Calc(calcResult, Physical);
	}

	Sound_Play(SE_Psi);

	return;
}

/* --- Ω - 魔力を消費しTPを増加させる、または魔力を回復する(TP:25) --- */
void Shepp::Omega()
{
	int calcResult;

	TP_Calc(TPofOmega, ISREDUCTION);

	settingMessagePattern = Message2Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionOmega);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionOmega);
	}

	if (Magic >= 2)
	{
		calcResult = (int)(Magic / 2);

		displayMessagePattern = Message3Line;

		Magic_Calc(calcResult, ISREDUCTION);
		TP_Calc(50, ISENHANCE);
	}
	else
	{
		displayMessagePattern = Message2Line;

		Magic_Calc(100, ISENHANCE);
	}

	Sound_Play(SE_Omega);

	return;
}

/* --- Σ - 攻撃力参照のブレス攻撃(TP:35) --- */
void Shepp::Sigma()
{
	int calcResult;		// 計算結果の格納変数

	TP_Calc(TPofSigma, ISREDUCTION);	// TPを消費TP分減らす

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message2Line;

	calcResult = (int)(Attack * 1.5);	// 攻撃力に補正をのせる

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionSigma);

		Enemy->Damage_Calc(calcResult, Breath);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionSigma);

		Player->Damage_Calc(calcResult, Breath);
	}

	Sound_Play(SE_Sigma);

	return;
}

/* --- η - η-魔力参照の魔法攻撃(TP:100) --- */
void Shepp::Eta()
{
	int calcResult;

	TP_Calc(TPofEta, ISREDUCTION);

	calcResult = (int)(Magic * 4);

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message2Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionEta);

		Enemy->Damage_Calc(calcResult, Magical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionEta);

		Player->Damage_Calc(calcResult, Magical);
	}

	Sound_Play(SE_Eta);

	return;
}