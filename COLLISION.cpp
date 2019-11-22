/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* COLLISION.cpp     																			   */
/* COLLISION�N���X																				   */

//##########�w�b�_�[�t�@�C���ǂݍ��� ##########
#include "COLLISION.hpp"

//########## �N���X�̒�` ##########

//�R���X�g���N�^
COLLISION::COLLISION()
{
	this->SetIsDraw(true);	//�����蔻��͈̔͂�`�悷��

	return;
}

//�R���X�g���N�^�̃I�[�o�[���[�h
COLLISION::COLLISION(int left, int top, int width, int height)
{
	this->Left = left;
	this->Top = top;
	this->Width = width;
	this->Height = height;

	this->SetIsDraw(true);	//�����蔻��͈̔͂�`�悷��

	return;
}


//�f�X�g���N�^
COLLISION::~COLLISION()
{
	return;
}

//�l�p�̈ʒu��ݒ�
void COLLISION::SetValue(int left, int top, int width, int height)
{
	this->Left = left;
	this->Top = top;
	this->Width = width;
	this->Height = height;

	this->Right = left + width;
	this->Bottom = top + height;

	return;
}

//�l�p�̒��S��X�ʒu���擾
int COLLISION::GetCenterX(void)
{
	return this->Left + this->Width / 2;
}

//�l�p�̒��S��Y�ʒu���擾
int COLLISION::GetCenterY(void)
{
	return this->Top + this->Height / 2;
}

//�Փˌ��m�`�F�b�N
//���@���FCollision�F�Փ˂�������
bool COLLISION::DetectionCheck(COLLISION *aite)
{
	if (this->Top < aite->Bottom &&
		this->Left < aite->Right &&
		this->Bottom > aite->Top &&
		this->Right > aite->Left)
	{
		return true;	//��������
	}

	return false;		//�������Ă��Ȃ�
}

//�����蔻��͈̔͂�`�悷�邩
void COLLISION::SetIsDraw(bool draw)
{
	this->IsDraw = draw;
	return;
}

//�����蔻��͈̔͂�`��
void COLLISION::Draw(void)
{
	if (this->IsDraw == true)
	{
		DrawBox(this->Left, this->Top, this->Right, this->Bottom, GetColor(255, 0, 0), false);	//�g�����`��
	}
	return;
}

//�����蔻��͈̔͂�`��i�I�[�o�[���[�h�j
//���@���Funsigned int�FGetColor(?,?,?)�̖߂�l
void COLLISION::Draw(unsigned int Color)
{
	if (this->IsDraw == true)
	{
		DrawBox(this->Left, this->Top, this->Right, this->Bottom, Color, false);	//�g�����`��
	}
	return;
}