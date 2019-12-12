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
#include "ENEMY.hpp"
#include "UI.hpp"
#include "DATA.hpp"

//########## �O���[�o���I�u�W�F�N�g ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPS�N���X�̃I�u�W�F�N�g�𐶐�
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWN�N���X�̃I�u�W�F�N�g�𐶐�

IMAGE *title;						//�^�C�g���摜
IMAGE *back;						//�w�i�摜
IMAGE *back_battle;					//�퓬��ʂ̔w�i�摜

MUSIC *bgm;							//BGM

FONT *font;							//�t�H���g
TEXTSTR *text;						//������
UI *ui;								//UI
DATA *data;	//�f�[�^

PLAYER *player;						//��l��

ENEMY *slime;						//�X���C��

MAPIMAGE *mapimage;					//�}�b�v�`�b�v�̃f�[�^
MAP *mapdata[MAP_DATA_KIND][MAP_LAYER_KIND];		//�}�b�v�f�[�^

//############## �O���[�o���ϐ� ##############
int GameSceneNow = (int)GAME_SCENE_TITLE;	//���݂̃Q�[���V�[��
int GameSceneBefor;							//�O�̃Q�[���V�[��
int GameSceneNext;							//���̃Q�[���V�[��

int BattleStageNow = (int)WAIT_PLAYER_ACT;	//�o�g���V�[���̌��݂̏��
int BattleActMsgCnt = 0;		//�s�����b�Z�[�W�J�E���g
int BattleActMsgCntMax = 60;	//�s�����b�Z�[�W�̕\������

int MapKind[MAP_DATA_TATE_KIND][MAP_DATA_YOKO_KIND];			//�}�b�v�̎��
int MapNowPos[2] = {0};								//���݂̃}�b�v��X�ʒu��Y�ʒu���i�[

int ChengeDrawCount = 0;	//�t�F�[�h�C�������Ɏg�p

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
	data = new DATA(DATA_DIR, DATA_NAME);
	
	player = new PLAYER();
	if (player->SetImage(MY_IMG_DIR_CHARCTOR, MY_IMG_NAME_PLAYER) == false) { return -1; }	//�ǂݍ��ݎ��s
	if (player->SetAnime(MY_ANIME_DIR_PLAYER, MY_ANIME_NAME_PLAYER, PLAYER_ALL_CNT, PLAYER_YOKO_CNT, PLAYER_TATE_CNT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_ANI_SPEED, true) == false) { return -1; } //�ǂݍ��ݎ��s
	if (player->AddEffect(MY_ANIME_DIR_ATKEFECT, MY_ANIME_NAME_ATKEFECT, ATK_ALL_CNT, ATK_YOKO_CNT, ATK_TATE_CNT, ATK_WIDTH, ATK_HEIGHT, ATK_SPEED, false) == false) { return -1; }
	if (player->AddMagicEffect(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC2, MAGIC2_ALL_CNT, MAGIC2_YOKO_CNT, MAGIC2_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGICN_SPEED, false) == false) { return -1; }
	player->SetInit();	//�����ݒ�
	player->SetName("�A�A�A");	//���O�ݒ�

	ui = new UI();		//UI�쐬
	ui->SetStateWindow(player);	//�`��HP�ݒ�

	slime = new ENEMY(ENEMY_DIR, ENEMY_NAME_SLIME);	//�X���C���쐬
	if (slime->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s
	if (slime->SetAtkEffect(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC, MAGIC_ALL_CNT, MAGIC_YOKO_CNT, MAGIC_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGICN_SPEED, false) == false) { return -1; }
	slime->SetImagePos(GAME_WIDTH / 2 - slime->GetWidth() / 2, GAME_HEIGHT / 2 - slime->GetHeight() / 2);	//�X���C���̈ʒu����(��ʒ���)
	slime->SetName("�X���C��");//���O�ݒ�

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

		case (int)GAME_SCENE_CHENGE:	//�V�[���J�ډ�ʂ�������

			Chenge();					//�V�[���J�ډ�ʂ̏���

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
	delete data;			//data��j��

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
	Init();		//������

	//���������������������������� ���̍Đ������������� ������������������������������������
	if (bgm->GetIsPlay() == false)	//�Đ�������Ȃ��Ƃ�
	{
		bgm->ChengeVolume(255 * 50 / 100);	//BGM�̉��ʂ�50%�ɕύX
		bgm->Play();				//BGM���Đ�
	}
	//���������������������������� ���̍Đ����������܂� ��������������������������������������


	Title_Draw();		//�^�C�g����ʂ̕`�揈��

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
		if (*text->GetPos() == "START")		//�I�����Ă��镶����"START"��������
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//���̉�ʂ̓v���C���
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
	Init();		//������

	player->Operation(keydown);	//�v���C���[�L�[����
	Play_Draw();		//�`�揈��

	if (keydown->IsKeyDownOne(KEY_INPUT_Q))		//Q�L�[�������ꂽ�u��
	{
		player->SetIsMenu(true);		//���j���[�`��J�n
	}
	else if (keydown->IsKeyDownOne(KEY_INPUT_ESCAPE))	//Esc�L�[�������ꂽ�u��
	{
		player->SetIsMenu(false);		//���j���[�`��I��
	}


	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������
	if (keydown->IsKeyDown(KEY_INPUT_SPACE))
	{
		SceneChenge(GameSceneNow, (int)GAME_SCENE_BATTLE);	//���̉�ʂ͐퓬���
	}
	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������


	return;
}

