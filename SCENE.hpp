//SCENE.cpp
//�V�[���N���X

#pragma once

//############### �w�b�_�[�t�@�C���ǂݍ��� ################
#include <DxLib.h>

//############### �񋓌^ ###############
enum GAME_SCENE {
	GAME_SCENE_TITLE,	//�^�C�g�����
	GAME_SCENE_PLAY,	//�v���C���
	GAME_SCENE_END		//�G���h���
};

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
