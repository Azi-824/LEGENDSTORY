//PLAYER.cpp
//�v���C���[�N���X

//############## �w�b�_�t�@�C���ǂݍ��� ################
#include "PLAYER.hpp"

//############## �N���X��` ##################

//�R���X�g���N�^
PLAYER::PLAYER()
{

	this->Collision = new COLLISION();		//�����蔻��̗̈���쐬

	this->sikaku_draw = new SIKAKU();		//�`��̈���쐬

	this->Weapon = new WEAPON();			//����𐶐�
	this->Armor = new ARMOR();				//�h��𐶐�

	this->Item = new ITEM();				//�A�C�e���𐶐�

	return;
}

//�f�X�g���N�^
PLAYER::~PLAYER()
{
	delete this->Anime;				//Anime��j��
	delete this->Collision;			//Collision��j��
	delete this->sikaku_draw;		//sikaku_draw��j��
	delete this->Weapon;			//Weapon��j��
	delete this->Armor;				//Armor��j��
	delete this->Item;				//Item��j��

	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Skil.swap(v);		//��ƒ��g�����ւ���

	return;
}

//***************************** �������A�ݒ�֌W **********************************
//�����ݒ�
bool PLAYER::SetInit()
{
	this->Dist = (int)FLONT;					//���������ݒ�
	this->MoveSpeed = PLAYE_DEFAULT_MOVESPEED;	//�����ړ����x�ݒ�

	//�����֌W
	//�ǂݍ��񂾃Z�[�u�f�[�^����A����A�h��𑕔����Ă��邩���肷��
	if (this->Equip_WeaponCode != PLAYER_INIT_VALUE)	//����R�[�h�������l����Ȃ����
	{
		this->EquipAtk = this->Weapon->GetAtk(this->Equip_WeaponCode);	//�����R�[�h����ɁA�����̍U���͂��擾
		this->Weapon->SetEquipFlg(this->Equip_WeaponCode, true);		//����𑕔����Ă���
	}
	else		//�����l�������ꍇ
	{
		this->EquipAtk = 0;	//������
	}

	if (this->Equip_ArmorCode != PLAYER_INIT_VALUE)	//�h��R�[�h�������l����Ȃ����
	{
		this->EquipDef = this->Armor->GetDef(this->Equip_ArmorCode);	//�����R�[�h����ɁA�����̖h��͂��擾
		this->Armor->SetEquipFlg(this->Equip_ArmorCode, true);			//�h��𑕔����Ă���
	}
	else	//�����l�������ꍇ
	{
		this->EquipDef = 0;	//������
	}

	this->Anime->SetSize();	//�摜�̃T�C�Y�ݒ�

	this->IsKeyDown = false;//�L�[�{�[�h������Ă��Ȃ�
	this->IsKeyOperation = true;	//�L�[����\
	this->IsMenu = false;	//���j���[�E�B���h�E�`�悳��Ă��Ȃ�

	this->ChengeMapKind = (int) MAP_CHENGE_NONE;	//�}�b�v�؂�ւ��Ȃ�

	this->BattleInit();		//�퓬�֌W�̗v�f������


	//�`��̈�쐬
	this->sikaku_draw->SetValue(this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->Anime->GetWidth(),
		this->Anime->GetHeight());

	//�����蔻��̈�쐬
	this->Collision->SetValue(this->sikaku_draw->Left + RECT_STAGGER,
		this->sikaku_draw->Top,
		this->Anime->GetWidth() - RECT_STAGGER * 2,
		this->Anime->GetHeight());

	return true;
}

