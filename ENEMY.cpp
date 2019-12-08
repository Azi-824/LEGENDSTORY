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
	this->IsEffectEnd = false;

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
	delete this->AtkEffect;	//AtkEffect�j��
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

//�G�t�F�N�g�ݒ�
bool ENEMY::SetAtkEffect(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	this->AtkEffect = new ANIMATION(dir, name, SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
	if (this->AtkEffect->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s

	return true;

}

//�G�t�F�N�g�֘A���Z�b�g
void ENEMY::ResetEffect()
{
	this->IsEffectEnd = false;
	this->AtkEffect->ResetIsAnime();
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

//�G�t�F�N�g�`��I���������擾
bool ENEMY::GetIeEffectEnd()
{
	return this->IsEffectEnd;
}

//�G�t�F�N�g�`��
void ENEMY::DrawEffect()
{
	if (this->AtkEffect->GetIsAnimeStop() == false)	//�A�j���[�V�������I����ĂȂ����
	{
		this->AtkEffect->DrawEffect(0, 0);		//�G�t�F�N�g�`��
	}
	else
	{
		this->IsEffectEnd = true;	//�G�t�F�N�g�`��I��
	}
	return;
}
