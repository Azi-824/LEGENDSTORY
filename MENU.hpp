//MENU.hpp
//���j���[�E�B���h�E�p�N���X

#pragma once

//######################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "DxLib.h"
#include "PLAYER.hpp"
#include "ITEM.hpp"
#include <vector>
#include <string>

//######################### �}�N����` ###########################
#define MENU_SPACE	30			//�����ƕ����̊Ԋu

#define MENU_WINDOW_RELATIVE_X	100	//���j���[�E�B���h�E�̑��Έʒu(X)
#define MENU_WINDOW_RELATIVE_Y	100	//���j���[�E�B���h�E�̑��Έʒu(Y)
#define MENU_WINDOW_WIDTH	100	//���j���[�E�B���h�̕�
#define MENU_WINDOW_HEIGHT	180	//���j���[�E�B���h�̍���
#define MENU_WINDOW_CHENGE_POSX	100		//���j���[�E�B���h�E�����E�ǂ���ɕ\�����邩���f����Ƃ���X�ʒu
#define MENU_WINDOW_CHENGE_POSY	85		//���j���[�E�B���h�E�����E�ǂ���ɕ\�����邩���f����Ƃ���Y�ʒu

//######################### �񋓌^ ###############################
enum MENU_COMMAND
{
	MENU_STATUS,		//�X�e�[�^�X
	MENU_ITEM,			//�A�C�e��
	MENU_SOUBI,			//����
	MENU_SAVE			//�Z�[�u
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

	void DrawChoise(int,PLAYER *,ITEM *[]);	//�I�񂾓��e���Ƃ̕`��

	void Reset();	//�I��v�f�����Z�b�g

	void SetIsChoise(bool);	//�I������Ă��邩�ݒ�

	bool GetIsChoise(void);	//�I������Ă��邩�擾

};
