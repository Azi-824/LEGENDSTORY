//UI.hpp
//�Q�[�����Ŏg�p����UI���Ǘ�����N���X

#pragma once

//######################### �w�b�_�t�@�C���ǂݍ��� #############################
#include "DxLib.h"
#include "PLAYER.hpp"
#include "SELECT.hpp"
#include "LIST_ITEM.hpp"
#include "LIST_ARMOR.hpp"
#include "LIST_WEAPON.hpp"

//######################### �}�N����` #####################################
#define UI_DIR	R"(.\MY_IMG\Ui\)"	//UI�摜�̃t�H���_��

#define UI_WINDOW_NAME	R"(window.png)"		//�E�B���h�E�̖��O

//�X�e�[�^�X�E�B���h�E�֌W
#define STA_WIN_X		0				//�X�e�[�^�X�E�B���h�E�`��J�nX�ʒu
#define STA_WIN_Y		530				//�X�e�[�^�X�E�B���h�E�`��J�nY�ʒu
#define STA_WIN_WIDTH	350				//�X�e�[�^�X�E�B���h�E�̉���
#define STA_WIN_HEIGHT	110				//�X�e�[�^�X�E�B���h�E�̍���
#define STA_TXT_X		STA_WIN_X + 10	//�X�e�[�^�X�̕����̕`��J�nX�ʒu
#define STA_TXT_Y		STA_WIN_Y + 5	//�X�e�[�^�X�̕����̕`��J�nY�ʒu
#define STA_SPACE		20				//�X�e�[�^�X�����̊Ԋu
//HP�o�[
#define STA_HP_BAR_X	90				//HP�o�[�̕`��J�nX�ʒu
#define	STA_HP_BAR_Y	580				//HP�o�[�̕`��J�nY�ʒu
#define	STA_HP_BAR_WIDTH 100			//HP�o�[�̕`�敝
#define STA_HP_BAR_HEIGHT 15			//HP�o�[�̕`�捂��
//MP�o�[
#define STA_MP_BAR_X	90				//MP�o�[�̕`��J�nX�ʒu
#define	STA_MP_BAR_Y	605				//MP�o�[�̕`��J�nY�ʒu
#define	STA_MP_BAR_WIDTH 100			//MP�o�[�̕`�敝
#define STA_MP_BAR_HEIGHT 15			//MP�o�[�̕`�捂��

//���j���[�ꗗ
#define MENU_LIST_WIN_X			50		//���j���[�E�B���h�E�i�ꗗ�j�̕`��J�nX�ʒu
#define MENU_LIST_WIN_Y			50		//���j���[�E�B���h�E�i�ꗗ�j�̕`��J�nY�ʒu
#define MENU_LIST_WIN_WIDTH		150		//���j���[�E�B���h�E�i�ꗗ�j�̕�
#define MENU_LIST_WIN_HEIGHT	180		//���j���[�E�B���h�E�i�ꗗ�j�̍���
#define MENU_LIST_TEXT_X		MENU_LIST_WIN_X + 10	//���j���[�E�B���h�E�i�ꗗ�j�̃e�L�X�g�̕`��J�nX�ʒu
#define MENU_LIST_TEXT_Y		MENU_LIST_WIN_Y	+ 5		//���j���[�E�B���h�E�i�ꗗ�j�̃e�L�X�g�̕`��J�nY�ʒu

//���j���[��
#define MENU_WINDOW_X	MENU_LIST_WIN_X	+ MENU_LIST_WIN_WIDTH	//�I�񂾃��j���[���̃E�B���h�E�̕`��J�nX�ʒu
#define MENU_WINDOW_Y	MENU_LIST_WIN_Y							//�I�񂾃��j���[���̃E�B���h�E�̕`��J�nY�ʒu
#define MENU_TEXT_X		MENU_WINDOW_X + 10						//�I�񂾃��j���[���̓��e�̕`��J�nX�ʒu
#define MENU_TEXT_Y		MENU_WINDOW_Y + 35						//�I�񂾃��j���[���̓��e�̕`��J�nY�ʒu
#define MENU_TEXT_TOP_Y	MENU_WINDOW_Y + 5						//�I�񂾃��j���[���̐擪�v�f�̕`��J�nY�ʒu
#define MENU_WINDOW_WIDTH	600									//�I�񂾃��j���[���̃E�B���h�E�̉���
#define MENU_WINDOW_HEIGHT	500									//�I�񂾃��j���[���̃E�B���h�E�̍���

