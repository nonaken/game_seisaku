#pragma once
#include "DxLib.h"


class EnemyCharacter
{
public:
	int	Enemy_Handle[12];
	int Enemy_X = 0;	//キー操作による、キャラクターのXの制御
	int	Enemy_Y = 0;	//キー操作による、キャラクターのYの制御

	int Enemy_soeji = 0;	//キャラクターの画像切り替えの添え字として、役割を持たせる
	

	int Enemy_flag = false;		//敵が画面外にいるのか、いないのかを判断する
	
	EnemyCharacter();
	~EnemyCharacter();
	
};


