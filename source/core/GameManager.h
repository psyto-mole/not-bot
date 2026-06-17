#pragma once
/* === ゲーム処理のヘッダファイル === */

#ifndef GAMEMANAGER_H	// 2重インクルード防止

#define GAMEMANAGER_H

#include "DxLib.h"

#define GameWindowWidth		1920				// ゲームウィンドウの幅
#define GameWindowHeight	1080				// ゲームウィンドウの高さ
#define GameColor			32					// ゲームに使用するカラー(32bit)
#define GameFPS				60					// ゲームのFPS

#define AllCharacterNumber	6							// キャラクターの種類(sheppを含む)
#define CharacterNumber		(AllCharacterNumber - 1)	// キャラクターの種類 - 1(sheppの分を引く)

#define BattleSceneFPS		150		// バトルシーン中のFPS設定(GameFPS / BattleSceneFPSの値がバトルシーン中のFPSとなる)

#define ISDISPLAY	true	// オブジェクトを表示する

#define GameDebug	true		// デバッグモードの設定
#define RuledLine	false		// 罫線モードの設定

#define STRINGLENGTH	256		// 使用できる文字列の長さ


extern void Draw_RuledLine();	// 画面に罫線を引く関数

#endif