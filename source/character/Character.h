#pragma once
/* === キャラクター関連のヘッダファイル === */

#include "DxLib.h"

#define ISPLAYER		true	// そのキャラがプレイヤーキャラである
#define ISENEMY			false	// そのキャラが敵キャラである
#define ISDAMAGE		true	// HPの数値変動がダメージである
#define ISHEAL			false	// HPの数値変動が回復である
#define ISENHANCE		true	// 数値の変動が増加である
#define ISREDUCTION		false	// 数値の変動が減少である

enum Context
{
	Physical,
	Magical,
	Breath
};

/* --- キャラクタークラス --- */
class Character
{
protected:
	int randomNumber;			// 行動選択についての乱数を保持する変数
	int randomStatusNumber;		// 状態異常についての乱数を保持する変数

	char characterName[64];		// 自身のキャラクター名を格納する配列

	bool isPlayer;		// 自キャラがプレイヤーかを管理するフラグ

	bool actionFlag;	// アクションフラグ(各フェイズでキャラクターが行動したか管理する)
	int actionNumber;	// アクションナンバー(行動の種類を管理する変数)

	bool defencePreemptive;		// 先制防御フラグ
	bool attackPreemptive;		// 先制攻撃フラグ

	float defenceCoefficient;	// 防御係数(ダメージ計算時にダメージ量に乗算する)

	int HP, MP, TP;						// HP、MPとTP(ヒットポイント、マジックポイント、テクニカルポイント)
	int MaxHP, MaxMP;					// 最大HPと最大MP
	int Attack, Defence;				// 攻撃力と守備力
	int OriginAttack, OriginDefence;	// 元々の攻撃力と守備力
	int Magic, Prevent;					// 魔法攻撃力と魔法守備力
	int OriginMagic, OriginPrevent;		// 元々の魔法攻撃力と魔法守備力
	int Speed;							// 速さ
	int OriginSpeed;					// 元々の速さ

public:
	void Damage_Calc(int attackValue, Context context);					// ダメージの計算関数
	void MaxHP_Calc(int Value, bool isEnhance);							// 最大HPの増減関数
	void HP_Calc(int Value, bool isDamage);								// HPの増減関数
	void MP_Calc(int Value, bool isEnhance);							// MPの増減関数
	void TP_Calc(int Value, bool isEnhance, bool isDisplay = false);	// TPの増減関数
	void Attack_Calc(int Value, bool isEnhance);						// 攻撃力の増減関数
	void Defence_Calc(int Value, bool isEnhance);						// 守備力の増減関数
	void Magic_Calc(int Value, bool isEnhance);							// 魔力の増減関数
	void Prevent_Calc(int Value, bool isEnhance);						// 魔防の増減関数
	void Speed_Calc(int Value, bool isEnhance);							// 速さの増減関数

	int GetMyHP();			// 自身のHPを取得する
	int GetMyMP();			// 自身のMPを取得する
	int GetMyTP();			// 自身のTPを取得する
	int GetMyAttack();		// 自身の攻撃力を取得する
	int GetMyDefence();	// 自身の守備力を取得する
	int GetMyMagic();		// 自身の魔力を取得する
	int GetMyPrevent();		// 自身の魔防を取得する
	int GetMySpeed();		// 自身の速さを取得する

	bool GetMyActionFlag();		// 自身のアクションフラグを取得する
	void MyActionFlagTrue();	// 自身のアクションフラグをtrueにする
	void MyActionFlagFalse();	// 自身のアクションフラグをfalseにする

	bool GetMyAttackPreemptive();		// 先制攻撃フラグを取得する
	bool GetMyDefencePreemptive();		// 先制防御フラグを取得する
	void MyAttackPreemptiveTrue();		// 先制攻撃フラグをtrueにする
	void MyDefencePreemptiveTrue();		// 先制防御フラグをfalseにする
	void MyPreemptiveFalse();			// 2種類の先制行動フラグをfalseにする

	bool GetMyCharacterAttribute();		// 自身の属性(プレイヤーキャラか敵キャラか)を取得する

	void DrawActionNumber(int x, int y, unsigned int color, int fontHandle);
	void DrawStatusUI(bool isPlayer);	// キャラクターのステータスUIを表示する関数
	void DrawBackBottun();				// 「戻る」ボタンを描画する関数

	void NormalAttack();	// 通常攻撃
	void NormalDefence();	// 防御


	virtual void Character_Init(bool isThisPlayer) = 0;		// キャラクターの初期化関数(純粋仮想関数)
	virtual void MainFase_Process() = 0;					// メインフェイズの処理関数(純粋仮想関数)
	virtual void MainFase_Draw() = 0;						// メインフェイズの描画関数(純粋仮想関数)
	virtual void BattleFase_Process() = 0;					// バトルフェイズの処理関数(純粋仮想関数)
	virtual void BattleFase_Draw() = 0;						// バトルフェイズの描画関数(純粋仮想関数)
	virtual void EndFase_Process() = 0;						// エンドフェイズの処理関数(純粋仮想関数)
	virtual void EndFase_Draw() = 0;						// エンドフェイズの描画関数(純粋仮想関数)
};

extern int enemyKindNumber;		// 敵キャラクターの種類を保持する変数
extern int playerKindNumber;	// 自キャラの種類を保持する変数


extern Character* Player, * Enemy;	// キャラクタークラスのポインタ変数

extern void ActionFlagFalse();		// アクションフラグをfalseにする関数
extern void PreemptiveFalse();		// 先制行動フラグをfalseにする関数
extern void DrawPlayerEnemyNum();	// 敵キャラと自キャラの識別番号を表示する関数