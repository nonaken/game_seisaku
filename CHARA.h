#pragma once

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"

//########## �N���X�̒�` ##########
class CHARA
{
public:
	//Chara�̉摜��`��
	int Handle[12];
	int Chara_X = 0;	//�L�[����ɂ��A�L�����N�^�[��X�̐���
	int	Chara_Y = 0;	//�L�[����ɂ��A�L�����N�^�[��Y�̐���
	int Chara_soeji = 0;	//�L�����N�^�[�̉摜�؂�ւ��̓Y�����Ƃ��āA��������������
	
	CHARA();
	~CHARA();
};