/* === ロボットキャラクター関連のソースファイル === */

#include <string.h>
#include "Robbot.h"
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

Robot PlRobot, EnRobot;		// ロボットクラスの変数

/* +++ ロボットクラスのオーバーライド +++ */
/* --- 初期化関数 --- */
void Robot::Character_Init(bool isThisPlayer)
{
	/* +++ 最大HPと最大MP、元々のステータスを設定 +++ */
	MaxHP			= RobotHP;
	MaxMP			= RobotMP;
	OriginAttack	= RobotAttack;
	OriginDefence	= RobotDefence;
	OriginMagic		= RobotMagic;
	OriginPrevent	= RobotPrevent;
	OriginSpeed		= RobotSpeed;

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

	statusAilment = Fine;		// 状態を「異常なし」に設定
	ailmentTurn = 0;			// 状態異常の継続ターンを0にする
	ailmentPoisoning = false;	// 「毒」の状態異常を解除

	sprintf_s(characterName, sizeof(characterName),"%s", CharacterNameRobot);	// キャラクターの名前を設定

	/* +++ キャラがプレイヤーキャラか敵キャラかを設定 +++ */
	if (isThisPlayer)
	{
		isPlayer = ISPLAYER;
	}
	else
	{
		isPlayer = ISENEMY;
	}

	return;
}