//�퓬��ʂ̏���
void Battle()
{

	Battle_Draw();			//�`�揈��


	switch (BattleStageNow)		//���݂̃o�g�����
	{
	//�������������������������������������� �����̃^�[���̏����������� ��������������������������������������

	case (int)WAIT_PLAYER_ACT:		//�v���C���[�̍s���I��҂���Ԃ̎�

		ui->BattleOperation(keydown);			//�퓬��ʂ̃L�[����

		//�������������������������������������� �o�g���R�}���h���̏����������� ��������������������������������������
		switch (ui->GetChoiseCommamd())		//�ǂ̃R�}���h��I�񂾂�
		{
		case (int)ATACK:					//�U����I�񂾎�

			BattleStageNow = (int)PLAYER_DAMEGE_CALC;	//�o�g����Ԃ��_���[�W�v�Z��Ԃ�

			break;

		case (int)DEFENSE:		//�h���I�񂾎�

			ui->BattleInit();	//�o�g���R�}���h���Z�b�g

			break;

		case (int)MAGIC:		//���@��I�񂾎�

			BattleStageNow = (int)PLAYER_DAMEGE_CALC;	//�o�g����Ԃ��_���[�W�v�Z��Ԃ�

			break;

		case (int)ITEM:			//�A�C�e����I�񂾎�

			ui->BattleInit();	//�o�g���R�}���h���Z�b�g

			break;

		case (int)ESCAPE:		//�������I�񂾎�

			data->Draw(200, 200);			//������Ƃ��̃��b�Z�[�W�`��
			ui->BattleInit();	//�o�g���R�}���h���Z�b�g
			SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//���̉�ʂ̓v���C���
			Init();									//������

			break;

		default:
			break;
		}
		//�������������������������������������� �o�g���R�}���h���̏��������܂� ��������������������������������������


		break;						//�v���C���[�̍s���I��҂���Ԃ̏��������܂�

	case (int)PLAYER_DAMEGE_CALC:			//�_���[�W�v�Z��Ԃ̎�

		player->DamegeCalc(slime);		//�_���[�W�v�Z

		BattleStageNow = (int)PLAYER_ACT_MSG;	//�s�����b�Z�[�W�\����Ԃ�

		break;						//�_���[�W�v�Z��Ԃ̎������܂�

	case (int)PLAYER_ACT_MSG:				//�s�����b�Z�[�W�\�����


		if (BattleActMsgCnt == BattleActMsgCntMax)		//�\���b���ɂȂ�����
		{
			BattleStageNow = (int)PLAYER_DRAW_EFFECT;			//�G�t�F�N�g�`���Ԃ�
		}
		else
		{
			BattleActMsgCnt++;	//�J�E���g�A�b�v
		}

		break;						//�s�����b�Z�[�W�\����Ԃ����܂�

	case (int)PLAYER_DRAW_EFFECT:			//�G�t�F�N�g�`����

		if (ui->GetChoiseCommamd() == (int)ATACK)	//�U����I��ł�����
		{
			player->DrawAtk(350, 250);		//�U���G�t�F�N�g�`��
		}
		else if (ui->GetChoiseCommamd() == (int)MAGIC)	//���@��I��ł�����
		{
			player->DrawMagic((GAME_WIDTH / 2 - MAGIC_WIDTH / 2), (GAME_HEIGHT / 2 - MAGIC_HEIGHT / 2));	//���@�G�t�F�N�g�`��
		}

		if (player->GetEffectEnd())		//�G�t�F�N�g�`�悪�I��������
		{
			
			player->EffectReset();			//�G�t�F�N�g�֘A���Z�b�g

			BattleStageNow = (int)ENEMY_WAIT_ACT;		//�G�̍s���I����Ԃ�

			BattleActMsgCnt = 0;	//�J�E���g���Z�b�g

			slime->SetHP((slime->GetHP() - player->GetSendDamege()));	//�_���[�W��^����

			if (slime->GetHP() <= 0)				//�G��HP��0�ɂȂ�����
			{
				slime->SetIsArive(false);		//�G���S
			}

		}

		break;

	//���������������������������������������������� �����̃^�[���̏��������܂� ��������������������������������������������������


	//���������������������������������������������� �G�̃^�[���̏����������� ����������������������������������������������������

	case (int)ENEMY_WAIT_ACT:			//�G�̍s���I��҂����

		//�G�̍s���I�����菈��

		BattleStageNow = (int)ENEMY_DAMEGE_CALC;	//�G�̃_���[�W�v�Z��

		break;

	case (int)ENEMY_DAMEGE_CALC:		//�G�̃_���[�W�v�Z���

		//�_���[�W�v�Z

		BattleStageNow = (int)ENEMY_ACT_MSG;	//�G�̍s�����b�Z�[�W�\����
		
		break;

	case (int)ENEMY_ACT_MSG:			//�G�̍s�����b�Z�[�W�\�����

		//�G�̍s�����b�Z�[�W�\��
		if (BattleActMsgCnt == BattleActMsgCntMax)		//�\���b���ɂȂ�����
		{
			BattleStageNow = (int)ENEMY_DRAW_EFFECT;			//�G�̃G�t�F�N�g�`���Ԃ�
		}
		else
		{
			BattleActMsgCnt++;	//�J�E���g�A�b�v
		}

		break;

	case (int)ENEMY_DRAW_EFFECT:		//�G�̃G�t�F�N�g�\�����

		//�G�̃G�t�F�N�g�\��
		slime->DrawEffect((GAME_WIDTH / 2 - MAGIC_WIDTH / 2),(GAME_HEIGHT / 2 - MAGIC_HEIGHT / 2));	//�G�̍U���G�t�F�N�g�`��

		if (slime->GetIeEffectEnd())		//�G�t�F�N�g�`�悪�I��������
		{
			BattleActMsgCnt = 0;	//�J�E���g���Z�b�g

			slime->ResetEffect();	//�G�t�F�N�g�֘A���Z�b�g

			player->SetHP(player->GetRecvDamege());		//�����Ƀ_���[�W��^����

			ui->SetStateWindow(player);		//�`��X�e�[�^�X�X�V

			ui->BattleInit();				//�o�g���R�}���h���Z�b�g

			BattleStageNow = (int)WAIT_PLAYER_ACT;		//�����̍s���I��҂���Ԃ�

			if (player->GetHP() <= 0)			//������HP��0�ɂȂ�����
			{
				player->SetIsArive(false);		//�������S
			}

		}

		break;

	//���������������������������������������������� �G�̃^�[���̏��������܂� ��������������������������������������������������


	default:

		break;


	}

	//��������
	if (slime->GetIsArive() == false)	//�G�����񂾂�
	{
		SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//���̉�ʂ̓v���C���

		BattleStageNow = (int)WAIT_PLAYER_ACT;		//�����̍s���I��҂���Ԃ�

		Init();									//������

	}
	else if (player->GetIsArive() == false)	//���������񂾂�
	{
		SceneChenge(GameSceneNow, (int)GAME_SCENE_END);	//���̉�ʂ̓G���h���

		BattleStageNow = (int)WAIT_PLAYER_ACT;		//�����̍s���I��҂���Ԃ�

		Init();									//������
	}

	if (keydown->IsKeyDown(KEY_INPUT_R))		//R�L�[�����ꂽ��
	{
		back_battle->ChengeImage(NIGHT);		//�w�i�摜���i��j�ɕύX
	}
	return;
}

