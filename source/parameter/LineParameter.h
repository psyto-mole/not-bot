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

#define AchievePlayerEdgeLineStartX		(GameWindowWidth / 2 - 200)
#define AchievePlayerEdgeLineEndX		(GameWindowWidth / 2 + 150)
#define AchievePlayerEdgeLineY			(GameWindowHeight / 2)
#define AchieveEnemyEdgeLineX			(GameWindowWidth / 2)
#define AchieveEnemyEdgeLineStartY		(GameWindowHeight / 2 - 200)
#define AchieveEnemyEdgeLineEndY		(GameWindowHeight / 2 + 150)

#define AchievePlayerRobotLineStartX	(GameWindowWidth / 2 - 200)
#define AchievePlayerRobotLineEndX		(GameWindowWidth / 2 + 150)
#define AchievePlayerRobotLineY			(GameWindowHeight / 2 + 50)
#define AchieveEnemyRobotLineX			(GameWindowWidth / 2 + 50)
#define AchieveEnemyRobotLineStartY		(GameWindowHeight / 2 - 200)
#define AchieveEnemyRobotLineEndY		(GameWindowHeight / 2 + 150)

#define AchievePlayerHumanLineStartX	(GameWindowWidth / 2 - 200)
#define AchievePlayerHumanLineEndX		(GameWindowWidth / 2 + 150)
#define AchievePlayerHumanLineY			(GameWindowHeight / 2 + 100)
#define AchieveEnemyHumanLineX			(GameWindowWidth / 2 + 100)
#define AchieveEnemyHumanLineStartY		(GameWindowHeight / 2 - 200)
#define AchieveEnemyHumanLineEndY		(GameWindowHeight / 2 + 150)

#define AchievePlayerDragonLineStartX	(GameWindowWidth / 2 - 200)
#define AchievePlayerDragonLineEndX		(GameWindowWidth / 2 + 150)
#define AchievePlayerDragonLineY		(GameWindowHeight / 2 + 150)
#define AchieveEnemyDragonLineX			(GameWindowWidth / 2 + 150)
#define AchieveEnemyDragonLineStartY	(GameWindowHeight / 2 - 200)
#define AchieveEnemyDragonLineEndY		(GameWindowHeight / 2 + 150)


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

