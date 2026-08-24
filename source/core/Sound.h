#pragma once
/* === サウンド処理のヘッダファイル === */

#include "DxLib.h"


#define VolumeQuiet		100		// 音量「小」の時の音量
#define VolumeMedium	150		// 音量「中」の時の音量
#define VolumeLoud		200		// 音量「大」の時の音量
#define VolumeMax		250		// 音量「最大」の時の音量

#define SoundPathStringMax 256	// サウンドの指定パスの文字列の最大長


/* --- サウンドの設定(構造体) --- */
typedef struct _Sound
{
	int Handle = -1;					// 画像ハンドル
	char Path[SoundPathStringMax];		// パス
	int Volume = -1;					// 音量
	bool PlayBeginning = true;			// 停止後に最初から再生するか
	int Playtype = DX_PLAYTYPE_BACK;	// 再生形式(デフォルトは1回のみ)
}Sounds;


/* +++ BGM +++ */
#define PathBGMFake			".\\Sound\\Maoh_Damashi\\maoh_game_village06.mp3"	// 偽のタイトル画面のBGMのパス
#define PathBGMTitle		".\\Sound\\Maoh_Damashi\\maoh_game_dangeon15.mp3"	// タイトル画面のBGMのパス
#define PathBGMResult		".\\Sound\\Maoh_Damashi\\maoh_game_theme14.mp3"		// ゲームオーバー画面のBGMのパス
#define PathBGMGameOver		".\\Sound\\Maoh_Damashi\\maoh_game_theme07.mp3"		// リザルト画面のBGMのパス
#define PathBGMBattle		".\\Sound\\Maoh_Damashi\\maoh_game_boss07.mp3"		// 対ロボットのバトル画面のBGMのパス

extern Sounds BGM_Fake;			// 偽のタイトル画面のBGM
extern Sounds BGM_Title;		// タイトル画面のBGM
extern Sounds BGM_GameOver;		// ゲームオーバー画面のBGM
extern Sounds BGM_Result;		// リザルト画面のBGM
extern Sounds BGM_Battle;		// 対ロボットのバトル画面のBGM


/* +++ 操作関連のSE +++ */
#define PathSEMenu			".\\Sound\\Sound_Effect_Lab\\Menu4.mp3"			// メニューを開くSEのパス
#define PathSEClick			".\\Sound\\Sound_Effect_Lab\\Click.mp3"			// クリックのSE(キャラセレクト用)のパス
#define PathSEEnter			".\\Sound\\Sound_Effect_Lab\\Cursor_Move3.mp3"	// 決定ボタンのSE(バトルシーン用)のパス
#define PathSEBack			".\\Sound\\Sound_Effect_Lab\\Cancel1.mp3"		// 戻るボタンのSE(バトルシーン用)のパス
#define PathSEUnavilable	".\\Sound\\Sound_Effect_Lab\\Sound_Beep4.mp3"	// 使用不可のSE(バトルシーン用)のパス

extern Sounds SE_Menu;			// メニューを開くSE
extern Sounds SE_Click;			// クリックのSE(キャラセレクト用)
extern Sounds SE_Enter;			// 決定ボタンのSE(バトルシーン用)
extern Sounds SE_Back;			// 戻るボタンのSE(バトルシーン用)
extern Sounds SE_Unavilable;	// 使用不可のSE(バトルシーン用)


/* +++ 共通技のSE +++ */
#define PathSENormalAttack		".\\Sound\\Sound_Effect_Lab\\Hitting2.mp3"		// 通常攻撃のSEのパス
#define PathSENormalDefence		".\\Sound\\Sound_Effect_Lab\\Warp.mp3"			// 通常防御のSEのパス
#define PathSEAttackMiss		".\\Sound\\Sound_Effect_Lab\\Sound_Beep2.mp3"	// 技失敗のSEのパス

extern Sounds SE_NormalAttack;	// 通常攻撃のSE
extern Sounds SE_NormalDefence;	// 通常防御のSE
extern Sounds SE_AttackMiss;	// 技失敗のSE


/* +++ ロボットの技のSE +++ */
#define PathSEFlameThrower1		".\\Sound\\Sound_Effect_Lab\\Magic_Fire2.mp3"		// 火炎放射のSE(弱版)のパス
#define PathSEFlameThrower2		".\\Sound\\Sound_Effect_Lab\\Magic_Fire3.mp3"		// 火炎放射のSE(強版)のパス
#define PathSESteelization		".\\Sound\\Sound_Effect_Lab\\Magic_Flozen.mp3"		// 鋼鉄化のSEのパス
#define PathSEMagicShut			".\\Sound\\Sound_Effect_Lab\\Magic_Reflect.mp3"		// 魔力遮断のSEのパス
#define PathSETripleBarrage		".\\Sound\\Sound_Effect_Lab\\Rocket_Launcher.mp3"	// 三連砲撃のSEのパス

extern Sounds SE_FlameThrower1;	// 火炎放射のSE(弱版)
extern Sounds SE_FlameThrower2;	// 火炎放射のSE(強版)
extern Sounds SE_Steelization;	// 鋼鉄化のSE
extern Sounds SE_MagicShut;		// 魔力遮断のSE
extern Sounds SE_TripleBarrage;	// 三連砲撃のSE


