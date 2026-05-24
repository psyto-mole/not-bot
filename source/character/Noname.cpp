/* === 「名無し」関連のソースファイル === */

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

Noname PlNoname, EnNoname;			// 「名無し」クラスの変数

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

					// の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicFire);
				}
				else if (actionNumber == 30)
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 精神統一の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfTPCharge);
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
						if (MP >= MPofMagicFire)	// MPがファイアの消費MP以上なら
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
						if (TP >= TPofTPCharge)	// TPが精神統一の消費TP以上なら
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
					displayMessagePattern = Message2Line;	// 表示するメッセージを2行に設定

					// サンダーの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicThunder1);
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s", DetailOfMagicThunder2);
				}
				else if (actionNumber == 30)
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 全霊斬りの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfAllHeartSoul);
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
						if (MP >= MPofMagicThunder)		// MPがサンダーの消費MP以上なら
						{
							Sound_Play(SE_Enter);

							actionNumber += 2;		// アクションナンバーに2を加える

							MyAttackPreemptiveTrue();	// 先制攻撃フラグをtrueにする

							MyActionFlagTrue();		// アクションフラグをtrueにする
						}
						else
						{
							Sound_Play(SE_Unavilable);
						}
					}
					else if (actionNumber == 30)		// アクションナンバーが30なら
					{
						if (TP >= TPofAllHeartSoul)		// TPが全霊斬りの消費TP以上なら
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

					// アイスの説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicIce);
				}
				else if (actionNumber == 30)
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					if (MaxMP > MP)
					{
						// 魔力補給の説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMPCharge);
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

						actionNumber = 30;	// アクションナンバーに30を代入
					}
					else if (actionNumber == 20)	// アクションナンバーが20なら
					{
						if (MP >= MPofMagicIce)		// MPがアイスの消費MP以上なら
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
						if (TP >= TPofMPCharge)		// TPが魔力補給の消費TP以上なら
						{
							if (MaxMP > MP)		// MPが減少していれば
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

					if (MaxHP > HP)
					{
						// ヒールの説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicHeal);
					}
					else
					{
						// 使用不可の説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailUnavilableMaxHP);
					}
				}
				else if (actionNumber == 30)		// アクションナンバーが30なら
				{
					displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

					// 気合の説明文をメッセージに設定
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfGatherEnergy);
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
						if (MP >= MPofMagicHeal)		// MPがヒールの消費MP以上なら
						{
							if (HP != MaxHP)	// 現在のHPが最大HPと異なるなら
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
						else
						{
							Sound_Play(SE_Unavilable);
						}
					}
					else if (actionNumber == 30)	// アクションナンバーが30なら
					{
						if (TP >= TPofGatherEnergy)	// TPが気合の消費TP以上なら
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

					if (MP < MPofMagicFire)	// MPがファイアの消費MP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 2:
					/* +++ 乱数の値が2 +++ */

					if (MP < MPofMagicThunder)	// MPがサンダーの消費MP未満なら
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

					if (MP < MPofMagicIce)	// MPがアイスの消費MP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 4:
					/* +++ 乱数の値が4 +++ */

					if (HP >= MaxHP || MP < MPofMagicHeal)	// MPがヒールの消費MP未満なら
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

					if (TP < TPofTPCharge)	// TPが精神統一の消費TP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 2:
					/* +++ 乱数の値が2 +++ */

					if (TP < TPofAllHeartSoul)	// TPが全霊斬りの消費TP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 3:
					/* +++ 乱数の値が3 +++ */

					if (MP >= MaxMP || TP < TPofMPCharge)	// TPが魔力補給の消費TP未満なら
					{
						actionNumber = 0;	// アクションナンバーをリセットする

						return;		// 処理を終了
					}
					break;
				case 4:
					/* +++ 乱数の値が4 +++ */

					if (TP < TPofGatherEnergy)	// TPが気合の消費TP未満なら
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

void Human::MainFase_Draw()
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
			if (MP < MPofMagicFire)
			{
				/* +++ 4つの選択肢のボタンを灰色枠で描画 +++ */
				DrawRect(optionButton1, Color_Gray, false, 3);
				DrawRect(optionButton2, Color_Gray, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 魔法の選択肢のテキストを灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicFire);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicThunder);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicIce);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicHeal);
			}
			else if (MP < MPofMagicIce)
			{
				/* +++ 4つの選択肢のボタンを白または灰色枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_White, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを白または灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicFire);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicThunder);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicIce);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicHeal);

				/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicFire);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicThunder);
				}
			}
			else
			{
				if (MaxHP > HP)
				{
					/* +++ 4つの選択肢のボタンを白枠で描画 +++ */
					DrawRect(optionButton1, Color_White, false, 3);
					DrawRect(optionButton2, Color_White, false, 3);
					DrawRect(optionButton3, Color_White, false, 3);
					DrawRect(optionButton4, Color_White, false, 3);

					/* +++ 特技の選択肢のテキストを白で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicFire);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicThunder);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicIce);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicHeal);

					/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicFire);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicThunder);
					}
					else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicIce);
					}
					else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton4, Color_White, true, 3);		// 選択肢4ボタンを白で塗りつぶして描画

						// 選択肢4のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicHeal);
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
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicFire);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicThunder);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicIce);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicHeal);

					/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicFire);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicThunder);
					}
					else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicIce);
					}
				}
			}

			DrawBackBottun();
		}
		else if (actionNumber == 30)	// アクションナンバーが30である
		{
			if (TP < TPofAllHeartSoul)
			{
				/* +++ 3つの選択肢のボタンを白または灰色枠で描画 +++ */
				DrawRect(optionButton2, Color_Gray, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionAllHeartSoul);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMPCharge);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionGatherEnergy);

				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTPCharge);
				}
				else
				{
					DrawRect(optionButton1, Color_White, false, 3);		// 選択肢1ボタンを白枠で描画

					// 選択肢1のテキストを白で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTPCharge);
				}
			}
			else if (TP < TPofMPCharge)
			{
				/* +++ 4つの選択肢のボタン白または灰色枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_White, false, 3);
				DrawRect(optionButton3, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_Gray, false, 3);

				/* +++ 特技の選択肢のテキストを白または灰色で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTPCharge);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionAllHeartSoul);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMPCharge);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionGatherEnergy);

				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTPCharge);
				}
				else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

					// 選択肢2のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionAllHeartSoul);
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
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTPCharge);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionAllHeartSoul);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMPCharge);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionGatherEnergy);

					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTPCharge);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionAllHeartSoul);
					}
					else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMPCharge);
					}
					else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton4, Color_White, true, 3);		// 選択肢4ボタンを白で塗りつぶして描画

						// 選択肢4のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionGatherEnergy);
					}
				}
				else
				{
					/* +++ 4つの選択肢のボタンを白または灰枠で描画 +++ */
					DrawRect(optionButton1, Color_White, false, 3);
					DrawRect(optionButton2, Color_White, false, 3);
					DrawRect(optionButton3, Color_Gray, false, 3);
					DrawRect(optionButton4, Color_White, false, 3);

					/* +++ 特技の選択肢のテキストを白または灰で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTPCharge);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionAllHeartSoul);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMPCharge);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionGatherEnergy);

					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTPCharge);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionAllHeartSoul);
					}
					else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton4, Color_White, true, 3);		// 選択肢4ボタンを白で塗りつぶして描画

						// 選択肢4のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionGatherEnergy);
					}
				}
			}

			DrawBackBottun();
		}
	}

	return;
}


void Human::BattleFase_Process()
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

			MagicFire();	// ファイアを実行
			break;
		case 22:
			/* +++ アクションナンバーが22 +++ */

			MagicThunder();		// サンダーを実行
			break;
		case 23:
			/* +++ アクションナンバーが23 +++ */

			MagicIce();		// アイスを実行
			break;
		case 24:
			/* +++ アクションナンバーが24 +++ */

			MagicHeal();	// ヒールを実行
			break;
		case 31:
			/* +++ アクションナンバーが31 +++ */

			TPCharge();		// 精神統一を実行
			break;
		case 32:
			/* +++ アクションナンバーが32 +++ */

			AllHeartSoul();		// 全霊斬りを実行
			break;
		case 33:
			/* +++ アクションナンバーが33 +++ */

			MPCharge();		// 魔力補給を実行
			break;
		case 34:
			/* +++ アクションナンバーが34 +++ */

			GatherEnergy();		// 気合を実行
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

	MP_Calc(TPofTentativeThunder, ISREDUCTION);	// TPを消費TP分減らす

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

	MP_Calc(TPofTentativePoison, ISREDUCTION);	// TPを消費TP分減らす

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

/* --- 無の息(仮) - ブレスで攻撃(TP: 25) --- */
void Noname::TentativeBreath()
{
	int calcResult;		// 計算結果の格納変数

	MP_Calc(TPofTentativeBreath, ISREDUCTION);	// TPを消費TP分減らす

	calcResult = (int)(Attack * 2.0);	// 攻撃力に補正をのせる

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message2Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionTentativeBreath);

		Enemy->Damage_Calc(calcResult, Breath);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionTentativeBreath);

		Player->Damage_Calc(calcResult, Breath);
	}

	Sound_Play(SE_TentativeBreath);

	return;
}

/* --- 最終撃(仮) - 守りを犠牲に攻撃する(TP: 40) --- */
void Noname::TentativeFinal()
{
	int calcResult;		// 計算結果の格納変数

	MP_Calc(TPofTentativeFinal, ISREDUCTION);	// TPを消費TP分減らす

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

	Defence_Calc(30, ISREDUCTION);
	Prevent_Calc(30, ISREDUCTION);

	Sound_Play(SE_TentativeFinal);

	return;
}