/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* ANIMATION.cpp     																			�@ */
/* �A�j���[�V�����N���X 																		�@ */

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "ANIMATION.hpp"

//########## �N���X�̒�` ##########

//�R���X�g���N�^
//�R���X�g���N�^
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
//���@���Fint�F�摜�̑�������
//���@���Fint�F�摜�̉������̕�����
//���@���Fint�F�摜�̏c�����̕�����
//���@���Fint�F�摜�̕������ꂽ���̑傫��
//���@���Fint�F�摜�̕������ꂽ�c�̑傫��
//���@���Fdouble�F���̉摜�ɕύX���鑬��
//���@���Fbool�F�A�j���[�V���������[�v���邩�ǂ���
ANIMATION::ANIMATION(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop,int size)
{
	//�����o�ϐ���������
	this->FilePath = "";	//�p�X
	this->FileName = "";	//���O
	this->Handle.resize(size);

	this->Handle[0].resize(SplitNumALL);			//resize�Fvector�̗v�f����ύX����
	this->Handle_itr = this->Handle[0].begin();		//�擪�̃|�C���^������

	this->ChangeMaxCnt.push_back(SpritNumX);
	this->ChangeCnt.push_back(0);
	this->ChangeCntNow.push_back(0);

	this->IsAnimeLoop.push_back(IsLoop);
	this->IsAnimeStop.push_back(false);

	this->Width.push_back(0);
	this->Height.push_back(0);

	this->IsLoad = false;			//�ǂݍ��߂����H

	//�摜��ǂݍ���
	std::string LoadfilePath;		//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	//�摜�𕪊����ēǂݍ���
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &this->Handle[0][0]);

	if (this->Handle[0][0] == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErrorMsg(ANIMATION_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadfilePath;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(ANIMATION_ERROR_TTILE),
			MB_OK);

		return;
	}

	this->FilePath = LoadfilePath;		//�摜�̃p�X��ݒ�
	this->FileName = name;				//�摜�̖��O��ݒ�

	//GetGraphSize(
	//	this->Handle[0][0],	//���̃n���h���̉摜�̑傫�����擾
	//	&this->Width[0],		//Width�̃A�h���X��n��
	//	&this->Height[0]		//Height�̃A�h���X��n��
	//);

	this->NextChangeSpeed.push_back(changeSpeed);

	this->IsLoad = true;		//�ǂݍ��߂�

	return;
}

//�f�X�g���N�^
ANIMATION::~ANIMATION()
{

	for (int i = 0; i < this->Handle.size(); ++i)
	{
		DeleteGraph(this->Handle[i][0]);
	}


	//vector�̃�����������s��
	std::vector<std::vector<int>> v;			//���vector���쐬����
	this->Handle.swap(v);						//��ƒ��g�����ւ���

	std::vector<int> v2;
	this->Width.swap(v2);

	std::vector<int> v3;
	this->Height.swap(v3);

	std::vector<bool> v4;
	this->IsAnimeLoop.swap(v4);

	std::vector<bool> v5;
	this->IsAnimeStop.swap(v5);

	std::vector<int> v6;
	this->ChangeMaxCnt.swap(v6);

	std::vector<int> v7;
	this->ChangeCnt.swap(v7);

	std::vector<double> v8;
	this->NextChangeSpeed.swap(v8);

	return;
}

//�t�@�C���̖��O���擾
std::string ANIMATION::GetFileName(void)
{
	return this->FileName;
}

//�����擾
int ANIMATION::GetWidth(int type)
{
	return this->Width[type];
}

//�������擾
int ANIMATION::GetHeight(int type)
{
	return this->Height[type];
}

//�ǂݍ��߂��H
bool ANIMATION::GetIsLoad(void)
{
	return this->IsLoad;
}

//�A�j���[�V�����̓X�g�b�v���������擾
bool  ANIMATION::GetIsAnimeStop(int type)
{
	return this->IsAnimeStop[type];
}

//�A�j���[�V�������X�g�b�v�����������Z�b�g
void ANIMATION::ResetIsAnime(int type)
{
	this->IsAnimeStop[type] = false;
	return;
}

