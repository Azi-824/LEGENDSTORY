//UI.cpp
//�Q�[�����Ŏg�p����UI���Ǘ�����N���X

//####################### �w�b�_�t�@�C���ǂݍ��� ########################
#include "UI.hpp"

//####################### �N���X��` ################################

//�R���X�g���N�^
UI::UI()
{

	this->UiImage = new IMAGE(UI_DIR, UI_WINDOW_NAME);	//ui�̉摜�쐬

	this->MenuSelect = new SELECT("�X�e�[�^�X", "�A�C�e��", "����", "�������", "�Z�[�u");	//���j���[�̑I��������
	this->BattleCommand = new SELECT("��������", "�ڂ�����", "�܂ق�", "�A�C�e��", "�ɂ���");	//�o�g���R�}���h�̑I��������

	this->ItemSelect = new SELECT();	//�A�C�e���̑I�����𐶐�
	this->WeaponSelect = new SELECT();	//����̑I�����𐶐�
	this->ArmorSelect = new SELECT();	//�h��̑I�����𐶐�
	this->Yes_No = new SELECT("�͂�", "������");	//�͂��A�������̑I�����𐶐�
	this->EquipSelect = new SELECT("����", "�h��");	//����A�h��̑I�����𐶐�

	this->EquipSelect->SetSideMode(true);		//�I�������������ɕ��ׂ�

	//�A�j���[�V�����摜�𐶐��i�e�L�X�g�|�[�Y�j
	this->UiAnime = new ANIMATION(TXT_POSE_DIR, TXT_POSE_NAME, TXT_POSE_ALL_CNT, TXT_POSE_YOKO_CNT, TXT_POSE_TATE_CNT, TXT_POSE_WIDTH, TXT_POSE_HEIGHT, TXT_POSE_SPEED, true);

	return;
}

//�f�X�g���N�^
UI::~UI()
{
	delete this->UiImage;		//Ui�j��
	delete this->UiAnime;		//uianime�j��
	delete this->MenuSelect;	//menuselect�j��
	delete this->BattleCommand;	//battlecommand�j��
	delete this->ItemSelect;	//ItemSelect�j��
	delete this->WeaponSelect;	//WeaponSelect�j��
	delete this->ArmorSelect;	//ArmorSelect�j��
	delete this->Yes_No;		//Yes_No�j��
	delete this->EquipSelect;	//EquipSelect�j��

	return;
}

//******************************** ���j���[�֌W *************************
//���j���[�E�B���h�E�`��
void UI::DrawMenu()
{

	this->DrawWindow(MENU_LIST_WIN_X, MENU_LIST_WIN_Y, MENU_LIST_WIN_WIDTH, MENU_LIST_WIN_HEIGHT);	//�E�B���h�E�`��
	this->MenuSelect->Draw(MENU_LIST_TEXT_X, MENU_LIST_TEXT_Y);										//���j���[��ʂ̑I�����`��

	return;
}

//���j���[�֌W�̃����o�[�����Z�b�g
void UI::ResetMenu()
{
	this->MenuSelect->SetSelectFlg(false);	//�I�����Ă��Ȃ�
	this->MenuSelect->NowSelectReset();		//�I�����Ă�����e�����Z�b�g

	this->Yes_No->Default();				//�͂��A�������̑I�������f�t�H���g�̏�Ԃɖ߂�
	this->WeaponSelect->Default();			//����̑I�������f�t�H���g��
	this->ArmorSelect->Default();			//�h��̑I�������f�t�H���g��
	this->EquipSelect->Default();			//����A�h��̑I�������f�t�H���g�̏�Ԃɖ߂�

	this->Menu_Equip_dir = (MENU_EQUIP_SELECT_KIND);//������ʂ̑I�����̒i�K���ŏ���

}

//���j���[�̑�����ʂ̑I�����̒i�K���擾
int UI::GetMenuEquipDir(void)
{
	return this->Menu_Equip_dir;
}

