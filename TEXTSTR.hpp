//TEXTSTR.hpp
//������A���͂��Ǘ�����

#pragma once

//###################### �w�b�_�t�@�C���ǂݍ��� ####################
#include "DxLib.h"
#include "FONT.hpp"
#include <string>
#include <vector>

//###################### �}�N����` #########################

//###################### �N���X��` #########################
class TEXTSTR
{
private:

	FONT *font;	//�t�H���g

	int Width;						//������̉���
	
	std::vector	<std::string> Str;	//��������Ǘ�����

	bool IsFontLoad;				//�t�H���g�͓ǂݍ��߂���

public:

	TEXTSTR();		//�R���X�g���N�^

	~TEXTSTR();		//�f�X�g���N�^	

	void SetText(char *, int);	//��������Z�b�g����
	
	int GetWidth();				//������̉������擾

	void Draw(int, int);		//�`��

};
