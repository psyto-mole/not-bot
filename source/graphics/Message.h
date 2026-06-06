#pragma once
/* === ゲーム中のメッセージ表示を管理するヘッダファイル === */

#include "DxLib.h"


/* === 汎用 === */
/* +++ 回答文 +++ */
#define ResponseYes	"はい"		// 回答文「はい」
#define ResponseNo	"いいえ"	// 回答文「いいえ」

/* +++ 助詞 +++ */
#define ParticleHA	"は"

/* +++ 「back」ボタン +++ */
#define BackButtonText	"戻る"	// 「戻る」ボタンのテキスト

/* +++ プレイヤー +++ */
#define NamePlayer	"プレイヤー"
#define NameEnemy	"エネミー"


/* === シーンマネージャ === */
#define FlagStatusTrue		"true"		// 「true」の文字列(デバッグ用)
#define FlagStatusFalse		"false"		// 「false」の文字列(デバッグ用)


/* === システムメニュー === */
/* +++ メニュートップ +++ */
#define OptionSystemMenuAchievement		"記録"
#define OptionSystemMenuDelete			"データ消去"
#define OptionSystemMenuEndGame			"ゲーム終了"
#define OptionSystemMenuCredit			"クレジット"
#define OptionSystemMenuBack			"戻る"

#define DetailAchievement	"これまでの討伐記録を確認します"
#define DetailDeleteData	"保存されているデータを消去します"
#define DetailGameEnd		"ゲームを終了します"
#define DetailCredit		"仕様楽曲などを表示します"
#define DetailBackMenu		"メニューを閉じゲームに戻ります"

/* +++ データ消去画面 +++ */
#define QuestionDeleteData1		"ゲームデータを消去しますか?"
#define QuestionDeleteData2		"※消去したデータは戻せません"

/* +++ ゲームの終了 +++ */
#define QuestionGameEnd		"ゲームを終了しますか?"

/* +++ クレジット +++ */
#define MusicUsed		"使用楽曲"
#define MaohDamashi		"魔王魂"
#define SoundEffectLab	"効果音ラボ"


/* === 偽のタイトル画面 === */
#define FakeTitle	"Desktop Adventure"


/* === タイトル画面 === */
#define GameTitle	"Not Bot"		// ゲームのタイトル
#define PressEnter	"Press Enter"	// Press Enterの文字列


/* === リザルト画面 === */
#define ResultTitle				"Result Scene"		// リザルト画面のタイトル
#define ResultDialogMessage		"セーブしますか?"	// セーブするかの質問文
#define ResultWinMessage		"WIN"				// 勝利タイトル


/* === ゲームオーバー画面 === */
#define GameOverTitle	"Game Over"		// ゲームオーバー画面のタイトル


/* === キャラクターセレクト画面 === */
/* +++ 質問文 +++ */
#define EnemyQuestionHead		"私は"				// 敵キャラについての質問の文章1
#define EnemyQuestionBottom		"ではありません"	// 敵キャラについての質問の文章2
#define BothQuestionNone		"名もなき存在"		// 敵、自キャラ共通の質問文
#define PlayerQuestionHead		"あなたは"			// 自キャラについての質問の文章1
#define PlayerQuestionBottom	"ですか？"			// 自キャラについての質問の文章2

/* +++ キャラクター名 +++ */
#define CharacterNameRobot		"ロボット"		// キャラクター名「ロボット」
#define CharacterNameHuman		"勇者"			// キャラクター名「勇者」
#define CharacterNameDragon		"ドラゴン"		// キャラクター名「ドラゴン」
#define CharacterNameDightmare	"ダイトメア"	// キャラクター名「ダイトメア」
#define CharacterNameNoname		"キュー(仮)"	// キャラクター名「キュー(仮)」
#define CharacterNameShepp		"Shepp"			// キャラクター名「Shepp」

/* +++ 修飾 +++ */
#define Players		"Playerの"
#define Enemys		"Enemyの"


/* === バトル画面 === */
/* +++ バトルシーンのフェイズ名 +++ */
#define BattleSceneStandby	"Standby Fase"	// スタンバイフェイズ
#define BattleSceneMain		"Main Fase"		// メインフェイズ
#define BattleSceneBattle	"Battle Fase"	// バトルフェイズ
#define BattleSceneEnd		"End Fase"		// エンドフェイズ

/* +++ バトル終了メッセージ +++ */
#define BattleEndMessage	"は倒れた"

