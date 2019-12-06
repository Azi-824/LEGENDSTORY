//ENEMY.cpp
//�G�̃N���X

//###################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "ENEMY.hpp"

//###################### �N���X��` ##########################

//�R���X�g���N�^
ENEMY::ENEMY(const char *dir,const char *name)
{
	//�����o�ϐ�������
	this->Name = "";
	this->HP = 0;
	this->ATK = 0;
	this->DEF = 0;
	this->SPD = 0;
	this->IsLoad = false;	

	//�摜�ݒ�
	if (this->SetImage(dir, name))	//�摜���ǂݍ��߂Ă�����
	{
		this->IsLoad = true;	//�ǂݍ��߂�
	}
	else		//�摜���ǂݍ��߂Ă��Ȃ�������
	{
		this->IsLoad = false;
	}

	this->SetInit();	//�����ݒ�

	this->StateSetInit();	//�X�e�[�^�X�����ݒ�

	this->SetKeyOperation(false);	//�L�[�{�[�h�ő���s��

	return;
}

//�f�X�g���N�^
ENEMY::~ENEMY()
{
	return;
}

//���O�ݒ�
void ENEMY::SetName(const char *name)
{
	this->Name += name;
	return;
}

//HP�ݒ�
void ENEMY::SetHP(int hp)
{
	this->HP = hp;
	return;
}

//�U���͐ݒ�
void ENEMY::SetATK(int atk)
{
	this->ATK = atk;
	return;
}

//�h��͐ݒ�
void ENEMY::SetDEF(int def)
{
	this->DEF = def;
	return;
}

//���x�ݒ�
void ENEMY::SetSPD(int spd)
{
	this->SPD = spd;
	return;
}

//�G�X�e�[�^�X�����ݒ�
void ENEMY::StateSetInit()
{
	this->HP = 10;	
	this->ATK = 50;
	this->DEF = 5;
	this->SPD = 5;

	this->SetIsArive(true);	//�����Ă���

	return;
}

//���O�擾
const char * ENEMY::GetName(void)
{
	return this->Name.c_str();
}

//�̗͎擾
int ENEMY::GetHP(void)
{
	return this->HP;
}

//�U���͎擾
int ENEMY::GetATK(void)
{
	return this->ATK;
}

//�h��͎擾
int ENEMY::GetDEF(void)
{
	return this->DEF;
}

//���x�擾
int ENEMY::GetSPD(void)
{
	return this->SPD;
}

//�ǂݍ��߂������擾
bool ENEMY::GetIsLoad()
{
	return this->IsLoad;
}
