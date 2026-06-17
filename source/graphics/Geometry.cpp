/* === 幾何学処理のソースファイル === */

#include "Geometry.h"
#include "PointParameter.h"
#include "LineParameter.h"
#include "RectParameter.h"
#include "CircleParameter.h"


/* === ゲームウィンドウ === */
POINT GameWindowCenter;		// ゲーム画面の中心点


/* === システムメニュー === */
/* +++ メニューボックス +++ */
RECT menuBox;		// メニューボックスの矩形
LINE menuLine1;		// メニューボックスのライン1
LINE menuLine2;		// メニューボックスのライン2
LINE menuLine3;		// メニューボックスのライン3

/* +++ メニューウィンドウ +++ */
RECT menuWindow1;		// メニューウィンドウの外枠
RECT menuWindow2;		// メニューウィンドウの内側
LINE devideMenuWindow;	// メニューウィンドウを分割する直線
RECT menuButton1;	// メニューウィンドウのボタン1
RECT menuButton2;	// メニューウィンドウのボタン2
RECT menuButton3;	// メニューウィンドウのボタン3
RECT menuButton4;	// メニューウィンドウのボタン4
RECT menuButton5;	// メニューウィンドウのボタン5
RECT menuYesButton;		// メニューウィンドウの「はい」ボタン
RECT menuNoButton;		// メニューウィンドウの「いいえ」ボタン

/* +++ 勝敗記録画面 +++ */
RECT achievementBackButton;										// 勝敗記録画面の「戻る」ボタン
RECT achievementTable;											// 勝敗記録の表
CIRCLE winLoseCircle[AllCharacterNumber][AllCharacterNumber];	// 勝敗結果を描画する円の配列

LINE achieveDiagonalLine;						// 討伐記録の表の斜め線
LINE enemyLine;									// 討伐記録の「討伐対象」の下側の横線
LINE playerLine;								// 討伐記録の「プレイヤー」の右側の縦線
LINE tableVerticalLine[AllCharacterNumber];		// 討伐記録の表の始めの縦線
LINE tableHorizontalLine[AllCharacterNumber];	// 討伐記録の表の始めの横線


/* === セレクトシーン === */
/* +++ メッセージボックス +++ */
RECT selectBoxBackGround;	// メッセージボックスのバックグラウンド
RECT selectBoxYes;			// メッセージボックスの「はい」
RECT selectBoxNo;			// メッセージボックスの「いいえ」


/* === バトルシーン === */
/* +++ バトルシーンウィンドウ +++ */
LINE devideScreenLine;	// 画面を2分割する直線
LINE devideWindowLine;	// メッセージウィンドウを分割する直線
RECT optionButton1;		// 選択肢1ボタン
RECT optionButton2;		// 選択肢2ボタン
RECT optionButton3;		// 選択肢3ボタン
RECT optionButton4;		// 選択肢4ボタン
RECT backButton;		// 「戻る」ボタン
RECT messageWindow;		// メッセージウィンドウ


/* === リザルトシーン === */
/* +++ リザルトダイアログ +++ */
RECT resultDialogBackGround;	// リザルトダイアログのバックグラウンド
RECT resultDialogYes;			// リザルトダイアログの「はい」
RECT resultDialogNo;			// リザルトダイアログの「いいえ」