/* +++ ステータスUI +++ */
#define StatusHP	"HP: "
#define StatusMP	"MP: "
#define StatusTP	"TP: "


/* === キャラクター === */
/* +++ 行動選択肢(共通項目) +++ */
#define OptionAttack	"攻撃"
#define OptionMagic		"魔法"
#define OptionSpecial	"特技"
#define OptionDefence	"防御"

/* +++ 選択肢の詳細(共通項目) +++ */
#define DetailOfNormalAttack	"通常攻撃を行う"
#define DetailOfMagic			"MPを消費して魔法を使う"
#define DetailOfSpecial			"TPを消費して特技を使う"
#define DetailOfNormalDefence	"身を守りダメージを半減させる"
#define DetailCantUseMagic		"は魔法が使えない"
#define DetailCantUseSpecial	"は特技が使えない"
#define DetailSealedMagic		"は魔法が封じられている"
#define DetailSealedSpecial		"は特技が封じられている"
#define DetailLackOfTP			"TPが足りない!"
#define DetailUnavilableMaxHP	"HPが最大では使えない"
#define DetailUnavilableMaxMP	"MPが最大では使えない"
#define DetailUnavilableNever	"すでに使用している"

/* +++行動の内容(共通項目)  +++ */
#define ActionNormalAttack		"の攻撃!"
#define ActionNormalDefence		"は守りを固めている"
#define ActionAttackMiss		"は攻撃を外した"
#define TakeDamage				"のダメージを受けた"
#define HealStatus				"回復した"
#define DamageStatus			"のダメージを受けた"
#define EnhanceStatus			"アップした"
#define ReductionStatus			"ダウンした"
#define PhraseMaxHP				"の最大HPが"
#define PhraseHP				"のHPが"
#define PhraseMP				"のMPが"
#define PhraseTP				"のTPが"
#define PhraseAttack			"の攻撃力が"
#define PhraseDefence			"の守備力が"
#define PhraseMagic				"の魔力が"
#define PhrasePrevent			"の魔法守備力が"
#define PhraseSpeed				"の素早さが"


/* === ロボット === */
/* +++ 技選択肢(ロボット) +++ */
#define OptionFlameThrower	"火炎放射"
#define OptionSelfRepair	"自己修復"	// いったんボツ
#define OptionSteelization	"鋼鉄化"
#define OptionMagicShut		"魔力遮断"
#define OptionElectricShock	"電撃"		// いったんボツ
#define OptionTripleBarrage	"三連砲撃"
#define Option33Crossfire	"三三砲撃"	// いったんボツ

/* +++ 選択肢の説明(ロボット) +++ */
#define DetailOfFlameThrower1	"炎を相手に噴射し燃やし尽くす(TP: 10)"
#define DetailOfFlameThrower2	"TPが50以上のとき追加でTPを30消費し威力アップ"
#define DetailOfSteelization	"身体を鋼鉄化し守備力を50上昇させる(TP: 15)"
#define DetailOfMagicShut		"魔力を遮断するバリアを張って魔法守備力を50上昇させる(TP: 15)"
#define DetailOfTripleBarrage	"連続で3発の砲撃を行う(TP: 25)"

/* +++行動の内容(ロボット)  +++ */
#define ActionFlameThrower1		"は赤橙の火炎を噴射した!"
#define ActionFlameThrower2		"から縹色の大火が噴きあがる!"
#define ActionSteelization		"は身体を鋼鉄のように硬くした"
#define ActionMagicShut			"は魔力遮断のバリアを展開した"
#define ActionTripleBarrage		"の3連続の砲撃!"


/* === 勇者 === */
/* +++ 選択肢(勇者) +++ */
#define OptionMagicFire			"ファイア"
#define OptionMagicThunder		"サンダー"
#define OptionMagicIce			"アイス"
#define OptionMagicHeal			"ヒール"

#define OptionTPCharge			"精神統一"
#define OptionAllHeartSoul		"全霊斬り"
#define OptionMPCharge			"魔力補給"
#define OptionGatherEnergy		"気合"

/* +++ 選択肢の説明(勇者) +++ */
#define DetailOfMagicFire		"小さな火の玉を打ち出す(MP: 5)"
#define DetailOfMagicThunder1	"雷の力で攻撃する魔法(MP: 5)"
#define DetailOfMagicThunder2	"相手より先に攻撃できる"
#define DetailOfMagicIce		"氷の柱を出現させる(MP: 10)"
#define DetailOfMagicHeal		"自分のHPを回復する魔法(MP: 10)"

