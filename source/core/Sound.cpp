/* === サウンド処理のソースファイル === */

#include <string.h>
#include "Sound.h"

/* +++ BGM +++ */
Sounds BGM_Fake;			// 偽のタイトル画面のBGM
Sounds BGM_Title;			// タイトル画面のBGM
Sounds BGM_GameOver;		// ゲームオーバー画面のBGM
Sounds BGM_Result;			// リザルト画面のBGM
Sounds BGM_Battle;			// 対ロボットのバトル画面のBGM

/* +++ 操作関連のSE +++ */
Sounds SE_Menu;			// メニューを開くSE
Sounds SE_Click;		// クリックのSE(キャラセレクト用)
Sounds SE_Enter;		// 決定ボタンのSE(バトルシーン用)
Sounds SE_Back;			// 戻るボタンのSE(バトルシーン用)
Sounds SE_Unavilable;	// 使用不可のSE(バトルシーン用)

/* +++ 共通技のSE +++ */
Sounds SE_NormalAttack;	// 通常攻撃のSE
Sounds SE_NormalDefence;	// 通常防御のSE

/* +++ ロボットの技のSE +++ */
Sounds SE_FlameThrower1;	// 火炎放射のSE(弱版)
Sounds SE_FlameThrower2;	// 火炎放射のSE(強版)
Sounds SE_Steelization;	// 鋼鉄化のSE
Sounds SE_MagicShut;		// 魔力遮断のSE
Sounds SE_TripleBarrage;	// 三連砲撃のSE

/* +++ 勇者の技のSE +++ */
Sounds SE_MagicFire;		// ファイアのSE
Sounds SE_MagicIce;		// アイスのSE
Sounds SE_MagicThunder;  // サンダーのSE
Sounds SE_MagicHeal;		// ヒールのSE

Sounds SE_TPCharge;		// 精神統一のSE
Sounds SE_AllHeartSoul;	// 全霊斬りのSE
Sounds SE_MPCharge;		// 魔力補給のSE
Sounds SE_GatherEnergy;	// 気合のSE

/* +++ ドラゴンの技のSE +++ */
Sounds SE_MagicPillar;		// ピラーのSE
Sounds SE_MagicFung;			// ファングのSE
Sounds SE_MagicRecover;		// リカバーのSE

Sounds SE_CurseBreath;		// 呪いの息のSE
Sounds SE_ImmortalScale;		// 竜仙鱗のSE
Sounds SE_DestructBreath;	// 破壊の息のSE
Sounds SE_AbsorbAtmosphere;	// 大気吸収のSE

/* +++ sheppの技のSE +++ */
Sounds SE_MagicMu;		// μのSE
Sounds SE_MagicNu;		// νのSE
Sounds SE_MagicLambda;	// ΛのSE
Sounds SE_MagicXi;		// ξのSE

Sounds SE_Psi;		// ψのSE
Sounds SE_Omega;		// ΩのSE
Sounds SE_Sigma;		// ΣのSE
Sounds SE_Eta;		// ηのSE


