/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* main.cpp     																				�@ */

//##########�w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"
#include "FONT.hpp"
#include "PLAYER.hpp"
#include "MAP.hpp"
#include "MAPIMAGE.hpp"
#include "MUSIC.hpp"
#include "ENEMY.hpp"
#include "UI.hpp"
#include "DATA.hpp"
#include "EFFECT.hpp"
#include "MSG.hpp"
#include "ITEM.hpp"

//########## �O���[�o���I�u�W�F�N�g ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPS�N���X�̃I�u�W�F�N�g�𐶐�
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWN�N���X�̃I�u�W�F�N�g�𐶐�

IMAGE *title;						//�^�C�g���摜
IMAGE *back;						//�w�i�摜
IMAGE *back_battle;					//�퓬��ʂ̔w�i�摜

MUSIC *bgm;							//BGM
MUSIC *se;							//SE

EFFECT *effect;						//�G�t�F�N�g

FONT *font;							//�t�H���g
UI *ui;								//UI
DATA *data;							//�f�[�^
MESSAGE *msg;						//���b�Z�[�W

PLAYER *player;						//��l��

ENEMY *enemy[ENEMY_KIND];			//�G

ITEM *item[ITEM_KIND];				//�A�C�e��

MAPIMAGE *mapimage;					//�}�b�v�`�b�v�̃f�[�^
MAP *mapdata[MAP_DATA_KIND][MAP_LAYER_KIND];		//�}�b�v�f�[�^

//############## �O���[�o���ϐ� ##############
int GameSceneNow = (int)GAME_SCENE_TITLE;	//���݂̃Q�[���V�[��
int GameSceneBefor;							//�O�̃Q�[���V�[��
int GameSceneNext;							//���̃Q�[���V�[��

int BattleStageNow = (int)WAIT_ACT;	//�o�g���V�[���̌��݂̏��
int BattleActMsgCnt = 0;		//�s�����b�Z�[�W�J�E���g
int BattleActMsgCntMax = 60;	//�s�����b�Z�[�W�̕\������

int MapKind[MAP_DATA_TATE_KIND][MAP_DATA_YOKO_KIND];			//�}�b�v�̎��
int MapNowPos[2] = {0};								//���݂̃}�b�v��X�ʒu��Y�ʒu���i�[

int ChengeDrawCount = 0;	//�t�F�[�h�A�E�g�����Ɏg�p

