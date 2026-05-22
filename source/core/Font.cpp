/* === フォント処理のソースファイル === */

#include "Font.h"


/* +++ 横書きフォント +++ */
int MSMincho_20_1;		// 明朝体(サイズ20、太さ1)
int MSMincho_30_1;		// 明朝体(サイズ30、太さ1)
int MSMincho_40_1;		// 明朝体(サイズ40、太さ1)
int MSMincho_50_1;		// 明朝体(サイズ50、太さ1)
int MSMincho_100_1;		// 明朝体(サイズ100、太さ1)
int MSMincho_100_9;		// 明朝体(サイズ100、太さ9)
int MSMincho_200_9;		// 明朝体(サイズ200、太さ9)
int MSMincho_300_9;		// 明朝体(サイズ300、太さ9)

/* +++ 縦書きフォント +++ */
int VMSMincho_30_1;	// 明朝体(サイズ30、太さ)
int VMSMincho_40_1;	// 明朝体(サイズ40、太さ)
int VMSMincho_50_1;	// 明朝体(サイズ50、太さ)

/* --- フォントの初期化関数 --- */
int Font_Init()
{
	/* === フォントデータの作成 === */
	/* +++ 横書きフォント +++ */
	MSMincho_20_1 = CreateFontToHandle("MS 明朝", 20, 1, DX_FONTTYPE_ANTIALIASING);		// 明朝体(サイズ20、太さ1)
	MSMincho_30_1 = CreateFontToHandle("MS 明朝", 30, 1, DX_FONTTYPE_ANTIALIASING);		// 明朝体(サイズ30、太さ1)
	MSMincho_40_1 = CreateFontToHandle("MS 明朝", 40, 1, DX_FONTTYPE_ANTIALIASING);		// 明朝体(サイズ40、太さ1)
	MSMincho_50_1 = CreateFontToHandle("MS 明朝", 50, 1, DX_FONTTYPE_ANTIALIASING);		// 明朝体(サイズ50、太さ1)
	MSMincho_100_1 = CreateFontToHandle("MS 明朝", 100, 1, DX_FONTTYPE_ANTIALIASING);	// 明朝体(サイズ100、太さ1)
	MSMincho_100_9 = CreateFontToHandle("MS 明朝", 100, 9, DX_FONTTYPE_ANTIALIASING);	// 明朝体(サイズ100、太さ9)
	MSMincho_200_9 = CreateFontToHandle("MS 明朝", 200, 9, DX_FONTTYPE_ANTIALIASING);	// 明朝体(サイズ200、太さ9)
	MSMincho_300_9 = CreateFontToHandle("MS 明朝", 300, 9, DX_FONTTYPE_ANTIALIASING);	// 明朝体(サイズ300、太さ9)

	/* +++ 縦書きフォント +++ */
	VMSMincho_30_1 = CreateFontToHandle("@MS 明朝", 30, 1, DX_FONTTYPE_ANTIALIASING);	// 明朝体(サイズ30、太さ1)
	VMSMincho_40_1 = CreateFontToHandle("@MS 明朝", 40, 1, DX_FONTTYPE_ANTIALIASING);	// 明朝体(サイズ40、太さ1)
	VMSMincho_50_1 = CreateFontToHandle("@MS 明朝", 50, 1, DX_FONTTYPE_ANTIALIASING);	// 明朝体(サイズ50、太さ1)


	if (MSMincho_100_9 == -1)	// フォントデータが作成できていなかったら
	{
		/* +++ エラーメッセージを出力 +++ */
		MessageBox(
			GetMainWindowHandle(),
			"Font Error Envoked",
			"Error",
			MB_OK
		);

		return -1;	// 初期化失敗(-1を返す)
	}

	return 0;	// 初期化成功(0を返す)
}

/* --- フォントの終了処理を行う関数 --- */
void Font_End()
{
	/* === フォントデータをメモリから削除 === */
	/* +++ 横書きフォント +++ */
	DeleteFontToHandle(MSMincho_20_1);		// 明朝体(サイズ20、太さ1)
	DeleteFontToHandle(MSMincho_30_1);		// 明朝体(サイズ30、太さ1)
	DeleteFontToHandle(MSMincho_40_1);		// 明朝体(サイズ40、太さ1)
	DeleteFontToHandle(MSMincho_50_1);		// 明朝体(サイズ50、太さ1)
	DeleteFontToHandle(MSMincho_100_1);		// 明朝体(サイズ100、太さ1)
	DeleteFontToHandle(MSMincho_100_9);		// 明朝体(サイズ100、太さ9)
	DeleteFontToHandle(MSMincho_200_9);		// 明朝体(サイズ200、太さ9)
	DeleteFontToHandle(MSMincho_300_9);		// 明朝体(サイズ300、太さ9)

	/* +++ 縦書きフォント +++ */
	DeleteFontToHandle(VMSMincho_30_1);		// 明朝体(サイズ30、太さ1)
	DeleteFontToHandle(VMSMincho_40_1);		// 明朝体(サイズ40、太さ1)
	DeleteFontToHandle(VMSMincho_50_1);		// 明朝体(サイズ50、太さ1)
}

