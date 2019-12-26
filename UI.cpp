//UI.cpp
//�Q�[�����Ŏg�p����UI���Ǘ�����N���X

//####################### �w�b�_�t�@�C���ǂݍ��� ########################
#include "UI.hpp"

//####################### �N���X��` ################################

//�R���X�g���N�^
UI::UI()
{
	this->menuwindow = new MENU();			//���j���[�E�B���h�E�쐬

	this->StateWindow = new STATEWINDOW();	//�X�e�[�^�X�E�B���h�E�쐬

	this->BattleCommand = new COMMAND();	//�o�g���R�}���h�쐬

	this->BattleCommadType = -1;			//�I�������o�g���R�}���h�̎�ނ�������

	this->ChoiseMenu = -1;					//���j���[��ʂł̑I����e��������

	return;
}

//�f�X�g���N�^
UI::~UI()
{
	delete this->menuwindow;	//menuwindow�j��
	delete this->BattleCommand;	//BattleCommand�j��
	delete this->StateWindow;	//StateWindow�j��

	return;
}

//���j���[�E�B���h�E�̃L�[�{�[�h����
void UI::MenuOperation(KEYDOWN *keydown,bool ismenu)
{
	if (ismenu)	//���j���[�`�撆
	{
		if (keydown->IsKeyDownOne(KEY_INPUT_W))	//W�L�[�������ꂽ�u��
		{
			this->menuwindow->Back();	//�O�̗v�f��
		}
		else if (keydown->IsKeyDownOne(KEY_INPUT_S))	//S�L�[�������ꂽ�u��
		{
			this->menuwindow->Next();	//���̗v�f��
		}
		this->DrawMenu();	//���j���[�E�B���h�E�`��

		//�R�}���h���菈��
		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ�u��
		{
			auto itr = this->menuwindow->GetChoiseMenu();	//���j���[��ʂ̑I����e���擾
			this->SetChoiseMenu(itr);						//�I����e��ݒ�
		}

	}
	return;
}

//���j���[�E�B���h�E�`��
void UI::DrawMenu()
{
	this->menuwindow->Draw();	//���j���[�`��
	return;
}

//���j���[�őI�񂾓��e��ݒ�
void UI::SetChoiseMenu(std::vector<std::string>::iterator itr)
{

	if (*itr == "�X�e�[�^�X")		//�X�e�[�^�X��I�񂾏ꍇ
	{
		this->ChoiseMenu = (int)MENU_STATUS;	//�X�e�[�^�X
		return;
	}
	else if (*itr == "�A�C�e��")	//�A�C�e����I�񂾏ꍇ
	{
		this->ChoiseMenu = (int)MENU_ITEM;		//�A�C�e��
		return;
	}
	else if (*itr == "����")			//������I�񂾏ꍇ
	{
		this->ChoiseMenu = (int)MENU_SOUBI;		//����
		return;
	}
	else if (*itr == "�Z�[�u")			//�Z�[�u��I�񂾏ꍇ
	{
		this->ChoiseMenu = (int)MENU_SAVE;		//�Z�[�u
		return;
	}
		
	return;
}

//���j���[��ʂł̑I����e���擾
int UI::GetChoiseMenu()
{
	return this->ChoiseMenu;
}

//���j���[�֌W�̃����o�[�����Z�b�g
void UI::ResetMenu()
{
	this->ChoiseMenu = -1;		//�I����e�����Z�b�g
	this->menuwindow->Reset();	//�I����e���Z�b�g
}

//�I�񂾓��e���Ƃ̃��j���[��`��
void UI::DrawChoiseMenu()
{
	this->menuwindow->DrawChoise(this->ChoiseMenu);
	return;
}

//�o�g���R�}���h�Ŏg�p����v�f������������
void UI::BattleInit()
{
	this->BattleCommand->Init();	//�I��v�f�̏�����
	this->BattleCommadType = -1;	//�I�������R�}���h���e���Z�b�g
}

//�퓬��ʂőI�񂾃R�}���h��ݒ肷��
void UI::SetBattleFlg(std::vector<std::string>::iterator choise_itr)
{
	if (*choise_itr == "��������")			//�U����I�񂾏ꍇ
	{
		this->BattleCommadType = ATACK;	//�U��
		return;
	}
	else if (*choise_itr == "�ڂ�����")		//�h���I�񂾏ꍇ
	{
		this->BattleCommadType = DEFENSE;	//�h��
		return;
	}
	else if (*choise_itr == "�܂ق�")			//���@��I�񂾏ꍇ
	{
		this->BattleCommadType = MAGIC;	//���@
		return;
	}
	else if (*choise_itr == "�A�C�e��")		//�A�C�e����I�񂾏ꍇ
	{
		this->BattleCommadType = ITEM;	//�A�C�e��
		return;
	}
	else if (*choise_itr == "�ɂ���")			//�������I�񂾏ꍇ
	{
		this->BattleCommadType = ESCAPE;	//������
		return;
	}
	return;
}

//�I�������R�}���h�̎�ނ��擾
int UI::GetChoiseCommamd()
{
	return this->BattleCommadType;
}

//�퓬��ʂ̑���
void UI::BattleOperation(KEYDOWN *keydown)
{
	//�R�}���h�I������
	if (keydown->IsKeyDownOne(KEY_INPUT_D))			//D�L�[�������ꂽ�u��
	{
		this->BattleCommand->Next();	//���̗v�f��
	}
	else if (keydown->IsKeyDownOne(KEY_INPUT_A))	//A�L�[�������ꂽ�u��
	{
		this->BattleCommand->Back();	//�O�̗v�f��
	}

	//�R�}���h���菈��
	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//�G���^�[�L�[�������ꂽ�u��
	{
		auto itr = this->BattleCommand->GetCommand();	//�I�����Ă���R�}���h���擾
		this->SetBattleFlg(itr);	//�o�g���t���O�ݒ�
	}

	return;
}

//�o�g���R�}���h�`��
void UI::DrawCommand()
{

	this->BattleCommand->Draw();	//�`��

	return;
}

//�X�e�[�^�X�E�B���h�E�̐ݒ�
void UI::SetStateWindow(int level ,int hp,int mp)
{
	std::vector<int> set;
	set.push_back(level);	//���x���擾
	set.push_back(hp);//HP�擾
	set.push_back(mp);//MP�擾
	this->StateWindow->SetText(set);	//Level�AHP�AMP��ݒ�
	return;
}

//�X�e�[�^�X�E�B���h�E�`��
void UI::DrawStateWindow()
{
	this->StateWindow->Draw();	//�`��
}

//�E�B���h�E��`�悷��
void UI::DrawWindow()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//�`�惂�[�h�𓧉߂���ɕύX�A���ߗ�80���ɐݒ�

	DrawBox(0, 380, 0 + 800,380 + 100, GetColor(0, 0, 0), TRUE);	//�h��Ԃ�����Ŏl�p�`��`��

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�`�惂�[�h��ʏ�ɖ߂�

}