//�A�j���[�V�����摜�ݒ�
/*
���@���Fconst char *�F�摜�̃f�B���N�g��
���@���Fconst char *�F�摜�̖��O
���@���Fint�F�摜�̑�������
���@���Fint�F�摜�̉������̕�����
���@���Fint�F�摜�̏c�����̕�����
���@���Fint�F�摜�̕������ꂽ���̑傫��
���@���Fint�F�摜�̕������ꂽ�c�̑傫��
���@���Fdouble�F���̉摜�ɕύX���鑬��
���@���Fbool�F�A�j���[�V���������[�v���邩�ǂ���
*/
bool PLAYER::SetAnime(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	this->Anime = new ANIMATION(dir, name, SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
	if (this->Anime->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s

	return true;

}

//�퓬�Ŏg�p������̂�����������
void PLAYER::BattleInit(void)
{
	this->BP = START_BP;	//BP��������
	this->UseBPNum = 0;		//�g�p����BP��������

	this->ChoiseSkil = -1;	//�g�p����X�L�����Z�b�g
	this->RecvDamege = 0;	//�󂯂�_���[�W���Z�b�g

	this->IsActMsg = false;		//�s�����b�Z�[�W�\���������Z�b�g
	this->IsBattleWin = false;	//�퓬�ɏ������������Z�b�g
	this->LevelUp_flg = false;//���x���A�b�v���b�Z�[�W�t���O���Z�b�g

	return;
}

//*********************** �X�e�[�^�X�֌W ******************************
//�Z�b�^

//���݂�MP�ݒ�
void PLAYER::SetMP(int mp)
{
	this->NowMP = mp;
}

//�g�p����X�L���ݒ�
void PLAYER::SetChoiseSkil(int type)
{
	this->ChoiseSkil = this->Skil[type];		//�w�肳�ꂽ�X�L�����A�g�p����X�L���Ƃ��Đݒ�
	return;
}

//�Q�b�^
//���O�擾
const char * PLAYER::GetName(void)
{
	return this->Name.c_str();
}

//���x���擾
int PLAYER::GetLevel(void)
{
	return this->Level;
}

//�o���l�̍ő�l�擾
int PLAYER::GetMaxEXP(void)
{
	return this->MaxEXP;
}

//���݂̌o���l�擾
int PLAYER::GetEXP(void)
{
	return this->NowEXP;
}

//�ő�̗͎擾
int PLAYER::GetMaxHP(void)
{
	return this->MaxHP;
}

//���݂̗͎̑擾
int PLAYER::GetHP(void)
{
	return this->NowHP;
}

//�ő�MP�擾
int PLAYER::GetMaxMP(void)
{
	return this->MaxMP;
}

//���݂�MP�擾
int PLAYER::GetMP(void)
{
	return this->NowMP;
}

//�U���͎擾
int PLAYER::GetATK(void)
{
	return this->ATK;
}

//�h��͎擾
int PLAYER::GetDEF(void)
{
	return this->DEF;
}

//���x�擾
int PLAYER::GetSPD(void)
{
	return this->SPD;
}

//�g�p����X�L�����擾
int PLAYER::GetChoiseSkil(void)
{
	return this->ChoiseSkil;
}

//�����Ă��邩�擾
bool PLAYER::GetIsArive()
{
	return this->IsArive;
}

//*************************** �L�[�֌W *****************************
//�L�[����\���ݒ�
void PLAYER::SetIsKeyOpe(bool iskeyope)
{
	this->IsKeyOperation = iskeyope;
	if (!this->IsKeyOperation)	//�L�[����s�̂Ƃ���
	{
		this->IsKeyDown = false;	//�L�[����s�̂Ƃ��́A�L�[���͂Ȃ��ɐݒ�
	}
	return;
}

//�L�[�{�[�h����ł��邩�擾
bool PLAYER::GetIsKeyOpe()
{
	return this->IsKeyOperation;
}

//�L�[���͂����邩�擾
bool PLAYER::GetIsKeyDown()
{
	return this->IsKeyDown;
}

//�L�[�����֌W
//����
void PLAYER::Operation(KEYDOWN *keydown, COLLISION *map[][MAP_YOKO])
{
	if (this->IsKeyOperation)	//�L�[����\�Ȃ�
	{
		if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_W))		//���j���[�`�撆�łȂ��AW�L�[�������Ă���Ƃ�
		{
			this->IsKeyDown = true;		//�L�[���͂���
			this->Dist = BACK;			//�ړ���������ɂ���

			//�̈��������ւ��炷
			this->Collision->Top -= RECT_STAGGER;
			this->Collision->Bottom -= RECT_STAGGER;

			//�}�b�v�Ƃ̓����蔻��
			if (this->CheckDetectionMap(map) == false)	//�ʍs�ł���Ȃ�
			{
				this->MoveUp();				//��ֈړ�
			}

		}
		else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_S))	//���j���[�`�撆�łȂ��AS�L�[�������Ă���Ƃ�
		{
			this->IsKeyDown = true;		//�L�[���͂���
			this->Dist = FLONT;			//�ړ�������

			//�̈���������ւ��炷
			this->Collision->Top += RECT_STAGGER;
			this->Collision->Bottom += RECT_STAGGER;

			//�}�b�v�Ƃ̓����蔻��
			if (this->CheckDetectionMap(map) == false)	//�ʍs�ł���Ȃ�
			{
				this->MoveDown();				//���ֈړ�
			}


		}
		else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_A))	//���j���[�`�撆�łȂ��AA�L�[�������Ă���Ƃ�
		{
			this->IsKeyDown = true;		//�L�[���͂���
			this->Dist = LEFT;			//�ړ�������

			//�̈���������ւ��炷
			this->Collision->Left -= RECT_STAGGER;
			this->Collision->Right -= RECT_STAGGER;

			//�}�b�v�Ƃ̓����蔻��
			if (this->CheckDetectionMap(map) == false)	//�ʍs�ł���Ȃ�
			{
				this->MoveLeft();				//���ֈړ�
			}

		}
		else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_D))	//���j���[�`�撆�łȂ��AD�L�[�������Ă���Ƃ�
		{
			this->IsKeyDown = true;		//�L�[���͂���
			this->Dist = RIGHT;			//�ړ������E

			//�̈�������E�ւ��炷
			this->Collision->Left += RECT_STAGGER;
			this->Collision->Right += RECT_STAGGER;

			//�}�b�v�Ƃ̓����蔻��
			if (this->CheckDetectionMap(map) == false)	//�ʍs�ł���Ȃ�
			{
				this->MoveRight();				//�E�ֈړ�
			}

		}
		else
		{
			this->IsKeyDown = false;	//�L�[���͂Ȃ�
		}

		//�`��̈�Đݒ�
		this->sikaku_draw->SetValue(
			this->sikaku_draw->Left,
			this->sikaku_draw->Top,
			this->sikaku_draw->Width,
			this->sikaku_draw->Height);

		//�̈�Đݒ�
		this->Collision->SetValue(this->sikaku_draw->Left + RECT_STAGGER,
			this->sikaku_draw->Top,
			this->Anime->GetWidth() - RECT_STAGGER * 2,
			this->Anime->GetHeight());

	}

	return;

}

