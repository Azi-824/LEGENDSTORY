//TEXTSTR.hpp
//������A���͂��Ǘ�����

#pragma once

//###################### �w�b�_�t�@�C���ǂݍ��� ####################
#include "DxLib.h"
#include "KEYDOWN.hpp"
#include <string>
#include <vector>


//###################### �}�N����` #########################
#define STR_SPACE	100			//������Ԃ̋�

#define DEFAULT_TEXT_Y	450		//�f�t�H���g�̃e�L�X�g�`��ʒu�iY���W�j

//###################### �N���X��` #########################
class TEXTSTR
{
private:

	int Width;							//������̉���

	int Height;							//������̍���
	
	std::vector	<std::string> Str;		//��������Ǘ�����
	
	std::vector <std::string> ::iterator Pos;	//������̃n���h��
	
public:

	TEXTSTR();		//�R���X�g���N�^

	~TEXTSTR();		//�f�X�g���N�^	

	void SetText(std::vector<std::string>);			//��������Z�b�g����
	
	int GetWidth();									//������̉������擾

	int GetHeight();								//������̍������擾

	void Draw(int, int, int,bool);					//�`��

	void Draw(int, int, int ,bool,unsigned int);	//�F���w�肵�ĕ`��

	void Next();									//�I�����Ă��镶��������̗v�f�ɕύX����

	void Back();									//�I�����Ă��镶�����O�̗v�f�ɕύX����

	std::vector<std::string>::iterator GetPos();	//���ݑI�����Ă��镶����̃|�C���^���擾����

};
