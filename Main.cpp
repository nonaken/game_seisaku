//##########ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "FPS.h"
#include "Keyboard.h"
#include "CHARA.h"
#include "Ball.h"

#include <iostream>
#include <random>




//#include <cstdlib>
//#include <ctime>

//#include <math.h>

//########## マクロ定義 ##########
#define GAME_WIDTH	1280		//画面の横の大きさ(画面右端の限界値)
#define GAME_MIN_WIDTH 0		//画面左端の限界値
#define GAME_HEIGHT 950			//画面の縦の大きさ
#define GAME_COLOR	32			//画面のカラービット

#define GAME_WINDOW_NAME	"GAME PLAY!"		//ウィンドウのタイトル
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE：ウィンドウモード / FALSE：フルスクリーン

#define SET_WINDOW_ST_MODE_DEFAULT			0	//デフォルト
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//タイトルバーなし
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//タイトルバーとフレームなし
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//フレームなし

#define GAME_FPS_SPEED					   60

#define GAME_BackImage_TITLE	"BackImage\\宇宙.jpg"			//タイトル画面背景画像
#define GAME_BackImage_PLAY		"BackImage\\pipo-battlebg017b.jpg"	//プレイ画面背景画像
#define GAME_CharaImage_PLAY	"クリスマスキャラチップ\\pipo-xmaschara05.png"			//キャラクター画像
#define GAME_CharaImage_PLAY_ATTACK "クリスマスキャラチップ\\pipo-xmaschara06.png"		//攻撃画像

#define GAME_BackImage_END		"BackImage\\pipo-battlebg020b.jpg"	//エンド画面背景画像
#define GAME_Chara_Set_X		GAME_WIDTH / 2		//キャラクターの初期X位置(中央)
#define GAME_Chara_Set_Y		700		//キャラクターの初期X位置

#define GAME_BallImage_Play		"BackImage\\Bowling-Ball-Vector-Set.jpg"		//プレイ画面で使うボールの画像

#define ATTACK_SYOKI_X	50	//攻撃画像の初期X値
#define ATTACK_SYOKI_Y	100	//攻撃画像の初期Y値
#define GAME_ATTACK_Y	20	//攻撃速度

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

//int RANDOM();





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


	//動的領域を確保する
	CHARA *c = new CHARA();
	ATTACK *a = new ATTACK();
	int ATTACK_flag = false;

	LoadDivGraph(GAME_CharaImage_PLAY, 12, 3, 5, 32, 32, &c->Handle[0]);	//読み込む画像の分割数や大きさ
	LoadDivGraph(GAME_CharaImage_PLAY_ATTACK, 12, 3, 5, 32, 32, &a->A_Handle[0]);	//読み込む画像の分割数や大きさ

	/*
	std::srand((unsigned int)time(NULL));
	int x = rand()% 6;
	*/
	

	


	while (TRUE)	//無限ループ
	{

		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了

		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		
		Keyboard_Update();   //キーボードの更新

		fps->Update();		//FPSの処理[更新]

		//画面の切り替え管理
		switch (gamestate_senni)
		{
		//タイトル画面なら
		case GAME_TITLE:
			DrawGameTitle();
			break;

		//プレイ画面なら
		case GAME_PLAY:
			DrawGamePlay();

			//左矢印キーを押し続けたら
			if (Keyboard_Get(KEY_INPUT_LEFT) >= 1)
			{
				c->Chara_soeji = 3;
				//キャラクターのX座標が左画面外に行かないように移動する
				if (GAME_Chara_Set_X + c->Chara_X >= GAME_MIN_WIDTH) 
				{
					c->Chara_X -= 5;
				}
			}

			//右矢印キーを押し続けたら
			if (Keyboard_Get(KEY_INPUT_RIGHT) >= 1)
			{
				c->Chara_soeji = 6;
				//キャラクターのX座標が右画面外に行かないように移動する
				if (c->Chara_X <= GAME_WIDTH - GAME_Chara_Set_X)
				{
					c->Chara_X += 5;
				}
			}

			//左矢印キーと右矢印キーを同時押したら
			if (Keyboard_Get(KEY_INPUT_LEFT) >= 1 && Keyboard_Get(KEY_INPUT_RIGHT) >= 1)
			{
				c->Chara_soeji = 0;
			}

			//上矢印キーを押したら
			if (Keyboard_Get(KEY_INPUT_UP) >= 1 && ATTACK_flag == false)
			{
				ATTACK_flag = true;
				a->A_X = c->Chara_X;
				a->A_Y = c->Chara_Y - ATTACK_SYOKI_Y;
			}

			if (ATTACK_flag == true)
			{
				DrawRotaGraph(GAME_Chara_Set_X + a->A_X, GAME_Chara_Set_Y + a->A_Y, 3.0, 0.0, a->A_Handle[a->A_soeji], TRUE);
				a->A_Y -= GAME_ATTACK_Y;

			}
			
			if (GAME_Chara_Set_Y + a->A_Y < GAME_MIN_WIDTH)
			{
				ATTACK_flag = false;
				
			}
			//プレイ画面のとき、キャラクターを拡大して描画
			DrawRotaGraph(GAME_Chara_Set_X + c->Chara_X, GAME_Chara_Set_Y + c->Chara_Y, 3.0, 0.0, c->Handle[c->Chara_soeji], TRUE);
			

			break;
		//case GAME_CLEAR:
			//DrawGameClear();
			//break;

		//エンド画面なら
		case GAME_END:

			DrawGameEnd();

			break;

		default:
			break;
		}

		

		//MY_ALL_KEYDOWN_UPDATE();				//キーの状態を取得



		fps->Draw(0, 0);	//FPSの処理[描画]

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画

		fps->Wait();		//FPSの処理[待つ]
	}



	delete c;				//Charaクラスの解放
	delete a;				//ATTCKクラスの解放
	delete fps;				//FPSを破棄
	
	DxLib_End();			//ＤＸライブラリ使用の終了処理

	return 0;
}

