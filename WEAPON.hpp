//WEAPON.hpp
//EQUIPMENT�N���X�̔h��
//�����̒��̕�����Ǘ�����N���X

#pragma once

//################ �w�b�_�t�@�C���ǂݍ��� #################
#include "EQUIPMENT.hpp"

//################ �}�N����` ####################

//################ �N���X��` ####################
class WEAPON :public EQUIPMENT	//EQUIPMENT�N���X���p��
{
private:

	std::vector<int> Atk;		//����̍U����

public:

	WEAPON();					//�R���X�g���N�^
	~WEAPON();					//�f�X�g���N�^

	void SetAtk(int);			//�U���͂�ݒ�

	int GetAtk(int);			//�U���͂��擾

};
