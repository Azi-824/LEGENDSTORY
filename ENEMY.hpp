//ENEMY.hpp
//�G�̏����Ǘ�����N���X

#pragma once

//############### �w�b�_�t�@�C���ǂݍ��� ###################
#include "DxLib.h"
#include "CHARACTOR.hpp"
#include "ANIMATION.hpp"
#include "main.hpp"
#include "EFFECT.hpp"
#include <vector>

//############### �}�N����`�F�t�@�C���p�X�A���O ################
#define ENEMY_DIR			R"(.\MY_IMG\ENEMY\)"	//�G�̉摜�̃t�@�C��

#define ENEMY_NAME_SLIME	R"(sraim.png)"			//�X���C���̉摜�̖��O
#define ENEMY_NAME_YADOKARI	R"(yadokari.png)"		//���h�J���̉摜�̖��O
#define ENEMY_NAME_BAT		R"(bat.png)"			//��������̉摜�̖��O
#define ENEMY_NAME_FARAO	R"(farao.png)"			//�t�@���I�̉摜�̖��O
#define ENEMY_NAME_GOBURIN	R"(goburin.png)"		//�S�u�����̉摜�̖��O
#define ENEMY_NAME_AKUMA	R"(akuma.png)"			//�����̉摜�̖��O
#define ENEMY_NAME_HARPY	R"(harpy.png)"			//�n�[�s�[�̉摜�̖��O
#define ENEMY_NAME_IFRIT	R"(ifrit.png)"			//�C�t���[�g�̉摜�̖��O

//############## �}�N����`�F�G���[���b�Z�[�W ###################

//############## �}�N����` ###################
#define ENEMY_KIND 8			//�G�̎��

//############## �񋓌^ ########################
enum ENEMY_TYPE
{
	SLIME,				//�X���C��
	YADOKARI,			//���h�J��
	BAT,				//��������
	FARAO,				//�t�@���I
	GOBURIN,			//�S�u����
	AKUMA,				//����
	HARPY,				//�n�[�s�[
	IFRIT				//�C�t���[�g
};

//############## �N���X��` #####################
class ENEMY :public CHARACTOR		//�L�����N�^�[�N���X���p��
{
private:

	std::string Name;	//���O

	int MaxHP;	//�ő�HP
	int HP;		//�̗�
	int ATK;	//�U����
	int DEF;	//�h���
	int SPD;	//�͂₳
	
	int EXP;	//�o���l

	int EmergenceMap;	//�o������MAP��No
	int EncounteRate;	//������

	std::vector<int> Skil;	//�X�L��
	int ChoiseSkil;			//�g�p����X�L��

	int EneType;	//�G�̎��

	bool IsLoad;	//�ǂݍ��߂���

public:

	ENEMY(const char *,const char *);			//�R���X�g���N�^

	~ENEMY();			//�f�X�g���N�^

	void SetName(const char *);	//���O�ݒ�
	void SetMaxHP(int);		//�ő�̗͐ݒ�
	void SetHP(int);		//�̗͐ݒ�
	void SetATK(int);		//�U���͐ݒ�
	void SetDEF(int);		//�h��͐ݒ�
	void SetSPD(int);		//���x�ݒ�
	void SetSkil(int);		//�X�L���ݒ�
	void SetEXP(int);		//�o���l�ݒ�

	void SetEmergenceMap(int);	//�o��MAPNo�̐ݒ�
	void SetEncounteRate(int);	//�������ݒ�

	void StateSetInit();	//�G�X�e�[�^�X�����ݒ�

	const char * GetName();			//���O�擾
	int GetHP();			//�̗͎擾
	int GetATK();			//�U���͎擾
	int GetDEF();			//�h��͎擾
	int GetSPD();			//���x�擾
	int GetChoiseSkil();	//�g�p����X�L���̎�ނ��擾
	int GetEXP();			//�o���l�擾
	
	int GetEmergenceMap();	//�o��MAPNo�̏���
	int GetEncounteRate();	//�������̎擾

	bool GetIsLoad();		//�ǂݍ��߂������擾

	void ActDecision();		//�s�����菈��

};
