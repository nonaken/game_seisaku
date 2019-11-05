#pragma once
#include "DxLib.h"

int RANDOM_soeji();

class EnemyCharacter
{
public:
	int	Enemy_Handle[12];
	int Enemy_X = 0;	//キー操作による、キャラクターのXの制御
	int	Enemy_Y = 0;	//キー操作による、キャラクターのYの制御
	int Enemy_Speed = 5;

	int Enemy_soeji = RANDOM_soeji();	//キャラクターの画像切り替えの添え字として、役割を持たせる
	int Enemy_tokuten = 0;
	int Enemy_GOUKEI_SCORE = 0;

	int Enemy_flag = false;		//敵が画面外にいるのか、いないのかを判断する
	
	EnemyCharacter();
	~EnemyCharacter();
	
};


