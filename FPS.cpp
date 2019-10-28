/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* fps.cpp     																					   */
/* FPS(Flame Per Second)�N���X																	   */
/* ��̃C���X�^���X�݂̂ɂ���																	   */

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "FPS.hpp"

//########## �N���X�̒�` ##########

//�R���X�g���N�^
FPS::FPS(int fps_value)
{
	this->value = fps_value;
	this->drawValue = 0;
	this->calcStartTime = 0;
	this->calcEndTime = 0;
	this->flameCount = 0;
	this->calcAverage = (double)value;

	return;
}

//�w�肵��FPS�ɂȂ�悤�ɑ҂�
VOID FPS::Wait(VOID)
{
	//���݂̎������~���b�Ŏ擾
	DWORD nowTime = GetTickCount();

	//1�t���[���ڂ�����ۂɂ����������Ԃ��v�Z
	DWORD keikaTime = nowTime - this->calcStartTime;

	//�[�����Z�΍�
	if (this->value > 0)
	{
		//�҂ׂ����� = �t���[�������Ƃɂ�����ׂ����� - ���ۂɂ�����������;
		int wait_tm = (this->flameCount * 1000 / this->value) - (keikaTime);

		//�҂ׂ����Ԃ��������ꍇ
		if (wait_tm > 0)
		{
			//�~���b���A�����𒆒f����
			Sleep(wait_tm);
		}
	}

	return;
}

//��ʍX�V�̎������擾����
VOID FPS::Update(VOID)
{
	//1�t���[���ڂȂ玞�����L��
	if (this->flameCount == 0)
	{
		//Windows���N�����Ă��猻�݂܂ł̎������~���b�Ŏ擾
		this->calcStartTime = GetTickCount();
	}

	//�w��t���[���̍Ō�̃t���[���Ȃ�A���ς��v�Z����
	if (this->flameCount == this->calcAverage)
	{
		//Windows���N�����Ă��猻�݂܂ł̎������~���b�Ŏ擾
		this->calcEndTime = GetTickCount();

		//���ϓI��FPS�l���v�Z
		this->drawValue = 1000.0f / ((this->calcEndTime - this->calcStartTime) / this->calcAverage);

		//����FPS�v�Z�̏���
		this->calcStartTime = this->calcEndTime;

		//�J�E���g������
		this->flameCount = 0;
	}

	//�t���[�����J�E���g�A�b�v
	this->flameCount++;

	return;
}

//FPS�̒l��\������
VOID FPS::Draw(int drawX, int drawY)
{
	//�������`��
	DrawFormatString(drawX, drawY, GetColor(255, 255, 255), "FPS:%.1f", this->drawValue);
	return;
}

//�f�X�g���N�^
FPS::~FPS()
{
	return;
}