/* +++ 幾何学処理の関数 +++ */
/* --- 幾何学処理の初期化関数 --- */
void Geometry_Init(void)
{
	int i, j;

	// ゲーム画面の中心点を取得
	GameWindowCenter = GetRectCenter(GetRect(0, 0, GameWindowWidth, GameWindowHeight));

	/* === システムメニュー === */
	/* +++ メニューボックス +++ */
	menuBox = GetRectOnPoint(MenuBoxCenterX, MenuBoxCenterY, MenuBoxWidth, MenuBoxHeight);								// メニューボックスの矩形
	menuLine1 = GetLine(GetPoint(MenuLineStartX, MenuLineY1), GetPoint(MenuLineEndX, MenuLineY1), MenuLineThickness);	// メニューボックスのライン1
	menuLine2 = GetLine(GetPoint(MenuLineStartX, MenuLineY2), GetPoint(MenuLineEndX, MenuLineY2), MenuLineThickness);	// メニューボックスのライン2
	menuLine3 = GetLine(GetPoint(MenuLineStartX, MenuLineY3), GetPoint(MenuLineEndX, MenuLineY3), MenuLineThickness);	// メニューボックスのライン3

	/* +++ メニューウィンドウ +++ */
	menuWindow1 = GetRectOnPoint(MenuWindowCenterX, MenuWindowCenterY, MenuWindowWidth1, MenuWindowHeight1);					// メニューウィンドウの外枠
	menuWindow2 = GetRectOnPoint(MenuWindowCenterX, MenuWindowCenterY, MenuWindowWidth2, MenuWindowHeight2);					// メニューウィンドウの内側の矩形
	devideMenuWindow = GetLine(GetPoint(DevideMenuWindowStartX, DevideMenuWindowStartY), GetPoint(DevideMenuWindowEndX, DevideMenuWindowEndY), DevideMenuWindowThickness);	// メニューウィンドウを分割する直線
	menuButton1 = GetRectOnPoint(MenuButtonCenterX, MenuButton1LineY, MenuButtonWidth, MenuButtonHeight);						// メニューウィンドウのボタン1
	menuButton2 = GetRectOnPoint(MenuButtonCenterX, MenuButton2LineY, MenuButtonWidth, MenuButtonHeight);						// メニューウィンドウのボタン2
	menuButton3 = GetRectOnPoint(MenuButtonCenterX, MenuButton3LineY, MenuButtonWidth, MenuButtonHeight);						// メニューウィンドウのボタン3
	menuButton4 = GetRectOnPoint(MenuButtonCenterX, MenuButton4LineY, MenuButtonWidth, MenuButtonHeight);						// メニューウィンドウのボタン4
	menuButton5 = GetRectOnPoint(MenuButtonCenterX, MenuButton5LineY, MenuButtonWidth, MenuButtonHeight);						// メニューウィンドウのボタン5
	menuYesButton = GetRectOnPoint(MenuYesButtonCenterX, MenuYesNoButtonCenterY, MenuYesNoButtonWidth, MenuYesNoButtonHeight);	// メニューウィンドウの「はい」ボタン
	menuNoButton = GetRectOnPoint(MenuNoButtonCenterX, MenuYesNoButtonCenterY, MenuYesNoButtonWidth, MenuYesNoButtonHeight);	// メニューウィンドウの「いいえ」ボタン

	/* +++ 勝敗記録画面 +++ */
	achievementBackButton = GetRectOnPoint(AchievementBackCenterX, AchievementBackCenterY, AchievementBackWidth, AchievementBackHeight);	// 勝敗記録画面の「戻る」ボタン
	achievementTable = GetRect(AchievementTableLeft, AchievementTableTop, AchievementTableRight, AchievementTableBottom);
	for (i = 0; i < AllCharacterNumber; i++)
	{
		for (j = 0; j < AllCharacterNumber; j++)
		{
			winLoseCircle[i][j] = GetCircle(GetPoint(WinLoseCircleStartX + 50 * j, WinLoseCircleStartY + 50 * i), WinLoseCircleRadius);
		}
	}
	

	

	achieveDiagonalLine = GetLine(GetPoint(AchievementTableLeft, AchievementTableTop), GetPoint(GameWindowWidth / 2, GameWindowHeight / 2), 3);
	enemyLine = GetLine(GetPoint(AchievementEnemyLineStartX, AchievementEnemyLineY), GetPoint(AchievementEnemyLineEndX, AchievementEnemyLineY), 3);
	playerLine = GetLine(GetPoint(AchievementPlayerLineX, AchievementPlayerLineStartY), GetPoint(AchievementPlayerLineX, AchievementPlayerLineEndY), 3);
	for (i = 0; i < AllCharacterNumber; i++)
	{
		tableVerticalLine[i] = GetLine(GetPoint(AchievementTableVerticalX + 50 * i, AchievementEnemyLineY), GetPoint(AchievementTableVerticalX + 50 * i, AchievementPlayerLineEndY), 3);
		tableHorizontalLine[i] = GetLine(GetPoint(AchievementPlayerLineX, AchievementTableHorizontalY + 50 * i), GetPoint(AchievementEnemyLineEndX, AchievementTableHorizontalY + 50 * i), 3);
	}


	/* === セレクトシーン === */
	/* +++ メッセージボックス +++ */
	selectBoxBackGround = GetRect(SelectBoxBackLeft, SelectBoxBackTop, SelectBoxBackRight, SelectBoxBackBottom);
	selectBoxYes = GetRectOnPoint(SelectBoxYesCenterX, SelectBoxButtonCenterY, SelectBoxYesWidth, SelectBoxButtonHeight);
	selectBoxNo = GetRectOnPoint(SelectBoxNoCenterX, SelectBoxButtonCenterY, SelectBoxNoWidth, SelectBoxButtonHeight);


	/* === バトルシーン === */
	/* +++ バトルシーンウィンドウ +++ */
	devideScreenLine = GetLine(GetPoint(DevideScrLineStartX, DevideScrLineStartY), GetPoint(DevideScrLineEndX, DevideScrLineEndY), DevideScrLineThickness);		// 画面を2分割する直線を取得
	devideWindowLine = GetLine(GetPoint(DevideWinLineStartX, DevideWinLineStartY), GetPoint(DevideWinLineEndX, DevideWinLineEndY), DevideWinLineThickness);		// メッセージウィンドウを分割する直線を取得
	optionButton1 = GetRectOnPoint(OptionButton1Line, OptionButton1Row, OptionButtonWidth, OptionButtonHeight);														// 選択肢1ボタンを取得
	optionButton2 = GetRectOnPoint(OptionButton2Line, OptionButton1Row, OptionButtonWidth, OptionButtonHeight);														// 選択肢2ボタンを取得
	optionButton3 = GetRectOnPoint(OptionButton1Line, OptionButton2Row, OptionButtonWidth, OptionButtonHeight);														// 選択肢3ボタンを取得
	optionButton4 = GetRectOnPoint(OptionButton2Line, OptionButton2Row, OptionButtonWidth, OptionButtonHeight);														// 選択肢4ボタンを取得
	backButton = GetRectOnPoint(GameWindowWidth / 2 - 890, 1065, 120, 30);																						// 「戻る」ボタンを取得
	messageWindow = GetRectOnPoint(MessageWindowCenterX, MessageWindowCenterY, MessageWindowWidth, MessageWindowHeight);										// メッセージウィンドウを取得


	/* === リザルトシーン === */
	/* +++ リザルトダイアログ +++ */
	resultDialogBackGround = GetRectOnPoint(ResultDialogBackCenterX, ResultDialogBackCenterY, ResultDialogBackWidth, ResultDialogBackHeight);
	resultDialogYes = GetRectOnPoint(ResultDialogYesCenterX,ResultDialogButtonCenterY, ResultDialogYesWidth, ResultDialogButtonHeight);
	resultDialogNo = GetRectOnPoint(ResultDialogNoCenterX, ResultDialogButtonCenterY, ResultDialogNoWidth, ResultDialogButtonHeight);

	return;
}