int EncounteEnemyType = 0;	//���������G�̎��
int Turn = (int)MY_TURN;	//�^�[��

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

	back = new IMAGE(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK_TITLE);			//�w�i�摜�𐶐�
	if (back->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��
	back->AddImage(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK_END, (int)END_BACK);	//�G���h��ʂ̔w�i�摜�ǂݍ���
	if (back->GetIsLoad() == false) { return -1; }							//�ǂݍ��ݎ��s

	back_battle = new IMAGE(MY_IMG_DIR_BATTLE, MY_IMG_NAME_BATTLE_NORMAL);	//�퓬��ʂ̔w�i�摜�ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, MY_IMG_NAME_BATTLE_NIGHT,(int)NIGHT);		//�퓬��ʁi��j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s

	//���֌W
	bgm = new MUSIC(MY_MUSIC_DIR_BGM, MY_MUSIC_NAME_BGM,BGM_KIND);			//BGM�𐶐�
	if (bgm->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��
	se = new MUSIC(MY_MUSIC_DIR_SE, MY_SE_NAME_LEVUP, SE_KIND);			//SE�𐶐�
	if (se->GetIsLoad() == false) { return -1; }						//�ǂݍ��ݎ��s��
	se->ChengePlayType(DX_PLAYTYPE_BACK);								//�Đ����@�ύX

	font = new FONT(MY_FONT_DIR, MY_FONT_NAME, FONT_NAME);			//�t�H���g�𐶐�
	if (font->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��

	data = new DATA();
	msg = new MESSAGE();	//���b�Z�[�W

	//�G�t�F�N�g�֌W
	effect = new EFFECT(MY_ANIME_DIR_ATKEFECT, MY_ANIME_NAME_ATKEFECT, ATK_ALL_CNT, ATK_YOKO_CNT, ATK_TATE_CNT, ATK_WIDTH, ATK_HEIGHT, ATK_SPEED, false);
	if (effect->GetIsLoad() == false) { return -1; }		//�ǂݍ��ݎ��s
	if (effect->Add(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC, MAGIC_ALL_CNT, MAGIC_YOKO_CNT, MAGIC_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC_SPEED, false, (int)MAGIC_1) == false) { return -1; }	//�ǂݍ��ݎ��s
	if (effect->Add(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC2, MAGIC2_ALL_CNT, MAGIC2_YOKO_CNT, MAGIC2_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC_SPEED, false, (int)MAGIC_2) == false) { return -1; }	//�ǂݍ��ݎ��s
	
	//�v���C���[�֌W
	player = new PLAYER();		//�v���C���[����
	if (player->SetImage(MY_IMG_DIR_CHARCTOR, MY_IMG_NAME_PLAYER) == false) { return -1; }	//�ǂݍ��ݎ��s
	if (player->SetAnime(MY_ANIME_DIR_PLAYER, MY_ANIME_NAME_PLAYER, PLAYER_ALL_CNT, PLAYER_YOKO_CNT, PLAYER_TATE_CNT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_ANI_SPEED, true) == false) { return -1; } //�ǂݍ��ݎ��s
	
	//�v���C���[�̃f�[�^��csv�t�@�C������ǂݍ���
	if (data->LoadPlayer(player, PLAYER_DATA_DIR, PLAYER_DATA_NAME) == false) { return -1; }	//�ǂݍ��ݎ��s
	player->SetInit();	//�����ݒ�

	ui = new UI();		//UI�쐬

	//�G�֌W
	enemy[(int)SLIME] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SLIME);	//�X���C���쐬
	if (enemy[(int)SLIME]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)YADOKARI]=new ENEMY(ENEMY_DIR, ENEMY_NAME_YADOKARI);	//���h�J���쐬
	if (enemy[(int)YADOKARI]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)BAT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_BAT);	//��������쐬
	if (enemy[(int)BAT]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)FARAO] = new ENEMY(ENEMY_DIR, ENEMY_NAME_FARAO);	//�t�@���I�쐬
	if (enemy[(int)FARAO]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)GOBURIN] = new ENEMY(ENEMY_DIR, ENEMY_NAME_GOBURIN);	//�S�u�����쐬
	if (enemy[(int)GOBURIN]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)AKUMA] = new ENEMY(ENEMY_DIR, ENEMY_NAME_AKUMA);	//�f�[�����쐬
	if (enemy[(int)AKUMA]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)HARPY] = new ENEMY(ENEMY_DIR, ENEMY_NAME_HARPY);	//�n�[�s�[�쐬
	if (enemy[(int)HARPY]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)IFRIT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_IFRIT);	//�C�t���[�g�쐬
	if (enemy[(int)IFRIT]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	//�G�̃f�[�^��csv�t�@�C������ǂݍ���
	if (data->LoadEnemy(enemy, ENEMY_DATA_DIR, ENEMY_DATA_NAME) == false) { return -1; }		//�ǂݍ��ݎ��s
	//�����ݒ�
	for (int i = 0; i < ENEMY_KIND; ++i)		//�G�̐����������ݒ�
	{
		enemy[i]->StateSetInit();		//�����ݒ�
	}

	//�A�C�e���֌W
	for (int i = 0; i < ITEM_KIND; ++i)	//�A�C�e���̎�ޕ�����
	{
		item[i] = new ITEM();	//�A�C�e���쐬
	}
	//�A�C�e���f�[�^��csv�t�@�C������ǂݍ���
	if (data->LoadItem(item, ITEM_DATA_DIR, ITEM_DATA_NAME) == false) { return -1; }		//�ǂݍ��ݎ��s

	//�}�b�v�֌W
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

		//fps->Draw(0, 0);				//FPS�̏���[�`��]

		ScreenFlip();				//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		fps->Wait();				//FPS�̏���[�҂�]
	}

	Delete_Class();			//�g�p�����N���X��j��

	DxLib_End();			//�c�w���C�u�����g�p�̏I������

	return 0;
}

