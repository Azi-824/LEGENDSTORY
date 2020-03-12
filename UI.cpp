//UI.cpp
//�Q�[�����Ŏg�p����UI���Ǘ�����N���X

//####################### �w�b�_�t�@�C���ǂݍ��� ########################
#include "UI.hpp"

//####################### �N���X��` ################################

//�R���X�g���N�^
UI::UI()
{

	this->UiImage = new IMAGE(UI_DIR, UI_WINDOW_NAME);	//ui�̉摜�쐬

	this->menuwindow = new MENU();			//���j���[�E�B���h�E�쐬

	this->MenuSelect = new SELECT("�X�e�[�^�X", "�A�C�e��", "����", "�������", "�Z�[�u");	//���j���[�̑I��������
	this->BattleCommand = new SELECT("��������", "�ڂ�����", "�܂ق�", "�A�C�e��", "�ɂ���");	//�o�g���R�}���h�̑I��������

	this->ItemSelect = new SELECT();	//�A�C�e���̑I�����𐶐�
	this->WeaponSelect = new SELECT();	//����̑I�����𐶐�
	this->ArmorSelect = new SELECT();	//�h��̑I�����𐶐�

	this->BattleCommadType = -1;			//�I�������o�g���R�}���h�̎�ނ�������

	this->ChoiseMenu = -1;					//���j���[��ʂł̑I����e��������

	this->IsDrawUIAnime = true;				//UI�̃A�j���[�V������`�悵�Ă悢

	//�A�j���[�V�����摜�𐶐��i�e�L�X�g�|�[�Y�j
	this->UiAnime = new ANIMATION(TXT_POSE_DIR, TXT_POSE_NAME, TXT_POSE_ALL_CNT, TXT_POSE_YOKO_CNT, TXT_POSE_TATE_CNT, TXT_POSE_WIDTH, TXT_POSE_HEIGHT, TXT_POSE_SPEED, true);

	return;
}

//�f�X�g���N�^
UI::~UI()
{
	delete this->menuwindow;	//menuwindow�j��
	delete this->UiImage;		//Ui�j��
	delete this->UiAnime;		//uianime�j��
	delete this->MenuSelect;	//menuselect�j��
	delete this->BattleCommand;	//battlecommand�j��
	delete this->ItemSelect;	//ItemSelect�j��
	delete this->WeaponSelect;	//WeaponSelect�j��
	delete this->ArmorSelect;	//ArmorSelect�j��

	return;
}

