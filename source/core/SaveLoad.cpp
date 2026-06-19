/* === ゲームデータのセーブ・ロードを管理するソースファイル === */

#include <stdio.h>
#include <stdbool.h>
#include "SaveLoad.h"
#include "Character.h"


errno_t errorCode;
int saveArray[CharacterNumber][CharacterNumber];
int total_saveArray_Previous;
int total_saveArray_Now;
bool alreadySaved;
bool alreadyConfirmedSave;
bool initialized;


/* --- ゲームデータの初期化関数 --- */
void Data_Init()
{
	int i,j;

	for (i = 0; i < CharacterNumber; i++)
	{
		for (j = 0; j < CharacterNumber; j++)
		{
			saveArray[i][j] = 0;
		}
	}

	total_saveArray_Now = 0;
	alreadySaved = false;
	alreadyConfirmedSave = false;
	initialized = true;

	Data_Load();

	for (i = 0; i < CharacterNumber; i++)
	{
		for (j = 0; j < CharacterNumber; j++)
		{
			total_saveArray_Now += saveArray[i][j];
		}
	}

	total_saveArray_Previous = total_saveArray_Now;

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

		dataSize = fwrite(saveArray, sizeof(int), CharacterNumber * CharacterNumber, fp);

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

	int i,j;


	errorCode = fopen_s(&fp, PathDataFile, "rb");

	if (errorCode == 0)
	{
		dataSize = fread(saveArray, sizeof(int), CharacterNumber * CharacterNumber, fp);

		if (dataSize != CharacterNumber * CharacterNumber)
		{
			for (i = 0; i < CharacterNumber; i++)
			{
				for (j = 0; j < CharacterNumber; j++)
				saveArray[i][j] = 0;
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
		for (i = 0; i < CharacterNumber; i++)
		{
			for (j = 0; j < CharacterNumber; j++)
			{
				saveArray[i][j] = 0;
			}
		}
	}

	alreadySaved = false;

	return;
}

/* --- ゲームデータを更新する関数 --- */
void Data_Update(int playerNumber, int enemyNumber)
{
	int i, j;
	int targetLine;
	int targetColumn;

	if (alreadySaved)
	{
		return;
	}
	else
	{
		if (enemyNumber <= CharacterNumber && playerNumber <= CharacterNumber)
		{
			targetLine = (playerNumber - 1);
			targetColumn = (enemyNumber - 1);

			saveArray[targetLine][targetColumn] = 1;

			Data_Save();

			total_saveArray_Now = 0;
			for (i = 0; i < CharacterNumber; i++)
			{
				for (j = 0; j < CharacterNumber; j++)
				{
					total_saveArray_Now += saveArray[i][j];
				}
			}
		}
	}

	return;
}

/* --- ゲームデータを消去する関数 --- */
void Data_Delete()
{
	size_t dataSize;
	FILE* fp;

	int i,j;

	
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

	for (i = 0; i < CharacterNumber; i++)
	{
		for (j = 0; j < CharacterNumber; j++)
		{
			saveArray[i][j] = 0;
		}
	}

	dataSize = fwrite(saveArray, sizeof(int), CharacterNumber * CharacterNumber, fp);

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