//��ֈړ�
void PLAYER::MoveUp()
{
	if (this->sikaku_draw->Top - this->MoveSpeed >= GAME_TOP)
	{
		this->sikaku_draw->Top -= this->MoveSpeed;	//�����蔻��ƁA�`��ʒu����ֈړ�
	}
	else
	{
		this->ChengeMapKind = (int)MAP_CHENGE_UP;//�؂�ւ������A��
	}

	return;
}

//���ֈړ�
void PLAYER::MoveDown()
{
	if (this->sikaku_draw->Bottom + this->MoveSpeed <= GAME_HEIGHT)
	{
		this->sikaku_draw->Top += this->MoveSpeed;	//���ֈړ�
	}
	else
	{
		this->ChengeMapKind = (int)MAP_CHENGE_DOWN;	//�؂�ւ������A��
	}
	return;
}

//���ֈړ�
void PLAYER::MoveLeft()
{
	if (this->sikaku_draw->Left - this->MoveSpeed >= GAME_LEFT)
	{
		this->sikaku_draw->Left -= this->MoveSpeed;	//���ֈړ�
	}
	else
	{
		this->ChengeMapKind = (int)MAP_CHENGE_LEFT;	//�؂�ւ������A��
	}
	return;
}

//�E�ֈړ�
void PLAYER::MoveRight()
{
	if (this->sikaku_draw->Right + this->MoveSpeed <= GAME_WIDTH)
	{
		this->sikaku_draw->Left += this->MoveSpeed;	//�E�ֈړ�
	}
	else
	{
		this->ChengeMapKind = (int)MAP_CHENGE_RIGHT;	//�؂�ւ������A�E
	}
	return;
}

//********************** �ʒu�֌W *****************************
//�ʒu��ݒ�
//�����Fint�FX�ʒu�𑊑ΓI�Ɏw��
//�����Fint�FY�ʒu�𑊑ΓI�Ɏw��
void PLAYER::SetPosRelative(int x, int y)
{
	this->Collision->Left += x;	//X�ʒu��ݒ�
	this->Collision->Top += y;	//Y�ʒu��ݒ�

	this->sikaku_draw->Left += x;
	this->sikaku_draw->Top += y;

	//�`��̈�Đݒ�
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);


	//�̈�Đݒ�
	this->Collision->SetValue(
		this->Collision->Left,
		this->Collision->Top,
		this->Collision->Width,
		this->Collision->Height);

	return;
}

//�ʒu��ݒ�
//�����Fint�FX�ʒu���Βl�Ŏw��
//�����Fint�FY�ʒu���Βl�Ŏw��
void PLAYER::SetPosAbsolute(int x, int y)
{
	this->Collision->Left = x;	//X�ʒu��ݒ�
	this->Collision->Top = y;	//Y�ʒu��ݒ�

	this->sikaku_draw->Left = x;
	this->sikaku_draw->Top = y;

	//�`��̈�Đݒ�
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);


	//�̈�Đݒ�
	this->Collision->SetValue(
		this->Collision->Left,
		this->Collision->Top,
		this->Collision->Width,
		this->Collision->Height);

	return;
}

//���݂̈ʒu���擾
/*
�����Fint *�FX�ʒu���Z�b�g����
�����Fint *�FY�ʒu���Z�b�g����
*/
void PLAYER::GetNowPos(int *x, int *y)
{
	*x = this->sikaku_draw->Left;	//X�ʒu�ݒ�
	*y = this->sikaku_draw->Top;	//Y�ʒu�ݒ�
	return;
}

//���݂̈ʒu��ݒ�
/*
�����Fint�F���݂�X�ʒu
�����Fint�F���݂�Y�ʒu
*/
void PLAYER::SetNowPos(int x, int y)
{
	this->sikaku_draw->Left = x;
	this->sikaku_draw->Top = y;

	//�`��̈�Đݒ�
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);

	//�̈�Đݒ�
	this->Collision->SetValue(
		this->sikaku_draw->Left + RECT_STAGGER,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width - RECT_STAGGER * 2,
		this->sikaku_draw->Height);


}

//********************************* �}�b�v�֌W ***********************************
//�}�b�v�؂�ւ��̎�ރ��Z�b�g
void PLAYER::ResetChengeMapKind(void)
{
	this->ChengeMapKind = PLAYER_INIT_VALUE;	//������
	return;
}

//�}�b�v�؂�ւ��������Ƃ��Ƀv���C���[�̈ʒu��ݒ�
//�����Fint�F�؂�ւ�������
void PLAYER::SetChengePos(int kind)
{
	switch (kind)	//�؂�ւ��������ɏ���
	{

	case (int)MAP_CHENGE_UP:	//��֐؂�ւ���Ƃ��A��������

		this->SetPosRelative(0, GAME_HEIGHT - (this->Collision->Height + RECT_STAGGER));	//�ʒu���C��

		break;

	case (int)MAP_CHENGE_DOWN:	//���֐؂�ւ���Ƃ��A��������

		this->SetPosRelative(0, -(this->Collision->Top - RECT_STAGGER));	//�ʒu���C��

		break;

	case (int)MAP_CHENGE_LEFT:	//���֐؂�ւ���Ƃ��A��������

		this->SetPosRelative(GAME_WIDTH - (this->Collision->Width + RECT_STAGGER), 0);	//�ʒu���C��

		break;

	case (int)MAP_CHENGE_RIGHT:	//�E�֐؂�ւ���Ƃ��A��������

		this->SetPosRelative(-(this->Collision->Left - RECT_STAGGER), 0);	//�ʒu���C��

		break;

	default:
		break;
	}

	return;

}