//�G���h��ʂ̏���
void End()
{
	Init();	//������

	End_Draw();	//�`�揈��

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
		if (*text->GetPos() == "TITLE")		//�I�����Ă��镶����"TITLE"��������
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_TITLE);	//���̉�ʂ̓^�C�g�����
		}
		else
		{
			GameEnd_Flg = true;	//�Q�[���I��
		}

	}
	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������

	return;
}

//��ʑJ�ڂ̉��o�����鏈��
void Chenge()
{
	static const int ChengeDrawCountMax = 60;	//�t�F�[�h�C�������Ɏg�p

	switch (GameSceneBefor)		//�ǂ̉�ʂ���̑J�ڂ��ŏ����𕪂���
	{
	case (int)GAME_SCENE_TITLE:	//�^�C�g����ʂ���̑J�ڂ�������

		Title_Draw();		//�^�C�g����ʂ̕`�揈��

		break;

	case (int)GAME_SCENE_PLAY:	//�v���C��ʂ���̑J�ڂ�������

		Play_Draw();		//�v���C��ʂ̕`�揈��

		break;

	case (int)GAME_SCENE_BATTLE://�퓬��ʂ���̑J�ڂ�������

		Battle_Draw();		//�퓬��ʂ̕`�揈��

		break;

	case (int)GAME_SCENE_END:	//�G���h��ʂ���̑J�ڂ�������

		End_Draw();			//�G���h��ʂ̕`�揈��

		break;

	default:
		break;
	}

	//60�t���[�����A�҂�
	if (ChengeDrawCount < ChengeDrawCountMax)
	{
		ChengeDrawCount++;
	}
	else
	{
		GameSceneNow = GameSceneNext;	//���̉�ʂɂ���
		StrSet_Flg = false;				//�����񖢐ݒ�
	}

	//�t�F�[�h�A�E�g�̏���
	double ToukaPercent = ChengeDrawCount / (double)ChengeDrawCountMax;//���߁������߂�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * 255);	//���߂�����
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);	//�^���Âȉ�ʂɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//���߂���߂�

	return;

}

