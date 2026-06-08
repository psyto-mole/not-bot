/* === ダイトメア関連のソースファイル === */

#include <string.h>
#include "Dightmare.h"
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

Dightmare PlDightmare, EnDightmare;			// ダイトメアクラスの変数

/* +++ 人間クラスのオーバーライド +++ */
void Dightmare::Character_Init(bool isThisPlayer)
{
	/* +++ 最大HPと最大MP、元々のステータスを設定 +++ */
	MaxHP = DightmareHP;
	MaxMP = DightmareMP;
	OriginAttack = DightmareAttack;
	OriginDefence = DightmareDefence;
	OriginMagic = DightmareMagic;
	OriginPrevent = DightmarePrevent;
	OriginSpeed = DightmareSpeed;

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

	chargeStep = 0;

	statusAilment = Fine;		// 状態を「異常なし」に設定
	ailmentTurn = 0;			// 状態異常の継続ターンを0にする
	ailmentPoisoning = false;	// 「毒」の状態異常を解除

	sprintf_s(characterName, sizeof(characterName), "%s", CharacterNameDightmare);

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
void Dightmare::MainFase_Process()
{
	if (actionFlag)		// 行動済みなら(アクションフラグがtrueなら)
	{
		return;		// 何もせずに終了する
	}
	else if (statusAilment == Paralysis)	// 「マヒ」なら
	{
		MyActionFlagTrue();		// アクションフラグをtrueにする
		actionNumber = 0;		// アクションナンバーをリセット

		return;
	}
	else	// 行動済みでないなら
	{
		if (isPlayer)	// プレイヤーキャラなら
		{
			if (chargeStep == 1)	// 技がチャージされているなら
			{
				actionNumber = 21;
				MyActionFlagTrue();

				return;
			}
			else
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

						// サロスの説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicSaros);
					}
					else if (actionNumber == 30)
					{
						displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

						// イムセトの説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfImseti);
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
							if (MP >= MPofMagicSaros)	// MPがサロスの消費MP以上なら
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
							if (TP >= TPofImseti)	// TPがの消費TP以上なら
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

						if (statusAilment == Silence)
						{
							// 魔法が封じれれている旨をメッセージに設定
							sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailSealedMagic);
						}
						else
						{
							// 魔法の説明文をメッセージに設定
							sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagic);
						}
					}
					else if (actionNumber == 20)
					{
						displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

						if (MaxHP > DightmareHP)
						{
							// 使用不可の説明文をメッセージに設定
							sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailUnavilableNever);
						}
						else
						{
							// デウスの説明文をメッセージに設定
							sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicDeus);
						}
					}
					else if (actionNumber == 30)
					{
						displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

						// ハーピの説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfHarpy);
					}

					if (Mouse_Check_Click(MOUSE_INPUT_LEFT))	// マウスがクリックされた
					{
						if (actionNumber < 10)	// アクションナンバーが10未満なら
						{
							if (statusAilment == Silence)
							{
								Sound_Play(SE_Unavilable);
							}
							else
							{
								Sound_Play(SE_Enter);

								actionNumber = 20;	// アクションナンバーに20を代入する
							}
						}
						else if (actionNumber == 20)		// アクションナンバーが20なら
						{
							if (MP >= MPofMagicDeus)		// MPがデウスの消費MP以上なら
							{
								if (MaxHP > DightmareHP)
								{
									Sound_Play(SE_Unavilable);
								}
								else
								{
									Sound_Play(SE_Enter);

									actionNumber += 2;		// アクションナンバーに2を加える

									MyActionFlagTrue();		// アクションフラグをtrueにする
								}
							}
							else
							{
								Sound_Play(SE_Unavilable);
							}
						}
						else if (actionNumber == 30)		// アクションナンバーが30なら
						{
							if (TP >= TPofHarpy)		// TPがハーピの消費TP以上なら
							{
								Sound_Play(SE_Enter);	// 決定時のSEを再生

								actionNumber += 2;			// アクションナンバーに2を加算する

								MyActionFlagTrue();			// アクションフラグをtrueにする
								MyAttackPreemptiveTrue();	// 先制攻撃フラグをtrueにする
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

						if (statusAilment == Slump)
						{
							// 特技が封じれれている旨をメッセージに設定
							sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailSealedSpecial);
						}
						else
						{
							// 特技の説明文をメッセージに設定
							sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfSpecial);
						}
					}
					else if (actionNumber == 20)		// アクションナンバーが20なら
					{
						displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

						// エクスの説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicEx);
					}
					else if (actionNumber == 30)
					{
						displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

						// ケベフスの説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfKebehsenuev);
					}

					if (Mouse_Check_Click(MOUSE_INPUT_LEFT))	// マウスがクリックされた
					{
						if (actionNumber < 10)	// アクションナンバーが10未満なら
						{
							if (statusAilment == Slump)
							{
								Sound_Play(SE_Unavilable);
							}
							else
							{
								Sound_Play(SE_Enter);

								actionNumber = 30;	// アクションナンバーに30を代入
							}
						}
						else if (actionNumber == 20)	// アクションナンバーが20なら
						{
							if (MP >= MPofMagicEx)		// MPがエクスの消費MP以上なら
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
							if (TP >= TPofKebehsenuev)		// TPがケベフスの消費TP以上なら
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

						// マキナの説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicMachina);
					}
					else if (actionNumber == 30)		// アクションナンバーが30なら
					{
						displayMessagePattern = Message1Line;	// 表示するメッセージを1行に設定

						// ドゥアムタの説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfDuamtef);
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
							if (MP >= MPofMagicMachina)		// MPがマキナの消費MP以上なら
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
							if (TP >= TPofDuamtef)	// TPがドゥアムタの消費TP以上なら
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
		}
		else	// 敵キャラなら
		{
			if (chargeStep == 1)
			{
				actionNumber = 21;
				MyActionFlagTrue();
			}
			else
			{
				randomNumber = GetRand(3) + 1;	// 1～4の乱数を生成

				/* +++ アクションナンバーと乱数の値によって処理を変更 +++ */
				if (actionNumber < 10)		// アクションナンバーが10未満
				{
					if (statusAilment == Silence)	// 「沈黙」状態なら
					{
						if (actionNumber != 2)	// アクションナンバーが2でないなら
						{
							actionNumber = randomNumber * 10;	// アクションナンバーに乱数の10倍を代入
						}
					}
					else if (statusAilment == Slump)	// 「不調」状態なら
					{
						if (actionNumber != 3)	// アクションナンバーが3でないなら
						{
							actionNumber = randomNumber * 10;	// アクションナンバーに乱数の10倍を代入
						}
					}
					else
					{
						actionNumber = randomNumber * 10;	// アクションナンバーに乱数の10倍を代入
					}
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

						if (MP < MPofMagicSaros)	// MPがサロスの消費MP未満なら
						{
							actionNumber = 0;	// アクションナンバーをリセットする

							return;		// 処理を終了
						}
						break;
					case 2:
						/* +++ 乱数の値が2 +++ */

						if (MP < MPofMagicDeus || MaxHP > DightmareHP)	// MPがデウスの消費MP未満または使用済みなら
						{
							actionNumber = 0;	// アクションナンバーをリセットする

							return;		// 処理を終了
						}
						break;
					case 3:
						/* +++ 乱数の値が3 +++ */

						if (MP < MPofMagicEx)	// MPがエクスの消費MP未満なら
						{
							actionNumber = 0;	// アクションナンバーをリセットする

							return;		// 処理を終了
						}
						break;
					case 4:
						/* +++ 乱数の値が4 +++ */

						if (MP < MPofMagicMachina)	// MPがマキナの消費MP未満なら
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

						if (TP < TPofImseti)	// TPがイムセトの消費TP未満なら
						{
							actionNumber = 0;	// アクションナンバーをリセットする

							return;		// 処理を終了
						}
						break;
					case 2:
						/* +++ 乱数の値が2 +++ */

						if (TP < TPofHarpy)	// TPがの消費TP未満なら
						{
							actionNumber = 0;	// アクションナンバーをリセットする

							return;		// 処理を終了
						}
						else
						{
							MyAttackPreemptiveTrue();
						}

						break;
					case 3:
						/* +++ 乱数の値が3 +++ */

						if (TP < TPofKebehsenuev)	// TPがケベフスの消費TP未満なら
						{
							actionNumber = 0;	// アクションナンバーをリセットする

							return;		// 処理を終了
						}
						break;
					case 4:
						/* +++ 乱数の値が4 +++ */

						if (TP < TPofDuamtef)	// TPがドゥアムタの消費TP未満なら
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
	}

	return;
}

void Dightmare::MainFase_Draw()
{
	if (isPlayer)	// プレイヤーキャラなら
	{
		if (statusAilment != Paralysis)
		{
			if (actionNumber < 10)	// アクションナンバーが10未満なら
			{
				/* +++ 選択肢1と4のボタンを白枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton4, Color_White, false, 3);

				/* +++ 選択肢1と4のテキストを白で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionAttack);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionDefence);

				/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
				if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

					// 選択肢1のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionAttack);
				}
				else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
				{
					DrawRect(optionButton4, Color_White, true, 3);		// 選択肢4ボタンを白で塗りつぶして描画

					// 選択肢4のテキストを黒で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionDefence);
				}

				if (statusAilment == Silence)
				{
					DrawRect(optionButton2, Color_Gray, false, 3);	// 選択肢2のボタンを灰枠で描画

					// 選択肢2のテキストを灰色で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagic);

					if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionSpecial);
					}
					else
					{
						DrawRect(optionButton3, Color_White, false, 3);		// 選択肢3ボタンを白で描画

						// 選択肢3のテキストを白で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionSpecial);
					}
				}
				else if (statusAilment == Slump)
				{
					DrawRect(optionButton3, Color_Gray, false, 3);	// 選択肢3のボタンを灰枠で描画

					// 選択肢3のテキストを灰色で描画
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionSpecial);

					if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagic);
					}
					else
					{
						DrawRect(optionButton2, Color_White, false, 3);		// 選択肢2ボタンを白で描画

						// 選択肢2のテキストを白で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagic);
					}
				}
				else
				{
					/* +++ 選択肢2と3のボタンを白枠で描画 +++ */
					DrawRect(optionButton2, Color_White, false, 3);
					DrawRect(optionButton3, Color_White, false, 3);

					/* +++ 選択肢2と3のテキストを白で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagic);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionSpecial);

					/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
					if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2ボタンとマウスカーソルが接触している
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
				}
			}
			else if (actionNumber == 20)
			{
				if (MP < MPofMagicSaros)
				{
					/* +++ 4つの選択肢のボタンを灰色枠で描画 +++ */
					DrawRect(optionButton1, Color_Gray, false, 3);
					DrawRect(optionButton2, Color_Gray, false, 3);
					DrawRect(optionButton3, Color_Gray, false, 3);
					DrawRect(optionButton4, Color_Gray, false, 3);

					/* +++ 魔法の選択肢のテキストを灰色で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicSaros);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicDeus);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicEx);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicMachina);
				}
				else if (MP < MPofMagicDeus)
				{
					/* +++ 3つの選択肢のボタンを白または灰色枠で描画 +++ */
					DrawRect(optionButton2, Color_Gray, false, 3);
					DrawRect(optionButton3, Color_Gray, false, 3);
					DrawRect(optionButton4, Color_Gray, false, 3);

					/* +++ 魔法の選択肢のテキストを白または灰色で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicDeus);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicEx);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicMachina);

					/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicSaros);
					}
					else
					{
						DrawRect(optionButton1, Color_White, false, 3);		// 選択肢1ボタンを白で描画

						// 選択肢1のテキストを白で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicSaros);
					}
				}
				else if (MP < MPofMagicEx)
				{
					if (MaxHP > DightmareHP)
					{
						/* +++ 4つの選択肢のボタンを白枠または灰枠で描画 +++ */
						DrawRect(optionButton1, Color_White, false, 3);
						DrawRect(optionButton2, Color_Gray, false, 3);
						DrawRect(optionButton3, Color_Gray, false, 3);
						DrawRect(optionButton4, Color_Gray, false, 3);

						/* +++ 魔法の選択肢のテキストを白または灰で描画 +++ */
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicSaros);
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicDeus);
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicEx);
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicMachina);

						/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
						if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
						{
							DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

							// 選択肢1のテキストを黒で描画
							DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicSaros);
						}
					}
					else
					{
						/* +++ 4つの選択肢のボタンを白枠または灰枠で描画 +++ */
						DrawRect(optionButton1, Color_White, false, 3);
						DrawRect(optionButton2, Color_White, false, 3);
						DrawRect(optionButton3, Color_Gray, false, 3);
						DrawRect(optionButton4, Color_Gray, false, 3);

						/* +++ 魔法の選択肢のテキストを白または灰で描画 +++ */
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicSaros);
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicDeus);
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicEx);
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicMachina);

						/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
						if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
						{
							DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

							// 選択肢1のテキストを黒で描画
							DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicSaros);
						}
						else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2ボタンとマウスカーソルが接触している
						{
							DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

							// 選択肢2のテキストを黒で描画
							DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicDeus);
						}
					}
				}
				else if (MP < MPofMagicMachina)
				{
					/* +++ 4つの選択肢のボタンを白枠または灰枠で描画 +++ */
					DrawRect(optionButton1, Color_White, false, 3);
					DrawRect(optionButton2, Color_White, false, 3);
					DrawRect(optionButton3, Color_White, false, 3);
					DrawRect(optionButton4, Color_Gray, false, 3);

					/* +++ 魔法の選択肢のテキストを白または灰で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicSaros);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicDeus);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicEx);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicMachina);

					/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicSaros);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicDeus);
					}
					else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicEx);
					}
				}
				else
				{
					/* +++ 4つの選択肢のボタンを白枠で描画 +++ */
					DrawRect(optionButton1, Color_White, false, 3);
					DrawRect(optionButton2, Color_White, false, 3);
					DrawRect(optionButton3, Color_White, false, 3);
					DrawRect(optionButton4, Color_White, false, 3);

					/* +++ 魔法の選択肢のテキストを白で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicSaros);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicDeus);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicEx);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicMachina);

					/* +++ マウスカーソルが触れている選択肢のボタンによって処理を変える +++ */
					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicSaros);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicDeus);
					}
					else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3ボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicEx);
					}
					else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton4, Color_White, true, 3);		// 選択肢4ボタンを白で塗りつぶして描画

						// 選択肢4のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicMachina);
					}
				}

				DrawBackBottun();
			}
			else if (actionNumber == 30)	// アクションナンバーが30である
			{
				if (TP < TPofKebehsenuev)	// TPがケベフスの消費TPより少ないなら
				{
					/* +++ 3つの選択肢のボタンを白または灰色枠で描画 +++ */
					DrawRect(optionButton1, Color_Gray, false, 3);
					DrawRect(optionButton2, Color_Gray, false, 3);
					DrawRect(optionButton3, Color_Gray, false, 3);
					DrawRect(optionButton4, Color_Gray, false, 3);

					/* +++ 特技の選択肢のテキストを灰色で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionImseti);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionHarpy);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionKebehsenuev);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionDuamtef);
				}
				else if (TP < TPofDuamtef)
				{
					/* +++ 4つの選択肢のボタン白または灰色枠で描画 +++ */
					DrawRect(optionButton1, Color_White, false, 3);
					DrawRect(optionButton2, Color_White, false, 3);
					DrawRect(optionButton3, Color_White, false, 3);
					DrawRect(optionButton4, Color_Gray, false, 3);

					/* +++ 特技の選択肢のテキストを白または灰色で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionImseti);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionHarpy);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionKebehsenuev);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionDuamtef);

					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionImseti);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionHarpy);
					}
					else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionKebehsenuev);
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
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionImseti);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionHarpy);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionKebehsenuev);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionDuamtef);

					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionImseti);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionHarpy);
					}
					else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionKebehsenuev);
					}
					else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton4, Color_White, true, 3);		// 選択肢4ボタンを白で塗りつぶして描画

						// 選択肢4のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionDuamtef);
					}
				}

				DrawBackBottun();
			}
		}
	}

	return;
}


void Dightmare::BattleFase_Process()
{
	if (actionFlag == false)	// アクションフラグがfalseなら
	{
		if (statusAilment == Paralysis)		// 「マヒ」なら
		{
			StatusProcess_Paralysis();	// 「マヒ」の処理を実行
		}
		else
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

				if (statusAilment == Silence)		// 「沈黙」なら
				{
					StatusProcess_Silence();	// 「沈黙」の処理を実行
				}
				else
				{
					MagicSaros();		// サロスを実行
				}
				break;
			case 22:
				/* +++ アクションナンバーが22 +++ */

				if (statusAilment == Silence)		// 「沈黙」なら
				{
					StatusProcess_Silence();	// 「沈黙」の処理を実行
				}
				else
				{
					MagicDeus();		// デウスを実行
				}
				break;
			case 23:
				/* +++ アクションナンバーが23 +++ */

				if (statusAilment == Silence)		// 「沈黙」なら
				{
					StatusProcess_Silence();	// 「沈黙」の処理を実行
				}
				else
				{
					MagicEx();			// エクスを実行
				}
				break;
			case 24:
				/* +++ アクションナンバーが24 +++ */

				if (statusAilment == Silence)		// 「沈黙」なら
				{
					StatusProcess_Silence();	// 「沈黙」の処理を実行
				}
				else
				{
					MagicMachina();		// マキナを実行
				}
				break;
			case 31:
				/* +++ アクションナンバーが31 +++ */

				if (statusAilment == Slump)		// 「不調」なら
				{
					StatusProcess_Slump();	// 「不調」の処理を実行
				}
				else
				{
					Imseti();		// イムセトを実行
				}
				break;
			case 32:
				/* +++ アクションナンバーが32 +++ */

				if (statusAilment == Slump)		// 「不調」なら
				{
					StatusProcess_Slump();	// 「不調」の処理を実行
				}
				else
				{
					Harpy();		// ハーピを実行
				}
				break;
			case 33:
				/* +++ アクションナンバーが33 +++ */

				if (statusAilment == Slump)		// 「不調」なら
				{
					StatusProcess_Slump();	// 「不調」の処理を実行
				}
				else
				{
					Kebehsenuev();	// ケベフスを実行
				}
				break;
			case 34:
				/* +++ アクションナンバーが34 +++ */

				if (statusAilment == Slump)		// 「不調」なら
				{
					StatusProcess_Slump();	// 「不調」の処理を実行
				}
				else
				{
					Duamtef();		// ドゥアムタを実行
				}
				break;
			case 40:
				/* +++ アクションナンバーが40 +++ */

				NormalDefence();	// 通常防御を実行
				break;
			default:
				break;
			}
		}

		actionNumber = 0;	// アクションナンバーをリセット
		MyActionFlagTrue();		// アクションフラグをtrueにする
	}

	return;
}