/* --- メインフェイズの処理関数 --- */
void Robot::MainFase_Process()
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
			/* +++ 押されたボタン(optionButton1～4,backButton)に応じて処理を変える +++ */
			if (CollisionRectToPoint(optionButton1, nowMousePoint))		// 選択肢1にカーソルが合っている
			{
				if (actionNumber < 10)	// アクションナンバーが10未満なら
				{
					displayMessagePattern = Message1Line;
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfNormalAttack);
				}
				else
				{
					displayMessagePattern = Message2Line;
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfFlameThrower1);
					sprintf_s(battleMessage2, sizeof(battleMessage1), "%s", DetailOfFlameThrower2);
				}

				if (Mouse_Check_Click(MOUSE_INPUT_LEFT))	// マウスがクリックされた
				{
					if (actionNumber < 10)	// アクションナンバーが10未満なら
					{
						Sound_Play(SE_Enter);

						actionNumber = 10;	// アクションナンバーに10を代入する

						MyActionFlagTrue();	// アクションフラグをtrueにする
					}
					else	// アクションナンバーが10以上なら
					{
						if (TP >= TPofFlameThrower)	// TPが火炎放射の消費TP以上なら
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
					displayMessagePattern = Message1Line;
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s", CharacterNameRobot, DetailCantUseMagic);
				}
				else
				{
					displayMessagePattern = Message1Line;
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfSteelization);
				}

				if (Mouse_Check_Click(MOUSE_INPUT_LEFT))	// マウスがクリックされた
				{
					if (actionNumber == 30)		// アクションナンバーが30なら
					{
						if (TP >= TPofSteelization)	// TPが鋼鉄化の消費TP以上なら
						{
							Sound_Play(SE_Enter);

							actionNumber += 2;	// アクションナンバーに2を加算する

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
			else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3にカーソルがあっている
			{
				if (actionNumber < 10)	// アクションナンバーが10未満なら
				{
					displayMessagePattern = Message1Line;

					if (statusAilment == Slump)
					{
						// 特技が封じられている旨をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailSealedSpecial);
					}
					else
					{
						// 特技の説明文をメッセージに設定
						sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfSpecial);
					}
				}
				else
				{
					displayMessagePattern = Message1Line;
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfMagicShut);
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
					else	// アクションナンバーが10以上なら
					{
						if (TP >= TPofMagicShut)	// TPが魔力遮断の消費TP以上なら
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
					displayMessagePattern = Message1Line;
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfNormalDefence);
				}
				else
				{
					displayMessagePattern = Message1Line;
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s", DetailOfTripleBarrage);
				}

				if (Mouse_Check_Click(MOUSE_INPUT_LEFT))	// マウスがクリックされた
				{
					if (actionNumber < 10)	// アクションナンバーが10未満なら
					{
						Sound_Play(SE_Enter);

						actionNumber = 40;	// アクションナンバーに40を代入

						MyDefencePreemptiveTrue();		// 自身の先制防御フラグをtrueにする

						MyActionFlagTrue();	// アクションフラグをtrueにする
					}
					else	// アクションナンバーが10以上なら
					{
						if (TP >= TPofTripleBarrage)	// TPが三連砲撃の消費TP以上なら
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
				if (actionNumber == 30)		// アクションナンバーが30なら
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
			if (actionNumber < 10 && randomNumber != 2)		// アクションナンバーが10未満で乱数が2ではない
			{
				if (statusAilment == Slump)
				{
					if (actionNumber != 3)
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
			else if(actionNumber == 30)		// アクションナンバーが30
			{
				/* +++ 乱数の値によって処理を変更 ++ */
				switch (randomNumber)
				{
				case 1:
					/* +++ 乱数の値が1 +++ */

					if (TP < TPofFlameThrower)	// TPが火炎放射の消費TP未満なら
					{
						actionNumber = 0;

						return;		// 処理を終了
					}
					break;
				case 2:
					/* +++ 乱数の値が2 +++ */

					if (TP < TPofSteelization)	// TPが鋼鉄化の消費TP未満なら
					{
						actionNumber = 0;

						return;		// 処理を終了
					}
					break;
				case 3:
					/* +++ 乱数の値が3 +++ */

					if (TP < TPofMagicShut)	// TPが魔力遮断の消費TP未満なら
					{
						actionNumber = 0;

						return;		// 処理を終了
					}
					break;
				case 4:
					/* +++ 乱数の値が4 +++ */

					if (TP < TPofTripleBarrage)	// TPが三連砲撃の消費TP未満なら
					{
						actionNumber = 0;

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

/* --- メインフェイズの描画関数 --- */
void Robot::MainFase_Draw()
{
	if (isPlayer)	// プレイヤーキャラなら
	{
		if (statusAilment != Paralysis)		// 「マヒ」でないなら
		{
			if (actionNumber < 10)	// アクションナンバーが10未満なら
			{
				/* +++ 選択肢1と4のボタンを白枠で描画 +++ */
				DrawRect(optionButton1, Color_White, false, 3);
				DrawRect(optionButton2, Color_Gray, false, 3);
				DrawRect(optionButton4, Color_White, false, 3);

				/* +++ 選択肢1と4のテキストを白で描画 +++ */
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionAttack);
				DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagic);
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

				if (statusAilment == Slump)
				{
					DrawRect(optionButton3, Color_Gray, false, 3);	// 選択肢3のボタンを灰枠で描画

					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionSpecial);
				}
				else
				{
					if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);	// 選択肢3のボタンを白で塗りつぶして描画

						// 選択肢3のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionSpecial);
					}
					else
					{
						DrawRect(optionButton3, Color_White, false, 3);	// 選択肢3のボタンを白で描画

						// 選択肢3のテキストを白で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionSpecial);
					}
				}
			}
			else if (actionNumber == 30)	// アクションナンバーが30である
			{
				if (TP < TPofFlameThrower)
				{
					/* +++ 4つの選択肢のボタンを灰色枠で描画 +++ */
					DrawRect(optionButton1, Color_Gray, false, 3);
					DrawRect(optionButton2, Color_Gray, false, 3);
					DrawRect(optionButton3, Color_Gray, false, 3);
					DrawRect(optionButton4, Color_Gray, false, 3);

					/* +++ 特技の選択肢のテキストを灰色で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionFlameThrower);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionSteelization);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicShut);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionTripleBarrage);
				}
				else if (TP < TPofSteelization)
				{
					/* +++ 3つの選択肢のボタンを灰色枠で描画 +++ */
					DrawRect(optionButton2, Color_Gray, false, 3);
					DrawRect(optionButton3, Color_Gray, false, 3);
					DrawRect(optionButton4, Color_Gray, false, 3);

					/* +++ 特技の選択肢のテキストを灰色で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionSteelization);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionMagicShut);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionTripleBarrage);

					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionFlameThrower);
					}
					else
					{
						DrawRect(optionButton1, Color_White, false, 3);		// 選択肢2ボタンを白枠で描画

						// 選択肢2のテキストを白で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionFlameThrower);
					}
				}
				else if (TP < TPofTripleBarrage)
				{
					/* +++ 4つの選択肢のボタンを白枠または灰色枠で描画 +++ */
					DrawRect(optionButton1, Color_White, false, 3);
					DrawRect(optionButton2, Color_White, false, 3);
					DrawRect(optionButton3, Color_White, false, 3);
					DrawRect(optionButton4, Color_Gray, false, 3);

					/* +++ 特技の選択肢のテキストを白または灰色で描画 +++ */
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionFlameThrower);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionSteelization);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicShut);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Gray, MSMincho_40_1, OptionTripleBarrage);

					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionFlameThrower);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionSteelization);
					}
					else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicShut);
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
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionFlameThrower);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionSteelization);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionMagicShut);
					DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_White, MSMincho_40_1, OptionTripleBarrage);

					if (CollisionRectToPoint(optionButton1, nowMousePoint))	// 選択肢1のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton1, Color_White, true, 3);		// 選択肢1ボタンを白で塗りつぶして描画

						// 選択肢1のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionFlameThrower);
					}
					else if (CollisionRectToPoint(optionButton2, nowMousePoint))	// 選択肢2のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton2, Color_White, true, 3);		// 選択肢2ボタンを白で塗りつぶして描画

						// 選択肢2のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 930, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionSteelization);
					}
					else if (CollisionRectToPoint(optionButton3, nowMousePoint))	// 選択肢3のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton3, Color_White, true, 3);		// 選択肢3ボタンを白で塗りつぶして描画

						// 選択肢のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 860, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionMagicShut);
					}
					else if (CollisionRectToPoint(optionButton4, nowMousePoint))	// 選択肢4のボタンとマウスカーソルが接触している
					{
						DrawRect(optionButton4, Color_White, true, 3);		// 選択肢4ボタンを白で塗りつぶして描画

						// 選択肢4のテキストを黒で描画
						DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 660, 1010, FAlign_AllCenter, Color_Black, MSMincho_40_1, OptionTripleBarrage);
					}
				}

				DrawBackBottun();
			}
		}
	}

	return;
}


