//STATEWINDOW.cpp
//�X�e�[�^�X�E�B���h�E�̃N���X

//######################### �w�b�_�t�@�C���ǂݍ��� #########################
#include "STATEWINDOW.hpp"

//######################### �N���X��` ############################

//�R���X�g���N�^
STATEWINDOW::STATEWINDOW()
{
	return;
}

//�f�X�g���N�^
STATEWINDOW::~STATEWINDOW()
{
	return;
}

//�`��
void STATEWINDOW::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//�`�惂�[�h�𓧉߂���ɕύX�A���ߗ�80���ɐݒ�

	DrawBox(this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight(), GetColor(255, 0, 0), TRUE);	//�h��Ԃ�����Ŏl�p�`��`��

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�`�惂�[�h��ʏ�ɖ߂�

	auto itr = this->GetNumPos();	//�`�搔���擾

	//�`�揈��
 	DrawFormatString(this->GetX(), this->GetY(), GetColor(255, 255, 255), "HP:%d", *itr);	//HP�`��
		
	++itr;	//���̗v�f��

	DrawFormatString(this->GetX(), this->GetY() + 50, GetColor(255, 255, 255), "MP:%d", *itr);	//MP�`��

}