void Dightmare::BattleFase_Draw()
{
	return;
}

void Dightmare::EndFase_Process()
{
	if (actionFlag == false)	// アクションフラグがfalseなら
	{
		TP_Calc(10, ISENHANCE);

		Check_Status();		// 状態異常からの復帰を確認する

		StatusProcess_Poisoning();	// 「毒」状態の処理を行う

		if (defenceCoefficient != 1)
		{
			defenceCoefficient = 1;
		}

		MyActionFlagTrue();
	}

	return;
}

void Dightmare::EndFase_Draw()
{
	return;
}


/* --- サロス - 1ターン溜めて放つ魔法(MP: 15) --- */
void Dightmare::MagicSaros()
{
	int calcResult;		// 計算結果の格納変数

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message2Line;

	if (chargeStep == 0)
	{
		MP_Calc(MPofMagicSaros, ISREDUCTION);	// MPを消費MP分減らす

		if (isPlayer)
		{
			sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicSaros1);
		}
		else
		{
			sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicSaros1);
		}

		Sound_Play(SE_MagicSaros1);
	}
	else if (chargeStep == 1)
	{
		calcResult = (int)(Magic * 3.0);	// 魔力に補正をのせる

		if (isPlayer)
		{
			sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicSaros2);

			Enemy->Damage_Calc(calcResult, Magical);
		}
		else
		{
			sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicSaros2);

			Player->Damage_Calc(calcResult, Magical);
		}

		Sound_Play(SE_MagicSaros2);
	}

	return;
}

