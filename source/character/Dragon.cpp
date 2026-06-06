/* === ドラゴンキャラクター関連のソースファイル ===*/

#include <string.h>
#include "Dragon.h"
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


Dragon PlDragon, EnDragon;		// ドラゴンクラスの変数

/* +++ ドラゴンクラスのオーバーライド +++ */
void Dragon::Character_Init(bool isThisPlayer)
{
	/* +++ 各種パラメータを設定 +++ */
	MaxHP			= DragonHP;
	MaxMP			= DragonMP;
	OriginAttack	= DragonAttack;
	OriginDefence	= DragonDefence;
	OriginMagic		= DragonMagic;
	OriginPrevent	= DragonPrevent;
	OriginSpeed		= DragonSpeed;

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
	randomDebuffNumber = 0;
	attackPreemptive = false;
	defencePreemptive = false;

	defenceCoefficient = 1.0;		// 防御係数を初期化

	statusAilment = Fine;		// 状態を「異常なし」に設定
	ailmentTurn = 0;			// 状態異常の継続ターンを0にする
	ailmentPoisoning = false;	// 「毒」の状態異常を解除

	sprintf_s(characterName, sizeof(characterName),"%s", CharacterNameDragon);

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

void Dragon::MainFase_Process()
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

					// ピラーの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicPillar);
				}
				else if (actionNumber == 30)
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 呪いの息の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfCurseBreath);
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
						if (MP >= MPofMagicPillar)	// MPがピラーの消費MP以上なら
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
						if (TP >= TPofCurseBreath)	// TPが呪いの息の消費TP以上なら
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

					// ファングの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicFung);
				}
				else if (actionNumber == 30)
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 竜仙鱗の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfImmortalScale);
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
						if (MP >= MPofMagicFung)		// MPがファングの消費MP以上なら
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
						if (TP >= TPofImmortalScale)	// TPが竜仙鱗の消費TP以上なら
						{
							Sound_Play(SE_Enter);

							actionNumber += 2;		// アクションナンバーに2を加算する

							MyDefencePreemptiveTrue();	// 自身の先制防御フラグをtrueにする

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

					if (MaxHP > HP)
					{
						// リカバーの説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicRecover);
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

					// 破壊の息の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfDestructBreath);
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
						if (MP >= MPofMagicRecover)		// MPがリカバーの消費MP以上なら
						{
							if (MaxHP > HP)
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
						if (TP >= TPofDestructBreath)	// TPが破壊の息の消費TP以上なら
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
				else if (actionNumber == 30)	// アクションナンバーが30なら
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					if (MaxMP > MP)
					{
						// 大気吸収の説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfAbsorbAtmosphere);
					}
					else
					{
						// 使用不可の説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailUnavilableMaxMP);
					}
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
					else if (actionNumber == 30)	// アクションナンバーが30なら
					{
						if (TP >= TPofAbsorbAtmosphere)		// TPが大気吸収の消費TP以上なら
						{
							if (MaxMP > MP)
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

					if (MP < MPofMagicPillar)		// MPがピラーの消費MP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 2:
					/* +++ 乱数の値が2 +++ */

					if (MP < MPofMagicFung)		// MPがファングの消費MP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 3:
					/* +++ 乱数の値が3 +++ */

					if (HP >= MaxHP || MP < MPofMagicRecover)	// MPがリカバーの消費MP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 4:
					/* +++ 乱数の値が4 +++ */

					actionNumber = 0;	// アクションナンバーをリセットする

					return;		// 処理を終了

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

					if (TP < TPofCurseBreath)	// TPが呪いの息の消費TP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 2:
					/* +++ 乱数の値が2 +++ */

					if (TP < TPofImmortalScale)		// TPが竜仙鱗の消費TP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					else
					{
						MyDefencePreemptiveTrue();	// 自身の先制防御フラグをtrueにする
					}
					break;
				case 3:
					/* +++ 乱数の値が3 +++ */

					if (TP < TPofDestructBreath)	// TPが破壊の息の消費TP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 4:
					/* +++ 乱数の値が4 +++ */

					if (MP >= MaxMP || TP < TPofAbsorbAtmosphere)	// TPが大気吸収の消費TP未満なら
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

void Dragon::MainFase_Draw()
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
			if (MP < MPofMagicPillar)
			{
				/* +++ 3つの選択肢のボタンを灰色枠で描画 +++ */
				DrawRect(optionButton1, Color_Gray, false, 3);
				DrawRect(optionButton2, Color_Gray, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);

				/* +++ 魔法の選択肢のテキストを灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicPillar);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicFung);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicRecover);
			}
			else if (MP < MPofMagicFung)
			{
				/* +++ 2つの選択肢のボタンを灰枠で描画 +++ */
				DrawRect(optionButton2, Color_Gray, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);

				/* +++ 魔法の選択肢のテキストを灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicFung);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicRecover);

				/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicPillar);
				}
				else
				{
					DrawRect(optionButton1, Color_White, false, 3);		// 選択肢1ボタンを白枠で描画

					// 選択肢1のテキストを白で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicPillar);
				}
			}
			else
			{
				if (MaxHP > HP)
				{
					/* +++ 3つの選択肢のボタンを白枠で描画 +++ */
					DrawRect(optionButton1, Color_White, false, 3);
					DrawRect(optionButton2, Color_White, false, 3);
					DrawRect(optionButton3, Color_White, false, 3);

					/* +++ 魔法の選択肢のテキストを白で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicPillar);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicFung);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicRecover);

					/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicPillar);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicFung);
					}
					else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicRecover);
					}
				}
				else
				{
					/* +++ 3つの選択肢のボタンを白または灰枠で描画 +++ */
					DrawRect(optionButton1, Color_White, false, 3);
					DrawRect(optionButton2, Color_White, false, 3);
					DrawRect(optionButton3, Color_Gray, false, 3);

					/* +++ 魔法の選択肢のテキストを白または灰で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicPillar);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicFung);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicRecover);

					/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicPillar);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicFung);
					}
				}
			}

			DrawBackBottun();
		}
		else if (actionNumber == 30)	// アクションナンバーが30である
		{
			if (TP < TPofCurseBreath)
			{
				/* +++ 4つの選択肢のボタンを灰枠で描画 +++ */
				DrawRect(optionButton1, Color_Gray, false, 3);
				DrawRect(optionButton2, Color_Gray, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionCurseBreath);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionImmortalScale);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionDestructBreath);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionAbsorbAtmosphere);
			}
			else if (TP < TPofImmortalScale)
			{
				/* +++ 3つの選択肢のボタンを灰枠で描画 +++ */
				DrawRect(optionButton2, Color_Gray, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionImmortalScale);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionDestructBreath);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionAbsorbAtmosphere);

				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionCurseBreath);
				}
				else
				{
					DrawRect(optionButton1, Color_White, false, 3);		// 選択肢1ボタンを白枠で描画

					// 選択肢1のテキストを白で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionCurseBreath);
				}
			}
			else if (TP < TPofDestructBreath)
			{
				/* +++ 4つの選択肢のボタンを白または灰枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_White, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを白または灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionCurseBreath);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionImmortalScale);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionDestructBreath);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionAbsorbAtmosphere);

				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionCurseBreath);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionImmortalScale);
				}
			}
			else if (TP < TPofAbsorbAtmosphere)
			{
				/* +++ 4つの選択肢のボタンを白または灰枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_White, false, 3);
				DrawRect(optionButton3, Color_White, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを白または灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionCurseBreath);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionImmortalScale);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionDestructBreath);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionAbsorbAtmosphere);

				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionCurseBreath);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionImmortalScale);
				}
				else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

					// 選択肢3のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionDestructBreath);
				}
			}
			else
			{
				if (MaxMP > MP)
				{
					/* +++ 4つの選択肢のボタンを白枠で描画 +++ */
					DrawRect(optionButton1, Color_White, false, 3);
					DrawRect(optionButton2, Color_White, false, 3);
					DrawRect(optionButton3, Color_White, false, 3);
					DrawRect(optionButton4, Color_White, false, 3);

					/* +++ 特技の選択肢のテキストを白で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionCurseBreath);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionImmortalScale);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionDestructBreath);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionAbsorbAtmosphere);

					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionCurseBreath);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionImmortalScale);
					}
					else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionDestructBreath);
					}
					else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton4, Color_White, true, 3);		// 選択肢4ボタンを白で塗りつぶして描画

						// 選択肢4のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionAbsorbAtmosphere);
					}
				}
				else
				{
					/* +++ 4つの選択肢のボタンを白または灰枠で描画 +++ */
					DrawRect(optionButton1, Color_White, false, 3);
					DrawRect(optionButton2, Color_White, false, 3);
					DrawRect(optionButton3, Color_White, false, 3);
					DrawRect(optionButton4, Color_Gray, false, 3);

					/* +++ 特技の選択肢のテキストを白または灰色で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionCurseBreath);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionImmortalScale);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionDestructBreath);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionAbsorbAtmosphere);

					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionCurseBreath);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionImmortalScale);
					}
					else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionDestructBreath);
					}
				}
			}

			DrawBackBottun();
		}
	}

	return;
}


void Dragon::BattleFase_Process()
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

			MagicPillar();	// ピラーを実行
			break;
		case 22:
			/* +++ アクションナンバーが22 +++ */

			MagicFung();	// ファングを実行
			break;
		case 23:
			/* +++ アクションナンバーが23 +++ */

			MagicRecover();		// リカバーを実行
			break;
		case 31:
			/* +++ アクションナンバーが31 +++ */

			CurseBreath();		// 呪いの息を実行
			break;
		case 32:
			/* +++ アクションナンバーが32 +++ */

			ImmortalScale();	// 竜仙鱗を実行
			break;
		case 33:
			/* +++ アクションナンバーが33 +++ */

			DestructBreath();	// 破壊の息を実行
			break;
		case 34:
			/* +++ アクションナンバーが34 +++ */

			AbsorbAtmosphere();		// 大気吸収を実行
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

void Dragon::BattleFase_Draw()
{


	return;
}

void Dragon::EndFase_Process()
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

void Dragon::EndFase_Draw()
{


	return;
}

/* --- ピラー - 魔力参照の魔法攻撃(MP:15) --- */
void Dragon::MagicPillar()
{
	int calcResult;		// 計算結果の格納変数

	MP_Calc(MPofMagicPillar, ISREDUCTION);	// MPを消費MP分減らす

	calcResult = (int)(Magic * 2);	// 魔力に補正を乗せる

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message1Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicPillar);

		Enemy->Damage_Calc(calcResult, Magical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicPillar);

		Player->Damage_Calc(calcResult, Magical);
	}

	Sound_Play(SE_MagicPillar);

	return;
}