#define DetailOfTPCharge		"心を整えることでTPを補給する(TP: 0)"
#define DetailOfAllHeartSoul	"全身全霊で相手に斬りかかる(TP: 10)"
#define DetailOfMPCharge		"TPをMPに変換して補給する(TP: 15)"
#define DetailOfGatherEnergy	"気合を込めて攻撃力を上昇させる(TP: 15)"

/* +++ 行動の内容(勇者) +++ */
#define ActionMagicFire		"は小さな火の玉を放った!"
#define ActionMagicThunder	"の剣から雷がほとばしる!"
#define ActionMagicIce		"は氷の柱を出現させた!"
#define ActionMagicHeal		"を光が包み込む"

#define ActionTPCharge		"は深呼吸して心を整えた"
#define ActionAllHeartSoul	"は全ての力を込めて剣を振り下ろした!"
#define ActionMPCharge		"は魔力を練って補給した"
#define ActionGatherEnergy	"は気合を込めている"


/* === ドラゴン === */
/* +++ 選択肢(ドラゴン) +++ */
#define OptionMagicPillar	"ピラー"
#define OptionMagicFung		"ファング"
#define OptionMagicRecover	"リカバー"

#define OptionCurseBreath		"呪いの息"
#define OptionImmortalScale		"竜仙鱗"
#define OptionDestructBreath	"破壊の息"
#define OptionAbsorbAtmosphere	"大気吸収"

/* +++ 選択肢の説明(ドラゴン) +++ */
#define DetailOfMagicPillar		"炎の柱を召喚し攻撃する(MP: 15)"
#define DetailOfMagicFung		"魔力を牙に変えて攻撃する(MP: 20)"
#define DetailOfMagicRecover	"上位の回復魔法(MP: 20)"

#define DetailOfCurseBreath			"呪われたブレスで攻撃し相手を弱らせる(TP: 15)"
#define DetailOfImmortalScale		"竜の鱗がダメージを防ぐ(TP: 20)"
#define DetailOfDestructBreath		"全てを破壊するブレス攻撃(TP: 25)"
#define DetailOfAbsorbAtmosphere	"大気を吸収し魔力を回復する(TP: 40)"

/* +++ 行動の内容(ドラゴン) +++ */
#define ActionMagicPillar	"は燃え盛る火柱を生み出した!"
#define ActionMagicFung		"は魔力を巨大な牙に変えた!"
#define ActionMagicRecover	"を光のヴェールが包み込む"

#define ActionCurseBreath		"は呪いを込めた息を吐き出した!"
#define ActionImmortalScale		"の鱗が淡く輝く!"
#define ActionDestructBreath	"は全てを破壊する息を吐き出した!"
#define ActionAbsorbAtmosphere	"は周囲の大気を取り込んだ"


/* === ダイトメア === */
/* +++ 選択肢(ダイトメア) +++ */
#define OptionMagicSaros	"サロス"
#define OptionMagicDeus		"デウス"
#define OptionMagicEx		"エクス"
#define OptionMagicMachina	"マキナ"

#define OptionImseti		"イムセト"
#define OptionHarpy			"ハーピ"
#define OptionKebehsenuev	"ケベフス"
#define OptionDuamtef		"ドゥアムタ"

/* +++ 選択肢の説明(ダイトメア) +++ */
#define DetailOfMagicSaros		"1ターンチャージして放つ魔法攻撃(MP: 15)"
#define DetailOfMagicDeus		"最大HPを増やし、HPも回復する(MP: 20)"
#define DetailOfMagicEx			"攻撃しつつHPを回復する(MP: 25)"
#define DetailOfMagicMachina	"攻撃力と魔力を上昇させる(MP: 30)"

#define DetailOfImseti			"2連続の物理攻撃(TP: 15)"
#define DetailOfHarpy			"必ず先制攻撃できる物理攻撃(TP: 15)"
#define DetailOfKebehsenuev		"魔力参照のブレス攻撃(TP: 15)"
#define DetailOfDuamtef			"物理、魔法ブレスの同時攻撃(TP: 45)"

/* +++ 行動の内容(ダイトメア) +++ */
#define ActionMagicSaros1	"は魔力を溜めている"
#define ActionMagicSaros2	"は溜めた魔力を放出した!"
#define ActionMagicDeus		"の生命力が高まる!"
#define ActionMagicEx		"は生命力を吸収する魔法を放った!"
#define ActionMagicMachina	"の身体が不気味に光る!"