/* --- デウス - HPを回復し最大HPを上昇させる(MP: 20) --- */
void Dightmare::MagicDeus()
{
	MP_Calc(MPofMagicDeus, ISREDUCTION);

	settingMessagePattern = Message3Line;
	displayMessagePattern = Message3Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicDeus);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicDeus);
	}

	MaxHP_Calc(100, ISENHANCE);
	HP_Calc(150, ISHEAL, false);

	Sound_Play(SE_MagicDeus);

	return;
}

/* --- エクス - 攻撃しつつHPを上昇させる(MP: 25) --- */
void Dightmare::MagicEx()
{
	int calcResult;		// 計算結果の格納変数

	MP_Calc(MPofMagicEx, ISREDUCTION);	// MPを消費MP分減らす

	calcResult = (int)(Magic * 1.2);	// 魔力に補正をのせる

	settingMessagePattern = Message3Line;
	displayMessagePattern = Message3Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicEx);

		Enemy->Damage_Calc(calcResult, Magical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicEx);

		Player->Damage_Calc(calcResult, Magical);
	}

	HP_Calc(100, ISHEAL, false);

	Sound_Play(SE_MagicEx);

	return;
}

/* --- マキナ - 攻撃力と魔力を上昇させる(MP: 30) --- */
void Dightmare::MagicMachina()
{
	MP_Calc(MPofMagicMachina, ISREDUCTION);

	settingMessagePattern = Message3Line;
	displayMessagePattern = Message3Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicMachina);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicMachina);
	}

	Attack_Calc(30, ISENHANCE);
	Magic_Calc(30, ISENHANCE);

	Sound_Play(SE_MagicMachina);

	return;
}

