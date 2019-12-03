//WINDOW.cpp
//�Q�[�����ŕ`�悷��E�B���h�E�̃N���X

//########################## �w�b�_�t�@�C���ǂݍ��� #########################
#include "WINDOW.hpp"

//########################## �N���X��` ##############################

//�R���X�g���N�^
WINDOW::WINDOW()
{
	//�����o�ϐ�������
	this->Window = { "" };	//�������������
	this->Window_itr = this->Window.begin();	//�擪�A�h���X

	this->Width = 100;		//����������
	this->Height = 100;		//������������

	this->X = 100;			//X�ʒu��������
	this->Y = 100;			//Y�ʒu��������

	this->StrHeight = GetFontSize();	//�������擾

}

//�f�X�g���N�^
WINDOW::~WINDOW()
{
	//vector�̃�����������s��
	std::vector<std::string> v;			//���vector���쐬����
	this->Window.swap(v);				//��ƒ��g�����ւ���

	return;

}

//�E�B���h�E���ɕ`�悷�镶�����Z�b�g����
void WINDOW::SetText(const char *text)
{
	//this->Window_itr->push_back(*text);	//�������ǉ�
	*this->Window_itr = text;
	return;
}

//�`��
void WINDOW::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//�`�惂�[�h�𓧉߂���ɕύX�A���ߗ�80���ɐݒ�

	DrawBox(this->X, this->Y, this->X + this->Width, this->Y + this->Height, GetColor(0, 0, 0), TRUE);	//�h��Ԃ�����Ŏl�p�`��`��

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�`�惂�[�h��ʏ�ɖ߂�

	DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%s", this->Window_itr->c_str());	//�����`��

	return;

}
