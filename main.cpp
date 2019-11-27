/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* main.cpp     																				�@ */

//##########�w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"
#include "IMAGE.hpp"
#include "ANIMATION.hpp"
#include "FONT.hpp"
#include "CHARACTOR.hpp"
#include "COLLISION.hpp"
#include "PLAYER.hpp"
#include "MAP.hpp"
#include "MAPIMAGE.hpp"
#include "TEXTSTR.hpp"


//########## �O���[�o���I�u�W�F�N�g ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPS�N���X�̃I�u�W�F�N�g�𐶐�
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWN�N���X�̃I�u�W�F�N�g�𐶐�
IMAGE *title;						//�^�C�g���摜
IMAGE *back;						//�w�i�摜
FONT *font;							//�t�H���g
TEXTSTR *text;						//������
PLAYER *player;						//��l��
MAPIMAGE *mapimage;					//�}�b�v�`�b�v�̃f�[�^
MAP *mapdata[MAP_LAYER_KIND];		//�}�b�v�f�[�^

//############## �O���[�o���ϐ� ##############
int GameSceneNow = (int)GAME_SCENE_TITLE;	//���݂̃Q�[���V�[��

bool StrSet_Flg = false;					//������ݒ�t���O
bool GameEnd_Flg = false;					//�Q�[���I���t���O

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//�w��̐��l�ŉ�ʂ�\������

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//�^�C�g���o�[����

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//�^�C�g���̕���

	if (DxLib_Init() == -1) { return -1; }						//�c�w���C�u��������������

	SetDrawScreen(DX_SCREEN_BACK);								//Draw�n�֐��͗���ʂɕ`��

	//���������������������������������������� �ǂݍ��ݏ��� ��������������������������������������������������

	title = new IMAGE(MY_IMG_DIR_TITLE, MY_ING_NAME_TITLE);			//�^�C�g���摜�𐶐�
	if (title->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��

	back = new IMAGE(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK);			//�w�i�摜�𐶐�
	if (back->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��

	font = new FONT(MY_FONT_DIR, MY_FONT_NAME, FONT_NAME);			//�t�H���g�𐶐�
	if (font->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��

	text = new TEXTSTR();

	player = new PLAYER();
	if (player->SetImage(MY_IMG_DIR_CHARCTOR, MY_IMG_NAME_PLAYER) == false) { return -1; }	//�ǂݍ��ݎ��s
	if (player->SetAnime(MY_ANIME_DIR_PLAYER, MY_ANIME_NAME_PLAYER, PLAYER_ALL_CNT, PLAYER_YOKO_CNT, PLAYER_TATE_CNT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_ANI_SPEED, true) == false) { return -1; } //�ǂݍ��ݎ��s
	player->SetInit();	//�����ݒ�

	mapimage = new MAPIMAGE();	//�}�b�v�`�b�v����
	if (mapimage->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	mapdata[FIRST_LAYER] = new MAP();	//��w�ڂ̃}�b�v�f�[�^����
	if (mapdata[FIRST_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_1) == false) { return -1; }		//�ǂݍ��ݎ��s

	mapdata[SECOND_LAYER] = new MAP();	//��w�ڂ̃}�b�v�f�[�^����
	if (mapdata[SECOND_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_2) == false) { return -1; }		//�ǂݍ��ݎ��s


	//�������������������������������������� �ǂݍ��ݏ��� ��������������������������������������������������

	while (TRUE)	//�������[�v
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��

		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		keydown->KeyDownUpdate();	//�L�[�̓��͏�Ԃ��X�V����

		fps->Update();				//FPS�̏���[�X�V]

		keydown->IsKeyDown(KEY_INPUT_LEFT);

		if (GameEnd_Flg)		//�Q�[���I���t���O�������Ă�����
		{
			break;				//���[�v�𔲂��A�Q�[���I��
		}

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


		//�����������Q�[���̃V�[�������܂Ł���������

		fps->Draw(0, 0);				//FPS�̏���[�`��]

		ScreenFlip();				//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		fps->Wait();				//FPS�̏���[�҂�]
	}

	delete title;			//title��j��
	delete fps;				//FPS��j��
	delete keydown;			//keydown��j��
	delete font;			//font��j��
	delete text;			//text��j��
	delete player;			//player��j��
	delete back;			//back��j��
	delete mapimage;		//mapimage��j��

	for (int cnt = 0; cnt < MAP_LAYER_KIND; cnt++)
	{
		delete mapdata[cnt];	//mapdata��j��
	}

	DxLib_End();			//�c�w���C�u�����g�p�̏I������

	return 0;
}

//�^�C�g����ʂ̏���
void Title()
{

	back->Draw(0, 0);	//�w�i�摜�`��

	title->Draw(0, GAME_HEIGHT / 2 - title->GetHeight() / 2);		//��ʒ����Ƀ^�C�g���`��

	std::vector<std::string> str = { "START","END" };

	if (StrSet_Flg == false)
	{
		text->SetText(str);		//�`�敶���Z�b�g

		StrSet_Flg = true;		//������ݒ�

		font->SetSize(BIG_FONTSIZE);		//�t�H���g�T�C�Y�ύX
	}

	text->Draw(GAME_WIDTH / 2 - text->GetWidth() / 2, DEFAULT_TEXT_Y,str.size(),true);	//�`��i���t���j

	if (keydown->IsKeyDown(KEY_INPUT_S))	//S�L�[�������ꂽ��
	{
		text->Next();	//�I���������
	}
	else if (keydown->IsKeyDown(KEY_INPUT_W))	//W�L�[�������ꂽ��
	{
		text->Back();	//�I������O��
	}

	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������
	if (keydown->IsKeyDown(KEY_INPUT_RETURN))				//�G���^�[�L�[�������ꂽ��
	{
		if (*text->GetPos() == str.begin()->c_str())		//�I�����Ă��镶����"START"��������
		{
			StrSet_Flg = false;						//�����񖢐ݒ�
			GameSceneNow = (int)GAME_SCENE_PLAY;	//�v���C��ʂ�
		}
		else
		{
			GameEnd_Flg = true;	//�Q�[���I��
		}
	}
	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������

	return;
}

//�v���C��ʂ̏���
void Play()
{
	//�}�b�v�`�揈��
	for (int cnt = 0; cnt < MAP_LAYER_KIND; cnt++)
	{
		mapdata[cnt]->Draw(mapimage->GetHandle((int)FILED));		//�}�b�v�`��
	}

	std::vector<std::string> str = { "PUSH SPACE" };
	
	text->SetText(str);		//������Z�b�g
	
	text->Draw(GAME_WIDTH / 2 - text->GetWidth() / 2, DEFAULT_TEXT_Y,str.size(),false);	//������`��i���Ȃ��j

	player->Operation(keydown);	//�v���C���[�L�[����
	player->DrawAnime();		//�A�j���[�V�����`��

	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������
	if (keydown->IsKeyDown(KEY_INPUT_SPACE))
	{
		GameSceneNow = (int)GAME_SCENE_END;	//�G���h��ʂ�
	}
	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������


	return;
}

//�G���h��ʂ̏���
void End()
{

	std::vector<std::string> str = { "PUSH BACK" };

	text->SetText(str);		//������Z�b�g

	text->Draw(GAME_WIDTH / 2 - text->GetWidth() / 2, DEFAULT_TEXT_Y,str.size(),false,GetColor(255,255,255));	//������`��i�F�w��j�i���Ȃ��j


	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������
	if (keydown->IsKeyDown(KEY_INPUT_BACK))
	{
		GameSceneNow = (int)GAME_SCENE_TITLE;	//�^�C�g����ʂ�
	}
	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������

	return;
}