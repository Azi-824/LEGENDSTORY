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

	SetFontSize(MSG_FONTSIZE);		//�t�H���g�T�C�Y��傫������

	auto itr = this->GetNumPos();	//�`�搔���擾

	//�`�揈��
	DrawFormatString(this->GetX(), this->GetY(), GetColor(255, 255, 255), "Level:%d", *itr);	//Level�`��
	++itr;	//���̗v�f��

	if (*itr <= 0)		//HP��0�ȉ��ɂȂ�����
		DrawString(this->GetX(), this->GetY(), "HP:0", GetColor(255, 255, 255));		//HP�̕`���0�ɂ���
	else				//HP��0��葽��������
 	DrawFormatString(this->GetX(), this->GetY() + 40, GetColor(255, 255, 255), "HP:%d", *itr);	//HP�`��
		
	++itr;	//���̗v�f��
	if (*itr <= 0)			//MP��0�ȉ��ɂȂ�����
		DrawString(this->GetX(), this->GetY(), "MP:0", GetColor(255, 255, 255));		//MP�`��0
	else				//MP��0��葽��������
	DrawFormatString(this->GetX(), this->GetY() + 80, GetColor(255, 255, 255), "MP:%d", *itr);	//MP�`��

	SetFontSize(DEFAULT_FONTSIZE);		//�t�H���g�T�C�Y�ύX(���̃T�C�Y�ɖ߂�)

}