/* --- バトルフェイズの処理関数 --- */
void Robot::BattleFase_Process()
{
	if (actionFlag == false)	// アクションフラグがfalseなら
	{
		if (statusAilment == Paralysis)		// 「マヒ」なら
		{
			StatusProcess_Paralysis();
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

				break;
			case 22:
				/* +++ アクションナンバーが22 +++ */

				break;
			case 23:
				/* +++ アクションナンバーが23 +++ */

				break;
			case 24:
				/* +++ アクションナンバーが24 +++ */

				break;
			case 31:
				/* +++ アクションナンバーが31 +++ */

				if (statusAilment == Slump)		// 「不調」なら
				{
					StatusProcess_Slump();
				}
				else
				{
					FlameThrower();		// 火炎放射を実行
				}
				break;
			case 32:
				/* +++ アクションナンバーが32 +++ */

				if (statusAilment == Slump)		// 「不調」なら
				{
					StatusProcess_Slump();
				}
				else
				{
					Steelization();		// 鋼鉄化を実行
				}
				break;
			case 33:
				/* +++ アクションナンバーが33 +++ */

				if (statusAilment == Slump)		// 「不調」なら
				{
					StatusProcess_Slump();
				}
				else
				{
					MagicShut();	// 魔力遮断を実行
				}
				break;
			case 34:
				/* +++ アクションナンバーが34 +++ */

				if (statusAilment == Slump)		// 「不調」なら
				{
					StatusProcess_Slump();
				}
				else
				{
					TripleBarrage();	// 三連砲撃を実行
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

/* --- バトルフェイズの描画関数 --- */
void Robot::BattleFase_Draw()
{


	return;
}

/* --- エンドフェイズの処理関数 --- */
void Robot::EndFase_Process()
{
	if (actionFlag == false)	// アクションフラグがfalseなら
	{
		TP_Calc(10, ISENHANCE);

		Check_Status();		// 状態異常からの復帰を確認する

		if (defenceCoefficient != 1)
		{
			defenceCoefficient = 1;
		}

		MyActionFlagTrue();
	}

	return;
}

/* --- エンドフェイズの描画関数 --- */
void Robot::EndFase_Draw()
{


	return;
}


/* --- 火炎放射 - 攻撃力参照の攻撃(TP:10)(後で効果を変える) --- */
void Robot::FlameThrower()
{
	int calcResult;

	displayMessagePattern = Message2Line;
	settingMessagePattern = Message2Line;

	if (TP < ThresholdFlameThrower)
	{
		TP_Calc(TPofFlameThrower, ISREDUCTION);		// TPを消費TP分減らす

		calcResult = (int)(Attack * 1.1);	// 攻撃力に補正をのせる

		if (isPlayer)	// プレイヤーキャラなら
		{
			sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionFlameThrower1);

			Enemy->Damage_Calc(calcResult, Physical);
		}
		else	// 敵キャラクターなら
		{
			sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionFlameThrower1);

			Player->Damage_Calc(calcResult, Physical);
		}

		Sound_Play(SE_FlameThrower1);
	}
	else
	{
		TP_Calc(TPofHighFlameThrower, ISREDUCTION);		// TPを消費TP分減らす

		calcResult = Attack * 3;

		if (isPlayer)	// プレイヤーキャラなら
		{
			sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionFlameThrower2);

			Enemy->Damage_Calc(calcResult, Physical);
		}
		else	// 敵キャラクターなら
		{
			sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionFlameThrower2);

			Player->Damage_Calc(calcResult, Physical);
		}

		Sound_Play(SE_FlameThrower2);
	}

	return;
}

