//ARMOR.hpp
//EQUIPMENT�N���X����h��
//�h����Ǘ�����N���X

#pragma once

//###################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "EQUIPMENT.hpp"

//###################### �}�N����` ###########################

//###################### �N���X��` ###########################
class ARMOR :public EQUIPMENT		//EQUIPMENT�N���X����h��
{
private:

	std::vector<int> Def;		//�h���

public:

	ARMOR();			//�R���X�g���N�^
	~ARMOR();			//�f�X�g���N�^

	void SetDef(int);	//�h��͂�ݒ�
	int GetDef(int);	//�h��͂��擾

};

