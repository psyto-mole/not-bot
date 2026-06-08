/* === キャラクター関連のソースファイル === */

#include "Character.h"
#include "GameManager.h"
#include "Geometry.h"
#include "Color.h"
#include "Font.h"
#include "Key.h"
#include "Mouse.h"
#include "Message.h"
#include "Sound.h"
#include "BattleScene.h"
#include "GameOver.h"

int enemyKindNumber;	// 敵キャラの種類を保持する変数
int playerKindNumber;	// 自キャラの種類を保持する変数

Character* Player, * Enemy;		// キャラクタークラスのポインタ変数

/* --- アクションフラグをfalseにする関数 --- */
void ActionFlagFalse()
{
	Player->MyActionFlagFalse();	// プレイヤーのアクションフラグをfalseにする
	Enemy->MyActionFlagFalse();		// 敵キャラのアクションフラグをfalseにする

	return;
}

/* --- 先制行動フラグをfalseにする --- */
void PreemptiveFalse()
{
	Player->MyPreemptiveFalse();	// プレイヤーの先制行動フラグをfalseにする
	Enemy->MyPreemptiveFalse();		// 敵キャラの先制行動フラグをfalseにする
}

// 敵キャラと自キャラの識別番号を表示する関数
void DrawPlayerEnemyNum()
{
	DrawFormatStringToHandleAlign(0, 0, FAlign_Left, Color_Green, MSMincho_30_1, "Plyer Num: %d", playerKindNumber);
	DrawFormatStringToHandleAlign(0, 30, FAlign_Left, Color_Purple, MSMincho_30_1, "Enemy Num: %d", enemyKindNumber);

	return;
}


/* --- ダメージの計算関数 --- */
void Character::Damage_Calc(int attackValue, Context context)
{
	int calcResult;		// 計算結果を格納するローカル変数
	
	calcResult = attackValue + GetRand((int)(attackValue / 10));	// 引数のダメージ量の10分の1を最大値として乱数を加算

	switch (context)
	{
	case Physical:
		/* +++ 物理攻撃の場合 +++ */

		calcResult = (int)(calcResult - (Defence / 2));
		break;
	case Magical:
		/* +++ 魔法攻撃の場合 +++ */

		calcResult = (int)(calcResult - (Prevent / 4));
		break;
	case Breath:
		/* +++ ブレス攻撃の場合 +++ */

	default:
		break;
	}

	if (calcResult < 0)
	{
		calcResult = 0;
	}

	calcResult = (int)(calcResult * defenceCoefficient);

	HP_Calc(calcResult, ISDAMAGE, false);	// 計算結果を引数としてHP計算関数を実行

	return;
}

/* --- 最大HPの増減関数 --- */
void Character::MaxHP_Calc(int Value, bool isEnhance)
{
	/* +++ 最大HP増減の計算 +++ */
	if (isEnhance)	// ダメージの場合
	{
		MaxHP = MaxHP + Value;	// 最大HPを変化量分だけ増加させる

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName,PhraseMaxHP, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseMaxHP, Value, EnhanceStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%d%s", Players, characterName, PhraseMaxHP, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%d%s", Enemys, characterName, PhraseMaxHP, Value, EnhanceStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%d%s", Players, characterName, PhraseMaxHP, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%d%s", Enemys, characterName, PhraseMaxHP, Value, EnhanceStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%d%s", Players, characterName, PhraseMaxHP, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%d%s", Enemys, characterName, PhraseMaxHP, Value, EnhanceStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}
	else
	{
		MaxHP = MaxHP - Value;	// 最大HPを変化量分だけ減少させる

		/* +++ HPが最大HPを超えたら最大HPに揃える +++ */
		if (HP >= MaxHP)
		{
			HP = MaxHP;
		}

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseMaxHP, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseMaxHP, Value, ReductionStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%d%s", Players, characterName, PhraseMaxHP, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%d%s", Enemys, characterName, PhraseMaxHP, Value, ReductionStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%d%s", Players, characterName, PhraseMaxHP, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%d%s", Enemys, characterName, PhraseMaxHP, Value, ReductionStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%d%s", Players, characterName, PhraseMaxHP, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%d%s", Enemys, characterName, PhraseMaxHP, Value, ReductionStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}

	return;
}

