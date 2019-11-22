//PLAYER.hpp
//�v���C���[�N���X

#pragma once

//################## �w�b�_�t�@�C���ǂݍ��� #####################
#include "DxLib.h"
#include "ANIMATION.hpp"
#include "CHARACTOR.hpp"
#include "COLLISION.hpp"

//################# �}�N����`: �t�@�C���p�X�A���O #######################
//#define ANIME_DIR_PLAYER R"(.\MY_ANIME\walk\)"		//�v���C���[�̉摜�t�H���_�̖��O
//
//#define ANIME_NAME_PLAYER R"(player_walk.png)"		//�v���C���[�̉摜�̖��O
//

//################# �N���X��` ##################
class PLAYER
{
private:
	ANIMATION *Anime;		//���s�摜
	COLLISION *Collision;	//�����蔻��
	CHARACTOR *Ilast;		//�����G

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

public:
	PLAYER();				//�R���X�g���N�^
	~PLAYER();				//�f�X�g���N�^

	bool SetInit();			//�����ݒ�
	bool SetAnime(const char *, const char *, int, int, int, int, int, double, bool);	//�A�j���[�V�����摜�̐ݒ�
	bool SetImage(const char *, const char *);		//�摜�̐ݒ�
	
	void SetHP(int);		//�̗͐ݒ�
	void SetATK(int);		//�U���͐ݒ�
	void SetDEF(int);		//�h��͐ݒ�
	void SetSPD(int);		//���x�ݒ�
	void SetMoveSpeed(int);	//�ړ����x�ݒ�
	void SetIsArive(bool);	//�����Ă��邩��ݒ�
	void SetIsDraw(bool);	//�`�悵�Ă悢����ݒ�
	void SetKeyOperation(bool); //�L�[�{�[�h�ő���ł��邩�ݒ�



	int GetHP();			//�̗͎擾
	int GetATK();			//�U���͎擾
	int GetDEF();			//�h��͎擾
	int GetSPD();			//���x�擾
	int GetMoveSpeed();		//�ړ����x�擾
	bool GetIsArive();		//�����Ă��邩�擾
	bool GetIsDraw();		//�`��ł��邩�擾
	bool GetKeyOperation();		//�L�[�{�[�h�ő���ł��邩�擾
	COLLISION * GetCollision();	//�����蔻����擾



	void DrawAnime();			//�`��

	void Operation(KEYDOWN *);	//����

	void MoveUp();				//��ֈړ�
	void MoveDown();			//���ֈړ�
	void MoveLeft();			//���ֈړ�
	void MoveRight();			//�E�ֈړ�

};
