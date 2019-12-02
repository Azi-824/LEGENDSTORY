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
	COLLISION *Collision;	//�����蔻��
	CHARACTOR *Ilast;		//�����G
	MENU *menuwindow;		//���j���[�E�B���h�E
	COMMAND *BattleCommand;	//�o�g���R�}���h


	int HP;					//HP
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

	int BattleCommadType;	//�I�������o�g���R�}���h�̎��


public:
	PLAYER();				//�R���X�g���N�^
	~PLAYER();				//�f�X�g���N�^

	bool SetInit();			//�����ݒ�
	bool SetAnime(const char *, const char *, int, int, int, int, int, double, bool);	//�A�j���[�V�����摜�̐ݒ�
	bool SetImage(const char *, const char *);		//�摜�̐ݒ�
	void BattleCommandReset();		//�o�g���R�}���h�̑I�������Z�b�g����
	
	void SetHP(int);		//�̗͐ݒ�
	void SetATK(int);		//�U���͐ݒ�
	void SetDEF(int);		//�h��͐ݒ�
	void SetSPD(int);		//���x�ݒ�
	void SetMoveSpeed(int);	//�ړ����x�ݒ�
	void SetIsArive(bool);	//�����Ă��邩��ݒ�
	void SetIsDraw(bool);	//�`�悵�Ă悢����ݒ�
	void SetKeyOperation(bool); //�L�[�{�[�h�ő���ł��邩�ݒ�
	void SetPosition(int, int);	//�ʒu��ݒ�
	void SetBattleFlg(std::vector<std::string>::iterator);	//�퓬��ʂőI�񂾃R�}���h�̃t���O��ݒ肷��


	int GetHP();			//�̗͎擾
	int GetATK();			//�U���͎擾
	int GetDEF();			//�h��͎擾
	int GetSPD();			//���x�擾
	int GetMoveSpeed();		//�ړ����x�擾
	bool GetIsArive();		//�����Ă��邩�擾
	bool GetIsDraw();		//�`��ł��邩�擾
	bool GetKeyOperation();		//�L�[�{�[�h�ő���ł��邩�擾
	COLLISION * GetCollision();	//�����蔻����擾
	int GetChoiseCommamd();		//�I�������R�}���h�̎�ނ��擾



	void DrawAnime();			//�`��
	void DrawMenu();			//���j���[�E�B���h�E�`��
	void DrawCommand();			//�o�g���R�}���h�`��

	void Operation(KEYDOWN *);	//����
	void BattleOperation(KEYDOWN *);	//�퓬��ʂ̑���

	void MoveUp();				//��ֈړ�
	void MoveDown();			//���ֈړ�
	void MoveLeft();			//���ֈړ�
	void MoveRight();			//�E�ֈړ�

	void DamegeCalc(ENEMY *);			//�_���[�W�v�Z

};
