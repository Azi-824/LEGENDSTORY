//SCENE.cpp
//�V�[���N���X

#pragma once

//############### �w�b�_�[�t�@�C���ǂݍ��� ################
#include <DxLib.h>



//############## �N���X�̒�` ################
class SCENE
{
private:
	static int GameSceneNow;			//���݂̃V�[��

public:
	SCENE();					//�R���X�g���N�^

	~SCENE();					//�f�X�g���N�^

	void SetScene(int);			//�w�肳�ꂽ�V�[�����Z�b�g����
};
