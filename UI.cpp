//UI.cpp
//�Q�[�����Ŏg�p����UI���Ǘ�����N���X

//####################### �w�b�_�t�@�C���ǂݍ��� ########################
#include "UI.hpp"

//####################### �N���X��` ################################

//�R���X�g���N�^
UI::UI()
{
	this->StateWindow = new STATEWINDOW();	//�X�e�[�^�X�E�B���h�E�쐬

	return;
}

//�f�X�g���N�^
UI::~UI()
{
	delete this->StateWindow;	//StateWindow�j��
	return;
}

//�X�e�[�^�X�E�B���h�E�̐ݒ�
void UI::SetStateWindow(PLAYER *player)
{
	this->StateWindow->SetText(player->GetHP());	//HP��ݒ�
	return;
}

//�X�e�[�^�X�E�B���h�E�`��
void UI::DrawStateWindow()
{
	this->StateWindow->Draw();	//�`��
}
