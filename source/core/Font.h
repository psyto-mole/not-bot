#pragma once
/* === フォント処理のヘッダーファイル === */

#include "DxLib.h"

#define FontAlignStringMax 512	// 文字揃えができる最大長

// 文字揃えの列挙型
enum Font_Align
{
	FAlign_Left,		// 左揃え
	FAlign_Center,		// 中央揃え
	FAlign_Right,		// 右揃え
	FAlign_AllCenter	// 上下左右ともに中央揃え
};

/* +++ 横書きフォント +++ */
extern int MSMincho_20_1;	// 明朝体(サイズ20、太さ1)
extern int MSMincho_30_1;	// 明朝体(サイズ30、太さ1)
extern int MSMincho_40_1;	// 明朝体(サイズ40、太さ1)
extern int MSMincho_50_1;	// 明朝体(サイズ50、太さ1)
extern int MSMincho_100_1;	// 明朝体(サイズ100、太さ1)
extern int MSMincho_100_9;	// 明朝体(サイズ100、太さ9)
extern int MSMincho_200_9;	// 明朝体(サイズ200、太さ9)
extern int MSMincho_300_9;	// 明朝体(サイズ300、太さ9)

/* +++ 横書きフォント +++ */
extern int VMSMincho_30_1;	// 明朝体(サイズ30、太さ)
extern int VMSMincho_40_1;	// 明朝体(サイズ40、太さ)
extern int VMSMincho_50_1;	// 明朝体(サイズ50、太さ)

/* --- フォントの初期化関数 --- */
extern int Font_Init(void);

/* --- フォントの終了処理を行う関数 --- */
extern void Font_End(void);

/* --- 文字列を指定フォント・指定の揃えで描画する関数 --- */
extern void DrawFormatStringToHandleAlign(int x, int y, Font_Align align,
								unsigned int Color, int FontHandle, const char* FormatString, ...);

/* --- 文字列を指定フォント・指定の揃えで縦書きする関数 --- */
extern void DrawFormatVStringToHandleAlign(int x, int y, Font_Align align, 
								unsigned int color, int fontHandle, const char* formatString, ...);
