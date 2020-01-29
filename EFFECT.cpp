//EFFECT.cpp
//�G�t�F�N�g�N���X

//################## �w�b�_�t�@�C���ǂݍ��� ##################
#include "EFFECT.hpp"

//################## �N���X��` #######################

//�R���X�g���N�^
/*
���@���Fconst char *�F�摜�̃f�B���N�g��
���@���Fconst char *�F�摜�̖��O
���@���Fint�F�摜�̑�������
���@���Fint�F�摜�̉������̕�����
���@���Fint�F�摜�̏c�����̕�����
���@���Fint�F�摜�̕������ꂽ���̑傫��
���@���Fint�F�摜�̕������ꂽ�c�̑傫��
���@���Fdouble�F���̉摜�ɕύX���鑬��
���@���Fbool�F�A�j���[�V���������[�v���邩�ǂ���
���@���Fint�F�T�C�Y
*/
EFFECT::EFFECT(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop,int size)
{
	//�����o�ϐ�������
	this->Handle.resize(size);		//�G�t�F�N�g�̎�ސ��ŃT�C�Y�ύX
	this->Width.resize(size);		//�G�t�F�N�g�̎�ސ��ŃT�C�Y�ύX
	this->Height.resize(size);		//�G�t�F�N�g�̎�ސ��ŃT�C�Y�ύX
	this->IsAnimeLoop.resize(size);	//�G�t�F�N�g�̎�ސ��ŃT�C�Y�ύX
	this->IsAnimeStop.resize(size);	//�G�t�F�N�g�̎�ސ��ŃT�C�Y�ύX

	this->Handle[0].resize(SplitNumALL);	//���������ŃT�C�Y�ύX
	this->Handle_itr = this->Handle[0].begin();	//�擪�v�f����

	this->ChangeMaxCnt = (int)(changeSpeed * fps->Getvalue());	//�A�j���[�V��������t���[���̍ő�l
	this->ChangeCnt = 0;	//�A�j���[�V��������t���[���̃J�E���g

	this->IsAnimeLoop[0] = IsLoop;		//�A�j���[�V�����̓��[�v����H
	this->IsAnimeStop[0] = false;		//�A�j���[�V�����𓮂���

	this->IsLoad = false;			//�ǂݍ��߂����H
	this->IsDrawEnd = false;		//�`��I��������?

	//�摜��ǂݍ���
	std::string LoadfilePath;		//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	//�摜�𕪊����ēǂݍ���
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &this->Handle[0][0]);

	if (this->Handle[0][0] == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErrorMsg(EFFECT_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadfilePath;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(EFFECT_ERROR_TTILE),
			MB_OK);

		return;
	}

	GetGraphSize(
		this->Handle[0][0],	//���̃n���h���̉摜�̑傫�����擾
		&this->Width[0],		//Width�̃A�h���X��n��
		&this->Height[0]		//Height�̃A�h���X��n��
	);

	this->NextChangeSpeed = changeSpeed;	//�摜��ς��鑬��

	this->IsLoad = true;		//�ǂݍ��߂�

	return;

}

//�f�X�g���N�^
EFFECT::~EFFECT()
{
	for (int i = 0; i < MAGIC_EFFECT_KIND; ++i)
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

	return;

}

//�����擾
int EFFECT::GetWidth(int type)
{
	return this->Width[type];
}

//�������擾
int EFFECT::GetHeight(int type)
{
	return this->Height[type];
}

//�ǂݍ��߂��H
bool EFFECT::GetIsLoad(void)
{
	return this->IsLoad;
}

//�A�j���[�V�����̓X�g�b�v���������擾
bool  EFFECT::GetIsAnimeStop(int type)
{
	return this->IsAnimeStop[type];
}

//�`��I���������ǂ����擾
bool EFFECT::GetIsDrawEnd()
{
	return this->IsDrawEnd;
}

//�`��I���������ݒ�
void EFFECT::SetIsDrawEnd(bool isend)
{
	this->IsDrawEnd = isend;
	return;
}

//�A�j���[�V�������X�g�b�v�����������Z�b�g
void EFFECT::ResetIsAnime(int type)
{
	this->IsAnimeStop[type] = false;
	this->IsDrawEnd = false;		
	return;
}

