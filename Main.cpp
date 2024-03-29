//##########ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "FPS.h"
#include "Keyboard.h"
#include "CHARA.h"
#include "Enemycharacter.h"
#include <random>

//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <math.h>

//########## マクロ定義 ##########
#define GAME_WIDTH		1280	//画面の横の大きさ(画面右端の限界値)
#define GAME_MIN_WIDTH	 0		//画面左端の限界値
#define GAME_HEIGHT		640		//画面の縦の大きさ
#define GAME_MIN_HEIGHT 0		//画面上の限界値
#define GAME_COLOR		32		//画面のカラービット

#define GAME_WIDTH_CENTER_X		GAME_WIDTH / 2		//画面の半分の長さ
#define GAME_HEIGHT_CENTER_Y	GAME_HEIGHT / 2		//画面の半分の高さ

#define GAME_WINDOW_NAME	"GAME PLAY!"		//ウィンドウのタイトル
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE：ウィンドウモード / FALSE：フルスクリーン

#define SET_WINDOW_ST_MODE_DEFAULT			0	//デフォルト
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//タイトルバーなし
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//タイトルバーとフレームなし
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//フレームなし

#define GAME_FPS_SPEED					   60

#define GAME_BackImage_TITLE	"BackImage\\pipo-battlebg010b.jpg"			//タイトル画面背景画像

#define GAME_BackImage_PLAY		"BackImage\\pipo-battlebg002b.jpg"	//プレイ画面背景画像
#define GAME_CharaImage_PLAY	"クリスマスキャラチップ\\雪だるま_透過処理.png"			//キャラクター画像
#define GAME_CharaImage_PLAY_ATTACK "クリスマスキャラチップ\\攻撃(赤雪だるま)_透過処理.png"		//攻撃画像
#define GAME_BallImage_Play		"Enemy\\骨_透過処理.png"		//プレイ画面で使うボールの画像

#define GAME_BackImage_END		"BackImage\\pipo-battlebg020b.jpg"	//エンド画面背景画像

#define GAME_Chara_Set_X		GAME_WIDTH / 2		//キャラクターの初期X位置(中央)
#define GAME_Chara_Set_Y		GAME_HEIGHT / 2				//キャラクターの初期X位置

#define CHARA_SPPED	10	//キャラクターの移動スピード

#define ATTACK_SYOKI_X	50	//攻撃画像の初期X値
#define ATTACK_SYOKI_Y	100	//攻撃画像の初期Y値
#define GAME_ATTACK_Y	20	//攻撃速度

#define RESET_CHARA	0	//エネミーと衝突したら、　キャラの位置をリセット
#define RESET_ENEMY	0	//　キャラと衝突したら、エネミーの位置をリセット

#define CHARA_SIZE_X	96		//キャラクターのXサイズ
#define CHARA_SIZE_Y	96		//キャラクターのYサイズ
#define ATTACK_SIZE_X	96		//キャラクターのXサイズ
#define ATTACK_SIZE_Y	96		//キャラクターのYサイズ
#define HONE_SIZE_X		96		//エネミーのXサイズ
#define HONE_SIZE_Y		96		//エネミーのYサイズ

#define CHARA_Divide_Size_W		3	//キャラチップの横分割数
#define CHARA_Divide_Size_H		4	//キャラチップの縦分割数
#define ATTACK_Divide_Size_W	3	//アタック(キャラチップ)の横分割数
#define ATTACK_Divide_Size_H	4	//アタック(キャラチップ)の縦分割数
#define Enemy_Divide_Size_W		3	//エネミーチップの横分割数
#define Enemy_Divide_Size_H		4	//エネミーチップの縦分割数

#define CHARA_Divide_All	12		//キャラチップの分割総数
#define ATTACK_Divide_All	12		//アタック(キャラチップの)分割総数
#define ENEMY_Divide_All	12		//エネミーチップの分割総数

#define LIMIT_TIME 60		//制限時間
#define PLAY_END_TIME 0		//制限時間が0秒になったらの条件式に使う

//列挙型で各画面を管理
enum GameState
{
GAME_TITLE,		//タイトル画面
GAME_PLAY,		//プレイ画面
//GAME_CLEAR,
GAME_END		//エンド画面
};