/* +++ 勇者の技のSE +++ */
#define PathSEMagicFire		".\\Sound\\Sound_Effect_Lab\\Magic_Fire1.mp3"			// ファイアのSEのパス
#define PathSEMagicIce		".\\Sound\\Sound_Effect_Lab\\Magic_Ice2.mp3"			// アイスのSEのパス
#define PathSEMagicThunder	".\\Sound\\OtoLogic\\Electric_Shock6.mp3"				// サンダーのSEのパス
#define PathSEMagicHeal		".\\Sound\\Sound_Effect_Lab\\Magic_Heal_Status1.mp3"	// ヒールのSEのパス

#define PathSETPCharge		".\\Sound\\Sound_Effect_Lab\\Cute_Sparkling1.mp3"			// 精神統一のSEのパス
#define PathSEAllHeartSoul	".\\Sound\\Sound_Effect_Lab\\Great_Sword.mp3"				// 全霊斬りのSEのパス
#define PathSEMPCharge		".\\Sound\\Sound_Effect_Lab\\Cute_Sparkling2.mp3"			// 魔力補給のSEのパス
#define PathSEGatherEnergy	".\\Sound\\Sound_Effect_Lab\\Magic_Enhance_Status1.mp3"		// 気合のSEのパス

extern Sounds SE_MagicFire;		// ファイアのSE
extern Sounds SE_MagicIce;		// アイスのSE
extern Sounds SE_MagicThunder;	// サンダーのSE
extern Sounds SE_MagicHeal;		// ヒールのSE

extern Sounds SE_TPCharge;		// 精神統一のSE
extern Sounds SE_AllHeartSoul;	// 全霊斬りのSE
extern Sounds SE_MPCharge;		// 魔力補給のSE
extern Sounds SE_GatherEnergy;	// 気合のSE


/* +++ ドラゴンの技のSE +++ */
#define PathSEMagicPillar	".\\Sound\\Sound_Effect_Lab\\Beam_Cannon3.mp3"			// ピラーのSEのパス
#define PathSEMagicFung		".\\Sound\\Sound_Effect_Lab\\Special_Move.mp3"			// ファングのSEのパス
#define PathSEMagicRecover	".\\Sound\\Sound_Effect_Lab\\Magic_Heal_Status2.mp3"	// リカバーのSEのパス

#define PathSECurseBreath		".\\Sound\\Sound_Effect_Lab\\Dragon_Fire.mp3"		// 呪いの息のSEのパス
#define PathSEImmortalScale		".\\Sound\\Sound_Effect_Lab\\Menu1.mp3"				// 竜仙鱗のSEのパス
#define PathSEDestructBreath	".\\Sound\\Sound_Effect_Lab\\Energy_Blast1.mp3"		// 破壊の息のSEのパス
#define PathSEAbsorbAtmosphere	".\\Sound\\Sound_Effect_Lab\\Magic_HPabsorb1.mp3"	// 大気吸収のSEのパス

extern Sounds SE_MagicPillar;	// ピラーのSE
extern Sounds SE_MagicFung;		// ファングのSE
extern Sounds SE_MagicRecover;	// リカバーのSE

extern Sounds SE_CurseBreath;		// 呪いの息のSE
extern Sounds SE_ImmortalScale;		// 竜仙鱗のSE
extern Sounds SE_DestructBreath;	// 破壊の息のSE
extern Sounds SE_AbsorbAtmosphere;	// 大気吸収のSE


/* +++ ダイトメアの技のSE +++ */
#define PathSEMagicSaros1	".\\Sound\\Sound_Effect_Lab\\Charge_Beam.mp3"			// サロスのSE1のパス
#define PathSEMagicSaros2	".\\Sound\\Sound_Effect_Lab\\Beam_Cannon2.mp3"			// サロスのSE2のパス
#define PathSEMagicDeus		".\\Sound\\OtoLogic\\Magic2-3.mp3"						// デウスのSEのパス
#define PathSEMagicEx		".\\Sound\\Sound_Effect_Lab\\Robot_Conbination1.mp3"	// エクスのSEのパス
#define PathSEMagicMachina  ".\\Sound\\OtoLogic\\Shortbridge29-2.mp3"				// マキナのSEのパス

#define PathSEImseti		".\\Sound\\Sound_Effect_Lab\\Sword_Cut4.mp3"		// イムセトのSEのパス
#define PathSEHarpy			".\\Sound\\Sound_Effect_Lab\\Magic_Thunder2.mp3"	// ハーピのSEのパス
#define PathSEKebehsenuev	".\\Sound\\Sound_Effect_Lab\\Pterosaur_Roar2.mp3"	// ケベフスのSEのパス
#define PathSEDuamtef1		".\\Sound\\Sound_Effect_Lab\\Sword_Cut3.mp3"		// ドゥアムタのSE1のパス
#define PathSEDuamtef2		".\\Sound\\Sound_Effect_Lab\\Magic_Ice3.mp3"		// ドゥアムタのSE2のパス
#define PathSEDuamtef3		".\\Sound\\Sound_Effect_Lab\\Magic_Fire2.mp3"		// ドゥアムタのSE3のパス

