//TEXTSTR.hpp
//������A���͂��Ǘ�����

#pragma once

//###################### �w�b�_�t�@�C���ǂݍ��� ####################
#include "DxLib.h"
#include <string>
#include <vector>

//###################### �}�N����` #########################

//###################### �N���X��` #########################
class TEXTSTR
{
private:

	int Width;						//������̉���
	
	//std::vector	<std::string> Str_2;	//��������Ǘ�����
	std::string Str;

	bool IsFontLoad;				//�t�H���g�͓ǂݍ��߂���

public:

	TEXTSTR();		//�R���X�g���N�^

	~TEXTSTR();		//�f�X�g���N�^	

	void SetText(const char*, int);	//��������Z�b�g����
	
	int GetWidth();				//������̉������擾

	void Draw(int, int,int);		//�`��

};
