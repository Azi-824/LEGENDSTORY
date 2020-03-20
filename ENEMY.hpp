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
#define ENEMY_NAME_BAT		R"(bat.png)"			//��������̉摜�̖��O
#define ENEMY_NAME_GOBURIN	R"(goburin.png)"		//�S�u�����̉摜�̖��O

#define ENEMY_NAME_MATANGO	R"(kinoko.png)"			//�}�^���S�̉摜�̖��O
#define ENEMY_NAME_SEED		R"(seed.png)"			//�����̎�̉摜�̖��O
#define ENEMY_NAME_TREANT	R"(treant.png)"			//�g�����g�̉摜�̖��O

#define ENEMY_NAME_YADOKARI	R"(yadokari.png)"		//���h�J���̉摜�̖��O
#define ENEMY_NAME_SCORPION	R"(scorpion.png)"		//�T�\���̉摜�̖��O
#define ENEMY_NAME_OCTPUS	R"(octpus.png)"			//�^�R�̉摜�̖��O

#define ENEMY_NAME_COBRA	R"(cobra.png)"			//�R�u���̉摜�̖��O
#define ENEMY_NAME_PUMPKIN	R"(kabocha.png)"		//�p���v�L���̉摜�̖��O
#define ENEMY_NAME_PAPILLON	R"(papillon.png)"		//�p�s�I���̉摜�̖��O

#define ENEMY_NAME_HARPY	R"(harpy.png)"			//�n�[�s�[�̉摜�̖��O
#define ENEMY_NAME_FLOWER	R"(flower.png)"			//�f�X�t�����[�̉摜�̖��O
#define ENEMY_NAME_MANTIS	R"(mantis.png)"			//�}���e�B�X�̉摜�̖��O

#define ENEMY_NAME_CRYSTAL	R"(crystal.png)"		//�N���X�^���̉摜�̖��O
#define ENEMY_NAME_ICICLE	R"(icicle.png)"			//�A�C�V�N���̉摜�̖��O
#define ENEMY_NAME_SNOWMAN	R"(snowman.png)"		//�X�m�[�}���̉摜�̖��O

#define ENEMY_NAME_FARAO	R"(farao.png)"			//�t�@���I�̉摜�̖��O
#define ENEMY_NAME_AKUMA	R"(akuma.png)"			//�����̉摜�̖��O
#define ENEMY_NAME_BONEBEAST R"(bone-b.png)"		//�{�[���r�[�X�g�̉摜�̖��O

#define ENEMY_NAME_IFRIT	R"(ifrit.png)"			//�C�t���[�g�̉摜�̖��O
#define ENEMY_NAME_GARGOYLE R"(gargoyle.png)"		//�K�[�S�C���̉摜�̖��O
#define ENEMY_NAME_PROMINENCE	R"(prominence.png)"	//�v���~�l���X�̉摜�̖��O

#define ENEMY_NAME_BOSS		R"(maou.png)"			//�����̉摜�̖��O
#define ENEMY_NAME_BOSS_MAP	R"(maou_mapimage.png)"	//�}�b�v�ɕ`�悷�閂���̉摜�̖��O

//############## �}�N����`�F�G���[���b�Z�[�W ###################

//############## �}�N����` ###################
#define ENEMY_KIND 25			//�G�̎��

#define BOSS_MAP_X	418			//�{�X�̃}�b�v�ł̕`��ʒuX
#define BOSS_MAP_Y	10			//�{�X�̃}�b�v�ł̕`��ʒuY

#define ENEMY_ENCOUNT_TYPE_NONE	-1	//�G�Ƒ������Ă��Ȃ��Ƃ�

#define ENEMY_NONE	-1			//�����l

#define ENEMY_DROP_KIND 3		//�h���b�v���镨�̎��
#define DROP_JUDGE_NUM	100		//�h���b�v�������̎�ނ𔻕ʂ���̂Ɏg�p����

//############## �񋓌^ ########################
enum ENEMY_TYPE
{
	ENE_SLIME,				//�X���C��
	ENE_BAT,				//��������
	ENE_GOBURIN,			//�S�u����
	ENE_MATANGO,			//�}�^���S
	ENE_SEED,				//�����̎�
	ENE_TREANT,				//�g�����g
	ENE_YADOKARI,			//���h�J��
	ENE_SCORPION,			//�T�\��
	ENE_OCTPUS,				//�^�R
	ENE_COBRA,				//�R�u��
	ENE_PUMPKIN,			//�p���v�L��
	ENE_PAPILLON,			//�p�s�I��
	ENE_HARPY,				//�n�[�s�[
	ENE_FLOWER,				//�f�X�t�����[
	ENE_MANTIS,				//�}���e�B�X
	ENE_CRYSTAL,			//�N���X�^��
	ENE_ICICLE,				//�A�C�V�N��
	ENE_SNOWMAN,			//�X�m�[�}��
	ENE_FARAO,				//�t�@���I
	ENE_AKUMA,				//����
	ENE_BONEBEAST,			//�{�[���r�[�X�g
	ENE_IFRIT,				//�C�t���[�g
	ENE_GARGOYLE,			//�K�[�S�C��
	ENE_PROMINENCE,			//�v���~�l���X
	ENE_BOSS				//����
};

enum DROP_TYPE
{
	DROP_TYPE_ITEM,		//�A�C�e��
	DROP_TYPE_WEAPON,	//����
	DROP_TYPE_ARMOR		//�h��
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

	int RecvDamege;	//�󂯂�_���[�W

	int EmergenceMap;	//�o������MAP��No
	int EncounteRate;	//������

	std::vector<int> Skil;	//�X�L��
	int ChoiseSkil;			//�g�p����X�L��

	int ItemCode;	//�A�C�e���R�[�h
	int WeaponCode;	//����R�[�h
	int ArmorCode;	//�h��R�[�h

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
	void SetRecvDamege(int);//�󂯂�_���[�W��ݒ�

	void SetEmergenceMap(int);	//�o��MAPNo�̐ݒ�
	void SetEncounteRate(int);	//�������ݒ�

	void SetItemCode(int);		//�A�C�e���R�[�h�ݒ�
	void SetWeaponCode(int);	//����R�[�h�ݒ�
	void SetArmorCode(int);		//�h��R�[�h�ݒ�

	void StateSetInit();	//�G�X�e�[�^�X������

	const char * GetName();			//���O�擾
	int GetHP();			//�̗͎擾
	int GetATK();			//�U���͎擾
	int GetDEF();			//�h��͎擾
	int GetSPD();			//���x�擾
	int GetChoiseSkil();	//�g�p����X�L���̎�ނ��擾
	int GetEXP();			//�o���l�擾
	int GetRecvDamege();	//�󂯂�_���[�W�擾
	
	int GetEmergenceMap();	//�o��MAPNo�̏���
	int GetEncounteRate();	//�������̎擾

	bool GetIsLoad();		//�ǂݍ��߂������擾

	void ActDecision();		//�s�����菈��
	void DamegeSend();		//�_���[�W��^����
	int Drop();				//�h���b�v����

};
