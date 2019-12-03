//WINDOW.hpp
//�Q�[�����ŕ`�悷��E�B���h�E�̌��ɂȂ�N���X

#pragma once

//######################### �w�b�_�t�@�C���ǂݍ��� ###########################
#include "DxLib.h"
#include <vector>
#include <string>

//######################### �}�N����` ###############################

//######################### �N���X��` ###############################
class WINDOW
{
private:

	std::vector<std::string> Window;					//�E�B���h�E���ɕ`�悷�镶����
	std::vector<std::string>::iterator Window_itr;		//������̃n���h��

	int X;			//�E�B���h�E�̘g��X���W
	int Y;			//�E�B���h�E�̘g��Y���W

	int Width;		//�E�B���h�E�̘g�̉���
	int Height;		//�E�B���h�E�̘g�̍���

	int StrHeight;	//������̍���
	int StrWidth;	//������̕�

public:

	WINDOW();				//�R���X�g���N�^

	~WINDOW();				//�f�X�g���N�^

	void SetText(const char*);			//�E�B���h�E���ɕ`�悷�镶�����Z�b�g����

	void Draw();			//�`��

};
