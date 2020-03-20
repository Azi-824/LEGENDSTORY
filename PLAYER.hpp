//PLAYER.hpp
//�v���C���[�N���X

#pragma once

//################## �w�b�_�t�@�C���ǂݍ��� #####################
#include "DxLib.h"
#include "ANIMATION.hpp"
#include "CHARACTOR.hpp"
#include "ENEMY.hpp"
#include "MAP.hpp"
#include "WEAPON.hpp"
#include "ARMOR.hpp"
#include "ITEM.hpp"
#include <fstream>
#include "LIST_ITEM.hpp"
#include "LIST_WEAPON.hpp"
#include "LIST_ARMOR.hpp"

//################# �}�N����` #######################
#define EXP_INCREASE_VALUE	5		//�o���l�̍ő�l�̑�����
#define HP_INCREASE_VALUE	5		//�̗͂̑�����
#define MP_INCREASE_VALUE	5		//MP�̑�����
#define ATK_INCREASE_VALUE	2		//�U���͂̑�����
#define DEF_INCREASE_VALUE	2		//�h��͂̑�����
#define SPD_INCREASE_VALUE	2		//�����̑�����

#define	DEF_BOOST	1.7				//�h���I�񂾎��̖h��͂̋����{��
#define ATK_BOOST	2				//�U���͂̋����{��

#define MAX_BP		5				//BP�̍ő�l
#define START_BP	1				//BP�̏����l
#define MAX_USE_BP	3				//���Ŏg�p���邱�Ƃ��ł���BP�̍ő�l
#define BP_BOOST_LEVEL0	1.0			//�g�p����BP��0�̏ꍇ�̋����{��
#define BP_BOOST_LEVEL1	1.4			//�g�p����BP��1�̏ꍇ�̋����{��
#define BP_BOOST_LEVEL2	1.8			//�g�p����BP��2�̏ꍇ�̋����{��
#define BP_BOOST_LEVEL3	2.0			//�g�p����BP��3�̏ꍇ�̋����{��

#define DIST_KIND	4				//�ړ������̎��

#define PLAYER_AF_CLEAR_POS_X		720	//�N���A��̃v���C���[�̈ʒu
#define PLAYRT_AF_CLEAR_POS_Y		300	//�N���A��̃v���C���[�̈ʒu

#define PLAYER_DATA_DIR			R"(.\MY_DATA\Player\)"		//�v���C���[�̃f�[�^�̃t�@�C����
#define PLAYER_DATA_NAME		R"(Player_Data.csv)"		//�v���C���[�̃f�[�^��csv�t�@�C��
#define PLATER_DATA_INIT_NAME	R"(Player_Data_Init.csv)"	//�v���C���[�̏����f�[�^��csv�t�@�C��


//############## �}�N����`�F�G���[���b�Z�[�W ###################
#define PLAYER_DATA_ERROR_TTILE	"PLAYER_DATA_ERROR"								//�G���[�^�C�g��
#define PLAYER_DATA_ERROR_MSG	"�v���C���[�f�[�^���ǂݍ��߂܂���ł���"		//�G���[���b�Z�[�W

//################# �񋓌^ ######################
enum COMMANDTYPE
{
	COMMANDE_ATACK,		//�U��
	COMMANDE_DEFENSE,	//�h��
	COMMANDE_MAGIC,		//���@
	COMMANDE_ITEM,		//�A�C�e��
	COMMANDE_ESCAPE,	//������
	COMMAND_NONE = -1		//�R�}���h��I��ł��Ȃ�
};	//�I�������R�}���h�̎��

enum USE_BP_NUM
{
	USE_BP_0,	//BP���g�p
	USE_BP_1,	//BP1�g�p
	USE_BP_2,	//BP2�g�p
	USE_BP_3	//BP3�g�p
};//�g�p����BP�̐�

//################# �N���X��` ##################
class PLAYER
{
private:
	ANIMATION *Anime;		//���s�摜
	
	COLLISION *Collision;	//�����蔻��
	SIKAKU *sikaku_draw;	//�`��̈�
	CHARACTOR *Ilast;		//�����G

