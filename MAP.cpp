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

	return true;

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
