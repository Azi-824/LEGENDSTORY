/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* IMAGE.cpp     																				�@ */
/*       																						�@ */

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "IMAGE.hpp"

//########## �N���X�̒�` ##########

//�R���X�g���N�^
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
IMAGE::IMAGE(const char *dir,const char *name)
{
	//�����o�ϐ���������
	this->FilePath = "";	//�p�X
	this->FileName = "";	//���O
	
	//*this->Handle_itr= -1;	//�n���h��

	this->Handle.push_back(-1);		//�n���h��

	this->Width.push_back(0);		//����������
	this->Height.push_back(0);		//������������

	this->Handle_itr = this->Handle.begin();	//�n���h���̐擪�A�h���X

	this->ImageKind = 0;	//�ǂݍ��񂾉摜�̎��

	this->IsLoad = false;	//�ǂݍ��߂����H

	//�摜��ǂݍ���
	std::string LoadfilePath;	//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	*this->Handle_itr = LoadGraph(LoadfilePath.c_str());	//�摜��ǂݍ���
	
	if (*this->Handle_itr == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErroeMsg(IMAGE_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErroeMsg += TEXT('\n');					//���s
		ErroeMsg += LoadfilePath;				//�摜�̃p�X

		MessageBox(
			NULL, 
			ErroeMsg.c_str(),	//char * ��Ԃ�
			TEXT(IMAGE_ERROR_TITLE),
			MB_OK);

		return;
	}

	this->FilePath = LoadfilePath;		//�摜�̃p�X��ݒ�
	this->FileName = name;				//�摜�̖��O��ݒ�

	GetGraphSize(
		*this->Handle_itr,	//���̃n���h���̉摜�̑傫�����擾
		this->Width.data(),		//Width�̃A�h���X��n��
		this->Height.data()		//Height�̃A�h���X��n��
	);

	this->Width_itr = this->Width.begin();		//�����̐擪�A�h���X
	this->Height_itr = this->Height.begin();	//�����̐擪�A�h���X

	this->IsLoad = true;		//�ǂݍ��߂�

	this->ImageKind = this->Handle.size();	//�ǂݍ��񂾐����擾

	return;
}

//�f�X�g���N�^
IMAGE::~IMAGE()
{
	for (int handle : this->Handle)
	{
		DeleteGraph(handle);		//�ǂݍ��񂾉摜���폜
	}

	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Handle.swap(v);		//��ƒ��g�����ւ���

	std::vector<int>v2;
	this->Width.swap(v2);

	std::vector<int>v3;
	this->Height.swap(v3);

	return;
}

//�t�@�C���̖��O���擾
std::string IMAGE::GetFileName(void)
{
	return this->FileName;
}

//�T�C�Y��ݒ肷��
void IMAGE::SetSize(void)
{
	//�摜�̐��������[�v����
	for (int i = 0; i < this->Handle.size(); ++i)
	{
		GetGraphSize(this->Handle[i], &this->Width[i], &this->Height[i]);	//�摜�T�C�Y�擾
	}
	return;
}

//�����擾
int IMAGE::GetWidth(int kind)
{
	return this->Width[kind];
}

//�������擾
int IMAGE::GetHeight(int kind)
{
	return this->Height[kind];
}

//�����擾�i�����Ȃ��j
int IMAGE::GetWidth()
{
	return this->Width.front();
}

//�������擾�i�����Ȃ��j
int IMAGE::GetHeight()
{
	return this->Height.front();
}


//�ǂݍ��߂��H
bool IMAGE::GetIsLoad(void)
{
	return this->IsLoad;
}

//�摜��`��
void IMAGE::Draw(int X,int Y)
{
	DrawGraph(X, Y, *this->Handle_itr, TRUE);	//�`��

	return;
}

//�摜��`��i�w�肳�ꂽ�j
void IMAGE::Draw(int x, int y, int type)
{
	DrawGraph(x, y, this->Handle[type], TRUE);	//�w�肳�ꂽ�摜��`��
}

//�摜��ǉ�
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
bool IMAGE::AddImage(const char *dir, const char *name,int type)
{

	this->IsLoad = false;	//�ǂݍ��߂Ă��Ȃ�

	//�摜��ǂݍ���
	std::string LoadfilePath;	//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	//�V�����摜������ꏊ��������
	this->Handle.push_back(-1);	
	this->Width.push_back(0);
	this->Height.push_back(0);

	this->Handle_itr = this->Handle.end() -1;	//�Ō�̗v�f

	*this->Handle_itr= LoadGraph(LoadfilePath.c_str());	//�摜��ǂݍ���

	if (*this->Handle_itr == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErroeMsg(IMAGE_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErroeMsg += TEXT('\n');					//���s
		ErroeMsg += LoadfilePath;				//�摜�̃p�X

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * ��Ԃ�
			TEXT(IMAGE_ERROR_TITLE),
			MB_OK);

		return false;
	}

	//GetGraphSize(
	//	*this->Handle_itr,	//���̃n���h���̉摜�̑傫�����擾
	//	this->Width.data(),		//Width�̃A�h���X��n��
	//	this->Height.data()		//Height�̃A�h���X��n��
	//);

	GetGraphSize(
		*this->Handle_itr,	//���̃n���h���̉摜�̑傫�����擾
		&this->Width[type],		//Width�̃A�h���X��n��
		&this->Height[type]		//Height�̃A�h���X��n��
	);




	this->IsLoad = true;		//�ǂݍ��߂�

	this->ImageKind = this->Handle.size();	//�ǂݍ��񂾐����擾

	this->Handle_itr = this->Handle.begin();	//�n���h�����ŏ��ɖ߂�
	this->Width_itr = this->Width.begin();		//�����̐擪�A�h���X
	this->Height_itr = this->Height.begin();	//�����̐擪�A�h���X

	return true;

}

//�`�悷��摜��ύX����
void IMAGE::ChengeImage(int kind)
{
	this->Handle_itr = this->Handle.begin() + kind;	//�w�肳�ꂽ�摜�ɕύX
	this->Width_itr = this->Width.begin() + kind;	//�w�肳�ꂽ�摜�ɕύX
	this->Height_itr = this->Height.begin() + kind;//�w�肳�ꂽ�摜�ɕύX
	return;
}
