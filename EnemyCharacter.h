#pragma once
#include "DxLib.h"

int RANDOM_soeji();

class EnemyCharacter
{
public:
	int	Enemy_Handle[12];
	int Enemy_X = 0;	//�L�[����ɂ��A�L�����N�^�[��X�̐���
	int	Enemy_Y = 0;	//�L�[����ɂ��A�L�����N�^�[��Y�̐���
	int Enemy_Speed = 5;

	int Enemy_soeji = RANDOM_soeji();	//�L�����N�^�[�̉摜�؂�ւ��̓Y�����Ƃ��āA��������������
	int Enemy_tokuten = 0;
	int Enemy_GOUKEI_SCORE = 0;

	int Enemy_flag = false;		//�G����ʊO�ɂ���̂��A���Ȃ��̂��𔻒f����
	
	EnemyCharacter();
	~EnemyCharacter();
	
};


