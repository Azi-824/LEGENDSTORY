//MAP.cpp
//�}�b�v�N���X

//################## �w�b�_�t�@�C���ǂݍ��� #####################
#include "MAP.hpp"

//################## �N���X��` #####################
//�R���X�g���N�^
MAP::MAP()
{
	//�����o�ϐ�������
	this->FilePath = "";		//�t�@�C���p�X
	this->FileName = "";		//�t�@�C����

	for (int i = 0; i < MAP_BUN_TATE * MAP_BUN_YOKO; i++)
	{
		this->Handle[i] = 0;	//�n���h��
		this->X[i] = 0;			//X�ʒu
		this->Y[i] = 0;			//Y�ʒu
		this->Width[i] = 0;		//��
		this->Height[i] = 0;	//����
	}

	for (int tate = 0; tate < MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO; yoko++)
		{
			MapData[tate][yoko] = 0;	//�}�b�v�f�[�^
		}
	}

	//�}�b�v�摜��ǂݍ���
	std::string LoadfilePath;		//�摜�̃t�@�C���p�X���쐬
	LoadfilePath += MY_MAP_IMG_DIR;
	LoadfilePath += MY_MAP_IMAGE;

	//�摜�𕪊����ēǂݍ���
	LoadDivGraph(LoadfilePath.c_str(), MAP_BUN_TATE * MAP_BUN_YOKO, MAP_BUN_YOKO, MAP_BUN_TATE, MAP_YOKO_SIZE, MAP_TATE_SIZE, &this->Handle[0]);

	if (this->Handle[0] == -1)	//�摜���ǂݍ��߂Ȃ������Ƃ�
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

	for (int i = 0; i < MAP_BUN_TATE * MAP_BUN_YOKO; i++)
	{
		GetGraphSize(
			this->Handle[0],	//���̃n���h���̉摜�̑傫�����擾
			&this->Width[0],		//Width�̃A�h���X��n��
			&this->Height[0]		//Height�̃A�h���X��n��
		);

	}
	return;
}

//�f�X�g���N�^
MAP::~MAP()
{
	for (int i = 0; i < MAP_BUN_TATE * MAP_BUN_YOKO; i++)
	{
		DeleteGraph(this->Handle[i]);	//�n���h���폜
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

//�`��
void MAP::Draw()
{
	for (int tate = 0; tate < MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO; yoko++)
		{
			DrawGraph(yoko*MAP_YOKO_SIZE, tate*MAP_TATE_SIZE, this->Handle[this->MapData[tate][yoko]], TRUE);	//�}�b�v�`��
		}
	}

	return;
}
