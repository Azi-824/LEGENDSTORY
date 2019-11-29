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
#include "MUSIC.hpp"
#include "MENU.hpp"


//########## �O���[�o���I�u�W�F�N�g ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPS�N���X�̃I�u�W�F�N�g�𐶐�
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWN�N���X�̃I�u�W�F�N�g�𐶐�

IMAGE *title;						//�^�C�g���摜
IMAGE *back;						//�w�i�摜
IMAGE *back_battle;					//�퓬��ʂ̔w�i�摜

MUSIC *bgm;							//BGM

FONT *font;							//�t�H���g
TEXTSTR *text;						//������

PLAYER *player;						//��l��

MAPIMAGE *mapimage;					//�}�b�v�`�b�v�̃f�[�^
MAP *mapdata[MAP_DATA_KIND][MAP_LAYER_KIND];		//�}�b�v�f�[�^

//############## �O���[�o���ϐ� ##############
int GameSceneNow = (int)GAME_SCENE_TITLE;	//���݂̃Q�[���V�[��

int MapKind[MAP_DATA_TATE_KIND][MAP_DATA_YOKO_KIND];			//�}�b�v�̎��
int MapNowPos[2] = {0};								//���݂̃}�b�v��X�ʒu��Y�ʒu���i�[

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

	back_battle = new IMAGE(MY_IMG_DIR_BATTLE, MY_IMG_NAME_BATTLE_NORMAL);	//�퓬��ʂ̔w�i�摜�ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, MY_IMG_NAME_BATTLE_NIGHT);		//�퓬��ʁi��j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s

	bgm = new MUSIC(MY_MUSIC_DIR_BGM, MY_MUSIC_NAME_BGM);			//BGM�𐶐�
	if (bgm->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��

	font = new FONT(MY_FONT_DIR, MY_FONT_NAME, FONT_NAME);			//�t�H���g�𐶐�
	if (font->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��

	text = new TEXTSTR();	//�e�L�X�g�쐬

	player = new PLAYER();
	if (player->SetImage(MY_IMG_DIR_CHARCTOR, MY_IMG_NAME_PLAYER) == false) { return -1; }	//�ǂݍ��ݎ��s
	if (player->SetAnime(MY_ANIME_DIR_PLAYER, MY_ANIME_NAME_PLAYER, PLAYER_ALL_CNT, PLAYER_YOKO_CNT, PLAYER_TATE_CNT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_ANI_SPEED, true) == false) { return -1; } //�ǂݍ��ݎ��s
	player->SetInit();	//�����ݒ�

	mapimage = new MAPIMAGE();	//�}�b�v�`�b�v����
	if (mapimage->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	//���������������������������������������� �}�b�v�f�[�^�ǂݍ��݊J�n ����������������������������������������
	mapdata[MAP_1][FIRST_LAYER] = new MAP();	//��w�ڂ̃}�b�v�f�[�^����
	if (mapdata[MAP_1][FIRST_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_1_1) == false) { return -1; }		//�ǂݍ��ݎ��s

	mapdata[MAP_1][SECOND_LAYER] = new MAP();	//��w�ڂ̃}�b�v�f�[�^����
	if (mapdata[MAP_1][SECOND_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_1_2) == false) { return -1; }	//�ǂݍ��ݎ��s

	mapdata[MAP_2][FIRST_LAYER] = new MAP();	//��w�ڂ̃}�b�v�f�[�^����
	if (mapdata[MAP_2][FIRST_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_2_1) == false) { return -1; }		//�ǂݍ��ݎ��s

	mapdata[MAP_2][SECOND_LAYER] = new MAP();	//��w�ڂ̃}�b�v�f�[�^����
	if (mapdata[MAP_2][SECOND_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_2_2) == false) { return -1; }	//�ǂݍ��ݎ��s

	mapdata[MAP_3][FIRST_LAYER] = new MAP();	//��w�ڂ̃}�b�v�f�[�^����
	if (mapdata[MAP_3][FIRST_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_3_1) == false) { return -1; }		//�ǂݍ��ݎ��s

	mapdata[MAP_3][SECOND_LAYER] = new MAP();	//��w�ڂ̃}�b�v�f�[�^����
	if (mapdata[MAP_3][SECOND_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_3_2) == false) { return -1; }	//�ǂݍ��ݎ��s

	mapdata[MAP_4][FIRST_LAYER] = new MAP();	//��w�ڂ̃}�b�v�f�[�^����
	if (mapdata[MAP_4][FIRST_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_4_1) == false) { return -1; }		//�ǂݍ��ݎ��s

	mapdata[MAP_4][SECOND_LAYER] = new MAP();	//��w�ڂ̃}�b�v�f�[�^����
	if (mapdata[MAP_4][SECOND_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_4_2) == false) { return -1; }	//�ǂݍ��ݎ��s

	//�}�b�v�̎�ނ�񎟌��z��ŊǗ�
	for (int yoko = 0; yoko < MAP_DATA_YOKO_KIND; yoko++)
	{
		static int cnt = 0;
		for (int tate = 0; tate < MAP_DATA_TATE_KIND; tate++)
		{
			MapKind[tate][yoko] = cnt;
			cnt++;
		}
	}

	//�������������������������������������� �}�b�v�f�[�^�ǂݍ��݂����܂� ��������������������������������������


	//�������������������������������������� �ǂݍ��ݏ��� ��������������������������������������������������

	while (TRUE)	//�������[�v
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��

		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		keydown->KeyDownUpdate();	//�L�[�̓��͏�Ԃ��X�V����

		fps->Update();				//FPS�̏���[�X�V]

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

		case (int)GAME_SCENE_BATTLE:	//�퓬��ʂ�������

			Battle();					//�퓬��ʂ̏���

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
	delete bgm;				//bgm��j��
	delete player;			//player��j��
	delete back;			//back��j��
	delete back_battle;		//back_battle��j��
	delete mapimage;		//mapimage��j��

	for (int i = 0; i < MAP_DATA_KIND; i++)
	{
		for (int cnt = 0; cnt < MAP_LAYER_KIND; cnt++)
		{
			delete mapdata[i][cnt];	//mapdata��j��
		}

	}

	DxLib_End();			//�c�w���C�u�����g�p�̏I������

	return 0;
}

//�^�C�g����ʂ̏���
void Title()
{
	//���������������������������� ���̍Đ������������� ������������������������������������
	if (bgm->GetIsPlay() == false)	//�Đ�������Ȃ��Ƃ�
	{
		bgm->ChengeVolume(255 * 50 / 100);	//BGM�̉��ʂ�50%�ɕύX
		bgm->Play();				//BGM���Đ�
	}
	//���������������������������� ���̍Đ����������܂� ��������������������������������������


	back->Draw(0, 0);	//�w�i�摜�`��

	title->Draw(0, GAME_HEIGHT / 2 - title->GetHeight(0) / 2);		//��ʒ����Ƀ^�C�g���`��

	std::vector<std::string> str = { "START","END" };

	if (StrSet_Flg == false)
	{
		text->SetText(str);		//�`�敶���Z�b�g

		StrSet_Flg = true;		//������ݒ�

		font->SetSize(BIG_FONTSIZE);		//�t�H���g�T�C�Y��傫������
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
	font->SetSize(DEFAULT_FONTSIZE);	//�t�H���g�T�C�Y��W���ɖ߂�

	//�}�b�v�`�揈��
	for (int cnt = 0; cnt < MAP_LAYER_KIND; cnt++)
	{
		mapdata[MapKind[MAPPOS_Y][MAPPOS_X]][cnt]->Draw(mapimage->GetHandle((int)FILED));		//�}�b�v�`��
		mapdata[MapKind[MAPPOS_Y][MAPPOS_X]][cnt]->ChengeMap(player,MapNowPos);					//�}�b�v�̐؂�ւ�����
	}

	player->Operation(keydown);	//�v���C���[�L�[����
	player->DrawAnime();		//�A�j���[�V�����`��

	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������
	if (keydown->IsKeyDown(KEY_INPUT_SPACE))
	{
		GameSceneNow = (int)GAME_SCENE_BATTLE;	//�G���h��ʂ�
	}
	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������


	return;
}

//�퓬��ʂ̏���
void Battle()
{

	back_battle->Draw(0, 0);	//�w�i�摜��`��

	if (keydown->IsKeyDown(KEY_INPUT_RETURN))		//�G���^�[�L�[�����ꂽ��
	{
		back_battle->ChengeImage(NIGHT);			//�w�i�摜���i��j�ɕύX
	}

	return;
}

//�G���h��ʂ̏���
void End()
{

	std::vector<std::string> str = { "TITLE","END" };

	if (StrSet_Flg == false)
	{
		text->SetText(str);		//�`�敶���Z�b�g

		StrSet_Flg = true;		//������ݒ�
	}

	text->Draw(GAME_WIDTH / 2 - text->GetWidth() / 2, DEFAULT_TEXT_Y,str.size(),true,GetColor(255,255,255));	//������`��i�F�w��j�i��󂠂�j

	if (keydown->IsKeyDown(KEY_INPUT_S))	//S�L�[�������ꂽ��
	{
		text->Next();	//�I���������
	}
	else if (keydown->IsKeyDown(KEY_INPUT_W))	//W�L�[�������ꂽ��
	{
		text->Back();	//�I������O��
	}


	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������
	if (keydown->IsKeyDown(KEY_INPUT_BACK))
	{
		if (*text->GetPos() == str.begin()->c_str())		//�I�����Ă��镶����"TITLE"��������
		{
			StrSet_Flg = false;						//�����񖢐ݒ�
			GameSceneNow = (int)GAME_SCENE_TITLE;	//�^�C�g����ʂ�
		}
		else
		{
			GameEnd_Flg = true;	//�Q�[���I��
		}

	}
	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������

	return;
}