//���j���[�E�B���h�E�ł̊m�F�̑I�����`��
void UI::DrawMenuCheck(void)
{

	this->UiImage->Draw(PLAY_WIN_X, PLAY_WIN_Y);	//�E�B���h�E�`��

	switch (this->MenuSelect->GetSelectNum())	//���j���[��ʂőI���������e��
	{

	case (int)MENU_ITEM:	//�A�C�e����I�񂾏ꍇ

		DrawFormatString(PLAY_WIN_TEXT_X, PLAY_WIN_TEXT_Y, GetColor(255, 255, 255), "%s���g���܂����H", this->ItemSelect->GetSelectText());	//�m�F���b�Z�[�W�`��

		break;

	case (int)MENU_EQUIPMENT:	//������I�񂾏ꍇ

		if (this->EquipSelect->GetSelectNum() == SELECT_EQUIP_WEAPON)	//���킾������
		{
			DrawFormatString(PLAY_WIN_TEXT_X, PLAY_WIN_TEXT_Y, GetColor(255, 255, 255), "%s�𑕔����܂����H", this->WeaponSelect->GetSelectText());	//�m�F���b�Z�[�W�`��
		}
		else	//�h�������
		{
			DrawFormatString(PLAY_WIN_TEXT_X, PLAY_WIN_TEXT_Y, GetColor(255, 255, 255), "%s�𑕔����܂����H", this->ArmorSelect->GetSelectText());	//�m�F���b�Z�[�W�`��
		}

		break;

	default:
		break;
	}

	int Height = GetFontSize();	//�����擾

	this->Yes_No->Draw(PLAY_WIN_TEXT_X, PLAY_WIN_TEXT_Y + Height);	//�͂��A�������̑I�����`��

	return;

}

//���j���[�̃A�C�e����ʂ̏���
bool UI::MenuSelectItem(KEYDOWN *keydown, MUSIC *sys_se)
{
	if (this->ItemSelect->GetSelectKind() != 0)	//�A�C�e�������ވȏ㎝���Ă����ꍇ
	{
		this->ItemSelect->SelectOperation(keydown, sys_se);	//�A�C�e���̑I�����L�[����

		if (this->ItemSelect->GetBackFlg())		//�߂�I���������Ƃ�
		{
			this->ItemSelect->Default();			//�A�C�e���̑I�������f�t�H���g��Ԃ�
			this->ResetMenu();					//���j���[�I���ɖ߂�
		}

		if (this->ItemSelect->GetSelectFlg())		//�A�C�e����I�񂾂�
		{
			this->ItemSelect->SetIsKeyOpe(false);	//�A�C�e���̑I�����L�[����s��
			this->Yes_No->SetIsKeyOpe(true);			//�͂��A�������̑I�����L�[����\

			this->Yes_No->SelectOperation(keydown, sys_se);	//�͂��A�������̑I�����L�[����

			if (this->Yes_No->GetSelectFlg())		//�͂�����������I��������
			{
				if (this->Yes_No->GetSelectNum() == (int)SELECT_YES)	//�͂���I�񂾂Ƃ�
				{
					return true;	//�A�C�e����I������
				}
				this->Yes_No->Default();			//�͂��A�������̑I�����f�t�H���g��
				this->ItemSelect->Default();	//�A�C�e���̑I�����f�t�H���g��
			}

		}

	}

	return false;	//�A�C�e����I�����Ă��Ȃ�

}

