//##########�w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "FPS.h"
#include "Keyboard.h"
#include "CHARA.h"
#include "Enemycharacter.h"

//#include <iostream>
#include <random>




//#include <cstdlib>
//#include <ctime>

#include <math.h>

//########## �}�N����` ##########
#define GAME_WIDTH	1280		//��ʂ̉��̑傫��(��ʉE�[�̌��E�l)
#define GAME_MIN_WIDTH 0		//��ʍ��[�̌��E�l
#define GAME_HEIGHT 950			//��ʂ̏c�̑傫��
#define GAME_MIN_HEIGHT 0		//��ʏ�̌��E�l
#define GAME_COLOR	32			//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_NAME	"GAME PLAY!"		//�E�B���h�E�̃^�C�g��
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE�F�E�B���h�E���[�h / FALSE�F�t���X�N���[��

#define SET_WINDOW_ST_MODE_DEFAULT			0	//�f�t�H���g
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//�^�C�g���o�[�Ȃ�
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//�^�C�g���o�[�ƃt���[���Ȃ�
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//�t���[���Ȃ�

#define GAME_FPS_SPEED					   60

#define GAME_BackImage_TITLE	"BackImage\\�F��.jpg"			//�^�C�g����ʔw�i�摜

#define GAME_BackImage_PLAY		"BackImage\\pipo-battlebg002b.jpg"	//�v���C��ʔw�i�摜
#define GAME_CharaImage_PLAY	"�N���X�}�X�L�����`�b�v\\�Ⴞ���_���ߏ���.png"			//�L�����N�^�[�摜
#define GAME_CharaImage_PLAY_ATTACK "�N���X�}�X�L�����`�b�v\\pipo-xmaschara06.png"		//�U���摜
#define GAME_BallImage_Play		"Enemy\\��_���ߏ���.png"		//�v���C��ʂŎg���{�[���̉摜

#define GAME_BackImage_END		"BackImage\\pipo-battlebg020b.jpg"	//�G���h��ʔw�i�摜

#define GAME_Chara_Set_X		GAME_WIDTH / 2		//�L�����N�^�[�̏���X�ʒu(����)
#define GAME_Chara_Set_Y		700					//�L�����N�^�[�̏���X�ʒu

#define CHARA_SPPED	10	//�L�����N�^�[�̈ړ��X�s�[�h

#define ATTACK_SYOKI_X	50	//�U���摜�̏���X�l
#define ATTACK_SYOKI_Y	100	//�U���摜�̏���Y�l
#define GAME_ATTACK_Y	20	//�U�����x

#define ENEMY_Down_Speed 7	//�G�l�~�[�̗������x

#define RESET_CHARA	0	//�G�l�~�[�ƏՓ˂�����A�@�L�����̈ʒu�����Z�b�g
#define RESET_ENEMY	0	//�@�L�����ƏՓ˂�����A�G�l�~�[�̈ʒu�����Z�b�g

#define CHARA_SIZE_X	96		//�L�����N�^�[��X�T�C�Y
#define CHARA_SIZE_Y	96		//�L�����N�^�[��Y�T�C�Y
#define HONE_SIZE_X		96		//�G�l�~�[��X�T�C�Y
#define HONE_SIZE_Y		96		//�G�l�~�[��Y�T�C�Y

#define CHARA_Divide_Size_W		3	//�L�����`�b�v�̉�������
#define CHARA_Divide_Size_H		4	//�L�����`�b�v�̏c������
#define ATTACK_Divide_Size_W	3	//�A�^�b�N(�L�����`�b�v)�̉�������
#define ATTACK_Divide_Size_H	4	//�A�^�b�N(�L�����`�b�v)�̏c������
#define Enemy_Divide_Size_W		3	//�G�l�~�[�`�b�v�̉�������
#define Enemy_Divide_Size_H		4	//�G�l�~�[�`�b�v�̏c������

#define CHARA_Divide_All	12		//�L�����`�b�v�̕�������
#define ATTACK_Divide_All	12		//�A�^�b�N(�L�����`�b�v��)��������
#define ENEMY_Divide_All	12		//�G�l�~�[�`�b�v�̕�������


//�񋓌^�Ŋe��ʂ��Ǘ�
enum GameState
{
	GAME_TITLE,		//�^�C�g�����
	GAME_PLAY,		//�v���C���
	//GAME_CLEAR,
	GAME_END		//�G���h���
};

//�Q�[����ʂ̑J�ڂ��Ǘ�����
GameState gamestate_senni = GAME_TITLE;	//��ʑJ�ڂ��R���g���[������(�ŏ��̉�ʂ̓^�C�g�����)

//�e��ʂ��Ǘ�����v���g�^�C�v�錾
void DrawGameTitle();
void DrawGamePlay();
//void DrawGameClear();
void DrawGameEnd();

int RANDOM();	//�����𐶐�����֐�





//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	

	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//�w��̐��l�ŉ�ʂ�\������

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//�^�C�g���o�[����

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//�^�C�g���̕���

	if (DxLib_Init() == -1) { return -1; }						//�c�w���C�u��������������
	
	SetDrawScreen(DX_SCREEN_BACK);								//Draw�n�֐��͗���ʂɕ`��

	FPS *fps = new FPS(GAME_FPS_SPEED);							//FPS�N���X�̃I�u�W�F�N�g�𐶐�


	//���I�̈���m�ۂ���
	CHARA *c = new CHARA();
	ATTACK *a = new ATTACK();
	EnemyCharacter *e = new  EnemyCharacter();

	int ATTACK_flag = false;	//�U�������U�����Ă��Ȃ����𔻒f����t���O
	int Enemy_flag = false;		//�G����ʊO�ɂ���̂��A���Ȃ��̂��𔻒f����
	int Chara_Size, Attack_Size, Enemy_Size;	//�摜�̉��Əc�̃T�C�Y�𒲂ׂ邽�߂̕ϐ�
	int Chara_Size_W, Chara_Size_H, Attack_Size_W, Attack_Size_H, Enemy_Size_W, Enemy_Size_H;	//�摜�̉��A�c�̃T�C�Y���L������
	
	LoadDivGraph(GAME_CharaImage_PLAY, CHARA_Divide_All, CHARA_Divide_Size_W, CHARA_Divide_Size_H, CHARA_SIZE_X, CHARA_SIZE_Y, &c->Handle[0]);	//�L�����摜�̕������A�傫���A�n���h���l��ݒ�
	LoadDivGraph(GAME_CharaImage_PLAY_ATTACK, ATTACK_Divide_All, ATTACK_Divide_Size_W, ATTACK_Divide_Size_H, 32, 32, &a->A_Handle[0]);	//�U���摜�̕������A�傫���A�n���h���l��ݒ�
	LoadDivGraph(GAME_BallImage_Play, ENEMY_Divide_All, Enemy_Divide_Size_W, Enemy_Divide_Size_H, HONE_SIZE_X, HONE_SIZE_X, &e->Enemy_Handle[0]);	//�G�l�~�[�摜�̕������A�傫���A�n���h���l��ݒ�

	Chara_Size = LoadGraph(GAME_CharaImage_PLAY);	//�L�����摜�@�̏c�Ɖ��̃T�C�Y���擾���邽�߃��[�h����(�����Ɏ̂Ă�)
	Enemy_Size = LoadGraph(GAME_BallImage_Play);	//�G�l�~�[�摜�̏c�Ɖ��̃T�C�Y���擾���邽�߃��[�h����(�����Ɏ̂Ă�)
	GetGraphSize(Chara_Size, &Chara_Size_W, &Chara_Size_H);	//�L�����摜�@�̏c�Ɖ��̃T�C�Y���擾
	GetGraphSize(Enemy_Size, &Enemy_Size_W, &Enemy_Size_H); //�G�l�~�[�摜�̏c�Ɖ��̃T�C�Y���擾

	DeleteGraph(Chara_Size);//�L�����摜�@�̏c�Ɖ��̃T�C�Y���擾������A�g���̂�
	DeleteGraph(Enemy_Size);//�G�l�~�[�摜�̏c�Ɖ��̃T�C�Y���擾������A�g���̂�


	while (TRUE)	//�������[�v
	{

		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��

		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		
		Keyboard_Update();   //�L�[�{�[�h�̍X�V

		fps->Update();		//FPS�̏���[�X�V]

		//��ʂ̐؂�ւ��Ǘ�
		switch (gamestate_senni)
		{
		//�^�C�g����ʂȂ�
		case GAME_TITLE:
			DrawGameTitle();
			break;

		//�v���C��ʂȂ�
		case GAME_PLAY:
			DrawGamePlay();
			
			//�G�l�~�[����ʊO�ɂ���Ȃ�
			if (Enemy_flag == false)
			{
				e->Enemy_X = RANDOM();
				Enemy_flag = true;
			}

			//�G�l�~�[����ʓ��ɂ���Ȃ�
			if (Enemy_flag == true)
			{
				e->Enemy_Y += ENEMY_Down_Speed;
				DrawGraph(e->Enemy_X, e->Enemy_Y, e->Enemy_Handle[e->Enemy_soeji], TRUE);
			}
			
			//�G�l�~�[������ʂ𒴂�����
			if (e->Enemy_Y > GAME_HEIGHT)
			{
				e->Enemy_Y = 0;
				Enemy_flag = false;
			}

			//�����L�[��������������
			if (Keyboard_Get(KEY_INPUT_LEFT) >= 1)
			{
				c->Chara_soeji = 3;
				//�L�����N�^�[��X���W������ʊO�ɍs���Ȃ��悤�Ɉړ�����
				if (GAME_Chara_Set_X + c->Chara_X >= GAME_MIN_WIDTH) 
				{
					c->Chara_X -= CHARA_SPPED;
				}
			}

			//�E���L�[��������������
			if (Keyboard_Get(KEY_INPUT_RIGHT) >= 1)
			{
				c->Chara_soeji = 6;
				//�L�����N�^�[��X���W���E��ʊO�ɍs���Ȃ��悤�Ɉړ�����
				if (c->Chara_X <= GAME_WIDTH - GAME_Chara_Set_X)
				{
					c->Chara_X += CHARA_SPPED;
				}
			}

			//����L�[��������������
			if (Keyboard_Get(KEY_INPUT_UP) >= 1)
			{
				c->Chara_soeji = 9;
				//�L�����N�^�[��X���W���E��ʊO�ɍs���Ȃ��悤�Ɉړ�����
				if (c->Chara_Y + GAME_Chara_Set_Y >= GAME_MIN_HEIGHT)
				{
					c->Chara_Y -= CHARA_SPPED;
				}
			}

			//�����L�[��������������
			if (Keyboard_Get(KEY_INPUT_DOWN) >= 1)
			{
				c->Chara_soeji = 0;
				//�L�����N�^�[��X���W���E��ʊO�ɍs���Ȃ��悤�Ɉړ�����
				if (c->Chara_Y + GAME_Chara_Set_Y <= GAME_HEIGHT)
				{
					c->Chara_Y += CHARA_SPPED;
				}
			}
			//�����L�[�ƉE���L�[�𓯎���������
			if (Keyboard_Get(KEY_INPUT_LEFT) >= 1 && Keyboard_Get(KEY_INPUT_RIGHT) >= 1)
			{
				c->Chara_soeji = 0;
			}

			//A�L�[����������
			if (Keyboard_Get(KEY_INPUT_A) >= 1 && ATTACK_flag == false)
			{
				ATTACK_flag = true;
				a->A_X = c->Chara_X;
				a->A_Y = c->Chara_Y - ATTACK_SYOKI_Y;
			}

			//�U�����Ă�����
			if (ATTACK_flag == true)
			{
				DrawRotaGraph(GAME_Chara_Set_X + a->A_X, GAME_Chara_Set_Y + a->A_Y, 3.0, 0.0, a->A_Handle[a->A_soeji], TRUE);
				a->A_Y -= GAME_ATTACK_Y;

			}
			
			//�U�������摜�����ʂ𒴂�����
			if (GAME_Chara_Set_Y + a->A_Y < GAME_MIN_HEIGHT)
			{
				ATTACK_flag = false;
				
			}
			
			//�L�����ƃG�l�~�[�̓����蔻��
			if (((GAME_Chara_Set_X + c->Chara_X > e->Enemy_X && GAME_Chara_Set_X + c->Chara_X < e->Enemy_X + Enemy_Size_W / Enemy_Divide_Size_H)  ||
				(e->Enemy_X > GAME_Chara_Set_X + c->Chara_X && e->Enemy_X < GAME_Chara_Set_X + c->Chara_X + Chara_Size_W / CHARA_Divide_Size_W)) &&
				((GAME_Chara_Set_Y + c->Chara_Y > e->Enemy_Y && GAME_Chara_Set_Y + c->Chara_Y  < e->Enemy_Y + Enemy_Size_H / Enemy_Divide_Size_H) ||
				(e->Enemy_Y > GAME_Chara_Set_Y + c->Chara_Y && e->Enemy_Y < GAME_Chara_Set_Y + c->Chara_Y + Chara_Size_H / CHARA_Divide_Size_H)))
			{
				//�ڐG���Ă���ꍇ�̓L�����ƃG�l�~�[�̈ʒu�����Z�b�g���A�G���h��ʂɔ��
				c->Chara_X = RESET_CHARA;
				c->Chara_Y = RESET_CHARA;

				e->Enemy_X = RANDOM();	//�G�l�~�[��X���W�����A�P�`���̉�ʃT�C�Y���̒l�𗐐��Ń��Z�b�g
				e->Enemy_Y = RESET_ENEMY;

				gamestate_senni = GAME_END;
			}
			
			//�v���C��ʂ̂Ƃ��A�L�����N�^�[���g�債�ĕ`��
			DrawRotaGraph(GAME_Chara_Set_X + c->Chara_X, GAME_Chara_Set_Y + c->Chara_Y, 1.0, 0.0, c->Handle[c->Chara_soeji], TRUE);
			//DrawRotaGraph(c->Chara_X, GAME_Chara_Set_Y + c->Chara_Y, 1.0, 0.0, c->Handle[c->Chara_soeji], TRUE);
			
			

			break;
		//case GAME_CLEAR:
			//DrawGameClear();
			//break;

		//�G���h��ʂȂ�
		case GAME_END:

			DrawGameEnd();

			break;

		default:
			break;
		}

		

		//MY_ALL_KEYDOWN_UPDATE();				//�L�[�̏�Ԃ��擾



		fps->Draw(0, 0);	//FPS�̏���[�`��]

		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		fps->Wait();		//FPS�̏���[�҂�]
	}


	delete c;				//Chara�N���X�̉��
	delete a;				//ATTCK�N���X�̉��
	delete e;				//EnemyCharacter�N���X�̉��
	delete fps;				//FPS��j��
	
	DxLib_End();			//�c�w���C�u�����g�p�̏I������

	return 0;
}

//�^�C�g����ʂ̐ݒ�
void DrawGameTitle()
{

	// �w�i�̉摜��ǂݍ���
	int imgBack_Title = LoadGraph(GAME_BackImage_TITLE);

	// �w�i�̉摜��`��
	DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, imgBack_Title, false);


	int FontHandle_TITLE = CreateFontToHandle(NULL, 120, 3);			//�����̑傫���ύX
	//�`�悷�镶���̈ʒu��ݒ�
	DrawStringToHandle(150, 100, "GAME START!", GetColor(255, 0, 255), FontHandle_TITLE);
	DrawString(0, 20, "Enter�L�[�������ĉ�����(�v���C��ʂ֑J�ڂ��܂�)", GetColor(0, 255, 255));

	//�G���^�[�L�[�������ꂽ��
		//
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1)
		{
			gamestate_senni = GAME_PLAY;	//�V�[�����Q�[����ʂɕύX
		}


	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(FontHandle_TITLE);
}