//�摜��`��
//�����Fint �FX���W
//�����Fint �FY���W
//�����Fint �F�ړ�����
//�����Fbool�F�A�j���[�V�������邩
void ANIMATION::Draw(int X, int Y,int Dist,bool animetion,int type)
{
	if (animetion)	//�A�j���[�V�����ŕ`�悷��ꍇ
	{
		if (*this->Handle_itr == this->Handle[type][Dist+this->ChangeCnt[type]])
		{
			if (this->ChangeCntNow[type] < this->NextChangeSpeed[type])
			{
				this->ChangeCntNow[type]++;
				DrawGraph(X, Y, *this->Handle_itr, TRUE);	//�`��
			}
			else
			{
				if (this->ChangeCnt[type] < this->ChangeMaxCnt[type] - 1)	//�Ō�̉摜����Ȃ��Ƃ�
				{
					DrawGraph(X, Y, *this->Handle_itr, TRUE);	//�`��
					this->ChangeCnt[type]++; //�J�E���g�A�b�v
					this->Handle_itr++;//���̉摜

				}
				else
				{
					DrawGraph(X, Y, *this->Handle_itr, TRUE);	//�`��
					this->ChangeCnt[type] = 0;	//�J�E���g���Z�b�g
				}
				this->ChangeCntNow[type] = 0;		//�J�E���g���Z�b�g

			}

		}
		else
		{
			DrawGraph(X, Y, *this->Handle_itr, TRUE);	//�`��
			this->Handle_itr = this->Handle[type].begin() + Dist + this->ChangeCnt[type];
		}

	}
	else	//�A�j���[�V�����`�悶��Ȃ��Ƃ�
	{
		this->Handle_itr = this->Handle[type].begin() + Dist + 1;	//�~�܂��Ă���Ƃ��̉摜
		DrawGraph(X, Y, *this->Handle_itr, TRUE);	//�`��
	}
	

	return;
}

//�A�j���[�V�����`��
void ANIMATION::DrawAnime(int x, int y,int type)
{
	if (this->IsAnimeStop[type] == false)	//�A�j���[�V�������X�g�b�v�����Ȃ��Ȃ�
	{
		DrawGraph(x, y, *this->Handle_itr, TRUE);	//�C�e���[�^(�|�C���^)���g�p���ĕ`��
	}
	else
	{
		
	}

	if (this->ChangeCnt[type] == this->NextChangeSpeed[type])	//���̉摜��\�����鎞��������
	{
		//this->Handle.end()�́A�Ō�̗v�f�̂P���̃C�e���[�^��Ԃ��̂ŁA-1���Ă���B
		if (this->Handle_itr == this->Handle[type].end() - 1)	//�C�e���[�^(�|�C���^)���Ō�̗v�f�̂Ƃ���
		{
			//�A�j���[�V���������[�v���Ȃ��Ȃ�
			if (this->IsAnimeLoop[type] == false)
			{
				this->IsAnimeStop[type] = true;	//�A�j���[�V�������~�߂�
			}

			//����̕`��ɔ����āA�擪�̉摜�ɖ߂��Ă���
			this->Handle_itr = this->Handle[type].begin();	//�C�e���[�^(�|�C���^)��v�f�̍ŏ��ɖ߂�
		}
		else
		{
			this->Handle_itr++;	//���̃C�e���[�^(�|�C���^)(���̉摜)�Ɉړ�����
		}

		this->ChangeCnt[type] = 0;	//�J�E���g������
	}
	else
	{
		this->ChangeCnt[type]++;	//�J�E���g�A�b�v
	}

}

//�A�j���[�V�����ǉ�
bool ANIMATION::Add(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop, int type)
{
	this->IsAnimeLoop[type] = IsLoop;		//�A�j���[�V�����̓��[�v����H
	this->IsAnimeStop[type] = false;		//�A�j���[�V�����𓮂���

	//�摜��ǂݍ���
	std::string LoadfilePath;		//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	//�摜�𕪊����ēǂݍ���
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &this->Handle[type][0]);

	if (this->Handle[type][0] == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErrorMsg(ANIMATION_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadfilePath;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(ANIMATION_ERROR_TTILE),
			MB_OK);

		return false;		//�ǂݍ��ݎ��s
	}

	//GetGraphSize(
	//	this->Handle[type][0],	//���̃n���h���̉摜�̑傫�����擾
	//	&this->Width[0],		//Width�̃A�h���X��n��
	//	&this->Height[0]		//Height�̃A�h���X��n��
	//);

	return true;		//�ǂݍ��߂�

}

//�T�C�Y��ݒ肷��
void ANIMATION::SetSize(void)
{
	for (int i = 0; i < this->Handle.size(); ++i)
	{
		GetGraphSize(this->Handle[i][0], &this->Width[i], &this->Height[i]);		//�摜�T�C�Y�擾
	}

	return;
}
