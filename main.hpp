/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* main.hpp     																				�@ */
/*       																						�@ */

#pragma once

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########


//########## �}�N����` ##########
#define GAME_LEFT	  0		//��ʂ̉��̎n�_
#define GAME_TOP	  0		//��ʂ̏c�̎n�_
#define GAME_WIDTH	800		//��ʂ̉��̑傫��
#define GAME_HEIGHT	600		//��ʂ̏c�̑傫��
#define GAME_COLOR	32		//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_NAME	"GAME TITLE"		//�E�B���h�E�̃^�C�g��
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE�F�E�B���h�E���[�h / FALSE�F�t���X�N���[��

#define SET_WINDOW_ST_MODE_DEFAULT			0	//�f�t�H���g
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//�^�C�g���o�[�Ȃ�
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//�^�C�g���o�[�ƃt���[���Ȃ�
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//�t���[���Ȃ�

#define GAME_FPS_SPEED					   60

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
	WAIT_PLAYER_ACT,		//�v���C���[�̍s���I��҂����
	PLAYER_DAMEGE_CALC,		//�_���[�W�v�Z���
	PLAYER_ACT_MSG,			//�s�����b�Z�[�W�\�����
	PLAYER_DRAW_EFFECT,		//�G�t�F�N�g�\�����
	DRAW_DAMEGE,			//�_���[�W�`����
	ENEMY_WAIT_ACT,			//�G�̍s���I��҂����
	ENEMY_DAMEGE_CALC,		//�G�̃_���[�W�v�Z
	ENEMY_ACT_MSG,			//�G�̍s�����b�Z�[�W�\�����
	ENEMY_DRAW_EFFECT		//�G�̃G�t�F�N�g�\�����
};

//############## �v���g�^�C�v�錾 #############

void Title();				//�^�C�g����ʂ̏���
void Play();				//�v���C��ʂ̏���
void Battle();				//�퓬��ʂ̏���
void End();					//�G���h��ʂ̏���
void Chenge();				//�V�[���J�ډ�ʂ̏���

void Init();				//����������
void SceneChenge(int, int);	//�V�[����ύX���鏈��

void Title_Draw();			//�^�C�g����ʂ̕`�揈��
void Play_Draw();			//�v���C��ʂ̕`�揈��
void Battle_Draw();			//�퓬��ʂ̕`�揈��
void End_Draw();			//�G���h��ʂ̕`�揈��

//########## �N���X�̒�` ##########