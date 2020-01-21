//PLAYER.cpp
//�v���C���[�N���X

//############## �w�b�_�t�@�C���ǂݍ��� ################
#include "PLAYER.hpp"

//############## �N���X��` ##################

//�R���X�g���N�^
PLAYER::PLAYER()
{
	return;
}

//�f�X�g���N�^
PLAYER::~PLAYER()
{
	delete this->Anime;
	delete this->Collision;
	delete this->Ilast;
	delete this->sikaku_draw;

	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Skil.swap(v);		//��ƒ��g�����ւ���

	std::vector<bool> v2;			//���vector���쐬����
	this->Stopflg.swap(v2);			//��ƒ��g�����ւ���

	return;
}

//�����ݒ�
bool PLAYER::SetInit()
{
	this->Dist = FLONT;	//���������ݒ�
	this->MoveSpeed = 5;//�����ړ����x�ݒ�
	this->InKeyKind = -1;	//������Ă��Ȃ��Ƃ��́[1

	this->ChoiseSkil = this->Skil[0];	//�ŏ��͒ʏ�U�����g�p����X�L���Ƃ��Đݒ肷��

	this->SendDamege = 0;	//�^����_���[�W0
	this->RecvDamege = 0;	//�󂯂�_���[�W0

	this->Ilast->SetInit();	//�摜�����ݒ�
	this->IsKeyDown = false;//�L�[�{�[�h������Ă��Ȃ�
	this->IsMenu = false;	//���j���[�E�B���h�E�`�悳��Ă��Ȃ�
	this->IsActMsg = false;		//�s�����b�Z�[�W�\�����Ă��Ȃ�
	this->IsBattleWin = false;	//�퓬�ɏ����Ă��Ȃ�
	this->LevUpMsgStart_flg = false;	//���x���A�b�v���b�Z�[�W��\�����Ă��Ȃ�

	this->Stopflg.assign(DIST_KIND, false);	//�S�Ă̕����ֈړ�

	this->Collision = new COLLISION();		//�����蔻��̗̈���쐬
	this->Collision->SetValue(400, 400, this->Anime->GetWidth(),this->Anime->GetHeight());	//�����蔻��̗̈��ݒ�

	this->sikaku_draw = new SIKAKU();		//�`��̈���쐬
	this->sikaku_draw->SetValue(400, 400, this->Anime->GetWidth(), this->Anime->GetHeight());	//�����蔻��̗̈��ݒ�

	return true;
}