/* --- ファング - 魔力参照の物理攻撃(MP:20) --- */
void Dragon::MagicFung()
{
	int calcResult;		// 計算結果を格納する変数

	MP_Calc(MPofMagicFung, ISREDUCTION);	// MPを消費MP分減らす

	calcResult = (int)(Magic * 2);	// 魔力に補正を乗せる

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message1Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicFung);

		Enemy->Damage_Calc(calcResult, Physical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicFung);

		Player->Damage_Calc(calcResult, Physical);
	}

	Sound_Play(SE_MagicFung);

	return;
}

/* --- リカバー - 魔力参照の回復魔法(MP:20) --- */
void Dragon::MagicRecover()
{
	int calcResult;		// 計算結果を格納する変数

	MP_Calc(MPofMagicRecover, ISREDUCTION);		// MPを消費MP分減らす

	calcResult = (int)(Magic * 1.5);	// 魔力に補正を乗せる

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message1Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicRecover);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicRecover);
	}

	HP_Calc(calcResult, ISHEAL);

	Sound_Play(SE_MagicRecover);

	return;
}

/* --- 呪いの息 - 魔力参照のブレス攻撃、相手のステータスをランダムに下げる(TP:15) --- */
void Dragon::CurseBreath()
{
	int calcResult;		// 計算結果を格納する変数

	TP_Calc(TPofCurseBreath, ISREDUCTION);	// TPを消費TP分減らす

	calcResult = (int)(Attack * 1.1);	// 攻撃力に補正を乗せる

	randomDebuffNumber = GetRand(4) + 1;	// 1～5の乱数を発生させる

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message1Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionCurseBreath);

		Enemy->Damage_Calc(calcResult, Breath);

		switch (randomDebuffNumber)
		{
		case 1:

			Enemy->Attack_Calc(30, ISREDUCTION);
			break;
		case 2:

			Enemy->Defence_Calc(30, ISREDUCTION);
			break;
		case 3:

			Enemy->Magic_Calc(30, ISREDUCTION);
			break;
		case 4:

			Enemy->Prevent_Calc(30, ISREDUCTION);
			break;
		case 5:

			Enemy->Speed_Calc(30, ISREDUCTION);
			break;
		default:
			break;
		}
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionCurseBreath);

		Player->Damage_Calc(calcResult, Breath);

		switch (randomDebuffNumber)
		{
		case 1:

			Player->Attack_Calc(30, ISREDUCTION);
			break;
		case 2:

			Player->Defence_Calc(30, ISREDUCTION);
			break;
		case 3:

			Player->Magic_Calc(30, ISREDUCTION);
			break;
		case 4:

			Player->Prevent_Calc(30, ISREDUCTION);
			break;
		case 5:

			Player->Speed_Calc(30, ISREDUCTION);
			break;
		default:
			break;
		}
	}

	Sound_Play(SE_CurseBreath);

	return;
}