/* --- イムセト - 2連続の物理攻撃(TP: 15) --- */
void Dightmare::Imseti()
{
	int calcResult;		// 計算結果の格納変数

	TP_Calc(TPofImseti, ISREDUCTION);	// TPを消費TP分減らす

	calcResult = (int)(Attack * 2.0);	// 攻撃力に補正をのせる

	settingMessagePattern = Message3Line;
	displayMessagePattern = Message3Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionImseti);

		Enemy->Damage_Calc(calcResult, Physical);
		Enemy->Damage_Calc(calcResult, Physical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionImseti);

		Player->Damage_Calc(calcResult, Physical);
		Player->Damage_Calc(calcResult, Physical);
	}

	Sound_Play(SE_Imseti);

	return;
}

/* --- ハーピ - 必ず先制攻撃できる物理攻撃(TP: 15) --- */
void Dightmare::Harpy()
{
	int calcResult;		// 計算結果の格納変数

	TP_Calc(TPofHarpy, ISREDUCTION);	// TPを消費TP分減らす

	calcResult = (int)(Attack * 1.1);	// 攻撃力に補正をのせる

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message2Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionHarpy);

		Enemy->Damage_Calc(calcResult, Physical);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionHarpy);

		Player->Damage_Calc(calcResult, Physical);
	}

	Sound_Play(SE_Harpy);

	return;
}