/* --- HPの計算関数(引数は変化量と変化の種類) --- */
void Character::HP_Calc(int Value, bool isDamage, bool isPoisoning)
{
	/* +++ HP増減の計算 +++ */
	if (isDamage)	// ダメージの場合
	{
		HP = HP - Value;	// HPを変化量分だけ減少させる

		/* +++ HPが0以下になったら0にする +++ */
		if (HP <= 0)
		{
			HP = 0;
		}

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				if (isPoisoning)
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%s%d%s", PhrasePoisoning, Players, characterName, ParticleHA, Value, TakeDamage);
				}
				else
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, ParticleHA, Value, TakeDamage);
				}
			}
			else
			{
				if (isPoisoning)
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%s%d%s", PhrasePoisoning, Enemys, characterName, ParticleHA, Value, TakeDamage);
				}
				else
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, ParticleHA, Value, TakeDamage);
				}
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				if (isPoisoning)
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%s%d%s", PhrasePoisoning, Players, characterName, ParticleHA, Value, TakeDamage);
				}
				else
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%d%s", Players, characterName, ParticleHA, Value, TakeDamage);
				}
			}
			else
			{
				if (isPoisoning)
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%s%d%s", PhrasePoisoning, Enemys, characterName, ParticleHA, Value, TakeDamage);
				}
				else
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%d%s", Enemys, characterName, ParticleHA, Value, TakeDamage);
				}
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				if (isPoisoning)
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%s%d%s", PhrasePoisoning, Players, characterName, ParticleHA, Value, TakeDamage);
				}
				else
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%d%s", Players, characterName, ParticleHA, Value, TakeDamage);
				}
			}
			else
			{
				if (isPoisoning)
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%s%d%s", PhrasePoisoning, Enemys, characterName, ParticleHA, Value, TakeDamage);
				}
				else
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%d%s", Enemys, characterName, ParticleHA, Value, TakeDamage);
				}
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				if (isPoisoning)
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%s%d%s", PhrasePoisoning, Players, characterName, ParticleHA, Value, TakeDamage);
				}
				else
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%d%s", Players, characterName, ParticleHA, Value, TakeDamage);
				}
			}
			else
			{
				if (isPoisoning)
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%s%d%s", PhrasePoisoning, Enemys, characterName, ParticleHA, Value, TakeDamage);
				}
				else
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%d%s", Enemys, characterName, ParticleHA, Value, TakeDamage);
				}
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}
	else
	{
		HP = HP + Value;	// HPを変化量分だけ増加させる

		/* +++ HPが最大HPを超えたら最大HPに揃える +++ */
		if (HP >= MaxHP)
		{
			HP = MaxHP;
		}

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseHP, Value, HealStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseHP, Value, HealStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseHP, Value, HealStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseHP, Value, HealStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseHP, Value, HealStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseHP, Value, HealStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseHP, Value, HealStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseHP, Value, HealStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}

	return;
}

/* --- MPの計算関数(引数は変化量と変化の種類) --- */
void Character::MP_Calc(int Value, bool isEnhance)
{
	/* +++ MPの増減の計算 +++ */
	if (isEnhance)	// 増加の場合
	{
		MP = MP + Value;	// 変化量分だけMPを増加させる

		/* +++ 最大MPを超えたなら +++ */
		if (MP >= MaxMP)
		{
			MP = MaxMP;		// 最大MPに揃える
		}
	}
	else			// 減少の場合
	{
		MP = MP - Value;	// 変化量分だけMPを減少させる

		/* +++ MPが0以下になったら +++ */
		if (MP <= 0)
		{
			MP = 0;		// MPを0にする
		}
	}

	return;
}

/* --- TPの計算関数(引数は変化量と変化の種類) --- */
void Character::TP_Calc(int Value, bool isEnhance, bool isDisplay)
{
	/* +++ TPの増減の計算 +++ */
	if (isEnhance)	// 増加の場合
	{
		TP = TP + Value;	// 変化量分だけTPを増加させる

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseTP, Value, HealStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseTP, Value, HealStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseTP, Value, HealStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseTP, Value, HealStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseTP, Value, HealStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseTP, Value, HealStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseTP, Value, HealStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseTP, Value, HealStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}
	else			// 減少の場合
	{
		TP = TP - Value;	// 変化量分だけTPを減少させる

		/* +++ TPが0以下になったら +++ */
		if (TP <= 0)
		{
			TP = 0;		// TPを0にする
		}

		if (isDisplay)
		{
			switch (settingMessagePattern)
			{
			case Message1Line:

				if (isPlayer)
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseTP, Value, ReductionStatus);
				}
				else
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseTP, Value, ReductionStatus);
				}

				settingMessagePattern = Message2Line;
				displayMessagePattern = Message1Line;
				break;
			case Message2Line:

				if (isPlayer)
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%d%s", Players, characterName, PhraseTP, Value, ReductionStatus);
				}
				else
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%d%s", Enemys, characterName, PhraseTP, Value, ReductionStatus);
				}

				settingMessagePattern = Message3Line;
				displayMessagePattern = Message2Line;
				break;
			case Message3Line:

				if (isPlayer)
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%d%s", Players, characterName, PhraseTP, Value, ReductionStatus);
				}
				else
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%d%s", Enemys, characterName, PhraseTP, Value, ReductionStatus);
				}

				settingMessagePattern = Message4Line;
				displayMessagePattern = Message3Line;
				break;
			case Message4Line:

				if (isPlayer)
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%d%s", Players, characterName, PhraseTP, Value, ReductionStatus);
				}
				else
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%d%s", Enemys, characterName, PhraseTP, Value, ReductionStatus);
				}

				settingMessagePattern = Message1Line;
				displayMessagePattern = Message4Line;
				break;
			default:
				break;
			}
		}
	}

	return;
}

