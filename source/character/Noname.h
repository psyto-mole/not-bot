#pragma once
/* === 「名無し」関連のヘッダファイル === */

#include <DxLib.h>
#include "Character.h"

/* +++ 「名無し」のステータス +++ */
#define NonameHP		500		// 「名無し」のHP
#define NonameMP		150		// 「名無し」のMP
#define NonameAttack	60		// 「名無し」の攻撃力
#define NonameDefence	90		// 「名無し」の守備力
#define NonameMagic		60		// 「名無し」の魔法攻撃力
#define NonamePrevent	90		// 「名無し」の魔法守備力
#define NonameSpeed		70		// 「名無し」の素早さ

#define MPofMagicTentativeDark		10	// ダーク(仮)の消費MP
#define MPofMagicTentativeLight		10	// ライト(仮)の消費MP
#define MPofMagicTentativeHeal		10	// ヒール(仮)の消費MP
#define MPofMagicTentativeRock		10	// ロック(仮)の消費MP

#define TPofTentativeThunder	15	// 雷刃(仮)の消費TP
#define TPofTentativePoison		15	// 毒刃(仮)の消費TP
#define TPofTentativeBreath		25	// 無の息(仮)の消費TP
#define TPofTentativeFinal		40	// 最終撃(仮)の消費TP


/* --- 「名無し」のクラス(キャラクタークラスを継承) --- */
class Noname : public Character
{
public:
	void Character_Init(bool isThisPlayer);		// キャラクターの初期化関数
	void MainFase_Process();					// メインフェイズの処理関数
	void MainFase_Draw();						// メインフェイズの描画関数
	void BattleFase_Process();					// バトルフェイズの処理関数
	void BattleFase_Draw();						// バトルフェイズの描画関数
	void EndFase_Process();						// エンドフェイズの処理関数
	void EndFase_Draw();						// エンドフェイズの描画関数

	void MagicTentativeDark();		// ダーク(仮) - 闇の魔力で攻撃し、たまに相手の魔法を封じる(MP: 10)
	void MagicTentativeLight();		// ライト(仮) - 光の魔力を放ち相手の物理攻撃の命中率を下げる(MP: 10)
	void MagicTentativeHeal();		// ヒール(仮) - 魔法を唱えてダメージを回復する(MP: 10)
	void MagicTentativeRock();		// ロック(仮) - 大地から岩石を掘り出し投げつける(MP: 25)

	void TentativeThunder();	// 雷刃(仮) - 雷の刃で攻撃し、たまに相手をマヒにする(TP: 15)
	void TentativePoison();		// 毒刃(仮) - 毒の刃で攻撃し、相手を毒状態にする(TP: 15)
	void TentativeBreath();		// 無の息(仮) - 形容しがたいブレスの攻撃(TP: 25)
	void TentativeFinal();		// 最終撃(仮) - 守りを犠牲に攻撃する(TP: 40)
};

extern Noname PlNoname, EnNoname;		// 「名無し」クラスの変数