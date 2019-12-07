//COMMAND.hpp
//�o�g���R�}���h�N���X

#pragma once

//##################### �w�b�_�t�@�C���ǂݍ��� ####################
#include "DxLib.h"
#include <vector>
#include <string>

//#################### �}�N����` ########################
#define COMMAND_SPACE		170		//�R�}���h�Ԃ̊Ԋu
#define COMMAND_KIND		5		//�R�}���h�̎��

//#################### �N���X��` ########################
class COMMAND
{
private:

	std::vector<std::string> Command;					//�R�}���h�E�B���h�E�̕�����
	std::vector<std::string>::iterator Command_itr;		//������̃n���h��

	int X;			//�R�}���h�E�B���h�E�̘g��X���W
	int Y;			//�R�}���h�E�B���h�E�̘g��Y���W

	int Width;		//�R�}���h�E�B���h�E�̘g�̉���
	int Height;		//�R�}���h�E�B���h�E�̘g�̍���

	int StrHeight;	//������̍���
	int StrWidth;	//������̕�

	bool IsDrawDamege;	//�_���[�W��\�����Ă悢��


public:

	COMMAND();			//�R���X�g���N�^

	~COMMAND();			//�f�X�g���N�^

	void Draw();		//�`��
	void EnemyDamegeDraw(const char *, int);	//�_���[�W�ʂ̕`��
	void MyDamegeDraw(const char *,int);		//�����̃_���[�W�ʂ̕`��

	int GetWidth();		//�����擾
	std::vector < std::string>::iterator GetCommand();	//�I�����Ă���R�}���h���擾

	void Next();		//���̗v�f��

	void Back();		//�O�̗v�f��

	void Init();		//����������

};
