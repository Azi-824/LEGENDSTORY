//ENEMY.hpp
//�G�̏����Ǘ�����N���X

#pragma once

//############### �w�b�_�t�@�C���ǂݍ��� ###################
#include "DxLib.h"
#include "CHARACTOR.hpp"
#include "ANIMATION.hpp"

//############### �}�N����`�F�t�@�C���p�X�A���O ################
#define ENEMY_DIR		R"(.\MY_IMG\ENEMY\)"	//�G�̉摜�̃t�@�C��

#define ENEMY_NAME_SLIME	R"(sraim.png)"			//�X���C���̉摜�̖��O

//############## �}�N����`�F�G���[���b�Z�[�W ###################


//############## �N���X��` #####################
class ENEMY :public CHARACTOR		//�L�����N�^�[�N���X���p��
{
private:

	std::string Name;	//���O

	ANIMATION *AtkEffect;	//�U���G�t�F�N�g

	int HP;		//�̗�
	int ATK;	//�U����
	int DEF;	//�h���
	int SPD;	//�͂₳

	bool IsLoad;	//�ǂݍ��߂���
	bool IsEffectEnd;	//�G�t�F�N�g�`�悪�I��������

public:

	ENEMY(const char *,const char *);			//�R���X�g���N�^

	~ENEMY();			//�f�X�g���N�^

	void SetName(const char *);	//���O�ݒ�
	void SetHP(int);		//�̗͐ݒ�
	void SetATK(int);		//�U���͐ݒ�
	void SetDEF(int);		//�h��͐ݒ�
	void SetSPD(int);		//���x�ݒ�

	void StateSetInit();	//�G�X�e�[�^�X�����ݒ�
	bool SetAtkEffect(const char *, const char * ,int, int, int, int, int, double, bool);	//�U���G�t�F�N�g�ݒ�
	void ResetEffect();		//�G�t�F�N�g�֘A���Z�b�g

	const char * GetName();			//���O�擾
	int GetHP();			//�̗͎擾
	int GetATK();			//�U���͎擾
	int GetDEF();			//�h��͎擾
	int GetSPD();			//���x�擾

	bool GetIsLoad();		//�ǂݍ��߂������擾
	bool GetIeEffectEnd();		//�G�t�F�N�g�`�悪�I���������擾

	void DrawEffect(int,int);		//�G�t�F�N�g�`��



};