//ゲーム画面の遷移を管理する
GameState gamestate_senni = GAME_TITLE;	//画面遷移をコントロールする(最初の画面はタイトル画面)

//各画面を管理するプロトタイプ宣言
void DrawGameTitle();
void DrawGamePlay();

//void DrawGameClear();
void DrawGameEnd();

int WINDOW_WIDTH_RANDOM();	//エネミーのX位置乱数を生成する関数
int RANDOM_soeji();			//エネミーの画像を乱数で生成する関数

CHARA *c = new CHARA();
ATTACK *a = new ATTACK();
EnemyCharacter *e = new  EnemyCharacter();



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
	
	int ATTACK_flag = false;	//攻撃中か攻撃していないかを判断するフラグ
	

	int Chara_Size, Attack_Size, Enemy_Size;	//画像の横と縦のサイズを調べるための変数
	int Chara_Size_W, Chara_Size_H, Attack_Size_W, Attack_Size_H, Enemy_Size_W, Enemy_Size_H;	//画像の横、縦のサイズを記憶する

	//現在の時間を取得
	int Get_Time = GetNowCount();

	int FontHandle_LIMIT = CreateFontToHandle(NULL, 60, 3);	//文字の大きさ変更

	LoadDivGraph(GAME_CharaImage_PLAY, CHARA_Divide_All, CHARA_Divide_Size_W, CHARA_Divide_Size_H, CHARA_SIZE_X, CHARA_SIZE_Y, &c->Handle[0]);	//キャラ画像の分割数、大きさ、ハンドル値を設定
	LoadDivGraph(GAME_CharaImage_PLAY_ATTACK, ATTACK_Divide_All, ATTACK_Divide_Size_W, ATTACK_Divide_Size_H, ATTACK_SIZE_X, ATTACK_SIZE_Y, &a->A_Handle[0]);	//攻撃画像の分割数、大きさ、ハンドル値を設定
	LoadDivGraph(GAME_BallImage_Play, ENEMY_Divide_All, Enemy_Divide_Size_W, Enemy_Divide_Size_H, HONE_SIZE_X, HONE_SIZE_Y, &e->Enemy_Handle[0]);	//エネミー画像の分割数、大きさ、ハンドル値を設定

	Chara_Size = LoadGraph(GAME_CharaImage_PLAY);			//キャラ画像　の縦と横のサイズを取得するためロードする(すぐに捨てる)
	Attack_Size = LoadGraph(GAME_CharaImage_PLAY_ATTACK);	//攻撃(キャラクター)画像の縦と横のサイズを取得するためロードする(すぐに捨てる)
	Enemy_Size = LoadGraph(GAME_BallImage_Play);			//エネミー画像の縦と横のサイズを取得するためロードする(すぐに捨てる)


	GetGraphSize(Chara_Size, &Chara_Size_W, &Chara_Size_H);	//キャラ画像　の縦と横のサイズを取得
	GetGraphSize(Attack_Size, &Attack_Size_W, &Attack_Size_H); //攻撃(キャラクター)画像の縦と横のサイズを取得
	GetGraphSize(Enemy_Size, &Enemy_Size_W, &Enemy_Size_H); //エネミー画像の縦と横のサイズを取得

	DeleteGraph(Chara_Size);//キャラ画像　の縦と横のサイズを取得したら、使い捨て
	DeleteGraph(Attack_Size);//キャラ画像　の縦と横のサイズを取得したら、使い捨て
	DeleteGraph(Enemy_Size);//エネミー画像の縦と横のサイズを取得したら、使い捨て


	while (TRUE)	//無限ルー
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

			//制限時間の表示
			DrawFormatStringToHandle(500, 0, GetColor(255, 255, 255), FontHandle_LIMIT, "LIMIT_TIME：%d秒", (LIMIT_TIME - (GetNowCount() - Get_Time) / 1000));	//文字の大きさ変更);

			
			//エネミーの得点
			for (int i = 0; i < 11; i++)
			{
				e->Enemy_tokuten = (e->Enemy_soeji + 1)* 10;
			}
			

			//制限時間が0秒になったら
			if (LIMIT_TIME - (GetNowCount() - Get_Time) / 1000 <= PLAY_END_TIME)
			{
				gamestate_senni = GAME_END;
			}
			//エネミーが画面外にいるなら
			if (e->Enemy_flag == false)
			{
				e->Enemy_X = WINDOW_WIDTH_RANDOM();
				e->Enemy_soeji = RANDOM_soeji();
				e->Enemy_flag = true;
			}

			//エネミーが画面内にいるなら
			if (e->Enemy_flag == true)
			{
				e->Enemy_Y += e->Enemy_Speed;
			}
				
			//エネミーを表示
			DrawGraph(e->Enemy_X, e->Enemy_Y, e->Enemy_Handle[e->Enemy_soeji], TRUE);

			//エネミーの当たり判定を表示
			DrawBox(e->Enemy_X, e->Enemy_Y,
				e->Enemy_X + Enemy_Size_W / Enemy_Divide_Size_W,
				e->Enemy_Y + Enemy_Size_H / Enemy_Divide_Size_H,
				GetColor(255, 0, 255), FALSE);

			
			//エネミーが下画面を超えたら
			if (e->Enemy_Y > GAME_HEIGHT)
			{
				e->Enemy_Y = 0;
				e->Enemy_flag = false;
			}

			//左矢印キーを押し続けたら
			if (Keyboard_Get(KEY_INPUT_LEFT) >= 1)
			{
				c->Chara_soeji = 3;
				//キャラクターのX座標が左画面外に行かないように移動する
				if (GAME_Chara_Set_X + c->Chara_X >= GAME_MIN_WIDTH) 
				{
					c->Chara_X -= CHARA_SPPED;
				}
			}

			//右矢印キーを押し続けたら
			if (Keyboard_Get(KEY_INPUT_RIGHT) >= 1)
			{
				c->Chara_soeji = 6;
				//キャラクターのX座標が右画面外に行かないように移動する
				if (c->Chara_X <= GAME_WIDTH - GAME_Chara_Set_X - Chara_Size_W / CHARA_Divide_Size_W)
				{
					c->Chara_X += CHARA_SPPED;
				}
			}

			//上矢印キーを押し続けたら
			if (Keyboard_Get(KEY_INPUT_UP) >= 1)
			{
				c->Chara_soeji = 9;
				//キャラクターのX座標が右画面外に行かないように移動する
				if (c->Chara_Y + GAME_Chara_Set_Y >= GAME_MIN_HEIGHT)
				{
					c->Chara_Y -= CHARA_SPPED;
				}
			}

			//下矢印キーを押し続けたら
			if (Keyboard_Get(KEY_INPUT_DOWN) >= 1)
			{
				c->Chara_soeji = 0;
				//キャラクターのY座標が下画面外に行かないように移動する
				if (c->Chara_Y + GAME_Chara_Set_Y + Chara_Size_H / CHARA_Divide_Size_H <= GAME_HEIGHT)
				{
					c->Chara_Y += CHARA_SPPED;
				}
			}
			//左矢印キーと右矢印キーを同時押したら
			if (Keyboard_Get(KEY_INPUT_LEFT) >= 1 && Keyboard_Get(KEY_INPUT_RIGHT) >= 1)
			{
				c->Chara_soeji = 0;
			}

			//Aキーを押したら
			if (Keyboard_Get(KEY_INPUT_A) >= 1 && ATTACK_flag == false)
			{
				ATTACK_flag = true;
				a->A_X = c->Chara_X;
				a->A_Y = c->Chara_Y - ATTACK_SYOKI_Y;
			}

			//攻撃していたら
			if (ATTACK_flag == true)
			{
				

				//攻撃の当たり判定を表示
				DrawBox(a->A_X + GAME_Chara_Set_X, a->A_Y + GAME_Chara_Set_Y, 
					a->A_X + Attack_Size_W / ATTACK_Divide_Size_W + GAME_Chara_Set_X,
					a->A_Y + Attack_Size_H / ATTACK_Divide_Size_H + GAME_Chara_Set_Y,
					GetColor(255, 0, 0), FALSE);

				//攻撃画像を上に移動
				a->A_Y -= GAME_ATTACK_Y;

				//攻撃画像を描画
				DrawGraph(GAME_Chara_Set_X + a->A_X, GAME_Chara_Set_Y + a->A_Y, a->A_Handle[a->A_soeji], TRUE);


			}

			
			
			//攻撃した画像が上画面を超えたら
			if (GAME_Chara_Set_Y + a->A_Y < GAME_MIN_HEIGHT)
			{
				ATTACK_flag = false;
			}
			
			

				//キャラの当たり判定を表示
			DrawBox(c->Chara_X + GAME_Chara_Set_X, c->Chara_Y + GAME_Chara_Set_Y,
				c->Chara_X + Chara_Size_W / CHARA_Divide_Size_W + GAME_Chara_Set_X,
				c->Chara_Y + Chara_Size_H / CHARA_Divide_Size_H + GAME_Chara_Set_Y,
				GetColor(0, 0, 255), FALSE);

			
				//キャラとエネミーの当たり判定
			if (((GAME_Chara_Set_X + c->Chara_X > e->Enemy_X && GAME_Chara_Set_X + c->Chara_X < e->Enemy_X + Enemy_Size_W / Enemy_Divide_Size_W) ||
				(e->Enemy_X > GAME_Chara_Set_X + c->Chara_X && e->Enemy_X < GAME_Chara_Set_X + c->Chara_X + Chara_Size_W / CHARA_Divide_Size_W)) &&
				((GAME_Chara_Set_Y + c->Chara_Y > e->Enemy_Y && GAME_Chara_Set_Y + c->Chara_Y < e->Enemy_Y + Enemy_Size_H / Enemy_Divide_Size_H) ||
				(e->Enemy_Y > GAME_Chara_Set_Y + c->Chara_Y && e->Enemy_Y < GAME_Chara_Set_Y + c->Chara_Y + Chara_Size_H / CHARA_Divide_Size_H)))
			{
				//接触している場合はキャラとエネミーの位置をリセットし、エンド画面に飛ぶ
				c->Chara_X = RESET_CHARA;
				c->Chara_Y = RESET_CHARA;

				e->Enemy_X = WINDOW_WIDTH_RANDOM();	//エネミーのX座標だけ、１〜横の画面サイズ分の値を乱数でリセット
				e->Enemy_Y = RESET_ENEMY;

				gamestate_senni = GAME_END;
			}



			   //攻撃(キャラ)画像とエネミーの当たり判定
			if (((GAME_Chara_Set_X + a->A_X > e->Enemy_X && GAME_Chara_Set_X + a->A_X < e->Enemy_X + Enemy_Size_W / Enemy_Divide_Size_W) ||
				(e->Enemy_X > GAME_Chara_Set_X + a->A_X && e->Enemy_X < GAME_Chara_Set_X + a->A_X + Chara_Size_W / ATTACK_Divide_Size_W)) &&
				((GAME_Chara_Set_Y + a->A_Y > e->Enemy_Y && GAME_Chara_Set_Y + a->A_Y < e->Enemy_Y + Enemy_Size_H / Enemy_Divide_Size_H) ||
				(e->Enemy_Y > GAME_Chara_Set_Y + a->A_Y && e->Enemy_Y < GAME_Chara_Set_Y + a->A_Y + Chara_Size_H / ATTACK_Divide_Size_H))
				&&
				//攻撃画像が表示されていたら
				ATTACK_flag == true)
			{
				e->Enemy_X = WINDOW_WIDTH_RANDOM();	//エネミーのX座標だけ、１〜横の画面サイズ分の値を乱数でリセット
				e->Enemy_soeji = RANDOM_soeji();
				e->Enemy_Y = RESET_ENEMY;

				//エネミーに攻撃を当てたら、得点を追加
				e->Enemy_GOUKEI_SCORE += e->Enemy_tokuten;

				//攻撃フラグを解除する(offにする)
				ATTACK_flag = false;
			}


			

			
			//DrawRotaGraph(c->Chara_X, GAME_Chara_Set_Y + c->Chara_Y, 1.0, 0.0, c->Handle[c->Chara_soeji], TRUE);
		
			

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
	delete e;				//EnemyCharacterクラスの解放
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


	int FontHandle_TITLE = CreateFontToHandle(NULL, 120, 3);	//文字の大きさ変更
	int FontHandle_ENTER = CreateFontToHandle(NULL, 50, 3);		//文字の大きさ変更

	//描画する文字の位置を設定
	DrawStringToHandle(GAME_WIDTH_CENTER_X / 2, GAME_HEIGHT_CENTER_Y / 2, "GAME START!", GetColor(255, 0, 255), FontHandle_TITLE);
	DrawStringToHandle(50, 100, "Enterキーを押して下さい(プレイ画面へ遷移します)", GetColor(0, 255, 255), FontHandle_ENTER);

	//エンターキーが押されたら
		//
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1)
		{
			gamestate_senni = GAME_PLAY;	//シーンをゲーム画面に変更
		}

		//総SCOREのリセット
		e->Enemy_GOUKEI_SCORE = 0;
		
		// 作成したフォントデータを削除する
		DeleteFontToHandle(FontHandle_TITLE);
		DeleteFontToHandle(FontHandle_ENTER);
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
	int FontHandle_PLAY_SCORE = CreateFontToHandle(NULL, 60, 3);			//文字の大きさ変更

	DrawStringToHandle(0, 50, "Spaceキーを押すか、敵に触れると、エンド画面へ遷移します", GetColor(255, 0, 255), FontHandle_PLAY);
	DrawStringToHandle(0, 100, "矢印キーで移動してね！", GetColor(0, 51, 255), FontHandle_PLAY);
	DrawStringToHandle(0, 150, "Aボタンで攻撃できるよ！\n(攻撃した画像が消えたら、もう一度打てます。)", GetColor(102, 0, 255), FontHandle_PLAY);
	

	//プレイ画面のとき、キャラクターを描画
	DrawGraph(GAME_Chara_Set_X + c->Chara_X, GAME_Chara_Set_Y + c->Chara_Y, c->Handle[c->Chara_soeji], TRUE);

	

	//合計スコアを表示
	DrawFormatStringToHandle(100, 250, GetColor(255, 255, 0), FontHandle_PLAY_SCORE, "現在の総SCORE:%d", e->Enemy_GOUKEI_SCORE);


	//スペースキーが押されたら
	if (Keyboard_Get(KEY_INPUT_SPACE) == 1)
	{
		gamestate_senni = GAME_END;//シーンをゲーム画面に変更
	}

	// 作成したフォントデータを削除する
	DeleteFontToHandle(FontHandle_PLAY);
	DeleteFontToHandle(FontHandle_PLAY_SCORE);
}