/* --- 攻撃力の計算関数(引数は変化量と変化の種類) --- */
void Character::Attack_Calc(int Value, bool isEnhance)
{
	/* +++ 攻撃力の増減の計算 +++ */
	if (isEnhance)	// 増加の場合
	{
		Attack = Attack + Value;	// 変化量分だけ攻撃力を増加させる

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseAttack, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseAttack, Value, EnhanceStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseAttack, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseAttack, Value, EnhanceStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseAttack, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseAttack, Value, EnhanceStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseAttack, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseAttack, Value, EnhanceStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}
	else			// 減少の場合
	{
		Attack = Attack - Value;	// 変化量分だけ攻撃力を減少させる

		/* +++ 攻撃力が0以下になったら +++ */
		if (Attack <= 0)
		{
			Attack = 0;		// 攻撃力を0にする
		}

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseAttack, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseAttack, Value, ReductionStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseAttack, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseAttack, Value, ReductionStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseAttack, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseAttack, Value, ReductionStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseAttack, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseAttack, Value, ReductionStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}

	return;
}

/* --- 守備力の計算関数(引数は変化量と変化の種類) --- */
void Character::Defence_Calc(int Value, bool isEnhance)
{
	/* +++ Defenceの増減の計算 +++ */
	if (isEnhance)	// 増加の場合
	{
		Defence = Defence + Value;	// 変化量分だけDefenceを増加させる

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseDefence, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseDefence, Value, EnhanceStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseDefence, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseDefence, Value, EnhanceStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseDefence, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseDefence, Value, EnhanceStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseDefence, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseDefence, Value, EnhanceStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}
	else			// 減少の場合
	{
		Defence = Defence - Value;	// 変化量分だけDefenceを減少させる

		/* +++ Defenceが0以下になったら +++ */
		if (Defence <= 0)
		{
			Defence = 0;		// Defenceを0にする
		}

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseDefence, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseDefence, Value, ReductionStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseDefence, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseDefence, Value, ReductionStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseDefence, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseDefence, Value, ReductionStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseDefence, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseDefence, Value, ReductionStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}

	return;
}

/* --- 魔力の計算関数(引数は変化量と変化の種類) --- */
void Character::Magic_Calc(int Value, bool isEnhance)
{
	/* +++ Magicの増減の計算 +++ */
	if (isEnhance)	// 増加の場合
	{
		Magic = Magic + Value;	// 変化量分だけMagicを増加させる

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseMagic, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseMagic, Value, EnhanceStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseMagic, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseMagic, Value, EnhanceStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseMagic, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseMagic, Value, EnhanceStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseMagic, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseMagic, Value, EnhanceStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}
	else			// 減少の場合
	{
		Magic = Magic - Value;	// 変化量分だけMagicを減少させる

		/* +++ Magicが0以下になったら +++ */
		if (Magic <= 0)
		{
			Magic = 0;		// Magicを0にする
		}

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseMagic, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseMagic, Value, ReductionStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseMagic, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseMagic, Value, ReductionStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseMagic, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseMagic, Value, ReductionStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseMagic, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseMagic, Value, ReductionStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}

	return;
}

/* --- 魔防の計算関数(引数は変化量と変化の種類) --- */
void Character::Prevent_Calc(int Value, bool isEnhance)
{
	/* +++ Preventの増減の計算 +++ */
	if (isEnhance)	// 増加の場合
	{
		Prevent = Prevent + Value;	// 変化量分だけPreventを増加させる

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhrasePrevent, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhrasePrevent, Value, EnhanceStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhrasePrevent, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhrasePrevent, Value, EnhanceStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhrasePrevent, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhrasePrevent, Value, EnhanceStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhrasePrevent, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhrasePrevent, Value, EnhanceStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}
	else			// 減少の場合
	{
		Prevent = Prevent - Value;	// 変化量分だけPreventを減少させる

		/* +++ Preventが0以下になったら +++ */
		if (Prevent <= 0)
		{
			Prevent = 0;		// Preventを0にする
		}

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhrasePrevent, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhrasePrevent, Value, ReductionStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhrasePrevent, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhrasePrevent, Value, ReductionStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhrasePrevent, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhrasePrevent, Value, ReductionStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhrasePrevent, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhrasePrevent, Value, ReductionStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}

	return;
}

