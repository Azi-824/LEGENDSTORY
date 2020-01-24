//MAP.cpp
//�}�b�v�N���X

//################## �w�b�_�t�@�C���ǂݍ��� #####################
#include "MAP.hpp"

//################## �N���X��` #####################
//�R���X�g���N�^
MAP::MAP(const char *dir,const char *name)
{

	this->Map_Image = new IMAGE(dir, name);	//�}�b�v�摜�쐬

	for (int tate = 0; tate < MAP_TATE; ++tate)
	{
		for (int yoko = 0; yoko < MAP_YOKO; ++yoko)
		{
			this->RectOK[tate][yoko] = new COLLISION();	//�����蔻��̗̈���쐬(�ʍs�ł���)
			this->RectNG[tate][yoko] = new COLLISION();	//�����蔻��̗̈���쐬(�ʍs�ł��Ȃ�)

			//�����蔻�菉����
			this->RectOK[tate][yoko]->SetValue(0, 0, MAP_YOKO_SIZE, MAP_TATE_SIZE);

			this->RectNG[tate][yoko]->SetValue(0, 0, MAP_YOKO_SIZE, MAP_TATE_SIZE);

		}
	}
	return;
}

//�f�X�g���N�^
MAP::~MAP()
{
	for (int tate = 0; tate < MAP_TATE; ++tate)
	{
		for (int yoko = 0; yoko < MAP_YOKO; ++yoko)
		{
			delete this->RectOK[tate][yoko];	//�����蔻���j��(�ʍs�ł���)
			delete this->RectNG[tate][yoko];	//�����蔻���j��(�ʍs�ł��Ȃ�)
		}
	}

	return;
}

//csv�t�@�C����ǂݍ���
//�����Fconst char * �}�b�vcsv�̃t�@�C����
//�����Fconst char * �}�b�vcsv�̖��O
bool MAP::LoadCsv(const char *dir, const char *name)
{

	std::string LoadFilePath;
	LoadFilePath += dir;
	LoadFilePath += name;

	if ((this->fp_map_csv = fopen(LoadFilePath.c_str(), "r")) == NULL)		//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	{
		return false;//�ُ�I��
	}

	//�������琳��ɓǂݍ��߂��Ƃ��̏���****************************************

	int result = 0;			//�t�@�C���̍Ōォ�`�F�b�N
	int LoopCnt = 0;		//���[�v�J�E���^

	while (result != EOF)		//EOF End Of File(�t�@�C���̍Ō�)�ł͂Ȃ��Ƃ��J��Ԃ�
	{
		//�t�@�C�����琔�l����ǂݍ���(%d,)�A�z��Ɋi�[����
		result = fscanf(this->fp_map_csv, "%d,", &this->MapData[LoopCnt / MAP_YOKO][LoopCnt % MAP_YOKO]);

		LoopCnt++;
	}

	fclose(this->fp_map_csv);	//�t�@�C�������

	this->FilePath = LoadFilePath;
	this->FileName = name;

	return true;

}

