//CHARACTOR.hpp
//�L�����N�^�[�N���X

#pragma once

//###################### �w�b�_�t�@�C���ǂݍ��� ###################
#include <DxLib.h>
#include "main.hpp"
#include "IMAGE.hpp"
#include "KEYDOWN.hpp"
#include "COLLISION.hpp"


//###################### �}�N����` #######################

//###################### �N���X��` #######################
class CHARACTOR
{
private:
	IMAGE *image;				//�摜
	COLLISION *collision;		//�����蔻��̗̈�

	int Speed;					//�ړ����x

	bool IsArive;				//�����Ă��邩
	bool IsKeyOperation;		//�L�[�{�[�h�ő���ł��邩
	bool IsDraw;				//�`��ł��邩

public:

	CHARACTOR();				//�R���X�g���N�^
	~CHARACTOR();				//�f�X�g���N�^

	void MoveUp();				//��ֈړ�
	void MoveDown();			//���ֈړ�
	void MoveLeft();			//���ֈړ�
	void MoveRight();			//�E�ֈړ�

	void SetIsArive(bool);		//�����Ă��邩��ݒ�
	void SetIsDraw(bool);		//�`�悵�Ă悢����ݒ�
	void SetSpeed(int);			//�ړ����x��ݒ�
	void SetKeyOperation(bool); //�L�[�{�[�h�ő���ł��邩�ݒ�

	bool GetIsArive();			//�����Ă��邩�擾
	bool GetIsDraw();			//�`��ł��邩�擾
	int GetSpeed();				//�ړ����x���擾
	bool GetKeyOperation();		//�L�[�{�[�h�ő���ł��邩�擾
	COLLISION * GetCollision();	//�����蔻����擾

	void Operation(KEYDOWN *);	//����

	void Draw();				//�`��

	bool SetInit();				//�����ݒ�

};