//���j���[��ʂ̑����`�揈��
void UI::DrawMenuEquip(WEAPON *weapon, ARMOR *armor)
{

	static int Height = 0;	//����
	Height = GetFontSize();	//�����擾

	this->EquipSelect->Draw(MENU_TEXT_X, MENU_TEXT_TOP_Y);		//�����I��`��

	this->WeaponSelect->Draw(MENU_TEXT_X, MENU_TEXT_Y);			//����̑I�����`��

	for (int i = 0; i < weapon->GetSize(); ++i)	//����̎�ޕ��J��Ԃ�
	{
		DrawFormatString(MENU_TEXT_X + MENU_EQUIP_NAME_SPACE, //X�ʒu
			MENU_TEXT_Y + i * Height,	//Y�ʒu
			GetColor(255, 255, 255),	//�`��F
			"%d��", weapon->GetPossession(weapon->GetCode(i)));	//�������Ă��镐��̐���`��

		DrawFormatString(MENU_TEXT_X + MENU_EQUIP_NAME_SPACE + MENU_WQUIP_POSSESSION_SPACE,
			MENU_TEXT_Y + i * Height,
			GetColor(255, 255, 255),
			"ATK+%d", weapon->GetAtk(weapon->GetCode(i)));	//�U���͂�`��

	}

	this->ArmorSelect->Draw(MENU_TEXT_X + (MENU_WINDOW_WIDTH / 2), MENU_TEXT_Y);	//�h��̑I�����`��

	for (int i = 0; i < armor->GetSize(); ++i)	//�h��̎�ޕ��J��Ԃ�
	{
		DrawFormatString((MENU_TEXT_X + (MENU_WINDOW_WIDTH / 2)) + MENU_EQUIP_NAME_SPACE,
			MENU_TEXT_Y + i * Height,
			GetColor(255, 255, 255),
			"%d��", armor->GetPossession(armor->GetCode(i)));	//�������Ă���h��̐���`��

		DrawFormatString((MENU_TEXT_X + (MENU_WINDOW_WIDTH / 2)) + MENU_EQUIP_NAME_SPACE + MENU_WQUIP_POSSESSION_SPACE,
			MENU_TEXT_Y + i * Height,
			GetColor(255, 255, 255),
			"DEF+%d", armor->GetDef(armor->GetCode(i)));	//�h��͂�`��

	}

	return;

}

