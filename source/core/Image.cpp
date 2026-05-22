/* === 画像処理のソースファイル === */

#include "Image.h"

int FakeImageHandle;	// 偽のタイトル画面の背景画像のハンドル

int RobotImageHandle;	// ロボットの画像のハンドル
int HumanImageHandle;	// 人間の画像のハンドル
int DragonImageHandle;	// ドラゴンの画像のハンドル
int SheppImageHandle;	// Sheppの画像のハンドル


/* --- 画像の初期化関数 --- */
int Image_Init(void)
{
	FakeImageHandle		= LoadGraph(FAKEIMAGEPATH);		// 偽のタイトルシーンの背景画像の読み込み・ハンドル取得

	RobotImageHandle	= LoadGraph(ROBOTIMAGEPATH);	// ロボット画像の読み込み・ハンドル取得
	HumanImageHandle	= LoadGraph(HUMANIMAGEPATH);	// 人間画像の読み込み・ハンドル取得
	DragonImageHandle	= LoadGraph(DRAGONIMAGEPATH);	// ドラゴン画像の読み込み・ハンドル取得
	SheppImageHandle	= LoadGraph(SHEPPIMAGEPATH);	// Shepp画像の読み込み・ハンドル取得

	/* +++ 画像の読み込みが成功しなければエラーメッセージを表示し終了させる +++ */
	if (RobotImageHandle == -1
		|| HumanImageHandle == -1
		|| DragonImageHandle == -1
		|| SheppImageHandle == -1
		)
	{
		// エラーメッセージの表示
		MessageBox(
			GetMainWindowHandle(),
			"Image Error",
			"Error",
			MB_OK
		);

		return -1;	// エラーで終了(-1を返す)
	}

	return 0;	// 正常終了(0を返す)
}

/* --- 画像の終了処を行う理関数 --- */
void Image_End()
{
	DeleteGraph(FakeImageHandle);		// 偽のタイトルシーンの背景画像の削除(メモリの解放)

	DeleteGraph(RobotImageHandle);		// ロボット画像の削除(メモリの解放)
	DeleteGraph(HumanImageHandle);		// 人間画像の削除(メモリの解放)
	DeleteGraph(DragonImageHandle);		// ドラゴン画像の削除(メモリの解放)
	DeleteGraph(SheppImageHandle);		// Shepp画像の削除(メモリの解放)

	return;
}

/* --- キャラクターの描画関数 --- */
void DrawExtendGraphConditional(int x1,int y1,int x2,int y2,int characterNumber,bool isPlayer)
{
	/* +++ キャラクターの種類に応じてキャラクターを表示 +++ */
	switch (characterNumber)
	{
	case 1:
		/* +++ ロボットキャラクターの場合 +++ */

		if (isPlayer)	// 自キャラなら
		{
			DrawExtendGraph(x1, y1, x2,y2,RobotImageHandle, true);		// 画面左側に描画
		}
		else			// 敵キャラなら
		{
			DrawExtendGraph(x1, y1, x2, y2, RobotImageHandle, true);	// 画面右側に描画
		}
		break;
	case 2:
		/* +++ 人間キャラクターの場合 +++ */

		if (isPlayer)	// 自キャラなら
		{
			DrawExtendGraph(x1, y1, x2, y2, HumanImageHandle, true);	// 画面左側に描画
		}
		else			// 敵キャラなら
		{
			DrawExtendGraph(x1, y1, x2, y2, HumanImageHandle, true);	// 画面右側に描画
		}
		
		break;
	case 3:
		/* +++ ドラゴンキャラクターの場合 +++ */

		if (isPlayer)	// 自キャラなら
		{
			DrawExtendGraph(x1, y1, x2, y2, DragonImageHandle, true);	// 画面左側に描画
		}
		else			// 敵キャラなら
		{
			DrawExtendGraph(x1, y1, x2, y2, DragonImageHandle, true);	// 画面右側に描画
		}
		
		break;
	case 99:
		/* +++ Sheppキャラクターの場合 +++ */

		if (isPlayer)	// 自キャラなら
		{
			DrawExtendGraph(x1, y1, x2, y2, SheppImageHandle, true);	// 画面左側に描画
		}
		else			// 敵キャラなら
		{
			DrawExtendGraph(x1, y1, x2, y2, SheppImageHandle, true);	// 画面右側に描画
		}
		
		break;
	default:
		break;
	}

	return;
}