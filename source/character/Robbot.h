#pragma once
/* === ロボットキャラクター関連のヘッダファイル === */

#include "DxLib.h"
#include "Character.h"


/* +++ ロボットキャラのステータス +++ */
#define RobotHP		500		// ロボットのHP
#define RobotMP		0		// ロボットのMP
#define RobotAttack	100		// ロボットの攻撃力
#define RobotDefence	100		// ロボットの守備力
#define RobotMagic		0		// ロボットの魔法攻撃力
#define RobotPrevent	10		// ロボットの魔法守備力
#define RobotSpeed		5		// ロボットの素早さ

#define TPofFlameThrower		10	// 火炎放射の消費TP
#define TPofHighFlameThrower	40	// 強化火炎放射の消費TP
#define ThresholdFlameThrower	50	// 火炎放射の強化の閾値
#define TPofSteelization		15	// 鋼鉄化の消費TP
#define TPofMagicShut			15	// 魔力遮断の消費TP
#define TPofTripleBarrage		25	// 三連砲撃の消費TP


/* --- ロボットキャラクターのクラス(キャラクタークラスを継承) --- */
class Robot : public Character
{
public:
	void Character_Init(bool isThisPlayer);		// キャラクターの初期化関数
	void MainFase_Process();					// メインフェイズの処理関数
	void MainFase_Draw();						// メインフェイズの描画関数
	void BattleFase_Process();					// バトルフェイズの処理関数
	void BattleFase_Draw();						// バトルフェイズの描画関数
	void EndFase_Process();						// エンドフェイズの処理関数
	void EndFase_Draw();						// エンドフェイズの描画関数

	void FlameThrower();	// 火炎放射-攻撃力参照の攻撃(TP:10)(後で効果を変える)
	void TripleBarrage();	// 三連砲撃-攻撃力参照の3回攻撃(TP:25)
	void Steelization();	// 鋼鉄化-守備力50アップ(TP:15)
	void MagicShut();		// 魔力遮断-魔防50アップ(TP:15)
};

extern Robot PlRobot;	// ロボットクラスの変数
extern Robot EnRobot;	// ロボットクラスの変数