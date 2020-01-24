//MAPIMAGE.cpp
//�g�p����}�b�v�`�b�v�̃N���X

//######################## �w�b�_�t�@�C���ǂݍ��� #####################
#include "MAPIMAGE.hpp"

//####################### �N���X��` ########################

//�R���X�g���N�^
MAPIMAGE::MAPIMAGE()
{
	//�����o�ϐ�������
	this->FilePath = "";		//�t�@�C���p�X
	this->FileName = "";		//�t�@�C����

	this->IsLoad = false;

	for (int kind = 0; kind < MAP_IMAGE_KIND; kind++)
	{
		for (int i = 0; i < MAP_BUN_TATE * MAP_BUN_YOKO; i++)
		{
			this->Handle[kind][i] = 0;		//�n���h��
			this->X[kind][i] = 0;			//X�ʒu
			this->Y[kind][i] = 0;			//Y�ʒu
			this->Width[kind][i] = 0;		//��
			this->Height[kind][i] = 0;		//����
		}

	}


	for (int kind = 0; kind < MAP_IMAGE_KIND; kind++)
	{
		//�}�b�v�摜��ǂݍ���
		std::string LoadfilePath;		//�摜�̃t�@�C���p�X���쐬
		LoadfilePath += MY_MAP_IMG_DIR;
		LoadfilePath += MY_MAP_IMAGE;

		//�摜�𕪊����ēǂݍ���
		LoadDivGraph(LoadfilePath.c_str(), MAP_BUN_TATE * MAP_BUN_YOKO, MAP_BUN_YOKO, MAP_BUN_TATE, MAP_YOKO_SIZE, MAP_TATE_SIZE, &this->Handle[kind][0]);

		if (this->Handle[kind][0] == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
		{
			std::string ErrorMsg(MAP_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
			ErrorMsg += TEXT('\n');						//���s
			ErrorMsg += LoadfilePath;					//�摜�̃p�X

			MessageBox(
				NULL,
				ErrorMsg.c_str(),	//char * ��Ԃ�
				TEXT(MAP_ERROR_TTILE),
				MB_OK);

			return;
		}

	}

	//�T�C�Y�擾
	for (int kind = 0; kind < MAP_IMAGE_KIND; kind++)
	{
		for (int i = 0; i < MAP_BUN_TATE * MAP_BUN_YOKO; i++)
		{
			GetGraphSize(
				this->Handle[kind][i],	//���̃n���h���̉摜�̑傫�����擾
				&this->Width[kind][i],		//Width�̃A�h���X��n��
				&this->Height[kind][i]		//Height�̃A�h���X��n��
			);

		}

	}
	this->IsLoad = true;
	return;
}

MAPIMAGE::~MAPIMAGE()
{
	for (int kind = 0; kind < MAP_IMAGE_KIND; kind++)
	{
		for (int i = 0; i < MAP_BUN_TATE * MAP_BUN_YOKO; i++)
		{
			DeleteGraph(this->Handle[kind][i]);	//�n���h���폜
		}

	}
	return;
}

int * MAPIMAGE::GetHandle(int kind)
{
	return &this->Handle[kind][0];		//�w�肳�ꂽ�}�b�v�`�b�v�̉摜����Ԃ�
}

bool MAPIMAGE::GetIsLoad(void)
{
	return this->IsLoad;	//�ǂݍ��߂���
}