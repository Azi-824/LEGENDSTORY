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

	std::vector<std::string> Str;					//�E�B���h�E���ɕ`�悷�镶����
	std::vector<std::string>::iterator Str_itr;		//������̃n���h��

	std::vector<int>Num;	//�E�B���h�E���ɕ\�����镶����i�����j
	std::vector<int>::iterator Num_itr;		//������i�����j�̃n���h��

	int X;			//�E�B���h�E�̘g��X���W
	int Y;			//�E�B���h�E�̘g��Y���W

	int Width;		//�E�B���h�E�̘g�̉���
	int Height;		//�E�B���h�E�̘g�̍���

	int StrHeight;	//������̍���
	int StrWidth;	//������̕�

public:

	WINDOW();				//�R���X�g���N�^

	~WINDOW();				//�f�X�g���N�^

	void SetX(int);			//X�ʒu�ݒ�
	void SetY(int);			//Y�ʒu�ݒ�
	void SetWidth(int);		//�����ݒ�
	void SetHeight(int);	//�����ݒ�

	int GetX(void);			//X�ʒu�擾
	int GetY(void);			//Y�ʒu�擾
	int GetWidth(void);		//�����擾
	int GetHeight(void);	//�����擾

	int GetStrWidth(void);	//������̉����擾
	int GetStrHeight(void);	//������̍����擾

	std::vector<int>::iterator GetNumPos(void);	//������̃A�h���X�擾

	void SetText(const char*);			//�E�B���h�E���ɕ`�悷�镶�����Z�b�g����
	void SetText(int);					//�E�B���h�E���ɕ`�悷�鐔�����Z�b�g����

	virtual void Draw();			//�`��

};
