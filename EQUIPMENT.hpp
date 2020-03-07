//EQUIPMENT.hpp
//�����֌W�̌��ɂȂ�N���X

#pragma once

//##################### �w�b�_�t�@�C���ǂݍ��� #######################
#include "DxLib.h"
#include <vector>
#include <string>

//##################### �}�N����` #########################

//##################### �N���X��` #########################
class EQUIPMENT
{
private:

	//std::vector<std::string> Name;			//������
	std::vector<int> CodeNum;				//�R�[�h�ԍ�
	std::vector<int> PossessionNum;			//�����̏�����
	std::vector<bool> EquipFlg;				//�������Ă��邩�ǂ���
	int Size;								//�v�f��
	//std::vector<std::string> Description;	//������

public:

	EQUIPMENT();							//�R���X�g���N�^
	~EQUIPMENT();							//�f�X�g���N�^

	//�Z�b�^
	//void SetName(int,const char *);			//�������ݒ�
	//void SetCodeNum(int,int);				//�R�[�h�ԍ��ݒ�
	void SetPossessionNum(int,int);			//�����������ݒ�
	void SetEquipFlg(int, bool);			//�������Ă��邩�ǂ����ݒ�
	void SetSize();							//�v�f���ݒ�
	//void SetDescription(int, const char *);	//�������ݒ�

	//�Q�b�^
	//const char * GetName(int);				//�������擾
	int GetCodeNum(int);					//�R�[�h�ԍ��擾
	int GetPossessionNum(int);				//�����������擾
	bool GetEquipFlg(int);					//�������Ă��邩�擾
	int GetSize();							//�v�f���擾
	//const char * GetDescription(int);		//�������擾

	void Add(int);							//�������ǉ�
	void AddPossession(int);				//������������������

};
