/* === キュー関連のソースファイル === */

#include <string.h>
#include "Noname.h"
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

Noname PlNoname, EnNoname;			// キュークラスの変数

/* +++ 人間クラスのオーバーライド +++ */
void Noname::Character_Init(bool isThisPlayer)
{
	/* +++ 最大HPと最大MP、元々のステータスを設定 +++ */
	MaxHP = NonameHP;
	MaxMP = NonameMP;
	OriginAttack = NonameAttack;
	OriginDefence = NonameDefence;
	OriginMagic = NonameMagic;
	OriginPrevent = NonamePrevent;
	OriginSpeed = NonameSpeed;

	/* +++ 各種パラメータを設定 +++ */
	HP = MaxHP;
	MP = MaxMP;
	TP = 0;
	Attack = OriginAttack;
	Defence = OriginDefence;
	Magic = OriginMagic;
	Prevent = OriginPrevent;
	Speed = OriginSpeed;

	/* +++ 行動関係の変数を初期化 +++ */
	actionFlag = false;
	actionNumber = 0;
	randomNumber = 0;
	attackPreemptive = false;
	defencePreemptive = false;

	defenceCoefficient = 1.0;		// 防御係数を初期化

	sprintf_s(characterName, sizeof(characterName), "%s", CharacterNameNoname);

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

/* ---メインフェイズの処理関数  --- */
void Noname::MainFase_Process()
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

					// ダーク(仮)の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicTentativeDark);
				}
				else if (actionNumber == 30)
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 雷刃(仮)の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfTentativeThunder);
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
						if (MP >= MPofMagicTentativeDark)	// MPがダーク(仮)の消費MP以上なら
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
						if (TP >= TPofTentativeThunder)	// TPが雷刃(仮)の消費TP以上なら
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

					// ライト(仮)の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicTentativeLight);
				}
				else if (actionNumber == 30)
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 毒刃(仮)の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfTentativePoison);
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
						if (MP >= MPofMagicTentativeLight)		// MPがライト(仮)の消費MP以上なら
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
						if (TP >= TPofTentativePoison)		// TPが毒刃(仮)の消費TP以上なら
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

					if (HP < MaxHP)
					{
						// ヒール(仮)の説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicTentativeHeal);
					}
					else
					{
						// 使用不可の説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailUnavilableMaxHP);
					}
				}
				else if (actionNumber == 30)
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 無の息(仮)の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfTentativeBreath);
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
						if (MP >= MPofMagicTentativeHeal)	// MPがヒール(仮)の消費MP以上なら
						{
							if (HP < MaxHP)
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
						else
						{
							Sound_Play(SE_Unavilable);
						}
					}
					else if (actionNumber == 30)	// アクションナンバーが30なら
					{
						if (TP >= TPofTentativeBreath)	// TPが無の息(仮)の消費TP以上なら
						{
							Sound_Play(SE_Enter);

							actionNumber += 3;	// アクションナンバーに3を加算する

							MyActionFlagTrue();	// アクションフラグをtrueにする
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

					// ロック(仮)の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicTentativeRock);
				}
				else if (actionNumber == 30)		// アクションナンバーが30なら
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 最終撃(仮)の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfTentativeFinal);
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
						if (MP >= MPofMagicTentativeRock)	// MPがロック(仮)の消費MP以上なら
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
						if (TP >= TPofTentativeFinal)	// TPが最終撃(仮)の消費TP以上なら
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

					if (MP < MPofMagicTentativeDark)	// MPがダーク(仮)の消費MP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 2:
					/* +++ 乱数の値が2 +++ */

					if (MP < MPofMagicTentativeLight)	// MPがライト(仮)の消費MP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					else
					{
						MyAttackPreemptiveTrue();	// 自身の先制攻撃をフラグをtrueにする
					}
					break;
				case 3:
					/* +++ 乱数の値が3 +++ */

					if (MP < MPofMagicTentativeHeal || HP >= MaxHP)		// MPがヒール(仮)の消費MP未満またはHPが最大HP以上なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 4:
					/* +++ 乱数の値が4 +++ */

					if (MP < MPofMagicTentativeRock)	// MPがロック(仮)の消費MP未満なら
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

					if (TP < TPofTentativeThunder)	// TPが雷刃(仮)の消費TP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 2:
					/* +++ 乱数の値が2 +++ */

					if (TP < TPofTentativePoison)	// TPが毒刃(仮)の消費TP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 3:
					/* +++ 乱数の値が3 +++ */

					if (TP < TPofTentativeBreath)	// TPが無の息(仮)の消費TP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 4:
					/* +++ 乱数の値が4 +++ */

					if (TP < TPofTentativeFinal)	// TPが最終撃(仮)の消費TP未満なら
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

