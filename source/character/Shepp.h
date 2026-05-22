#pragma once
/* === Sheppキャラクター関連のヘッダファイル ===*/

#include "DxLib.h"
#include "Character.h"


#define SheppHP			800		// sheppのHP
#define SheppMP			30		// sheppのMP
#define SheppAttack		50		// sheppの攻撃力
#define SheppDefence	80		// sheppの守備力
#define SheppMagic		200		// sheppの魔法攻撃力
#define SheppPrevent	150		// sheppの魔法守備力
#define SheppSpeed		1		// sheppの素早さ

#define MPofMagicMu		30	// μの消費MP
#define MPofMagicNu		30	// νの消費MP
#define MPofMagicLambda	30	// Λの消費MP
#define MPofMagicXi		30	// ξの消費MP

#define TPofPsi		20		// ψの消費TP
#define TPofOmega	25		// Ωの消費TP
#define TPofSigma	35		// Σの消費TP
#define TPofEta		100		// ηの消費TP


/* --- Sheppキャラクターのクラス(キャラクタークラスを継承) --- */
class Shepp : public Character
{
public:
	void Character_Init(bool isThisPlayer);		// キャラクターの初期化関数
	void MainFase_Process();					// メインフェイズの処理関数
	void MainFase_Draw();						// メインフェイズの描画関数
	void BattleFase_Process();					// バトルフェイズの処理関数
	void BattleFase_Draw();						// バトルフェイズの描画関数
	void EndFase_Process();						// エンドフェイズの処理関数
	void EndFase_Draw();						// エンドフェイズの描画関数

	void MagicMu();			// μ-TPを増加させる(MP:30)
	void MagicNu();			// ν-最大HPを増加させる(MP:30)
	void MagicLambda();		// Λ-魔力を増加させる(MP:30)
	void MagicXi();			// ξ-相手の守備力、魔法守備力、TPを減少させる(MP:30)

	void Psi();		// ψ-攻撃力参照の物理攻撃(TP:20)
	void Omega();	// Ω-魔力を消費しTPを増加させる、または魔力を回復する(TP:25)
	void Sigma();	// Σ-攻撃力参照のブレス攻撃(TP:35)
	void Eta();		// η-魔力参照の魔法攻撃(TP:100)
};

extern Shepp PlShepp, EnShepp;		// Sheppクラスの変数