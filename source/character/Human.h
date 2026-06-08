#pragma once
/* === 人間キャラクター関連のヘッダファイル === */

#include "DxLib.h"
#include "Character.h"

/* +++ 人間キャラのステータス +++ */
#define HumanHP			300		// 人間のHP
#define HumanMP			100		// 人間のMP
#define HumanAttack		60		// 人間の攻撃力
#define HumanDefence	80		// 人間の守備力
#define HumanMagic		70		// 人間の魔法攻撃力
#define HumanPrevent	40		// 人間の魔法守備力
#define HumanSpeed		30		// 人間の素早さ

#define MPofMagicFire		5	// ファイアの消費MP
#define MPofMagicThunder	5	// サンダーの消費MP
#define MPofMagicIce		10	// アイスの消費MP
#define MPofMagicHeal		10	// ヒールの消費MP

#define TPofTPCharge		0	// 精神統一の消費TP
#define TPofAllHeartSoul	10	// 全霊斬りの消費TP
#define TPofMPCharge		15	// 魔力補給の消費TP
#define TPofGatherEnergy	15	// 気合の消費TP


/* --- 人間キャラクターのクラス(キャラクタークラスを継承) --- */
class Human : public Character
{
public:
	void Character_Init(bool isThisPlayer);		// キャラクターの初期化関数
	void MainFase_Process();					// メインフェイズの処理関数
	void MainFase_Draw();						// メインフェイズの描画関数
	void BattleFase_Process();					// バトルフェイズの処理関数
	void BattleFase_Draw();						// バトルフェイズの描画関数
	void EndFase_Process();						// エンドフェイズの処理関数
	void EndFase_Draw();						// エンドフェイズの描画関数

	void MagicFire();		// ファイア-魔力参照の攻撃(MP:5)
	void MagicThunder();	// サンダー-魔力参照の先制攻撃(MP:5)
	void MagicIce();		// アイス-魔力参照の攻撃(MP:10)
	void MagicHeal();		// ヒール-魔力参照の状態異常も回復する回復技(MP:10)

	void TPCharge();		// 精神統一-TPを回復する(TP:0)
	void AllHeartSoul();	// 全霊斬り-攻撃力参照の攻撃(TP:0)
	void MPCharge();		// 魔力補給-MPを回復する(TP:15)
	void GatherEnergy();	// 気合-攻撃力を上げる(TP:15)
};

extern Human PlHuman, EnHuman;		// 人間クラスの変数