//�}�b�v��؂�ւ���
//�����Fint	  �F�}�b�v�؂�ւ��̎��
//�����Fint	�@�F���݂̃}�b�v��X���W��Y���W�̏��
int MAP::ChengeMap(int kind,int *mapnowpos)
{

	switch (kind)	//�}�b�v�ύX�̎��
	{

	case (int)MAP_CHENGE_UP:	//��֐؂�ւ���Ƃ��A��������

		if ((mapnowpos[POS_Y]) > 0)	//��̃}�b�v������ꍇ��
		{
			mapnowpos[POS_Y]--;	//��̃}�b�v��

			return (int)MAP_CHENGE_UP;//�؂�ւ������A��
		}

		break;	//��֐؂�ւ���Ƃ��A�����܂�

	case (int)MAP_CHENGE_DOWN:	//���֐؂�ւ���Ƃ��A��������

		if ((mapnowpos[POS_Y]) < MAP_DATA_TATE_KIND - 1)	//���̃}�b�v������ꍇ��
		{
			mapnowpos[POS_Y]++;	//���̃}�b�v��

			return (int)MAP_CHENGE_DOWN;	//�؂�ւ������A��
		}

		break;	//���֐؂�ւ���Ƃ��A�����܂�

	case (int)MAP_CHENGE_LEFT:	//���֐؂�ւ���Ƃ��A��������

		if ((mapnowpos[POS_X]) - (MAP_DATA_TATE_KIND - 1) >= 0)			//���̃}�b�v������ꍇ��
		{
			(mapnowpos[POS_X]) -= (MAP_DATA_TATE_KIND - 1);	//���̃}�b�v��

			return (int)MAP_CHENGE_LEFT;	//�؂�ւ������A��
		}

		break;	//���֐؂�ւ���Ƃ��A�����܂�

	case (int)MAP_CHENGE_RIGHT:	//�E�֐؂�ւ���Ƃ��A��������

		if ((mapnowpos[POS_X]) + MAP_DATA_TATE_KIND <= MAP_DATA_TATE_KIND)	//���Ƀ}�b�v������ꍇ��
		{
			(mapnowpos[POS_X]) += (MAP_DATA_TATE_KIND - 1);	//�E�̃}�b�v��

			return (int)MAP_CHENGE_RIGHT;	//�؂�ւ������A�E
		}

		break;	//�E�֐؂�ւ���Ƃ��A�����܂�

	default:
		break;
	}

	return (int)MAP_CHENGE_NONE;	//�؂�ւ��Ȃ�
}

//�`��
//�����Fint *�F�`�悵�����}�b�v�̃}�b�v�`�b�v�̃n���h��
void MAP::Draw(int *handle)
{
	//for (int tate = 0; tate < MAP_TATE; tate++)
	//{
	//	for (int yoko = 0; yoko < MAP_YOKO; yoko++)
	//	{
	//		DrawGraph(yoko*MAP_YOKO_SIZE, tate*MAP_TATE_SIZE, handle[this->MapData[tate][yoko]], TRUE);	//�}�b�v�`��
	//	}
	//}

	this->Map_Image->Draw(0, 0);

	return;
}

//�����蔻��̗̈���쐬
/*
�����Fint *�F�ʍs�ł���}�b�v�̃i���o�[
�����Fint *�F�ʍs�ł��Ȃ��}�b�v�̃i���o�[
*/
void MAP::CreateRect(int *ok_kind,int *ng_kind)
{
	for (int tate = 0; tate < MAP_TATE; ++tate)
	{
		for (int yoko = 0; yoko < MAP_YOKO; ++yoko)
		{

			//�����蔻��̗̈���쐬(�ʍs�ł���)
			for (int cnt = 0; cnt < MAP_OK_KIND; ++cnt)
			{
				if (this->MapData[tate][yoko] == ok_kind[cnt])
				{
					this->RectOK[tate][yoko]->Left = yoko * this->RectOK[tate][yoko]->Width;
					this->RectOK[tate][yoko]->Top = tate * this->RectOK[tate][yoko]->Height;
					this->RectOK[tate][yoko]->Right = (yoko + 1) * this->RectOK[tate][yoko]->Width;
					this->RectOK[tate][yoko]->Bottom = (tate + 1)*this->RectOK[tate][yoko]->Height;

				}
			}

			//�����蔻��̗̈���쐬(�ʍs�ł��Ȃ�)
			for (int cnt = 0; cnt < MAP_NG_KIND; ++cnt)
			{
				if (this->MapData[tate][yoko] == ng_kind[cnt])
				{
					this->RectNG[tate][yoko]->Left = yoko * this->RectOK[tate][yoko]->Width;
					this->RectNG[tate][yoko]->Top = tate * this->RectOK[tate][yoko]->Height;
					this->RectNG[tate][yoko]->Right = (yoko + 1) * this->RectOK[tate][yoko]->Width;
					this->RectNG[tate][yoko]->Bottom = (tate + 1)*this->RectOK[tate][yoko]->Height;
				}
			}

		}
	}

	return;

}