/* --- 鋼鉄化 - 守備力50アップ(TP:15) --- */
void Robot::Steelization()
{
	displayMessagePattern = Message2Line;
	settingMessagePattern = Message2Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionSteelization);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionSteelization);
	}

	Defence_Calc(50, ISENHANCE);				// 自身の守備力を50増加
	TP_Calc(TPofSteelization, ISREDUCTION);		// TPを消費TP分減らす

	Sound_Play(SE_Steelization);

	return;
}

/* --- 魔力遮断 - 魔防50アップ(TP:15) --- */
void Robot::MagicShut()
{
	displayMessagePattern = Message2Line;
	settingMessagePattern = Message2Line;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionMagicShut);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionMagicShut);
	}

	Prevent_Calc(50, ISENHANCE);	// 自身の魔法守備力を50増加
	TP_Calc(TPofMagicShut, ISREDUCTION);		// TPを消費TP分減らす

	Sound_Play(SE_MagicShut);

	return;
}

/* --- 三連砲撃 - 攻撃力参照の3回攻撃(TP:25) --- */
void Robot::TripleBarrage()
{
	int i;	// 繰り返しを管理するための簡易的な変数

	displayMessagePattern = Message4Line;
	settingMessagePattern = Message2Line;
	
	if (isPlayer)	// プレイヤーキャラクターなら
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionTripleBarrage);

		/* +++ ダメージ計算関数を3回実行する +++ */
		for (i = 0; i < 3; i++)
		{
			Enemy->Damage_Calc(Attack, Physical);		// 敵キャラのダメージ計算関数を自身の攻撃力を引数として実行
		}
	}
	else	// 敵キャラなら
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionTripleBarrage);

		/* +++ ダメージ計算関数を3回実行する +++ */
		for (i = 0; i < 3; i++)
		{
			Player->Damage_Calc(Attack, Physical);	// プレイヤーキャラクターのダメージ計算関数を自身の攻撃力を引数として実行
		}
	}

	TP_Calc(TPofTripleBarrage, ISREDUCTION);	// TPを消費TP分減らす

	Sound_Play(SE_TripleBarrage);
	Sound_Play(SE_TripleBarrage);
	Sound_Play(SE_TripleBarrage);

	return;
}