void Noname::MainFase_Draw()
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
			if (MP < MPofMagicTentativeHeal)
			{
				/* +++ 4つの選択肢のボタンを灰色枠で描画 +++ */
				DrawRect(optionButton1, Color_Gray, false, 3);
				DrawRect(optionButton2, Color_Gray, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 魔法の選択肢のテキストを灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicTentativeDark);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicTentativeLight);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicTentativeHeal);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicTentativeRock);
			}
			else if (MP < MPofMagicTentativeRock)
			{
				/* +++ 3つの選択肢のボタンを白または灰色枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_White, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 魔法の選択肢のテキストを白または灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicTentativeDark);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicTentativeLight);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicTentativeRock);

				/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicTentativeDark);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicTentativeLight);
				}

				if (HP < MaxHP)
				{
					if (CollisionRectToPoint(optionButton3, nowMousePoint))		// 選択肢3のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicTentativeHeal);
					}
					else
					{
						DrawRect(optionButton3, Color_White, false, 3);		// 選択肢3ボタンを白で描画

						// 選択肢3のテキストを白で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicTentativeHeal);
					}
				}
				else
				{
					DrawRect(optionButton3, Color_Gray, false, 3);		// 選択肢3ボタンを灰色で描画

					// 選択肢3のテキストを灰色で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicTentativeHeal);
				}
			}
			else
			{
				/* +++ 3つの選択肢のボタンを白枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_White, false, 3);
				DrawRect(optionButton4, Color_White, false, 3);

				/* +++ 魔法の選択肢のテキストを白で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicTentativeDark);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicTentativeLight);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicTentativeRock);

				/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicTentativeDark);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicTentativeLight);
				}
				else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton4, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢4のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicTentativeRock);
				}

				if (HP < MaxHP)
				{
					if (CollisionRectToPoint(optionButton3, nowMousePoint))		// 選択肢3のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicTentativeHeal);
					}
					else
					{
						DrawRect(optionButton3, Color_White, false, 3);		// 選択肢3ボタンを白で描画

						// 選択肢3のテキストを白で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicTentativeHeal);
					}
				}
				else
				{
					DrawRect(optionButton3, Color_Gray, false, 3);		// 選択肢3ボタンを灰色で描画

					// 選択肢3のテキストを灰色で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicTentativeHeal);
				}
			}

			DrawBackBottun();
		}
		else if (actionNumber == 30)	// アクションナンバーが30である
		{
			if (TP < TPofTentativePoison)
			{
				/* +++ 4つの選択肢のボタンを灰枠で描画 +++ */
				DrawRect(optionButton1, Color_Gray, false, 3);
				DrawRect(optionButton2, Color_Gray, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionTentativeThunder);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionTentativePoison);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionTentativeBreath);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionTentativeFinal);
			}
			else if (TP < TPofTentativeBreath)
			{
				/* +++ 4つの選択肢のボタンを白または灰色枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_White, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを白または灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTentativeThunder);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTentativePoison);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionTentativeBreath);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionTentativeFinal);

				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTentativeThunder);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTentativePoison);
				}
			}
			else if (TP < TPofTentativeFinal)
			{
				/* +++ 4つの選択肢のボタン白または灰色枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_White, false, 3);
				DrawRect(optionButton3, Color_White, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを白または灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTentativeThunder);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTentativePoison);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTentativeBreath);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionTentativeFinal);

				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTentativeThunder);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTentativePoison);
				}
				else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

					// 選択肢3のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTentativeBreath);
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
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTentativeThunder);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTentativePoison);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTentativeBreath);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTentativeFinal);

				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTentativeThunder);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTentativePoison);
				}
				else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

					// 選択肢3のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTentativeBreath);
				}
				else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton4, Color_White, true, 3);		// 選択肢4ボタンを白で塗りつぶして描画

					// 選択肢4のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTentativeFinal);
				}
			}

			DrawBackBottun();
		}
	}

	return;
}


void Noname::BattleFase_Process()
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

			MagicTentativeDark();	// ダーク(仮)を実行
			break;
		case 22:
			/* +++ アクションナンバーが22 +++ */

			MagicTentativeLight();		// ライト(仮)を実行
			break;
		case 23:
			/* +++ アクションナンバーが23 +++ */

			MagicTentativeHeal();		// ヒール(仮)を実行
			break;
		case 24:
			/* +++ アクションナンバーが24 +++ */

			MagicTentativeRock();	// ロック(仮)を実行
			break;
		case 31:
			/* +++ アクションナンバーが31 +++ */

			TentativeThunder();		// 雷刃(仮)を実行
			break;
		case 32:
			/* +++ アクションナンバーが32 +++ */

			TentativePoison();		// 毒刃(仮)を実行
			break;
		case 33:
			/* +++ アクションナンバーが33 +++ */

			TentativeBreath();		// 無の息(仮)を実行
			break;
		case 34:
			/* +++ アクションナンバーが34 +++ */

			TentativeFinal();		// 最終撃(仮)を実行
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

void Noname::BattleFase_Draw()
{


	return;
}

void Noname::EndFase_Process()
{
	if (actionFlag == false)	// アクションフラグがfalseなら
	{
		TP_Calc(10, ISENHANCE);

		if (defenceCoefficient != 1)
		{
			defenceCoefficient = 1;
		}

		MyActionFlagTrue();
	}

	return;
}

void Noname::EndFase_Draw()
{


	return;
}

/* --- ダーク(仮) - 闇の魔力で攻撃し、たまに相手の魔法を封じる(MP: 10) --- */
void Noname::MagicTentativeDark()
{
	int calcResult;		// 計算結果の格納変数

	MP_Calc(MPofMagicTentativeDark, ISREDUCTION);	// MPを消費MP分減らす

	calcResult = (int)(Magic * 1.1);	// 魔力に補正をのせる

	settingMessagePattern = Message3Line;
	displayMessagePattern = Message3Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicTentativeDark);

		Enemy->Damage_Calc(calcResult, Magical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicTentativeDark);

		Player->Damage_Calc(calcResult, Magical);
	}

	/* +++ 沈黙の付与処理 +++ */
	/* +++ 沈黙の付与処理 +++ */

	Sound_Play(SE_MagicTentativeDark);

	return;
}

