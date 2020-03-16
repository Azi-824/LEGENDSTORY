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

	std::vector<int> Code;					//�R�[�h�ԍ�
	std::vector<int> Possession;			//�����̏�����
	std::vector<bool> EquipFlg;				//�������Ă��邩�ǂ���
	std::vector<bool> IsDraw;				//�`�悵�Ă悢��
	int Size;								//�v�f��
	bool Chenge_flg;						//������ύX�������ǂ���

public:

	EQUIPMENT();							//�R���X�g���N�^
	~EQUIPMENT();							//�f�X�g���N�^

	//�Z�b�^
	//void SetPossessionNum(int,int);			//�����������ݒ�
	void IncreasePossession(int);			//����������
	void DecreasePossession(int);			//����������
	void SetEquipFlg(int, bool);			//�������Ă��邩�ǂ����ݒ�
	void SetSize();							//�v�f���ݒ�
	void SetChengeFlg(bool);				//������ύX�������ݒ�

	//�Q�b�^
	int GetCode(int);						//�R�[�h�ԍ��擾
	int GetPossession(int);					//�����������擾
	std::vector<int> GetPossession();		//�����������擾�i���ׂāj
	bool GetEquipFlg(int);					//�������Ă��邩�擾
	int GetSize();							//�v�f���擾
	bool GetChengeFlg();					//������ύX�������擾

	void Add(int);							//�������ǉ�
	void LoadData(int, int);				//��������ǂݍ���

	bool GetIsDraw(int);					//�`�悵�Ă悢���擾

};