//エンド画面の設定
void DrawGameEnd()
{


	// 背景の画像を読み込む
	int imgBack_End = LoadGraph(GAME_BackImage_END);

	// 背景の画像を描画
	DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, imgBack_End, false);

	int FontHandle_END = CreateFontToHandle(NULL, 50, 3);			//文字の大きさ変更
	int FontHandle_END_SCORE = CreateFontToHandle(NULL, 120, 3);			//文字の大きさ変更

	DrawString(0, 20, "BackSpaceキーを押して下さい(タイトル画面へ遷移します)", GetColor(0, 255, 255));	//BackSpaceキーの説明
	DrawString(0, 40, "Escapeキーを押して下さい(ゲームが終了します)", GetColor(255, 255, 0));		//Escapeキーの説明
	DrawStringToHandle(GAME_WIDTH_CENTER_X / 2, GAME_HEIGHT_CENTER_Y / 2 , "お疲れさまでした！\nまた挑戦してね！", GetColor(0, 155, 155), FontHandle_END);

	//合計スコアを表示
	DrawFormatStringToHandle(50, 330, GetColor(255, 255, 0), FontHandle_END_SCORE, "あなたの総SCORE:%d", e->Enemy_GOUKEI_SCORE);

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


	//作成したフォントデータを削除する
	DeleteFontToHandle(FontHandle_END);
	DeleteFontToHandle(FontHandle_END_SCORE);
}

//乱数を生成する関数
int WINDOW_WIDTH_RANDOM()
{
	std::random_device rd;

	std::mt19937 mt(rd());

	//1〜画面サイズの横幅までを乱数で決める
	std::uniform_int_distribution<int> WINDOW_WIDTH_RANDOM(1 + HONE_SIZE_X, GAME_WIDTH - HONE_SIZE_X);
	return WINDOW_WIDTH_RANDOM(mt);
}

//乱数を生成する関数
int RANDOM_soeji()
{
	std::random_device rd;

	std::mt19937 mt(rd());

	//1〜画面サイズの横幅までを乱数で決める
	std::uniform_int_distribution<int> RANDOM_soeji(0, ENEMY_Divide_All - 1);
	return RANDOM_soeji(mt);
}