//�؂�ւ���}�b�v�̎�ނ��擾
int PLAYER::GetChengeMapKind()
{
	return this->ChengeMapKind;
}

//�}�b�v�Ƃ̓����蔻��(���������ꏊ���擾���Ȃ�)
bool PLAYER::CheckDetectionMap(COLLISION * map[][MAP_YOKO])
{

	for (int tate = 0; tate < MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO; yoko++)
		{
			//�L�����N�^�[�̓������Ă���ꏊ���擾
			if (map[tate][yoko]->DetectionCheck(this->Collision))
			{
				return true;
			}
		}
	}

	return false;
}

//*************************** ���j���[�֌W *******************************
//���j���[�`�撆���ݒ�
void PLAYER::SetIsMenu(bool ismenu)
{
	this->IsMenu = ismenu;
	return;
}

//���j���[�`�撆���擾
bool PLAYER::GetIsMenu()
{
	return this->IsMenu;
}

//************************* �퓬�֌W ****************************
//�퓬�ɏ��������擾
void PLAYER::SetIsBattleWin(bool isbattlewin)
{
	this->IsBattleWin = isbattlewin;
	return;
}

//���x���A�b�v�������擾
void PLAYER::SetLevelUpFlg(bool start_flg)
{
	this->LevelUp_flg = start_flg;
	return;
}

//�󂯂�_���[�W���擾
int PLAYER::GetRecvDamege()
{
	return this->RecvDamege;
}

//�s�����b�Z�[�W�\�������擾
bool PLAYER::GetIsActMsg()
{
	return this->IsActMsg;
}

//�퓬�ɏ��������擾
bool PLAYER::GetIsBattleWin()
{
	return this->IsBattleWin;
}

//���x���A�b�v�t���O�擾
bool PLAYER::GetLevelUpFlg()
{
	return this->LevelUp_flg;
}

//************************** �����֌W *********************************
//����֌W
//�����U���͎擾
int PLAYER::GetEquipAtk(void)
{
	return this->EquipAtk;	//�����U���͎擾
}

//����𑕔�����
void PLAYER::EquipWeapon(int element)
{

	this->Equip_WeaponCode = this->Weapon->GetCode(element);	//�����̃R�[�h�ԍ����擾

	this->EquipAtk = this->Weapon->GetAtk(this->Equip_WeaponCode);	//�����R�[�h����ɁA�����̍U���͂��擾

	this->Weapon->SetEquipFlg(this->Equip_WeaponCode, true);	//����𑕔����Ă���

	return;

}

//����N���X���擾
WEAPON * PLAYER::GetWeaponClass(void)
{
	return this->Weapon;
}

//����̍U���͂�ݒ�
void PLAYER::SetWeaponAtk(LIST_WEAPON *list_weapon)
{

	for (int i = 0; i < this->Weapon->GetSize(); ++i)	//���퐔���J��Ԃ�
	{
		this->Weapon->SetAtk(list_weapon->GetPower(this->Weapon->GetCode(i)));	//����U���͐ݒ�
	}

	return;
}

//�h���b�v��������̒ǉ�
void PLAYER::AddDropWeapon(int code, int value)
{
	//����o�^
	if (this->Weapon->Add(code))		//���o�^��������
	{
		this->Weapon->SetAtk(value);	//�U���͓o�^
	}
	return;
}

//�h��֌W
//�����h��͎擾
int PLAYER::GetEquipDef(void)
{
	return this->EquipDef;	//�����h��͎擾
}

//�h��𑕔�����
void PLAYER::EquipArmor(int element)
{

	this->Equip_ArmorCode = this->Armor->GetCode(element);	//�����̃R�[�h�ԍ����擾

	this->EquipDef = this->Armor->GetDef(this->Equip_ArmorCode);	//�����R�[�h����ɁA�����̖h��͂��擾

	this->Armor->SetEquipFlg(this->Equip_ArmorCode, true);	//�h��𑕔����Ă���

	return;

}

//�h��N���X���擾
ARMOR * PLAYER::GetArmorClass(void)
{
	return this->Armor;
}

//�h��̖h��͐ݒ�
void PLAYER::SetArmorDef(LIST_ARMOR *list_armor)
{
	for (int i = 0; i < this->Armor->GetSize(); ++i)	//�h����J��Ԃ�
	{
		this->Armor->SetDef(list_armor->GetDefense(this->Armor->GetCode(i)));	//�h��h��͐ݒ�
	}
	return;
}

//�h���b�v�����h��̒ǉ�
void PLAYER::AddDropArmor(int code, int value)
{
	//�h��o�^
	if (this->Armor->Add(code))	//�h����o�^��������
	{
		this->Armor->SetDef(value);	//�h��͐ݒ�
	}
	return;
}