/* --- 速さの計算関数(引数は変化量と変化の種類) --- */
void Character::Speed_Calc(int Value, bool isEnhance)
{
	/* +++ Speedの増減の計算 +++ */
	if (isEnhance)	// 増加の場合
	{
		Speed = Speed + Value;	// 変化量分だけSpeedを増加させる

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseSpeed, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseSpeed, Value, EnhanceStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseSpeed, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseSpeed, Value, EnhanceStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseSpeed, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseSpeed, Value, EnhanceStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseSpeed, Value, EnhanceStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseSpeed, Value, EnhanceStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}
	else			// 減少の場合
	{
		Speed = Speed - Value;	// 変化量分だけSpeedを減少させる

		/* +++ Speedが0以下になったら +++ */
		if (Speed <= 0)
		{
			Speed = 0;		// Speedを0にする
		}

		switch (settingMessagePattern)
		{
		case Message1Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseSpeed, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseSpeed, Value, ReductionStatus);
			}

			settingMessagePattern = Message2Line;
			displayMessagePattern = Message1Line;
			break;
		case Message2Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseSpeed, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseSpeed, Value, ReductionStatus);
			}

			settingMessagePattern = Message3Line;
			displayMessagePattern = Message2Line;
			break;
		case Message3Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseSpeed, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseSpeed, Value, ReductionStatus);
			}

			settingMessagePattern = Message4Line;
			displayMessagePattern = Message3Line;
			break;
		case Message4Line:

			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Players, characterName, PhraseSpeed, Value, ReductionStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage1), "%s%s%s%d%s", Enemys, characterName, PhraseSpeed, Value, ReductionStatus);
			}

			settingMessagePattern = Message1Line;
			displayMessagePattern = Message4Line;
			break;
		default:
			break;
		}
	}

	return;
}

/* --- 自身のHPを取得する --- */
int Character::GetMyHP()
{
	return HP;	// 自身のHPを返す
}

/* --- 自身のMPを取得する --- */
int Character::GetMyMP()
{
	return MP;	// 自身のMPを返す
}

/* --- 自身のTPを取得する --- */
int Character::GetMyTP()
{
	return TP;	// 自身のTPを返す
}

/* --- 自身の攻撃力を取得する ---*/
int Character::GetMyAttack()
{
	return Attack;	// 自身のAttackを返す
}

/* --- 自身の守備力を取得する --- */
int Character::GetMyDefence()
{
	return Defence;	// 自身のDefenceを返す
}

/* --- 自身の魔力を取得する --- */
int Character::GetMyMagic()
{
	return Magic;	// 自身のMagicを返す
}

/* --- 自身の魔防を取得する --- */
int Character::GetMyPrevent()
{
	return Prevent;	// 自身のPreventを返す
}

/* --- 自身の速さを取得する --- */
int Character::GetMySpeed()
{
	return Speed;	// 自身のSpeedを返す
}

/* --- 自身のアクションフラグを取得する --- */
bool Character::GetMyActionFlag()
{
	return actionFlag;	// 自身のアクションフラグを返す
}

/* --- 自身のアクションフラグをtrueにする --- */
void Character::MyActionFlagTrue()
{
	actionFlag = true;	// アクションフラグをtrueにする

	return;
}

/* --- 自身のアクションフラグをfalseにする --- */
void Character::MyActionFlagFalse()
{
	actionFlag = false;		// アクションフラグをfalseにする

	return;
}

/* --- 先制攻撃か否かを取得 --- */
bool Character::GetMyAttackPreemptive()
{
	return attackPreemptive;	// 先制攻撃フラグを返す
}

/* --- 先制防御かを取得 --- */
bool Character::GetMyDefencePreemptive()
{
	return defencePreemptive;	// 先制防御フラグを返す
}

/* --- 先制攻撃フラグをtrueにする --- */
void Character::MyAttackPreemptiveTrue()
{
	attackPreemptive = true;	// 先制攻撃フラグをtrueにする

	return;
}

/* --- 先制防御フラグをfalseにする --- */
void Character::MyDefencePreemptiveTrue()
{
	defencePreemptive = true;	// 先制防御フラグをtrueにする

	return;
}

/* --- 2種類の先制行動フラグをfalseにする --- */
void Character::MyPreemptiveFalse()
{
	attackPreemptive = false;		// 先制攻撃フラグをfalseにする
	defencePreemptive = false;		// 先制防御フラグをfalseにする

	return;
}