#define MENU_ITEM_NAME_SPACE	200		//�A�C�e����ʂ̖��O�Ə������̕\���Ԋu
#define MENU_EQUIP_NAME_SPACE	200		//������ʂ̖��O�Ə������̕\���Ԋu

//�o�g���R�}���h�֌W
#define CMD_WIN_X		350				//�o�g���R�}���h�̃E�B���h�E�̕`��J�nX�ʒu
#define	CMD_WIN_Y		530				//�o�g���R�}���h�̃E�B���h�E�̕`��J�nY�ʒu
#define CMD_WIN_WIDTH	120				//�o�g���R�}���h�̃E�B���h�E�̉���
#define CMD_WIN_HEIGHT	110				//�o�g���R�}���h�̃E�B���h�E�̍���
#define CMD_TXT_X		CMD_WIN_X + 10	//�o�g���R�}���h�̕����̕`��J�nX�ʒu
#define CMD_TXT_Y		CMD_WIN_Y + 5	//�o�g���R�}���h�̕����̕`��J�nY�ʒu

//���@�ꗗ�֌W
#define BT_LIST_WIN_X		470						//���@�ꗗ�̃E�B���h�E�̕`��J�nX�ʒu
#define BT_LIST_WIN_Y		530						//���@�ꗗ�̃E�B���h�E�̕`��J�nY�ʒu
#define BT_LIST_WIN_WIDTH	100						//���@�ꗗ�̃E�B���h�E�̉���
#define BT_LIST_WIN_HEIGHT	110						//���@�ꗗ�̃E�B���h�E�̍���
#define BT_LIST_TXT_X		BT_LIST_WIN_X + 10		//���@�ꗗ�̕����̕`��J�nX�ʒu
#define BT_LIST_TXT_Y		BT_LIST_WIN_Y + 5		//���@�ꗗ�̕����̕`��J�nY�ʒu

//�E�B���h�E�֌W
#define BT_WINDOW_X		0			//�o�g����ʂ̃E�B���h�E�̕`��J�nX�ʒu
#define BT_WINDOW_Y		380			//�o�g����ʂ̃E�B���h�E�̕`��J�nY�ʒu
#define PLAY_WIN_X		0			//�v���C��ʂ̃E�B���h�E�̕`��J�nX�ʒu
#define PLAY_WIN_Y		490			//�v���C��ʂ̃E�B���h�E�̕`��J�nY�ʒu

#define PLAY_WIN_TEXT_X	PLAY_WIN_X + 20	//�v���C��ʂ̃E�B���h�E���ɕ`�悷��e�L�X�g�̕`��J�nX�ʒu
#define PLAY_WIN_TEXT_Y	PLAY_WIN_Y + 20	//�v���C��ʂ̃E�B���h�E���ɕ`�悷��e�L�X�g�̕`��J�nY�ʒu

//�e�L�X�g�|�[�Y�֌W
#define BT_TXT_POSE_Y	510		//�o�g����ʂ̃e�L�X�g�|�[�Y�̕`��Y�ʒu

#define DEFAULT_TEXT_Y	490		//�f�t�H���g�̃e�L�X�g�`��ʒu�iY���W�j
#define TXT_Y_3			450		//�I������3�̎��̃e�L�X�g�`��ʒu�iY���W�j

//######################### �񋓌^ #################################
enum UI_IMAGE_TYPE
{
	UI_WINDOW			//�E�B���h�E
};

enum MENU_COMMAND
{
	MENU_STATUS,		//�X�e�[�^�X
	MENU_ITEM,			//�A�C�e��
	MENU_EQUIPMENT,		//����
	MENU_SETUMEI,		//�������
	MENU_SAVE			//�Z�[�u
};