//�`��
/*
�����Fint�FX�̕`��ʒu
�����Fint�FY�̕`��ʒu
�����Fint�F�`�悷��G�t�F�N�g�̎��
*/
void EFFECT::Draw(int x, int y,int type)
{


	static int cnt = 0;		//�t�F�[�h�A�E�g�p
	static int cntMax = 60;	//�t�F�[�h�A�E�g�p
	static bool flg = false;//�t�F�[�h�A�E�g�I���t���O

	//60�t���[�����A�҂�
	if (cnt < cntMax)
	{
		cnt++;	//�J�E���g�A�b�v
	}
	else
	{
		flg = true;	//�t�F�[�h�A�E�g�����I��
	}

	//�t�F�[�h�A�E�g�̏���
	double ToukaPercent = cnt / (double)cntMax;//���߁������߂�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * 255);	//���߂�����
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);	//�^���Âȉ�ʂɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//���߂���߂�

	if (flg)		//�t�F�[�h�A�E�g���I�����Ă�����
	{
			if (this->IsAnimeStop[type] == false)	//�A�j���[�V�������X�g�b�v�����Ȃ��Ȃ�
			{
				DrawGraph(x, y, *this->Handle_itr, TRUE);	//�C�e���[�^(�|�C���^)���g�p���ĕ`��
			}
			else
			{
				this->IsDrawEnd = true;		//�`��I��
				flg = false;	//�t�F�[�h�A�E�g�t���O���Z�b�g
				cnt = 0;		//�t�F�[�h�A�E�g�J�E���g���Z�b�g
			}

			if (this->ChangeCnt == this->ChangeMaxCnt)	//���̉摜��\�����鎞��������
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

				this->ChangeCnt = 0;	//�J�E���g������
			}
			else
			{
				this->ChangeCnt++;	//�J�E���g�A�b�v
			}

	}
	else
	{
		this->Handle_itr = this->Handle[type].begin();		//�w�肳�ꂽ�G�t�F�N�g�^�C�v�̃n���h������
	}

	return;

}

//�`��(�ő哧�ߗ����w�肷��)
/*
�����Fint�FX�̕`��ʒu
�����Fint�FY�̕`��ʒu
�����Fint�F�`�悷��G�t�F�N�g�̎��
�����Fint�F�ő哧�ߗ�(0�`100%)
*/
void EFFECT::Draw(int x, int y, int type,int maxtouka)
{

	static int cnt = 0;		//�t�F�[�h�A�E�g�p
	static int cntMax = 60;	//�t�F�[�h�A�E�g�p
	static bool flg = false;//�t�F�[�h�A�E�g�I���t���O

	//60�t���[�����A�҂�
	if (cnt < cntMax)
	{
		cnt++;	//�J�E���g�A�b�v
	}
	else
	{
		flg = true;	//�t�F�[�h�A�E�g�����I��
	}

	//�t�F�[�h�A�E�g�̏���
	double ToukaPercent = (cnt / ( 100 / maxtouka)) / (double)cntMax;//���߁������߂�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * 255);	//���߂�����
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);	//�^���Âȉ�ʂɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//���߂���߂�

	if (flg)		//�t�F�[�h�A�E�g���I�����Ă�����
	{
		if (this->IsAnimeStop[type] == false)	//�A�j���[�V�������X�g�b�v�����Ȃ��Ȃ�
		{
			DrawGraph(x, y, *this->Handle_itr, TRUE);	//�C�e���[�^(�|�C���^)���g�p���ĕ`��
		}
		else
		{
			this->IsDrawEnd = true;		//�`��I��
			flg = false;	//�t�F�[�h�A�E�g�t���O���Z�b�g
			cnt = 0;		//�t�F�[�h�A�E�g�J�E���g���Z�b�g
		}

		if (this->ChangeCnt == this->ChangeMaxCnt)	//���̉摜��\�����鎞��������
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

			this->ChangeCnt = 0;	//�J�E���g������
		}
		else
		{
			this->ChangeCnt++;	//�J�E���g�A�b�v
		}

	}
	else
	{
		this->Handle_itr = this->Handle[type].begin();		//�w�肳�ꂽ�G�t�F�N�g�^�C�v�̃n���h������
	}

	return;

}


//�ǉ�
/*
���@���Fconst char *�F�摜�̃f�B���N�g��
���@���Fconst char *�F�摜�̖��O
���@���Fint�F�摜�̑�������
���@���Fint�F�摜�̉������̕�����
���@���Fint�F�摜�̏c�����̕�����
���@���Fint�F�摜�̕������ꂽ���̑傫��
���@���Fint�F�摜�̕������ꂽ�c�̑傫��
���@���Fdouble�F���̉摜�ɕύX���鑬��
���@���Fbool�F�A�j���[�V���������[�v���邩�ǂ���
���@���Fint�F�ǉ�����G�t�F�N�g�̎��
*/
bool EFFECT::Add(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop, int type)
{
	this->IsAnimeLoop[type] = IsLoop;		//�A�j���[�V�����̓��[�v����H
	this->IsAnimeStop[type] = false;		//�A�j���[�V�����𓮂���

	this->Handle[type].resize(SplitNumALL);	//���������ŃT�C�Y�ύX

	//�摜��ǂݍ���
	std::string LoadfilePath;		//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	//�摜�𕪊����ēǂݍ���
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &this->Handle[type][0]);

	if (this->Handle[type][0] == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErrorMsg(EFFECT_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadfilePath;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(EFFECT_ERROR_TTILE),
			MB_OK);

		return false;		//�ǂݍ��ݎ��s
	}

	GetGraphSize(
		this->Handle[type][0],	//���̃n���h���̉摜�̑傫�����擾
		&this->Width[type],		//Width�̃A�h���X��n��
		&this->Height[type]		//Height�̃A�h���X��n��
	);

	return true;		//�ǂݍ��߂�

}
