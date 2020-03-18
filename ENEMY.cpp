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
	this->RecvDamege = 0;
	this->IsLoad = false;	
	this->SetIsArive(true);	//�����Ă���

	this->EmergenceMap = 0;	//�o��MAP
	this->EncounteRate = 0;	//������

	this->EneType = 0;	//�G�̎��
	this->ChoiseSkil = -1;	//�g�p����X�L��������

	//�摜�ݒ�
	if (this->SetImage(dir, name))	//�摜���ǂݍ��߂Ă�����
	{
		this->IsLoad = true;	//�ǂݍ��߂�
	}
	else		//�摜���ǂݍ��߂Ă��Ȃ�������
	{
		this->IsLoad = false;
	}

	this->SetKeyOperation(false);	//�L�[�{�[�h�ő���s��

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

//�󂯂�_���[�W��ݒ�
void ENEMY::SetRecvDamege(int recvdamege)
{
	this->RecvDamege = recvdamege;
	return;
}

//�o��MAP�̐ݒ�
void ENEMY::SetEmergenceMap(int mapno)
{
	this->EmergenceMap = mapno;
	return;
}

//�������̐ݒ�
void ENEMY::SetEncounteRate(int encounterate)
{
	this->EncounteRate = encounterate;
	return;
}

//�G�X�e�[�^�X�����ݒ�
void ENEMY::StateSetInit()
{

	this->HP = this->MaxHP;	//HP�Đݒ�
	this->RecvDamege = 0;	//�󂯂�_���[�W������

	this->SetIsArive(true);	//�����Ă���

	this->ChoiseSkil = -1;	//�g�p����X�L��������

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

//�󂯂�_���[�W�擾
int ENEMY::GetRecvDamege(void)
{
	return this->RecvDamege;
}

//�o��MAP�̎擾
int ENEMY::GetEmergenceMap(void)
{
	return this->EmergenceMap;
}

//�������̎擾
int ENEMY::GetEncounteRate(void)
{
	return this->EncounteRate;
}

//�ǂݍ��߂������擾
bool ENEMY::GetIsLoad()
{
	return this->IsLoad;
}

//�g�p����X�L���̎�ނ��擾
int ENEMY::GetChoiseSkil()
{
	return this->ChoiseSkil;
	//return 2;
}

//�s�����菈��
void ENEMY::ActDecision(void)
{
	int rand = GetRand(this->Skil.size() - 1);		//�g�p����X�L���������_���Ō���

	this->ChoiseSkil = rand;	//�g�p����X�L���ݒ�

	return;
	
}

//�_���[�W��^����
void ENEMY::DamegeSend(void)
{
	this->HP -= this->RecvDamege;	//�_���[�W��^����

	if (this->HP <= 0)	//HP��0�ȉ��ɂȂ�����
	{
		this->HP = 0;	//HP��0
		this->SetIsArive(false);	//���S
	}

	return;
}
