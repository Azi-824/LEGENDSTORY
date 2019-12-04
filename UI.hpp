//UI.hpp
//�Q�[�����Ŏg�p����UI���Ǘ�����N���X

#pragma once

//######################### �w�b�_�t�@�C���ǂݍ��� #############################
#include "DxLib.h"
#include "STATEWINDOW.hpp"
#include "COMMAND.hpp"
#include "PLAYER.hpp"

//######################### �}�N����` #####################################

//######################### �N���X��` #####################################
class UI
{
private:

	MENU *menuwindow;				//���j���[�E�B���h�E

	COMMAND *BattleCommand;			//�o�g���R�}���h

	STATEWINDOW *StateWindow;		//�X�e�[�^�X�E�B���h�E

	int BattleCommadType;			//�I�������o�g���R�}���h�̎��


public:

	UI();					//�R���X�g���N�^

	~UI();					//�f�X�g���N�^

	//���j���[�E�B���h�E�֘A
	void MenuOperation(KEYDOWN *,bool);	//���j���[�E�B���h�E�̃L�[�{�[�h����
	void DrawMenu();				//���j���[�E�B���h�E�`��

	//�o�g���R�}���h�֘A
	void SetBattleFlg(std::vector<std::string>::iterator);	//�퓬��ʂőI�񂾃R�}���h�̃t���O��ݒ肷��
	int GetChoiseCommamd();									//�I�������R�}���h�̎�ނ��擾
	void DrawCommand();										//�o�g���R�}���h�`��
	void BattleOperation(KEYDOWN *);						//�퓬��ʂ̑���
	void ResetBattleMember();								//�퓬��ʂŎg�p����ϐ��Ȃǂ����Z�b�g����

	//�X�e�[�^�X�E�B���h�E�֘A
	void SetStateWindow(PLAYER *);	//�X�e�[�^�X�E�B���h�E�̐ݒ������
	void DrawStateWindow();			//�X�e�[�^�X�E�B���h�E�`��

};
