//##########ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "FPS.hpp"
#include "Keyboard.hpp"
#include <math.h>

//########## マクロ定義 ##########
#define GAME_WIDTH	1280		//画面の横の大きさ
#define GAME_HEIGHT 950		//画面の縦の大きさ
#define GAME_COLOR	32		//画面のカラービット

#define GAME_WINDOW_NAME	"GAME PLAY!"		//ウィンドウのタイトル
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE：ウィンドウモード / FALSE：フルスクリーン

#define SET_WINDOW_ST_MODE_DEFAULT			0	//デフォルト
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//タイトルバーなし
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//タイトルバーとフレームなし
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//フレームなし

#define GAME_FPS_SPEED					   60

#define GAME_BackImage_TITLE	"BackImage\\宇宙.jpg"			//背景画像


#define GAME_CharaImage_TITLE	"クリスマスキャラチップ\\pipo-xmaschara05.png"			//背景画像
//列挙型で各画面を管理
enum GameState
{
	GAME_TITLE,		//タイトル画面
	GAME_PLAY,		//プレイ画面
	//GAME_CLEAR,
	GAME_END		//エンド画面
};

//ゲーム画面の遷移を管理する
GameState gamestate_senni = GAME_TITLE;

//各画面を管理するプロトタイプ宣言
void DrawGameTitle();
void DrawGamePlay();
//void DrawGameClear();
void DrawGameEnd();

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	

	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//指定の数値で画面を表示する

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//タイトルバーあり

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//タイトルの文字

	if (DxLib_Init() == -1) { return -1; }						//ＤＸライブラリ初期化処理
	
	SetDrawScreen(DX_SCREEN_BACK);								//Draw系関数は裏画面に描画

	FPS *fps = new FPS(GAME_FPS_SPEED);							//FPSクラスのオブジェクトを生成

	
	
	while (TRUE)	//無限ループ
	{

		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了

		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		
		switch (gamestate_senni)
		{
		case GAME_TITLE:
			DrawGameTitle();
			break;
		case GAME_PLAY:
			DrawGamePlay();
			break;
		//case GAME_CLEAR:
			//DrawGameClear();
			//break;
		case GAME_END:
			DrawGameEnd();
			break;
		default:
			break;
		}

		//MY_ALL_KEYDOWN_UPDATE();				//キーの状態を取得

		Keyboard_Update();   //キーボードの更新

		fps->Update();		//FPSの処理[更新]

		fps->Draw(0, 0);	//FPSの処理[描画]

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画

		fps->Wait();		//FPSの処理[待つ]
	}




	delete fps;				//FPSを破棄
	
	DxLib_End();			//ＤＸライブラリ使用の終了処理

	return 0;
}

//タイトル画面の設定
void DrawGameTitle()
{

	// 背景の画像を読み込む
	int imgBack = LoadGraph(GAME_BackImage_TITLE);

	// 背景の画像を描画
	DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, imgBack, false);


	int FontHandle_TITLE = CreateFontToHandle(NULL, 120, 3);			//文字の大きさ変更
	//描画する文字の位置を設定
	DrawStringToHandle(150, 100, "GAME START!", GetColor(255, 0, 255), FontHandle_TITLE);
	DrawString(0, 20, "Enterキーを押して下さい(プレイ画面へ遷移します)", GetColor(0, 255, 255));

	//エンターキーが押されたら
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1)
	{
		gamestate_senni = GAME_PLAY;//シーンをゲーム画面に変更
	}


	// 作成したフォントデータを削除する
	DeleteFontToHandle(FontHandle_TITLE);
}

//プレイ画面の設定
void DrawGamePlay()
{
	int FontHandle_PLAY = CreateFontToHandle(NULL, 20, 3);			//文字の大きさ変更
	DrawString(0, 20, "Spaceキーを押して下さい(エンド画面へ遷移します)", GetColor(0, 255, 255));
	DrawStringToHandle(0, 40, "矢印キーで移動してね！(上矢印キーは攻撃ボタンだよ！)", GetColor(0, 155, 155), FontHandle_PLAY);

	//スペースキーが押されたら
	if (Keyboard_Get(KEY_INPUT_SPACE) == 1)
	{
		gamestate_senni = GAME_END;//シーンをゲーム画面に変更
	}

	DeleteFontToHandle(FontHandle_PLAY);
}

//エンド画面の設定
void DrawGameEnd()
{
	int FontHandle_END = CreateFontToHandle(NULL, 20, 3);			//文字の大きさ変更
	DrawString(0, 20, "BackSpaceキーを押して下さい(タイトル画面へ遷移します)", GetColor(0, 255, 255));
	DrawStringToHandle(0, 40, "お疲れさまでした！また挑戦してね！", GetColor(0, 155, 155), FontHandle_END);

	//スペースキーが押されたら
	if (Keyboard_Get(KEY_INPUT_BACK) == 1)
	{
		gamestate_senni = GAME_TITLE;//シーンをゲーム画面に変更
	}

	DeleteFontToHandle(FontHandle_END);
}
