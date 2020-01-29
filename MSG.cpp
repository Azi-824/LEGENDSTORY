//MSG.cpp
//���b�Z�[�W�N���X

//################# �w�b�_�t�@�C���ǂݍ��� ######################
#include "MSG.hpp"

//################# �N���X��` ############################

//�R���X�g���N�^
MESSAGE::MESSAGE()
{
	//����������
	this->IsLastMsg = false;		//�Ō�̃��b�Z�[�W�ł͂Ȃ�
	this->IsMsgEnd = false;			//���b�Z�[�W�`��I���ł͂Ȃ�

	return;
}

//�f�X�g���N�^
MESSAGE::~MESSAGE()
{

	std::vector<std::string> v;			//���vector���쐬����
	this->Msg.swap(v);					//��ƒ��g�����ւ���

	return;
}

//�������ݒ�
void MESSAGE::SetMsg(const char *msg)
{
	this->ResetFlg();					//�t���O�֌W���Z�b�g
	this->Msg.clear();					//���g���N���A
	this->Msg.push_back(msg);			//�󂯎�����������ǉ�
	this->Msg_itr = this->Msg.begin();	//�擪�v�f�̃A�h���X���擾
	return;
}

//�������ǉ�
void MESSAGE::AddMsg(const char *msg)
{
	this->Msg.push_back(msg);		//�󂯎�����������ǉ�
	this->Msg_itr = this->Msg.begin();	//�擪�v�f�̃A�h���X���擾
	return;
}

//���̃��b�Z�[�W�ֈړ�����
void MESSAGE::NextMsg(void)
{

	if (this->IsLastMsg || this->Msg.size() == 1)	//�Ō�̃��b�Z�[�W��\�����Ă����� �������́A�v�f��������Ȃ�������i�ŏ��̃��b�Z�[�W���Ō�̃��b�Z�[�W�̏ꍇ)
	{
		this->IsMsgEnd = true;	//���b�Z�[�W�`��I��
	}

	if (*this->Msg_itr != this->Msg.back())			//�Ō�̃��b�Z�[�W�łȂ����
	{
		++this->Msg_itr;	//���̃��b�Z�[�W��
	}
	if(*this->Msg_itr == this->Msg.back())			//�Ō�̃��b�Z�[�W��������
	{
		this->IsLastMsg = true;	//�t���O�𗧂Ă�
	}

	return;
}

//�O�̃��b�Z�[�W�ֈړ�����
void MESSAGE::BackMsg(void)
{
	if (*this->Msg_itr != this->Msg.front())		//�ŏ��̃��b�Z�[�W����Ȃ����
	{
		--this->Msg_itr;	//�O�̃��b�Z�[�W��
	}
}

//���b�Z�[�W�`��
void MESSAGE::DrawMsg(int x, int y,unsigned int color)
{
	DrawFormatString(x, y, color, "%s", this->Msg_itr->c_str());	//���b�Z�[�W�`��
	return;
}

//�Ō�̃��b�Z�[�W���ǂ����擾
bool MESSAGE::GetIsLastMsg(void)
{
	return this->IsLastMsg;
}

//�󂩂ǂ����擾
bool MESSAGE::GetIsEmpty(void)
{
	return this->Msg.empty();
}

//���b�Z�[�W�`��I�����擾
bool MESSAGE::GetIsMsgEnd(void)
{
	return this->IsMsgEnd;
}

//�t���O�֌W���Z�b�g
void MESSAGE::ResetFlg(void)
{
	this->IsLastMsg = false;	//�Ō�̃��b�Z�[�W����Ȃ�
	this->IsMsgEnd = false;		//���b�Z�[�W�I������Ȃ�
	return;
}