//���j���[�̑�����ʂ̏���
int UI::MenuSelectEquip(KEYDOWN *keydown, MUSIC *sys_se)
{

	switch (this->Menu_Equip_dir)		//�I�����̒i�K
	{

	case (int)MENU_EQUIP_SELECT_KIND:		//���킩�h��I������i�K

		this->EquipSelect->SelectOperation(keydown, sys_se);	//���킩�h��̑I�����̃L�[����

		if (this->EquipSelect->GetBackFlg())	//�߂�I����������
		{
			this->ResetMenu();					//���j���[�I���ɖ߂�
			this->EquipSelect->Default();		//����h��̑I�������f�t�H���g��
		}

		if (this->EquipSelect->GetSelectFlg())	//���킩�h���I��������
		{
			this->EquipSelect->SetIsKeyOpe(false);	//����h��̑I�����̃L�[����s��
			this->EquipSelect->SetIsDrawImage(false);//UI��\��
			this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_EQUIP;	//�I�����̒i�K������
		}

		break;	//���킩�h��I������i�K�����܂�

	case (int)MENU_EQUIP_SELECT_EQUIP:		//�������镐��A�������͖h���I������i�K

		switch (this->EquipSelect->GetSelectNum())		//���킩�A�h��ǂ����I�񂾂�
		{

		case (int)SELECT_EQUIP_WEAPON:		//�����I�񂾂Ƃ�

			this->WeaponSelect->SetIsKeyOpe(true);						//����̑I�����A�L�[����\
			this->WeaponSelect->SetIsDrawImage(true);					//����̑I��UI�\��
			this->WeaponSelect->SelectOperation(keydown, sys_se);		//����̑I���L�[����

			//************* �߂�I�����������̏��� *****************
			if (this->WeaponSelect->GetBackFlg())	//�߂�I����������
			{
				this->WeaponSelect->Default();			//����̑I�����A�f�t�H���g�l��
				this->EquipSelect->Default();			//����A�h��̑I�����\��
				this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_KIND;	//�I�����̒i�K��O��
			}

			//************** �������镐��I����̏��� ******************
			if (this->WeaponSelect->GetSelectFlg())		//�������镐���I�񂾂�
			{
				this->WeaponSelect->SetIsKeyOpe(false);		//����̑I���͂ł��Ȃ��悤�ɐݒ�
				this->WeaponSelect->SetIsDrawImage(false);	//�h��̑I����UI��\��

				this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_DECISION;	//�I�����̒i�K������

			}

			break;	//�����I�񂾂Ƃ������܂�

		case (int)SELECT_EQUIP_ARMOR:		//�h���I�񂾂Ƃ�

			this->ArmorSelect->SetIsKeyOpe(true);					//�h��̑I�����A�L�[����\
			this->ArmorSelect->SetIsDrawImage(true);				//�h��̑I��UI�\��
			this->ArmorSelect->SelectOperation(keydown, sys_se);	//�h��̑I���L�[����

			//************* �߂�I�����������̏��� *****************
			//�C���_����
			if (this->ArmorSelect->GetBackFlg())	//�߂�I����������
			{
				this->ArmorSelect->Default();		//�h��̑I�����A�f�t�H���g�l��
				this->EquipSelect->Default();			//����A�h��̑I�����\��
				this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_KIND;	//�I�����̒i�K��O��
			}


			//************** ��������h��I����̏��� ******************
			if (this->ArmorSelect->GetSelectFlg())		//��������h���I�񂾂�
			{
				this->ArmorSelect->SetIsKeyOpe(false);	//�h��̑I���͂ł��Ȃ��悤�ɐݒ�
				this->ArmorSelect->SetIsDrawImage(false);//�h��̑I����UI��\��
				this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_DECISION;	//�I�����̒i�K������

			}

			break;	//�h���I�񂾂Ƃ�

		default:
			break;
		}


		break;	//�������镐��A�������͖h���I������i�K�����܂�

	case (int)MENU_EQUIP_SELECT_DECISION:	//�������邩���肷��i�K(�͂��A������)

		this->Yes_No->SetIsKeyOpe(true);					//�͂��A�������̑I�����̑���\��
		this->Yes_No->SelectOperation(keydown, sys_se);	//�͂��A�������̑I�����̃L�[����

		if (this->Yes_No->GetSelectFlg())					//�������邩�I��������
		{
			if (this->Yes_No->GetSelectNum() == (int)SELECT_YES)		//�͂��A��I��������
			{
				this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_EQUIP;	//�I�����̒i�K����O��
				this->Yes_No->Default();								//�͂��A�������̑I�����f�t�H���g��
				sys_se->Play((int)SYS_SE_EQUIP);						//�����������̉���炷

				return this->EquipSelect->GetSelectNum();	//����A�h��̂ǂ����I����������Ԃ�
			}

			this->Yes_No->Default();								//�͂��A�������̑I�����f�t�H���g��
			this->ArmorSelect->Default();							//�h��̑I�����f�t�H���g��
			this->WeaponSelect->Default();							//����̑I�����f�t�H���g��
			this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_EQUIP;	//�I�����̒i�K����O��

		}


		break;	//�������邩���肷��i�K(�͂��A������)�����܂�

	default:
		break;
	}

	return SELECT_NONE;	//����������̂�I�΂Ȃ������ꍇ-1��Ԃ�

}

//******************************* �o�g���֌W *******************************
//�o�g���R�}���h�Ŏg�p����v�f������������
void UI::BattleInit()
{
	this->BattleCommand->NowSelectReset();	//�R�}���h�̑I�������Z�b�g
	this->BattleCommand->SetSelectFlg(false);	//�I�����Ă��Ȃ���Ԃ�
}

//�o�g���R�}���h�`��
void UI::DrawCommand()
{
	this->DrawWindow(CMD_WIN_X, CMD_WIN_Y, CMD_WIN_WIDTH, CMD_WIN_HEIGHT);	//�E�B���h�E�`��

	//�I�����`��
	this->BattleCommand->Draw(CMD_TXT_X, CMD_TXT_Y);

	return;
}

