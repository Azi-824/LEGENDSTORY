/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* main.cpp     																				�@ */

//##########�w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"
#include "IMAGE.hpp"
#include "ANIMATION.hpp"

//########## �O���[�o���I�u�W�F�N�g ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPS�N���X�̃I�u�W�F�N�g�𐶐�
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWN�N���X�̃I�u�W�F�N�g�𐶐�
IMAGE *title;


//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//�w��̐��l�ŉ�ʂ�\������

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//�^�C�g���o�[����

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//�^�C�g���̕���

	if (DxLib_Init() == -1) { return -1; }						//�c�w���C�u��������������

	SetDrawScreen(DX_SCREEN_BACK);								//Draw�n�֐��͗���ʂɕ`��



	title = new IMAGE(MY_IMG_DIR_TITLE, MY_ING_NAME_TITLE);			//�^�C�g���摜�𐶐�
	if (title->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��


	while (TRUE)	//�������[�v
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��

		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		keydown->KeyDownUpdate();	//�L�[�̓��͏�Ԃ��X�V����

		fps->Update();				//FPS�̏���[�X�V]

		keydown->IsKeyDown(KEY_INPUT_LEFT);

		//�����������Q�[���̃V�[���������灥��������

		switch (GameSceneNow)
		{
		case (int)GAME_SCENE_TITLE:		//�^�C�g����ʂ�������
			
			Title();					//�^�C�g����ʂ̏���

			break;

		case (int)GAME_SCENE_PLAY:		//�v���C��ʂ�������

			Play();						//�v���C��ʂ̏���

			break;

		case (int)GAME_SCENE_END:		//�G���h��ʂ�������

			End();						//�G���h��ʂ̏���

			break;

		default:
			break;

		}

		keydown->IsKeyDown(KEY_INPUT_UP);


		//�����������Q�[���̃V�[�������܂Ł���������

		fps->Draw(0, 0);				//FPS�̏���[�`��]

		ScreenFlip();				//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		fps->Wait();				//FPS�̏���[�҂�]
	}

	delete title;			//title��j��
	delete fps;				//FPS��j��
	delete keydown;			//keydown��j��

	DxLib_End();			//�c�w���C�u�����g�p�̏I������

	return 0;
}

//�^�C�g����ʂ̏���
void Title()
{

	title->Draw(0, GAME_HEIGHT / 2 - title->GetHeight() / 2);		//��ʒ����Ƀ^�C�g���`��

	

	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������
	if (keydown->IsKeyDown(KEY_INPUT_RETURN))
	{
		GameSceneNow = (int)GAME_SCENE_PLAY;	//�v���C��ʂ�
	}
	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������

	return;
}

//�v���C��ʂ̏���
void Play()
{
	return;
}

//�G���h��ʂ̏���
void End()
{
	return;
}