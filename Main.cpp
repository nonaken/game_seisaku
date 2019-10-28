//##########�w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "FPS.hpp"
#include "Keyboard.hpp"
#include <math.h>

//########## �}�N����` ##########
#define GAME_WIDTH	1280		//��ʂ̉��̑傫��
#define GAME_HEIGHT 950		//��ʂ̏c�̑傫��
#define GAME_COLOR	32		//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_NAME	"GAME PLAY!"		//�E�B���h�E�̃^�C�g��
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE�F�E�B���h�E���[�h / FALSE�F�t���X�N���[��

#define SET_WINDOW_ST_MODE_DEFAULT			0	//�f�t�H���g
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//�^�C�g���o�[�Ȃ�
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//�^�C�g���o�[�ƃt���[���Ȃ�
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//�t���[���Ȃ�

#define GAME_FPS_SPEED					   60

#define GAME_BackImage_TITLE	"BackImage\\�F��.jpg"			//�w�i�摜


#define GAME_CharaImage_TITLE	"�N���X�}�X�L�����`�b�v\\pipo-xmaschara05.png"			//�w�i�摜
//�񋓌^�Ŋe��ʂ��Ǘ�
enum GameState
{
	GAME_TITLE,		//�^�C�g�����
	GAME_PLAY,		//�v���C���
	//GAME_CLEAR,
	GAME_END		//�G���h���
};

//�Q�[����ʂ̑J�ڂ��Ǘ�����
GameState gamestate_senni = GAME_TITLE;

//�e��ʂ��Ǘ�����v���g�^�C�v�錾
void DrawGameTitle();
void DrawGamePlay();
//void DrawGameClear();
void DrawGameEnd();

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

	
	
	while (TRUE)	//�������[�v
	{

		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��

		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		
		switch (gamestate_senni)
		{
		case GAME_TITLE:
			DrawGameTitle();
			break;
		case GAME_PLAY:
			DrawGamePlay();
			break;
		//case GAME_CLEAR:
			//DrawGameClear();
			//break;
		case GAME_END:
			DrawGameEnd();
			break;
		default:
			break;
		}

		//MY_ALL_KEYDOWN_UPDATE();				//�L�[�̏�Ԃ��擾

		Keyboard_Update();   //�L�[�{�[�h�̍X�V

		fps->Update();		//FPS�̏���[�X�V]

		fps->Draw(0, 0);	//FPS�̏���[�`��]

		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		fps->Wait();		//FPS�̏���[�҂�]
	}




	delete fps;				//FPS��j��
	
	DxLib_End();			//�c�w���C�u�����g�p�̏I������

	return 0;
}

//�^�C�g����ʂ̐ݒ�
void DrawGameTitle()
{

	// �w�i�̉摜��ǂݍ���
	int imgBack = LoadGraph(GAME_BackImage_TITLE);

	// �w�i�̉摜��`��
	DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, imgBack, false);


	int FontHandle_TITLE = CreateFontToHandle(NULL, 120, 3);			//�����̑傫���ύX
	//�`�悷�镶���̈ʒu��ݒ�
	DrawStringToHandle(150, 100, "GAME START!", GetColor(255, 0, 255), FontHandle_TITLE);
	DrawString(0, 20, "Enter�L�[�������ĉ�����(�v���C��ʂ֑J�ڂ��܂�)", GetColor(0, 255, 255));

	//�G���^�[�L�[�������ꂽ��
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1)
	{
		gamestate_senni = GAME_PLAY;//�V�[�����Q�[����ʂɕύX
	}


	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(FontHandle_TITLE);
}

//�v���C��ʂ̐ݒ�
void DrawGamePlay()
{
	int FontHandle_PLAY = CreateFontToHandle(NULL, 20, 3);			//�����̑傫���ύX
	DrawString(0, 20, "Space�L�[�������ĉ�����(�G���h��ʂ֑J�ڂ��܂�)", GetColor(0, 255, 255));
	DrawStringToHandle(0, 40, "���L�[�ňړ����ĂˁI(����L�[�͍U���{�^������I)", GetColor(0, 155, 155), FontHandle_PLAY);

	//�X�y�[�X�L�[�������ꂽ��
	if (Keyboard_Get(KEY_INPUT_SPACE) == 1)
	{
		gamestate_senni = GAME_END;//�V�[�����Q�[����ʂɕύX
	}

	DeleteFontToHandle(FontHandle_PLAY);
}

//�G���h��ʂ̐ݒ�
void DrawGameEnd()
{
	int FontHandle_END = CreateFontToHandle(NULL, 20, 3);			//�����̑傫���ύX
	DrawString(0, 20, "BackSpace�L�[�������ĉ�����(�^�C�g����ʂ֑J�ڂ��܂�)", GetColor(0, 255, 255));
	DrawStringToHandle(0, 40, "����ꂳ�܂ł����I�܂����킵�ĂˁI", GetColor(0, 155, 155), FontHandle_END);

	//�X�y�[�X�L�[�������ꂽ��
	if (Keyboard_Get(KEY_INPUT_BACK) == 1)
	{
		gamestate_senni = GAME_TITLE;//�V�[�����Q�[����ʂɕύX
	}

	DeleteFontToHandle(FontHandle_END);
}