/* --- 竜仙鱗 - 発動したターンに受けるダメージを90 % カットする(TP:20) --- */
void Dragon::ImmortalScale()
{
	TP_Calc(TPofImmortalScale, ISREDUCTION);	// TPを消費TP分減らす

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message1Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionImmortalScale);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionImmortalScale);
	}

	defenceCoefficient = 0.1;	// 防御係数を0.1にする

	/* +++ 状態異常無効の付与処理 +++ */
	/* +++ 状態異常無効の付与処理 +++ */

	Sound_Play(SE_ImmortalScale);

	return;
}

/* --- 破壊の息 - 攻撃力参照のブレス攻撃(TP:25) --- */
void Dragon::DestructBreath()
{
	int calcResult;		// 計算結果を格納する変数

	TP_Calc(TPofDestructBreath, ISREDUCTION);	// TPを消費TP分減らす

	calcResult = (int)(Attack * 2.0);	// 攻撃力に補正を乗せる

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message1Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionDestructBreath);

		Enemy->Damage_Calc(calcResult, Breath);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionDestructBreath);

		Player->Damage_Calc(calcResult, Breath);
	}

	Sound_Play(SE_DestructBreath);

	return;
}

/* --- 大気吸収 - 自身のMPとTPを回復する(TP:40) --- */
void Dragon::AbsorbAtmosphere()
{
	TP_Calc(TPofAbsorbAtmosphere, ISREDUCTION);		// TPを消費TP分減らす

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message1Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionAbsorbAtmosphere);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionAbsorbAtmosphere);
	}

	MP_Calc(30, ISENHANCE);		// MPを30回復する
	TP_Calc(30, ISENHANCE);		// TPを30回復する

	Sound_Play(SE_AbsorbAtmosphere);

	return;
}