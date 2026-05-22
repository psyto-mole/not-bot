#pragma once
///* === ダイトメア関連のヘッダファイル === */
//
//#include "DxLib.h"
//#include "Character.h"
//
///* +++ ダイトメアのステータス +++ */
//#define DightmareHP				// ダイトメアのHP
//#define DightmareMP				// ダイトメアのMP
//#define DightmareAttack			// ダイトメアの攻撃力
//#define DightmareDefence		// ダイトメアの守備力
//#define DightmareMagic			// ダイトメアの魔法攻撃力
//#define DightmarePrevent		// ダイトメアの魔法守備力
//#define DightmareSpeed			// ダイトメアの素早さ
//
//#define MPofMagicSaros		15	// サロスの消費MP
//#define MPofMagicDeus		20	// デウスの消費MP
//#define MPofMagicEx			25	// エクスの消費MP
//#define MPofMagicMachina	30	// マキナの消費MP
//
//#define TPofImseti			15	// イムセトの消費TP
//#define TPofHarpy			15	// ハーピの消費TP
//#define TPofKebehsenuev		15	// ケベフスの消費TP
//#define TPofDuamtef			45	// ドゥアムタの消費TP
//
//
///* --- ダイトメアのクラス(キャラクタークラスを継承) --- */
//class Dightmare : public Character
//{
//protected:
//	int chargeStep;		// チャージ技の溜め段階を保持する変数
//
//public:
//	void Character_Init(bool isThisPlayer);		// キャラクターの初期化関数
//	void MainFase_Process();					// メインフェイズの処理関数
//	void MainFase_Draw();						// メインフェイズの描画関数
//	void BattleFase_Process();					// バトルフェイズの処理関数
//	void BattleFase_Draw();						// バトルフェイズの描画関数
//	void EndFase_Process();						// エンドフェイズの処理関数
//	void EndFase_Draw();						// エンドフェイズの描画関数
//
//	void MagicSaros();		// サロス-1ターンチャージして放つ魔法(MP: 15)
//	void MagicDeus();		// デウス-HPを回復し最大HPを上昇させる(MP: 20)
//	void MagicEx();			// エクス-攻撃しつつHPを回複する(MP: 25)
//	void MagicMachina();	// マキナ-攻撃力と魔力を上昇させる(MP: 30)
//
//	void Imseti();			// イムセト-2連続の物理攻撃(TP: 15)
//	void Harpy();			// ハーピ-必ず先制攻撃できる物理攻撃(TP: 15)
//	void Kebehsenuev();		// ケベフス-魔力参照のブレス攻撃(TP: 15)
//	void Duamtef();			// ドゥアムタ-物理、魔法、ブレスの同時攻撃(TP: 45)
//};
//
//extern Dightmare PlDightmare, EnDightmare;		// ダイトメアクラスの変数