//PLAYER.hpp
//�v���C���[�N���X

#pragma once

//################## �w�b�_�t�@�C���ǂݍ��� #####################
#include "DxLib.h"
#include "ANIMATION.hpp"
#include "CHARACTOR.hpp"
#include "COLLISION.hpp"
#include "MENU.hpp"
#include "COMMAND.hpp"
#include "ENEMY.hpp"
#include "STATEWINDOW.hpp"

//################# �}�N����`: �t�@�C���p�X�A���O #######################

//################# �񋓌^ ######################
enum COMMANDTYPE
{
	ATACK,		//�U��
	DEFENSE,	//�h��
	MAGIC,		//���@
	ITEM,		//�A�C�e��
	ESCAPE,		//������
};	//�I�������R�}���h�̎��

//################# �N���X��` ##################
class PLAYER
{
private:
	ANIMATION *Anime;		//���s�摜
	ANIMATION *AtkEffect;	//�U���G�t�F�N�g
	
	COLLISION *Collision;	//�����蔻��
	CHARACTOR *Ilast;		//�����G
	
	MENU *menuwindow;		//���j���[�E�B���h�E


	int HP;					//HP
	int MP;					//MP
	int ATK;				//�U����
	int DEF;				//�h���
	int SPD;				//���x

	int MoveSpeed;			//�ړ����x
	int Dist;				//�ړ�����

	bool IsArive;			//�����Ă��邩
	bool IsDraw;			//�`�悵�Ă悢��
	bool IsKeyOperation;	//�L�[�{�[�h�ő���ł��邩
	bool IsKeyDown;			//�L�[�{�[�h��������Ă��邩
	bool IsMenu;			//���j���[�E�B���h�E���`�悳��Ă��邩
	bool EffectEnd;			//�G�t�F�N�g�`�揈�����I��������


public:
	PLAYER();				//�R���X�g���N�^
	~PLAYER();				//�f�X�g���N�^

	bool SetInit();			//�����ݒ�
	bool SetAnime(const char *, const char *, int, int, int, int, int, double, bool);	//�A�j���[�V�����摜�̐ݒ�
	bool AddEffect(const char *, const char *, int, int, int, int, int, double, bool);	//�G�t�F�N�g�摜�̐ݒ�
	bool SetImage(const char *, const char *);		//�摜�̐ݒ�
	void EffectReset();		//�G�t�F�N�g�֘A�̃��Z�b�g
	
	void SetHP(int);		//�̗͐ݒ�
	void SetMP(int);		//MP�ݒ�
	void SetATK(int);		//�U���͐ݒ�
	void SetDEF(int);		//�h��͐ݒ�
	void SetSPD(int);		//���x�ݒ�
	void SetMoveSpeed(int);	//�ړ����x�ݒ�
	void SetIsArive(bool);	//�����Ă��邩��ݒ�
	void SetIsDraw(bool);	//�`�悵�Ă悢����ݒ�
	void SetKeyOperation(bool); //�L�[�{�[�h�ő���ł��邩�ݒ�
	void SetPosition(int, int);	//�ʒu��ݒ�


	int GetHP();			//�̗͎擾
	int GetMP();			//MP�擾
	int GetATK();			//�U���͎擾
	int GetDEF();			//�h��͎擾
	int GetSPD();			//���x�擾
	int GetMoveSpeed();		//�ړ����x�擾
	bool GetIsArive();		//�����Ă��邩�擾
	bool GetIsDraw();		//�`��ł��邩�擾
	bool GetKeyOperation();		//�L�[�{�[�h�ő���ł��邩�擾
	COLLISION * GetCollision();	//�����蔻����擾
	bool GetEffectEnd();		//�G�t�F�N�g�̕`�揈�����I���������擾


	void DrawAnime();			//�`��
	void DrawMenu();			//���j���[�E�B���h�E�`��
	void DrawAtk(int, int);		//�U���G�t�F�N�g�`��

	void Operation(KEYDOWN *);	//����

	void MoveUp();				//��ֈړ�
	void MoveDown();			//���ֈړ�
	void MoveLeft();			//���ֈړ�
	void MoveRight();			//�E�ֈړ�

	void DamegeCalc(ENEMY *);			//�_���[�W�v�Z

};
