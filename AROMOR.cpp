//AROMOR.cpp
//EQUIPMENT�N���X����h��
//�h����Ǘ�����N���X

//##################### �w�b�_�t�@�C���ǂݍ��� ###################
#include "ARMOR.hpp"

//##################### �N���X��` ##########################

//�R���X�g���N�^
ARMOR::ARMOR()
{
	return;
}

//�f�X�g���N�^
ARMOR::~ARMOR()
{
	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Def.swap(v);			//��ƒ��g�����ւ���

	return;
}

//�h��͂�ݒ�
void ARMOR::SetDef(int def)
{
	this->Def.push_back(def);
	return;
}

//�h��͂��擾
int ARMOR::GetDef(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			return this->Def[i];
		}
	}

}
