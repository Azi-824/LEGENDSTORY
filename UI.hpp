//UI.hpp
//�Q�[�����Ŏg�p����UI���Ǘ�����N���X

#pragma once

//######################### �w�b�_�t�@�C���ǂݍ��� #############################
#include "DxLib.h"
#include "STATEWINDOW.hpp"
#include "PLAYER.hpp"

//######################### �}�N����` #####################################

//######################### �N���X��` #####################################
class UI
{
private:

	STATEWINDOW *StateWindow;		//�X�e�[�^�X�E�B���h�E

public:

	UI();					//�R���X�g���N�^

	~UI();					//�f�X�g���N�^

	void SetStateWindow(PLAYER *);	//�X�e�[�^�X�E�B���h�E�̐ݒ������

	void DrawStateWindow();			//�X�e�[�^�X�E�B���h�E�`��

};