enum MENU_EQUIP_DIR
{
	MENU_EQUIP_SELECT_KIND,		//���킩�h���I������i�K
	MENU_EQUIP_SELECT_EQUIP,	//�������镐��A�������͖h���I������i�K
	MENU_EQUIP_SELECT_DECISION	//�������邩�I������i�K�i�͂��A���A�������j
};

//######################### �N���X��` #####################################
class UI
{
private:

	IMAGE *UiImage;					//ui�̉摜

	ANIMATION *UiAnime;				//ui�̃A�j���[�V����

	bool IsDrawUIAnime;				//UI�̃A�j���[�V������`�悵�Ă悢��

	int Menu_Equip_dir;				//������ʂ̑I���̒i�K���Ǘ�����ϐ�

public:

	SELECT *MenuSelect;			//���j���[�̑I����
	SELECT *BattleCommand;		//�o�g���R�}���h�̑I����
	SELECT *ItemSelect;			//�A�C�e���̑I����
	SELECT *WeaponSelect;		//����̑I����
	SELECT *ArmorSelect;		//�h��̑I����
	SELECT *Yes_No;				//�͂��A�������̑I����
	SELECT *EquipSelect;		//���킩�h��̑I����

	UI();					//�R���X�g���N�^

	~UI();					//�f�X�g���N�^

	//���j���[�E�B���h�E�֘A
	void DrawMenu();					//���j���[�E�B���h�E�`��
	void ResetMenu();					//���j���[�֌W�̃����o�[�����Z�b�g
	int GetMenuEquipDir(void);			//���j���[�̑�����ʂ̑I�����̒i�K���擾
	void DrawMenuCheck();				//���j���[�E�B���h�E�ł̊m�F�̑I�����`��

	//�o�g���R�}���h�֘A
	void DrawCommand();					//�o�g���R�}���h�`��
	void BattleInit();					//�o�g���R�}���h�Ŏg�p����v�f������������

	//�X�e�[�^�X�E�B���h�E�֘A
	void DrawStateWindow(PLAYER *);				//�X�e�[�^�X�E�B���h�E�`��
	void DrawWindow(int, int, int, int);				//�E�B���h�E��`�悷��
	void DrawWindow(int,int,int,int,unsigned int);		//�E�B���h�E��`�悷��(�F�w��)
	void DrawWindowFrame(int, int, int, int);			//�E�B���h�E�̘g��`�悷��

	//UI�摜�֌W
	void DrawUiImage(int, int,int);				//UI�̉摜��`�悷��
	bool AddUiImage(const char *, const char *,int);//ui�摜��ǉ�����
	int GetUiImageWidth(int);					//ui�摜�̉����擾
	int GetUiImageHeight(int);					//ui�摜�̍����擾

	//�A�j���[�V�����֌W
	bool AddUiAnime(const char *, const char *, int, int, int, int, int, double, bool);	//�A�j���[�V�����摜��ǉ�����
	void DrawUiAnime(int,int);			//�A�j���[�V�����摜��`�悷��
	void SetIsDrawUIAnime(bool);		//�A�j���[�V�����摜��`�悵�Ă悢���ݒ�
	bool GetIsDrawUIAnime(void);		//�A�j���[�V�����摜��`�悵�Ă悢���擾

	void SetSize(void);					//�摜�T�C�Y��ݒ肷��

	//�A�C�e���֌W
	void DrawItemSelect(int, int, std::vector<int>);	//�A�C�e���̑I������`�悷��
	bool MenuSelectItem(KEYDOWN *,MUSIC *);				//���j���[�̃A�C�e����ʂ̏���


	//�����֌W
	void DrawMenuEquip(std::vector<int>, std::vector<int>);	//���j���[��ʂ̑����`�揈��
	int MenuSelectEquip(KEYDOWN *, MUSIC *);				//���j���[�̑�����ʂ̏���

	//�I�����֌W
	void SelectUpdate(ITEM *, LIST_ITEM *);		//�I�����̓��e���X�V���鏈��(�A�C�e��)
	void SelectUpdate(WEAPON *, LIST_WEAPON *);	//����
	void SelectUpdate(ARMOR *, LIST_ARMOR *);	//�h��

	void DrawCheck(const char *);				//�m�F�̑I������`�悷��

};
