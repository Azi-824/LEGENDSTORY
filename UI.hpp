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

	int ChoiseMenu;					//���j���[��ʂőI���������e

public:

	UI();					//�R���X�g���N�^

	~UI();					//�f�X�g���N�^

	//���j���[�E�B���h�E�֘A
	void MenuOperation(KEYDOWN *,bool);	//���j���[�E�B���h�E�̃L�[�{�[�h����
	void DrawMenu();				//���j���[�E�B���h�E�`��
	void SetChoiseMenu(std::vector<std::string>::iterator);	//���j���[�őI�񂾓��e��ݒ肷��
	int GetChoiseMenu();				//���j���[��ʂł̑I����e���擾
	void ResetMenu();					//���j���[�֌W�̃����o�[�����Z�b�g
	void DrawChoiseMenu();				//�I�񂾃��j���[���e���Ƃ̕`��

	//�o�g���R�}���h�֘A
	void SetBattleFlg(std::vector<std::string>::iterator);	//�퓬��ʂőI�񂾃R�}���h�̃t���O��ݒ肷��
	int GetChoiseCommamd();									//�I�������R�}���h�̎�ނ��擾
	void DrawCommand();										//�o�g���R�}���h�`��
	void BattleOperation(KEYDOWN *);						//�퓬��ʂ̑���
	void BattleInit();										//�o�g���R�}���h�Ŏg�p����v�f������������

	//�X�e�[�^�X�E�B���h�E�֘A
	void SetStateWindow(int,int,int);	//�X�e�[�^�X�E�B���h�E�̐ݒ������
	void DrawStateWindow();			//�X�e�[�^�X�E�B���h�E�`��

	

	void DrawWindow();				//�E�B���h�E��`�悷��

};
