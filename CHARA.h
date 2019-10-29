#pragma once

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"

//########## クラスの定義 ##########
class CHARA
{
public:
	//Charaの画像を描画
	int Handle[12];
	int Chara_X = 0;	//キー操作による、キャラクターのXの制御
	int	Chara_Y = 0;	//キー操作による、キャラクターのYの制御
	int Chara_soeji = 0;	//キャラクターの画像切り替えの添え字として、役割を持たせる
	
	CHARA();
	~CHARA();
};