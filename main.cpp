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
#include "LIST.hpp"

//########## �O���[�o���I�u�W�F�N�g ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPS�N���X�̃I�u�W�F�N�g�𐶐�
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWN�N���X�̃I�u�W�F�N�g�𐶐�

IMAGE *title;						//�^�C�g���摜
IMAGE *back;						//�w�i�摜
IMAGE *back_battle;					//�퓬��ʂ̔w�i�摜
IMAGE *setumei;						//�����摜
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
MESSAGE *msg;		//���b�Z�[�W

PLAYER *player;						//��l��

ENEMY *enemy[ENEMY_KIND];			//�G

ITEM *item[ITEM_KIND];				//�A�C�e��

MAP *mapdata[DRAW_MAP_KIND][MAP_DATA_KIND];		//�}�b�v�f�[�^

//�I�����֌W
SELECT *Title_select;	//�^�C�g����ʂ̑I����
SELECT *End_select;		//�G���h��ʂ̑I����
SELECT *bt_magic_list;	//�X�L���̑I����

//�ꗗ�֌W
LIST *mgc_list;			//���@�ꗗ

//############## �O���[�o���ϐ� ##############
int GameSceneNow = (int)GAME_SCENE_TITLE;	//���݂̃Q�[���V�[��
int GameSceneBefor;							//�O�̃Q�[���V�[��
int GameSceneNext;							//���̃Q�[���V�[��

int BattleStageNow = (int)WAIT_ACT;	//�o�g���V�[���̌��݂̏��
int BattleActMsgCnt = 0;		//�s�����b�Z�[�W�J�E���g
int BattleActMsgCntMax = 60;	//�s�����b�Z�[�W�̕\������

int MapKind[MAP_DATA_TATE_KIND][MAP_DATA_YOKO_KIND];			//�}�b�v�̎��
int MapNowPos[2] = {0};											//���݂̃}�b�v��X�ʒu��Y�ʒu���i�[
int NowDrawMapKind = (int)DRAW_FILED;							//���݂̕`��}�b�v�̎��(�ŏ��̓t�B�[���h�}�b�v)
bool IsChengeDrawMap = false;									//�`�悷��}�b�v�̎�ނ�؂�ւ��邩

int ChengeDrawCount = 0;	//�t�F�[�h�A�E�g�����Ɏg�p

int EncounteEnemyType = 0;	//���������G�̎��
int Turn = (int)MY_TURN;	//�^�[��

bool GameEnd_Flg = false;	//�Q�[���I���t���O
bool Boss_flg = false;		//�{�X�t���O
bool Clear_flg = false;		//�N���A�t���O