//�A�j���[�V�����摜�ݒ�
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
//���@���Fint�F�摜�̑�������
//���@���Fint�F�摜�̉������̕�����
//���@���Fint�F�摜�̏c�����̕�����
//���@���Fint�F�摜�̕������ꂽ���̑傫��
//���@���Fint�F�摜�̕������ꂽ�c�̑傫��
//���@���Fdouble�F���̉摜�ɕύX���鑬��
//���@���Fbool�F�A�j���[�V���������[�v���邩�ǂ���
bool PLAYER::SetAnime(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	this->Anime = new ANIMATION(dir, name, SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
	if (this->Anime->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s

	return true;

}

//���O�ݒ�
void PLAYER::SetName(const char *name)
{
	this->Name = name;
	return;
}

//�摜�ݒ�
bool PLAYER::SetImage(const char *dir, const char *name)
{
	this->Ilast = new CHARACTOR();
	if (this->Ilast->SetImage(dir, name) == false) { return false; }//�ǂݍ��ݎ��s

	return true;

}

//���x���ݒ�
void PLAYER::SetLevel(int level)
{
	this->Level = level;
	return;
}

//�o���l�̍ő�l�ݒ�
void PLAYER::SetMaxEXP(int maxexp)
{
	this->MaxEXP = maxexp;
	return;
}

//���݂̌o���l�ݒ�
void PLAYER::SetEXP(int exp)
{
	this->NowEXP = exp;
	return;
}

//�ő�HP�ݒ�
void PLAYER::SetMaxHP(int hp)
{
	this->MaxHP = hp;
	return;
}

//���݂�HP�ݒ�
void PLAYER::SetHP(int hp)
{
	this->NowHP = hp;
	return;
}

//�ő�MP�ݒ�
void PLAYER::SetMaxMP(int maxmp)
{
	this->MaxMP = maxmp;
	return;
}

//���݂�MP�ݒ�
void PLAYER::SetMP(int mp)
{
	this->NowMP = mp;
}

//�U���͐ݒ�
void PLAYER::SetATK(int atk)
{
	this->ATK = atk;
	return;
}

//�h��͐ݒ�
void PLAYER::SetDEF(int def)
{
	this->DEF = def;
	return;
}

//���x�ݒ�
void PLAYER::SetSPD(int spd)
{
	this->SPD = spd;
	return;
}

//�X�L���ꗗ��ݒ�
void PLAYER::SetSkil(int skil)
{
	this->Skil.push_back(skil);
	return;
}

//�g�p����X�L���ݒ�
void PLAYER::SetChoiseSkil(int type)
{
	this->ChoiseSkil = this->Skil[type];		//�w�肳�ꂽ�X�L�����A�g�p����X�L���Ƃ��Đݒ�
	return;
}

//�ړ����x�ݒ�
void PLAYER::SetMoveSpeed(int movespeed)
{
	this->MoveSpeed = movespeed;
	return;
}

//�����Ă��邩�ݒ�
void PLAYER::SetIsArive(bool Isarive)
{
	this->IsArive = Isarive;
	return;
}

//�L�[�{�[�h�ő���ł��邩�ݒ�
void PLAYER::SetKeyOperation(bool Iskeyoperation)
{
	this->IsKeyOperation = IsKeyOperation;
	return;
}

//�L�[���͂��肩�ݒ�
void PLAYER::SetIsKeyDown(bool Iskeydown)
{
	this->IsKeyDown = Iskeydown;
}

//�`��ł��邩�ݒ�
void PLAYER::SetIsDraw(bool Isdraw)
{
	this->IsDraw = IsDraw;
	return;
}

//�ʒu��ݒ�
//�����Fint�FX�ʒu�𑊑ΓI�Ɏw��
//�����Fint�FY�ʒu�𑊑ΓI�Ɏw��
void PLAYER::SetPosition(int x, int y)
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

//���j���[�`�撆���ݒ�
void PLAYER::SetIsMenu(bool ismenu)
{
	this->IsMenu = ismenu;
	return;
}

//�퓬�ɏ��������擾
void PLAYER::SetIsBattleWin(bool isbattlewin)
{
	this->IsBattleWin = isbattlewin;
	return;
}

//���x���A�b�v���b�Z�[�W���X�^�[�g�������擾
void PLAYER::SetLevUpMsgStartFlg(bool start_flg)
{
	this->LevUpMsgStart_flg = start_flg;
	return;
}

//�X�g�b�v���邩�ݒ�
void PLAYER::SetStopFlg(bool stop_flg)
{
	this->Stopflg.assign(DIST_KIND, false);
	this->Stopflg[this->InKeyKind] = stop_flg;
	return;
}

//�X�g�b�v�t���O���Z�b�g
void PLAYER::ResetStopFlg(void)
{
	this->Stopflg.assign(DIST_KIND, false);	
	return;
}

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

//�X�L���ꗗ�̐擪�v�f�擾
std::vector<int> PLAYER::GetSkil(void)
{
	return this->Skil;
}

//�ړ����x�擾
int PLAYER::GetMoveSpeed(void)
{
	return this->MoveSpeed;
}

//�����Ă��邩�擾
bool PLAYER::GetIsArive()
{
	return this->IsArive;
}

//�`��ł��邩�擾
bool PLAYER::GetIsDraw()
{
	return this->IsDraw;
}

//�L�[�{�[�h����ł��邩�擾
bool PLAYER::GetKeyOperation()
{
	return this->IsKeyOperation;
}

//�����蔻����擾
COLLISION * PLAYER::GetCollision()
{
	return this->Collision;
}

//���j���[�`�撆���擾
bool PLAYER::GetIsMenu()
{
	return this->IsMenu;
}

//�^����_���[�W���擾
int PLAYER::GetSendDamege()
{
	return this->SendDamege;
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

//�ړ������ǂ����擾
bool PLAYER::GetIsMove()
{
	return this->IsKeyDown;
}

//�퓬�ɏ��������擾
bool PLAYER::GetIsBattleWin()
{
	return this->IsBattleWin;
}

//���x���A�b�v���b�Z�[�W��\�����Ă��邩�擾
bool PLAYER::GetLevUpMsgStartFlg()
{
	return this->LevUpMsgStart_flg;
}

//�L�[���͂����邩�擾
bool PLAYER::GetIsKeyDown()
{
	return this->IsKeyDown;
}

//����
void PLAYER::Operation(KEYDOWN *keydown)
{

	if (this->IsMenu ==false && keydown->IsKeyDown(KEY_INPUT_W))		//���j���[�`�撆�łȂ��AW�L�[�������Ă���Ƃ�
	{
		this->IsKeyDown = true;		//�L�[���͂���
		this->Dist = BACK;			//�ړ���������ɂ���
		this->InKeyKind = (int)KEY_UP;	//�L�[���͂̎�ށA��
		if (this->Stopflg[(int)KEY_UP] == false)	//�X�g�b�v�t���O�������Ă��Ȃ����
		{
			this->MoveUp();				//��ֈړ�
		}
	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_S))	//���j���[�`�撆�łȂ��AS�L�[�������Ă���Ƃ�
	{
		this->IsKeyDown = true;		//�L�[���͂���
		this->Dist = FLONT;			//�ړ�������
		this->InKeyKind = (int)KEY_DOWN;	//�L�[���͂̎�ށA��
		if (this->Stopflg[(int)KEY_DOWN] == false)	//�X�g�b�v�t���O�������Ă��Ȃ����
		{
			this->MoveDown();			//���ֈړ�
		}
	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_A))	//���j���[�`�撆�łȂ��AA�L�[�������Ă���Ƃ�
	{
		this->IsKeyDown = true;		//�L�[���͂���
		this->Dist = LEFT;			//�ړ�������
		this->InKeyKind = (int)KEY_LEFT;	//�L�[���͂̎�ށA��
		if (this->Stopflg[(int)KEY_LEFT] == false)	//�X�g�b�v�t���O�������Ă��Ȃ����
		{
			this->MoveLeft();			//���ֈړ�
		}
	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_D))	//���j���[�`�撆�łȂ��AD�L�[�������Ă���Ƃ�
	{
		this->IsKeyDown = true;		//�L�[���͂���
		this->Dist = RIGHT;			//�ړ������E
		this->InKeyKind = (int)KEY_RIGHT;	//�L�[���͂̎�ށA�E
		if (this->Stopflg[(int)KEY_RIGHT] == false)	//�X�g�b�v�t���O�������Ă��Ȃ����
		{
			this->MoveRight();			//�E�ֈړ�
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
	this->Collision->SetValue(
		this->Collision->Left,
		this->Collision->Top,
		this->Collision->Width,
		this->Collision->Height);

	return;

}

//�`��
void PLAYER::DrawAnime()
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

//��ֈړ�
void PLAYER::MoveUp()
{
	if (this->sikaku_draw->Top - this->MoveSpeed >= GAME_TOP)
	{
		this->sikaku_draw->Top -= this->MoveSpeed;	//�����蔻��ƁA�`��ʒu����ֈړ�
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
	return;
}

//���ֈړ�
void PLAYER::MoveLeft()
{
	if (this->sikaku_draw->Left - this->MoveSpeed >= GAME_LEFT)
	{
		this->sikaku_draw->Left -= this->MoveSpeed;	//���ֈړ�
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
	return;
}

//�_���[�W�v�Z
void PLAYER::DamegeCalc(ENEMY *enemy,int choiecommand)
{
	switch (choiecommand)		//�I�������R�}���h
	{

	case(int)COMMANDE_ATACK:				//�U����I�񂾎��̏�����������

		//�������������������������������������� �����̍U�������������� ��������������������������������������������
		if (this->ATK > enemy->GetDEF())	//�����̍U���͂��G�̖h��͂��ゾ������
		{
			this->SendDamege = this->ATK - enemy->GetDEF();		//�_���[�W�ʂ��v�Z �����U���� - �G�h��͂̃_���[�W��^����
		}
		else								//�����̍U���͂��G�̖h��͂�艺��������A
		{
			this->SendDamege = 0;			//�^����_���[�W��0
		}
		//�������������������������������������� �����̍U�����������܂� ��������������������������������������������



		//�������������������������������������� �G�̍U�������������� ��������������������������������������������
		if (enemy->GetATK() > this->DEF)		//�G�̍U���͂������̖h��͂��ゾ������
		{
			this->RecvDamege = enemy->GetATK() - this->DEF;	//�G�U���� - �����h��͂̃_���[�W��^����
		}
		else									//�G�̍U���͂������̖h��͂�艺��������A
		{
			this->RecvDamege = 0;				//�󂯂�_���[�W0
		}
		//�������������������������������������� �G�̍U�����������܂� ��������������������������������������������


		break;					//�U����I�񂾎��̏��������܂�

	case (int)COMMANDE_DEFENSE:			//�h���I�񂾎��̏�����������

		//�������������������������������������� �����̍U�������������� ��������������������������������������������
		this->SendDamege = 0;	//�h���I�񂾎��̓_���[�W��^���Ȃ�
		//�������������������������������������� �����̍U�����������܂� ��������������������������������������������



		//�������������������������������������� �G�̍U�������������� ��������������������������������������������

		//�h��͂��������ă_���[�W�v�Z
		if (enemy->GetATK() > (this->DEF * DEF_BOOST))		//�G�̍U���͂������̖h��͂��ゾ������
		{
			this->RecvDamege = enemy->GetATK() - (this->DEF * DEF_BOOST);	//�G�U���� - �����h��͂̃_���[�W��^����
		}
		else									//�G�̍U���͂������̖h��͂�艺��������A
		{
			this->RecvDamege = 0;				//�󂯂�_���[�W0
		}
		//�������������������������������������� �G�̍U�����������܂� ��������������������������������������������


		break;					//�h���I�񂾎��̏��������܂�

	case (int)COMMANDE_MAGIC:			//���@��I�񂾎��̏�����������

		//�������������������������������������� �����̍U�������������� ��������������������������������������������

		//�����̍U���͂��������ă_���[�W�v�Z
		//���@�U���͂�ǉ����āA�ʏ�U���ƕ�����\��
		if ((this->ATK * ATK_BOOST) > enemy->GetDEF())	//�����̍U���͂��G�̖h��͂��ゾ������
		{
			this->SendDamege = (this->ATK * ATK_BOOST) - enemy->GetDEF();		//�_���[�W�ʂ��v�Z �����U���� - �G�h��͂̃_���[�W��^����
		}
		else								//�����̍U���͂��G�̖h��͂�艺��������A
		{
			this->SendDamege = 0;			//�^����_���[�W��0
		}
		//�������������������������������������� �����̍U�����������܂� ��������������������������������������������



		//�������������������������������������� �G�̍U�������������� ��������������������������������������������
		if (enemy->GetATK() > this->DEF)		//�G�̍U���͂������̖h��͂��ゾ������
		{
			this->RecvDamege = enemy->GetATK() - this->DEF;	//�G�U���� - �����h��͂̃_���[�W��^����
		}
		else									//�G�̍U���͂������̖h��͂�艺��������A
		{
			this->RecvDamege = 0;				//�󂯂�_���[�W0
		}
		//�������������������������������������� �G�̍U�����������܂� ��������������������������������������������


		break;					//���@��I�񂾎��̏��������܂�

	case(int)COMMANDE_ITEM:				//�A�C�e����I�񂾎��̏�����������

		break;					//�A�C�e����I�񂾎��̏��������܂�

	default:
		break;
	}

	return;
}

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
		this->LevUpMsgStart_flg = true;	//���x���A�b�v���b�Z�[�W�̕\�����X�^�[�g����
	}
	return;
}

//���݂̈ʒu���擾
/*
�����Fint�FX�ʒu���Z�b�g����
�����Fint�FY�ʒu���Z�b�g����
*/
void PLAYER::GetNowPos(int *x, int *y)
{
	*x = this->sikaku_draw->Left;	//X�ʒu�ݒ�
	*y = this->sikaku_draw->Top;	//Y�ʒu�ݒ�
	return;
}

//���݂̃L�[���͂̎�ނ��擾
int PLAYER::GetInKeyKind(void)
{
	return this->InKeyKind;
}
