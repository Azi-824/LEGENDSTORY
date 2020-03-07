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

//################# �}�N����` #######################
#define EXP_INCREASE_VALUE	5		//�o���l�̍ő�l�̑�����
#define HP_INCREASE_VALUE	5		//�̗͂̑�����
#define MP_INCREASE_VALUE	5		//MP�̑�����
#define ATK_INCREASE_VALUE	2		//�U���͂̑�����
#define DEF_INCREASE_VALUE	2		//�h��͂̑�����
#define SPD_INCREASE_VALUE	2		//�����̑�����

#define	DEF_BOOST	1.7				//�h���I�񂾎��̖h��͂̋����{��
#define ATK_BOOST	2				//�U���͂̋����{��

#define DIST_KIND	4				//�ړ������̎��

#define PLAYER_AF_CLEAR_POS_X		720	//�N���A��̃v���C���[�̈ʒu
#define PLAYRT_AF_CLEAR_POS_Y		300	//�N���A��̃v���C���[�̈ʒu

//################# �񋓌^ ######################
enum COMMANDTYPE
{
	COMMANDE_ATACK,		//�U��
	COMMANDE_DEFENSE,	//�h��
	COMMANDE_MAGIC,		//���@
	COMMANDE_ITEM,		//�A�C�e��
	COMMANDE_ESCAPE,	//������
	COMMAND_NONE=-1		//�R�}���h��I��ł��Ȃ�
};	//�I�������R�}���h�̎��

//################# �N���X��` ##################
class PLAYER
{
private:
	ANIMATION *Anime;		//���s�摜
	
	COLLISION *Collision;	//�����蔻��
	SIKAKU *sikaku_draw;	//�`��̈�
	CHARACTOR *Ilast;		//�����G
	WEAPON *Weapon;			//����

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

	int EquipAtk;			//�����̍U����
	int EquipDef;			//�����̖h���

	std::vector<int> Skil;	//�X�L���ꗗ
	int ChoiseSkil;			//�g�p����X�L��

	int SendDamege;			//�^����_���[�W
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

	int ChengeMapKind;	//�}�b�v�؂�ւ��̎��

public:
	PLAYER();				//�R���X�g���N�^
	~PLAYER();				//�f�X�g���N�^

	bool SetInit();			//�����ݒ�
	bool SetAnime(const char *, const char *, int, int, int, int, int, double, bool);	//�A�j���[�V�����摜�̐ݒ�
	bool SetImage(const char *, const char *);		//�摜�̐ݒ�
	
	void SetName(const char *);//���O�ݒ�

	void SetLevel(int);		//���x���ݒ�
	void SetMaxEXP(int);	//�o���l�̍ő�l�ݒ�
	void SetEXP(int);		//���݂̌o���l�ݒ�

	void SetMaxHP(int);		//�ő�̗͐ݒ�
	void SetHP(int);		//���݂̗̑͐ݒ�
	void SetMaxMP(int);		//�ő�MP�ݒ�
	void SetMP(int);		//MP�ݒ�
	void SetATK(int);		//�U���͐ݒ�
	void SetDEF(int);		//�h��͐ݒ�
	void SetSPD(int);		//���x�ݒ�
	void SetEquipAtk(int);	//�����U���͐ݒ�
	void SetEquipDef(int);	//�����h���

	void SetSkil(int);		//�X�L���ꗗ��ݒ�
	void SetChoiseSkil(int);//�g�p����X�L���ݒ�

	void SetMoveSpeed(int);	//�ړ����x�ݒ�
	void SetIsArive(bool);	//�����Ă��邩��ݒ�
	void SetIsDraw(bool);	//�`�悵�Ă悢����ݒ�
	void SetKeyOperation(bool); //�L�[�{�[�h�ő���ł��邩�ݒ�
	void SetIsKeyDown(bool);	//�L�[���͂��肩�ݒ�
	void SetPosRelative(int, int);	//�ʒu��ݒ�(���ΓI)
	void SetPosAbsolute(int, int);	//�ʒu��ݒ�(��ΓI)
	void SetIsMenu(bool);		//���j���[�`�撆���ݒ�
	void SetIsBattleWin(bool);	//�퓬�ɏ��������ݒ�
	void SetLevUpMsgStartFlg(bool);	//���x���A�b�v���b�Z�[�W�X�^�[�g�̃t���O��ݒ�
	//void SetChengeMapKind(int);		//�؂�ւ���}�b�v�̎�ނ�ݒ�
	void ResetChengeMapKind(void);		//�؂�ւ���}�b�v�̎�ނ����Z�b�g
	void SetChengePos(int);				//�}�b�v�؂�ւ��������Ƃ��Ƀv���C���[�̈ʒu��ݒ�

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

	int GetChoiseSkil();	//�g�p����X�L���擾
	std::vector<int> GetSkil();		//�X�L���ꗗ�̐擪�v�f�擾

	int GetMoveSpeed();		//�ړ����x�擾
	bool GetIsArive();		//�����Ă��邩�擾
	bool GetIsDraw();		//�`��ł��邩�擾
	bool GetKeyOperation();		//�L�[�{�[�h�ő���ł��邩�擾
	COLLISION * GetCollision();	//�����蔻����擾
	bool GetIsMenu();			//���j���[�`�撆���擾
	int GetSendDamege();		//�^�����_���[�W���擾
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

	void DamegeCalc(ENEMY *,int);			//�_���[�W�v�Z

	void AddExp(int);			//�o���l�ǉ�����

	void GetNowPos(int *, int *);	//���݂̈ʒu���擾
	void SetNowPos(int, int);		//���݂̈ʒu��ݒ�

	int GetInKeyKind(void);		//���݂̃L�[���͂̎�ނ��擾

	bool CheckDetectionMap(COLLISION *[][MAP_YOKO], int *, int *);	//�}�b�v�Ƃ̓����蔻�������
	bool CheckDetectionMap(COLLISION *[][MAP_YOKO]);				//�}�b�v�Ƃ̓����蔻�������(���������ꏊ���擾���Ȃ�)

	void Recovery(void);			//�񕜂�����

	//�����֌W
	void AddWeapon(int, int);		//�����ǉ�����
	int GetWeaponCode(int);			//����R�[�h�ԍ����擾����
	int GetWeaponPossession(int);	//����̏��������擾����
	int GetWeaponSize();			//�������Ă��镐��̐��i��ށj���擾����

};