//���j���[�E�B���h�E�`��
void UI::DrawMenu(int x,int y)
{
	//�v���C���[�̈ʒu�ɂ���ĕ`��ʒu��ς���
	if (x <= MENU_WINDOW_CHENGE_POSX && y >= MENU_WINDOW_CHENGE_POSY)	//����ɂ���Ƃ���
	{
		//�v���C���[�̉E��Ƀ��j���[�E�B���h�E��\��
		this->DrawWindow(x + MENU_LIST_WINDOW_RELATIVE_X - TRIANGLE_MINI_SIZE, y + (-MENU_LIST_WINDOW_RELATIVE_Y), MENU_LIST_WINDOW_WIDTH, MENU_LIST_WINDOW_HEIGHT);	//�E�B���h�E�`��
		this->MenuSelect->Draw(x + MENU_LIST_WINDOW_RELATIVE_X, y + (-MENU_LIST_WINDOW_RELATIVE_Y), 1);
	}
	else if (x <= MENU_WINDOW_CHENGE_POSX && y <= MENU_WINDOW_CHENGE_POSY)	//�����ɂ���Ƃ���
	{
		//�v���C���[�̉E���Ƀ��j���[�E�B���h�E��\��
		this->DrawWindow((x + MENU_LIST_WINDOW_RELATIVE_X) - TRIANGLE_MINI_SIZE, y + MENU_LIST_WINDOW_RELATIVE_Y, MENU_LIST_WINDOW_WIDTH, MENU_LIST_WINDOW_HEIGHT);	//�E�B���h�E�`��
		this->MenuSelect->Draw(x + MENU_LIST_WINDOW_RELATIVE_X, y + MENU_LIST_WINDOW_RELATIVE_Y, 1);
	}
	else if (x >= MENU_WINDOW_CHENGE_POSX && y <= MENU_WINDOW_CHENGE_POSY)	//�㑤�ɂ���Ƃ���
	{
		//�v���C���[�̍����Ƀ��j���[�E�B���h�E��\��
		this->DrawWindow(x + (-MENU_LIST_WINDOW_RELATIVE_X) - TRIANGLE_MINI_SIZE, y + MENU_LIST_WINDOW_RELATIVE_Y, MENU_LIST_WINDOW_WIDTH, MENU_LIST_WINDOW_HEIGHT);	//�E�B���h�E�`��
		this->MenuSelect->Draw(x + (-MENU_LIST_WINDOW_RELATIVE_X), y + MENU_LIST_WINDOW_RELATIVE_Y, 1);
	}
	else			//����ȊO�̎���
	{
		//�v���C���[�̍���Ƀ��j���[�E�B���h�E��\��
		this->DrawWindow(x + (-MENU_LIST_WINDOW_RELATIVE_X) - TRIANGLE_MINI_SIZE, y + (-MENU_LIST_WINDOW_RELATIVE_Y), MENU_LIST_WINDOW_WIDTH, MENU_LIST_WINDOW_HEIGHT);	//�E�B���h�E�`��
		this->MenuSelect->Draw(x + (-MENU_LIST_WINDOW_RELATIVE_X), y + (-MENU_LIST_WINDOW_RELATIVE_Y), 1);
	}

	return;
}

//���j���[�őI�񂾓��e��ݒ�
void UI::SetChoiseMenu(std::vector<std::string>::iterator itr)
{

	if (*itr == "�X�e�[�^�X")		//�X�e�[�^�X��I�񂾏ꍇ
	{
		this->ChoiseMenu = (int)MENU_STATUS;	//�X�e�[�^�X
		//return;
	}
	else if (*itr == "�A�C�e��")	//�A�C�e����I�񂾏ꍇ
	{
		this->ChoiseMenu = (int)MENU_ITEM;		//�A�C�e��
		//return;
	}
	else if (*itr == "����")			//������I�񂾏ꍇ
	{
		this->ChoiseMenu = (int)MENU_EQUIPMENT;		//����
		//return;
	}
	else if (*itr == "�������")			//���������I�񂾏ꍇ
	{
		this->ChoiseMenu = (int)MENU_SETUMEI;	//�������
	}
	else if (*itr == "�Z�[�u")			//�Z�[�u��I�񂾏ꍇ
	{
		this->ChoiseMenu = (int)MENU_SAVE;		//�Z�[�u
		//return;
	}

	this->menuwindow->SetIsChoise(true);
		
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
	this->NowSelectReset((int)UI_SELECT_MENU);	//�I�����Ă���v�f�����Z�b�g
	this->MenuSelect->SetSelectFlg(false);		//�I�����Ă��Ȃ�
	this->menuwindow->Reset();	//�I����e���Z�b�g

}

//�I������Ă��邩�擾
bool UI::GetIsChoise(void)
{
	return this->menuwindow->GetIsChoise();
}

//�o�g���R�}���h�Ŏg�p����v�f������������
void UI::BattleInit()
{
	this->BattleCommadType = (int)COMMAND_NONE;	//�I�������R�}���h���e���Z�b�g
	this->BattleCommand->SetSelectFlg(false);	//�I�����Ă��Ȃ���Ԃ�
}