/* --- 自身の属性(プレイヤーキャラか敵キャラか)を取得する --- */
bool Character::GetMyCharacterAttribute()
{
	return isPlayer;
}

void Character::DrawActionNumber(int x,int y, unsigned int color,int fontHandle)
{
	if (defencePreemptive)
	{
		if (attackPreemptive)
		{
			DrawFormatStringToHandle(x, y, color, fontHandle, "Act: %d Coe: %f DPreem: True APreem: True", actionNumber, defenceCoefficient);
		}
		else
		{
			DrawFormatStringToHandle(x, y, color, fontHandle, "Act: %d Coe: %f DPreem: True APreem: False", actionNumber, defenceCoefficient);
		}
	}
	else
	{
		if (attackPreemptive)
		{
			DrawFormatStringToHandle(x, y, color, fontHandle, "Act: %d Coe: %f DPreem: False APreem: True", actionNumber, defenceCoefficient);
		}
		else
		{
			DrawFormatStringToHandle(x, y, color, fontHandle, "Act: %d Coe: %f DPreem: False APreem: False", actionNumber, defenceCoefficient);
		}
	}

	return;
}

/* --- キャラクターのステータスUIを表示する関数 --- */
void Character:: DrawStatusUI(bool isPlayer)
{
	if (isPlayer)	// プレイヤーキャラなら
	{
		/* +++ 自キャラのステータスのUI表示 +++ */
		DrawBoxOnPoint(GameWindowWidth / 2 - 150, 90, 240, 180, Color_White, false, 5);		// UIを表示するボックスを描画
		DrawBoxOnPoint(GameWindowWidth / 2 - 150, 25, 240, 50, Color_White, false, 5);		// 名前を表示するボックスを描画
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 150, 25, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", characterName);	// キャラクターの名前を描画
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 210, 60, FAlign_Left, Color_White, MSMincho_30_1, "%s%d", StatusHP, HP);		// 自身のHPを描画
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 210, 90, FAlign_Left, Color_White, MSMincho_30_1, "%s%d", StatusMP, MP);		// 自身のMPを描画
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 210, 120, FAlign_Left, Color_White, MSMincho_30_1, "%s%d", StatusTP, TP);		// 自身のTPを描画
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 210, 150, FAlign_Left, Color_White, MSMincho_30_1, "Any: %d", 0);
	}
	else	// 敵キャラなら
	{
		/* +++ 相手キャラのステータスのUI表示 +++ */
		DrawBoxOnPoint(GameWindowWidth / 2 + 150, 90, 240, 180, Color_White, false, 5);		// UIを表示するボックスを描画
		DrawBoxOnPoint(GameWindowWidth / 2 + 150, 25, 240, 50, Color_White, false, 5);		// 名前を表示するボックスを描画
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 150, 25, FAlign_AllCenter, Color_White, MSMincho_30_1, "%s", characterName);	// キャラクターの名前を描画
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 90, 60, FAlign_Left, Color_White, MSMincho_30_1, "%s%d", StatusHP, HP);			// 自身のHPを描画
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 90, 90, FAlign_Left, Color_White, MSMincho_30_1, "%s%d", StatusMP, MP);			// 自身のMPを描画
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 90, 120, FAlign_Left, Color_White, MSMincho_30_1, "%s%d", StatusTP, TP);		// 自身のTPを描画
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 90, 150, FAlign_Left, Color_White, MSMincho_30_1, "Any: %d", 0);
	}
}

/* --- 「戻る」ボタンを描画する関数 --- */
void Character::DrawBackBottun()
{
	if (CollisionRectToPoint(backButton, nowMousePoint))	// 「戻る」ボタンとマウスカーソルが接触している
	{
		DrawRect(backButton, Color_White, true, 3);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 890, 1065, FAlign_AllCenter, Color_Black, MSMincho_20_1, "%s", BackButtonText);
	}
	else
	{
		DrawRect(backButton, Color_White, false, 3);
		DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 890, 1065, FAlign_AllCenter, Color_White, MSMincho_20_1, "%s", BackButtonText);
	}

	return;
}

/* --- 通常攻撃 --- */
void Character::NormalAttack()
{
	displayMessagePattern = Message2Line;
	settingMessagePattern = Message2Line;

	if (isPlayer)	// プレイヤーキャラなら
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s",Players, characterName, ActionNormalAttack);
		Enemy->Damage_Calc(Attack, Physical);		// 自身の攻撃力を引数に敵キャラのダメージ計算関数を実行
	}
	else	// 敵キャラなら
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionNormalAttack);
		Player->Damage_Calc(Attack, Physical);	// 自身の攻撃力を引数にプレイヤーキャラのダメージ計算関数を実行
	}

	Sound_Play(SE_NormalAttack);

	return;
}

