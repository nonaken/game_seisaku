#pragma once
#include "DxLib.h"


class EnemyCharacter
{
public:
	int	Enemy_Handle[12];
	int Enemy_X = 0;	//�L�[����ɂ��A�L�����N�^�[��X�̐���
	int	Enemy_Y = 0;	//�L�[����ɂ��A�L�����N�^�[��Y�̐���

	int Enemy_soeji = 0;	//�L�����N�^�[�̉摜�؂�ւ��̓Y�����Ƃ��āA��������������
	

	int Enemy_flag = false;		//�G����ʊO�ɂ���̂��A���Ȃ��̂��𔻒f����
	
	EnemyCharacter();
	~EnemyCharacter();
	
};


