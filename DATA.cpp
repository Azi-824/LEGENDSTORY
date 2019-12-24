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
DATA::DATA()
{
	return;
}

//�f�X�g���N�^
DATA::~DATA()
{
	return;
}

//�ǂݍ���(�����̃f�[�^)
void DATA::Load(PLAYER *player,const char *dir,const char *name)
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


	std::string buf;
	//1�s�ڂ�ǂݍ���Ŕ�΂�
	std::getline(ifs, buf);	//1�s�ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		player->SetName(buf.c_str());	//���O�ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		player->SetLevel(atoi(buf.c_str()));	//���x���ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		player->SetMaxEXP(atoi(buf.c_str()));	//�o���l�̍ő�l�ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		player->SetEXP(atoi(buf.c_str()));	//���݂̌o���l�ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		player->SetMaxHP(atoi(buf.c_str()));	//�ő�HP�ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		player->SetHP(atoi(buf.c_str()));	//���݂�HP�ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		player->SetMaxMP(atoi(buf.c_str()));	//�ő�MP�ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		player->SetMP(atoi(buf.c_str()));	//���݂�MP�ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		player->SetATK(atoi(buf.c_str()));	//ATK�ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		player->SetDEF(atoi(buf.c_str()));	//DEF�ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		player->SetSPD(atoi(buf.c_str()));	//SPD�ǂݍ���

		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		player->SetSkil(atoi(buf.c_str()));	//Skil1�ǂݍ���

		std::getline(ifs, buf, '\n');	//�Ō�͉��s�܂œǂݍ���
		player->SetSkil(atoi(buf.c_str()));	//Skil2�ǂݍ���

	return;
}

//�ǂݍ��݁i�G�f�[�^�j
void DATA::Load(ENEMY *enemy[],const char *dir,const char *name)
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


	std::string buf;
	//1�s�ڂ�ǂݍ���Ŕ�΂�
	std::getline(ifs, buf);	//1�s�ǂݍ���

		for (int i = 0; i < ENEMY_KIND; ++i)				//�G�̎�ޕ��ǂݍ���
		{
			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
			enemy[i]->SetName(buf.c_str());	//���O�ǂݍ���

			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
			enemy[i]->SetMaxHP(atoi(buf.c_str()));	//HP�ǂݍ���

			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
			enemy[i]->SetATK(atoi(buf.c_str()));	//ATK�ǂݍ���

			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
			enemy[i]->SetDEF(atoi(buf.c_str()));	//DEF�ǂݍ���

			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
			enemy[i]->SetSPD(atoi(buf.c_str()));	//SPD�ǂݍ���

			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
			enemy[i]->SetEXP(atoi(buf.c_str()));	//EXP�ǂݍ���
			
			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
			enemy[i]->SetSkil(atoi(buf.c_str()));	//Skil1�ǂݍ���

			std::getline(ifs, buf, '\n');	//�Ō�͉��s�܂œǂݍ���
			enemy[i]->SetSkil(atoi(buf.c_str()));	//Skil2�ǂݍ���

		}

	return;


}

//�Z�[�u
void DATA::Save(PLAYER *data ,const char *dir,const char *name)
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