/* --- 防御 --- */
void Character::NormalDefence()
{
	defenceCoefficient = 0.5;

	if (isPlayer)
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionNormalDefence);
	}
	else
	{
		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionNormalDefence);
	}

	displayMessagePattern = Message1Line;

	Sound_Play(SE_NormalDefence);

	return;
}

/* --- 命中したかを判定する関数 --- */
bool Character::Judge_Hit(int hitProbability)
{
	int actionRandomNumber;

	actionRandomNumber = GetRand(99) + 1;	// 1～100までの乱数を生成

	if (actionRandomNumber <= hitProbability)	// 命中確率の大きさが乱数以上なら
	{
		return true;	// 命中(trueを返す)
	}
	else
	{
		return false;	// 失敗(falseを返す)
	}
}

/* --- 状態異常からの復帰を確認する --- */
void Character::Check_Status()
{
	if (statusAilment != Fine)	// 状態異常になっているなら
	{
		if (statusAilment == Protection)	// 「保護」状態なら
		{
			ailmentTurn -= 1;	// 状態異常の継続ターンを1減らす
		}

		if (ailmentTurn <= 0)	// 状態異常の継続ターンが0以下なら
		{
			Become_Fine(false);		// 状態を「状態異常なし」に設定する(毒は回復しない)
		}
	}

	return;
}

