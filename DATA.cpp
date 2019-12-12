//DATA.cpp
//�f�[�^�N���X

//#################### �w�b�_�t�@�C���ǂݍ��� #################
#include "DATA.hpp"

//#################### �N���X��` #########################

/*
�R���X�g���N�^
//�����Fconst char *�F�t�@�C���̃p�X
//�����Fconst char *�F���O
*/
DATA::DATA(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;


	std::ifstream ifs(LoadFile.c_str());	//�t�@�C���ǂݎ��

	if (!ifs)		//�t�@�C���I�[�v�����s��
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadFile;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return;

	}

	//ifs >> this->Text;		//�t�@�C�����烁���o�[�ϐ��Ƀf�[�^���i�[
	std::string buf;
	while (!ifs.eof())			//�t�@�C���̏I�[�܂œǂݍ���
	{
		std::getline(ifs, buf);	//1�s�ǂݍ���
		this->Text += buf + "\n";	//�ǂݍ��񂾃f�[�^���i�[
	}

	return;

}

//�f�X�g���N�^
DATA::~DATA()
{
	return;
}

//�C���v�b�g
template<typename T>
void DATA::Input(T data)
{
	return;
}

//�A�E�g�v�b�g
void DATA::Output(PLAYER *data ,const char *dir,const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;
	
	std::ofstream ofs(LoadFile.c_str());	//�t�@�C���I�[�v��

	if (!ofs)		//�t�@�C���I�[�v�����s��
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadFile;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return;

	}

	//ofs << data << std::endl;		//�A�E�g�v�b�g
	ofs << data->GetHP() << std::endl;

	return;
}

//�`��
void DATA::Draw(int x, int y)
{
	DrawFormatString(x, y, GetColor(255, 255, 255), "%s", this->Text.c_str());	//�����`��
	return;
}