//�v���C��ʂ̐ݒ�
void DrawGamePlay()
{

	// �w�i�̉摜��ǂݍ���
	int imgBack_Play = LoadGraph(GAME_BackImage_PLAY);

	// �w�i�̉摜��`��
	DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, imgBack_Play, false);

	int FontHandle_PLAY = CreateFontToHandle(NULL, 30, 3);			//�����̑傫���ύX
	//DrawString(0, 20, "Space�L�[�������ĉ�����(�G���h��ʂ֑J�ڂ��܂�)", GetColor(255, 0, 255));
	DrawStringToHandle(0, 50, "Space�L�[���������A�G�ɐG���ƁA�G���h��ʂ֑J�ڂ��܂�", GetColor(255, 0, 255), FontHandle_PLAY);
	DrawStringToHandle(0, 100, "���L�[�ňړ����ĂˁI", GetColor(0, 51, 255), FontHandle_PLAY);
	DrawStringToHandle(0, 150, "A�{�^���ōU���ł����I\n(�U�������摜����������A������x�łĂ܂��B�����蔻�薢�����ł����E�E�E)", GetColor(102, 0, 255), FontHandle_PLAY);
	

	//�X�y�[�X�L�[�������ꂽ��
	if (Keyboard_Get(KEY_INPUT_SPACE) == 1)
	{
		gamestate_senni = GAME_END;//�V�[�����Q�[����ʂɕύX
	}

	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(FontHandle_PLAY);
}

