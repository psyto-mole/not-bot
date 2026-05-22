/* === ゲームデータのセーブ・ロードを管理するソースファイル === */

#include <stdio.h>
#include <stdbool.h>
#include "SaveLoad.h"
#include "Character.h"


errno_t errorCode;
int round_robin[CharacterNumber * CharacterNumber];
bool alreadySaved;
bool initialized;


/* --- ゲームデータの初期化関数 --- */
void Data_Init()
{
	int i;

	for (i = 0; i < CharacterNumber * CharacterNumber; i++)
	{
		round_robin[i] = 0;
	}

	alreadySaved = false;
	initialized = true;

	Data_Load();

	return;
}

/* --- ゲームデータをセーブする関数 --- */
void Data_Save()
{
	size_t dataSize;
	FILE* fp;

	if (alreadySaved)
	{
		return;
	}
	else
	{
		errorCode = fopen_s(&fp, PathDataFile, "wb");

		if (errorCode != 0)
		{
			MessageBox(
				GetMainWindowHandle(),			// ウィンドウハンドル
				"Save file could not be open",	// エラー内容
				"Save Error",					// エラータイトル
				MB_OK							// OKボタンのみ表示
			);

			return;
		}

		dataSize = fwrite(round_robin, sizeof(int), CharacterNumber * CharacterNumber, fp);

		if (dataSize != CharacterNumber * CharacterNumber)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Save failed",				// エラー内容
				"Save Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return;
		}

		if (alreadySaved == false)
		{
			alreadySaved = true;
		}

		if (initialized)
		{
			initialized = false;
		}

		dataSize = fwrite(&initialized, sizeof(bool), 1, fp);

		if (dataSize != 1)
		{
			MessageBox(
				GetMainWindowHandle(),		// ウィンドウハンドル
				"Save failed",				// エラー内容
				"Save Error",				// エラータイトル
				MB_OK						// OKボタンのみ表示
			);

			return;
		}
	}

	fclose(fp);
	return;
}

/* --- ゲームデータをロードする関数 --- */
void Data_Load()
{
	size_t dataSize;
	FILE* fp;

	int i;


	errorCode = fopen_s(&fp, PathDataFile, "rb");

	if (errorCode == 0)
	{
		dataSize = fread(round_robin, sizeof(int), CharacterNumber * CharacterNumber, fp);

		if (dataSize != CharacterNumber * CharacterNumber)
		{
			for (i = 0; i < CharacterNumber * CharacterNumber; i++)
			{
				round_robin[i] = 0;
			}
		}

		dataSize = fread(&initialized, sizeof(bool), 1, fp);

		if (dataSize != 1)
		{
			initialized = true;
		}

		fclose(fp);
	}
	else
	{
		for (i = 0; i < CharacterNumber * CharacterNumber; i++)
		{
			round_robin[i] = 0;
		}
	}

	alreadySaved = false;

	return;
}

/* --- ゲームデータを更新する関数 --- */
void Data_Update(int playerNumber, int enemyNumber)
{
	int targetElement;

	if (alreadySaved)
	{
		return;
	}
	else
	{
		if (enemyNumber <= CharacterNumber && playerNumber <= CharacterNumber)
		{
			targetElement = ((playerNumber - 1) * CharacterNumber) + (enemyNumber - 1);

			round_robin[targetElement] = 1;

			Data_Save();
		}
	}

	return;
}

/* --- ゲームデータを消去する関数 --- */
void Data_Delete()
{
	size_t dataSize;
	FILE* fp;

	int i;

	
	errorCode = fopen_s(&fp, PathDataFile, "wb");

	if (errorCode != 0)
	{
		MessageBox(
			GetMainWindowHandle(),			// ウィンドウハンドル
			"Save file could not be open",	// エラー内容
			"Save Error",					// エラータイトル
			MB_OK							// OKボタンのみ表示
		);

		return;
	}

	for (i = 0; i < CharacterNumber * CharacterNumber; i++)
	{
		round_robin[i] = 0;
	}

	dataSize = fwrite(round_robin, sizeof(int), CharacterNumber * CharacterNumber, fp);

	if (dataSize != CharacterNumber * CharacterNumber)
	{
		MessageBox(
			GetMainWindowHandle(),		// ウィンドウハンドル
			"Save failed",				// エラー内容
			"Save Error",				// エラータイトル
			MB_OK						// OKボタンのみ表示
		);

		return;
	}

	if (alreadySaved)
	{
		alreadySaved = false;
	}

	if (initialized == false)
	{
		initialized = true;
	}

	dataSize = fwrite(&initialized, sizeof(bool), 1, fp);

	if (dataSize != 1)
	{
		MessageBox(
			GetMainWindowHandle(),		// ウィンドウハンドル
			"Save failed",				// エラー内容
			"Save Error",				// エラータイトル
			MB_OK						// OKボタンのみ表示
		);

		return;
	}

	fclose(fp);

	return;
}