//タイトル画面の設定
void DrawGameTitle()
{

	// 背景の画像を読み込む
	int imgBack_Title = LoadGraph(GAME_BackImage_TITLE);

	// 背景の画像を描画
	DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, imgBack_Title, false);


	int FontHandle_TITLE = CreateFontToHandle(NULL, 120, 3);			//文字の大きさ変更
	//描画する文字の位置を設定
	DrawStringToHandle(150, 100, "GAME START!", GetColor(255, 0, 255), FontHandle_TITLE);
	DrawString(0, 20, "Enterキーを押して下さい(プレイ画面へ遷移します)", GetColor(0, 255, 255));

	//エンターキーが押されたら
		//
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1)
		{
			gamestate_senni = GAME_PLAY;	//シーンをゲーム画面に変更
		}


	// 作成したフォントデータを削除する
	DeleteFontToHandle(FontHandle_TITLE);
}

//プレイ画面の設定
void DrawGamePlay()
{

	// 背景の画像を読み込む
	int imgBack_Play = LoadGraph(GAME_BackImage_PLAY);

	// 背景の画像を描画
	DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, imgBack_Play, false);

	int FontHandle_PLAY = CreateFontToHandle(NULL, 30, 3);			//文字の大きさ変更
	//DrawString(0, 20, "Spaceキーを押して下さい(エンド画面へ遷移します)", GetColor(255, 0, 255));
	DrawStringToHandle(0, 50, "Spaceキーを押して下さい(エンド画面へ遷移します)", GetColor(255, 0, 255), FontHandle_PLAY);
	DrawStringToHandle(0, 80, "矢印キーで移動してね！(上矢印キーは攻撃ボタンだよ！)", GetColor(255, 0, 255), FontHandle_PLAY);
	

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


	// 背景の画像を読み込む
	int imgBack_End = LoadGraph(GAME_BackImage_END);

	// 背景の画像を描画
	DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, imgBack_End, false);

	int FontHandle_END = CreateFontToHandle(NULL, 20, 3);			//文字の大きさ変更
	DrawString(0, 20, "BackSpaceキーを押して下さい(タイトル画面へ遷移します)", GetColor(0, 255, 255));	//BackSpaceキーの説明
	DrawString(0, 40, "Escapeキーを押して下さい(ゲームが終了します)", GetColor(255, 255, 0));		//Escapeキーの説明
	DrawStringToHandle(0, 60, "お疲れさまでした！また挑戦してね！", GetColor(0, 155, 155), FontHandle_END);


	
	//バックスペースキーが押されたら
	if (Keyboard_Get(KEY_INPUT_BACK) == 1)
	{
		gamestate_senni = GAME_TITLE;//シーンをゲーム画面に変更
	}

	//エスケープキーが押されたら
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		DxLib_End();			//ＤＸライブラリ使用の終了処理
	}

	DeleteFontToHandle(FontHandle_END);
}

/*
int RANDOM()
{
	std::random_device rd;

	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> random(1, 1280);
	return random(mt);
}
*/