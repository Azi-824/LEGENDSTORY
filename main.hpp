/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* main.hpp     																				�@ */
/*       																						�@ */

#pragma once

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########


//########## �}�N����` ##########
#define GAME_LEFT	  0		//��ʂ̉��̎n�_
#define GAME_TOP	  0		//��ʂ̏c�̎n�_
#define GAME_WIDTH	880		//��ʂ̉��̑傫��
#define GAME_HEIGHT	640		//��ʂ̏c�̑傫��
#define GAME_COLOR	32		//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_NAME	"LEGEND STORY"		//�E�B���h�E�̃^�C�g��
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE�F�E�B���h�E���[�h / FALSE�F�t���X�N���[��

#define SET_WINDOW_ST_MODE_DEFAULT			0	//�f�t�H���g
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//�^�C�g���o�[�Ȃ�
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//�^�C�g���o�[�ƃt���[���Ȃ�
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//�t���[���Ȃ�

#define GAME_FPS_SPEED					   60

#define GAME_WAITCNT_MAX				   60	//�҂����Ԃ̃J�E���g�}�b�N�X�l

#define GAME_ICON_ID					   333	//�A�C�R����ID

#define ENCOUNT_TXT_KIND	3

//�e�L�X�g�֌W
#define SAVE_TEXT				"�Z�[�u���ł��B"		//�Z�[�u���̃e�L�X�g
#define GAME_CLEAR_TEXT			"�Q�[���N���A�I"		//�Q�[���N���A���̃e�L�X�g
#define GAME_OVER_TEXT			"�Q�[���I�[�o�[�c"		//�Q�[���I�[�o�[���̃e�L�X�g

#define ENCOUNT_TEXT_1			"�o�C�g�A���"			//�G�ɑ����������̃e�L�X�g1��
#define ENCOUNT_TEXT_2			"�얞�̂�"				//�G�ɑ����������̃e�L�X�g2��
#define ENCOUNT_TEXT_3			"���ʂĂ�"			//�G�ɑ����������̃e�L�X�g3��
#define ENCOUNT_AF_TEXT			"�����ꂽ�I"			//�G�ɑ����������̓G�̖��O�̌��ɂ���e�L�X�g

#define BT_WAIT_ACT_TEXT		"�ǂ�����H"			//�퓬��ʂŃv���C���[�s���҂���Ԃɕ\�������e�L�X�g

#define TITLE_SELECT_START_TEXT	"�X�^�[�g"				//�^�C�g���̑I�����i�Q�[���X�^�[�g�j�̃e�L�X�g
#define TITLE_SELECT_END_TEXT	"�����"				//�^�C�g���̑I�����i�Q�[���I���j�̃e�L�X�g

#define END_SELECT_TITLE_TEXT	"�^�C�g��"				//�G���h��ʂ̑I�����i�^�C�g���֖߂�j�̃e�L�X�g
#define END_SELECT_END_TEXT		"�����"				//�G���h��ʂ̑I�����i�Q�[���I���j�̃e�L�X�g

#define MGC_SELECT_MP_TEXT		"MP:"					//���@�ꗗ�̑I������MP�\���̃e�L�X�g

#define BT_ESCAPE_TEXT			"��肭�����؂ꂽ�I"	//�퓬���ɓ������I�񂾂Ƃ��̃e�L�X�g
#define BT_DEF_TEXT_1			"�͖h�䂵�Ă���I"		//�퓬���ɖh���I�񂾂Ƃ��̃e�L�X�g1��
#define BT_DEF_TEXT_2			"�h��ɏW�����Ă���I"	//�퓬���ɖh���I�񂾂Ƃ��̃e�L�X�g2��
#define BT_ITEM_TEXT_1			"���g�p�����I"			//�퓬���ɃA�C�e����I�񂾂Ƃ��̃e�L�X�g1��
#define BT_ITEM_TEXT_HP			"HP��"					//�퓬���Ɏg�p�����A�C�e����HP�񕜂̂��̂��������̃e�L�X�g
#define BT_ITEM_TEXT_MP			"MP��"					//�퓬���Ɏg�p�����A�C�e����MP�񕜂̂��̂��������̃e�L�X�g
#define BT_ITEM_TEXT_2			"�񕜂����I"			//�퓬���ɃA�C�e����I�񂾂Ƃ��̃e�L�X�g2��
#define BT_ATK_TEXT				"�̍U���I"				//�퓬���̍U���e�L�X�g
#define BT_ATK_RECV_TEXT		"�̃_���[�W���󂯂��I"	//�퓬���Ƀ_���[�W���󂯂��Ƃ��̃e�L�X�g
#define BT_ATK_SEND_TEXT		"�̃_���[�W��^�����I"	//�퓬���Ƀ_���[�W��^�����Ƃ��̃e�L�X�g
#define BT_LOSE_TEXT			"�S�ł��Ă��܂����c"	//�퓬���ɑS�ł������̃e�L�X�g

#define BT_RESULT_TEXT			"��|�����I"			//�퓬�ɏ��������̃e�L�X�g
#define BT_DROP_MIDLE_TEXT		"�́A"					//�h���b�v���b�Z�[�W�̐^�񒆂ɓ����e�L�X�g
#define BT_DROP_AF_TEXT			"�𗎂Ƃ��Ă������I"	//�h���b�v���b�Z�[�W�̌��ɓ����e�L�X�g
#define BT_DROP_GET_TEXT		"����ɓ��ꂽ�I"		//�h���b�v���b�Z�[�W
#define BT_RESULT_GET_EXP_TEXT	"�̌o���l����ɓ��ꂽ�I"//��ɓ��ꂽ�o���l��\������Ƃ��̃e�L�X�g
#define BT_LEVELUP_BF_TEXT		"���x��"				//���x���A�b�v���b�Z�[�W�̑O�ɓ����e�L�X�g
#define BT_LEVELUP_AF_TEXT		"�ɂȂ����I"			//���x���A�b�v���b�Z�[�W�̌��ɓ����e�L�X�g




//############### �񋓌^ ###############
enum GAME_SCENE {
	GAME_SCENE_TITLE,	//�^�C�g�����
	GAME_SCENE_PLAY,	//�v���C���
	GAME_SCENE_BATTLE,	//�퓬���
	GAME_SCENE_END,		//�G���h���
	GAME_SCENE_CHENGE	//�V�[���J�ډ��
};

enum BATTLE_STAGE
{
	WAIT_ACT,			//�s���I��҂����
	DAMEGE_CALC,		//�_���[�W�v�Z���
	ACT_MSG,			//�s�����b�Z�[�W�\�����
	DRAW_EFFECT,		//�G�t�F�N�g�\�����
	DRAW_DAMEGE,		//�_���[�W�`����
	RESULT_MSG			//���U���g���b�Z�[�W�`����
};

enum TURN
{
	MY_TURN,		//�����̃^�[��
	ENEMY_TURN		//�G�̃^�[��
};

enum ENCOUNT_TXT_TYPE
{
	ENCOUNT_TXT_PATARN1,	//�����������̃e�L�X�g���1��
	ENCOUNT_TXT_PATARN2,	//�����������̃e�L�X�g���2��
	ENCOUNT_TXT_PATARN3		//�����������̃e�L�X�g���3��
};

enum TITLE_SELECT
{
	TITLE_SELECT_START,	//�X�^�[�g
	TITLE_SELECT_END	//�I��
};

enum END_SELECT
{
	END_SELECT_TITLE,	//�^�C�g����
	END_SELECT_END		//�I��
};

//############## �v���g�^�C�v�錾 #############

void Load();				//���[�h��ʂ̏���
void Title();				//�^�C�g����ʂ̏���
void Play();				//�v���C��ʂ̏���
void Battle();				//�퓬��ʂ̏���
void End();					//�G���h��ʂ̏���
void Chenge();				//�V�[���J�ډ�ʂ̏���

void Init();				//����������
void BattleInit();			//�퓬��ʊ֌W������
void SceneChenge(int, int);	//�V�[����ύX���鏈��

void Load_Draw();			//���[�h��ʂ̕`�揈��
void Title_Draw();			//�^�C�g����ʂ̕`�揈��
void Play_Draw();			//�v���C��ʂ̕`�揈��
void Battle_Draw();			//�퓬��ʂ̕`�揈��
void End_Draw();			//�G���h��ʂ̕`�揈��

void Enconte();				//�G�Ƃ̑�������
bool Wait();				//�҂���
void Delete_Class();		//�N���X���폜���鏈��
bool LoadGameData();		//�Q�[���Ŏg�p����f�[�^����ǂݍ��ޏ���
void SetGameInit();			//�Q�[���̏����ݒ���s������
void SetSize();				//�摜���̃T�C�Y�ݒ���s������
bool GameMainLoop();		//�������[�v���̃Q�[������

//�퓬��ʂ̏���
void Bt_WaitAct();			//�퓬��ʍs���҂���Ԃ̏���
void Bt_DamegeCalc();		//�퓬��ʃ_���[�W�v�Z��Ԃ̏���
void Bt_ActMsg();			//�퓬��ʍs�����b�Z�[�W�`���Ԃ̏���
void Bt_DrawEffect();		//�퓬��ʃG�t�F�N�g�`���Ԃ̏���
void Bt_DrawDamege();		//�퓬��ʃ_���[�W�`���Ԃ̏���
void Bt_ResultMsg();		//�퓬��ʃ��U���g���b�Z�[�W�`���Ԃ̏���

const char * JudgeDrop();	//�h���b�v�������̎�ނ𔻕ʂ���

//########## �N���X�̒�` ##########