//�퓬��ʂőI�񂾃R�}���h��ݒ肷��
void UI::SetBattleFlg()
{

	auto choise_itr = this->BattleCommand->GetNowSelect();

	if (*choise_itr == "��������")			//�U����I�񂾏ꍇ
	{
		this->BattleCommadType = COMMANDE_ATACK;	//�U��
		return;
	}
	else if (*choise_itr == "�ڂ�����")		//�h���I�񂾏ꍇ
	{
		this->BattleCommadType = COMMANDE_DEFENSE;	//�h��
		return;
	}
	else if (*choise_itr == "�܂ق�")			//���@��I�񂾏ꍇ
	{
		this->BattleCommadType = COMMANDE_MAGIC;	//���@
		return;
	}
	else if (*choise_itr == "�A�C�e��")		//�A�C�e����I�񂾏ꍇ
	{
		this->BattleCommadType = COMMANDE_ITEM;	//�A�C�e��
		return;
	}
	else if (*choise_itr == "�ɂ���")			//�������I�񂾏ꍇ
	{
		this->BattleCommadType = COMMANDE_ESCAPE;	//������
		return;
	}
	return;
}

//�I�������R�}���h�̎�ނ��擾
int UI::GetChoiseCommamd()
{
	return this->BattleCommadType;
}

//�o�g���R�}���h�`��
void UI::DrawCommand()
{
	this->DrawWindow(CMD_WIN_X, CMD_WIN_Y, CMD_WIN_WIDTH, CMD_WIN_HEIGHT);	//�E�B���h�E�`��

	//�I�����`��
	this->BattleCommand->Draw(CMD_TXT_X, CMD_TXT_Y, (int)UI_SELECT_BATTLE_CMD);

	return;
}

//�X�e�[�^�X�E�B���h�E�`��
void UI::DrawStateWindow(PLAYER *player)
{

	this->DrawWindow(STA_WIN_X, STA_WIN_Y,STA_WIN_WIDTH, STA_WIN_HEIGHT);	//�E�B���h�E�`��
	

	//�X�e�[�^�X�`��
	DrawFormatString(STA_TXT_X, STA_TXT_Y, GetColor(255,255,255), "%s\nLv:%d\nHP:%d\nMP:%d\n",player->GetName(), player->GetLevel(), player->GetHP(), player->GetMP());
	DrawBox(STA_HP_BAR_X, STA_HP_BAR_Y, STA_HP_BAR_X + STA_HP_BAR_WIDTH, STA_HP_BAR_Y + STA_HP_BAR_HEIGHT, GetColor(0, 255, 0), FALSE);	//HP�o�[�g���`��
	static double hp_percent = 0.0;//HP����
	static double hp_now = 0.0, hp_max = 0.0;	//���݂�HP�ƍő�HP
	static int draw_hp = 0;		//�`��HP
	hp_now = player->GetHP();	//���݂�HP
	hp_max = player->GetMaxHP();//�ő��HP
	hp_percent = hp_now / hp_max;//HP�̊����v�Z
	draw_hp = STA_HP_BAR_WIDTH * hp_percent;		//�`�悷��HP�ʌv�Z
	DrawBox(STA_HP_BAR_X, STA_HP_BAR_Y, STA_HP_BAR_X + draw_hp, STA_HP_BAR_Y + STA_HP_BAR_HEIGHT, GetColor(0, 255, 0), TRUE);	//HP�`��

	DrawBox(STA_MP_BAR_X, STA_MP_BAR_Y, STA_MP_BAR_X + STA_MP_BAR_WIDTH, STA_MP_BAR_Y + STA_MP_BAR_HEIGHT, GetColor(0, 0, 255), FALSE);	//HP�o�[�g���`��
	static double mp_percent = 0.0;//MP����
	static double mp_now = 0.0, mp_max = 0.0;	//���݂�MP�ƍő�MP
	static int draw_mp = 0;		//�`��HP
	mp_now = player->GetMP();	//���݂�MP
	mp_max = player->GetMaxMP();//�ő��MP
	mp_percent = mp_now / mp_max;//MP�̊����v�Z
	draw_mp = STA_MP_BAR_WIDTH * mp_percent;		//�`�悷��MP�ʌv�Z
	DrawBox(STA_MP_BAR_X, STA_MP_BAR_Y, STA_MP_BAR_X + draw_mp, STA_MP_BAR_Y + STA_MP_BAR_HEIGHT, GetColor(0, 0, 255), TRUE);	//HP�`��


}

