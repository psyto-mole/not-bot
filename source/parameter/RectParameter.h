#pragma once
/* === 矩形の幅と高さを管理するヘッダーファイル === */

#include "DxLib.h"


/* === メニュー === */
/* +++ メニューボックス +++ */
#define MenuBoxCenterX	(GameWindowWidth - 20)	// ゲーム終了ボックスの中心のX座標
#define MenuBoxCenterY	20						// ゲーム終了ボックスの中心のY座標
#define MenuBoxWidth	30						// ゲーム終了ボックスの幅
#define MenuBoxHeight	30						// ゲーム終了ボックスの高さ

/* +++ メニューウィンドウ +++ */
#define MenuWindowCenterX	(GameWindowWidth / 2)			// メニューウィンドウの中心のX座標
#define MenuWindowCenterY	(GameWindowHeight / 2 + 50)		// メニューウィンドウの中心のY座標
#define MenuWindowWidth1	1000							// メニューウィンドウの外枠の幅
#define MenuWindowHeight1	900								// メニューウィンドウの外枠の高さ
#define MenuWindowWidth2	994								// メニューウィンドウの内側の矩形の幅
#define MenuWindowHeight2	894								// メニューウィンドウの内側の矩形の高さ

/* +++ メニューボタン +++ */
#define MenuButtonCenterX	(GameWindowWidth / 2 - 350)		// メニューボタンの中心のX座標
#define MenuButton1LineY	(GameWindowHeight / 2 - 350)	// 1行目のメニューボタンの中心のY座標
#define MenuButton2LineY	(GameWindowHeight / 2 - 250)	// 2行目のメニューボタンの中心のY座標
#define MenuButton3LineY	(GameWindowHeight / 2 - 150)	// 3行目のメニューボタンの中心のY座標
#define MenuButton4LineY	(GameWindowHeight / 2 - 50)		// 4行目のメニューボタンの中心のY座標
#define MenuButton5LineY	(GameWindowHeight / 2 + 50)		// 5行目のメニューボタンの中心のY座標
#define MenuButtonWidth		270								// メニューボタンの幅
#define MenuButtonHeight	70								// メニューボタンの高さ

/* +++ 勝敗の記録 +++ */
#define AchievementTableLeft	(GameWindowWidth / 2 - 300)		// 勝敗記録画面の表の左上のX座標
#define AchievementTableTop		(GameWindowHeight / 2 - 300)	// 勝敗記録画面の表の左上のY座標
#define AchievementTableRight	(GameWindowWidth / 2 + 250)		// 勝敗記録画面の表の右下のX座標
#define AchievementTableBottom	(GameWindowHeight / 2 + 250)	// 勝敗記録画面の表の右下のY座標
#define AchievementBackCenterX	(GameWindowWidth / 2 - 450)		// 勝敗の記録画面の「戻る」ボタンの中心のX座標
#define AchievementBackCenterY	(GameWindowHeight / 2 - 375)	// 勝敗の記録画面の「戻る」ボタンの中心のY座標
#define AchievementBackWidth	100								// 勝敗の記録画面の「戻る」ボタンの幅
#define AchievementBackHeight	50								// 勝敗の記録画面の「戻る」ボタンの高さ

/* +++ 「はい」・「いいえ」ボタン +++ */
#define MenuYesButtonCenterX	(GameWindowWidth / 2)			// メニューウィンドウの「はい」ボタンの中心のX座標
#define MenuNoButtonCenterX		(GameWindowWidth / 2 + 300)		// メニューウィンドウの「いいえ」ボタンの中心のX座標
#define MenuYesNoButtonCenterY	(GameWindowHeight / 2)			// メニューウィンドウの「はい」・「いいえ」ボタンの中心のY座標
#define MenuYesNoButtonWidth	100								// メニューウィンドウの「はい」・「いいえ」ボタンの幅
#define MenuYesNoButtonHeight	50								// メニューウィンドウの「はい」・「いいえ」ボタンの高さ