//************************** �A�C�e���֌W ***************************
//�A�C�e���g�p����
bool PLAYER::UseItem(int code)
{
	if (this->Item->GetItemType(code) == ITEM_TYPE_HP)	//�A�C�e���^�C�v��HP�񕜂̏ꍇ
	{

		if (this->NowHP == this->MaxHP)	//���݂�HP�����^����������
		{
			return false;		//�A�C�e���͎g�p�ł��Ȃ�
		}

		this->NowHP += this->Item->GetRecovery(code);	//�񕜗ʂ��擾���A���݂�HP�ɉ�����

		if (this->NowHP > this->MaxHP)	//�ő�HP��葽���Ȃ�����
		{
			this->NowHP = this->MaxHP;	//���݂�HP���ő�HP�Ɠ����ɂ���
		}

	}
	else if (this->Item->GetItemType(code) == ITEM_TYPE_MP)	//�A�C�e���^�C�v��MP�񕜂̏ꍇ
	{

		if (this->NowMP == this->MaxMP)		//���݂�MP�����^����������
		{
			return false;		//�A�C�e���͎g�p�ł��Ȃ�
		}

		this->NowMP += this->Item->GetRecovery(code);	//�񕜗ʂ��擾���A���݂�MP�ɉ�����

		if (this->NowMP > this->MaxMP)		//�ő�MP��葽���Ȃ�����
		{
			this->NowMP = this->MaxMP;		//���݂�MP���ő�MP�Ɠ����ɂ���
		}
	}

	this->Item->DecreasePossession(code);	//�A�C�e���̏����������炷

	return true;
}

//�A�C�e���N���X���擾
ITEM * PLAYER::GetItemClass(void)
{
	return this->Item;
}

//�A�C�e���̉񕜗ʂ�ݒ�
void PLAYER::SetItemRecovery(LIST_ITEM *list_item)
{
	for (int i = 0; i < this->Item->GetSize(); ++i)	//�A�C�e�������J��Ԃ�
	{
		this->Item->SetRecovery(list_item->GetRecovery(this->Item->GetCode(i)),	//�A�C�e���񕜗ʐݒ�
			list_item->GetItemType(this->Item->GetCode(i)));					//�A�C�e���^�C�v�ݒ�	
	}
}

//�A�C�e���̒ǉ�����
void PLAYER::AddDropItem(int code, int value, char type)
{
	this->Item->AddItem(code, value, type);	//�A�C�e���ǉ�

	return;
}

//************************ �Z�[�u�f�[�^�֌W ***************************
//�Z�[�u�f�[�^�ǂݍ���
bool PLAYER::LoadData(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ifstream ifs(LoadFile.c_str());	//�t�@�C���ǂݎ��

	if (!ifs)		//�t�@�C���I�[�v�����s��
	{
		std::string ErrorMsg(PLAYER_DATA_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadFile;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(PLAYER_DATA_ERROR_TTILE),
			MB_OK);

		return false;	//�ǂݍ��ݎ��s

	}


	std::string buf;

	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	this->Name = buf.c_str();		//���O�ǂݍ���

	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	this->Level = atoi(buf.c_str());//���x���ǂݍ���

	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	this->MaxEXP = atoi(buf.c_str());//�o���l�̍ő�l�ǂݍ���

	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	this->NowEXP = atoi(buf.c_str());//���݂̌o���l�ǂݍ���

	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	this->MaxHP = atoi(buf.c_str());//�ő�HP�ǂݍ���

	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	this->NowHP = atoi(buf.c_str());//���݂�HP�ǂݍ���

	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	this->MaxMP = atoi(buf.c_str());//�ő�MP�ǂݍ���

	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	this->NowMP = atoi(buf.c_str());//���݂�MP�ǂݍ���

	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	this->ATK = atoi(buf.c_str());	//ATK�ǂݍ���

	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	this->DEF = atoi(buf.c_str());	//DEF�ǂݍ���

	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	this->SPD = atoi(buf.c_str());	//SPD�ǂݍ���

	int x = 0, y = 0;				//�ʒu�擾�p
	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	x = atoi(buf.c_str());			//X�ʒu�i�[
	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	y = atoi(buf.c_str());			//Y�ʒu�i�[

	this->SetNowPos(x, y);			//���݈ʒu�ݒ�

	int size = 0;					//�v�f��������ϐ�
	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	size = atoi(buf.c_str());		//�X�L���̐����擾

	int check = 0;					//���s�������Ă��Ȃ����m�F���邽�߂Ɏg�p
	for (int i = 0; i < size; ++i)	//�X�L���̐������J��Ԃ�
	{

		if (i == size - 1)	//�Ō�̗v�f��������
		{
			std::getline(ifs, buf, '\n');	//���s�܂œǂݍ���
		}
		else	//�Ōザ��Ȃ����
		{
			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		}

		this->Skil.push_back(atoi(buf.c_str()));	//�X�L���ǂݍ���
	}


	//******************* �A�C�e���f�[�^�ǂݍ��� ************************
	std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
	size = atoi(buf.c_str());		//�A�C�e�����ǂݍ���

	int code = 0, posse = 0;		//�R�[�h�ԍ��Ə�����

	for (int i = 0; i < size; ++i)	//�A�C�e���������J��Ԃ�
	{
		std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		code = (atoi(buf.c_str()));		//�A�C�e���R�[�h�ǂݍ���

		if (i == size - 1)	//�Ō�̗v�f��������
		{
			std::getline(ifs, buf, '\n');	//���s�܂œǂݍ���
		}
		else	//�Ōザ��Ȃ����
		{
			std::getline(ifs, buf, ',');	//�J���}�܂œǂݍ���
		}

		posse = (atoi(buf.c_str()));		//�������ݒ�

		this->Item->LoadData(code, posse);	//�ǂݍ��񂾃A�C�e���f�[�^��ݒ�
	}

	//************************ ����f�[�^�ǂݍ��� ****************************
	std::getline(ifs, buf, ',');		//�J���}�܂œǂݍ���
	size = atoi(buf.c_str());			//���퐔�ǂݍ���

	for (int i = 0; i < size; ++i)	//���퐔���J��Ԃ�
	{
		std::getline(ifs, buf, ',');		//�J���}�܂œǂݍ���
		code = atoi(buf.c_str());			//����R�[�h�ǂݍ���

		if (i == size - 1)	//�Ō�̗v�f��������
		{
			std::getline(ifs, buf, '\n');	//���s�܂œǂݍ���
		}
		else	//�Ōザ��Ȃ����
		{
			std::getline(ifs, buf, ',');		//�J���}�܂œǂݍ���
		}

		posse = atoi(buf.c_str());			//�������ǂݍ���

		this->Weapon->LoadData(code, posse);	//�ǂݍ��񂾃f�[�^��ݒ�

	}

	//*********************** �h��f�[�^�ǂݍ��� ****************************
	std::getline(ifs, buf, ',');		//�J���}�܂œǂݍ���
	size = atoi(buf.c_str());			//�h��ǂݍ���
	for (int i = 0; i < size; ++i)	//�h����J��Ԃ�
	{
		std::getline(ifs, buf, ',');		//�J���}�܂œǂݍ���
		code = atoi(buf.c_str());			//�h��R�[�h�ǂݍ���

		if (i == size - 1)	//�Ō�̗v�f��������
		{
			std::getline(ifs, buf, '\n');	//���s�܂œǂݍ���
		}
		else	//�Ōザ��Ȃ����
		{
			std::getline(ifs, buf, ',');		//�J���}�܂œǂݍ���
		}

		posse = atoi(buf.c_str());			//�������ǂݍ���

		this->Armor->LoadData(code, posse);	//�ǂݍ��񂾃f�[�^��ݒ�

	}

	//�������Ă��镐��Ɩh��̃R�[�h�ԍ���ǂݍ���
	std::getline(ifs, buf, ',');				//�J���}�܂œǂݍ���
	this->Equip_WeaponCode = atoi(buf.c_str());	//����R�[�h�ݒ�

	std::getline(ifs, buf, ',');				//�J���}�܂œǂݍ���
	this->Equip_ArmorCode = atoi(buf.c_str());	//�h��R�[�h�ݒ�

	return true;	//�ǂݍ��ݐ���

}