/* +++ 点に関する関数 +++ */
/* --- X座標とY座標からPOINT型を取得(引数は点の座標) --- */
POINT GetPoint(int x, int y)
{
	POINT point;	// POINT潟の変数

	point.x = x;	// 引数のx座標をPOINT型のx座標に設定
	point.y = y;	// 引数のy座標をPOINT型のy座標に設定

	return point;	// POINT型を戻り値として返す
}

/* --- 点と点が接触しているか(引数は2つの点) --- */
bool CollisionPointToPoint(POINT a, POINT b)
{
	// aとbの座標が一致している
	if (a.x == b.x && a.y == b.y)
	{
		return true;	// trueを返す
	}

	return false;	// falseを返す
}

/* --- POINT型から点を描画 --- */
void DrawPoint(POINT point, unsigned int color)
{
	DrawPixel(point.x, point.y, color);

	return;
}

/* +++ 線に関する関数 +++ */
/* --- 始点と終点からLINE型を取得 --- */
LINE GetLine(POINT a, POINT b, int Thickness)
{
	LINE line;

	line.startPoint = a;
	line.endPoint = b;
	line.Thickness = Thickness;

	return line;
}

/* --- LINE型から直線を描画 --- */
void DrawLineWithStruct(LINE line, unsigned int color)
{
	DrawLine(line.startPoint.x, line.startPoint.y, line.endPoint.x, line.endPoint.y, color, line.Thickness);

	return;
}

