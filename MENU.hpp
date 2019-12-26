//MENU.hpp
//���j���[�E�B���h�E�p�N���X

#pragma once

//######################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "DxLib.h"
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
	
	std::vector<std::string> Menu;					//���j���[�E�B���h�E�̕�����
	std::vector<std::string>::iterator Menu_itr;	//������̃n���h��

	int X;			//���j���[�E�B���h�E�̘g��X���W
	int Y;			//���j���[�E�B���h�E�̘g��Y���W

	int Width;		//���j���[�E�B���h�E�̘g�̉���
	int Height;		//���j���[�E�B���h�E�̘g�̍���

	int StrHeight;	//������̍���

public:

	MENU();			//�R���X�g���N�^

	~MENU();		//�f�X�g���N�^

	void Draw(int,int);	//�`��
	void DrawChoise(int);	//�I�񂾓��e���Ƃ̕`��

	void Next();	//�I��v�f�����ֈړ�

	void Back();	//�I��v�f��O�ֈړ�

	void Reset();	//�I��v�f�����Z�b�g

	std::vector<std::string>::iterator GetChoiseMenu();	//�I���������ڂ��擾

};
