//NPC.cpp
//NPC���Ǘ�����N���X

//################### �w�b�_�t�@�C���ǂݍ��� #######################
#include "NPC.hpp"

//################### �N���X��` ####################

//�R���X�g���N�^
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
NPC::NPC(const char *dir, const char *name)
{
	this->ImageIsLoad = false;	//�ǂݍ��߂���������

	this->Image = new IMAGE(dir, name);				//NPC�摜�̐����i�ǂݍ��݁j
	this->ImageIsLoad = this->Image->GetIsLoad();	//�ǂݍ��߂����ݒ�

	//this->Text = new MESSAGE();						//�e�L�X�g����(������̐ݒ�́ANPC�f�[�^�ǂݍ��݂ōs��)

	return;

}

//�f�X�g���N�^
NPC::~NPC()
{
	delete this->Image;	//Image�j��
	//delete this->Text;	//Text�j��

	//vector�̃�����������s��
	std::vector<std::string> v;		//���vector���쐬����
	this->Name.swap(v);				//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<int> v2;			//���vector���쐬����
	this->DrawMapKind.swap(v2);		//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<int> v3;			//���vector���쐬����
	this->Draw_X.swap(v3);			//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<int> v4;			//���vector���쐬����
	this->Draw_X.swap(v4);			//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<int> v5;			//���vector���쐬����
	this->Draw_Y.swap(v5);			//��ƒ��g�����ւ���

	return;

}

//�摜��ǂݍ��߂����擾
bool NPC::GetImageIsLoad(void)
{
	return this->ImageIsLoad;
}

//�w�肳�ꂽNPC��`�悷��
void NPC::DrawNPC(int kind)
{
	this->Image->Draw(this->Draw_X[kind], this->Draw_Y[kind], kind);	//NPC�`��
	return;
}

//NPC�f�[�^��ǂݍ���
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
bool NPC::Load(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ifstream ifs(LoadFile.c_str());	//�t�@�C���ǂݎ��

	if (!ifs)		//�t�@�C���I�[�v�����s��
	{
		std::string ErrorMsg(NPC_DATA_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadFile;						//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(NPC_DATA_ERROR_TTILE),
			MB_OK);

		return false;	//�ǂݍ��ݎ��s

	}

	std::string buf;
	//1�s�ڂ�ǂݍ���Ŕ�΂�
	std::getline(ifs, buf);	//1�s�ǂݍ���

	while (!ifs.eof())	//�Ō�̍s�܂œǂݍ���
	{

		std::getline(ifs, buf, ',');						//�J���}�܂œǂݍ���

		if (buf.empty())	//�ǂݎ�������e���󂾂�����
		{
			break;	//�ǂݎ�菈���I��
		}

		this->Name.push_back(buf.c_str());					//���O�ݒ�

		std::getline(ifs, buf, ',');						//�J���}�܂œǂݍ���
		this->DrawMapKind.push_back(atoi(buf.c_str()));		//�`��}�b�v�̎�ނ�ݒ�

		std::getline(ifs, buf, ',');						//�J���}�܂œǂݍ���
		this->DrawMap_Num.push_back(atoi(buf.c_str()));		//�`��}�b�v�ԍ���ݒ�

		std::getline(ifs, buf, ',');						//�J���}�܂œǂݍ���
		this->Draw_X.push_back(atoi(buf.c_str()));			//�`��X�ʒu��ݒ�

		std::getline(ifs, buf, '\n');						//�Ō�͉��s�܂œǂݍ���
		this->Draw_Y.push_back(atoi(buf.c_str()));			//�`��Y�ʒu��ݒ�

	}

	return true;

}
