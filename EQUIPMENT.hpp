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

	std::vector<int> CodeNum;				//�R�[�h�ԍ�
	std::vector<int> PossessionNum;			//�����̏�����
	std::vector<bool> EquipFlg;				//�������Ă��邩�ǂ���
	int Size;								//�v�f��
	bool AddFlg;							//�����ǉ��������ǂ���

public:

	EQUIPMENT();							//�R���X�g���N�^
	~EQUIPMENT();							//�f�X�g���N�^

	//�Z�b�^
	void SetPossessionNum(int,int);			//�����������ݒ�
	void SetEquipFlg(int, bool);			//�������Ă��邩�ǂ����ݒ�
	void SetSize();							//�v�f���ݒ�
	void SetAddFlg(bool);					//�����ǉ��������ݒ�

	//�Q�b�^
	int GetCodeNum(int);					//�R�[�h�ԍ��擾
	int GetPossessionNum(int);				//�����������擾
	std::vector<int> GetPossessionNum();	//�����������擾�i���ׂāj
	bool GetEquipFlg(int);					//�������Ă��邩�擾
	int GetSize();							//�v�f���擾
	bool GetAddFlg();						//������ǉ��������擾

	void Add(int);							//�������ǉ�
	void AddPossession(int);				//������������������

};
