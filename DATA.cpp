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
bool DATA::LoadPlayer(PLAYER *player,const char *dir,const char *name)
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

	return true;	//�ǂݍ��ݐ���
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

			std::getline(ifs, buf, '\n');	//�Ō�͉��s�܂œǂݍ���
			enemy[i]->SetEmergenceMap(atoi(buf.c_str()));	//�o��MAP�ǂݍ���

		}

		return true;	//�ǂݍ��ݐ���

}

//�Z�[�u
bool DATA::Save(PLAYER *player ,const char *dir,const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;
	
	std::ofstream ofs(LoadFile.c_str(),std::ios_base::ate);	//�t�@�C���I�[�v��

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

	//�v���C���[���������o��
	ofs << player->GetName() << ',';		//���O�����o��
	ofs << player->GetLevel() << ',';		//���x��
	ofs << player->GetMaxEXP() << ',';		//�o���l�̍ő�l
	ofs << player->GetEXP() << ',';			//���݂̌o���l

	ofs << player->GetMaxHP() << ',';		//�ő�HP
	ofs << player->GetHP() << ',';			//���݂�HP
	ofs << player->GetMaxMP() << ',';		//�ő�MP
	ofs << player->GetMP() << ',' ;			//���݂�MP

	ofs << player->GetATK() << ',';			//�U����
	ofs << player->GetDEF() << ',';			//�h���
	ofs << player->GetSPD() << ',';			//����

	std::vector<int> skil = player->GetSkil();	//�X�L���ꗗ���擾

	for (int i = 0; i < skil.size(); ++i)		//�X�L���̐�����������
	{

		ofs << skil[i];					//�X�L����������

		if (i != skil.size() - 1)		//�Ō�̗v�f����Ȃ��Ƃ���
		{
			ofs << ',';			//�J���}�ŋ�؂�
		}
		else					//�Ō�̗v�f�̎���
		{
			ofs << std::endl;	//���s
		}
	}

	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	skil.swap(v);				//��ƒ��g�����ւ���

	return true;		//�Z�[�u����
}