/* --- 自身の状態を「状態異常なし」にする --- */
void Character::Become_Fine(bool healPoison)
{
	if (healPoison)		// 「毒」を回復するなら
	{
		ailmentPoisoning = false;	// 「毒」状態を解除
	}

	if (ailmentPoisoning)	// 「毒」状態なら
	{
		/* +++ 状態によって処理を変える +++ */
		switch (statusAilment)
		{
		case Paralysis:
			/* +++ 「マヒ」なら +++ */

			/* +++ 文章を設定する行数によって処理を変える +++ */
			switch (settingMessagePattern)
			{
			case Message1Line:
				/* +++ 1行目なら +++ */

				/* +++ 1行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishParalysis);
				}
				else
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishParalysis);
				}

				settingMessagePattern = Message2Line;	// 次に文章を設定する行を2行目に設定
				displayMessagePattern = Message1Line;	// 表示する行数を1行に設定
				break;
			case Message2Line:
				/* +++ 2行目なら +++ */

				/* +++ 2行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishParalysis);
				}
				else
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishParalysis);
				}

				settingMessagePattern = Message3Line;	// 次に文章を設定する行を3行目に設定
				displayMessagePattern = Message2Line;	// 表示する行数を2行に設定
				break;
			case Message3Line:
				/* +++ 3行目なら +++ */

				/* +++ 3行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishParalysis);
				}
				else
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishParalysis);
				}

				settingMessagePattern = Message4Line;	// 次に文章を設定する行を4行目に設定
				displayMessagePattern = Message3Line;	// 表示する行数を3行に設定
				break;
			case Message4Line:
				/* +++ 4行目なら +++ */

				/* +++ 4行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishParalysis);
				}
				else
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishParalysis);
				}

				settingMessagePattern = Message1Line;	// 次に文章を設定する行を1行目に設定
				displayMessagePattern = Message4Line;	// 表示する行数を4行に設定
				break;
			default:
				break;
			}

			break;
		case Silence:
			/* +++ 「沈黙」なら +++ */

			/* +++ 文章を設定する行数によって処理を変える +++ */
			switch (settingMessagePattern)
			{
			case Message1Line:
				/* +++ 1行目なら +++ */

				/* +++ 1行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishSilence);
				}
				else
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishSilence);
				}

				settingMessagePattern = Message2Line;	// 次に文章を設定する行を2行目に設定
				displayMessagePattern = Message1Line;	// 表示する行数を1行に設定
				break;
			case Message2Line:
				/* +++ 2行目なら +++ */

				/* +++ 2行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishSilence);
				}
				else
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishSilence);
				}

				settingMessagePattern = Message3Line;	// 次に文章を設定する行を3行目に設定
				displayMessagePattern = Message2Line;	// 表示する行数を2行に設定
				break;
			case Message3Line:
				/* +++ 3行目なら +++ */

				/* +++ 3行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishSilence);
				}
				else
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishSilence);
				}

				settingMessagePattern = Message4Line;	// 次に文章を設定する行を4行目に設定
				displayMessagePattern = Message3Line;	// 表示する行数を3行に設定
				break;
			case Message4Line:
				/* +++ 4行目なら +++ */

				/* +++ 4行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishSilence);
				}
				else
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishSilence);
				}

				settingMessagePattern = Message1Line;	// 次に文章を設定する行を1行目に設定
				displayMessagePattern = Message4Line;	// 表示する行数を4行に設定
				break;
			default:
				break;
			}
			
			break;
		case Slump:
			/* +++ 「不調」なら +++ */

			/* +++ 文章を設定する行数によって処理を変える +++ */
			switch (settingMessagePattern)
			{
			case Message1Line:
				/* +++ 1行目なら +++ */

				/* +++ 1行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishSlump);
				}
				else
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishSlump);
				}

				settingMessagePattern = Message2Line;	// 次に文章を設定する行を2行目に設定
				displayMessagePattern = Message1Line;	// 表示する行数を1行に設定
				break;
			case Message2Line:
				/* +++ 2行目なら +++ */

				/* +++ 2行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishSlump);
				}
				else
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishSlump);
				}

				settingMessagePattern = Message3Line;	// 次に文章を設定する行を3行目に設定
				displayMessagePattern = Message2Line;	// 表示する行数を2行に設定
				break;
			case Message3Line:
				/* +++ 3行目なら +++ */

				/* +++ 3行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishSlump);
				}
				else
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishSlump);
				}

				settingMessagePattern = Message4Line;	// 次に文章を設定する行を4行目に設定
				displayMessagePattern = Message3Line;	// 表示する行数を3行に設定
				break;
			case Message4Line:
				/* +++ 4行目なら +++ */

				/* +++ 4行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishSlump);
				}
				else
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishSlump);
				}

				settingMessagePattern = Message1Line;	// 次に文章を設定する行を1行目に設定
				displayMessagePattern = Message4Line;	// 表示する行数を4行に設定
				break;
			default:
				break;
			}

			break;
		case Protection:
			/* +++ 「保護」なら +++ */

			/* +++ 文章を設定する行数によって処理を変える +++ */
			switch (settingMessagePattern)
			{
			case Message1Line:
				/* +++ 1行目なら +++ */

				/* +++ 1行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishProtection);
				}
				else
				{
					sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishProtection);
				}

				settingMessagePattern = Message2Line;	// 次に文章を設定する行を2行目に設定
				displayMessagePattern = Message1Line;	// 表示する行数を1行に設定
				break;
			case Message2Line:
				/* +++ 2行目なら +++ */

				/* +++ 2行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishProtection);
				}
				else
				{
					sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishProtection);
				}

				settingMessagePattern = Message3Line;	// 次に文章を設定する行を3行目に設定
				displayMessagePattern = Message2Line;	// 表示する行数を2行に設定
				break;
			case Message3Line:
				/* +++ 3行目なら +++ */

				/* +++ 3行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishProtection);
				}
				else
				{
					sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishProtection);
				}

				settingMessagePattern = Message4Line;	// 次に文章を設定する行を4行目に設定
				displayMessagePattern = Message3Line;	// 表示する行数を3行に設定
				break;
			case Message4Line:
				/* +++ 4行目なら +++ */

				/* +++ 4行目に文章を設定 +++ */
				if (isPlayer)
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishProtection);
				}
				else
				{
					sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishProtection);
				}

				settingMessagePattern = Message1Line;	// 次に文章を設定する行を1行目に設定
				displayMessagePattern = Message4Line;	// 表示する行数を4行に設定
				break;
			default:
				break;
			}

			break;
		default:
			break;
		}
	}
	else
	{
		/* +++ 文章を設定する行数によって処理を変える +++ */
		switch (settingMessagePattern)
		{
		case Message1Line:
			/* +++ 1行目なら +++ */

			/* +++ 1行目に文章を設定 +++ */
			if (isPlayer)
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishAllStatus);
			}
			else
			{
				sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishAllStatus);
			}

			settingMessagePattern = Message2Line;	// 次に文章を設定する行を2行目に設定
			displayMessagePattern = Message1Line;	// 表示する行数を1行に設定
			break;
		case Message2Line:
			/* +++ 2行目なら +++ */

			/* +++ 2行目に文章を設定 +++ */
			if (isPlayer)
			{
				sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishAllStatus);
			}
			else
			{
				sprintf_s(battleMessage2, sizeof(battleMessage2), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishAllStatus);
			}

			settingMessagePattern = Message3Line;	// 次に文章を設定する行を3行目に設定
			displayMessagePattern = Message2Line;	// 表示する行数を2行に設定
			break;
		case Message3Line:
			/* +++ 3行目なら +++ */

			/* +++ 3行目に文章を設定 +++ */
			if (isPlayer)
			{
				sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishAllStatus);
			}
			else
			{
				sprintf_s(battleMessage3, sizeof(battleMessage3), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishAllStatus);
			}

			settingMessagePattern = Message4Line;	// 次に文章を設定する行を4行目に設定
			displayMessagePattern = Message3Line;	// 表示する行数を3行に設定
			break;
		case Message4Line:
			/* +++ 4行目なら +++ */

			/* +++ 4行目に文章を設定 +++ */
			if (isPlayer)
			{
				sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%s", Players, characterName, ParticleHA, ActionFinishAllStatus);
			}
			else
			{
				sprintf_s(battleMessage4, sizeof(battleMessage4), "%s%s%s%s", Enemys, characterName, ParticleHA, ActionFinishAllStatus);
			}

			settingMessagePattern = Message1Line;	// 次に文章を設定する行を1行目に設定
			displayMessagePattern = Message4Line;	// 表示する行数を4行に設定
			break;
		default:
			break;
		}
	}

	statusAilment = Fine;	// 「状態異常なし」に設定
	ailmentTurn = 0;		// 状態異常の継続ターンを0に戻す

	return;
}

