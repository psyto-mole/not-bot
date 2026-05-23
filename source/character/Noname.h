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

#define MPofMagic			// の消費MP
#define MPofMagic			// の消費MP
#define MPofMagic			// の消費MP
#define MPofMagic			// の消費MP

#define TPof			// の消費TP
#define TPof			// の消費TP
#define TPof			// の消費TP
#define TPof			// の消費TP


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

	void MagicAA();		//  - (MP: )
	void MagicAB();		//  - (MP: )
	void MagicAC();		//  - (MP: )
	void MagicAD();		//  - (MP: )

	void AA();		//  - (TP: )
	void AB();		//  - (TP: )
	void AC();		//  - (TP: )
	void AD();		//  - (TP: )
};

extern Noname PlNoname, EnNoname;		// 「名無し」クラスの変数