//�X�e�[�^�X�E�B���h�E�`��
void UI::DrawStateWindow(PLAYER *player)
{

	this->DrawWindow(STA_WIN_X, STA_WIN_Y,STA_WIN_WIDTH, STA_WIN_HEIGHT);	//�E�B���h�E�`��
	

	//�X�e�[�^�X�`��
	DrawFormatString(STA_TXT_X, STA_TXT_Y, GetColor(255,255,255), "%s\nLv:%d\nHP:%d\nMP:%d\n",player->GetName(), player->GetLevel(), player->GetHP(), player->GetMP());

	//HP�o�[�`�揈��
	DrawBox(STA_HP_BAR_X, STA_HP_BAR_Y, STA_HP_BAR_X + STA_HP_BAR_WIDTH, STA_HP_BAR_Y + STA_HP_BAR_HEIGHT, GetColor(0, 255, 0), FALSE);	//HP�o�[�g���`��
	static double hp_percent = 0.0;//HP����
	static double hp_now = 0.0, hp_max = 0.0;	//���݂�HP�ƍő�HP
	static int draw_hp = 0;		//�`��HP
	hp_now = player->GetHP();	//���݂�HP
	hp_max = player->GetMaxHP();//�ő��HP
	hp_percent = hp_now / hp_max;//HP�̊����v�Z
	draw_hp = STA_HP_BAR_WIDTH * hp_percent;		//�`�悷��HP�ʌv�Z
	DrawBox(STA_HP_BAR_X, STA_HP_BAR_Y, STA_HP_BAR_X + draw_hp, STA_HP_BAR_Y + STA_HP_BAR_HEIGHT, GetColor(0, 255, 0), TRUE);	//HP�`��

	//MP�o�[�`�揈��
	DrawBox(STA_MP_BAR_X, STA_MP_BAR_Y, STA_MP_BAR_X + STA_MP_BAR_WIDTH, STA_MP_BAR_Y + STA_MP_BAR_HEIGHT, GetColor(0, 0, 255), FALSE);	//HP�o�[�g���`��
	static double mp_percent = 0.0;//MP����
	static double mp_now = 0.0, mp_max = 0.0;	//���݂�MP�ƍő�MP
	static int draw_mp = 0;		//�`��HP
	mp_now = player->GetMP();	//���݂�MP
	mp_max = player->GetMaxMP();//�ő��MP
	mp_percent = mp_now / mp_max;//MP�̊����v�Z
	draw_mp = STA_MP_BAR_WIDTH * mp_percent;		//�`�悷��MP�ʌv�Z
	DrawBox(STA_MP_BAR_X, STA_MP_BAR_Y, STA_MP_BAR_X + draw_mp, STA_MP_BAR_Y + STA_MP_BAR_HEIGHT, GetColor(0, 0, 255), TRUE);	//HP�`��

	//BP�`�揈��
	for (int i = 0; i < MAX_BP; ++i)	//BP�̍ő�l���J��Ԃ�
	{
		//BP�̐������A�h��Ԃ��ĕ`�悷��
		//BP���Ȃ��ꍇ�́A�g�������`�悷��
		//�g�p����BP�͐F��ς��ĕ`�悷��
		if (i < player->GetUseBP())	//�g�p����BP��菭�Ȃ�������
		{
			DrawCircle(STA_BP_X + i * STA_BP_INTERVAL, STA_BP_Y, STA_BP_DRAW_SIZE, GetColor(0, 255, 0), TRUE);	//�g�p����BP�`��(�F��ς��ĕ`��)
		}
		else if (i < player->GetBP())	//���݂�BP��菬����������
		{
			DrawCircle(STA_BP_X + i * STA_BP_INTERVAL, STA_BP_Y, STA_BP_DRAW_SIZE, GetColor(255, 0, 0), TRUE);	//BP�`��(�~�̒���h��Ԃ��ĕ`��)
		}

		DrawCircle(STA_BP_X + i * STA_BP_INTERVAL, STA_BP_Y, STA_BP_DRAW_SIZE, GetColor(255, 255, 255), FALSE);	//BP�`��(�g��)

	}

	return;

}