//�Z�[�u
bool PLAYER::Save(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ofstream ofs(LoadFile.c_str(), std::ios_base::ate);	//�t�@�C���I�[�v��

	if (!ofs)		//�t�@�C���I�[�v�����s��
	{
		std::string ErrorMsg(PLAYER_DATA_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadFile;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(PLAYER_DATA_ERROR_TTILE),
			MB_OK);

		return false;		//�Z�[�u���s

	}

	//�v���C���[���������o��
	ofs << this->Name << ',';		//���O�����o��
	ofs << this->Level << ',';		//���x��
	ofs << this->MaxEXP << ',';		//�o���l�̍ő�l
	ofs << this->NowEXP << ',';		//���݂̌o���l

	ofs << this->MaxHP << ',';		//�ő�HP
	ofs << this->NowHP << ',';		//���݂�HP
	ofs << this->MaxMP << ',';		//�ő�MP
	ofs << this->NowMP << ',';		//���݂�MP

	ofs << this->ATK << ',';		//�U����
	ofs << this->DEF << ',';		//�h���
	ofs << this->SPD << ',';		//����

	int x = 0, y = 0;				//���݂̈ʒu�擾�p
	this->GetNowPos(&x, &y);		//���݈ʒu�擾
	ofs << x << ',' << y << ',';	//���݈ʒu�Z�[�u

	ofs << this->Skil.size() << ',';//�X�L������������

	for (int i = 0; i < this->Skil.size(); ++i)		//�X�L���̐�����������
	{
		if (i == this->Skil.size() - 1)			//�Ō�X�L���̏������݂�������
		{
			ofs << this->Skil[i] << '\n';			//�X�L����������(�Ō�͉��s)
		}
		else	//�Ōザ��Ȃ�������
		{
			ofs << this->Skil[i] << ',';			//�X�L����������(�J���}�ŋ�؂�)
		}

	}

	//************************* �A�C�e���f�[�^�������� *******************************
	ofs << this->Item->GetSize() << ',';	//�A�C�e������������

	for (int i = 0; i < this->Item->GetSize(); ++i)	//�o�^���Ă���A�C�e���̐����J��Ԃ�
	{
		ofs << this->Item->GetCode(i) << ',';		//�A�C�e���R�[�h�����o��
		if (i == this->Item->GetSize() - 1)	//�Ō�̏������݂�������
		{
			ofs << this->Item->GetPossession(this->Item->GetCode(i)) << '\n';	//�����������o��(�Ō�͉��s)
		}
		else	//�Ōザ��Ȃ�������
		{
			ofs << this->Item->GetPossession(this->Item->GetCode(i)) << ',';	//�����������o��(�J���}�ŋ�؂�)
		}

	}

	//************************* ����f�[�^�����o�� *********************************
	ofs << this->Weapon->GetSize() << ',';	//���퐔�����o��

	for (int i = 0; i < this->Weapon->GetSize(); ++i)//����̐����J��Ԃ�
	{
		ofs << this->Weapon->GetCode(i) << ',';	//����R�[�h�����o��
		if (i == this->Weapon->GetSize() - 1)	//�Ō�̏������݂�������
		{
			ofs << this->Weapon->GetPossession(this->Weapon->GetCode(i)) << '\n';	//�����������o��(�Ō�͉��s)
		}
		else	//�Ōザ��Ȃ�������
		{
			ofs << this->Weapon->GetPossession(this->Weapon->GetCode(i)) << ',';	//�����������o��(�J���}�ŋ�؂�)
		}
	}

	//**************************** �h��f�[�^�����o�� ******************************
	ofs << this->Armor->GetSize() << ',';	//�h������o��

	for (int i = 0; i < this->Armor->GetSize(); ++i)	//�h����J��Ԃ�
	{
		ofs << this->Armor->GetCode(i) << ',';			//�h��R�[�h�����o��
		if (i == this->Armor->GetSize() - 1)	//�Ō�̏������݂�������
		{
			ofs << this->Armor->GetPossession(this->Armor->GetCode(i)) << '\n';	//�����������o��(�Ō�͉��s)
		}
		else	//�Ōザ��Ȃ�������
		{
			ofs << this->Armor->GetPossession(this->Armor->GetCode(i)) << ',';	//�����������o��(�J���}�ŋ�؂�)
		}
	}

	//�������Ă��鑕���R�[�h�����o��
	ofs << this->Equip_WeaponCode << ',';	//�������Ă��镐��R�[�h�����o��
	ofs << this->Equip_ArmorCode << '\n';	//�������Ă���h��R�[�h�����o��

	return true;		//�Z�[�u����

}

