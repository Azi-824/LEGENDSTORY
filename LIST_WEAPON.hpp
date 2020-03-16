//LIST_WEAPON.hpp
//���X�g�N���X�̔h��
//����̈ꗗ���Ǘ�����N���X

#pragma once

//################# �w�b�_�t�@�C���ǂݍ��� ##################
#include "LIST.hpp"

//################# �}�N����` ###################
#define WEAPON_LIST_NAME	R"(weapon_list.csv)"		//����ꗗ�̃t�@�C����

//################# �N���X��` ###################
class LIST_WEAPON :public LIST		//���X�g�N���X����h��
{
private:

	std::vector<int> Power;			//����̍U����

public:

	LIST_WEAPON(const char *,const char *);		//�R���X�g���N�^
	~LIST_WEAPON();								//�f�X�g���N�^

	int GetPower(int);			//�U���͎擾
	std::vector<int> GetPower();//�U���͎擾(�S��)

};