/* --- ケベフス - 魔力参照のブレス攻撃(TP: 15) --- */
void Dightmare::Kebehsenuev()
{
	int calcResult;		// 計算結果の格納変数

	TP_Calc(TPofKebehsenuev, ISREDUCTION);	// TPを消費MP分減らす

	calcResult = (int)(Magic * 1.5);	// 魔力に補正をのせる

	settingMessagePattern = Message2Line;
	displayMessagePattern = Message2Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionKebehsenuev);

		Enemy->Damage_Calc(calcResult, Breath);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionKebehsenuev);

		Player->Damage_Calc(calcResult, Breath);
	}

	Sound_Play(SE_Kebehsenuev);

	return;
}

/* --- ドゥアムタ - 物理、魔法、ブレスの同時攻撃(TP: 45) --- */
void Dightmare::Duamtef()
{
	int calcResult1, calcResult2;

	TP_Calc(TPofDuamtef, ISREDUCTION);		// 消費TP分TPを減らす

	calcResult1 = (int)(Attack * 1.5);	// 攻撃力に補正をのせる
	calcResult2 = (int)(Magic * 1.5);	// 魔力に補正をのせる

	settingMessagePattern = Message4Line;
	displayMessagePattern = Message4Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionDuamtef);

		Enemy->Damage_Calc(calcResult1, Physical);
		Enemy->Damage_Calc(calcResult2, Magical);
		Enemy->Damage_Calc(calcResult1, Breath);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionDuamtef);

		Player->Damage_Calc(calcResult1, Physical);
		Player->Damage_Calc(calcResult2, Magical);
		Player->Damage_Calc(calcResult1, Breath);
	}

	Sound_Play(SE_Duamtef1);
	Sound_Play(SE_Duamtef2);
	Sound_Play(SE_Duamtef3);

	return;
}