//************************* BP�֌W ***************************
//BP�擾
int PLAYER::GetBP(void)
{
	return this->BP;
}

//BP���Z
bool PLAYER::AddBP(void)
{
	if (this->BP < MAX_BP)	//���݂�BP��BP�̍ő�l��菬����������
	{
		++this->BP;
		return true;	//BP�𑝂₹��
	}
	return false;		//BP�𑝂₹�Ȃ�����
}

//�g�p����BP���擾
int PLAYER::GetUseBP(void)
{
	return this->UseBPNum;
}

//�g�p����BP�𑝂₷
bool PLAYER::PlusUseBP(void)
{
	if (this->UseBPNum < this->BP)	//�g�p����BP�����ݎ����Ă���BP�������Ȃ�������
	{
		if (this->UseBPNum < MAX_USE_BP)	//���݂̎g�pBP���A���Ŏg�p�ł���BP�������Ȃ�������
		{
			++this->UseBPNum;	//�g�p����BP�𑝂₷
			return true;	//���₹��
		}
	}
	return false;	//���₹�Ȃ�����
}

//�g�p����BP�����炷
bool PLAYER::MinusUseBP(void)
{
	if (this->UseBPNum > 0)	//�g�p����BP��0��葽��������
	{
		--this->UseBPNum;		//�g�p����BP�����炷
		return true;		//���点��
	}
	return false;	//���点�Ȃ�����
}

//BP�ɂ���ċ��������{�����擾(�_���[�W�v�Z���Ŏg�p)
double PLAYER::GetBPBoostValue(void)
{
	switch (this->UseBPNum)	//�g�p����BP�̐��ɂ���āA�Ԃ������{����ς���
	{

	case (int)USE_BP_1:	//�g�p����BP��1�̏ꍇ

		return BP_BOOST_LEVEL1;

		break;	//�g�p����BP��1�̂Ƃ������܂�

	case (int)USE_BP_2:	//BP2�̂Ƃ�

		return BP_BOOST_LEVEL2;

		break;	//BP2�̂Ƃ������܂�

	case (int)USE_BP_3:	//BP3�̂Ƃ�

		return BP_BOOST_LEVEL3;

		break;	//BP3�̂Ƃ������܂�

	default:	//����ȊO�̂Ƃ�(BP���g�p�̎��Ȃ�)

		return BP_BOOST_LEVEL0;

		break;
	}
}

//BP���g�p����
void PLAYER::BPUse(void)
{
	this->BP -= this->UseBPNum;	//�g�p������BP�����炷
	this->UseBPNum = 0;			//�g�p����BP�����Z�b�g
	return;
}