extern Sounds SE_MagicSaros1;	// サロスのSE1
extern Sounds SE_MagicSaros2;	// サロスのSE2
extern Sounds SE_MagicDeus;		// デウスのSE
extern Sounds SE_MagicEx;		// エクスのSE
extern Sounds SE_MagicMachina;	// マキナのSE

extern Sounds SE_Imseti;		// イムセトのSE
extern Sounds SE_Harpy;			// ハーピのSE
extern Sounds SE_Kebehsenuev;	// ケベフスのSE
extern Sounds SE_Duamtef1;		// ドゥアムタのSE1
extern Sounds SE_Duamtef2;		// ドゥアムタのSE2
extern Sounds SE_Duamtef3;		// ドゥアムタのSE3


/* +++ キューの技のSE +++ */
#define PathSEMagicTentativeDark	".\\Sound\\OtoLogic\\Magic_Down1.mp3"			// ダーク(仮)のSEのパス
#define PathSEMagicTentativeLight	".\\Sound\\Sound_Effect_Lab\\Magic_Ice3.mp3"	// ライト(仮)のSEのパス
#define PathSEMagicTentativeHeal	".\\Sound\\Sound_Effect_Lab\\Magic_Heal1.mp3"	// ヒール(仮)のSEのパス
#define PathSEMagicTentativeRock	".\\Sound\\Sound_Effect_Lab\\Explode4.mp3"		// ロック(仮)のSEのパス

#define PathSETentativeThunder		".\\Sound\\Sound_Effect_Lab\\Magic_Thunder1.mp3"	// 雷刃(仮)のSEのパス
#define PathSETentativePoison		".\\Sound\\Sound_Effect_Lab\\Impact7.mp3"			// 毒刃(仮)のSEのパス
#define PathSETentativeStance		".\\Sound\\Sound_Effect_Lab\\Magic_Gravity1.mp3"	// 構え(仮)のSEのパス
#define PathSETentativeSevereBlow	".\\Sound\\Sound_Effect_Lab\\Heavy_Kick1.mp3"		// 痛打(仮)のSEのパス

extern Sounds SE_MagicTentativeDark;	// ダーク(仮)のSE
extern Sounds SE_MagicTentativeLight;	// ライト(仮)のSE
extern Sounds SE_MagicTentativeHeal;	// ヒール(仮)のSE
extern Sounds SE_MagicTentativeRock;	// ロック(仮)のSE

extern Sounds SE_TentativeThunder;		// 雷刃(仮)のSE
extern Sounds SE_TentativePoison;		// 毒刃(仮)のSE
extern Sounds SE_TentativeStance;		// 構え(仮)のSE
extern Sounds SE_TentativeSevereBlow;	// 痛打(仮)のSE


/* +++ sheppの技のSE +++ */
#define PathSEMagicMu		".\\Sound\\Sound_Effect_Lab\\Robot_Activation1.mp3"		// μのSEのパス
#define PathSEMagicNu		".\\Sound\\Sound_Effect_Lab\\Robot_Activation2.mp3"		// νのSEのパス
#define PathSEMagicLambda	".\\Sound\\Sound_Effect_Lab\\Aura2.mp3"					// ΛのSEのパス
#define PathSEMagicXi		".\\Sound\\Sound_Effect_Lab\\DJ_Scratch2.mp3"			// ξのSEのパス

#define PathSEPsi		".\\Sound\\Sound_Effect_Lab\\KO.mp3"				// ψのSEのパス
#define PathSEOmega		".\\Sound\\OtoLogic\\Magic_Up1.mp3"					// ΩのSEのパス
#define PathSESigma		".\\Sound\\Sound_Effect_Lab\\Magic_Holy.mp3"		// ΣのSEのパス
#define PathSEEta		".\\Sound\\Sound_Effect_Lab\\Energy_Blast2.mp3"		// ηのSEのパス

extern Sounds SE_MagicMu;		// μのSE
extern Sounds SE_MagicNu;		// νのSE
extern Sounds SE_MagicLambda;	// ΛのSE
extern Sounds SE_MagicXi;		// ξのSE

extern Sounds SE_Psi;	// ψのSE
extern Sounds SE_Omega;	// ΩのSE
extern Sounds SE_Sigma;	// ΣのSE
extern Sounds SE_Eta;	// ηのSE


extern int Sound_Init(void);	// サウンドの初期化関数
extern void Sound_End(void);	// サウンドの終了処理を行う関数

extern Sounds Sound_Load(const char* path, int volume, int playType);	// 読み込み
extern void Sound_Play(Sounds sound);									// 再生
extern void Sound_Pause(Sounds *sound);									// 一時停止
extern void Sound_Stop(Sounds *sound);									// 停止
extern void Sound_Delete(Sounds sound);									// 削除

void ChangeSoundVolume(Sounds *sound, int volume);	// 音量変更