	WEAPON *Weapon;			//����
	ARMOR *Armor;			//�h��
	ITEM *Item;				//�A�C�e��

	std::string Name;		//�L�����̖��O

	int Level;				//���x��
	int MaxEXP;				//�o���l�̍ő�l
	int NowEXP;				//���݂̌o���l

	int MaxHP;				//HP�̍ő�l
	int NowHP;				//���݂�HP
	int MaxMP;				//MP�̍ő�l
	int NowMP;				//MP
	int ATK;				//�U����
	int DEF;				//�h���
	int SPD;				//���x

	int BP;					//�u�[�X�g�|�C���g(BP)
	int UseBPNum;			//�g�p����BP

	int EquipAtk;			//�����̍U����
	int EquipDef;			//�����̖h���
	int Equip_WeaponCode;	//�������Ă��镐��̃R�[�h�ԍ����i�[���Ă���
	int Equip_ArmorCode;	//�������Ă���h��̃R�[�h�ԍ����i�[���Ă���

	std::vector<int> Skil;	//�X�L���ꗗ
	int ChoiseSkil;			//�g�p����X�L��

	int RecvDamege;			//�󂯂�_���[�W

	int MoveSpeed;			//�ړ����x
	int Dist;				//�ړ�����
	int InKeyKind;			//������Ă���L�[�{�[�h�̎��

	bool IsArive;			//�����Ă��邩
	bool IsDraw;			//�`�悵�Ă悢��
	bool IsKeyOperation;	//�L�[�{�[�h�ő���ł��邩
	bool IsKeyDown;			//�L�[�{�[�h��������Ă��邩
	bool IsMenu;			//���j���[�E�B���h�E���`�悳��Ă��邩
	bool IsActMsg;			//�s�����b�Z�[�W�\������
	bool IsBattleWin;		//�퓬�ɏ�������
	bool LevUpMsgStart_flg;	//���x���A�b�v���b�Z�[�W�X�^�[�g�t���O

	int ChengeMapKind;		//�}�b�v�؂�ւ��̎��

public:
	PLAYER();				//�R���X�g���N�^
	~PLAYER();				//�f�X�g���N�^

	bool SetInit();			//�����ݒ�
	bool SetAnime(const char *, const char *, int, int, int, int, int, double, bool);	//�A�j���[�V�����摜�̐ݒ�
	bool SetImage(const char *, const char *);		//�摜�̐ݒ�
	
	void SetMP(int);		//MP�ݒ�

	void SetChoiseSkil(int);//�g�p����X�L���ݒ�

	void SetIsKeyDown(bool);		//�L�[���͂��肩�ݒ�
	void SetPosRelative(int, int);	//�ʒu��ݒ�(���ΓI)
	void SetPosAbsolute(int, int);	//�ʒu��ݒ�(��ΓI)
	void SetIsMenu(bool);			//���j���[�`�撆���ݒ�
	void SetIsBattleWin(bool);		//�퓬�ɏ��������ݒ�
	void SetLevUpMsgStartFlg(bool);	//���x���A�b�v���b�Z�[�W�X�^�[�g�̃t���O��ݒ�
	void ResetChengeMapKind(void);	//�؂�ւ���}�b�v�̎�ނ����Z�b�g
	void SetChengePos(int);			//�}�b�v�؂�ւ��������Ƃ��Ƀv���C���[�̈ʒu��ݒ�

	//�X�e�[�^�X�֌W
	const char *GetName();	//���O�擾

	int GetLevel();			//���x���擾
	int GetMaxEXP();		//�o���l�̍ő�l�擾
	int GetEXP();			//���݂̌o���l�擾

	int GetMaxHP();			//�ő�̗͎擾
	int GetHP();			//���݂̗͎̑擾
	int GetMaxMP();			//�ő�MP�擾
	int GetMP();			//MP�擾
	int GetATK();			//�U���͎擾
	int GetDEF();			//�h��͎擾
	int GetSPD();			//���x�擾

	int GetEquipAtk();		//�����U���͎擾
	int GetEquipDef();		//�����h��͎擾