/* --- ライト(仮) - 光の魔力を放ち相手の物理攻撃の命中率を下げる(MP: 10) --- */
void Noname::MagicTentativeLight()
{
	int calcResult;		// 計算結果の格納変数

	MP_Calc(MPofMagicTentativeLight, ISREDUCTION);	// MPを消費MP分減らす

	calcResult = (int)(Magic * 1.1);	// 魔力に補正をのせる

	settingMessagePattern = Message3Line;
	displayMessagePattern = Message3Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicTentativeLight);

		Enemy->Damage_Calc(calcResult, Magical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicTentativeLight);

		Player->Damage_Calc(calcResult, Magical);
	}

	/* +++ 暗闇の付与処理 +++ */
	/* +++ 暗闇の付与処理 +++ */

	Sound_Play(SE_MagicTentativeLight);

	return;
}

/* --- ヒール(仮) - 魔法を唱えてダメージを回復する(MP: 10) --- */
void Noname::MagicTentativeHeal()
{
	int calcResult;		// 計算結果の格納変数

	MP_Calc(MPofMagicTentativeHeal, ISREDUCTION);	// MPを消費MP分減らす

	calcResult = (int)(Magic * 1.1);	// 魔力に補正をのせる

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message2Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicTentativeHeal);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicTentativeHeal);
	}

	HP_Calc(calcResult, ISHEAL);

	Sound_Play(SE_MagicTentativeHeal);

	return;
}

