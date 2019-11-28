//MAP.cpp
//�}�b�v�N���X

//################## �w�b�_�t�@�C���ǂݍ��� #####################
#include "MAP.hpp"

//################## �N���X��` #####################
//�R���X�g���N�^
MAP::MAP()
{
	return;
}

//�f�X�g���N�^
MAP::~MAP()
{
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

	//this->MapNow = MAP_1;		//1�}�b�v�ڂ����݂̃}�b�v�Ɏw��

	return true;

}

////���݂̃}�b�v���擾
//int MAP::GetMapNow()
//{
//	this->MapNow;
//}

//�}�b�v��؂�ւ���
void MAP::ChengeMap(PLAYER *player,int *mapnowpos)
{
	COLLISION *player_collision = player->GetCollision();	//�v���C���[�̓����蔻����擾

	if (player_collision->Bottom >= GAME_HEIGHT)	//��ʂ̉��ɗ�����
	{
		if ((mapnowpos[1]) < MAP_DATA_TATE_KIND - 1)	//���̃}�b�v������ꍇ��
		{
			(mapnowpos[1])++;	//���̃}�b�v��
			player->SetPosition(0, -(player_collision->Top - 5));	//�ʒu���C��
		}
	}
	else if (player_collision->Top <= GAME_TOP)		//��ʂ̏�ɗ�����
	{
		if ((mapnowpos[1]) > 0)	//��̃}�b�v������ꍇ��
		{
			(mapnowpos[1])--;	//��̃}�b�v��
			player->SetPosition(0, GAME_HEIGHT- (player_collision->Height + 5));	//�ʒu���C��
		}

	}
	else if (player_collision->Right >= GAME_WIDTH)	//��ʂ̉E�ɗ�����
	{
		if ((mapnowpos[0]) + MAP_DATA_TATE_KIND <= MAP_DATA_KIND - 1)	//���Ƀ}�b�v������ꍇ��
		{
			(mapnowpos[0]) += MAP_DATA_TATE_KIND;	//�E�̃}�b�v��
			player->SetPosition(-(player_collision->Left - 5), 0);	//�ʒu���C��
		}
	}
	else if (player_collision->Left <= GAME_LEFT)		//��ʂ̍��ɗ�����
	{
		if ((mapnowpos[0]) - MAP_DATA_TATE_KIND >= 0)			//���̃}�b�v������ꍇ��
		{
			(mapnowpos[0]) -= MAP_DATA_TATE_KIND;	//���̃}�b�v��
			player->SetPosition(GAME_WIDTH - (player_collision->Width + 5), 0);	//�ʒu���C��
		}
	}
	return;
}

//�`��
void MAP::Draw(int *handle)
{
	for (int tate = 0; tate < MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO; yoko++)
		{
			DrawGraph(yoko*MAP_YOKO_SIZE, tate*MAP_TATE_SIZE, handle[this->MapData[tate][yoko]], TRUE);	//�}�b�v�`��
		}
	}

	return;
}