	int GetChoiseSkil();		//�g�p����X�L���擾
	std::vector<int> GetSkil();	//�X�L���ꗗ�擾

	int GetMoveSpeed();			//�ړ����x�擾
	bool GetIsArive();			//�����Ă��邩�擾
	bool GetIsDraw();			//�`��ł��邩�擾
	bool GetKeyOperation();		//�L�[�{�[�h�ő���ł��邩�擾
	COLLISION * GetCollision();	//�����蔻����擾
	bool GetIsMenu();			//���j���[�`�撆���擾
	int GetRecvDamege();		//�󂯂��_���[�W���擾
	bool GetIsActMsg();			//�s�����b�Z�[�W�\�������擾
	bool GetIsMove();			//�ړ������ǂ����擾
	bool GetIsBattleWin();		//�퓬�ɏ��������擾
	bool GetLevUpMsgStartFlg();	//���x���A�b�v�X�^�[�g���b�Z�[�W�t���O���擾
	bool GetIsKeyDown();		//�L�[���͂����邩�擾
	int GetChengeMapKind();		//�؂�ւ���}�b�v�̎�ނ��擾

	void DrawWalk();			//�`��

	void Operation(KEYDOWN *, COLLISION *[][MAP_YOKO]);	//����

	void MoveUp();				//��ֈړ�
	void MoveDown();			//���ֈړ�
	void MoveLeft();			//���ֈړ�
	void MoveRight();			//�E�ֈړ�

	void DamegeCalc(ENEMY *,int);	//�_���[�W�v�Z
	void DamegeSend();				//�_���[�W��^����

	void AddExp(int);	//�o���l�ǉ�����

	void GetNowPos(int *, int *);	//���݂̈ʒu���擾
	void SetNowPos(int, int);		//���݂̈ʒu��ݒ�

	int GetInKeyKind(void);		//���݂̃L�[���͂̎�ނ��擾

	bool CheckDetectionMap(COLLISION *[][MAP_YOKO], int *, int *);	//�}�b�v�Ƃ̓����蔻�������
	bool CheckDetectionMap(COLLISION *[][MAP_YOKO]);				//�}�b�v�Ƃ̓����蔻�������(���������ꏊ���擾���Ȃ�)

	void Recovery(void);			//�񕜂�����

	//����֌W
	void EquipWeapon(int);					//����𑕔�����
	WEAPON * GetWeaponClass();				//����N���X���擾
	void SetWeaponAtk(LIST_WEAPON *);		//����̍U���͐ݒ�
	void AddDropWeapon(int, int);			//�h���b�v��������̒ǉ�

	////�h��֌W
	void EquipArmor(int);					//�h��𑕔�����
	ARMOR * GetArmorClass();				//�h��N���X���擾
	void SetArmorDef(LIST_ARMOR *);			//�h��̖h��͐ݒ�
	void AddDropArmor(int, int);			//�h���b�v�����h��̒ǉ�

	//�A�C�e���֌W
	bool UseItem(int);						//�A�C�e���g�p����
	ITEM * GetItemClass();					//�A�C�e���N���X���擾
	void SetItemRecovery(LIST_ITEM *);		//�A�C�e���̉񕜗ʐݒ�
	void AddDropItem(int, int, char);		//�A�C�e���ǉ�����

	//�Z�[�u�f�[�^�֌W
	bool LoadData(const char *, const char *);	//�Z�[�u�f�[�^�Ǎ�
	bool Save(const char *, const char *);		//�Z�[�u

	//BP�֌W
	int GetBP(void);			//BP�擾
	bool AddBP(void);			//BP���Z
	int GetUseBP(void);			//�g�p����BP���擾
	bool PlusUseBP(void);		//�g�p����BP�𑝂₷
	bool MinusUseBP(void);		//�g�p����BP�����炷
	double GetBPBoostValue();	//BP�ɂ���ċ��������{�����擾(�_���[�W�v�Z���Ŏg�p)
	void BPUse(void);			//BP���g�p����

	void BattleInit(void);		//�퓬�Ŏg�p������̂�����������

};
