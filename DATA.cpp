//DATA.cpp
//�f�[�^�N���X

//#################### �w�b�_�t�@�C���ǂݍ��� #################
#include "DATA.hpp"

//#################### �N���X��` #########################

//�R���X�g���N�^

DATA::DATA()
{
	return;
}

//�f�X�g���N�^
DATA::~DATA()
{
	return;
}

//�ǂݍ��݁i�G�f�[�^�j
bool DATA::LoadEnemy(ENEMY *enemy[],const char *dir,const char *name)
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

		return false;	//�ǂݍ��ݎ��s

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

			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
			enemy[i]->SetSkil(atoi(buf.c_str()));	//Skil2�ǂݍ���

			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
			enemy[i]->SetEncounteRate(atoi(buf.c_str()));	//�������ǂݍ���

			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
			enemy[i]->SetEmergenceMap(atoi(buf.c_str()));	//�o��MAP�ǂݍ���

			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
			enemy[i]->SetItemCode(atoi(buf.c_str()));	//�h���b�v����A�C�e���R�[�h�ǂݍ���

			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
			enemy[i]->SetWeaponCode(atoi(buf.c_str()));	//�h���b�v���镐��R�[�h�ǂݍ���

			std::getline(ifs, buf, '\n');	//�Ō�͉��s�܂œǂݍ���
			enemy[i]->SetArmorCode(atoi(buf.c_str()));	//�h���b�v����h��R�[�h�ǂݍ���

		}

		return true;	//�ǂݍ��ݐ���

}

//�ǂݍ��݁i���b�Z�[�W�f�[�^�j
bool DATA::LoadMsg(MESSAGE *msg, const char *dir, const char *name)
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

		return false;	//�ǂݍ��ݎ��s

	}


	std::string buf;

		std::getline(ifs, buf);					//1�s�ǂݍ���
		msg->SetMsg(buf.c_str());				//������ǂݍ���

		while (!ifs.eof())	//�Ō�̍s�܂œǂݍ���
		{
			std::getline(ifs, buf);	//1�s�ǂݍ���
			msg->AddMsg(buf.c_str());	//������ǉ�
		}

		return true;	//�ǂݍ��ݐ���

}

//�ǂݍ��݁i���݂̃}�b�v�ʒu�j
bool DATA::LoadNowMap(int *nowmapdrawkind, int *nowmapkind, const char *dir, const char *name)
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

		return false;	//�ǂݍ��ݎ��s

	}

	std::string buf;

	std::getline(ifs, buf, ',');			//�J���}�܂œǂݍ���
	*nowmapdrawkind = atoi(buf.c_str());	//���݂̕`��}�b�v�̎��

	std::getline(ifs, buf, ',');			//���s�܂œǂݍ���
	nowmapkind[0] = atoi(buf.c_str());		//���݂̃}�b�v�̎��
	std::getline(ifs, buf, '\n');			//���s�܂œǂݍ���
	nowmapkind[1] = atoi(buf.c_str());		//���݂̃}�b�v�̎��

	return true;			//�ǂݍ��ݐ���

}

//���݂̃}�b�v�ʒu���Z�[�u
bool DATA::SaveMap(int nowmapdrawkind, int nowmapkind[],const char *dir,const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ofstream ofs(LoadFile.c_str(), std::ios_base::ate);	//�t�@�C���I�[�v��

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

		return false;		//�Z�[�u���s

	}

	//���݂̃}�b�v�ʒu�������o��
	ofs << nowmapdrawkind << ',';		//���݂̕`��}�b�v�̎��
	ofs << nowmapkind[0] << ',' ;		//���݂̃}�b�v�̎��
	ofs << nowmapkind[1] << std::endl;

	return true;		//�Z�[�u����

}
