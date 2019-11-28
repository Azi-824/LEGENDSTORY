//MENU.hpp
//���j���[�E�B���h�E�p�N���X

#pragma once

//######################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "DxLib.h"
#include <vector>
#include <string>

//######################### �}�N����` ###########################
#define MENU_SPACE	30		//�����ƕ����̊Ԋu

//######################### �N���X��` ###########################
class MENU
{
private :
	
	std::vector<std::string> Menu;					//���j���[�E�B���h�E�̕�����
	std::vector<std::string>::iterator Menu_itr;	//������̃n���h��

	int X;			//���j���[�E�B���h�E�̘g��X���W
	int Y;			//���j���[�E�B���h�E�̘g��Y���W:

	int Width;		//���j���[�E�B���h�E�̘g�̉���
	int Height;		//���j���[�E�B���h�E�̘g�̍���

public:

	MENU();			//�R���X�g���N�^

	~MENU();		//�f�X�g���N�^

	void Draw();	//�`��

};
