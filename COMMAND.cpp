//COMMAND.cpp
//�o�g���R�}���h�N���X

//####################### �w�b�_�t�@�C���ǂݍ��� ###########################
#include "COMMAND.hpp"

//####################### �N���X��` ##############################

//�R���X�g���N�^
COMMAND::COMMAND()
{
	this->Command = { "��������","�ڂ�����","�܂ق�","�A�C�e��","�ɂ���" };	//�o�g���E�B���h�E�̕������ݒ�
	this->Command_itr = this->Command.begin();								//�擪�̃A�h���X������

	this->X = 400;		//�����ʒu��ݒ�
	this->Y = 0;		//�����ʒu��ݒ�

	this->Width = 800;	//��������ݒ�
	this->Height = 200;	//����������ݒ�

	this->StrHeight = GetFontSize();	//�������擾

	return;

}


//�f�X�g���N�^
COMMAND::~COMMAND()
{
	//vector�̃�����������s��
	std::vector<std::string> v;			//���vector���쐬����
	this->Command.swap(v);				//��ƒ��g�����ւ���

	return;

}

//�`��
void COMMAND::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//�`�惂�[�h�𓧉߂���ɕύX�A���ߗ�80���ɐݒ�

	DrawBox(this->X, this->Y, this->X + this->Width, this->Y + this->Height, GetColor(0, 0, 0), TRUE);	//�h��Ԃ�����Ŏl�p�`��`��

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�`�惂�[�h��ʏ�ɖ߂�

	int cnt = 0;	//�`��ʒu�p

	auto w_itr = this->Command_itr;	//�ޔ�p

	for (this->Command_itr = this->Command.begin(); this->Command_itr != this->Command.end(); ++this->Command_itr)
	{
		if (w_itr == this->Command_itr)			//�I�𒆂̗v�f��������
		{
			DrawFormatString(this->X + 10, this->Y + cnt * COMMAND_SPACE, GetColor(255, 255, 255), "%s\n", this->Command_itr->c_str());	//�E�ɂ��炵�ĕ`��
		}
		else
		{
			DrawFormatString(this->X, this->Y + cnt * COMMAND_SPACE, GetColor(255, 255, 255), "%s\n", this->Command_itr->c_str());	//�����`��
		}
		cnt++;
	}

	this->Command_itr = w_itr;		//�I��v�f�����ɖ߂�

	return;

}

//�I��v�f�����ֈړ�
void COMMAND::Next()
{
	if (this->Command_itr != this->Command.end() - 1)	//�Ō�̗v�f�Ŗ������
	{
		this->Command_itr++;	//���̗v�f��
	}
	return;
}

//�I��v�f��O�ֈړ�
void COMMAND::Back()
{
	if (this->Command_itr != this->Command.begin())	//�ŏ��̗v�f�łȂ����
	{
		this->Command_itr--;	//�O�̗v�f��
	}
	return;
}