/* +++ 矩形に関する関数 +++ */
/* --- RECT型を一時的に取得(引数は矩形の左上と右下の座標) --- */
RECT GetRect(int left, int top, int right, int bottom)
{
	RECT rect;	// RECT型の変数

	rect.left = left;		// 引数の左上のx座標をRECT型のleftに設定
	rect.top = top;			// 引数の左上のy座標をRECT型のtopに設定
	rect.right = right;		// 引数の右下のx座標をRECT型のrightに設定
	rect.bottom = bottom;	// 引数の右下のy座標をRECT型のbottomに設定

	return rect;	// RECT型変数を戻り値として返す
}

/* --- 中心座標と幅、高さからRECT型を一時的に取得 --- */
RECT GetRectOnPoint(int centerX, int centerY, int width, int height)
{
	RECT rect;

	rect.left = centerX - width / 2;
	rect.top = centerY - height / 2;
	rect.right = centerX + (width / 2) + 1;
	rect.bottom = centerY + (height / 2) + 1;

	return rect;
}

/* --- 矩形の中心座標を取得(引数は矩形) --- */
POINT GetRectCenter(RECT rect)
{
	POINT centerPoint;	// 中心座標を格納するPOINT型変数

	centerPoint.x = (rect.right + rect.left) / 2;	// 矩形の中心のx座標を計算
	centerPoint.y = (rect.bottom + rect.top) / 2;	// 矩形の中心のy座標を計算

	return centerPoint;		// 中心座標を戻り値として返す
}

/* --- 矩形を描画(引数は矩形と色と塗りつぶすかの選択) --- */
void DrawRect(RECT rect, unsigned int color, bool fill, int lineThickness)
{
	/* +++ 引数をもとに矩形を描画 +++ */
	DrawBox(
		rect.left, rect.top,
		rect.right + 1, rect.bottom + 1,
		color, fill, lineThickness
	);

	return;
}

/* --- 矩形を中心点を用いて描画 --- */
void DrawBoxOnPoint(int centerX,int centerY,int width, int height, unsigned int color, bool fill, int lineThickness)
{
	int left, top;
	int right, bottom;

	if (width % 2 == 0)
	{
		left = centerX - width / 2;
		right = (centerX + width / 2) + 1;
	}
	else
	{
		left = (centerX - 1) - width / 2;
		right = ((centerX - 1) + width / 2) + 1;
	}

	if (height % 2 == 0)
	{
		top = centerY - height / 2;
		bottom = (centerY + height / 2) + 1;
	}
	else
	{
		top = (centerY - 1) - height / 2;
		bottom = ((centerY - 1) + height / 2) + 1;
	}

	DrawBox(left, top, right, bottom, color, fill, lineThickness);

	return;
}

/* --- 矩形と点が接触しているか(引数は矩形と点) --- */
bool CollisionRectToPoint(RECT rect, POINT point)
{
	// 矩形と点が接触しているなら
	if (rect.left <= point.x && rect.top <= point.y
		&& rect.right >= point.x && rect.bottom >= point.y)
	{
		return true;	// trueを返す
	}

	return false;	// falseを返す
}

/* --- 矩形と矩形が接触している(引数は2つの矩形) --- */
bool CollisionRectToRect(RECT a, RECT b)
{
	// 矩形同士が接触しているなら
	if (a.left <= b.right && a.top <= b.bottom
		&& a.right >= b.left && a.bottom >= b.top)
	{
		return true;	// trueを返す
	}

	return false;	// falseを返す
}

/* +++ 円に関する関数 +++ */
/* --- CIRCLE型を取得(引数は中心点と半径)する関数 --- */
CIRCLE GetCircle(POINT point, float radius)
{
	CIRCLE circle;	// CIRCLE型の変数

	circle.point = point;		// 引数の中心点をCIRCLE型のpointに設定
	circle.radius = radius;		// 引数の半径をCIRCLE型のradiusに設定

	return circle;
}

/* --- CIRCLE型を用いて円を描画する関数 --- */
void DrawCircleWithStruct(CIRCLE circle, int color, bool fill, int thickness)
{
	int x, y, radius;

	x = circle.point.x;
	y = circle.point.y;
	radius = circle.radius;

	DrawCircle(x, y, radius, color, fill, thickness);

	return;
}