//SCENE.cpp

//############### �w�b�_�[�t�@�C���ǂݍ��� #################
#include "SCENE.hpp"

//############### �N���X�̒�` ##################

//�R���X�g���N�^
SCENE::SCENE()
{
	return;
}

//�f�X�g���N�^
SCENE::~SCENE()
{
	return;
}

//�w�肳�ꂽ�V�[�����Z�b�g����
void SCENE::SetScene(int Nextscene)
{
	this->GameSceneNow = Nextscene;	//�w�肳�ꂽ�V�[�����Z�b�g
}