//�G���h��ʂ̐ݒ�
void DrawGameEnd()
{


	// �w�i�̉摜��ǂݍ���
	int imgBack_End = LoadGraph(GAME_BackImage_END);

	// �w�i�̉摜��`��
	DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, imgBack_End, false);

	int FontHandle_END = CreateFontToHandle(NULL, 50, 3);			//�����̑傫���ύX
	DrawString(0, 20, "BackSpace�L�[�������ĉ�����(�^�C�g����ʂ֑J�ڂ��܂�)", GetColor(0, 255, 255));	//BackSpace�L�[�̐���
	DrawString(0, 40, "Escape�L�[�������ĉ�����(�Q�[�����I�����܂�)", GetColor(255, 255, 0));		//Escape�L�[�̐���
	DrawStringToHandle(200, 100, "����ꂳ�܂ł����I\n�܂����킵�ĂˁI", GetColor(0, 155, 155), FontHandle_END);


	
	//�o�b�N�X�y�[�X�L�[�������ꂽ��
	if (Keyboard_Get(KEY_INPUT_BACK) == 1)
	{
		gamestate_senni = GAME_TITLE;//�V�[�����Q�[����ʂɕύX
	}

	//�G�X�P�[�v�L�[�������ꂽ��
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		DxLib_End();			//�c�w���C�u�����g�p�̏I������
	}

	//�쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(FontHandle_END);
}

//�����𐶐�����֐�
int RANDOM()
{
	std::random_device rd;

	std::mt19937 mt(rd());

	//1�`��ʃT�C�Y�̉����܂ł𗐐��Ō��߂�
	std::uniform_int_distribution<int> random(1, GAME_WIDTH);
	return random(mt);
}

