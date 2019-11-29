//ENEMY.hpp
//�G�̏����Ǘ�����N���X

#pragma once

//############### �w�b�_�t�@�C���ǂݍ��� ###################
#include "DxLib.h"
#include "CHARACTOR.hpp"

//############### �}�N����`�F�t�@�C���p�X�A���O ################
#define ENEMY_DIR		R"(.\MY_IMG\ENEMY\)"	//�G�̉摜�̃t�@�C��

#define ENEMY_NAME_SLIME	R"(sraim.png)"			//�X���C���̉摜�̖��O

//############## �}�N����`�F�G���[���b�Z�[�W ###################


//############## �N���X��` #####################
class ENEMY :public CHARACTOR		//�L�����N�^�[�N���X���p��
{
private:

	int HP;		//�̗�
	int ATK;	//�U����
	int DEF;	//�h���
	int SPD;	//�͂₳

	bool IsLoad;	//�ǂݍ��߂���

public:

	ENEMY(const char *,const char *);			//�R���X�g���N�^

	~ENEMY();			//�f�X�g���N�^

	void SetHP(int);		//�̗͐ݒ�
	void SetATK(int);		//�U���͐ݒ�
	void SetDEF(int);		//�h��͐ݒ�
	void SetSPD(int);		//���x�ݒ�

	void StateSetInit();	//�G�X�e�[�^�X�����ݒ�

	int GetHP();			//�̗͎擾
	int GetATK();			//�U���͎擾
	int GetDEF();			//�h��͎擾
	int GetSPD();			//���x�擾

	bool GetIsLoad();		//�ǂݍ��߂������擾



};