//�E�B���h�E��`�悷��
void UI::DrawWindow(int x, int y, int width, int height)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//�`�惂�[�h�𓧉߂���ɕύX�A���ߗ�80���ɐݒ�

	DrawBox(x, y, x + width, y + height, GetColor(0, 0, 0), TRUE);	//�h��Ԃ�����Ŏl�p�`��`��

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�`�惂�[�h��ʏ�ɖ߂�

	this->DrawWindowFrame(x, y, width, height);				//�E�B���h�E�̘g��`��

	return;
}

//�E�B���h�E��`�悷��(�F�w��)
void UI::DrawWindow(int x,int y,int width,int height,unsigned int color)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//�`�惂�[�h�𓧉߂���ɕύX�A���ߗ�80���ɐݒ�

	DrawBox(x, y, x + width, y + height, color, TRUE);	//�h��Ԃ�����Ŏl�p�`��`��

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�`�惂�[�h��ʏ�ɖ߂�

	this->DrawWindowFrame(x, y, width, height);				//�E�B���h�E�̘g��`��

	return;
}

//�E�B���h�E�̘g��`�悷��
void UI::DrawWindowFrame(int x, int y, int width, int height)
{
	DrawBox(x, y, x + width, y + height, GetColor(255, 255, 255), FALSE);	//�h��Ԃ��Ȃ��Ŏl�p�`��`��
	return;
}

//ui�摜��`�悷��
void UI::DrawUiImage(int x, int y,int type)
{
	this->UiImage->Draw(x, y,type);
	return;
}

//ui�摜��ǉ�����
bool UI::AddUiImage(const char *dir, const char *name,int type)
{
	if (this->UiImage->AddImage(dir, name,type))	//�ǂݍ��ݐ���������
	{
		return true;	//�ǂݍ��ݐ���
	}
	else
	{
		return false;	//�ǂݍ��ݎ��s
	}
	
}

//ui�摜�̕����擾
int UI::GetUiImageWidth(int type)
{
	return this->UiImage->GetWidth(type);
}

//ui�摜�̍����擾
int UI::GetUiImageHeight(int type)
{
	return this->UiImage->GetHeight(type);
}

//�w�肳�ꂽ�I�����̃L�[������s��
void UI::SelectOperation(KEYDOWN *keydown, MUSIC *se, int kind)
{
	switch (kind)
	{

	case (int)UI_SELECT_MENU:		//���j���[���

		this->MenuSelect->SelectOperation(keydown, se);			//���j���[��ʃL�[����

		break;

	case (int)UI_SELECT_BATTLE_CMD:		//�o�g���R�}���h

		this->BattleCommand->SelectOperation(keydown, se);		//�o�g���R�}���h�̃L�[����

		break;

	default:
		break;
	}

	return;
}

//�w�肳�ꂽ�I�����̌��ݑI�����Ă���v�f���擾����
std::vector<std::string>::iterator UI::GetNowSelect(int kind)
{
	switch (kind)
	{

	case (int)UI_SELECT_MENU:			//���j���[��ʂ̎�

		return this->MenuSelect->GetNowSelect();

		break;

	case (int)UI_SELECT_BATTLE_CMD:			//�o�g���R�}���h�̎�

		return this->BattleCommand->GetNowSelect();

		break;

	default:
		break;
	}
}

//�I�����̓��e���N���A����
void UI::SelectClear(int kind)
{

	switch (kind)
	{

	case (int)UI_SELECT_MENU:			//���j���[��ʂ̎�

		this->MenuSelect->SelectClear();	//�I�����폜

		break;

	case (int)UI_SELECT_BATTLE_CMD:			//�o�g���R�}���h�̎�

		return this->BattleCommand->SelectClear();	//�I�����폜

		break;

	default:
		break;
	}


	return;
}