std::string Work_Str;		//��Ɨp������

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//�w��̐��l�ŉ�ʂ�\������

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//�^�C�g���o�[����

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//�^�C�g���̕���

	SetWindowIconID(GAME_ICON_ID);								//�Q�[���̃A�C�R���ύX

	if (DxLib_Init() == -1) { return -1; }						//�c�w���C�u��������������

	SetDrawScreen(DX_SCREEN_BACK);								//Draw�n�֐��͗���ʂɕ`��

	//���������������������������������������� �ǂݍ��ݏ��� ��������������������������������������������������

	//�摜�֌W
	title = new IMAGE(MY_IMG_DIR_TITLE, MY_ING_NAME_TITLE);			//�^�C�g���摜�𐶐�
	if (title->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��

	back = new IMAGE(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK_TITLE);			//�w�i�摜�𐶐�
	if (back->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��
	back->AddImage(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK_END, (int)END_BACK);	//�G���h��ʂ̔w�i�摜�ǂݍ���
	if (back->GetIsLoad() == false) { return -1; }							//�ǂݍ��ݎ��s

	back_battle = new IMAGE(MY_IMG_DIR_BATTLE, IMG_NAME_BT_SOUGEN);	//�퓬���(����)�̔w�i�摜�ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_FOREST,(int)BT_BACK_FOREST);		//�퓬��ʁi�X�j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_OCEAN, (int)BT_BACK_OCEAN);		//�퓬��ʁi�C�j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_AUTUMN, (int)BT_BACK_AUTUMN);		//�퓬��ʁi�H�j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_BOSS, (int)BT_BACK_BOSS);			//�퓬��ʁi�{�X�j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_SPRING, (int)BT_BACK_SPRING);		//�퓬��ʁi�t�j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_WINTER, (int)BT_BACK_WINTER);		//�퓬��ʁi�~�j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_REMAINS, (int)BT_BACK_REMAINS);	//�퓬��ʁi��Ձj�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s
	back_battle->AddImage(MY_IMG_DIR_BATTLE, IMG_NAME_BT_CASTLE, (int)BT_BACK_CASTLE);		//�퓬��ʁi��j�̔w�i�摜�̓ǂݍ���
	if (back_battle->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s


	setumei = new IMAGE(MY_IMG_DIR_BACK, SETUMEI_NAME);		//�����摜�̓ǂݍ���
	if (setumei->GetIsLoad() == false) { return -1; }		//�ǂݍ��ݎ��s

	//���֌W
	bgm = new MUSIC(MY_MUSIC_DIR_BGM, MY_BGM_NAME_TITLE,BGM_KIND);		//BGM�𐶐�
	if (bgm->GetIsLoad() == false) { return -1; }						//�ǂݍ��ݎ��s��
	if (bgm->Add(MY_MUSIC_DIR_BGM, MY_BGM_NAME_FIELD, (int)BGM_FIELD) == false) { return -1; }	//�t�B�[���h��BGM�ǉ�
	if (bgm->Add(MY_MUSIC_DIR_BGM, MY_BGM_NAME_CITY, (int)BGM_CITY) == false) { return -1; }	//�X��BGM�ǉ�
	if (bgm->Add(MY_MUSIC_DIR_BGM, MY_BGM_NAME_BATTLE, (int)BGM_BATTLE) == false) { return -1; }//�퓬��ʂ�BGM�ǉ�
	if (bgm->Add(MY_MUSIC_DIR_BGM, MY_BGM_NAME_END, (int)BGM_END) == false) { return -1; }//�G���h��ʂ�BGM�ǉ�

	//�퓬�Ŏg�p����SE
	bt_se = new MUSIC(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_LEVUP, BT_SE_KIND);	//SE�𐶐�
	if (bt_se->GetIsLoad() == false) { return -1; }						//�ǂݍ��ݎ��s��
	bt_se->ChengePlayType(DX_PLAYTYPE_BACK);							//�Đ����@�ύX
	//���̒ǉ�����
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_SLASH, (int)BT_SE_SLASH) == false) { return -1; }	//�a��Ƃ��̉��ǉ�
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_THUNDER, (int)BT_SE_THUNDER) == false) { return -1; }//���̉��ǉ�
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_NIGERU, (int)BT_SE_NIGERU) == false) { return -1; }//������Ƃ��̉��ǉ�
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_DAMEGE, (int)BT_SE_DAMEGE) == false) { return -1; }//�_���[�W���ǉ�

	//�V�X�e���Ŏg�p����SE
	sys_se = new MUSIC(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_CURSOR, SYS_SE_KIND);	//�V�X�e���pSE����
	if (sys_se->GetIsLoad() == false) { return -1; }							//�ǂݍ��ݎ��s
	sys_se->ChengePlayType(DX_PLAYTYPE_BACK);									//�Đ����@�ύX
	//���̒ǉ�����
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_CANSEL, (int)SYS_SE_CANSEL) == false) { return -1; }	//�L�����Z�����ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_KETTEI, (int)SYS_SE_KETTEI) == false) { return -1; }	//���艹�ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_MENU, (int)SYS_SE_MENU) == false) { return -1; }		//���j���[���J�������̉��ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_ENCOUNT, (int)SYS_SE_ENCOUNT) == false) { return -1; }	//�G�Ƒ����������̉��ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_SAVE, (int)SYS_SE_SAVE) == false) { return -1; }	//�Z�[�u�̉��ǉ�
	if (sys_se->Add(MY_MUSIC_DIR_SYS_SE, MY_SE_NAME_BLIP, (int)SYS_SE_BLIP) == false) { return -1; }	//�I���ł��Ȃ��Ƃ��̉��ǉ�


	//�t�H���g�֌W
	font = new FONT(MY_FONT_DIR, MY_FONT_NAME, FONT_NAME);			//�t�H���g�𐶐�
	if (font->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��

	data = new DATA();		//�f�[�^

	//���b�Z�[�W�֌W
	for (int cnt = 0; cnt < BT_MSG_KIND; ++cnt)
	{
		bt_msg[cnt] = new MESSAGE();	//���b�Z�[�W�쐬
	}
	msg = new MESSAGE();	//���b�Z�[�W�쐬
	if (data->LoadMsg(msg, MSG_DATA_DIR, MSG_DATA_NAME) == false) { return -1; }	//���b�Z�[�W�f�[�^�ǂݍ���

	//�G�t�F�N�g�֌W
	//���@�G�t�F�N�g
	Magic_effect = new EFFECT(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC, MAGIC_ALL_CNT, MAGIC_YOKO_CNT, MAGIC_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC_SPEED, false, MAGIC_EFFECT_KIND);
	if (Magic_effect->GetIsLoad() == false) { return -1; }		//�ǂݍ��ݎ��s
	if (Magic_effect->Add(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC2, MAGIC2_ALL_CNT, MAGIC2_YOKO_CNT, MAGIC2_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC_SPEED, false, (int)MAGIC_2) == false) { return -1; }	//�ǂݍ��ݎ��s
	
	//�U���G�t�F�N�g
	Atack_effect = new EFFECT(MY_ANIME_DIR_ATKEFECT, MY_ANIME_NAME_ATKEFECT, ATK_ALL_CNT, ATK_YOKO_CNT, ATK_TATE_CNT, ATK_WIDTH, ATK_HEIGHT, ATK_SPEED, false, ATACK_EFFECT_KIND);
	if (Atack_effect->GetIsLoad() == false) { return -1; }		//�ǂݍ��ݎ��s

	//�G�U���G�t�F�N�g
	Enemy_Atk_effect = new EFFECT(MY_ANIME_DIR_ENE_ATK, MY_ANIME_NAME_ENE_ATK_TUME, ENE_ATK_TUME_ALL_CNT, ENE_ATK_TUME_YOKO_CNT, ENE_ATK_TUME_TATE_CNT, ENE_ATK_TUME_WIDTH, ENE_ATK_TUME_HEIGHT, ENE_ATK_TUME_SPEED, false,ENE_ATK_EFFECT_KIND);
	if (Enemy_Atk_effect->GetIsLoad() == false) { return -1; }		//�ǂݍ��ݎ��s
	//�G�U���G�t�F�N�g�ǉ�
	if (Enemy_Atk_effect->Add(MY_ANIME_DIR_ENE_ATK, MY_ANIME_NAME_ENE_ATK_KIBA, ENE_ATK_KIBA_ALL_CNT, ENE_ATK_KIBA_YOKO_CNT, ENE_ATK_KIBA_TATE_CNT, ENE_ATK_KIBA_WIDTH, ENE_ATK_KIBA_HEIGHT, ENE_ATK_KIBA_SPEED, false, (int)ENE_ATK_KIBA) == false) { return -1; }	//�ǂݍ��ݎ��s
	if (Enemy_Atk_effect->Add(MY_ANIME_DIR_ENE_ATK, MY_ANIME_NAME_ENE_ATK_TAIL_BIG, ENE_ATK_TAIL_BIG_ALL_CNT, ENE_ATK_TAIL_BIG_YOKO_CNT, ENE_ATK_TAIL_BIG_TATE_CNT, ENE_ATK_TAIL_BIG_WIDTH, ENE_ATK_TAIL_BIG_HEIGHT, ENE_ATK_TAIL_BIG_SPEED, false, (int)ENE_ATK_TAIL_BIG) == false) { return -1; }	//�ǂݍ��ݎ��s

	//�{�X�U���G�t�F�N�g
	Boss_Atk_effect = new EFFECT(MY_ANIME_DIR_BOSS_ATK, MY_ANIME_NAME_BOSS_ATK_LASER, BOSS_ATK_LEASER_ALL_CNT, BOSS_ATK_LEASER_YOKO_CNT, BOSS_ATK_LEASER_TATE_CNT, BOSS_ATK_LEASER_WIDTH, BOSS_ATK_LEASER_HEIGHT, BOSS_ATK_LEASER_SPEED, false, BOSS_ATK_EFFECT_KIND);
	if (Boss_Atk_effect->GetIsLoad() == false) { return -1; }		//�ǂݍ��ݎ��s
	//�{�X�U���G�t�F�N�g�ǉ�
	if (Boss_Atk_effect->Add(MY_ANIME_DIR_BOSS_ATK, MY_ANIME_NAME_BOSS_ATK_TOGE, BOSS_ATK_TOGE_ALL_CNT, BOSS_ATK_TOGE_YOKO_CNT, BOSS_ATK_TOGE_TATE_CNT, BOSS_ATK_TOGE_WIDTH, BOSS_ATK_TOGE_HEIGT, BOSS_ATK_TOGE_SPEED, false, (int)BOSS_ATK_TOGE) == false) { return -1; }	//�ǂݍ��ݎ��s


	//�v���C���[�֌W
	player = new PLAYER();		//�v���C���[����
	if (player->SetImage(MY_IMG_DIR_CHARCTOR, MY_IMG_NAME_PLAYER) == false) { return -1; }	//�ǂݍ��ݎ��s
	if (player->SetAnime(MY_ANIME_DIR_PLAYER, MY_ANIME_NAME_PLAYER, PLAYER_ALL_CNT, PLAYER_YOKO_CNT, PLAYER_TATE_CNT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_ANI_SPEED, true) == false) { return -1; } //�ǂݍ��ݎ��s
	
	//�v���C���[�̃f�[�^��csv�t�@�C������ǂݍ���
	if (data->LoadPlayer(player, PLAYER_DATA_DIR, PLAYER_DATA_NAME) == false) { return -1; }	//�ǂݍ��ݎ��s
	player->SetInit();	//�����ݒ�

	//UI�֌W
	ui = new UI();		//UI�쐬

	//���������������������������������������� �G�֌W�������� ����������������������������������������
	enemy[(int)ENE_SLIME] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SLIME);	//�X���C���쐬
	if (enemy[(int)ENE_SLIME]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_BAT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_BAT);	//��������쐬
	if (enemy[(int)ENE_BAT]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_GOBURIN] = new ENEMY(ENEMY_DIR, ENEMY_NAME_GOBURIN);	//�S�u�����쐬
	if (enemy[(int)ENE_GOBURIN]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_MATANGO] = new ENEMY(ENEMY_DIR, ENEMY_NAME_MATANGO);	//�}�^���S�쐬
	if (enemy[(int)ENE_MATANGO]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_SEED] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SEED);	//�����̎�쐬
	if (enemy[(int)ENE_SEED]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_TREANT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_TREANT);	//�g�����g�쐬
	if (enemy[(int)ENE_TREANT]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_YADOKARI]=new ENEMY(ENEMY_DIR, ENEMY_NAME_YADOKARI);	//���h�J���쐬
	if (enemy[(int)ENE_YADOKARI]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_SCORPION] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SCORPION);	//�T�\���쐬
	if (enemy[(int)ENE_SCORPION]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_OCTPUS] = new ENEMY(ENEMY_DIR, ENEMY_NAME_OCTPUS);	//�^�R�쐬
	if (enemy[(int)ENE_OCTPUS]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_COBRA] = new ENEMY(ENEMY_DIR, ENEMY_NAME_COBRA);		//�R�u���쐬
	if (enemy[(int)ENE_COBRA]->GetIsLoad() == false) { return -1; }		//�ǂݍ��ݎ��s

	enemy[(int)ENE_PUMPKIN] = new ENEMY(ENEMY_DIR, ENEMY_NAME_PUMPKIN);	//�p���v�L���쐬
	if (enemy[(int)ENE_PUMPKIN]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_PAPILLON] = new ENEMY(ENEMY_DIR, ENEMY_NAME_PAPILLON);	//�p�s�I���쐬
	if (enemy[(int)ENE_PAPILLON]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_HARPY] = new ENEMY(ENEMY_DIR, ENEMY_NAME_HARPY);	//�n�[�s�[�쐬
	if (enemy[(int)ENE_HARPY]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_FLOWER] = new ENEMY(ENEMY_DIR, ENEMY_NAME_FLOWER);	//�f�X�t�����[�쐬
	if (enemy[(int)ENE_FLOWER]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_MANTIS] = new ENEMY(ENEMY_DIR, ENEMY_NAME_MANTIS);	//�}���e�B�X�쐬
	if (enemy[(int)ENE_MANTIS]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_CRYSTAL] = new ENEMY(ENEMY_DIR, ENEMY_NAME_CRYSTAL);	//�N���X�^���쐬
	if (enemy[(int)ENE_CRYSTAL]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_ICICLE] = new ENEMY(ENEMY_DIR, ENEMY_NAME_ICICLE);	//�A�C�V�N���쐬
	if (enemy[(int)ENE_ICICLE]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_SNOWMAN] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SNOWMAN);	//�X�m�[�}���쐬
	if (enemy[(int)ENE_SNOWMAN]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_FARAO] = new ENEMY(ENEMY_DIR, ENEMY_NAME_FARAO);	//�t�@���I�쐬
	if (enemy[(int)ENE_FARAO]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_AKUMA] = new ENEMY(ENEMY_DIR, ENEMY_NAME_AKUMA);	//�f�[�����쐬
	if (enemy[(int)ENE_AKUMA]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_BONEBEAST] = new ENEMY(ENEMY_DIR, ENEMY_NAME_BONEBEAST);	//�{�[���r�[�X�g�쐬
	if (enemy[(int)ENE_BONEBEAST]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_IFRIT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_IFRIT);	//�C�t���[�g�쐬
	if (enemy[(int)ENE_IFRIT]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_GARGOYLE] = new ENEMY(ENEMY_DIR, ENEMY_NAME_GARGOYLE);	//�K�[�S�C���쐬
	if (enemy[(int)ENE_GARGOYLE]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_PROMINENCE] = new ENEMY(ENEMY_DIR, ENEMY_NAME_PROMINENCE);	//�v���~�l���X�쐬
	if (enemy[(int)ENE_PROMINENCE]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s

	enemy[(int)ENE_BOSS] = new ENEMY(ENEMY_DIR, ENEMY_NAME_BOSS);	//�{�X�쐬
	if (enemy[(int)ENE_BOSS]->GetIsLoad() == false) { return -1; }	//�ǂݍ��ݎ��s


	boss_mapimage = new IMAGE(ENEMY_DIR, ENEMY_NAME_BOSS_MAP);		//�}�b�v�ɕ`�悷��{�X�̉摜�𐶐�
	if (boss_mapimage->GetIsLoad() == false) { return -1; }					//�ǂݍ��ݎ��s��


	//�G�̃f�[�^��csv�t�@�C������ǂݍ���
	if (data->LoadEnemy(enemy, ENEMY_DATA_DIR, ENEMY_DATA_NAME) == false) { return -1; }		//�ǂݍ��ݎ��s
	//�����ݒ�
	for (int i = 0; i < ENEMY_KIND; ++i)		//�G�̐����������ݒ�
	{
		enemy[i]->StateSetInit();				//�����ݒ�
	}
	//�������������������������������������� �G�֌W�����܂� ��������������������������������������

	//�A�C�e���֌W
	for (int i = 0; i < ITEM_KIND; ++i)	//�A�C�e���̎�ޕ�����
	{
		item[i] = new ITEM();			//�A�C�e���쐬
	}
	//�A�C�e���f�[�^��csv�t�@�C������ǂݍ���
	if (data->LoadItem(item, ITEM_DATA_DIR, ITEM_DATA_NAME) == false) { return -1; }		//�ǂݍ��ݎ��s

	//�}�b�v�֌W
	//���������������������������������������� �}�b�v�f�[�^�ǂݍ��݊J�n ����������������������������������������
	//�t�B�[���h�}�b�v�ǂݍ���
	mapdata[(int)DRAW_FILED][(int)MAP_SOUGEN] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_SOUGEN);	//�����}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_SOUGEN]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_SOUGEN_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_FOREST] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_FOREST);	//�X�}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_FOREST]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_FOREST_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_OCEAN] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_OCEAN);		//�C�}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_OCEAN]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_OCEAN_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_AUTUMN] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_AUTUMN);	//�H�}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_AUTUMN]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_AUTUMN_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_BOSS] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_BOSS);	//�{�X�}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_BOSS]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_BOSS_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_SPRING] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_SPRING);			//�t�}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_SPRING]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_SPRING_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_WINTER] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_WINTER);			//�~�}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_WINTER]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_WINTER_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_REMAINS] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_REMAINS);					//��Ճ}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_REMAINS]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_REMAINS_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_FILED][(int)MAP_CASTLE] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_CASTLE);					//������}�b�v����
	if (mapdata[(int)DRAW_FILED][(int)MAP_CASTLE]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_CASTLE_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	//�X�}�b�v�ǂݍ���
	mapdata[(int)DRAW_CITY][(int)MAP_CITY_NW] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_NW);	//�k���}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_NW]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_NW_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_W] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_W);	//���}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_W]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_W_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_SW] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_SW);		//�쐼�}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_SW]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_SW_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_N] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_N);	//�k�}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_N]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_N_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_CNETER] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_CENTER);	//�����}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_CNETER]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_CENTER_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_S] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_S);			//��}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_S]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_S_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_NE] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_NE);			//�k���}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_NE]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_NE_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_E] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_E);					//���}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_E]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_E_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

	mapdata[(int)DRAW_CITY][(int)MAP_CITY_SE] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_SE);					//�쓌�}�b�v����
	if (mapdata[(int)DRAW_CITY][(int)MAP_CITY_SE]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_SE_ATARI) == false) { return -1; }	//�����蔻��ǂݍ��ݎ��s

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
	if (data->LoadNowMap(&NowDrawMapKind, MapNowPos, MAPPOS_DATA_DIR, MAPPOS_DATA_NAME) == false) { return -1; }	//�ǂݍ��ݎ��s
	//�������������������������������������� �}�b�v�f�[�^�ǂݍ��݂����܂� ��������������������������������������

	//�ꗗ�֌W
	mgc_list = new LIST(LIST_DIR, MGC_LIST_NAME);			//���@�ꗗ�𐶐�
	if (mgc_list->GetIsLoad() == false) { return -1; }		//�ǂݍ��ݎ��s


	//�I�����֌W
	Title_select = new SELECT("START", "END");			//�^�C�g����ʂ̑I��������
	End_select = new SELECT("TITLE", "PLAY", "END");	//�G���h��ʂ̑I��������
	bt_magic_list = new SELECT(mgc_list->GetName((int)MAGIC_1), mgc_list->GetName((int)MAGIC_2));		//�X�L���̑I��������


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

		//fps->Draw(0, 0);			//FPS�̏���[�`��]

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
	if (bgm->GetIsPlay((int)BGM_TITLE) == false)	//�Đ�������Ȃ��Ƃ�
	{
		bgm->Stop();							//�S�Ă�BGM���~�߂�
		bgm->Play((int)BGM_TITLE);				//BGM���Đ�
	}
	//���������������������������� ���̍Đ����������܂� ��������������������������������������


	Title_Draw();		//�^�C�g����ʂ̕`�揈��

	//�I�����̃L�[����
	if (Title_select->SelectOperation(keydown, sys_se))		//�G���^�[�L�[�������ꂽ��
	{
		if (*Title_select->GetNowSelect() == "START")		//�I�����Ă��镶����"START"��������
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//���̉�ʂ̓v���C���
		}
		else
		{
			GameEnd_Flg = true;	//�Q�[���I��
		}

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

	if (player->GetIsMenu() == true && keydown->IsKeyDownOne(KEY_INPUT_Q))		//���j���[�`�撆��Q�L�[�������ꂽ�u��
	{
		sys_se->Play((int)SYS_SE_CANSEL);	//�L�����Z������炷
		sys_se->Reset();				//�Đ���ԃ��Z�b�g
		player->SetIsMenu(false);		//���j���[�`��I��
	}
	else if (keydown->IsKeyDownOne(KEY_INPUT_Q))		//Q�L�[�������ꂽ�u��
	{
		sys_se->Play((int)SYS_SE_MENU);	//���j���[���J������炷
		sys_se->Reset();				//�Đ���ԃ��Z�b�g
		player->SetIsMenu(true);		//���j���[�`��J�n
	}

	//���������������������������������������������� ���j���[���̏����������� ��������������������������������������������������
	if (player->GetIsMenu())			//���j���[�`�撆��������
	{

		//���j���[�E�B���h�E�L�[����
		if (ui->SelectOperation(keydown, sys_se, (int)UI_SELECT_MENU))		//�G���^�[�L�[�������ꂽ�Ƃ�
		{
			ui->SetChoiseMenu(ui->GetNowSelect((int)UI_SELECT_MENU));		//�I���������e���Z�b�g
		}

		if (ui->GetIsChoise())	//�I�����Ă�����
		{
			if (ui->GetChoiseMenu() == (int)MENU_SAVE)	//�Z�[�u��I�񂾎�
			{
				if (Wait())			//�҂����Ԃ��߂�����
				{
					data->Save(player, PLAYER_DATA_DIR, PLAYER_DATA_NAME);		//�v���C���[���̃Z�[�u
					data->SaveMap(NowDrawMapKind, MapNowPos, MAPPOS_DATA_DIR, MAPPOS_DATA_NAME);	//�}�b�v�ʒu�̃Z�[�u
					sys_se->Play((int)SYS_SE_SAVE);		//�Z�[�u����炷
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

		if (Turn == (int)MY_TURN)		//�����̃^�[����������
		{
			bt_msg[(int)BT_MSG_ACT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//���b�Z�[�W�`��
			if (bt_msg[(int)BT_MSG_ACT]->GetIsLastMsg())	//�Ō�̃��b�Z�[�W��������
			{

				ui->SetIsDrawUIAnime(false);		//UI�̃A�j���[�V������\��

				if (ui->GetChoiseCommamd() == COMMAND_NONE)	//�R�}���h��I�����Ă��Ȃ��Ƃ���
				{
					//�o�g���R�}���h�L�[����
					if (ui->SelectOperation(keydown, sys_se, (int)UI_SELECT_BATTLE_CMD))	//�G���^�[�L�[�������ꂽ��
					{
						ui->SetBattleFlg();	//�I�������R�}���h��ݒ�
					}

				}

			}
			else				//���b�Z�[�W���c���Ă����
			{
				if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
				{
					sys_se->Play((int)SYS_SE_KETTEI);	//���艹��炷

					bt_msg[(int)BT_MSG_ACT]->NextMsg();				//���̃��b�Z�[�W��
				}
			}


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

				ui->DrawWindow(MGC_WIN_X, MGC_WIN_Y, GAME_WIDTH - MGC_WIN_X, MGC_WIN_HEIGHT);	//�E�B���h�E�`��
				bt_magic_list->Draw(MGC_TXT_X, MGC_TXT_Y,(int)SELECT_TRIANGLE_MINI);		//���@�ꗗ��`��
				if (bt_magic_list->SelectOperation(keydown, sys_se))		//�G���^�[�L�[�������ꂽ�Ƃ���
				{
					//�I�񂾖��@�̏���MP���c���Ă���MP��葽��������(���@���g���Ȃ�����)
					if (player->GetMP() < mgc_list->GetCost(bt_magic_list->GetSelectNum()))
					{
						sys_se->Play((int)SYS_SE_BLIP);			//�I���ł��Ȃ����̉���炷
					}
					else		//�I�񂾖��@���g��������
					{
						player->SetChoiseSkil(bt_magic_list->GetSelectNum());	//�I���������e���g�p���閂�@�Ƃ��Đݒ肷��
						bt_magic_list->NowSelectReset();						//�I��v�f��擪�ɖ߂�
						BattleStageNow = (int)DAMEGE_CALC;	//�o�g����Ԃ��_���[�W�v�Z��Ԃ�
					}
				}

				break;

			case (int)COMMANDE_ITEM:			//�A�C�e����I�񂾎�

				BattleStageNow = (int)DAMEGE_CALC;	//�o�g����Ԃ��_���[�W�v�Z��Ԃ�

				break;

			case (int)COMMANDE_ESCAPE:		//�������I�񂾎�

				Work_Str = "��肭�����؂ꂽ�I";
				bt_msg[(int)BT_MSG_ACT]->SetMsg(Work_Str.c_str());	//������ݒ�

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
			enemy[EncounteEnemyType]->ActDecision();		//�s�����菈��

			BattleStageNow = (int)DAMEGE_CALC;	//�_���[�W�v�Z��

		}

		break;						//�s���I��҂���Ԃ̏��������܂�

	case (int)DAMEGE_CALC:			//�_���[�W�v�Z��Ԃ̎�

		if (Turn == (int)MY_TURN)		//�����̃^�[����������
		{
			player->DamegeCalc(enemy[EncounteEnemyType],ui->GetChoiseCommamd());		//�_���[�W�v�Z

			//�������������������������������� ���b�Z�[�W�ݒ菈���������� ��������������������������������������

			ui->SetIsDrawUIAnime(true);			//UI�̃A�j���[�V�����\��

			//����
			if (ui->GetChoiseCommamd() == (int)COMMANDE_DEFENSE)	//�h���I�񂾎�
			{
				Work_Str = player->GetName();					//�����̖��O�擾
				Work_Str += "�͖h�䂵�Ă���I";
				bt_msg[(int)BT_MSG_ACT]->SetMsg(Work_Str.c_str());	//������ݒ�
				Work_Str = "�h��ɏW�����Ă���I";
				bt_msg[(int)BT_MSG_ACT]->AddMsg(Work_Str.c_str());	//������ݒ�
			}
			else if (ui->GetChoiseCommamd() == (int)COMMANDE_ITEM)	//�A�C�e����I�񂾎�
			{
				Work_Str = player->GetName();					//�����̖��O�擾
				Work_Str += "�͖򑐂������Ă����I";
				bt_msg[(int)BT_MSG_ACT]->SetMsg(Work_Str.c_str());	//������ݒ�
				Work_Str = "HP��30�񕜂����I";
				bt_msg[(int)BT_MSG_ACT]->AddMsg(Work_Str.c_str());	//������ݒ�

			}
			else					//����ȊO�̎�
			{
				Work_Str = player->GetName();					//�����̖��O�擾
				Work_Str += "�̍U��!";
				bt_msg[(int)BT_MSG_ACT]->SetMsg(Work_Str.c_str());	//������ݒ�
				Work_Str = std::to_string(player->GetSendDamege());	//�^�����_���[�W�擾
				Work_Str += "�̃_���[�W��^����";
				bt_msg[(int)BT_MSG_ACT]->AddMsg(Work_Str.c_str());	//������ݒ�
			}

			//�G
			Work_Str = enemy[EncounteEnemyType]->GetName();	//�G�̖��O�擾
			Work_Str += "�̍U��!";
			bt_msg[(int)BT_MSG_ACT]->AddMsg(Work_Str.c_str());	//������ݒ�
			Work_Str = std::to_string(player->GetRecvDamege());	//�󂯂��_���[�W�擾
			Work_Str += "�̃_���[�W���󂯂�";
			bt_msg[(int)BT_MSG_ACT]->AddMsg(Work_Str.c_str());	//������ݒ�
			//�������������������������������� ���b�Z�[�W�ݒ菈�������܂� ��������������������������������������

			BattleStageNow = (int)ACT_MSG;	//�s�����b�Z�[�W�\����Ԃ�

			ui->NowSelectReset((int)UI_SELECT_BATTLE_CMD);		//�I�����ŏ��̗v�f�֖߂�

		}
		else if (Turn = (int)ENEMY_TURN)	//�G�̃^�[����������
		{
			//�_���[�W�v�Z
			BattleStageNow = (int)ACT_MSG;	//�s�����b�Z�[�W�\����

		}

		break;						//�_���[�W�v�Z��Ԃ̎������܂�

	case (int)ACT_MSG:				//�s�����b�Z�[�W�\�����

		bt_msg[(int)BT_MSG_ACT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//���b�Z�[�W�`��

		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ��
		{

			sys_se->Play((int)SYS_SE_KETTEI);	//���艹��炷

			if (Turn == (int)MY_TURN)		//�����̃^�[����������
			{
				if (ui->GetChoiseCommamd() == (int)COMMANDE_ESCAPE)		//�������I�񂾂�
				{
					bt_se->Play((int)BT_SE_NIGERU);	//������Ƃ��̉���炷
					bt_se->Reset();					//�Đ���ԃ��Z�b�g
					SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//���̉�ʂ̓v���C���
				}
			}

			bt_msg[(int)BT_MSG_ACT]->NextMsg();	//���̃��b�Z�[�W��
			BattleStageNow = (int)DRAW_EFFECT;	//�G�t�F�N�g�\����Ԃ�
		}

		break;						//�s�����b�Z�[�W�\����Ԃ����܂�

	case (int)DRAW_EFFECT:			//�G�t�F�N�g�`����

		if (Turn == (int)MY_TURN)		//�����̃^�[����������
		{
			if (ui->GetChoiseCommamd() == (int)COMMANDE_ATACK)	//�U����I��ł�����
			{
				//�t�F�[�h�A�E�g�Ȃ��ŕ`��
				Atack_effect->DrawNormal(ATK_DRAW_X, ATK_DRAW_Y, (int)NOMAL_ATACK);	//�U���G�t�F�N�g�`��

				if (bt_se->GetIsPlayed((int)BT_SE_SLASH) == false)		//�Đ��ς݂łȂ����
				{
					if (bt_se->GetIsPlay((int)BT_SE_SLASH) == false)		//�Đ�������Ȃ����
					{
						bt_se->Play((int)BT_SE_SLASH);						//�a��Ƃ���SE��炷
						bt_se->SetIsPlayed((int)BT_SE_SLASH,true);			//�Đ��ς�
					}

				}

			}
			else if (ui->GetChoiseCommamd() == (int)COMMANDE_MAGIC)	//���@��I��ł�����
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


			}
			else				//����ȊO��������
			{
				if (ui->GetChoiseCommamd() == (int)COMMANDE_ITEM)		//�A�C�e����I��ł�����
				{
					player->SetHP(player->GetHP()+ ITME_YAKUSOU_RECOVERY_AMOUNT);		//�̗͉�	
				}
				BattleStageNow = (int)DRAW_DAMEGE;		//�_���[�W�`���Ԃ�

				enemy[EncounteEnemyType]->SetHP((enemy[EncounteEnemyType]->GetHP() - player->GetSendDamege()));	//�_���[�W��^����
			}

			if (Magic_effect->GetIsDrawEnd()||Atack_effect->GetIsDrawEnd())		//�G�t�F�N�g�`�悪�I��������
			{

				if (ui->GetChoiseCommamd() == (int)COMMANDE_MAGIC)	//���@��I��ł�����
				{
					player->SetMP(player->GetMP() - mgc_list->GetCost(player->GetChoiseSkil()));		//�g�������@�ɉ�����MP�����炷
				}

				BattleStageNow = (int)DRAW_DAMEGE;		//�_���[�W�`���Ԃ�

				enemy[EncounteEnemyType]->SetHP((enemy[EncounteEnemyType]->GetHP() - player->GetSendDamege()));	//�_���[�W��^����

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
			else				//�{�X�킶��Ȃ����
			{
				//�G�̃G�t�F�N�g�\��
				Enemy_Atk_effect->Draw((GAME_WIDTH / 2 - Enemy_Atk_effect->GetWidth(enemy[EncounteEnemyType]->GetChoiseSkil()) / 2),
					(GAME_HEIGHT / 2 - Enemy_Atk_effect->GetHeight(enemy[EncounteEnemyType]->GetChoiseSkil()) / 2),
					enemy[EncounteEnemyType]->GetChoiseSkil());

			}



			if (Enemy_Atk_effect->GetIsDrawEnd()||Boss_Atk_effect->GetIsDrawEnd())		//�G�t�F�N�g�`��I��������
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

				player->SetHP((player->GetHP()) - (player->GetRecvDamege()));		//�����Ƀ_���[�W��^����

				if (player->GetHP() <= 0)			//HP��0�ȉ��ɂȂ�����
				{
					player->SetHP(0);				//HP��0�ɂ���
				}

				BattleStageNow = (int)DRAW_DAMEGE;	//�_���[�W�`���Ԃ�

			}

		}

		break;

	case (int)DRAW_DAMEGE:				//�_���[�W�`����
		
		//�_���[�W�`��
		bt_msg[(int)BT_MSG_ACT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//���b�Z�[�W�`��

		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ��
		{

			sys_se->Play((int)SYS_SE_KETTEI);	//���艹��炷

			bt_se->Reset();	//SE�̍Đ���Ԃ����Z�b�g

			if (Turn == (int)MY_TURN)			//�����̃^�[���̎�
			{
				if (ui->GetChoiseCommamd() == (int)COMMANDE_ATACK)	//�U����I�񂾎���
				{
					Atack_effect->ResetIsAnime((int)NOMAL_ATACK);		//�U���G�t�F�N�g���Z�b�g
				}
				else							//�U���ȊO��I�񂾎���
				{
					Magic_effect->ResetIsAnime(player->GetChoiseSkil());//���@�G�t�F�N�g���Z�b�g
				}

				Turn = (int)ENEMY_TURN;				//�G�̃^�[����

			}
			else if (Turn == (int)ENEMY_TURN)			//�G�̃^�[���̎�
			{

				Work_Str = "�ǂ�����H";
				bt_msg[(int)BT_MSG_ACT]->SetMsg(Work_Str.c_str());	//������ݒ�

				Enemy_Atk_effect->ResetIsAnime(enemy[EncounteEnemyType]->GetChoiseSkil());		//�G�t�F�N�g���Z�b�g
				Boss_Atk_effect->ResetIsAnime(enemy[EncounteEnemyType]->GetChoiseSkil());		//�G�t�F�N�g���Z�b�g�i�{�X�j
				Turn = (int)MY_TURN;				//�����̃^�[����
			}

			if (player->GetHP() <= 0)			//������HP��0�ɂȂ�����
			{
				player->SetIsArive(false);		//�������S
				player->SetIsBattleWin(false);	//�퓬�ɔs�k

				//������������������������������ ���U���g���b�Z�[�W�ݒ菈���������� ������������������������������������������
				Work_Str = "�S�ł��Ă��܂����c";
				bt_msg[(int)BT_MSG_RESULT]->SetMsg(Work_Str.c_str());	//������ݒ�
				//������������������������������ ���U���g���b�Z�[�W�ݒ菈�������܂� ������������������������������������������

				BattleStageNow = (int)RESULT_MSG;		//���U���g���b�Z�[�W�\����Ԃ�

			}
			else if (enemy[EncounteEnemyType]->GetHP() <= 0)				//�G��HP��0�ɂȂ�����
			{
				enemy[EncounteEnemyType]->SetIsArive(false);		//�G���S
				player->SetIsBattleWin(true);						//�퓬�ɏ���
				player->AddExp(enemy[EncounteEnemyType]->GetEXP());	//�o���l���Z

				//������������������������������ ���U���g���b�Z�[�W�ݒ菈���������� ������������������������������������������
				Work_Str = enemy[EncounteEnemyType]->GetName();
				Work_Str += "��|�����I";
				bt_msg[(int)BT_MSG_RESULT]->SetMsg(Work_Str.c_str());	//������ݒ�
				Work_Str = std::to_string(enemy[EncounteEnemyType]->GetEXP());
				Work_Str += "�̌o���l����ɓ��ꂽ�I";
				bt_msg[(int)BT_MSG_RESULT]->AddMsg(Work_Str.c_str());	//������ݒ�

				if (player->GetLevUpMsgStartFlg())		//���x���A�b�v�����Ƃ���
				{
					Work_Str = "���x��";
					Work_Str += std::to_string(player->GetLevel());	//���x���擾
					Work_Str += "�ɂȂ����I";
					bt_msg[(int)BT_MSG_RESULT]->AddMsg(Work_Str.c_str());	//������ݒ�
				}
				//������������������������������ ���U���g���b�Z�[�W�ݒ菈�������܂� ������������������������������������������

				BattleStageNow = (int)RESULT_MSG;		//���U���g���b�Z�[�W�\����Ԃ�

			}
			else
			{
				BattleStageNow = (int)WAIT_ACT;		//�s���I����Ԃ�
			}

			bt_msg[(int)BT_MSG_ACT]->NextMsg();	//���̃��b�Z�[�W��

			ui->BattleInit();				//�o�g���R�}���h���Z�b�g

		}

		break;

	case (int)RESULT_MSG:		//�퓬�I����̃��b�Z�[�W��`�悷����

		bt_msg[(int)BT_MSG_RESULT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//���b�Z�[�W�`��

		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ�Ƃ�
		{

			sys_se->Play((int)SYS_SE_KETTEI);	//���艹��炷

			bt_msg[(int)BT_MSG_RESULT]->NextMsg();	//���̃��b�Z�[�W��

			if (bt_msg[(int)BT_MSG_RESULT]->GetIsLastMsg())		//�Ō�̃��b�Z�[�W��������
			{
				if (player->GetLevUpMsgStartFlg())			//���x���A�b�v���Ă�����
				{
					if (bt_se->GetIsPlay((int)BT_SE_LEVELUP) == false)		//�Đ�������Ȃ����
					{
						bt_se->Play((int)BT_SE_LEVELUP);	//���x���A�b�v��SE��炷
						bt_se->SetIsPlayed((int)BT_SE_SLASH,true);			//�Đ��ς�
						player->SetLevUpMsgStartFlg(false);	//���x���A�b�v�I��
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

		break;					//�퓬�I����̃��b�Z�[�W��`�悷���Ԃ̏��������܂�

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

	//�I�����̃L�[����
	if (End_select->SelectOperation(keydown, sys_se))		//�G���^�[�L�[�������ꂽ��
	{
		if (*End_select->GetNowSelect() == "TITLE")		//�I�����Ă��镶����"TITLE"��������
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_TITLE);	//���̉�ʂ̓^�C�g�����
		}
		else if (*End_select->GetNowSelect() == "PLAY")	//�v���C��I��������
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//���̉�ʂ̓v���C���
		}
		else
		{
			GameEnd_Flg = true;	//�Q�[���I��
		}

	}

	player->Recovery();		//��

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
		//ui->SelectClear();				//�I�����̓��e���N���A����
	}


	return;

}

//����������
void Init()
{
	ChengeDrawCount = 0;		//�t�F�[�h�C���p������

	if (GameSceneBefor == (int)GAME_SCENE_BATTLE)	//�퓬��ʂ���J�ڂ����ꍇ
	{
		enemy[EncounteEnemyType]->StateSetInit();		//���������G������

		ui->BattleInit();			//�o�g���R�}���h������

		ui->NowSelectReset((int)UI_SELECT_BATTLE_CMD);		//�I�����ŏ��̗v�f�֖߂�

		bt_se->Reset();				//SE�̍Đ���Ԃ����Z�b�g

		EncounteEnemyType = 0;		//���������G�̎�ނ����Z�b�g

		BattleStageNow = (int)WAIT_ACT;	//�o�g����Ԃ��A�s���҂���Ԃ�

		Turn = (int)MY_TURN;		//�^�[���𖡕��̃^�[���ɐݒ�

		for (int i = 0; i < BT_MSG_KIND; ++i)	//���b�Z�[�W�̎�ޕ�
		{
			bt_msg[i]->ResetFlg();		//�t���O���Z�b�g
		}

	}
	else if (GameSceneBefor == (int)GAME_SCENE_END)	//�G���h��ʂ���J�ڂ����ꍇ
	{
		Clear_flg = false;				//�N���A�t���O���Z�b�g
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
	back->Draw(GAME_LEFT, GAME_TOP,(int)TITLE_BACK);	//�w�i�摜�`��

	title->Draw(GAME_LEFT, GAME_HEIGHT / 2 - title->GetHeight(0) / 2);		//��ʒ����Ƀ^�C�g���`��

	font->SetSize(BIG_FONTSIZE);		//�t�H���g�T�C�Y��傫������

	Title_select->DrawCenter(GAME_WIDTH / 2, DEFAULT_TEXT_Y,0);	//�I�����`��
	
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

	player->DrawWalk();		//�v���C���[�`��

	static int Player_X = 0, Player_Y = 0;	//�v���C���[��X�ʒu��Y�ʒu

	player->GetNowPos(&Player_X, &Player_Y);//�v���C���[�̌��݈ʒu���擾

	//�������������������������������������������� ���j���[�`�揈���������� ����������������������������������������
	if (player->GetIsMenu())	//���j���[�`�撆�Ȃ�
	{
		ui->DrawMenu(Player_X,Player_Y);	//���j���[�E�B���h�E�`��

		if (ui->GetIsChoise())	//�I��������
		{

			ui->DrawWindow(GAME_LEFT, GAME_TOP, GAME_WIDTH, GAME_HEIGHT);	//�E�B���h�E�`��

			switch (ui->GetChoiseMenu())		//�I�񂾓��e���Ƃɏ����𕪂���
			{

			case (int)MENU_STATUS:	//�X�e�[�^�X��I�񂾎��̏�����������

				//�X�e�[�^�X�`��
				DrawFormatString(GAME_LEFT, GAME_TOP, GetColor(255, 255, 255), "%s\n�o���l�F%d/%d\nHP %d/%d\nMP %d/%d\nATK %d\nDEF %d\nSPD %d",
					player->GetName(),		//���O
					player->GetEXP(),		//���݂̌o���l
					player->GetMaxEXP(),	//�ő�o���l
					player->GetHP(),		//HP
					player->GetMaxHP(),		//�ő�HP
					player->GetMP(),		//MP
					player->GetMaxMP(),		//�ő�MP
					player->GetATK(),		//�U����
					player->GetDEF(),		//�h���
					player->GetSPD());		//�X�s�[�h

				break;				//�X�e�[�^�X��I�񂾎��̏��������܂�

			case (int)MENU_ITEM:	//�A�C�e����I�񂾎��̏�����������

				//�A�C�e���`�揈��
				for (int cnt = 0; cnt < ITEM_KIND; ++cnt)
				{
					DrawFormatString(GAME_LEFT, cnt * MENU_SPACE, GetColor(255, 255, 255), "%s %s\n", item[cnt]->GetName(), item[cnt]->GetDescription());
				}

				break;				//�A�C�e����I�񂾂Ƃ��̏��������܂�

			case (int)MENU_SOUBI:	//������I�񂾎��̏�����������

				//�����`�揈��
				DrawString(0, 0, "�����`��", GetColor(255, 255, 255));	//�����`��

				break;				//������I�񂾎��̏��������܂�

			case (int)MENU_SETUMEI:	//���������I�񂾎��̏�����������

				//��������`�揈��
				setumei->Draw(GAME_LEFT, GAME_TOP);	//�����摜�̕`��
				if (keydown->IsKeyDownOne(KEY_INPUT_E))	//E�L�[�������ꂽ��
				{
					ui->ResetMenu();	//���j���[���Z�b�g
				}

				break;				//���������I�񂾎��̏��������܂�

			case (int)MENU_SAVE:	//�Z�[�u��I�񂾎��̏�����������

				//�Z�[�u���̕`�揈��
				DrawString(0, 0, "�Z�[�u���ł��B", GetColor(255, 255, 255));	//�����`��

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
		int Strlen = strlen("�Q�[���N���A�I�I�I");
		int Width = GetDrawStringWidth("�Q�[���N���A�I�I�I", Strlen);	//�����擾

		DrawString((GAME_WIDTH / 2) - (Width / 2), GAME_HEIGHT / 2, "�Q�[���N���A�I�I�I", GetColor(255, 0, 0));		//�N���A�����`��
	}
	else				//�N���A���Ă��Ȃ�������
	{
		int Strlen = strlen("�Q�[���I�[�o�[�c");
		int Width = GetDrawStringWidth("�Q�[���I�[�o�[�c", Strlen);	//�����擾

		DrawString((GAME_WIDTH / 2) - (Width / 2), GAME_HEIGHT / 2, "�Q�[���I�[�o�[�c", GetColor(255, 0, 0));		//�Q�[���I�[�o�[�����`��
	}

	font->SetSize(BIG_FONTSIZE);	//�t�H���g�T�C�Y��傫������

	End_select->DrawCenter(GAME_WIDTH / 2, TXT_Y_3, 0,GetColor(0,0,0));		//�I�����`��

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

				//�`�敶���ݒ�
				Work_Str = "�o�C�g�A���";
				Work_Str += enemy[EncounteEnemyType]->GetName();		//���������G�̖��O�擾
				Work_Str += "�����ꂽ�I";
				bt_msg[(int)BT_MSG_ACT]->SetMsg(Work_Str.c_str());	//������ݒ�
				Work_Str = "�ǂ�����H";
				bt_msg[(int)BT_MSG_ACT]->AddMsg(Work_Str.c_str());	//������ݒ�

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
	delete setumei;			//setumei��j��
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

	delete msg;//msg�j��

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

	//�A�C�e���̍폜
	for (int i = 0; i < ITEM_KIND; ++i)	//�A�C�e���̎�ޕ�
	{
		delete item[i];				//item��j��
	}

	return;

}
