#pragma once
/* === 線の長さと位置を管理するヘッダファイル === */

#include "DxLib.h"


/* === シーンマネージャ === */
/* +++ メニューボックス +++ */
#define MenuLineStartX		(GameWindowWidth - 28)	// メニューボックスの横線の始点のX座標
#define MenuLineEndX		(GameWindowWidth - 11)	// メニューボックスの横線の終点のX座標
#define MenuLineY1			15						// メニューボックスの1本目の横線のY座標
#define MenuLineY2			20						// メニューボックスの2本目の横線のY座標
#define MenuLineY3			25						// メニューボックスの3本目の横線のY座標
#define MenuLineThickness	2						// メニューボックスの横線の幅

/* +++ メニューウィンドウ +++ */
#define DevideMenuWindowStartX		(GameWindowWidth / 2 - 200)		// メニューウィンドウを左右に分割する縦線の始点のX座標
#define DevideMenuWindowStartY		(GameWindowHeight / 2 - 400)	// メニューウィンドウを左右に分割する縦線の始点のY座標
#define DevideMenuWindowEndX		(GameWindowWidth / 2 - 200)		// メニューウィンドウを左右に分割する縦線の終点のX座標(視点と等しい)
#define DevideMenuWindowEndY		(GameWindowHeight / 2 + 500)	// メニューウィンドウを左右に分割する縦線の終点のY座標
#define DevideMenuWindowThickness	3								// メニューウィンドウを左右に分割する縦線の幅

/* +++ 勝敗記録 +++ */
#define AchievementEnemyLineStartX		(GameWindowWidth / 2 - 300)		// 勝敗記録画面の「エネミー」欄を構成する横線のX座標
#define AchievementEnemyLineEndX		(GameWindowWidth / 2 + 250)		// 勝敗記録画面の「エネミー」欄を構成する横線のX座標
#define AchievementEnemyLineY			(GameWindowHeight / 2 - 200)	// 勝敗記録画面の「エネミー」欄を構成する横線のY座標
#define AchievementPlayerLineX			(GameWindowWidth / 2 - 200)		// 勝敗記録画面の「プレイヤー」欄を構成する縦線のX座標
#define AchievementPlayerLineStartY		(GameWindowHeight / 2 - 300)	// 勝敗記録画面の「プレイヤー」欄を構成する縦線のY座標
#define AchievementPlayerLineEndY		(GameWindowHeight / 2 + 250)	// 勝敗記録画面の「プレイヤー」欄を構成する縦線のY座標


#define AchievementTableHorizontalY		(GameWindowHeight / 2)	// 勝敗記録画面のプレイヤー側のキャラクターごとの記録を隔てる1本目の横線のY座標
#define AchievementTableVerticalX		(GameWindowWidth / 2)	// 勝敗記録画面のエネミー側のキャラクターごとの記録を隔てる1本目の縦線のX座標


/* === バトルシーン === */
/* +++ 画面を2分割する縦線 +++ */
#define DevideScrLineStartX		(GameWindowWidth / 2)	// 戦闘画面を左右に2分割する縦線の始点のX座標
#define DevideScrLineStartY		0						// 戦闘画面を左右に2分割する縦線の始点のY座標
#define DevideScrLineEndX		(GameWindowWidth / 2)	// 戦闘画面を左右に2分割する縦線の終点のX座標
#define DevideScrLineEndY		880						// 戦闘画面を左右に2分割する縦線の終点のY座標
#define DevideScrLineThickness	5						// 戦闘画面を左右に2分割する縦線の幅

/* +++ メッセージウィンドウを分割する縦線 +++ */
#define DevideWinLineStartX		(GameWindowWidth / 2 - 560)		// 戦闘画面のメッセージウィンドウを2つに分割する縦線の始点のX座標
#define DevideWinLineStartY		880								// 戦闘画面のメッセージウィンドウを2つに分割する縦線の始点のY座標
#define DevideWinLineEndX		(GameWindowWidth / 2 - 560)		// 戦闘画面のメッセージウィンドウを2つに分割する縦線の終点のX座標
#define DevideWinLineEndY		1080							// 戦闘画面のメッセージウィンドウを2つに分割する縦線の終点のY座標
#define DevideWinLineThickness	5								// 戦闘画面のメッセージウィンドウを2つに分割する縦線の幅

