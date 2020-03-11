//MENU.hpp
//���j���[�E�B���h�E�p�N���X

#pragma once

//######################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "DxLib.h"
#include <vector>
#include <string>

//######################### �}�N����` ###########################
#define MENU_SPACE	30			//�����ƕ����̊Ԋu

//���j���[�ꗗ
#define MENU_LIST_WINDOW_RELATIVE_X	100	//���j���[�E�B���h�E(�ꗗ)�̑��Έʒu(X)
#define MENU_LIST_WINDOW_RELATIVE_Y	100	//���j���[�E�B���h�E(�ꗗ)�̑��Έʒu(Y)
#define MENU_LIST_WINDOW_WIDTH	150		//���j���[�E�B���h(�ꗗ)�̕�
#define MENU_LIST_WINDOW_HEIGHT	180		//���j���[�E�B���h(�ꗗ)�̍���
#define MENU_WINDOW_CHENGE_POSX	100		//���j���[�E�B���h�E(�ꗗ)�����E�ǂ���ɕ\�����邩���f����Ƃ���X�ʒu
#define MENU_WINDOW_CHENGE_POSY	85		//���j���[�E�B���h�E(�ꗗ)�����E�ǂ���ɕ\�����邩���f����Ƃ���Y�ʒu

//���j���[��
#define MENU_WINDOW_X	200				//�I�񂾃��j���[���̃E�B���h�E�̕`��J�nX�ʒu
#define MENU_WINDOW_Y	50				//�I�񂾃��j���[���̃E�B���h�E�̕`��J�nY�ʒu
#define MENU_TEXT_X		220				//�I�񂾃��j���[���̓��e�̕`��J�nX�ʒu
#define MENU_TEXT_Y		75				//�I�񂾃��j���[���̓��e�̕`��J�nY�ʒu
#define MENU_TEXT_IND_Y	55				//�I�񂾃��j���[���̖ڎ��`��J�nY�ʒu
#define MENU_WINDOW_WIDTH	600			//�I�񂾃��j���[���̃E�B���h�E�̉���
#define MENU_WINDOW_HEIGHT	500			//�I�񂾃��j���[���̃E�B���h�E�̍���


//######################### �񋓌^ ###############################
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

//######################### �N���X��` ###########################
class MENU
{
private :
	
	int X;			//���j���[�E�B���h�E�̘g��X���W
	int Y;			//���j���[�E�B���h�E�̘g��Y���W

	int Width;		//���j���[�E�B���h�E�̘g�̉���
	int Height;		//���j���[�E�B���h�E�̘g�̍���

	int StrHeight;	//������̍���

	bool IsChoise;	//�I������Ă��邩

public:

	MENU();			//�R���X�g���N�^

	~MENU();		//�f�X�g���N�^

	void Reset();	//�I��v�f�����Z�b�g

	void SetIsChoise(bool);	//�I������Ă��邩�ݒ�

	bool GetIsChoise(void);	//�I������Ă��邩�擾

};