//*************************** �E�B���h�E�֌W *******************************
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

//******************************* UI�摜�֌W *********************************
//ui�摜��`�悷��
void UI::DrawUiImage(int x, int y,int type)
{
	this->UiImage->Draw(x, y,type);
	return;
}

//ui�摜��ǉ�����
bool UI::AddUiImage(const char *dir, const char *name)
{
	if (this->UiImage->AddImage(dir, name))	//�ǂݍ��ݐ���������
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

//**************************** UI�A�j���[�V�����֌W *******************************
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

//**************************** �ݒ�֌W ****************************
//����������
void UI::Init(void)
{

	this->IsDrawUIAnime = true;				//UI�̃A�j���[�V������`�悵�Ă悢

	this->Menu_Equip_dir = (MENU_EQUIP_SELECT_KIND);//������ʂ̑I�����̒i�K���ŏ���

	//����̑I����
	this->WeaponSelect->ChengeDefault(false, false);//�f�t�H���g�l��ύX�i�L�[����s�AUI��\���j
	this->WeaponSelect->Default();					//�f�t�H���g�l�ɐݒ�
	//�h��̑I����
	this->ArmorSelect->ChengeDefault(false, false);	//�f�t�H���g�l��ύX�i�L�[����s�AUI��\���j
	this->ArmorSelect->Default();					//�f�t�H���g�l�ɐݒ�


	return;
}

//�摜�T�C�Y��ݒ肷��
void UI::SetSize(void)
{
	this->UiImage->SetSize();		//UI�摜�T�C�Y�ݒ�
	this->UiAnime->SetSize();		//Ui�A�j���[�V�����摜�T�C�Y�ݒ�
	this->MenuSelect->SetSize();	//���j���[��ʂ̑I�����̃T�C�Y�ݒ�
	this->BattleCommand->SetSize();	//�퓬��ʂ̑I�����̃T�C�Y�ݒ�
	this->WeaponSelect->SetSize();	//����̑I�����̃T�C�Y�ݒ�
	this->ArmorSelect->SetSize();	//�h��̑I�����̃T�C�Y�ݒ�
	this->ItemSelect->SetSize();	//�A�C�e���̑I�����̃T�C�Y�ݒ�
	this->Yes_No->SetSize();		//�͂��A�������̑I�����̃T�C�Y�ݒ�
	this->EquipSelect->SetSize();	//����h��̑I�����̃T�C�Y�ݒ�
	
	return;
}

//*************************** �A�C�e���֌W *****************************
//�A�C�e���̑I������`�悷��
void UI::DrawItemSelect(int x,int y,ITEM *item)
{
	this->ItemSelect->Draw(x, y);	//�A�C�e���̑I�����`��

	static int Height = 0;	//����
	int Cnt = 0;			//�J�E���g�p

	Height = GetFontSize();	//�����擾

	for (int i = 0; i < item->GetSize(); ++i)	//�A�C�e���̎�ސ����J��Ԃ�
	{

		if (item->GetPossession(item->GetCode(i)) != 0)	//��������0����Ȃ����
		{
			DrawFormatString(x + MENU_ITEM_NAME_SPACE, y + Cnt * Height, GetColor(255, 255, 255), "%d��", item->GetPossession(item->GetCode(i)));	//�������Ă���A�C�e���̐���`��

			++Cnt;	//�J�E���g�A�b�v

		}

	}

	return;

}

//�A�C�e���̑I������`�悷��(�������t��)
void UI::DrawItemSelect(int x, int y,ITEM *item,LIST_ITEM *list_item)
{
	this->ItemSelect->Draw(x, y);	//�A�C�e���̑I�����`��

	static int Height = 0;	//����
	int Cnt = 0;			//�J�E���g�p

	
	Height = GetFontSize();	//�����擾

	for (int i = 0; i < item->GetSize(); ++i)	//�A�C�e���̎�ސ����J��Ԃ�
	{

		if (item->GetPossession(item->GetCode(i)) != 0)	//��������0����Ȃ����
		{
			DrawFormatString(x + MENU_ITEM_NAME_SPACE, y + Cnt * Height, GetColor(255, 255, 255), "%d��", item->GetPossession(item->GetCode(i)));	//�������Ă���A�C�e���̐���`��

			DrawFormatString(x + MENU_ITEM_NAME_SPACE + MENU_ITEM_POSSESSION_SPACE,
				y + Cnt * Height,
				GetColor(255, 255, 255),
				"%s", list_item->GetDescription(item->GetCode(i)));	//�������`��

			++Cnt;	//�J�E���g�A�b�v

		}

	}

	return;

}

//**************************** �I�����֌W *******************************
//�I�����̓��e���X�V���鏈��(�A�C�e��)
void UI::SelectUpdate(ITEM *item, LIST_ITEM *item_list)
{

	if (item->GetChengeFlg())	//�ύX����������
	{
		this->ItemSelect->SelectClear();	//���݂̑I�����N���A

		for (int i = 0; i < item->GetSize(); ++i)	//�����Ă���A�C�e���̎�ޕ��J��Ԃ�
		{
			if (item->GetIsDraw(i))	//�A�C�e���������Ă���ꍇ
			{
				this->ItemSelect->AddSelect(item_list->GetName(item->GetCode(i)), item->GetCode(i));	//�V�����I������ǉ����A���O�ƃA�C�e���R�[�h��n��
			}
		}

		item->SetChengeFlg(false);	//�ύX�Ȃ�

	}

	return;

}

//�I�����̓��e���X�V���鏈��(����)
void UI::SelectUpdate(WEAPON *weapon, LIST_WEAPON *weapon_list)
{

	if (weapon->GetChengeFlg())	//�ύX����������
	{
		this->WeaponSelect->SelectClear();	//���݂̑I�����N���A

		for (int i = 0; i < weapon->GetSize(); ++i)	//�����Ă��镐��̎�ޕ��J��Ԃ�
		{
			if (weapon->GetIsDraw(i))	//����������Ă���ꍇ
			{
				this->WeaponSelect->AddSelect(weapon_list->GetName(weapon->GetCode(i)), weapon->GetCode(i));	//�V�����I������ǉ����A���O�ƃA�C�e���R�[�h��n��
			}
		}

		weapon->SetChengeFlg(false);	//�ύX�Ȃ�

	}

	return;

}

//�I�����̓��e���X�V���鏈��(�h��)
void UI::SelectUpdate(ARMOR *armor, LIST_ARMOR *armor_list)
{

	if (armor->GetChengeFlg())	//�ύX����������
	{
		this->ArmorSelect->SelectClear();	//���݂̑I�����N���A

		for (int i = 0; i < armor->GetSize(); ++i)	//�����Ă���h��̎�ޕ��J��Ԃ�
		{
			if (armor->GetIsDraw(i))	//�h��������Ă���ꍇ
			{
				this->ArmorSelect->AddSelect(armor_list->GetName(armor->GetCode(i)), armor->GetCode(i));	//�V�����I������ǉ����A���O�ƃA�C�e���R�[�h��n��
			}
		}

		armor->SetChengeFlg(false);	//�ύX�Ȃ�

	}

	return;

}

//�m�F�̑I������`�悷��
void UI::DrawCheck(const char *check_msg)
{
	this->UiImage->Draw(PLAY_WIN_X, PLAY_WIN_Y);	//�E�B���h�E�`��
	
	DrawFormatString(PLAY_WIN_TEXT_X, PLAY_WIN_TEXT_Y, GetColor(255, 255, 255), "%s", check_msg);	//�m�F���b�Z�[�W�`��

	int Height = GetFontSize();	//�����擾

	this->Yes_No->Draw(PLAY_WIN_TEXT_X, PLAY_WIN_TEXT_Y + Height);	//�͂��A�������̑I�����`��

	return;

}
