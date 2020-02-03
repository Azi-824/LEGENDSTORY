//UI.hpp
//�Q�[�����Ŏg�p����UI���Ǘ�����N���X

#pragma once

//######################### �w�b�_�t�@�C���ǂݍ��� #############################
#include "DxLib.h"
#include "MENU.hpp"
#include "PLAYER.hpp"
#include "SELECT.hpp"

//######################### �}�N����` #####################################
#define UI_DIR	R"(.\MY_IMG\Ui\)"	//UI�摜�̃t�H���_��

#define UI_WINDOW_NAME	R"(window.png)"		//�E�B���h�E�̖��O

#define STR_SPACE		100			//������Ԃ̋�

//�X�e�[�^�X�E�B���h�E�֌W
#define STA_WIN_X		0			//�X�e�[�^�X�E�B���h�E�`��J�nX�ʒu
#define STA_WIN_Y		540			//�X�e�[�^�X�E�B���h�E�`��J�nY�ʒu
#define STA_WIN_WIDTH	350			//�X�e�[�^�X�E�B���h�E�̉���
#define STA_WIN_HEIGHT	100			//�X�e�[�^�X�E�B���h�E�̍���
#define STA_TXT_X		10			//�X�e�[�^�X�̕����̕`��J�nX�ʒu
#define STA_TXT_Y		540			//�X�e�[�^�X�̕����̕`��J�nY�ʒu
#define STA_SPACE		20			//�X�e�[�^�X�����̊Ԋu

//�o�g���R�}���h�֌W
#define CMD_WIN_X		350			//�o�g���R�}���h�̃E�B���h�E�̕`��J�nX�ʒu
#define	CMD_WIN_Y		540			//�o�g���R�}���h�̃E�B���h�E�̕`��J�nY�ʒu
#define CMD_WIN_WIDTH	120			//�o�g���R�}���h�̃E�B���h�E�̉���
#define CMD_WIN_HEIGHT	100			//�o�g���R�}���h�̃E�B���h�E�̍���
#define CMD_TXT_X		370			//�o�g���R�}���h�̕����̕`��J�nX�ʒu
#define CMD_TXT_Y		540			//�o�g���R�}���h�̕����̕`��J�nY�ʒu

//���@�ꗗ�֌W
#define MGC_WIN_X		470			//���@�ꗗ�̃E�B���h�E�̕`��J�nX�ʒu
#define MGC_WIN_Y		540			//���@�ꗗ�̃E�B���h�E�̕`��J�nY�ʒu
#define MGC_WIN_WIDTH	100			//���@�ꗗ�̃E�B���h�E�̉���
#define MGC_WIN_HEIGHT	100			//���@�ꗗ�̃E�B���h�E�̍���
#define MGC_TXT_X		485			//���@�ꗗ�̕����̕`��J�nX�ʒu
#define MGC_TXT_Y		540			//���@�ꗗ�̕����̕`��J�nY�ʒu

//�E�B���h�E�֌W
#define BT_WINDOW_X		0			//�o�g����ʂ̃E�B���h�E�̕`��J�nX�ʒu
#define BT_WINDOW_Y		390			//�o�g����ʂ̃E�B���h�E�̕`��J�nY�ʒu

//�e�L�X�g�|�[�Y�֌W
#define BT_TXT_POSE_Y	510			//�o�g����ʂ̃e�L�X�g�|�[�Y�̕`��Y�ʒu

#define DEFAULT_TEXT_Y	490			//�f�t�H���g�̃e�L�X�g�`��ʒu�iY���W�j
#define TXT_Y_3			450			//�I������3�̎��̃e�L�X�g�`��ʒu�iY���W�j

//######################### �񋓌^ #################################
enum UI_IMAGE_TYPE
{
	UI_WINDOW			//�E�B���h�E
};

enum UI_SELECT_TYPE
{
	UI_SELECT_MENU,			//���j���[�̑I����
	UI_SELECT_BATTLE_CMD	//�o�g���R�}���h�̑I����
};

//######################### �N���X��` #####################################
class UI
{
private:

	MENU *menuwindow;				//���j���[�E�B���h�E

	IMAGE *UiImage;					//ui�̉摜

	ANIMATION *UiAnime;				//ui�̃A�j���[�V����

	SELECT *MenuSelect;				//���j���[�̑I����
	SELECT *BattleCommand;			//�o�g���R�}���h�̑I����

	int BattleCommadType;			//�I�������o�g���R�}���h�̎��

	int ChoiseMenu;					//���j���[��ʂőI���������e

	std::vector<std::string> Str;	//������i�[�p
	std::vector<std::string>::iterator Str_itr;	//�C�e���[�^

	bool IsDrawUIAnime;				//UI�̃A�j���[�V������`�悵�Ă悢��

public:

	UI();					//�R���X�g���N�^

	~UI();					//�f�X�g���N�^

	//���j���[�E�B���h�E�֘A
	void DrawMenu(int ,int);				//���j���[�E�B���h�E�`��
	void SetChoiseMenu(std::vector<std::string>::iterator);	//���j���[�őI�񂾓��e��ݒ肷��
	int GetChoiseMenu();				//���j���[��ʂł̑I����e���擾
	void ResetMenu();					//���j���[�֌W�̃����o�[�����Z�b�g
	bool GetIsChoise(void);				//�I������Ă��邩�擾

	//�o�g���R�}���h�֘A
	void SetBattleFlg();				//�퓬��ʂőI�񂾃R�}���h�̃t���O��ݒ肷��
	int GetChoiseCommamd();				//�I�������R�}���h�̎�ނ��擾
	void DrawCommand();					//�o�g���R�}���h�`��
	void BattleInit();					//�o�g���R�}���h�Ŏg�p����v�f������������

	//�X�e�[�^�X�E�B���h�E�֘A
	void DrawStateWindow(PLAYER *);				//�X�e�[�^�X�E�B���h�E�`��
	void DrawWindow(int, int, int, int);				//�E�B���h�E��`�悷��
	void DrawWindow(int,int,int,int,unsigned int);		//�E�B���h�E��`�悷��(�F�w��)

	//UI�摜�֌W
	void DrawUiImage(int, int,int);				//UI�̉摜��`�悷��
	bool AddUiImage(const char *, const char *,int);//ui�摜��ǉ�����
	int GetUiImageWidth(int);					//ui�摜�̉����擾
	int GetUiImageHeight(int);					//ui�摜�̍����擾

	//�I�����֌W
	bool SelectOperation(KEYDOWN *, MUSIC *, int);			//�w�肳�ꂽ�I�����̃L�[������s��
	std::vector<std::string>::iterator GetNowSelect(int);	//�w�肳�ꂽ�I�����̌��ݑI�����Ă���v�f���擾����
	void SelectClear(int);									//�w�肳�ꂽ�I�����̓��e���N���A����
	void NowSelectReset(int);								//�w�肳�ꂽ�I�����̌��ݑI�����Ă�����e���A�ŏ��̗v�f�ɖ߂�

	//�A�j���[�V�����֌W
	bool AddUiAnime(const char *, const char *, int, int, int, int, int, double, bool);	//�A�j���[�V�����摜��ǉ�����
	void DrawUiAnime(int,int);			//�A�j���[�V�����摜��`�悷��
	void SetIsDrawUIAnime(bool);		//�A�j���[�V�����摜��`�悵�Ă悢���ݒ�
	bool GetIsDrawUIAnime(void);		//�A�j���[�V�����摜��`�悵�Ă悢���擾

};