#define ActionImseti		"は連続で打撃を放った!"
#define ActionHarpy			"は姿を消しとびかかった!"
#define ActionKebehsenuev	"は口から穢れた息を吐き出した!"
#define ActionDuamtef		"は大地を轟かせる!"


/* === キュー(仮) === */
/* +++ 選択肢(キュー(仮)) +++ */
#define OptionMagicTentativeDark	"ダーク(仮)"
#define OptionMagicTentativeLight	"ライト(仮)"
#define OptionMagicTentativeHeal	"ヒール(仮)"
#define OptionMagicTentativeRock	"ロック(仮)"

#define OptionTentativeThunder	"雷刃(仮)"
#define OptionTentativePoison	"毒刃(仮)"
#define OptionTentativeBreath	"構え(仮)"
#define OptionTentativeFinal	"痛打(仮)"

/* +++ 選択肢の説明(キュー(仮)) +++ */
#define DetailOfMagicTentativeDark		"闇の魔力で攻撃し、たまに相手の魔法を封じるようだ(MP: 10)"
#define DetailOfMagicTentativeLight		"光の魔力で攻撃し、たまに相手の特技を封じるようだ(MP: 10)"
#define DetailOfMagicTentativeHeal		"光の魔力で自身の傷を回復するようだ(MP: 10)"
#define DetailOfMagicTentativeRock		"魔石を生み出し攻撃するようだ(MP: 25)"

#define DetailOfTentativeThunder	"雷の刃で攻撃し、たまに相手をマヒさせるようだ(TP: 15)"
#define DetailOfTentativePoison		"毒の刃で攻撃し、たまに相手を毒にするようだ(TP: 15)"
#define DetailOfTentativeBreath		"使うほどに守備力が上昇するようだ(TP: 25)"
#define DetailOfTentativeFinal		"相手に致命の攻撃を叩き込むことがあるようだ(TP: 40)"

/* +++ 行動の内容(キュー(仮)) +++ */
#define ActionMagicTentativeDark	"は闇の魔力を放出した"
#define ActionMagicTentativeLight	"は光の魔力を放出した"
#define ActionMagicTentativeHeal	"は傷を癒した"
#define ActionMagicTentativeRock	"は魔石を放った"

#define ActionTentativeThunder		"は雷の刃で斬り込んだ"
#define ActionTentativePoison		"は毒の刃で斬り込んだ"
#define ActionTentativeStance		"は構えた"
#define ActionTentativeSevereBlow	"は腹部と頭部に打撃を叩き込んだ"


/* === shepp === */
/* +++ 選択肢(shepp) +++ */
#define OptionMagicMu		"μ"
#define OptionMagicNu		"ν"
#define OptionMagicLambda	"Λ"
#define OptionMagicXi		"ξ"

#define OptionPsi		"ψ"
#define OptionOmega		"Ω"
#define OptionSigma		"Σ"
#define OptionEta		"η"

/* +++ 選択肢の説明(shepp) +++ */
#define DetailOfMagicMu			"???(MP: 30)"
#define DetailOfMagicNu			"???(MP: 30)"
#define DetailOfMagicLambda		"???(MP: 30)"
#define DetailOfMagicXi			"???(MP: 30)"

#define DetailOfPsi				"???(TP: 20)"
#define DetailOfOmega			"???(TP: 25)"
#define DetailOfSigma			"???(TP: 35)"
#define DetailOfEta				"???(TP: 100)"

/* +++ 行動の内容(shepp) +++ */
#define ActionMagicMu		"Yu-ARC-is! Gi-indefensible Oh V"
#define ActionMagicNu		"yrots eht ni stops thgirb emos era ereht"
#define ActionMagicLambda	"niy pbrtsaa yjr rbsaisyopm od qppt"
#define ActionMagicXi		"Th lgndry psd 92 nd th BB fght r prtclrly bd"

#define ActionPsi			"2箱5虚な0根区しっ2駅くた6伝"
#define ActionOmega			"ろだぎすよつひさあだろく"
#define ActionSigma			"ぼじのどりょはてさのまではむりょ"
#define ActionEta			"おおょうううおああああいいあ"



/* --- メッセージの表示パターンの列挙型 --- */
enum MessagePattern
{
	Message1Line,	// メッセージを1行表示
	Message2Line,	// メッセージを2行表示
	Message3Line,	// メッセージを3行表示
	Message4Line	// メッセージを4行表示
};

extern MessagePattern settingMessagePattern;
extern MessagePattern displayMessagePattern;