//����������
void Init()
{
	ChengeDrawCount = 0;		//�t�F�[�h�C���p������

	slime->StateSetInit();		//�G������

	ui->BattleInit();			//�o�g���R�}���h������

}

//�V�[����ύX���鏈��
void SceneChenge(int beforscene, int nextscene)
{
	GameSceneBefor = beforscene;				//���݂̃Q�[���V�[����O�̃Q�[���V�[���Ƃ��ĕۑ�
	GameSceneNow = (int)GAME_SCENE_CHENGE;		//�J�ډ�ʂɕύX
	GameSceneNext = nextscene;					//���̃V�[�����w��
	return;
}

//�^�C�g����ʂ̕`�揈��
void Title_Draw()
{
	back->Draw(0, 0);	//�w�i�摜�`��

	title->Draw(0, GAME_HEIGHT / 2 - title->GetHeight(0) / 2);		//��ʒ����Ƀ^�C�g���`��

	std::vector<std::string> str = { "START","END" };

	if (StrSet_Flg == false)
	{
		text->SetText(str);		//�`�敶���Z�b�g

		StrSet_Flg = true;		//������ݒ�

		font->SetSize(BIG_FONTSIZE);		//�t�H���g�T�C�Y��傫������
	}

	text->Draw(GAME_WIDTH / 2 - text->GetWidth() / 2, DEFAULT_TEXT_Y, str.size(), true);	//�`��i���t���j
	
	return;

}

//�v���C��ʂ̕`�揈��
void Play_Draw()
{
	font->SetSize(DEFAULT_FONTSIZE);	//�t�H���g�T�C�Y��W���ɖ߂�

	//�}�b�v�`�揈��
	for (int cnt = 0; cnt < MAP_LAYER_KIND; cnt++)
	{
		mapdata[MapKind[MAPPOS_Y][MAPPOS_X]][cnt]->Draw(mapimage->GetHandle((int)FILED));		//�}�b�v�`��
		mapdata[MapKind[MAPPOS_Y][MAPPOS_X]][cnt]->ChengeMap(player, MapNowPos);					//�}�b�v�̐؂�ւ�����
	}

	player->DrawAnime();		//�A�j���[�V�����`��
	ui->MenuOperation(keydown, player->GetIsMenu());	//���j���[��ʑ���

	return;

}

//�퓬��ʂ̕`�揈��
void Battle_Draw()
{
	back_battle->Draw(0, 0);	//�w�i�摜��`��


	slime->Draw();	//�X���C���`��

	if (BattleStageNow==(int)ENEMY_ACT_MSG)	//�G�̍s�����b�Z�[�W�\����Ԃ�������
	{
		ui->EnemyDrawDamege(slime->GetName(), player->GetRecvDamege());		//�󂯂����b�Z�[�W�\��
	}
	else if (BattleStageNow == (int)PLAYER_ACT_MSG)	//�����̍s�����b�Z�[�W�\����Ԃ�������
	{
		ui->MyDrawDamege(player->GetName(), player->GetSendDamege());		//�^�����_���[�W�\��
	}
	else
	{
		ui->DrawCommand();						//�o�g���R�}���h�`��
	}

	ui->DrawStateWindow();					//�X�e�[�^�X�E�B���h�E�`��

	return;

}

//�G���h��ʂ̕`�揈��
void End_Draw()
{
	std::vector<std::string> str = { "TITLE","END" };

	if (StrSet_Flg == false)
	{
		text->SetText(str);		//�`�敶���Z�b�g

		StrSet_Flg = true;		//������ݒ�
	}

	text->Draw(GAME_WIDTH / 2 - text->GetWidth() / 2, DEFAULT_TEXT_Y, str.size(), true, GetColor(255, 255, 255));	//������`��i�F�w��j�i��󂠂�j

	return;

}