/* --- 自身の状態を「マヒ」にする --- */
void Character::Become_Paralyzed()
{
	if (statusAilment != Protection)	// 「保護」状態でないなら
	{
		statusAilment = Paralysis;	// 「マヒ」の状態異常を設定
		ailmentTurn = 1;			// 継続ターンに1をセット
	}

	return;
}

/* --- 自身の状態を「毒」にする --- */
void Character::Become_Poisoning()
{
	if (statusAilment != Protection)	// 「保護」状態でないなら
	{
		ailmentPoisoning = true;
	}

	return;
}

/* --- 自身の状態を「沈黙」にする --- */
void Character::Become_Silence()
{
	if (statusAilment != Protection)	// 「保護」状態でないなら
	{
		statusAilment = Silence;	// 「沈黙」の状態異常を設定
		ailmentTurn = 3;			// 継続ターンに3をセット
	}

	return;
}

/* --- 自身の状態を「不調」にする --- */
void Character::Become_Slump()
{
	if (statusAilment != Protection)	// 「保護」状態でないなら
	{
		statusAilment = Slump;	// 「不調」の状態異常を設定
		ailmentTurn = 3;		// 継続ターンに3をセット
	}

	return;
}

/* --- 自身の状態を「保護」にする --- */
void Character::Become_Protection(int continueTurn)
{
	statusAilment = Protection;		// 状態異常に「保護」を設定
	ailmentTurn = continueTurn;		// 継続ターンをセット

	if (ailmentPoisoning)	// 「毒」状態なら
	{
		ailmentPoisoning = false;	// 「毒」を回復
	}

	return;
}

/* --- 状態異常「毒」の処理 --- */
void Character::StatusProcess_Poisoning()
{
	int calcResult, nowHP;

	nowHP = GetMyHP();
	calcResult = (int)(nowHP * 0.1);

	if (ailmentPoisoning)
	{
		HP_Calc(calcResult, ISDAMAGE, true);
	}

	return;
}

/* --- バトルフェイズにおける状態異常「マヒ」の処理 --- */
void Character::StatusProcess_Paralysis()
{
	if (isPlayer)
	{
		ailmentTurn -= 1;	// 状態異常の継続ターンを1減らす

		displayMessagePattern = Message1Line;	// 表示する行数を1行に設定

		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionStatusParalysis);
	}
	else
	{
		ailmentTurn -= 1;	// 状態異常の継続ターンを1減らす

		displayMessagePattern = Message1Line;	// 表示する行数を1行に設定

		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionStatusParalysis);
	}

	return;
}

/* --- バトルフェイズにおける状態異常「沈黙」の処理 --- */
void Character::StatusProcess_Silence()
{
	if (isPlayer)
	{
		ailmentTurn -= 1;	// 状態異常の継続ターンを1減らす

		displayMessagePattern = Message1Line;	// 表示する行数を1行に設定

		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionStatusSilence);
	}
	else
	{
		ailmentTurn -= 1;	// 状態異常の継続ターンを1減らす

		displayMessagePattern = Message1Line;	// 表示する行数を1行に設定

		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionStatusSilence);
	}

	return;
}

/* --- バトルフェイズにおける状態異常「不調」の処理 --- */
void Character::StatusProcess_Slump()
{
	if (isPlayer)
	{
		ailmentTurn -= 1;	// 状態異常の継続ターンを1減らす

		displayMessagePattern = Message1Line;	// 表示する行数を1行に設定

		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Players, characterName, ActionStatusSlump);
	}
	else
	{
		ailmentTurn -= 1;	// 状態異常の継続ターンを1減らす

		displayMessagePattern = Message1Line;	// 表示する行数を1行に設定

		sprintf_s(battleMessage1, sizeof(battleMessage1), "%s%s%s", Enemys, characterName, ActionStatusSlump);
	}

	return;
}