//�^�C�g����ʂ̏���
void Title()
{
	//���������������������������� ���̍Đ������������� ������������������������������������
	if (bgm->GetIsPlay((int)TITLE_BGM) == false)	//�Đ�������Ȃ��Ƃ�
	{
		bgm->ChengeVolume(255 * 50 / 100, (int)TITLE_BGM);	//BGM�̉��ʂ�50%�ɕύX
		bgm->Play((int)TITLE_BGM);				//BGM���Đ�
	}
	//���������������������������� ���̍Đ����������܂� ��������������������������������������


	Title_Draw();		//�^�C�g����ʂ̕`�揈��

	ui->ChoiseOperation(keydown);	//�I�����̃L�[����

	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������
	if (keydown->IsKeyDown(KEY_INPUT_RETURN))				//�G���^�[�L�[�������ꂽ��
	{
		if (*ui->GetNowChoise() == "START")		//�I�����Ă��镶����"START"��������
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
	player->Operation(keydown);	//�v���C���[�L�[����

	Play_Draw();		//�`�揈��

	if (player->GetIsMenu() == true && keydown->IsKeyDownOne(KEY_INPUT_Q))		//���j���[�`�撆��Q�L�[�������ꂽ�u��
	{
		player->SetIsMenu(false);		//���j���[�`��I��
	}
	else if (keydown->IsKeyDownOne(KEY_INPUT_Q))		//Q�L�[�������ꂽ�u��
	{
		player->SetIsMenu(true);		//���j���[�`��J�n
	}

	//���������������������������������������������� ���j���[���̏����������� ��������������������������������������������������
	if (player->GetIsMenu())			//���j���[�`�撆��������
	{
		ui->ChoiseOperation(keydown);		//���j���[�E�B���h�E�L�[����

		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ��
		{
			ui->SetChoiseMenu(ui->GetNowChoise());		//�I���������e���Z�b�g

		}

		if (ui->GetIsChoise())	//�I�����Ă�����
		{
			if (ui->GetChoiseMenu() == (int)MENU_SAVE)	//�Z�[�u��I�񂾎�
			{
				if (Wait())			//�҂����Ԃ��߂�����
				{
					data->Save(player, PLAYER_DATA_DIR, PLAYER_DATA_NAME);		//�v���C���[���̃Z�[�u
					player->SetIsMenu(false);		//���j���[�`��I��
				}

			}

		}

	}
	else			//���j���[�`��I�����Ă���
	{
		ui->ResetMenu();	//���j���[�֌W�̃��Z�b�g
	}
	//������������������������������������ ���j���[���̏��������܂� ��������������������������������������������



	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������

	if (player->GetIsMove())			//�v���C���[���ړ�����������
	{
		Enconte();			//�G�Ƃ̑�������
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

	case (int)WAIT_ACT:		//�v���C���[�̍s���I��҂���Ԃ̎�

		if (Turn == (int)MY_TURN)		//�����̃^�[����������
		{
			ui->BattleOperation(keydown);			//�퓬��ʂ̃L�[����

			//�������������������������������������� �o�g���R�}���h���̏����������� ��������������������������������������
			switch (ui->GetChoiseCommamd())		//�ǂ̃R�}���h��I�񂾂�
			{
			case (int)COMMANDE_ATACK:					//�U����I�񂾎�

				BattleStageNow = (int)DAMEGE_CALC;	//�o�g����Ԃ��_���[�W�v�Z��Ԃ�

				break;

			case (int)COMMANDE_DEFENSE:		//�h���I�񂾎�

				BattleStageNow = (int)DAMEGE_CALC;	//�o�g����Ԃ��_���[�W�v�Z��Ԃ�

				break;

			case (int)COMMANDE_MAGIC:		//���@��I�񂾎�

				player->SetChoiseSkil(1);			//�g�p����X�L���𖂖@�ɐݒ肷��
				BattleStageNow = (int)DAMEGE_CALC;	//�o�g����Ԃ��_���[�W�v�Z��Ԃ�

				break;

			case (int)COMMANDE_ITEM:			//�A�C�e����I�񂾎�

				ui->BattleInit();	//�o�g���R�}���h���Z�b�g

				break;

			case (int)COMMANDE_ESCAPE:		//�������I�񂾎�

				BattleStageNow = (int)ACT_MSG;	//���b�Z�[�W�`����
				
				break;

			default:
				break;
			}
			//�������������������������������������� �o�g���R�}���h���̏��������܂� ��������������������������������������

		} 
		else if (Turn = (int)ENEMY_TURN)	//�G�̃^�[����������
		{
			//�G�̍s���I�����菈��

			BattleStageNow = (int)DAMEGE_CALC;	//�_���[�W�v�Z��

		}

		break;						//�s���I��҂���Ԃ̏��������܂�

	case (int)DAMEGE_CALC:			//�_���[�W�v�Z��Ԃ̎�

		if (Turn == (int)MY_TURN)		//�����̃^�[����������
		{
			player->DamegeCalc(enemy[EncounteEnemyType],ui->GetChoiseCommamd());		//�_���[�W�v�Z

			BattleStageNow = (int)ACT_MSG;	//�s�����b�Z�[�W�\����Ԃ�

		}
		else if (Turn = (int)ENEMY_TURN)	//�G�̃^�[����������
		{
			//�_���[�W�v�Z

			BattleStageNow = (int)ACT_MSG;	//�s�����b�Z�[�W�\����

		}

		break;						//�_���[�W�v�Z��Ԃ̎������܂�

	case (int)ACT_MSG:				//�s�����b�Z�[�W�\�����

		if (Wait())			//�҂����Ԃ��߂�����
		{
			if (Turn == (int)MY_TURN)		//�����̃^�[����������
			{
				if (ui->GetChoiseCommamd() == (int)COMMANDE_ESCAPE)		//�������I�񂾂�
				{
					SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//���̉�ʂ̓v���C���
				}
			}

			if (ui->GetChoiseCommamd() == (int)COMMANDE_DEFENSE)		//�h���I�񂾂�
			{
				effect->SetIsDrawEnd(true);	//�`�揈�����΂����߂ɁA�`��I���t���O�𗧂Ă�
			}

			BattleStageNow = (int)DRAW_EFFECT;			//�G�t�F�N�g�`���Ԃ�

		}

		break;						//�s�����b�Z�[�W�\����Ԃ����܂�

	case (int)DRAW_EFFECT:			//�G�t�F�N�g�`����

		if (Turn == (int)MY_TURN)		//�����̃^�[����������
		{
			if (ui->GetChoiseCommamd() == (int)COMMANDE_ATACK)	//�U����I��ł�����
			{
				effect->Draw(350, 250, (int)NOMAL_ATACK);	//�U���G�t�F�N�g�`��
			}
			else if (ui->GetChoiseCommamd() == (int)COMMANDE_MAGIC)	//���@��I��ł�����
			{
				effect->Draw((GAME_WIDTH / 2 - MAGIC_WIDTH / 2), (GAME_HEIGHT / 2 - MAGIC_HEIGHT / 2), player->GetChoiseSkil());	//���@�G�t�F�N�g�`��
			}

			if (effect->GetIsDrawEnd())		//�G�t�F�N�g�`�悪�I��������
			{

				BattleStageNow = (int)DRAW_DAMEGE;		//�_���[�W�`���Ԃ�

				enemy[EncounteEnemyType]->SetHP((enemy[EncounteEnemyType]->GetHP() - player->GetSendDamege()));	//�_���[�W��^����

			}

		}
		else if (Turn = (int)ENEMY_TURN)	//�G�̃^�[����������
		{
			//�G�̃G�t�F�N�g�\��
			effect->Draw((GAME_WIDTH / 2 - MAGIC_WIDTH / 2), (GAME_HEIGHT / 2 - MAGIC_HEIGHT / 2), enemy[EncounteEnemyType]->GetSkil());

			if (effect->GetIsDrawEnd())		//�G�t�F�N�g�`��I��������
			{
				player->SetHP((player->GetHP()) - (player->GetRecvDamege()));		//�����Ƀ_���[�W��^����

				ui->SetStateWindow(player->GetLevel(),player->GetHP(),player->GetMP());	//�`��X�e�[�^�X�X�V

				BattleStageNow = (int)DRAW_DAMEGE;		//�_���[�W�`���Ԃ�

			}

		}

		break;

	case (int)DRAW_DAMEGE:				//�_���[�W�`����

		//�_���[�W�`��
		if (Wait())				//�҂����Ԃ��߂�����
		{
			if (Turn == (int)MY_TURN)			//�����̃^�[���̎�
			{
				if (ui->GetChoiseCommamd() == (int)COMMANDE_ATACK)	//�U����I�񂾎���
				{
					effect->ResetIsAnime((int)NOMAL_ATACK);		//�G�t�F�N�g���Z�b�g
				}
				else							//�U���ȊO��I�񂾎���
				{
					effect->ResetIsAnime(player->GetChoiseSkil());		//�G�t�F�N�g���Z�b�g
				}

				Turn = (int)ENEMY_TURN;				//�G�̃^�[����

			}
			else if (Turn == (int)ENEMY_TURN)			//�G�̃^�[���̎�
			{
				effect->ResetIsAnime(enemy[EncounteEnemyType]->GetSkil());		//�G�t�F�N�g���Z�b�g
				Turn = (int)MY_TURN;				//�����̃^�[����

			}

			if (player->GetHP() <= 0)			//������HP��0�ɂȂ�����
			{
				player->SetIsArive(false);		//�������S

				player->SetIsBattleWin(false);	//�퓬�ɔs�k

				BattleStageNow = (int)RESULT_MSG;		//���U���g���b�Z�[�W�\����Ԃ�
			}
			else if (enemy[EncounteEnemyType]->GetHP() <= 0)				//�G��HP��0�ɂȂ�����
			{
				enemy[EncounteEnemyType]->SetIsArive(false);		//�G���S

				player->SetIsBattleWin(true);		//�퓬�ɏ���

				player->AddExp(enemy[EncounteEnemyType]->GetEXP());	//�o���l���Z

				BattleStageNow = (int)RESULT_MSG;		//���U���g���b�Z�[�W�\����Ԃ�
			}
			else
			{
				BattleStageNow = (int)WAIT_ACT;		//�s���I����Ԃ�
			}

			ui->BattleInit();				//�o�g���R�}���h���Z�b�g

		}

		break;

	case (int)RESULT_MSG:		//�퓬�I����̃��b�Z�[�W��`�悷����

		if (msg->GetDrawMsgKind()==(int)LEVELUP_MSG && se->GetIsPlayEnd()==false)	//���x���A�b�v�����Ƃ���
		{
			if (se->GetIsPlay((int)LEVELUP_SE) == false)		//�Đ�������Ȃ����
			{
				se->Play((int)LEVELUP_SE);		//���x���A�b�v��SE��炷
				se->SetIsPlayEnd(true);			//�Đ��I��
			}

			ui->SetStateWindow(player->GetLevel(), player->GetHP(), player->GetMP());	//�`��X�e�[�^�X�X�V

		}

		if (msg->GetIsResultMsgEnd())		//���U���g���b�Z�[�W�̕\�����I�����Ă�����
		{
			if (player->GetIsBattleWin())		//�퓬�ɏ������Ă�����
			{
				SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//���̉�ʂ̓v���C���
			}
			else if (player->GetIsBattleWin() == false)	//�퓬�ɔs�k���Ă�����
			{
				SceneChenge(GameSceneNow, (int)GAME_SCENE_END);	//���̉�ʂ̓G���h���
			}

			BattleStageNow = (int)WAIT_ACT;		//�s���I��҂���Ԃ�

		}

		break;					//�퓬�I����̃��b�Z�[�W��`�悷���Ԃ̏��������܂�

	default:

		break;


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

	End_Draw();	//�`�揈��

	ui->ChoiseOperation(keydown);	//�I�����̃L�[����

	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������
	if (keydown->IsKeyDown(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ�u��
	{
		if (*ui->GetNowChoise() == "TITLE")		//�I�����Ă��镶����"TITLE"��������
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

	//�t�F�[�h�A�E�g�̏���
	double ToukaPercent = ChengeDrawCount / (double)ChengeDrawCountMax;//���߁������߂�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * 255);	//���߂�����
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);	//�^���Âȉ�ʂɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//���߂���߂�

	//60�t���[�����A�҂�
	if (ChengeDrawCount < ChengeDrawCountMax)
	{
		ChengeDrawCount++;
	}
	else
	{
		GameSceneNow = GameSceneNext;	//���̉�ʂɂ���
		Init();							//������
		ui->ChoiseClear();				//�I�����̓��e���N���A����
	}


	return;

}

//����������
void Init()
{
	ChengeDrawCount = 0;		//�t�F�[�h�C���p������

	ui->SetStateWindow(player->GetLevel(), player->GetHP(), player->GetMP());	//�`��X�e�[�^�X�X�V

	se->SetIsPlayEnd(false);	//SE�̍Đ���ԃ��Z�b�g

	if (GameSceneBefor == (int)GAME_SCENE_BATTLE)	//�퓬��ʂ���J�ڂ����ꍇ
	{
		enemy[EncounteEnemyType]->StateSetInit();		//���������G������

		ui->BattleInit();			//�o�g���R�}���h������

		EncounteEnemyType = 0;		//���������G�̎�ނ����Z�b�g

		BattleStageNow = (int)WAIT_ACT;	//�o�g����Ԃ��A�s���҂���Ԃ�

		Turn = (int)MY_TURN;		//�^�[���𖡕��̃^�[���ɐݒ�

		msg->ResetResultMsg();		//���U���g���b�Z�[�W�֌W�̃����o�[�����Z�b�g

	}
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
	back->Draw(0, 0,(int)TITLE_BACK);	//�w�i�摜�`��

	title->Draw(0, GAME_HEIGHT / 2 - title->GetHeight(0) / 2);		//��ʒ����Ƀ^�C�g���`��

	font->SetSize(BIG_FONTSIZE);		//�t�H���g�T�C�Y��傫������

	ui->ChoiseDraw(GAME_WIDTH / 2 , DEFAULT_TEXT_Y,true,GetColor(255,255,255),"START", "END");	//�I�����`��
	
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

	static int Player_X = 0, Player_Y = 0;	//�v���C���[��X�ʒu��Y�ʒu

	player->GetNowPos(&Player_X, &Player_Y);//�v���C���[�̌��݈ʒu���擾

	if (player->GetIsMenu())	//���j���[�`�撆�Ȃ�
	{
		ui->DrawMenu(Player_X,Player_Y);	//���j���[�E�B���h�E�`��

		if (ui->GetIsChoise())	//�I��������
		{
			ui->DrawChoiseMenu(player, item);	//�I�������̕`��
		}
	}

	return;

}

//�퓬��ʂ̕`�揈��
void Battle_Draw()
{

	back_battle->Draw(0, 0);	//�w�i�摜��`��

	enemy[EncounteEnemyType]->Draw();	//�G�`��

	ui->DrawWindow(MSG_WINDOW_START_X, MSG_WINDOW_START_Y, MSG_WINDOW_WIDTH, MSG_WINDOW_HEIGHT);		//�E�B���h�E�̕`��

	//���b�Z�[�W�֌W�`��
	msg->DrawBattleMsg(BattleStageNow, Turn, ui->GetChoiseCommamd(), player, enemy[EncounteEnemyType],keydown->IsKeyDownOne(KEY_INPUT_RETURN));

	if (BattleStageNow == (int)WAIT_ACT)		//�s���I����Ԃ̎�
	{
		if (Turn == (int)MY_TURN)		//�����̃^�[����������
		{
			ui->DrawCommand();						//�o�g���R�}���h�`��
		}
		else if (Turn = (int)ENEMY_TURN)	//�G�̃^�[����������
		{

		}

	}

	ui->DrawStateWindow();		//�X�e�[�^�X�E�B���h�E�`��

	return;

}

//�G���h��ʂ̕`�揈��
void End_Draw()
{

	back->Draw(0, 0, (int)END_BACK);	//�w�i�摜�`��

	font->SetSize(BIG_FONTSIZE);	//�t�H���g�T�C�Y��傫������

	ui->ChoiseDraw(GAME_WIDTH / 2, DEFAULT_TEXT_Y, true ,GetColor(0,0,0),"TITLE", "END");	//�I�����`��

	return;

}

//�G�Ƃ̑�������
void Enconte()
{

	for (int i = 0; i < ENEMY_KIND; ++i)		//�G�̕��������[�v����
	{
		if (enemy[i]->GetEmergenceMap() == MapKind[MAPPOS_Y][MAPPOS_X])		//�G�̏o��MAP�����݂�MAP��������
		{
			//�����_���ő�������
			int rand = GetRand(enemy[i]->GetEncounteRate());		//�������͈͓̔��ŗ����𐶐�

			if (rand%enemy[i]->GetEncounteRate() == 0)			//�G�Ƒ���������
			{

				player->SetIsKeyDown(false);			//�v���C���[�̓������~�߂�

				EncounteEnemyType = i;		//���������G��ݒ�

				SceneChenge(GameSceneNow, (int)GAME_SCENE_BATTLE);	//���̉�ʂ͐퓬���

			}
		}
	}


	return;

}

//�҂���
/*
�߂�l�Ftrue�F�҂��Ԃ��߂�����
�߂�l�Ffalse�F�҂��Ă���Ƃ�
*/
bool Wait()
{
	static int WaitCnt = 0;		//�J�E���g�p
	static int WaitCntMax = 60;	//�҂ő�l

	if (WaitCnt == WaitCntMax)		//�҂��Ԃ��߂�����
	{
		WaitCnt = 0;	//�J�E���g���Z�b�g
		return true;
	}
	else
	{
		++WaitCnt;		//�J�E���g�A�b�v
		return false;
	}
}

//�Q�[�����Ŏg�p�����N���X���폜���鏈��
void Delete_Class()
{
	delete title;			//title��j��
	delete fps;				//FPS��j��
	delete keydown;			//keydown��j��
	delete font;			//font��j��
	delete bgm;				//bgm��j��
	delete se;				//se��j��
	delete player;			//player��j��
	delete back;			//back��j��
	delete back_battle;		//back_battle��j��
	delete mapimage;		//mapimage��j��
	delete data;			//data��j��
	delete effect;			//effect��j��
	delete msg;				//msg��j��

	//�}�b�v�f�[�^�̍폜
	for (int i = 0; i < MAP_DATA_KIND; i++)	//�}�b�v�̎�ޕ�
	{
		for (int cnt = 0; cnt < MAP_LAYER_KIND; cnt++)	//�}�b�v�̃��C���[��
		{
			delete mapdata[i][cnt];	//mapdata��j��
		}

	}

	//�G�̍폜
	for (int i = 0; i < ENEMY_KIND; ++i)	//�G�̎�ޕ�
	{
		delete enemy[i];			//enemy��j��
	}

	//�A�C�e���̍폜
	for (int i = 0; i < ITEM_KIND; ++i)	//�A�C�e���̎�ޕ�
	{
		delete item[i];				//item��j��
	}

	return;

}