/* --- 読み込み・ハンドル生成(初期化) --- */
int Sound_Init(void)
{
	/* +++ BGM +++ */
	{
		BGM_Fake = Sound_Load(PathBGMFake, VolumeQuiet, DX_PLAYTYPE_LOOP);
		if (BGM_Fake.Handle == -1)
		{
			return -1;
		}

		BGM_Title = Sound_Load(PathBGMTitle, VolumeQuiet, DX_PLAYTYPE_LOOP);
		if (BGM_Title.Handle == -1)
		{
			return -1;
		}

		BGM_GameOver = Sound_Load(PathBGMGameOver, VolumeQuiet, DX_PLAYTYPE_LOOP);
		if (BGM_GameOver.Handle == -1)
		{
			return -1;
		}

		BGM_Result = Sound_Load(PathBGMResult, VolumeLoud, DX_PLAYTYPE_LOOP);
		if (BGM_Result.Handle == -1)
		{
			return -1;
		}

		BGM_Battle = Sound_Load(PathBGMBattle, VolumeQuiet, DX_PLAYTYPE_LOOP);
		if (BGM_Battle.Handle == -1)
		{
			return -1;
		}
	}

	/* +++ 操作関連のSE +++ */
	{
		SE_Menu = Sound_Load(PathSEMenu, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_Menu.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Sound Menu",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_Click = Sound_Load(PathSEClick, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_Click.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Sound Click",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_Enter = Sound_Load(PathSEEnter, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_Enter.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Enter Selection",			// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_Back = Sound_Load(PathSEBack, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_Back.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Back Selection",			// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_Unavilable = Sound_Load(PathSEUnavilable, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_Unavilable.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Unavilable Selection",		// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}
	}

	/* +++ 共通技のSE +++ */
	{
		SE_NormalAttack = Sound_Load(PathSENormalAttack, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_NormalAttack.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Normal Attack",			// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_NormalDefence = Sound_Load(PathSENormalDefence, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_NormalDefence.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Normal Defence",			// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}
	}

	/* +++ ロボットの技のSE +++ */
	{
		SE_FlameThrower1 = Sound_Load(PathSEFlameThrower1, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_FlameThrower1.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Flame Thr 1",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_FlameThrower2 = Sound_Load(PathSEFlameThrower2, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_FlameThrower2.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Flame Thr 2",					// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_Steelization = Sound_Load(PathSESteelization, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_Steelization.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Steelization",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_MagicShut = Sound_Load(PathSEMagicShut, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MagicShut.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Magic Shut",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_TripleBarrage = Sound_Load(PathSETripleBarrage, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_TripleBarrage.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Triple Bar",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}
	}

	/* +++ 勇者の技のSE +++ */
	{
		SE_MagicFire = Sound_Load(PathSEMagicFire, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MagicFire.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"MagicFire",				// エラー内容
				"Sound Error",				// エラータイトル
					MB_OK						// OKボタンのみ表示
					);

					return -1;
		}

		SE_MagicIce = Sound_Load(PathSEMagicIce, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MagicIce.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Magic Ice",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_MagicThunder = Sound_Load(PathSEMagicThunder, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MagicThunder.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Magic Thunder",			// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_MagicHeal = Sound_Load(PathSEMagicHeal, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MagicHeal.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Magic Heal",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_TPCharge = Sound_Load(PathSETPCharge, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_TPCharge.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"TP Charge",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_AllHeartSoul = Sound_Load(PathSEAllHeartSoul, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_AllHeartSoul.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"All Heart Soul",			// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_MPCharge = Sound_Load(PathSEMPCharge, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MPCharge.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"MP Charge",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_GatherEnergy = Sound_Load(PathSEGatherEnergy, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_GatherEnergy.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Gather Energy",			// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}
	}

	/* +++ ドラゴンの技のSE +++ */
	{
		SE_MagicPillar = Sound_Load(PathSEMagicPillar, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MagicPillar.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Magic Pillar",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_MagicFung = Sound_Load(PathSEMagicFung, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MagicFung.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Magic Fung",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_MagicRecover = Sound_Load(PathSEMagicRecover, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MagicRecover.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Magic Recover",			// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_CurseBreath = Sound_Load(PathSECurseBreath, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_CurseBreath.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Curse Breath",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_ImmortalScale = Sound_Load(PathSEImmortalScale, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_ImmortalScale.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Immortal Scale",			// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_DestructBreath = Sound_Load(PathSEDestructBreath, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_DestructBreath.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Destruct Breath",			// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_AbsorbAtmosphere = Sound_Load(PathSEAbsorbAtmosphere, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_AbsorbAtmosphere.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Absorb Atmosphere",		// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}
	}

	/* +++ sheppの技のSE +++ */
	{
		SE_MagicMu = Sound_Load(PathSEMagicMu, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MagicMu.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Magic Mu",					// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_MagicNu = Sound_Load(PathSEMagicNu, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MagicNu.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Magic Nu",					// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_MagicLambda = Sound_Load(PathSEMagicLambda, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MagicLambda.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Magic Lambda",				// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_MagicXi = Sound_Load(PathSEMagicXi, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_MagicXi.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Magic Xi",					// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_Psi = Sound_Load(PathSEPsi, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_Psi.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Psi",						// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_Sigma = Sound_Load(PathSESigma, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_Sigma.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Sigma",					// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_Omega = Sound_Load(PathSEOmega, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_Omega.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Omega",					// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}

		SE_Eta = Sound_Load(PathSEEta, VolumeMax, DX_PLAYTYPE_BACK);
		if (SE_Eta.Handle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Eta",						// エラー内容
				"Sound Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return -1;
		}
	}

	return 0;
}

/* --- 後始末 --- */
void Sound_End(void)
{
	/* +++ BGM +++ */
	Sound_Delete(BGM_Fake);
	Sound_Delete(BGM_Title);
	Sound_Delete(BGM_GameOver);
	Sound_Delete(BGM_Result);
	Sound_Delete(BGM_Battle);

	/* +++ 操作関連のSE +++ */
	Sound_Delete(SE_Menu);
	Sound_Delete(SE_Click);
	Sound_Delete(SE_Enter);
	Sound_Delete(SE_Back);
	Sound_Delete(SE_Unavilable);

	/* +++ 共通技のSE +++ */
	Sound_Delete(SE_NormalAttack);
	Sound_Delete(SE_NormalDefence);

	/* +++ ロボットの技のSE +++ */
	Sound_Delete(SE_FlameThrower1);
	Sound_Delete(SE_FlameThrower2);
	Sound_Delete(SE_Steelization);
	Sound_Delete(SE_MagicShut);
	Sound_Delete(SE_TripleBarrage);

	/* +++ 勇者の技のSE +++ */
	Sound_Delete(SE_MagicFire);
	Sound_Delete(SE_MagicIce);
	Sound_Delete(SE_MagicThunder);
	Sound_Delete(SE_MagicHeal);

	Sound_Delete(SE_TPCharge);
	Sound_Delete(SE_AllHeartSoul);
	Sound_Delete(SE_MPCharge);
	Sound_Delete(SE_GatherEnergy);

	/* +++ ドラゴンの技のSE +++ */
	Sound_Delete(SE_MagicPillar);
	Sound_Delete(SE_MagicFung);
	Sound_Delete(SE_MagicRecover);

	Sound_Delete(SE_CurseBreath);
	Sound_Delete(SE_ImmortalScale);
	Sound_Delete(SE_DestructBreath);
	Sound_Delete(SE_AbsorbAtmosphere);

	/* +++ sheppの技のSE +++ */
	Sound_Delete(SE_MagicMu);
	Sound_Delete(SE_MagicNu);
	Sound_Delete(SE_MagicLambda);
	Sound_Delete(SE_MagicXi);

	Sound_Delete(SE_Psi);
	Sound_Delete(SE_Sigma);
	Sound_Delete(SE_Omega);
	Sound_Delete(SE_Eta);

	return;
}

/* --- 読み込み --- */
Sounds Sound_Load(const char* path, int volume, int playType)
{
	Sounds sound;

	// ファイルの場所をコピー
	sprintf_s(sound.Path, sizeof(sound.Path), "%s", path);

	// 音楽をメモリに読み込み
	sound.Handle = LoadSoundMem(sound.Path);

	/* === 読み込みが成功したかの確認 === */
	if (sound.Handle != -1)
	{
		/* === 正常に読み込みができたらパラメータ設定 === */
		sound.Volume = volume;						// 音量を設定
		ChangeSoundVolume(&sound, sound.Volume);	// 再生音量を設定
		sound.Playtype = playType;					// 再生形式の設定
		sound.PlayBeginning = true;					// 停止後は最初から再生する
	}

	return sound;
}

/* --- 再生 --- */
void Sound_Play(Sounds sound)
{
	switch (sound.Playtype)
	{
	case DX_PLAYTYPE_BACK:
		// 1回のみ再生(通常再生)

		// 再生
		PlaySoundMem(sound.Handle, DX_PLAYTYPE_BACK, sound.PlayBeginning);
		break;

	case DX_PLAYTYPE_LOOP:
		// ループ再生

		if (CheckSoundMem(sound.Handle) == 0)	// 再生されていないとき
		{
			// ループ再生する
			PlaySoundMem(sound.Handle, DX_PLAYTYPE_LOOP, sound.PlayBeginning);
		}

		break;

	default:
		break;
	}

	return;
}

/* --- 一時停止 --- */
void Sound_Pause(Sounds *sound)
{
	// 停止後の再生位置を今の位置にする
	sound->PlayBeginning = false;

	// 再生されているなら
	if (CheckSoundMem(sound->Handle) == 1)
	{
		// 音楽停止
		StopSoundMem(sound->Handle);

		// マスタ音量に戻す
		ChangeVolumeSoundMem(sound->Volume, sound->Handle);
	}

	return;
}

/* --- 停止 --- */
void Sound_Stop(Sounds *sound)
{
	// 停止後の再生位置は最初からにする
	sound->PlayBeginning = true;

	if (CheckSoundMem(sound->Handle) == 1)
	{
		// 音楽停止
		StopSoundMem(sound->Handle);

		// マスタ音量に戻す
		ChangeVolumeSoundMem(sound->Volume, sound->Handle);
	}

	return;
}

/* --- 削除 --- */
/* === ハンドルを渡すので引数は値渡し === */
void Sound_Delete(Sounds sound)
{
	if (sound.Handle != -1)		// 正常に読み込みができていれば
	{
		DeleteSoundMem(sound.Handle);	// メモリから削除(メモリを解放)
	}

	return;
}

/* --- 音量変更 --- */
void ChangeSoundVolume(Sounds *sound, int volume)
{
	/* === マスタ音量は変えず、再生されている音量を変更 === */
	/* ※構造体のボリュームは最大音量(マスタ音量)なので変更しない */
	if (volume <= sound->Volume) 
	{
		ChangeVolumeSoundMem(volume, sound->Handle);
	}


	return;
}