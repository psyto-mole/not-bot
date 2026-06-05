#pragma once
/* === ドラゴンキャラクター関連のヘッダファイル === */

#include "DxLib.h"
#include "Character.h"


#define DragonHP		400		// ドラゴンのHP
#define DragonMP		40		// ドラゴンのMP
#define DragonAttack	100		// ドラゴンの攻撃力
#define DragonDefence	100		// ドラゴンの守備力
#define DragonMagic		80		// ドラゴンの魔法攻撃力
#define DragonPrevent	80		// ドラゴンの魔法守備力
#define DragonSpeed		40		// ドラゴンの素早さ

#define MPofMagicPillar		15	// ピラーの消費MP
#define MPofMagicFung		20	// ファングの消費MP
#define MPofMagicRecover	20	// リカバーの消費MP

#define TPofCurseBreath			15	// 呪いの息の消費TP
#define TPofImmortalScale		20	// 竜仙鱗の消費TP
#define TPofDestructBreath		25	// 破壊の息の消費TP
#define TPofAbsorbAtmosphere	40	// 大気吸収の消費TP


/* --- ドラゴンキャラクターのクラス(キャラクタークラスを継承) --- */
class Dragon : public Character
{
private:
	int randomDebuffNumber;		// 付与する状態異常についての乱数を保持する変数

public:
	void Character_Init(bool isThisPlayer);		// キャラクターの初期化関数
	void MainFase_Process();					// メインフェイズの処理関数
	void MainFase_Draw();						// メインフェイズの描画関数
	void BattleFase_Process();					// バトルフェイズの処理関数
	void BattleFase_Draw();						// バトルフェイズの描画関数
	void EndFase_Process();						// エンドフェイズの処理関数
	void EndFase_Draw();						// エンドフェイズの描画関数

	void MagicPillar();		// ピラー-魔力参照の魔法攻撃(MP:15)
	void MagicFung();		// ファング-魔力参照の物理攻撃(MP:20)
	void MagicRecover();	// リカバー-魔力参照の回復魔法(MP:20)

	void CurseBreath();			// 呪いの息-魔力参照のブレス攻撃、相手のステータスをランダムに下げる(TP:15)
	void ImmortalScale();		// 竜仙鱗-発動したターンに受けるダメージを90%カットする(TP:20)
	void DestructBreath();		// 破壊の息-攻撃力参照のブレス攻撃(TP:25)
	void AbsorbAtmosphere();	// 大気吸収-自身のMPとTPを回復する(TP:40)
};

extern Dragon PlDragon, EnDragon;	// ドラゴンクラスの変数