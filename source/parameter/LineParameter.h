#pragma once
/* === 線の長さと位置を管理するヘッダファイル === */

#include "DxLib.h"


/* === シーンマネージャ === */
/* +++ メニューボックス +++ */
#define MenuLineStartX		(GameWindowWidth - 28)
#define MenuLineEndX		(GameWindowWidth - 11)
#define MenuLineY1			15
#define MenuLineY2			20
#define MenuLineY3			25
#define MenuLineThickness	2

/* +++ メニューウィンドウ +++ */
#define DevideMenuWindowStartX		(GameWindowWidth / 2 - 200)
#define DevideMenuWindowStartY		(GameWindowHeight / 2 - 400)
#define DevideMenuWindowEndX		(GameWindowWidth / 2 - 200)
#define DevideMenuWindowEndY		(GameWindowHeight / 2 + 500)
#define DevideMenuWindowThickness	3

/* +++ 勝敗記録 +++ */
#define AchievementEnemyLineStartX		(GameWindowWidth / 2 - 300)
#define AchievementEnemyLineEndX		(GameWindowWidth / 2 + 300)
#define AchievementEnemyLineY			(GameWindowHeight / 2 - 200)
#define AchievementPlayerLineX			(GameWindowWidth / 2 - 200)
#define AchievementPlayerLineStartY		(GameWindowHeight / 2 - 300)
#define AchievementPlayerLineEndY		(GameWindowHeight / 2 + 300)


#define AchievementTableHorizontalY		(GameWindowHeight / 2)
#define AchievementTableVerticalX		(GameWindowWidth / 2)


/* === バトルシーン === */
/* +++ 画面を2分割する直線 +++ */
#define DevideScrLineStartX		(GameWindowWidth / 2)
#define DevideScrLineStartY		0
#define DevideScrLineEndX		(GameWindowWidth / 2)
#define DevideScrLineEndY		880
#define DevideScrLineThickness	5

/* +++ メッセージウィンドウを分割する直線 +++ */
#define DevideWinLineStartX		(GameWindowWidth / 2 - 560)
#define DevideWinLineStartY		880
#define DevideWinLineEndX		(GameWindowWidth / 2 - 560)
#define DevideWinLineEndY		1080
#define DevideWinLineThickness	5

