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

	this->X = 0;		//�����ʒu��ݒ�
	this->Y = 400;		//�����ʒu��ݒ�

	this->Width = 800;	//��������ݒ�
	this->Height = 100;	//����������ݒ�


	this->StrHeight = GetFontSize();	//�������擾
	this->GetWidth();					//�擪������̉������擾


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

		int cnt = 0;	//�`��ʒu�p

		auto w_itr = this->Command_itr;	//�ޔ�p

		SetFontSize(this->StrHeight * 2);	//�t�H���g�T�C�Y���{�ɂ���

		for (this->Command_itr = this->Command.begin(); this->Command_itr != this->Command.end(); ++this->Command_itr)
		{
			if (w_itr == this->Command_itr)			//�I�𒆂̗v�f��������
			{
				DrawFormatString(this->X + cnt * COMMAND_SPACE, this->Y + 10, GetColor(255, 255, 255), "%s\n", this->Command_itr->c_str());	//�E�ɂ��炵�ĕ`��
			}
			else
			{
				DrawFormatString(this->X + cnt * COMMAND_SPACE, this->Y, GetColor(255, 255, 255), "%s\n", this->Command_itr->c_str());	//�����`��
			}
			cnt++;
		}

		this->Command_itr = w_itr;		//�I��v�f�����ɖ߂�

		SetFontSize(this->StrHeight);	//�t�H���g�T�C�Y�����ɖ߂�


	return;

}

//�G�̃_���[�W�ʂ̕`��
void COMMAND::EnemyDamegeDraw(int damege)
{
	DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%d�̃_���[�W��������",damege);	//�_���[�W�e�L�X�g�`��

	return;

}

//�G�̖��O�`��
void COMMAND::EnemyNameDraw(const char *name)
{
	DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%s�̂��������I", name);	//�G�̖��O�`��
	return;
}

//�G�ɗ^����_���[�W�ʂ̕`��
void COMMAND::MyDamegeDraw(int damege)
{
	DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%d�̃_���[�W����������",damege);	//�_���[�W�e�L�X�g�`��

	return;

}

//�����̖��O�`��
void COMMAND::MyNameDraw(const char *name)
{
	DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%s�̂��������I", name);	//�����̖��O�`��
}

//�����擾
int COMMAND::GetWidth()
{
	int Strlen = 0;		//������̒����擾�p

	Strlen = strlen(this->Command_itr->c_str());

	this->StrWidth = GetDrawStringWidth(this->Command_itr->c_str(), Strlen);	//�����擾

	return this->StrWidth;

}

//�I�����Ă���R�}���h���擾
std::vector <std::string>::iterator COMMAND:: GetCommand()
{
	return this->Command_itr;
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

//����������
void COMMAND::Init()
{
	this->Command_itr = this->Command.begin();	//�I��v�f���ŏ��̗v�f�ɂ���
}
