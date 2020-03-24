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
#include "MUSIC.hpp"
#include "ENEMY.hpp"
#include "UI.hpp"
#include "DATA.hpp"
#include "EFFECT.hpp"
#include "MSG.hpp"
#include "ITEM.hpp"
#include "SELECT.hpp"
#include "LIST_MGC.hpp"
#include "LIST_WEAPON.hpp"
#include "LIST_ARMOR.hpp"
#include "LIST_ITEM.hpp"
#include "NPC.hpp"

//########## �O���[�o���I�u�W�F�N�g ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPS�N���X�̃I�u�W�F�N�g�𐶐�
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWN�N���X�̃I�u�W�F�N�g�𐶐�

IMAGE *title;						//�^�C�g���摜
IMAGE *back;						//�w�i�摜
IMAGE *back_battle;					//�퓬��ʂ̔w�i�摜
IMAGE *description;						//�����摜
IMAGE *boss_mapimage;				//�}�b�v�ɕ`�悷��{�X�̉摜

MUSIC *bgm;							//BGM
MUSIC *bt_se;						//�퓬�Ŏg�p����SE
MUSIC *sys_se;						//�V�X�e����SE

EFFECT *Magic_effect;				//���@�G�t�F�N�g
EFFECT *Atack_effect;				//�U���G�t�F�N�g
EFFECT *Enemy_Atk_effect;			//�G�U���G�t�F�N�g
EFFECT *Boss_Atk_effect;			//�{�X�U���G�t�F�N�g

FONT *font;							//�t�H���g
UI *ui;								//UI
DATA *data;							//�f�[�^
MESSAGE *bt_msg[BT_MSG_KIND];		//�퓬��ʂ̃��b�Z�[�W

PLAYER *player;						//��l��

ENEMY *enemy[ENEMY_KIND];			//�G

NPC *npc;							//NPC

MAP *mapdata[DRAW_MAP_KIND][MAP_DATA_KIND];		//�}�b�v�f�[�^

//�I�����֌W
SELECT *Title_select;	//�^�C�g����ʂ̑I����
SELECT *End_select;		//�G���h��ʂ̑I����

//�ꗗ�֌W
LIST_MGC *mgc_list;			//���@�ꗗ
LIST_WEAPON *weapon_list;	//����ꗗ
LIST_ARMOR *armor_list;		//�h��ꗗ
LIST_ITEM *item_list;		//�A�C�e���ꗗ

//############## �O���[�o���ϐ� ##############
int GameSceneNow = (int)GAME_SCENE_TITLE;	//���݂̃Q�[���V�[��
int GameSceneBefor;							//�O�̃Q�[���V�[��
int GameSceneNext;							//���̃Q�[���V�[��

int BattleStageNow = (int)WAIT_ACT;	//�o�g���V�[���̌��݂̏��

int MapKind[MAP_DATA_TATE_KIND][MAP_DATA_YOKO_KIND];			//�}�b�v�̎��
int MapNowPos[2] = {0};											//���݂̃}�b�v��X�ʒu��Y�ʒu���i�[
int NowDrawMapKind = (int)DRAW_FILED;							//���݂̕`��}�b�v�̎��(�ŏ��̓t�B�[���h�}�b�v)
bool IsChengeDrawMap = false;									//�`�悷��}�b�v�̎�ނ�؂�ւ��邩

int ChengeDrawCount = 0;	//�t�F�[�h�A�E�g�����Ɏg�p

int EncounteEnemyType = ENEMY_ENCOUNT_TYPE_NONE;	//���������G�̎��
int Turn = (int)MY_TURN;	//�^�[��
int NowTurnCnt = 1;			//�^�[�������i�[����(1�^�[���ڂ���X�^�[�g)
int TotalTurnCnt = 0;		//�����̃^�[�������i�[����(�퓬���J�n���ꂽ��A�^�[�����Ƃɉ��Z�����)

bool GameEnd_Flg = false;	//�Q�[���I���t���O
bool Boss_flg = false;		//�{�X�t���O
bool Clear_flg = false;		//�N���A�t���O

bool IsLoad = false;		//�ǂݍ��݊����t���O

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//�w��̐��l�ŉ�ʂ�\������

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//�^�C�g���o�[����

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//�^�C�g���̕���

	SetWindowIconID(GAME_ICON_ID);								//�Q�[���̃A�C�R���ύX
	
	SetAlwaysRunFlag(TRUE);										//��A�N�e�B�u�ɐݒ�

	if (DxLib_Init() == -1) { return -1; }						//�c�w���C�u��������������

	SetDrawScreen(DX_SCREEN_BACK);								//Draw�n�֐��͗���ʂɕ`��

	SetUseASyncLoadFlag(TRUE);									//�񓯊��ǂݍ��݂ɐݒ�

	//�Q�[���f�[�^�ǂݍ��݊J�n(�񓯊�)
	if (LoadGameData() == false) { return -1; }		//�ǂݍ��ݎ��s���A�����I��

	//�Q�[���̃��C�����[�v
	while (GameMainLoop())	
	{
		/*
		���[�v���ňُ킪��������܂Ŗ������[�v
		�Q�[���I����G���[�������������烋�[�v�I��
		*/
	}

	Delete_Class();			//�g�p�����N���X��j��

	DxLib_End();			//�c�w���C�u�����g�p�̏I������

	return 0;
}

//���[�h��ʂ̏���
void Load()
{
	if (GetASyncLoadNum() != 0)			//�񓯊��œǂݍ���ł��鏈�����I����Ă��Ȃ�����
	{
		Load_Draw();					//���[�h��ʂ̕`�揈��
	}
	else								//�񓯊��œǂݍ���ł��鏈�����I���������
	{

		SetUseASyncLoadFlag(FALSE);		//�����ǂݍ��݂ɐݒ�

		if (!sys_se->GetIsPlayed((int)SYS_SE_LOAD))	//���[�h����炵�Ă��Ȃ����
		{
			sys_se->Play((int)SYS_SE_LOAD);	//���[�h����炷
			sys_se->SetIsPlayed((int)SYS_SE_LOAD, true);	//�Đ��ς�
		}

		description->DrawNow(GAME_LEFT, GAME_TOP);	//�����摜�`��

		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ��
		{
			sys_se->Play((int)SYS_SE_KETTEI);	//���艹�Đ�

			if (description->GetIsLast())	//�Ō�̉摜��������
			{
				description->ResetNowImage();//�����摜�����Z�b�g

				SetGameInit();					//�Q�[���̏����ݒ�
				IsLoad = true;					//�ǂݍ��݊���
			}
			else	//�Ō�̉摜����Ȃ����
			{
				description->NextImage();	//���̉摜��
			}
		}

	}

	return;

}

//�^�C�g����ʂ̏���
void Title()
{

	Init();	//����������

	//���������������������������� ���̍Đ������������� ������������������������������������
	if (bgm->GetIsPlay((int)BGM_TITLE) == false)	//�Đ�������Ȃ��Ƃ�
	{
		bgm->Stop();							//�S�Ă�BGM���~�߂�
		bgm->Play((int)BGM_TITLE);				//BGM���Đ�
	}
	//���������������������������� ���̍Đ����������܂� ��������������������������������������


	Title_Draw();		//�^�C�g����ʂ̕`�揈��

	Title_select->SelectOperation(keydown, sys_se);		//�I�����̃L�[����

	if (Title_select->GetSelectFlg())		//�I�����ꂽ��
	{
		if (Title_select->GetSelectNum()==(int)TITLE_SELECT_START)		//�X�^�[�g��I��������
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//���̉�ʂ̓v���C���
		}
		else	//�I����I��������
		{
			GameEnd_Flg = true;	//�Q�[���I��
		}

		Title_select->NowSelectReset();		//���ݑI�����Ă���v�f��擪�ɖ߂�
		Title_select->SetSelectFlg(false);	//�I�����Ă��Ȃ���Ԃ�

	}

	return;
}