/* --- 文字列を指定フォント・指定の揃えで描画する関数 --- */
void DrawFormatStringToHandleAlign(int x, int y, Font_Align align,
	unsigned int Color, int FontHandle, const char* FormatString, ...)
{
	int align_x, align_y;			// 揃え後の文字列の書き始め位置
	int StringWidth, StringHeight;	// 文字列の幅と高さ

	char DrawString[FontAlignStringMax];	// 描画する時の文字列

	va_list args;		// 可変引数(...)をうけとる変数

	/* +++ 各変数の初期化(左揃えで初期化) +++ */
	align_x = x;
	align_y = y;
	StringWidth = 0;
	StringHeight = 0;

	va_start(args, FormatString);	// 直前の引数のアドレスからデータの位置を求め変数に格納

	// 文字列を可変引数から生成
	vsnprintf(DrawString, sizeof(DrawString), FormatString, args);

	// 文字列の幅を計算
	StringWidth = GetDrawStringWidthToHandle(DrawString, strlen(DrawString), FontHandle);

	// 文字列の高さを取得
	StringHeight = GetFontSizeToHandle(FontHandle);

	// 揃える位置ごとに位置を計算
	switch (align)
	{
	case FAlign_Left:
		// そのままなので何もしない
		break;

	case FAlign_Center:
		// 中央位置を計算

		// x座標だけ中央に寄せる
		align_x = x - StringWidth / 2;
		break;

	case FAlign_Right:
		// 右揃え

		// x座標のみ右に寄せる
		align_x = x - StringWidth;
		break;

	case FAlign_AllCenter:
		// 上下左右ともに中央揃え

		// x座標を中央に寄せる
		align_x = x - StringWidth / 2;

		// y座標を中央に寄せる
		align_y = y - StringHeight / 2;
		break;

	default:
		break;
	}

	// 揃え後の書き出し位置を基に文字列を描画
	DrawFormatStringToHandle(align_x, align_y, Color, FontHandle, "%s", DrawString);

	va_end(args);	// 可変引数をもらうのを終える

	return;
}

/* --- 文字列を指定フォント・指定の揃えで縦書きする関数 --- */
void DrawFormatVStringToHandleAlign(int x, int y, Font_Align align, unsigned int color, int fontHandle, const char* formatString, ...)
{
	int align_x, align_y;			// 揃え後の文字列の書き始め位置
	int StringWidth, StringHeight;	// 文字列の幅と高さ

	char DrawString[FontAlignStringMax];	// 描画する時の文字列

	va_list args;		// 可変引数(...)をうけとる変数

	/* +++ 各変数の初期化(左揃えで初期化) +++ */
	align_x = x;
	align_y = y;
	StringWidth = 0;
	StringHeight = 0;

	va_start(args, formatString);	// 直前の引数のアドレスからデータの位置を求め変数に格納

	// 文字列を可変引数から生成
	vsnprintf(DrawString, sizeof(DrawString), formatString, args);

	// 文字列の幅を計算
	StringHeight = GetDrawStringWidthToHandle(DrawString, strlen(DrawString), fontHandle);

	// 文字列の高さを取得
	StringWidth = GetFontSizeToHandle(fontHandle);

	// 揃える位置ごとに位置を計算
	switch (align)
	{
	case FAlign_Left:
		// そのままなので何もしない
		break;

	case FAlign_Center:
		// 中央位置を計算

		// x座標だけ中央に寄せる
		align_x = x - StringWidth / 2;
		break;

	case FAlign_Right:
		// 右揃え

		// x座標のみ右に寄せる
		align_x = x - StringWidth;
		break;

	case FAlign_AllCenter:
		// 上下左右ともに中央揃え

		// x座標を中央に寄せる
		align_x = x - StringWidth / 2;

		// y座標を中央に寄せる
		align_y = y - StringHeight / 2;
		break;

	default:
		break;
	}

	// 揃え後の書き出し位置を基に文字列を描画
	DrawFormatVStringToHandle(align_x, align_y, color, fontHandle, "%s", DrawString);

	va_end(args);	// 可変引数をもらうのを終える

	return;
}