//************************** �_���[�W�֌W ************************
//�_���[�W�v�Z
void PLAYER::DamegeCalc(ENEMY *enemy, int choiecommand)
{

	double bp_value = this->GetBPBoostValue();	//BP�ɂ�鋭���{�����擾
	switch (choiecommand)		//�I�������R�}���h
	{

	case(int)COMMANDE_ATACK:				//�U����I�񂾎��̏�����������

		//�^����_���[�W�v�Z
		//�����U����(�U��+�����U��) * BP�̋����{�� - �G�h���
		enemy->SetRecvDamege((this->ATK + this->EquipAtk) * bp_value - enemy->GetDEF());

		//�󂯂�_���[�W�v�Z
		//�G�U���� - �����h���(�h��+�����h��) * BP�̋����{��
		this->RecvDamege = enemy->GetATK() - (this->DEF + this->EquipDef) * bp_value;

		break;					//�U����I�񂾎��̏��������܂�

	case (int)COMMANDE_DEFENSE:			//�h���I�񂾎��̏�����������

		//�^����_���[�W�v�Z
		enemy->SetRecvDamege(0);		//�G�A�󂯂�_���[�W0

		//�󂯂�_���[�W�v�Z
		//�h��͂��������ă_���[�W�v�Z
		//�G�U���� - �����h���((�h��+�����h��) * �h�䋭���l) * BP�̋����{��
		this->RecvDamege = enemy->GetATK() - ((this->DEF + this->EquipDef) * DEF_BOOST) * bp_value;

		break;					//�h���I�񂾎��̏��������܂�

	case (int)COMMANDE_MAGIC:			//���@��I�񂾎��̏�����������

		//�^����_���[�W�v�Z
		//�����̍U���͂��������ă_���[�W�v�Z
		//���@�U���͂�ǉ����āA�ʏ�U���ƕ�����\��
		//�����U����((�U��+�����U��) * ���@�����l) * BP�̋����{�� - �G�h���
		enemy->SetRecvDamege(((this->ATK + this->EquipAtk) * ATK_BOOST) * bp_value - enemy->GetDEF());

		//�󂯂�_���[�W�v�Z
		//�G�U���� - �����h���(�h��+�����h��) * BP�̋����{��
		this->RecvDamege = enemy->GetATK() - (this->DEF + this->EquipDef) * bp_value;

		break;					//���@��I�񂾎��̏��������܂�

	case(int)COMMANDE_ITEM:				//�A�C�e����I�񂾎��̏�����������

		//�^����_���[�W�v�Z
		//�^����_���[�W0
		enemy->SetRecvDamege(0);

		//�󂯂�_���[�W�v�Z
		//�G�U���� - �����h���(�h��+�����h��) * BP�̋����{��
		this->RecvDamege = enemy->GetATK() - (this->DEF + this->EquipDef) * bp_value;

		break;					//�A�C�e����I�񂾎��̏��������܂�

	default:
		break;
	}

	if (this->RecvDamege < 0)	//�󂯂�_���[�W��0��菭�Ȃ��Ƃ���
	{
		this->RecvDamege = 0;	//�󂯂�_���[�W0
	}

	if (enemy->GetRecvDamege() < 0)	//�G�ɗ^����_���[�W��0��菭�Ȃ��Ƃ���
	{
		enemy->SetRecvDamege(0);	//�^����_���[�W0
	}

	this->BPUse();	//BP���g�p����

	return;
}

//�_���[�W��^����
void PLAYER::DamegeSend(void)
{
	this->NowHP -= this->RecvDamege;	//���݂�HP����A�󂯂�_���[�W������

	if (this->NowHP <= 0)	//HP��0�ȉ��ɂȂ�����
	{
		this->NowHP = 0;		//HP��0
		this->IsArive = false;	//���S
	}

	return;

}

//************************* �`��֌W ******************************
//�`��ł��邩�擾
bool PLAYER::GetIsDraw()
{
	return this->IsDraw;
}

//�`��
void PLAYER::DrawWalk()
{
	if (this->IsDraw)		//�`�悵�Ă悢��
	{
		if (this->IsArive)	//�����Ă���Ƃ�
		{
			if (this->IsKeyDown)		//�L�[�{�[�h��������Ă���Ƃ�
			{
				this->Anime->Draw(this->sikaku_draw->Left, this->sikaku_draw->Top, this->Dist, true);	//�A�j���[�V�����ŕ`��

			}
			else						//�L�[�{�[�h��������Ă��Ȃ��Ƃ�
			{
				this->Anime->Draw(this->sikaku_draw->Left, this->sikaku_draw->Top, this->Dist, false);	//�ʏ�`��
			}
		}
	}
}

//************************* ���̑������֌W ************************
//�o���l�ǉ�����
void PLAYER::AddExp(int exp)
{
	this->NowEXP += exp;	//���݂̌o���l�ɉ��Z����

	if (this->NowEXP >= this->MaxEXP)		//���݂̌o���l���o���l�̍ő�l�ȏ�ɂȂ�����
	{
		int work = 0;	//�ޔ�p�ϐ�
		work = this->NowEXP - this->MaxEXP;	//�ő�l�𒴉߂�������ۊ�

		this->MaxEXP += EXP_INCREASE_VALUE * this->Level;	//�o���l�̍ő�l�𑝂₷(�o���l�̑����� * ���݂̃��x��)
		this->NowEXP = 0;		//���݂̌o���l��0�ɖ߂�
		this->NowEXP += work;	//���߂������̌o���l�����Z����

		//�X�e�[�^�X�̑�������
		this->MaxHP += HP_INCREASE_VALUE;	//�ő�HP�𑝂₷
		this->MaxMP += MP_INCREASE_VALUE;	//�ő�MP�𑝂₷
		this->ATK += ATK_INCREASE_VALUE;	//�U���͂𑝂₷
		this->DEF += DEF_INCREASE_VALUE;	//�h��͂𑝂₷
		this->SPD += SPD_INCREASE_VALUE;	//�����𑝂₷

		//HP��MP��S�񕜂�����
		this->NowHP = this->MaxHP;
		this->NowMP = this->MaxMP;

		this->Level++;			//���x������グ��
		this->LevelUp_flg = true;	//���x���A�b�v���b�Z�[�W�̕\�����X�^�[�g����
	}
	return;
}

//�񕜂�����
void PLAYER::Recovery(void)
{
	this->NowHP = this->MaxHP;	//HP��
	this->NowMP = this->MaxMP;	//MP��

	this->IsArive = true;		//�����Ă���

	return;
}