//�v���C��ʂ̏���
void Play()
{

	if (NowDrawMapKind == (int)DRAW_FILED)		//�t�B�[���h�}�b�v�ɂ���Ƃ���
	{
		//���������������������������� ���̍Đ������������� ������������������������������������
		if (bgm->GetIsPlay((int)BGM_FIELD) == false)	//�Đ�������Ȃ��Ƃ�
		{
			bgm->Stop();							//�S�Ă�BGM���~�߂�
			bgm->Play((int)BGM_FIELD);				//�t�B�[���hBGM���Đ�
		}
		//���������������������������� ���̍Đ����������܂� ��������������������������������������

	}
	else if (NowDrawMapKind == (int)DRAW_CITY)	//�X�}�b�v�ɂ���Ƃ���
	{
		//���������������������������� ���̍Đ������������� ������������������������������������
		if (bgm->GetIsPlay((int)BGM_CITY) == false)	//�Đ�������Ȃ��Ƃ�
		{
			bgm->Stop();							//�S�Ă�BGM���~�߂�
			bgm->Play((int)BGM_CITY);				//�X��BGM���Đ�
		}
		//���������������������������� ���̍Đ����������܂� ��������������������������������������

	}

	Play_Draw();		//�`�揈��

	if (!player->GetIsKeyOpe())	//�v���C���[�̃L�[���삪�s�\�ɂȂ��Ă����ꍇ
	{
		player->SetIsKeyOpe(true);	//�v���C���[�̃L�[������\��
	}

	player->Operation(keydown, mapdata[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->GetRect((int)MAP_NG));	//�v���C���[�L�[����

	//������������������������������������������������ �}�b�v�؂�ւ������������� ��������������������������������������������������
	if (player->GetChengeMapKind() != -1)		//�}�b�v�̒[�ɗ�����
	{
		int chengekind = (int)MAP_CHENGE_NONE;	//�}�b�v�؂�ւ��̎��

		//�X�ֈړ�����Ƃ���
		if (player->CheckDetectionMap(mapdata[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->GetRect((int)MAP_WARP)))
		{
			if (NowDrawMapKind == (int)DRAW_FILED)		//�`��}�b�v���t�B�[���h��������
			{
				NowDrawMapKind = (int)DRAW_CITY;		//�`��}�b�v���X�֐؂�ւ���
			}
			else if (NowDrawMapKind == (int)DRAW_CITY)	//�`��}�b�v���X��������
			{
				NowDrawMapKind = (int)DRAW_FILED;		//�`��}�b�v���t�B�[���h�֐؂�ւ���
			}

			IsChengeDrawMap = true;	//�`��}�b�v��؂�ւ���
		}
		else		//�ړ����Ȃ��Ƃ���
		{
			IsChengeDrawMap = false;	//�`��}�b�v��؂�ւ��Ȃ�
		}

		//�}�b�v�̐؂�ւ�����
		chengekind = mapdata[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->ChengeMap(player->GetChengeMapKind(), MapNowPos, IsChengeDrawMap);

		if (chengekind != (int)MAP_CHENGE_NONE)	//�}�b�v�؂�ւ����s�����Ƃ���
		{

			player->SetChengePos(chengekind);		//�v���C���[�̈ʒu���C��

			player->ResetChengeMapKind();			//�}�b�v�؂�ւ��̎�ރ��Z�b�g

		}
	}
	//���������������������������������������������������� �}�b�v�؂�ւ����������܂� ��������������������������������������������������

	if (player->GetIsMenu())		//���j���[�`�撆��
	{
		if (keydown->IsKeyDownOne(KEY_INPUT_Q) ||	//Q�L�[�������ꂽ�ꍇ��
			!ui->MenuSelect->GetSelectFlg() && keydown->IsKeyDownOne(KEY_INPUT_BACK))//���j���[��I��ł��Ȃ���ԂŁA�o�b�N�X�y�[�X�L�[�������ꂽ��
		{
			sys_se->Play((int)SYS_SE_CANSEL);	//�L�����Z������炷
			sys_se->Reset();				//�Đ���ԃ��Z�b�g
			player->SetIsMenu(false);		//���j���[�`��I��
		}
	}		//���j���[�`�撆����Ȃ��Ƃ�
	else if (keydown->IsKeyDownOne(KEY_INPUT_Q))		//Q�L�[�������ꂽ�u��
	{
		sys_se->Play((int)SYS_SE_MENU);	//���j���[���J������炷
		sys_se->Reset();				//�Đ���ԃ��Z�b�g
		player->SetIsMenu(true);		//���j���[�`��J�n
	}

	//���������������������������������������������� ���j���[���̏����������� ��������������������������������������������������
	if (player->GetIsMenu())			//���j���[�`�撆��������
	{
		if (ui->MenuSelect->GetSelectFlg())	//�I�����Ă�����
		{

			switch (ui->MenuSelect->GetSelectNum())	//�I���������e��
			{

			case (int)MENU_STATUS:		//�X�e�[�^�X��I�񂾂Ƃ�

				break;	//�X�e�[�^�X��I�񂾂Ƃ������܂�

			case (int)MENU_ITEM:		//�A�C�e����I�񂾂Ƃ�

					ui->SelectUpdate(player->GetItemClass(), item_list);	//�A�C�e���̑I�����̓��e�X�V

					//�A�C�e����ʂ̏���
					if (ui->MenuSelectItem(keydown, sys_se))	//�A�C�e����I�������ꍇ
					{
						if (player->UseItem(ui->ItemSelect->GetSelectCode()))	//�A�C�e�����g�p�ł�����
						{
							sys_se->Play((int)SYS_SE_ITEM);	//�A�C�e���g�p�̉���炷
							ui->Yes_No->Default();			//�͂��A�������̑I�����f�t�H���g��
							ui->ItemSelect->Default();		//�A�C�e���̑I�����f�t�H���g��
						}
						else		//�g�p�ł��Ȃ�������
						{
							//�g�p�ł��Ȃ��ꍇ�̏�����ǉ��\��
							sys_se->Play((int)SYS_SE_BLIP);
							ui->Yes_No->Default();		//�͂��A�������̑I�����f�t�H���g��
							ui->ItemSelect->Default();	//�A�C�e���̑I�����f�t�H���g��
						}
					}

				break;	//�A�C�e����I�񂾂Ƃ������܂�

			case (int)MENU_EQUIPMENT:	//������I�񂾂Ƃ�

				ui->SelectUpdate(player->GetWeaponClass(), weapon_list);	//����̑I�����̓��e���X�V
				ui->SelectUpdate(player->GetArmorClass(), armor_list);		//�h��̑I�����̓��e���X�V

				//������ʂ̏���
				switch (ui->MenuSelectEquip(keydown,sys_se))	//����A�h��̂ǂ����I��������
				{

				case (int)SELECT_EQUIP_WEAPON:	//�����I�������ꍇ

					//����̑�������
					//�I����������̗v�f�ԍ����擾��
					//���푕�������̈����Ƃ��ēn��
					player->EquipWeapon(ui->WeaponSelect->GetSelectNum());	//����𑕔�����
					ui->WeaponSelect->Default();							//����̑I�����f�t�H���g��


					break;	//�����I�������ꍇ�����܂�

				case (int)SELECT_EQUIP_ARMOR:	//�h���I�������ꍇ

					//�h��̑�������
					//�I�������h��̗v�f�ԍ����擾��
					//�h��������̈����Ƃ��ēn��
					player->EquipArmor(ui->ArmorSelect->GetSelectNum());	//�h��𑕔�����
					ui->ArmorSelect->Default();								//�h��̑I�����f�t�H���g��

					break;	//�h���I�������ꍇ�����܂�

				default:
					break;
				}

				break;	//������I�񂾂Ƃ������܂�

			case (int)MENU_SETUMEI:		//������I�񂾂Ƃ�

				if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ��
				{
					sys_se->Play((int)SYS_SE_KETTEI);	//���̍Đ�

					if (description->GetIsLast())	//�Ō�̉摜��������
					{
						ui->ResetMenu();	//���j���[���Z�b�g
						description->ResetNowImage();	//�`�悷��摜���ŏ��ɖ߂�
					}
					else	//�Ōザ��Ȃ����
					{
						description->NextImage();	//���̐�����
					}
				}

				break;	//������I�񂾂Ƃ������܂�

			case (int)MENU_SAVE:		//�Z�[�u��I�񂾂Ƃ�

				if (Wait())			//�҂����Ԃ��߂�����
				{
					player->Save(PLAYER_DATA_DIR, PLAYER_DATA_NAME);		//�v���C���[���̃Z�[�u
					data->SaveMap(NowDrawMapKind, MapNowPos, MAPPOS_DATA_DIR, MAPPOS_DATA_NAME);	//�}�b�v�ʒu�̃Z�[�u
					sys_se->Play((int)SYS_SE_SAVE);		//�Z�[�u����炷
					player->SetIsMenu(false);			//���j���[�`��I��
				}

				break;	//�Z�[�u��I�񂾂Ƃ������܂�

			default:
				break;
			}

		}
		else			//�I�������Ă��Ȃ�������
		{
			ui->MenuSelect->SelectOperation(keydown, sys_se);			//���j���[�E�B���h�E�L�[����
		}

	}
	else			//���j���[�`��I�����Ă���
	{
		ui->ResetMenu();	//���j���[�֌W�̃��Z�b�g
	}


	//������������������������������������ ���j���[���̏��������܂� ��������������������������������������������



	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������

	if (player->GetIsKeyDown())		//�L�[���͂���Ă���(�v���C���[���ړ�����������)
	{

			if (player->CheckDetectionMap(mapdata[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->GetRect((int)MAP_ENCOUNT)))	//�G�Ƒ�������}�b�v��������
			{
				Enconte();			//�G�Ƃ̑�������
			}

			//�{�X�}�b�v�ֈړ�����Ƃ���
			if (player->CheckDetectionMap(mapdata[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->GetRect((int)MAP_WARP_BOSS)))
			{
				Boss_flg = true;		//�{�X�t���O�𗧂Ă�
				MAPPOS_Y = BOSS_MAP_NUM_Y;	//���݂̃}�b�v�ʒu���{�X�}�b�v�֐؂�ւ��iX�j
				MAPPOS_X = BOSS_MAP_NUM_X;	//���݂̃}�b�v�ʒu���{�X�}�b�v�֐؂�ւ��iY)
				player->SetPosAbsolute(BOSS_PLAYER_X, BOSS_PLAYER_Y);	//�v���C���[�̈ʒu���C��
			}

	}

	//������������������������������ ��ʑJ�ڂ̏��� ��������������������������������������


	return;
}

//�퓬��ʂ̏���
void Battle()
{

	//���������������������������� ���̍Đ������������� ������������������������������������
	if (bgm->GetIsPlay((int)BGM_BATTLE) == false)	//�Đ�������Ȃ��Ƃ�
	{
		bgm->Stop();							//�S�Ă�BGM���~�߂�
		bgm->Play((int)BGM_BATTLE);				//�퓬BGM���Đ�
	}
	//���������������������������� ���̍Đ����������܂� ��������������������������������������

	Battle_Draw();			//�`�揈��

	switch (BattleStageNow)		//���݂̃o�g�����
	{

	case (int)WAIT_ACT:		//�v���C���[�̍s���I��҂���Ԃ̎�

		Bt_WaitAct();		//�s���҂���Ԃ̏���

		break;				//�s���I��҂���Ԃ̏��������܂�

	case (int)DAMEGE_CALC:	//�_���[�W�v�Z��Ԃ̎�

		Bt_DamegeCalc();	//�_���[�W�v�Z��Ԃ̏���

		break;				//�_���[�W�v�Z��Ԃ̎������܂�

	case (int)ACT_MSG:		//�s�����b�Z�[�W�\�����

		Bt_ActMsg();		//�s�����b�Z�[�W�\����Ԃ̏���

		break;				//�s�����b�Z�[�W�\����Ԃ����܂�

	case (int)DRAW_EFFECT:	//�G�t�F�N�g�`����

		Bt_DrawEffect();	//�G�t�F�N�g�`���Ԃ̏���

		break;				//�G�t�F�N�g�`���Ԃ����܂�

	case (int)DRAW_DAMEGE:	//�_���[�W�`����
		
		Bt_DrawDamege();	//�_���[�W�`���Ԃ̏���

		break;				//�_���[�W�`���Ԃ̏��������܂�

	case (int)RESULT_MSG:	//�퓬�I����̃��b�Z�[�W��`�悷����

		Bt_ResultMsg();		//���U���g���b�Z�[�W�`���Ԃ̏���

		break;				//�퓬�I����̃��b�Z�[�W��`�悷���Ԃ̏��������܂�

	default:
		break;

	}

	return;
}

//�G���h��ʂ̏���
void End()
{

	//���������������������������� ���̍Đ������������� ������������������������������������
	if (bgm->GetIsPlay((int)BGM_END) == false)	//�Đ�������Ȃ��Ƃ�
	{
		bgm->Stop();							//�S�Ă�BGM���~�߂�
		bgm->Play((int)BGM_END);				//�G���hBGM���Đ�
	}
	//���������������������������� ���̍Đ����������܂� ��������������������������������������

	End_Draw();	//�`�揈��

	End_select->SelectOperation(keydown, sys_se);		//�I�����̃L�[����

	if (End_select->GetSelectFlg())						//�I�����ꂽ��
	{
		if (End_select->GetSelectNum()==(int)END_SELECT_TITLE)		//�^�C�g����I��������
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_TITLE);	//���̉�ʂ̓^�C�g�����
		}
		else	//�I����I��������
		{
			GameEnd_Flg = true;	//�Q�[���I��
		}


		player->Recovery();	//��

		End_select->NowSelectReset();	//�I����ԃ��Z�b�g
		End_select->SetSelectFlg(false);//�I�����Ă��Ȃ���Ԃ�

	}


	return;
}

//��ʑJ�ڂ̉��o�����鏈��
void Chenge()
{
	const int ChengeDrawCountMax = 60;	//�t�F�[�h�C�������Ɏg�p

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
		ChengeDrawCount = 0;			//�t�F�[�h�C���p������
		GameSceneNow = GameSceneNext;	//���̉�ʂɂ���
	}


	return;

}

//����������
void Init()
{
	Clear_flg = false;	//�N���A�t���O���Z�b�g
}

//�퓬��ʊ֌W������
void BattleInit(void)
{

	ui->BattleInit();			//�o�g���R�}���h������

	player->BattleInit();		//�퓬�Ŏg�p����v�f������

	bt_se->Reset();				//SE�̍Đ���Ԃ����Z�b�g

	if (EncounteEnemyType != ENEMY_ENCOUNT_TYPE_NONE)	//���������G�̎�ނ������Ă�����
	{
		enemy[EncounteEnemyType]->StateSetInit();		//���������G������
		EncounteEnemyType = ENEMY_ENCOUNT_TYPE_NONE;	//���������G�̎�ނ����Z�b�g
	}

	BattleStageNow = (int)WAIT_ACT;	//�o�g����Ԃ��A�s���҂���Ԃ�

	NowTurnCnt = 1;				//���̐퓬�ɔ����āA�^�[���������Z�b�g
	TotalTurnCnt = 0;			//���̐퓬�ɔ����āA�^�[���������Z�b�g
	Turn = (int)MY_TURN;		//�^�[���𖡕��̃^�[���ɐݒ�

	for (int i = 0; i < BT_MSG_KIND; ++i)	//���b�Z�[�W�̎�ޕ�
	{
		bt_msg[i]->ResetFlg();		//�t���O���Z�b�g
	}

	return;

}

//�V�[����ύX���鏈��
void SceneChenge(int beforscene, int nextscene)
{
	GameSceneBefor = beforscene;				//���݂̃Q�[���V�[����O�̃Q�[���V�[���Ƃ��ĕۑ�
	GameSceneNow = (int)GAME_SCENE_CHENGE;		//�J�ډ�ʂɕύX
	GameSceneNext = nextscene;					//���̃V�[�����w��
	return;
}

//���[�h��ʂ̕`�揈��
void Load_Draw()
{
	std::string LoadMessage = "Now Loading�E�E�E";		//���[�h��ʂɕ`�悷�镶��
	int Width = 0;										//����
	int Strlen = 0;										//������

	Strlen = strlen(LoadMessage.c_str());						//�������擾
	Width = GetDrawStringWidth(LoadMessage.c_str(), Strlen);	//�����擾

	DrawFormatString((GAME_WIDTH / 2) - (Width / 2), GAME_HEIGHT / 2, GetColor(255, 255, 255),"%s",LoadMessage.c_str());	//���[�h�����`��

	return;
}

//�^�C�g����ʂ̕`�揈��
void Title_Draw()
{
	back->Draw(GAME_LEFT, GAME_TOP,(int)TITLE_BACK);	//�w�i�摜�`��

	title->Draw(GAME_LEFT, GAME_HEIGHT / 2 - title->GetHeight() / 2);		//��ʒ����Ƀ^�C�g���`��

	font->SetSize(BIG_FONTSIZE);		//�t�H���g�T�C�Y��傫������

	Title_select->DrawCenter(GAME_WIDTH / 2, DEFAULT_TEXT_Y,(int)SELECT_TRIANGLE);	//�I�����`��
	
	return;

}

//�v���C��ʂ̕`�揈��
void Play_Draw()
{
	font->SetSize(DEFAULT_FONTSIZE);	//�t�H���g�T�C�Y��W���ɖ߂�

	mapdata[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->Draw();	//�}�b�v�`��

	if (Boss_flg)		//�{�X�}�b�v�ɂ���Ƃ���
	{
		boss_mapimage->Draw(BOSS_MAP_X, BOSS_MAP_Y);			//�{�X�L�����`��
	}

	//NPC�`�揈��

	player->DrawWalk();		//�v���C���[�`��

	//�������������������������������������������� ���j���[�`�揈���������� ����������������������������������������
	if (player->GetIsMenu())	//���j���[�`�撆�Ȃ�
	{
		ui->DrawMenu();			//���j���[�E�B���h�E�`��

		if (ui->MenuSelect->GetSelectFlg())	//�I��������
		{

			ui->DrawWindow(MENU_WINDOW_X, MENU_WINDOW_Y, MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//�E�B���h�E�`��

			switch (ui->MenuSelect->GetSelectNum())		//�I�񂾓��e���Ƃɏ����𕪂���
			{

			case (int)MENU_STATUS:	//�X�e�[�^�X��I�񂾎��̏�����������

				ui->DrawMenuState(player);		//�X�e�[�^�X�`��

				break;				//�X�e�[�^�X��I�񂾎��̏��������܂�

			case (int)MENU_ITEM:	//�A�C�e����I�񂾎��̏�����������

				//�A�C�e���`�揈��
				if (ui->ItemSelect->GetSelectKind() != 0)	//�A�C�e�������ވȏ㎝���Ă�����
				{
					ui->DrawItemSelect(MENU_TEXT_X,MENU_TEXT_TOP_Y, player->GetItemClass(),item_list);	//�A�C�e���`��

					if (ui->ItemSelect->GetSelectFlg())		//�A�C�e����I��������
					{
						ui->DrawMenuCheck();	//�m�F���b�Z�[�W�`��
					}

				}

				break;				//�A�C�e����I�񂾂Ƃ��̏��������܂�

			case (int)MENU_EQUIPMENT:	//������I�񂾎��̏�����������

				//�����`�揈��

				ui->DrawMenuEquip(player->GetWeaponClass(), player->GetArmorClass());	//�����`�揈��

				if (ui->GetMenuEquipDir() == (int)MENU_EQUIP_SELECT_DECISION)		//�I�����̒i�K���A�͂��A�������̒i�K��������
				{
					ui->DrawMenuCheck();	//�m�F���b�Z�[�W�`��
				}

				break;				//������I�񂾎��̏��������܂�

			case (int)MENU_SETUMEI:	//���������I�񂾎��̏�����������

				description->DrawNow(GAME_LEFT, GAME_TOP);	//�����摜�̕`��

				break;				//���������I�񂾎��̏��������܂�

			case (int)MENU_SAVE:	//�Z�[�u��I�񂾎��̏�����������

				//�Z�[�u���̕`�揈��
				DrawString(MENU_TEXT_X, MENU_TEXT_TOP_Y, SAVE_TEXT, GetColor(255, 255, 255));	//�����`��

				break;				//�Z�[�u��I�񂾎��̏��������܂�

			default:
				break;
			}

		}
	}
	//���������������������������������� ���j���[�`�揈�������܂� ������������������������������������������

	return;

}

//�퓬��ʂ̕`�揈��
void Battle_Draw()
{

	back_battle->Draw(GAME_LEFT, GAME_TOP, MapKind[MAPPOS_Y][MAPPOS_X]);	//�w�i�摜��`��

	enemy[EncounteEnemyType]->Draw();	//�G�`��

	ui->DrawStateWindow(player);		//�X�e�[�^�X�E�B���h�E�`��

	ui->DrawCommand();					//�o�g���R�}���h�`��

	ui->DrawUiImage(BT_WINDOW_X, BT_WINDOW_Y, (int)UI_WINDOW);	//���b�Z�[�W�E�B���h�E�`��

	ui->DrawUiAnime(ui->GetUiImageWidth((int)UI_WINDOW) / 2 - TXT_POSE_WIDTH / 2, BT_TXT_POSE_Y);		//�e�L�X�g�|�[�Y�`��

	return;

}

//�G���h��ʂ̕`�揈��
void End_Draw()
{

	back->Draw(GAME_LEFT, GAME_TOP, (int)END_BACK);	//�w�i�摜�`��

	if (Clear_flg)		//�N���A���Ă�����
	{
		int Strlen = strlen(GAME_CLEAR_TEXT);
		int Width = GetDrawStringWidth(GAME_CLEAR_TEXT, Strlen);	//�����擾

		DrawString((GAME_WIDTH / 2) - (Width / 2), GAME_HEIGHT / 2, GAME_CLEAR_TEXT, GetColor(255, 0, 0));		//�N���A�����`��

		MAPPOS_Y = AF_CLEAR_MAP_NUM_Y;	//���݂̃}�b�v�ʒu���{�X�}�b�v�̑O�֐؂�ւ��iX�j
		MAPPOS_X = AF_CLEAR_MAP_NUM_X;	//���݂̃}�b�v�ʒu���{�X�}�b�v�̑O�֐؂�ւ��iY)
		player->SetPosAbsolute(PLAYER_AF_CLEAR_POS_X, PLAYRT_AF_CLEAR_POS_Y);	//�v���C���[�̈ʒu���C��
		Boss_flg = false;	//�{�X�t���O���Z�b�g


	}
	else				//�N���A���Ă��Ȃ�������
	{
		int Strlen = strlen(GAME_OVER_TEXT);
		int Width = GetDrawStringWidth(GAME_OVER_TEXT, Strlen);	//�����擾

		DrawString((GAME_WIDTH / 2) - (Width / 2), GAME_HEIGHT / 2, GAME_OVER_TEXT, GetColor(255, 0, 0));		//�Q�[���I�[�o�[�����`��
	}

	font->SetSize(BIG_FONTSIZE);	//�t�H���g�T�C�Y��傫������

	End_select->DrawCenter(GAME_WIDTH / 2, DEFAULT_TEXT_Y, (int)SELECT_TRIANGLE,GetColor(0,0,0));		//�I�����`��

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
			int rand = GetRand(enemy[i]->GetEncounteRate());	//�������͈͓̔��ŗ����𐶐�

			if (rand%enemy[i]->GetEncounteRate() == 0)			//�G�Ƒ���������
			{
				BattleInit();		//�퓬�֌W������

				player->SetIsKeyOpe(false);	//�v���C���[�̓������~�߂�

				EncounteEnemyType = i;			//���������G��ݒ�

				//�`�敶���ݒ�
				switch (GetRand(ENCOUNT_TXT_KIND-1))
				{

				case (int)ENCOUNT_TXT_PATARN1:

					bt_msg[(int)BT_MSG_ACT]->SetMsg(ENCOUNT_TEXT_1);	//�G���J�E���g�e�L�X�g�ݒ�


					break;

				case (int)ENCOUNT_TXT_PATARN2:

					bt_msg[(int)BT_MSG_ACT]->SetMsg(ENCOUNT_TEXT_2);		//�G���J�E���g�e�L�X�g�ݒ�

					break;

				case (int)ENCOUNT_TXT_PATARN3:

					bt_msg[(int)BT_MSG_ACT]->SetMsg(ENCOUNT_TEXT_3);		//�G���J�E���g�e�L�X�g�ݒ�

					break;
						
				default:
					break;
				}

				bt_msg[(int)BT_MSG_ACT]->AddText(enemy[EncounteEnemyType]->GetName());	//�G���J�E���g�����G�̖��O�擾
				bt_msg[(int)BT_MSG_ACT]->AddText(ENCOUNT_AF_TEXT);		//���b�Z�[�W���e�ǉ�
				bt_msg[(int)BT_MSG_ACT]->AddMsg(BT_WAIT_ACT_TEXT);		//���b�Z�[�W�ǉ�

				sys_se->Play((int)SYS_SE_ENCOUNT);					//�G�Ƒ�����������炷
				sys_se->Reset();									//�Đ���ԃ��Z�b�g

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

	if (WaitCnt == GAME_WAITCNT_MAX)		//�҂��Ԃ��߂�����
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
	delete description;			//setumei��j��
	delete fps;				//FPS��j��
	delete keydown;			//keydown��j��
	delete font;			//font��j��
	delete bgm;				//bgm��j��
	delete bt_se;			//bt_se��j��
	delete sys_se;			//sys_se��j��
	delete player;			//player��j��
	delete back;			//back��j��
	delete back_battle;		//back_battle��j��
	delete data;			//data��j��
	delete Magic_effect;	//effect��j��
	delete boss_mapimage;	//boss_mapimage��j��
	delete Title_select;	//title_select�j��
	delete End_select;		//end_select�j��
	delete mgc_list;		//mgc_list��j��
	delete weapon_list;		//weapon_list��j��
	delete armor_list;		//armor_list��j��
	delete npc;				//npc��j��

	//���b�Z�[�W�̍폜
	for (int i = 0; i < BT_MSG_KIND; ++i)
	{
		delete bt_msg[i];				//bt_msg��j��
	}

	//�}�b�v�f�[�^�̍폜
	for (int cnt = 0; cnt < DRAW_MAP_KIND; ++cnt)
	{
		for (int i = 0; i < MAP_DATA_KIND; i++)	//�}�b�v�̎�ޕ�
		{
			delete mapdata[cnt][i];	//mapdata��j��
		}

	}

	//�G�̍폜
	for (int i = 0; i < ENEMY_KIND; ++i)	//�G�̎�ޕ�
	{
		delete enemy[i];			//enemy��j��
	}
	return;

}

//�Q�[�����Ŏg�p����f�[�^����ǂݍ��ޏ���
/*
�߂�l�Ftrue�F�ǂݍ��ݐ���
�߂�l�Ffalse�F�ǂݍ��ݎ��s
*/
bool LoadGameData()
{

	//�t�H���g�֌W
	font = new FONT(MY_FONT_DIR, MY_FONT_NAME, FONT_NAME);			//�t�H���g�𐶐�
	if (font->GetIsLoad() == false) { return false; }				//�ǂݍ��ݎ��s��

	//�摜�֌W
	title = new IMAGE(MY_IMG_DIR_TITLE, MY_ING_NAME_TITLE);			//�^�C�g���摜�𐶐�
	if (title->GetIsLoad() == false) { return false; }				//�ǂݍ��ݎ��s��

	back = new IMAGE(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK_TITLE);			//�w�i�摜�𐶐�
	if (back->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s��
	back->AddImage(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK_END);	//�G���h��ʂ̔w�i�摜�ǂݍ���
	if (back->GetIsLoad() == false) { return false; }							//�ǂݍ��ݎ��s

	back_battle = new IMAGE(MY_IMG_DIR_BATTLE, IMG_NAME_BT_SOUGEN);		//�퓬���(����)�̔w�i�摜�ǂݍ���
	if (back_battle->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_FOREST);		//�퓬��ʁi�X�j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_OCEAN);		//�퓬��ʁi�C�j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_AUTUMN);		//�퓬��ʁi�H�j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_BOSS);			//�퓬��ʁi�{�X�j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_SPRING);		//�퓬��ʁi�t�j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_WINTER);		//�퓬��ʁi�~�j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_REMAINS);		//�퓬��ʁi��Ձj�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_CASTLE);		//�퓬��ʁi��j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s


	description = new IMAGE(MY_IMG_DIR_DISCRIPTION, DISCRIPTION_PLAY_NAME);		//�����摜�̓ǂݍ���
	if (description->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s
	description->AddImage(MY_IMG_DIR_DISCRIPTION, DISCRIPTION_BATTLE_NAME);		//�����摜�ǉ�
	if (description->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s
	description->AddImage(MY_IMG_DIR_DISCRIPTION, DISCRIPTION_BP_NAME);			//�����摜�ǉ�
	if (description->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s

	//���֌W
	bgm = new MUSIC(MY_MUSIC_DIR_BGM, MY_BGM_NAME_TITLE);		//BGM�𐶐�
	if (bgm->GetIsLoad() == false) { return false; }						//�ǂݍ��ݎ��s��
	if (bgm->Add(MY_MUSIC_DIR_BGM, MY_BGM_NAME_FIELD) == false) { return false; }	//�t�B�[���h��BGM�ǉ�
	if (bgm->Add(MY_MUSIC_DIR_BGM, MY_BGM_NAME_CITY) == false) { return false; }	//�X��BGM�ǉ�
	if (bgm->Add(MY_MUSIC_DIR_BGM, MY_BGM_NAME_BATTLE) == false) { return false; }//�퓬��ʂ�BGM�ǉ�
	if (bgm->Add(MY_MUSIC_DIR_BGM, MY_BGM_NAME_END) == false) { return false; }//�G���h��ʂ�BGM�ǉ�

	//�퓬�Ŏg�p����SE
	bt_se = new MUSIC(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_LEVUP);	//SE�𐶐�
	if (bt_se->GetIsLoad() == false) { return false; }						//�ǂݍ��ݎ��s��
	bt_se->ChengePlayType(DX_PLAYTYPE_BACK);								//�Đ����@�ύX
	//���̒ǉ�����
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_SLASH) == false) { return false; }		//�a��Ƃ��̉��ǉ�
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_THUNDER) == false) { return false; }		//���̉��ǉ�
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_NIGERU) == false) { return false;	}		//������Ƃ��̉��ǉ�
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_DAMEGE) == false) { return false; }		//�_���[�W���ǉ�
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_RECOVERY) == false) { return false; }		//�񕜉��ǉ�
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_BPPLUS) == false) { return false; }		//�g�p����BP�𑝂₷���ǉ�
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_BPMINUS) == false) { return false; }		//�g�p����BP�����炷���ǉ�
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_BPCHARGE) == false) { return false; }		//BP�`���[�W���ǉ�

	//�V�X�e���Ŏg�p����SE
	sys_se = new MUSIC(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_CURSOR);	//�V�X�e���pSE����
	if (sys_se->GetIsLoad() == false) { return false; }							//�ǂݍ��ݎ��s
	sys_se->ChengePlayType(DX_PLAYTYPE_BACK);									//�Đ����@�ύX
	//���̒ǉ�����
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_CANSEL) == false) { return false; }		//�L�����Z�����ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_KETTEI) == false) { return false; }		//���艹�ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_MENU) == false) { return false; }		//���j���[���J�������̉��ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_ENCOUNT) == false) { return false; }	//�G�Ƒ����������̉��ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_SAVE) == false) { return false; }		//�Z�[�u�̉��ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_BLIP) == false) { return false; }		//�I���ł��Ȃ��Ƃ��̉��ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_ITEM) == false) { return false; }		//�A�C�e�����g�p�����Ƃ��̉��ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_EQUIP) == false) { return false; }		//���������Ƃ��̉��ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_LOAD) == false) { return false; }		//���[�h�����Ƃ��̉��ǉ�


	data = new DATA();		//�f�[�^

	//���b�Z�[�W�֌W
	for (int cnt = 0; cnt < BT_MSG_KIND; ++cnt)
	{
		bt_msg[cnt] = new MESSAGE();	//���b�Z�[�W�쐬
	}

	//�G�t�F�N�g�֌W
	//���@�G�t�F�N�g
	Magic_effect = new EFFECT(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC, MAGIC_ALL_CNT, MAGIC_YOKO_CNT, MAGIC_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC_SPEED, false, MAGIC_EFFECT_KIND);
	if (Magic_effect->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s
	if (Magic_effect->Add(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC2, MAGIC2_ALL_CNT, MAGIC2_YOKO_CNT, MAGIC2_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC_SPEED, false, (int)MAGIC_2) == false) { return false; }	//�ǂݍ��ݎ��s

	//�U���G�t�F�N�g
	Atack_effect = new EFFECT(MY_ANIME_DIR_ATKEFECT, MY_ANIME_NAME_ATKEFECT, ATK_ALL_CNT, ATK_YOKO_CNT, ATK_TATE_CNT, ATK_WIDTH, ATK_HEIGHT, ATK_SPEED, false, ATACK_EFFECT_KIND);
	if (Atack_effect->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s

	//�G�U���G�t�F�N�g
	Enemy_Atk_effect = new EFFECT(MY_ANIME_DIR_ENE_ATK, MY_ANIME_NAME_ENE_ATK_TUME, ENE_ATK_TUME_ALL_CNT, ENE_ATK_TUME_YOKO_CNT, ENE_ATK_TUME_TATE_CNT, ENE_ATK_TUME_WIDTH, ENE_ATK_TUME_HEIGHT, ENE_ATK_TUME_SPEED, false, ENE_ATK_EFFECT_KIND);
	if (Enemy_Atk_effect->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s
	//�G�U���G�t�F�N�g�ǉ�
	if (Enemy_Atk_effect->Add(MY_ANIME_DIR_ENE_ATK, MY_ANIME_NAME_ENE_ATK_KIBA, ENE_ATK_KIBA_ALL_CNT, ENE_ATK_KIBA_YOKO_CNT, ENE_ATK_KIBA_TATE_CNT, ENE_ATK_KIBA_WIDTH, ENE_ATK_KIBA_HEIGHT, ENE_ATK_KIBA_SPEED, false, (int)ENE_ATK_KIBA) == false) { return false; }	//�ǂݍ��ݎ��s
	if (Enemy_Atk_effect->Add(MY_ANIME_DIR_ENE_ATK, MY_ANIME_NAME_ENE_ATK_TAIL_BIG, ENE_ATK_TAIL_BIG_ALL_CNT, ENE_ATK_TAIL_BIG_YOKO_CNT, ENE_ATK_TAIL_BIG_TATE_CNT, ENE_ATK_TAIL_BIG_WIDTH, ENE_ATK_TAIL_BIG_HEIGHT, ENE_ATK_TAIL_BIG_SPEED, false, (int)ENE_ATK_TAIL_BIG) == false) { return false; }	//�ǂݍ��ݎ��s

	//�{�X�U���G�t�F�N�g
	Boss_Atk_effect = new EFFECT(MY_ANIME_DIR_BOSS_ATK, MY_ANIME_NAME_BOSS_ATK_LASER, BOSS_ATK_LEASER_ALL_CNT, BOSS_ATK_LEASER_YOKO_CNT, BOSS_ATK_LEASER_TATE_CNT, BOSS_ATK_LEASER_WIDTH, BOSS_ATK_LEASER_HEIGHT, BOSS_ATK_LEASER_SPEED, false, BOSS_ATK_EFFECT_KIND);
	if (Boss_Atk_effect->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s
	//�{�X�U���G�t�F�N�g�ǉ�
	if (Boss_Atk_effect->Add(MY_ANIME_DIR_BOSS_ATK, MY_ANIME_NAME_BOSS_ATK_TOGE, BOSS_ATK_TOGE_ALL_CNT, BOSS_ATK_TOGE_YOKO_CNT, BOSS_ATK_TOGE_TATE_CNT, BOSS_ATK_TOGE_WIDTH, BOSS_ATK_TOGE_HEIGT, BOSS_ATK_TOGE_SPEED, false, (int)BOSS_ATK_TOGE) == false) { return false; }	//�ǂݍ��ݎ��s


	//�v���C���[�֌W
	player = new PLAYER();		//�v���C���[����
	if (player->SetAnime(MY_ANIME_DIR_PLAYER, MY_ANIME_NAME_PLAYER, PLAYER_ALL_CNT, PLAYER_YOKO_CNT, PLAYER_TATE_CNT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_ANI_SPEED, true) == false) { return false; } //�ǂݍ��ݎ��s

	//�v���C���[�̃f�[�^��csv�t�@�C������ǂݍ���
	if(player->LoadData(PLAYER_DATA_DIR, PLAYER_DATA_NAME) == false) { return false; }	//�ǂݍ��ݎ��s
	//�v���C���[�̏����f�[�^ver
	//if (player->LoadData(PLAYER_DATA_DIR, PLATER_DATA_INIT_NAME) == false) { return false; }	//�ǂݍ��ݎ��s

	//UI�֌W
	ui = new UI();		//UI�쐬

	//���������������������������������������� �G�֌W�������� ����������������������������������������
	enemy[(int)ENE_SLIME] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SLIME);	//�X���C���쐬
	if (enemy[(int)ENE_SLIME]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_BAT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_BAT);	//��������쐬
	if (enemy[(int)ENE_BAT]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_GOBURIN] = new ENEMY(ENEMY_DIR, ENEMY_NAME_GOBURIN);	//�S�u�����쐬
	if (enemy[(int)ENE_GOBURIN]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_MATANGO] = new ENEMY(ENEMY_DIR, ENEMY_NAME_MATANGO);	//�}�^���S�쐬
	if (enemy[(int)ENE_MATANGO]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_SEED] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SEED);	//�����̎�쐬
	if (enemy[(int)ENE_SEED]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_TREANT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_TREANT);	//�g�����g�쐬
	if (enemy[(int)ENE_TREANT]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_YADOKARI] = new ENEMY(ENEMY_DIR, ENEMY_NAME_YADOKARI);	//���h�J���쐬
	if (enemy[(int)ENE_YADOKARI]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_SCORPION] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SCORPION);	//�T�\���쐬
	if (enemy[(int)ENE_SCORPION]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_OCTPUS] = new ENEMY(ENEMY_DIR, ENEMY_NAME_OCTPUS);	//�^�R�쐬
	if (enemy[(int)ENE_OCTPUS]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_COBRA] = new ENEMY(ENEMY_DIR, ENEMY_NAME_COBRA);		//�R�u���쐬
	if (enemy[(int)ENE_COBRA]->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s

	enemy[(int)ENE_PUMPKIN] = new ENEMY(ENEMY_DIR, ENEMY_NAME_PUMPKIN);	//�p���v�L���쐬
	if (enemy[(int)ENE_PUMPKIN]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_PAPILLON] = new ENEMY(ENEMY_DIR, ENEMY_NAME_PAPILLON);	//�p�s�I���쐬
	if (enemy[(int)ENE_PAPILLON]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_HARPY] = new ENEMY(ENEMY_DIR, ENEMY_NAME_HARPY);	//�n�[�s�[�쐬
	if (enemy[(int)ENE_HARPY]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_FLOWER] = new ENEMY(ENEMY_DIR, ENEMY_NAME_FLOWER);	//�f�X�t�����[�쐬
	if (enemy[(int)ENE_FLOWER]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_MANTIS] = new ENEMY(ENEMY_DIR, ENEMY_NAME_MANTIS);	//�}���e�B�X�쐬
	if (enemy[(int)ENE_MANTIS]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_CRYSTAL] = new ENEMY(ENEMY_DIR, ENEMY_NAME_CRYSTAL);	//�N���X�^���쐬
	if (enemy[(int)ENE_CRYSTAL]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_ICICLE] = new ENEMY(ENEMY_DIR, ENEMY_NAME_ICICLE);	//�A�C�V�N���쐬
	if (enemy[(int)ENE_ICICLE]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_SNOWMAN] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SNOWMAN);	//�X�m�[�}���쐬
	if (enemy[(int)ENE_SNOWMAN]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_FARAO] = new ENEMY(ENEMY_DIR, ENEMY_NAME_FARAO);	//�t�@���I�쐬
	if (enemy[(int)ENE_FARAO]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_AKUMA] = new ENEMY(ENEMY_DIR, ENEMY_NAME_AKUMA);	//�f�[�����쐬
	if (enemy[(int)ENE_AKUMA]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_BONEBEAST] = new ENEMY(ENEMY_DIR, ENEMY_NAME_BONEBEAST);	//�{�[���r�[�X�g�쐬
	if (enemy[(int)ENE_BONEBEAST]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_IFRIT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_IFRIT);	//�C�t���[�g�쐬
	if (enemy[(int)ENE_IFRIT]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_GARGOYLE] = new ENEMY(ENEMY_DIR, ENEMY_NAME_GARGOYLE);	//�K�[�S�C���쐬
	if (enemy[(int)ENE_GARGOYLE]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_PROMINENCE] = new ENEMY(ENEMY_DIR, ENEMY_NAME_PROMINENCE);	//�v���~�l���X�쐬
	if (enemy[(int)ENE_PROMINENCE]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_BOSS] = new ENEMY(ENEMY_DIR, ENEMY_NAME_BOSS);	//�{�X�쐬
	if (enemy[(int)ENE_BOSS]->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s


	boss_mapimage = new IMAGE(ENEMY_DIR, ENEMY_NAME_BOSS_MAP);		//�}�b�v�ɕ`�悷��{�X�̉摜�𐶐�
	if (boss_mapimage->GetIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s��

	//�G�̃f�[�^��csv�t�@�C������ǂݍ���
	if (data->LoadEnemy(enemy, ENEMY_DATA_DIR, ENEMY_DATA_NAME) == false) { return false; }		//�ǂݍ��ݎ��s
	//�������������������������������������� �G�֌W�����܂� ��������������������������������������


	//���������������������������������������� �}�b�v�f�[�^�ǂݍ��݊J�n ����������������������������������������
	//�t�B�[���h�}�b�v�ǂݍ���
	mapdata[(int)DRAW_FILED][(int)MAP_SOUGEN] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_SOUGEN);	//�����}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_SOUGEN]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_SOUGEN_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_FOREST] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_FOREST);	//�X�}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_FOREST]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_FOREST_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_OCEAN] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_OCEAN);		//�C�}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_OCEAN]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_OCEAN_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_AUTUMN] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_AUTUMN);	//�H�}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_AUTUMN]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_AUTUMN_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_BOSS] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_BOSS);	//�{�X�}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_BOSS]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_BOSS_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_SPRING] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_SPRING);			//�t�}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_SPRING]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_SPRING_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_WINTER] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_WINTER);			//�~�}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_WINTER]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_WINTER_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_REMAINS] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_REMAINS);					//��Ճ}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_REMAINS]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_REMAINS_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_CASTLE] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_CASTLE);					//������}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_CASTLE]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_CASTLE_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	//�X�}�b�v�ǂݍ���
	mapdata[(int)DRAW_CITY][(int)MAP_CITY_NW] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_NW);	//�k���}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_NW]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_NW_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_W] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_W);	//���}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_W]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_W_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_SW] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_SW);		//�쐼�}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_SW]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_SW_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_N] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_N);	//�k�}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_N]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_N_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_CNETER] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_CENTER);	//�����}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_CNETER]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_CENTER_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_S] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_S);			//��}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_S]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_S_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_NE] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_NE);			//�k���}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_NE]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_NE_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_E] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_E);					//���}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_E]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_E_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_SE] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_SE);					//�쓌�}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_SE]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_SE_ATARI) == false) { return false; }	//�����蔻��ǂݍ��ݎ��s

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

	//���݂̃}�b�v�ʒu��ǂݍ���Őݒ�
	if (data->LoadNowMap(&NowDrawMapKind, MapNowPos, MAPPOS_DATA_DIR, MAPPOS_DATA_NAME) == false) { return false; }	//�ǂݍ��ݎ��s
	//���݂̃}�b�v�ʒu��ǂݍ���Őݒ�(����ver)
	//if (data->LoadNowMap(&NowDrawMapKind, MapNowPos, MAPPOS_DATA_DIR, MAPPOS_INITDATA_NAME) == false) { return false; }	//�ǂݍ��ݎ��s
	//�������������������������������������� �}�b�v�f�[�^�ǂݍ��݂����܂� ��������������������������������������

	//�ꗗ�֌W
	mgc_list = new LIST_MGC(LIST_DIR, MGC_LIST_NAME);		//���@�ꗗ�𐶐�
	if (mgc_list->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	weapon_list = new LIST_WEAPON(LIST_DIR, WEAPON_LIST_NAME);	//����ꗗ�𐶐�
	if (weapon_list->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	armor_list = new LIST_ARMOR(LIST_DIR, ARMOR_LIST_NAME);		//�h��ꗗ�𐶐�
	if (armor_list->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s

	item_list = new LIST_ITEM(LIST_DIR, ITEM_LIST_NAME);		//�A�C�e���ꗗ�𐶐�
	if (item_list->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s


	//�I�����֌W
	Title_select = new SELECT(TITLE_SELECT_START_TEXT, TITLE_SELECT_END_TEXT);	//�^�C�g����ʂ̑I��������
	End_select = new SELECT(END_SELECT_TITLE_TEXT, END_SELECT_END_TEXT);		//�G���h��ʂ̑I��������

	//���@�ꗗ����A�퓬��ʂŎg�p���邽�߂́A���@�̑I�������쐬
	for (int i = 0; i < mgc_list->GetListSize(); ++i)			//���@�̎�ޕ����[�v������
	{
		ui->MgcSelect->AddSelect(std::to_string(mgc_list->GetCost(i)).c_str());//����MP�ݒ�
		ui->MgcSelect->AddText(i, MGC_SELECT_MP_TEXT);							//������ǉ�
		ui->MgcSelect->AddText(i, mgc_list->GetName(i));						//���@���ݒ�
	}

	//NPC�֌W
	npc = new NPC(NPC_IMAGE_DIR, NPC_IMAGE_DATA_NAME);						//NPC�𐶐�
	if (npc->GetImageIsLoad() == false) { return false; }					//�ǂݍ��ݎ��s
	if (npc->Load(NPC_DATA_DIR, NPC_DATA_NAME) == false) { return false; }	//NPC�f�[�^�ǂݍ���

	return true;		//�S�Ă̓ǂݍ��݂ɐ���

}

//�Q�[���̏����ݒ���s������
void SetGameInit()
{

	SetSize();		//�Q�[�����Ŏg�p����摜�Ȃǂ̃T�C�Y��ݒ�

	player->SetWeaponAtk(weapon_list);		//����U���͐ݒ�
	player->SetArmorDef(armor_list);		//�h��h��͐ݒ�
	player->SetItemRecovery(item_list);		//�񕜗ʐݒ�

	//******************** �����ݒ肱������ ***************************
	player->SetInit();	//�v���C���[�̏����ݒ�

	//�G�̏����ݒ�
	for (int i = 0; i < ENEMY_KIND; ++i)		//�G�̐����������ݒ�
	{
		enemy[i]->SetInit();					//�����ݒ�
		enemy[i]->StateSetInit();				//�X�e�[�^�X�����ݒ�
	}

	ui->Init();		//UI�֌W������
	//******************** �����ݒ肱���܂� ***************************

	ui->SelectUpdate(player->GetWeaponClass(), weapon_list);	//����̑I�����X�V
	ui->SelectUpdate(player->GetArmorClass(), armor_list);		//�h��̑I�����X�V
	ui->SelectUpdate(player->GetItemClass(), item_list);		//�A�C�e���̑I�����X�V

	return;

}

//�Q�[���Ŏg�p����摜�Ȃǂ̃T�C�Y��ݒ肷�鏈��
void SetSize()
{
	//�摜�֌W
	title->SetSize();			//�^�C�g���摜�̃T�C�Y�ݒ�
	back->SetSize();			//�w�i�摜�̃T�C�Y�ݒ�
	back_battle->SetSize();		//�퓬��ʂ̉摜�T�C�Y�ݒ�
	description->SetSize();			//�����摜�̃T�C�Y�ݒ�
	boss_mapimage->SetSize();	//�{�X�̃}�b�v�ł̉摜�T�C�Y�ݒ�

	//UI�֌W
	ui->SetSize();				//UI�摜�̃T�C�Y�ݒ�

	//�I�����֌W
	Title_select->SetSize();	//�I�����̉摜�T�C�Y�ݒ�
	
	//�G�t�F�N�g�֌W
	Magic_effect->SetSize();	//���@�G�t�F�N�g�̃T�C�Y�ݒ�
	Atack_effect->SetSize();	//�U���G�t�F�N�g�̃T�C�Y�ݒ�
	Enemy_Atk_effect->SetSize();//�G�U���G�t�F�N�g�̃T�C�Y�ݒ�
	Boss_Atk_effect->SetSize();	//�{�X�U���G�t�F�N�g�̃T�C�Y�ݒ�

	return;

}

//�������[�v���̃Q�[������
/*
�߂�l�Ftrue�F����
�߂�l�Ffalse�F�G���[�A�����I��
*/
bool GameMainLoop()
{
	if (ProcessMessage() != 0) { return false; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��

	if (ClearDrawScreen() != 0) { return false; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

	keydown->KeyDownUpdate();	//�L�[�̓��͏�Ԃ��X�V����

	fps->Update();				//FPS�̏���[�X�V]

	if (IsLoad == false)		//�ǂݍ��݂��I�����Ă��Ȃ����
	{
		Load();					//���[�h��ʂ̏���
	}
	else						//�ǂݍ��݂��I�����Ă����
	{
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

	}

	if (GameEnd_Flg)		//�Q�[���I���t���O�������Ă�����
	{
		return false;				//���[�v�𔲂��A�Q�[���I��
	}


	ScreenFlip();				//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

	fps->Wait();				//FPS�̏���[�҂�]

	return true;				//����

}

//************************ �퓬��ʂ̊e���� *****************************
//�퓬��ʍs���҂���Ԃ̏���
void Bt_WaitAct()
{
	if (Turn == (int)MY_TURN)		//�����̃^�[����������
	{
		bt_msg[(int)BT_MSG_ACT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//���b�Z�[�W�`��

		if (bt_msg[(int)BT_MSG_ACT]->GetIsLastMsg())	//�Ō�̃��b�Z�[�W��������
		{

			//1�^�[����1�񂾂��s������
			if (TotalTurnCnt < NowTurnCnt)	//�^�[�����n�܂��čŏ��̏�����������
			{
				if (player->AddBP())	//BP�𑝂₹����
				{
					bt_se->Play((int)BT_SE_BP_CHARGE);	//�`���[�W����炷
				}
				++TotalTurnCnt;		//�����̃^�[���������Z����
			}

			ui->SetIsDrawUIAnime(false);		//UI�̃A�j���[�V������\��

			if (!ui->BattleCommand->GetSelectFlg())	//�R�}���h��I�����Ă��Ȃ��Ƃ���
			{
				ui->BattleCommand->SelectOperation(keydown, sys_se);	//�o�g���R�}���h�L�[����

				if (keydown->IsKeyDownOne(KEY_INPUT_SPACE))	//�X�y�[�X�L�[�������ꂽ��
				{
					if (player->PlusUseBP())	//�g�p����BP�𑝂₹����
					{
						bt_se->Play((int)BT_SE_BP_PLUS);	//�g�p����BP�����̉���炷
					}
				}
				else if (keydown->IsKeyDownOne(KEY_INPUT_LSHIFT))	//���V�t�g�L�[�������ꂽ��
				{
					if (player->MinusUseBP())	//�g�p����BP�����点����
					{
						bt_se->Play((int)BT_SE_BP_MINUS);	//�g�p����BP�����̉���炷
					}
				}

			}

		}
		else				//���b�Z�[�W���c���Ă����
		{
			if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
			{
				sys_se->Play((int)SYS_SE_KETTEI);				//���艹��炷

				bt_msg[(int)BT_MSG_ACT]->NextMsg();				//���̃��b�Z�[�W��
			}
		}


		if (ui->BattleCommand->GetSelectFlg())	//�R�}���h��I��������
		{
			//�������������������������������������� �o�g���R�}���h���̏����������� ��������������������������������������
			switch (ui->BattleCommand->GetSelectNum())		//�ǂ̃R�}���h��I�񂾂�
			{
			case (int)COMMANDE_ATACK:					//�U����I�񂾎�

				BattleStageNow = (int)DAMEGE_CALC;	//�o�g����Ԃ��_���[�W�v�Z��Ԃ�

				break;

			case (int)COMMANDE_DEFENSE:		//�h���I�񂾎�

				BattleStageNow = (int)DAMEGE_CALC;	//�o�g����Ԃ��_���[�W�v�Z��Ԃ�

				break;

			case (int)COMMANDE_MAGIC:		//���@��I�񂾎�

				ui->DrawWindow(BT_LIST_WIN_X, BT_LIST_WIN_Y, GAME_WIDTH - BT_LIST_WIN_X, BT_LIST_WIN_HEIGHT);	//�E�B���h�E�`��
				ui->MgcSelect->Draw(BT_LIST_TXT_X, BT_LIST_TXT_Y);	//���@�ꗗ��`��

				ui->MgcSelect->SelectOperation(keydown, sys_se);	//���@�ꗗ�̃L�[����

				if (ui->MgcSelect->GetBackFlg())	//�߂�I����������
				{
					ui->BattleCommand->SetSelectFlg(false);	//�I�����ĂȂ�
					ui->MgcSelect->SetBackFlg(false);		//�߂�I�����Z�b�g
					ui->MgcSelect->NowSelectReset();		//���݂̑I�����Z�b�g
				}
				else if (ui->MgcSelect->GetSelectFlg())	//�I�����ꂽ����
				{
					//�I�񂾖��@�̏���MP���c���Ă���MP��葽��������(���@���g���Ȃ�����)
					if (player->GetMP() < mgc_list->GetCost(ui->MgcSelect->GetSelectNum()))
					{
						sys_se->Play((int)SYS_SE_BLIP);			//�I���ł��Ȃ����̉���炷
					}
					else		//�I�񂾖��@���g��������
					{
						player->SetChoiseSkil(ui->MgcSelect->GetSelectNum());	//�I���������e���g�p���閂�@�Ƃ��Đݒ肷��
						ui->MgcSelect->NowSelectReset();						//�I��v�f��擪�ɖ߂�
						ui->MgcSelect->SetSelectFlg(false);						//�I�����ĂȂ���Ԃ�
						BattleStageNow = (int)DAMEGE_CALC;	//�o�g����Ԃ��_���[�W�v�Z��Ԃ�
					}

				}

				break;

			case (int)COMMANDE_ITEM:			//�A�C�e����I�񂾎�

				ui->SelectUpdate(player->GetItemClass(), item_list);	//�I�����X�V

				ui->DrawWindow(BT_LIST_WIN_X, BT_LIST_WIN_Y, GAME_WIDTH - BT_LIST_WIN_X, BT_LIST_WIN_HEIGHT);	//�E�B���h�E�`��

				if (ui->ItemSelect->GetSelectKind() != 0)	//�A�C�e���������Ă�����
				{

					ui->DrawItemSelect(BT_LIST_TXT_X, BT_LIST_TXT_Y, player->GetItemClass());	//�����Ă���A�C�e����`��

					ui->ItemSelect->SelectOperation(keydown, sys_se);	//�A�C�e���I�����L�[����

					if (ui->ItemSelect->GetSelectFlg())	//�A�C�e����I��������
					{

						if (player->UseItem(ui->ItemSelect->GetSelectCode()))	//�A�C�e�����g�p�o������
						{
							bt_se->Play((int)BT_SE_RECOVERY);					//�񕜉���炷

							//�A�C�e���ɂ�BP���g�p�ł��Ȃ����߁A�g��BP�����Z�b�g����
							player->ResetUseBP();

							BattleStageNow = (int)DAMEGE_CALC;	//�o�g����Ԃ��_���[�W�v�Z��Ԃ�

						}
						else		//�g�p�ł��Ȃ�������
						{
							sys_se->Play((int)SYS_SE_BLIP);			//�g�p�ł��Ȃ�����炷
							ui->ItemSelect->SetSelectFlg(false);	//�I�����Ă��Ȃ���Ԃ�
						}
					}

					if (ui->ItemSelect->GetBackFlg())	//�߂�I����������
					{
						ui->BattleCommand->SetSelectFlg(false);	//�I�����Ă��Ȃ�
						ui->ItemSelect->SetBackFlg(false);		//�߂�I�����Z�b�g
						ui->ItemSelect->NowSelectReset();		//���݂̑I�����Z�b�g
					}

				}
				else		//�A�C�e���������Ă��Ȃ�������
				{
					if (keydown->IsKeyDownOne(KEY_INPUT_BACK))	//�o�b�N�X�y�[�X�L�[�������ꂽ��
					{
						ui->BattleCommand->SetSelectFlg(false);	//�R�}���h��I�����Ă��Ȃ�
					}
				}

				break;

			case (int)COMMANDE_ESCAPE:		//�������I�񂾎�

				bt_msg[(int)BT_MSG_ACT]->SetMsg(BT_ESCAPE_TEXT);	//������ݒ�

				BattleStageNow = (int)ACT_MSG;	//���b�Z�[�W�`����

				break;

			default:
				break;
			}
			//�������������������������������������� �o�g���R�}���h���̏��������܂� ��������������������������������������

		}

	}
	else if (Turn = (int)ENEMY_TURN)	//�G�̃^�[����������
	{
		//�G�̍s���I�����菈��
		enemy[EncounteEnemyType]->ActDecision();		//�s�����菈��

		BattleStageNow = (int)DAMEGE_CALC;	//�_���[�W�v�Z��

	}

	return;


}

//�퓬��ʃ_���[�W�v�Z��Ԃ̏���
void Bt_DamegeCalc()
{
	if (Turn == (int)MY_TURN)		//�����̃^�[����������
	{
		player->DamegeCalc(enemy[EncounteEnemyType], ui->BattleCommand->GetSelectNum());		//�_���[�W�v�Z

		//�������������������������������� ���b�Z�[�W�ݒ菈���������� ��������������������������������������

		ui->SetIsDrawUIAnime(true);			//UI�̃A�j���[�V�����\��

		//����
		if (ui->BattleCommand->GetSelectNum() == (int)COMMANDE_DEFENSE)	//�h���I�񂾎�
		{

			bt_msg[(int)BT_MSG_ACT]->SetMsg(player->GetName());	//���O�ݒ�
			bt_msg[(int)BT_MSG_ACT]->AddText(BT_DEF_TEXT_1);	//���b�Z�[�W���e�ǉ�
			bt_msg[(int)BT_MSG_ACT]->AddMsg(BT_DEF_TEXT_2);		//���b�Z�[�W�ǉ�

		}
		else if (ui->BattleCommand->GetSelectNum() == (int)COMMANDE_ITEM)	//�A�C�e����I�񂾎�
		{
			bt_msg[(int)BT_MSG_ACT]->SetMsg(item_list->GetName(ui->ItemSelect->GetSelectCode()));	//�g�p�����A�C�e�����ݒ�
			bt_msg[(int)BT_MSG_ACT]->AddText(BT_ITEM_TEXT_1);		//���b�Z�[�W���e�ǉ�
			if (item_list->GetItemType(ui->ItemSelect->GetSelectCode()) == ITEM_TYPE_HP)	//HP�񕜃A�C�e����������
			{
				bt_msg[(int)BT_MSG_ACT]->AddMsg(BT_ITEM_TEXT_HP);				//���b�Z�[�W�ǉ�
			}
			else if (item_list->GetItemType(ui->ItemSelect->GetSelectCode()) == ITEM_TYPE_MP)	//MP�񕜃A�C�e����������
			{
				bt_msg[(int)BT_MSG_ACT]->AddMsg(BT_ITEM_TEXT_MP);				//���b�Z�[�W�ǉ�
			}
			bt_msg[(int)BT_MSG_ACT]->AddText(std::to_string(item_list->GetRecovery(ui->ItemSelect->GetSelectCode())).c_str());	//�񕜗ʐݒ�
			bt_msg[(int)BT_MSG_ACT]->AddText(BT_ITEM_TEXT_2);	//���b�Z�[�W���e�ǉ�

			ui->ItemSelect->NowSelectReset();					//�A�C�e���̑I�������Z�b�g
			ui->ItemSelect->SetSelectFlg(false);				//�I�����Ă��Ȃ���Ԃ�

		}
		else					//����ȊO�̎�
		{
			bt_msg[(int)BT_MSG_ACT]->SetMsg(player->GetName());	//���O�ݒ�
			bt_msg[(int)BT_MSG_ACT]->AddText(BT_ATK_TEXT);		//���b�Z�[�W���e�ǉ�
			bt_msg[(int)BT_MSG_ACT]->AddMsg(std::to_string(enemy[EncounteEnemyType]->GetRecvDamege()).c_str());	//�^�����_���[�W�ݒ�
			bt_msg[(int)BT_MSG_ACT]->AddText(BT_ATK_SEND_TEXT);	//���b�Z�[�W���e�ǉ�
		}

		//�G
		bt_msg[(int)BT_MSG_ACT]->AddMsg(enemy[EncounteEnemyType]->GetName());	//�G�̖��O�ݒ�
		bt_msg[(int)BT_MSG_ACT]->AddText(BT_ATK_TEXT);		//���b�Z�[�W���e�ǉ�
		bt_msg[(int)BT_MSG_ACT]->AddMsg(std::to_string(player->GetRecvDamege()).c_str());	//�󂯂�_���[�W�ݒ�
		bt_msg[(int)BT_MSG_ACT]->AddText(BT_ATK_RECV_TEXT);	//���b�Z�[�W���e�ǉ�
		//�������������������������������� ���b�Z�[�W�ݒ菈�������܂� ��������������������������������������

		BattleStageNow = (int)ACT_MSG;	//�s�����b�Z�[�W�\����Ԃ�

	}
	else if (Turn = (int)ENEMY_TURN)	//�G�̃^�[����������
	{
		//�_���[�W�v�Z
		BattleStageNow = (int)ACT_MSG;	//�s�����b�Z�[�W�\����

	}

	return;

}

//�퓬��ʍs�����b�Z�[�W�`���Ԃ̏���
void Bt_ActMsg()
{
	bt_msg[(int)BT_MSG_ACT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//���b�Z�[�W�`��

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
	{

		sys_se->Play((int)SYS_SE_KETTEI);	//���艹��炷

		if (Turn == (int)MY_TURN)		//�����̃^�[����������
		{
			if (ui->BattleCommand->GetSelectNum() == (int)COMMANDE_ESCAPE)		//�������I�񂾂�
			{
				bt_se->Play((int)BT_SE_NIGERU);	//������Ƃ��̉���炷
				bt_se->Reset();					//�Đ���ԃ��Z�b�g
				SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//���̉�ʂ̓v���C���
			}
		}

		bt_msg[(int)BT_MSG_ACT]->NextMsg();	//���̃��b�Z�[�W��
		BattleStageNow = (int)DRAW_EFFECT;	//�G�t�F�N�g�\����Ԃ�
	}

	return;

}

//�퓬��ʃG�t�F�N�g�`���Ԃ̏���
void Bt_DrawEffect()
{
	if (Turn == (int)MY_TURN)		//�����̃^�[����������
	{
		if (ui->BattleCommand->GetSelectNum() == (int)COMMANDE_ATACK)	//�U����I��ł�����
		{
			//�t�F�[�h�A�E�g�Ȃ��ŕ`��
			Atack_effect->DrawNormal(ATK_DRAW_X, ATK_DRAW_Y, (int)NOMAL_ATACK);	//�U���G�t�F�N�g�`��

			if (bt_se->GetIsPlayed((int)BT_SE_SLASH) == false)		//�Đ��ς݂łȂ����
			{
				if (bt_se->GetIsPlay((int)BT_SE_SLASH) == false)		//�Đ�������Ȃ����
				{
					bt_se->Play((int)BT_SE_SLASH);						//�a��Ƃ���SE��炷
					bt_se->SetIsPlayed((int)BT_SE_SLASH, true);			//�Đ��ς�
				}

			}

			if (Atack_effect->GetIsDrawEnd())	//�U���G�t�F�N�g�̕`�悪�I�������
			{
				enemy[EncounteEnemyType]->DamegeSend();			//�_���[�W��^����
				Atack_effect->ResetIsAnime((int)NOMAL_ATACK);	//�U���G�t�F�N�g���Z�b�g
				BattleStageNow = (int)DRAW_DAMEGE;				//�_���[�W�`���Ԃ�
			}

		}
		else if (ui->BattleCommand->GetSelectNum() == (int)COMMANDE_MAGIC)	//���@��I��ł�����
		{
			//�t�F�[�h�A�E�g�Ȃ��ŕ`��
			Magic_effect->DrawNormal((GAME_WIDTH / 2 - MAGIC_WIDTH / 2), (GAME_HEIGHT / 2 - MAGIC_HEIGHT / 2), player->GetChoiseSkil());	//���@�G�t�F�N�g�`��

			if (bt_se->GetIsPlayed((int)BT_SE_THUNDER) == false)		//�Đ��ς݂łȂ����
			{
				if (bt_se->GetIsPlay((int)BT_SE_THUNDER) == false)		//�Đ�������Ȃ����
				{
					bt_se->Play((int)BT_SE_THUNDER);						//����SE��炷
					bt_se->SetIsPlayed((int)BT_SE_THUNDER, true);			//�Đ��ς�
				}

			}

			if (Magic_effect->GetIsDrawEnd())	//���@�G�t�F�N�g�̕`�悪�I�������
			{
				player->SetMP(player->GetMP() - mgc_list->GetCost(player->GetChoiseSkil()));	//�g�������@�ɉ�����MP�����炷
				Magic_effect->ResetIsAnime(player->GetChoiseSkil());							//���@�G�t�F�N�g���Z�b�g

				enemy[EncounteEnemyType]->DamegeSend();	//�_���[�W��^����
				BattleStageNow = (int)DRAW_DAMEGE;		//�_���[�W�`���Ԃ�
			}

		}
		else		//�G�t�F�N�g�`��̂Ȃ��R�}���h��I��ł�����(�h��A�A�C�e��)
		{
			enemy[EncounteEnemyType]->DamegeSend();	//�_���[�W��^����
			BattleStageNow = (int)DRAW_DAMEGE;		//�_���[�W�`���Ԃ�
		}

	}
	else if (Turn = (int)ENEMY_TURN)	//�G�̃^�[����������
	{

		if (Boss_flg)		//�{�X�킾������
		{
			//�{�X�̃G�t�F�N�g�`��
			Boss_Atk_effect->DrawNormal((GAME_WIDTH / 2 - Boss_Atk_effect->GetWidth(enemy[EncounteEnemyType]->GetChoiseSkil()) / 2),
				(GAME_HEIGHT / 2 - Boss_Atk_effect->GetHeight(enemy[EncounteEnemyType]->GetChoiseSkil()) / 2),
				enemy[EncounteEnemyType]->GetChoiseSkil());

		}
		else	//�{�X�킶��Ȃ����
		{
			//�G�̃G�t�F�N�g�\��
			Enemy_Atk_effect->Draw((GAME_WIDTH / 2 - Enemy_Atk_effect->GetWidth(enemy[EncounteEnemyType]->GetChoiseSkil()) / 2),
				(GAME_HEIGHT / 2 - Enemy_Atk_effect->GetHeight(enemy[EncounteEnemyType]->GetChoiseSkil()) / 2),
				enemy[EncounteEnemyType]->GetChoiseSkil());

		}

		if (Enemy_Atk_effect->GetIsDrawEnd() || Boss_Atk_effect->GetIsDrawEnd())		//�G�t�F�N�g�`��I��������
		{

			//���̍Đ�
			if (bt_se->GetIsPlayed((int)BT_SE_DAMEGE) == false)		//�Đ��ς݂łȂ����
			{
				if (bt_se->GetIsPlay((int)BT_SE_DAMEGE) == false)		//�Đ�������Ȃ����
				{
					bt_se->Play((int)BT_SE_DAMEGE);						//�_���[�W��SE��炷
					bt_se->SetIsPlayed((int)BT_SE_DAMEGE, true);		//�Đ��ς�
				}

			}

			//*************** �G�t�F�N�g���Z�b�g���� **************
			Enemy_Atk_effect->ResetIsAnime(enemy[EncounteEnemyType]->GetChoiseSkil());		//�G�t�F�N�g���Z�b�g
			Boss_Atk_effect->ResetIsAnime(enemy[EncounteEnemyType]->GetChoiseSkil());		//�G�t�F�N�g���Z�b�g�i�{�X�j

			player->DamegeSend();	//�v���C���[�Ƀ_���[�W��^����

			BattleStageNow = (int)DRAW_DAMEGE;	//�_���[�W�`���Ԃ�

		}

	}

	return;

}

//�퓬��ʃ_���[�W�`���Ԃ̏���
void Bt_DrawDamege()
{
	//�_���[�W�`��
	bt_msg[(int)BT_MSG_ACT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//���b�Z�[�W�`��

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ��
	{

		sys_se->Play((int)SYS_SE_KETTEI);	//���艹��炷

		bt_se->Reset();	//SE�̍Đ���Ԃ����Z�b�g

		if (Turn == (int)MY_TURN)			//�����̃^�[���̎�
		{
			Turn = (int)ENEMY_TURN;			//�G�̃^�[����
		}
		else if (Turn == (int)ENEMY_TURN)	//�G�̃^�[���̎�
		{

			bt_msg[(int)BT_MSG_ACT]->SetMsg(BT_WAIT_ACT_TEXT);	//������ݒ�

			++NowTurnCnt;			//�^�[�������Z����
			Turn = (int)MY_TURN;	//�����̃^�[����
		}

		if (player->GetIsArive()==false)	//���������S���Ă�����
		{
			player->SetIsBattleWin(false);	//�퓬�ɔs�k

			bt_msg[(int)BT_MSG_RESULT]->SetMsg(BT_LOSE_TEXT);	//���U���g���b�Z�[�W�ݒ�

			BattleStageNow = (int)RESULT_MSG;		//���U���g���b�Z�[�W�\����Ԃ�

		}
		else if (enemy[EncounteEnemyType]->GetIsArive()==false)	//�G��HP��0�ɂȂ�����
		{
			player->SetIsBattleWin(true);						//�퓬�ɏ���
			player->AddExp(enemy[EncounteEnemyType]->GetEXP());	//�o���l���Z

			//�h���b�v����
			//�߂�l�́A�h���b�v�������̖��O
			std::string drop_name = JudgeDrop();	

			//������������������������������ ���U���g���b�Z�[�W�ݒ菈���������� ������������������������������������������
			bt_msg[(int)BT_MSG_RESULT]->SetMsg(enemy[EncounteEnemyType]->GetName());	//���O�ݒ�
			bt_msg[(int)BT_MSG_RESULT]->AddText(BT_RESULT_TEXT);						//���b�Z�[�W���e�ǉ�

			bt_msg[(int)BT_MSG_RESULT]->AddMsg(enemy[EncounteEnemyType]->GetName());	//�G�̖��O��ݒ�
			bt_msg[(int)BT_MSG_RESULT]->AddText(BT_DROP_MIDLE_TEXT);					//���b�Z�[�W���e�ǉ�
			bt_msg[(int)BT_MSG_RESULT]->AddText(drop_name.c_str());						//�h���b�v�������̖��O��ݒ�
			bt_msg[(int)BT_MSG_RESULT]->AddText(BT_DROP_AF_TEXT);						//���b�Z�[�W���e�ǉ�

			bt_msg[(int)BT_MSG_RESULT]->AddMsg(drop_name.c_str());	//�h���b�v�������̖��O��ݒ�
			bt_msg[(int)BT_MSG_RESULT]->AddText(BT_DROP_GET_TEXT);	//���b�Z�[�W���e�ǉ�

			bt_msg[(int)BT_MSG_RESULT]->AddMsg(std::to_string(enemy[EncounteEnemyType]->GetEXP()).c_str());	//�o���l�ݒ�
			bt_msg[(int)BT_MSG_RESULT]->AddText(BT_RESULT_GET_EXP_TEXT);				//���b�Z�[�W���e�ǉ�

			if (player->GetLevelUpFlg())		//���x���A�b�v�����Ƃ���
			{
				bt_msg[(int)BT_MSG_RESULT]->AddMsg(BT_LEVELUP_BF_TEXT);		//���b�Z�[�W���e�ǉ�
				bt_msg[(int)BT_MSG_RESULT]->AddText(std::to_string(player->GetLevel()).c_str());	//���x���ݒ�
				bt_msg[(int)BT_MSG_RESULT]->AddText(BT_LEVELUP_AF_TEXT);	//���b�Z�[�W���e�ǉ�
			}
			//������������������������������ ���U���g���b�Z�[�W�ݒ菈�������܂� ������������������������������������������

			BattleStageNow = (int)RESULT_MSG;		//���U���g���b�Z�[�W�\����Ԃ�

		}
		else	//�G�A�����Ƃ��Ɏ��S���Ă��Ȃ�������
		{
			BattleStageNow = (int)WAIT_ACT;		//�s���I����Ԃ�
		}

		bt_msg[(int)BT_MSG_ACT]->NextMsg();	//���̃��b�Z�[�W��

		ui->BattleInit();				//�o�g���R�}���h���Z�b�g

	}

	return;

}

//�퓬��ʃ��U���g���b�Z�[�W�`���Ԃ̏���
void Bt_ResultMsg()
{
	bt_msg[(int)BT_MSG_RESULT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//���b�Z�[�W�`��

	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ�Ƃ�
	{

		sys_se->Play((int)SYS_SE_KETTEI);	//���艹��炷

		bt_msg[(int)BT_MSG_RESULT]->NextMsg();	//���̃��b�Z�[�W��

		if (bt_msg[(int)BT_MSG_RESULT]->GetIsLastMsg())		//�Ō�̃��b�Z�[�W��������
		{
			if (player->GetLevelUpFlg())			//���x���A�b�v���Ă�����
			{
				if (bt_se->GetIsPlay((int)BT_SE_LEVELUP) == false)		//�Đ�������Ȃ����
				{
					bt_se->Play((int)BT_SE_LEVELUP);	//���x���A�b�v��SE��炷
					bt_se->SetIsPlayed((int)BT_SE_SLASH, true);			//�Đ��ς�
					player->SetLevelUpFlg(false);	//���x���A�b�v�I��
				}
			}

			if (bt_msg[(int)BT_MSG_RESULT]->GetIsMsgEnd())	//�S�Ẵ��b�Z�[�W�`�悪�I��������
			{
				if (player->GetIsBattleWin())		//�퓬�ɏ������Ă�����
				{
					if (Boss_flg)					//�|�����̂��{�X��������
					{
						Clear_flg = true;			//�N���A�t���O�𗧂Ă�
						SceneChenge(GameSceneNow, (int)GAME_SCENE_END);	//���̉�ʂ̓G���h���
					}
					else							//�|�����̂��{�X�ȊO��������
					{
						SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//���̉�ʂ̓v���C���
					}
				}
				else if (player->GetIsBattleWin() == false)	//�퓬�ɔs�k���Ă�����
				{
					SceneChenge(GameSceneNow, (int)GAME_SCENE_END);	//���̉�ʂ̓G���h���
				}

				BattleStageNow = (int)WAIT_ACT;		//�s���I��҂���Ԃ�

			}

		}

	}

	return;

}

//�h���b�v�������̎�ނ𔻕ʂ���
//�߂�l�F�h���b�v�������̖��O
const char * JudgeDrop()
{
	int drop_code = enemy[EncounteEnemyType]->Drop();	//�h���b�v���������A�h���b�v�������̂̃R�[�h�ԍ����擾����

	/*
	�h���b�v������̂ɂ́A�R�[�h�ԍ������Ă���
	��ނɂ���ăR�[�h�ԍ����قȂ�
	0�ԑ�@(0�`99)�@�@�F�A�C�e��
	100�ԑ�(100�`199) �F����
	200�ԑ�(200�`299) �F�h��
	�R�[�h�ԍ����A100(DROP_JUDGE_NUM)�Ŋ��������ʂɂ���Ď�ނ𔻕ʂł���
	*/
	switch (drop_code / DROP_JUDGE_NUM)	//�h���b�v�������̃R�[�h�ԍ������ނ𔻒�
	{

	case (int)DROP_TYPE_ITEM:	//�A�C�e���������ꍇ

		player->AddDropItem(drop_code, item_list->GetRecovery(drop_code), item_list->GetItemType(drop_code));	//�A�C�e����ǉ�

		return item_list->GetName(drop_code);	//�h���b�v�����A�C�e���̖��O��Ԃ�

		break;	//�A�C�e���������ꍇ�����܂�

	case (int)DROP_TYPE_WEAPON:	//���킾�����ꍇ

		player->AddDropWeapon(drop_code, weapon_list->GetPower(drop_code));	//�����ǉ�

		return weapon_list->GetName(drop_code);	//�h���b�v��������̖��O��Ԃ�

		break;	//���킾�����ꍇ�����܂�

	case (int)DROP_TYPE_ARMOR:	//�h������ꍇ

		player->AddDropArmor(drop_code, armor_list->GetDefense(drop_code));	//�h���ǉ�

		return armor_list->GetName(drop_code);	//�h���b�v�����h��̖��O��Ԃ�

	default:
		break;
	}

}