/* --- ロック(仮) - 大地から岩石を掘り出し投げつける(MP: 25) --- */
void Noname::MagicTentativeRock()
{
	int calcResult;		// 計算結果の格納変数

	MP_Calc(MPofMagicTentativeDark, ISREDUCTION);	// MPを消費MP分減らす

	calcResult = (int)(Magic * 2.5);	// 魔力に補正をのせる

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message2Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicTentativeRock);

		Enemy->Damage_Calc(calcResult, Magical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicTentativeRock);

		Player->Damage_Calc(calcResult, Magical);
	}

	Sound_Play(SE_MagicTentativeRock);

	return;
}

/* --- 雷刃(仮) - 雷の刃で攻撃し、たまに相手をマヒにする(TP: 15) --- */
void Noname::TentativeThunder()
{
	int calcResult;		// 計算結果の格納変数

	TP_Calc(TPofTentativeThunder, ISREDUCTION);	// TPを消費TP分減らす

	calcResult = (int)(Attack * 1.1);	// 攻撃力に補正をのせる

	settingMessagePattern = Message3Line;
	displayMessagePattern = Message3Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionTentativeThunder);

		Enemy->Damage_Calc(calcResult, Physical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionTentativeThunder);

		Player->Damage_Calc(calcResult, Physical);
	}

	/* +++ マヒの付与処理 +++ */
	/* +++ マヒの付与処理 +++ */

	Sound_Play(SE_TentativeThunder);

	return;
}

/* --- 毒刃(仮) - 毒の刃で攻撃し、相手を毒状態にする(TP: 15) --- */
void Noname::TentativePoison()
{
	int calcResult;		// 計算結果の格納変数

	TP_Calc(TPofTentativePoison, ISREDUCTION);	// TPを消費TP分減らす

	calcResult = (int)(Attack * 1.1);	// 攻撃力に補正をのせる

	settingMessagePattern = Message3Line;
	displayMessagePattern = Message3Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionTentativePoison);

		Enemy->Damage_Calc(calcResult, Physical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionTentativePoison);

		Player->Damage_Calc(calcResult, Physical);
	}

	/* +++ 毒の付与処理 +++ */
	/* +++ 毒の付与処理 +++ */

	Sound_Play(SE_TentativePoison);

	return;
}

/* --- 構え(仮) - 使うほどに守備力が上がる(TP: 25) --- */
void Noname::TentativeStance()
{
	int calcResult;		// 計算結果の格納変数

	TP_Calc(TPofTentativeBreath, ISREDUCTION);	// TPを消費TP分減らす

	calcResult = (int)( * );	// 攻撃力に補正をのせる

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message2Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionTentativeBreath);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionTentativeBreath);
	}

	Sound_Play(SE_TentativeStance);

	return;
}

/* --- 痛打(仮) - 当たれば致命の攻撃(TP: 40) --- */
void Noname::TentativeSevereBlow()
{
	int calcResult;		// 計算結果の格納変数

	TP_Calc(TPofTentativeFinal, ISREDUCTION);	// TPを消費TP分減らす

	calcResult = (int)(Attack * 3.0);	// 攻撃力に補正をのせる

	settingMessagePattern = Message4Line;
	displayMessagePattern = Message4Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionTentativeFinal);

		Enemy->Damage_Calc(calcResult, Physical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionTentativeFinal);

		Player->Damage_Calc(calcResult, Physical);
	}

	Sound_Play(SE_TentativeFinal);

	return;
}