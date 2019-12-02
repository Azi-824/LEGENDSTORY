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
ANIMATION::ANIMATION(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	//�����o�ϐ���������
	this->FilePath = "";	//�p�X
	this->FileName = "";	//���O

	this->Handle.resize(SplitNumALL);			//resize�Fvector�̗v�f����ύX����
	this->Handle_itr = this->Handle.begin();	//�擪�̃|�C���^������

	this->ChangeMaxCnt = PLAYER_YOKO_CNT;						//�A�j���[�V��������t���[���̍ő�l
	this->ChangeCnt = 0;										//�A�j���[�V��������t���[���̃J�E���g
	this->ChangeCntMax = 5;
	this->ChangeCntNow = 0;

	this->EffectChangeMaxCnt = (int)(changeSpeed * fps->Getvalue());	//�A�j���[�V��������t���[���̍ő�l
	this->EffectChangeCnt = 0;											//�A�j���[�V��������t���[���̃J�E���g

	this->IsAnimeLoop = IsLoop;		//�A�j���[�V�����̓��[�v����H
	this->IsAnimeStop = false;		//�A�j���[�V�����𓮂���

	this->IsLoad = false;			//�ǂݍ��߂����H

	//�摜��ǂݍ���
	std::string LoadfilePath;		//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	//�摜�𕪊����ēǂݍ���
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &this->Handle[0]);

	if (this->Handle[0] == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
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

	GetGraphSize(
		this->Handle[0],	//���̃n���h���̉摜�̑傫�����擾
		&this->Width,		//Width�̃A�h���X��n��
		&this->Height		//Height�̃A�h���X��n��
	);

	this->NextChangeSpeed = changeSpeed;	//�摜��ς��鑬��

	this->EffectNextChangeSpeed = changeSpeed;	//�摜��ς��鑬��

	this->IsLoad = true;		//�ǂݍ��߂�

	return;
}

//�f�X�g���N�^
ANIMATION::~ANIMATION()
{
	//�͈̓x�[�X�� for ���[�v
	//vector�Ȃǂ̃R���e�i�N���X�Ŏg�p�ł���
	//auto�F�^���_�F�R���p�C���������l���琄�_���Č^�����߂Ă����
	for (int handle : this->Handle)
	{
		DeleteGraph(handle);
	}

	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Handle.swap(v);		//��ƒ��g�����ւ���

	return;
}

//�t�@�C���̖��O���擾
std::string ANIMATION::GetFileName(void)
{
	return this->FileName;
}

//�����擾
int ANIMATION::GetWidth(void)
{
	return this->Width;
}

//�������擾
int ANIMATION::GetHeight(void)
{
	return this->Height;
}

//�ǂݍ��߂��H
bool ANIMATION::GetIsLoad(void)
{
	return this->IsLoad;
}

//�A�j���[�V�����̓X�g�b�v���������擾
bool  ANIMATION::GetIsAnimeStop(void)
{
	return this->IsAnimeStop;
}

//�摜��`��
//�����Fint �FX���W
//�����Fint �FY���W
//�����Fint �F�ړ�����
//�����Fbool�F�A�j���[�V�������邩
void ANIMATION::Draw(int X, int Y,int Dist,bool animetion)
{
	if (animetion)	//�A�j���[�V�����ŕ`�悷��ꍇ
	{
		if (*this->Handle_itr == this->Handle[Dist+ChangeCnt])
		{
			if (this->ChangeCntNow < this->ChangeCntMax)
			{
				this->ChangeCntNow++;
				DrawGraph(X, Y, *this->Handle_itr, TRUE);	//�`��
			}
			else
			{
				if (this->ChangeCnt < this->ChangeMaxCnt - 1)	//�Ō�̉摜����Ȃ��Ƃ�
				{
					DrawGraph(X, Y, *this->Handle_itr, TRUE);	//�`��
					this->ChangeCnt++; //�J�E���g�A�b�v
					this->Handle_itr++;//���̉摜

				}
				else
				{
					DrawGraph(X, Y, *this->Handle_itr, TRUE);	//�`��
					this->ChangeCnt = 0;	//�J�E���g���Z�b�g
				}
				this->ChangeCntNow = 0;		//�J�E���g���Z�b�g

			}

		}
		else
		{
			DrawGraph(X, Y, *this->Handle_itr, TRUE);	//�`��
			this->Handle_itr = this->Handle.begin() + Dist + ChangeCnt;
		}

	}
	else	//�A�j���[�V�����`�悶��Ȃ��Ƃ�
	{
		DrawGraph(X, Y, *this->Handle_itr, TRUE);	//�`��
	}
	

	return;
}

//�G�t�F�N�g��`��
void ANIMATION::DrawEffect(int x, int y)
{
		if (this->IsAnimeStop == false)	//�A�j���[�V�������X�g�b�v�����Ȃ��Ȃ�
		{
			DrawGraph(x, y, *this->Handle_itr, TRUE);	//�C�e���[�^(�|�C���^)���g�p���ĕ`��
		}

	if (this->EffectChangeCnt == this->EffectChangeMaxCnt)	//���̉摜��\�����鎞��������
	{
		//this->Handle.end()�́A�Ō�̗v�f�̂P���̃C�e���[�^��Ԃ��̂ŁA-1���Ă���B
		if (this->Handle_itr == this->Handle.end() - 1)	//�C�e���[�^(�|�C���^)���Ō�̗v�f�̂Ƃ���
		{
			//�A�j���[�V���������[�v���Ȃ��Ȃ�
			if (this->IsAnimeLoop == false)
			{
				this->IsAnimeStop = true;	//�A�j���[�V�������~�߂�
			}

			//����̕`��ɔ����āA�擪�̉摜�ɖ߂��Ă���
			this->Handle_itr = this->Handle.begin();	//�C�e���[�^(�|�C���^)��v�f�̍ŏ��ɖ߂�
		}
		else
		{
			this->Handle_itr++;	//���̃C�e���[�^(�|�C���^)(���̉摜)�Ɉړ�����
		}

		this->EffectChangeCnt = 0;	//�J�E���g������
	}
	else
	{
		this->EffectChangeCnt++;	//�J�E���g�A�b�v
	}
	return;
}
