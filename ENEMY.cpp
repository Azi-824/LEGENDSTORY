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
	this->MaxHP = 0;
	this->EXP = 0;
	this->IsLoad = false;	
	this->SetIsArive(true);	//�����Ă���

	this->EneType = 0;	//�G�̎��

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

	this->SetKeyOperation(false);	//�L�[�{�[�h�ő���s��

	this->SetImagePos(GAME_WIDTH / 2 - this->GetWidth() / 2, GAME_HEIGHT / 2 - this->GetHeight() / 2);	//�ʒu����(��ʒ���)

	return;
}

//�f�X�g���N�^
ENEMY::~ENEMY()
{
	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Skil.swap(v);		//��ƒ��g�����ւ���

	return;
}

//���O�ݒ�
void ENEMY::SetName(const char *name)
{
	this->Name += name;
	return;
}

//�ő�̗͐ݒ�
void ENEMY::SetMaxHP(int maxhp)
{
	this->MaxHP = maxhp;
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

//�X�L���ݒ�
void ENEMY::SetSkil(int skil)
{
	this->Skil.push_back(skil);
	return;
}

//�o���l�ݒ�
void ENEMY::SetEXP(int exp)
{
	this->EXP = exp;
	return;
}

//�G�X�e�[�^�X�����ݒ�
void ENEMY::StateSetInit()
{

	this->HP = this->MaxHP;	//HP�Đݒ�

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

//�o���l�擾
int ENEMY::GetEXP(void)
{
	return this->EXP;
}

//�ǂݍ��߂������擾
bool ENEMY::GetIsLoad()
{
	return this->IsLoad;
}

//�g�p����X�L���̎�ނ��擾
int ENEMY::GetSkil()
{
	return this->Skil[0];
}