/* === セレクトシーン === */
/* +++ セレクトボックスバックグラウンド +++ */
#define SelectBoxBackLeft		(GameWindowWidth / 2 - 250)		// セレクトボックスのバックグラウンドの左上の点のX座標
#define SelectBoxBackTop		(GameWindowHeight / 2 - 150)	// セレクトボックスのバックグラウンドの左上の点のY座標
#define SelectBoxBackRight		(GameWindowWidth / 2 + 250)		// セレクトボックスのバックグラウンドの右下の点のX座標
#define SelectBoxBackBottom		(GameWindowHeight / 2 + 150)	// セレクトボックスのバックグラウンドの右下の点のY座標

/* +++ セレクトボックスのボタン +++ */
#define SelectBoxYesWidth		80														// セレクトボックスの「はい」のボタンの幅
#define SelectBoxNoWidth		100														// セレクトボックスの「いいえ」のボタンの幅
#define SelectBoxButtonHeight	40														// セレクトボックスのボタンの高さ
#define SelectBoxYesCenterX		((GameWindowWidth / 2) - (SelectBoxYesWidth / 2 + 30))	// セレクトボックスの「はい」ボタンの中心のX座標
#define SelectBoxNoCenterX		((GameWindowWidth / 2) + (SelectBoxNoWidth / 2 + 20))	// セレクトボックスの「いいえ」ボタンの中心のX座標
#define SelectBoxButtonCenterY	(GameWindowHeight / 2 + 20)								// セレクトボックスのボタンの中心のY座標


/* === バトルシーン === */
/* +++ 選択肢ボタン +++ */
#define OptionButton1Line	(GameWindowWidth / 2 - 860)		// 1行目の択肢ボタンの中心のX座標
#define OptionButton2Line	(GameWindowWidth / 2 - 660)		// 2行目の択肢ボタンの中心のX座標
#define OptionButton1Row	930								// 1列目の選択肢ボタンの中心のY座標
#define OptionButton2Row	1010							// 2列目の選択肢ボタンの中心のY座標
#define OptionButtonWidth	180								// 選択肢ボタンの幅
#define OptionButtonHeight	60								// 選択肢ボタンの高さ

/* +++ メッセージウィンドウ +++ */
#define MessageWindowCenterX	(GameWindowWidth / 2)	// メッセージウィンドウの中心のX座標
#define MessageWindowCenterY	980						// メッセージウィンドウの中心のY座標
#define MessageWindowWidth		1920					// メッセージウィンドウの幅
#define MessageWindowHeight		200						// メッセージウィンドウの高さ


/* === リザルトシーン === */
/* +++ リザルトダイアログのバックグラウンド +++ */
#define ResultDialogBackWidth		500
#define ResultDialogBackHeight		300
#define ResultDialogBackCenterX		(GameWindowWidth / 2)
#define ResultDialogBackCenterY		(GameWindowHeight / 2)

/* +++ リザルトダイアログのボタン +++ */
#define ResultDialogYesWidth		80															// リザルトダイアログの「はい」ボタンの幅
#define ResultDialogNoWidth			100															// リザルトダイアログの「いいえ」ボタンの幅
#define ResultDialogOKWidth			80															// リザルトダイアログの「OK」ボタンの幅
#define ResultDialogButtonHeight	40															// リザルトダイアログのボタンの高さ
#define ResultDialogYesCenterX		(ResultDialogBackCenterX - (SelectBoxYesWidth / 2 + 30))	// リザルトダイアログの「はい」ボタンの中心のX座標
#define ResultDialogNoCenterX		(ResultDialogBackCenterX + (SelectBoxNoWidth / 2 + 20))		// リザルトダイアログの「いいえ」ボタンの中心のX座標
#define ResultDialogOKCenterX		ResultDialogBackCenterX										// リザルトダイアログの「OK」ボタンの中心のX座標
#define ResultDialogButtonCenterY	(ResultDialogBackCenterY + 20)								// リザルトダイアログのボタンの中心のY座標