//���ݑI�����Ă�����e���ŏ��̗v�f�ɖ߂�
void UI::NowSelectReset(int kind)
{
	switch (kind)
	{

	case (int)UI_SELECT_MENU:			//���j���[��ʂ̎�

		this->MenuSelect->NowSelectReset();	//�I�����폜

		break;

	case (int)UI_SELECT_BATTLE_CMD:			//�o�g���R�}���h�̎�

		this->BattleCommand->NowSelectReset();	//�I�����폜

		break;

	default:
		break;
	}

	return;
}

//�I�����ꂽ���擾
bool UI::GetSelectFlg(int kind)
{
	switch (kind)
	{

	case (int)UI_SELECT_MENU:			//���j���[��ʂ̎�

		return this->MenuSelect->GetSelectFlg();	//�I�����ꂽ���擾

		break;

	case (int)UI_SELECT_BATTLE_CMD:			//�o�g���R�}���h�̎�

		return this->BattleCommand->GetSelectFlg();	//�I�����ꂽ���擾

		break;

	default:
		break;
	}

}

//�A�j���[�V�����摜�ǉ�
bool UI::AddUiAnime(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	
	return this->UiAnime->Add(dir, name, SplitNumALL,SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
}

//UI�A�j���`��
void UI::DrawUiAnime(int x,int y)
{
	if (this->IsDrawUIAnime)	//�`�悵�Ă悢����
	{
		this->UiAnime->DrawAnime(x, y);	//�A�j���[�V�����`��
	}

	return;
}

//�A�j���[�V�����摜��`�悵�Ă悢���ݒ�
void UI::SetIsDrawUIAnime(bool Isdrawuianime)
{
	this->IsDrawUIAnime = Isdrawuianime;
	return;
}

//�A�j���[�V�����摜��`�悵�Ă悢���擾
bool UI::GetIsDrawUIAnime(void)
{
	return this->IsDrawUIAnime;
}

//�摜�T�C�Y��ݒ肷��
void UI::SetSize(void)
{
	this->UiImage->SetSize();		//UI�摜�T�C�Y�ݒ�
	this->UiAnime->SetSize();		//Ui�A�j���[�V�����摜�T�C�Y�ݒ�
	this->MenuSelect->SetSize();	//���j���[��ʂ̑I�����̃T�C�Y�ݒ�
	this->BattleCommand->SetSize();	//�퓬��ʂ̑I�����̃T�C�Y�ݒ�
	
	return;
}

//�A�C�e���̑I������`�悷��
void UI::DrawItemSelect(int x, int y, std::vector<int> item_possession)
{
	this->ItemSelect->Draw(x, y);	//�A�C�e���̑I�����`��

	static int Height = 0;	//����

	Height = GetFontSize();	//�����擾

	for (int i = 0; i < item_possession.size(); ++i)	//�A�C�e���̎�ސ����J��Ԃ�
	{
		DrawFormatString(x + MENU_ITEM_NAME_SPACE, y + i * Height, GetColor(255, 255, 255), "%d��", item_possession[i]);	//�������Ă���A�C�e���̐���`��
	}

	return;

}

//���j���[��ʂ̑����`�揈��
void UI::DrawMenuEquip(int x, int y, std::vector<int> wpn_possession, std::vector<int> amr_possession)
{

	static int Height = 0;	//����
	Height = GetFontSize();	//�����擾

	this->WeaponSelect->Draw(x, y);								//����̑I�����`��

	for (int i = 0; i < wpn_possession.size(); ++i)	//����̎�ޕ��J��Ԃ�
	{
		DrawFormatString(x + MENU_EQUIP_NAME_SPACE, y + i * Height, GetColor(255, 255, 255), "%d��", wpn_possession[i]);	//�������Ă��镐��̐���`��
	}

	this->ArmorSelect->Draw(x + (MENU_WINDOW_WIDTH / 2), y);	//�h��̑I�����`��

	for (int i = 0; i < amr_possession.size(); ++i)	//�h��̎�ޕ��J��Ԃ�
	{
		DrawFormatString((x + (MENU_WINDOW_WIDTH / 2)) + MENU_EQUIP_NAME_SPACE, y + i * Height, GetColor(255, 255, 255), "%d��", amr_possession[i]);	//�������Ă���h��̐���`��
	}

	return;

}
