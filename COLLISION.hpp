//COLLISION.hpp
//�����蔻��̃N���X

#pragma once

//###################### �w�b�_�t�@�C���ǂݍ��� ####################
#include "DxLib.h"

//###################### �}�N����` #######################

//###################### �N���X��` #######################
class COLLISION{
private:

	bool IsDraw;							//�����蔻��͈̔͂�`�悷�邩�H

public:
	int Left;		//X�ʒu
	int Top;		//Y�ʒu
	int Width;		//��
	int Height;		//����
	int Right;		//X�ʒu�{��
	int Bottom;		//Y�ʒu�{����

public:
	COLLISION();							//�R���X�g���N�^
	COLLISION(int, int, int, int);			//�R���X�g���N�^�̃I�[�o�[���[�h
	virtual ~COLLISION();					//�f�X�g���N�^

	void SetValue(int, int, int, int);		//���A��A���A����������

	int GetCenterX(void);					//�l�p�̒��S��X�ʒu���擾
	int GetCenterY(void);					//�l�p�̒��S��Y�ʒu���擾

	bool DetectionCheck(COLLISION*);		//�Փˌ��m

	void SetIsDraw(bool);					//�����蔻��͈̔͂�`�悷�邩

	void Draw(void);						//�����蔻��͈̔͂�ԐF�ŕ`��
	void Draw(unsigned int);				//�����蔻��͈̔͂̐F��ݒ肵�ĕ`��

};
