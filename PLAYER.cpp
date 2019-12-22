//PLAYER.cpp
//�v���C���[�N���X

//############## �w�b�_�t�@�C���ǂݍ��� ################
#include "PLAYER.hpp"

//############## �N���X��` ##################

//�R���X�g���N�^
PLAYER::PLAYER()
{
	this->Skil.push_back(NOMAL_ATACK);	//�ʏ�U���̃X�L��
	this->Skil.push_back(MAGIC_2);		//���@2�̃X�L��
	return;
}

//�f�X�g���N�^
PLAYER::~PLAYER()
{
	delete this->Anime;
	delete this->AtkEffect;
	delete this->Collision;
	delete this->Ilast;

	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Skil.swap(v);		//��ƒ��g�����ւ���

	return;
}

//�����ݒ�
bool PLAYER::SetInit()
{
	this->Level = 1;		//�������x���ݒ�
	this->MaxHP = 100;		//�����ő�HP�ݒ�
	this->NowHP = this->MaxHP;//�������݂�HP�ݒ�
	this->MP = 100;		//����MP�ݒ�
	this->ATK = 10;		//�����U���͐ݒ�
	this->DEF = 10;		//�����h��͐ݒ�
	this->SPD = 10;		//�������x�ݒ�
	this->Dist = FLONT;	//���������ݒ�
	this->MoveSpeed = 5;//�����ړ����x�ݒ�

	this->ChoiseSkil = this->Skil[0];	//�ŏ��͒ʏ�U�����g�p����X�L���Ƃ��Đݒ肷��

	this->SendDamege = 0;	//�^����_���[�W0
	this->RecvDamege = 0;	//�󂯂�_���[�W0

	this->Ilast->SetInit();	//�摜�����ݒ�
	this->IsKeyDown = false;//�L�[�{�[�h������Ă��Ȃ�
	this->IsMenu = false;	//���j���[�E�B���h�E�`�悳��Ă��Ȃ�
	this->EffectEnd = false;	//�G�t�F�N�g�`�揈���I�����Ă��Ȃ�
	this->IsActMsg = false;		//�s�����b�Z�[�W�\�����Ă��Ȃ�

	this->Collision = new COLLISION();		//�����蔻��̗̈���쐬
	this->Collision->SetValue(GAME_LEFT, GAME_TOP, this->Anime->GetWidth(),this->Anime->GetHeight());	//�����蔻��̗̈��ݒ�

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

//�G�t�F�N�g�摜�ݒ�
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
//���@���Fint�F�摜�̑�������
//���@���Fint�F�摜�̉������̕�����
//���@���Fint�F�摜�̏c�����̕�����
//���@���Fint�F�摜�̕������ꂽ���̑傫��
//���@���Fint�F�摜�̕������ꂽ�c�̑傫��
//���@���Fdouble�F���̉摜�ɕύX���鑬��
//���@���Fbool�F�A�j���[�V���������[�v���邩�ǂ���

bool PLAYER::AddEffect(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	this->AtkEffect = new ANIMATION(dir, name, SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
	if (this->AtkEffect->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s

	return true;

}

//���@�G�t�F�N�g�̉摜�ݒ�
bool PLAYER::AddMagicEffect(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	this->MagicEffect = new ANIMATION(dir, name, SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
	if (this->MagicEffect->GetIsLoad() == false) { return false; }		//�ǂݍ��ݎ��s

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

//�G�t�F�N�g�֘A�̃��Z�b�g
void PLAYER::EffectReset()
{
	this->EffectEnd = false;			//�G�t�F�N�g�`��I�����Ă��Ȃ�
	this->AtkEffect->ResetIsAnime();	//�G�t�F�N�g�̃A�j���[�V�����������Z�b�g
	this->MagicEffect->ResetIsAnime();	//���@�G�t�F�N�g�̃A�j���[�V�����������Z�b�g
	return;
}

//���x���ݒ�
void PLAYER::SetLevel(int level)
{
	this->Level = level;
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
	this->NowHP -= hp;
	return;
}

//MP�ݒ�
void PLAYER::SetMP(int mp)
{
	this->MP += mp;
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

//MP�擾
int PLAYER::GetMP(void)
{
	return this->MP;
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

//�G�t�F�N�g�`�揈�����I���������擾
bool PLAYER::GetEffectEnd()
{
	return this->EffectEnd;
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

//����
void PLAYER::Operation(KEYDOWN *keydown)
{

	if (this->IsMenu ==false && keydown->IsKeyDown(KEY_INPUT_W))		//���j���[�`�撆�łȂ��AW�L�[�������Ă���Ƃ�
	{
		this->IsKeyDown = true;		//�L�[���͂���
		this->Dist = BACK;			//�ړ���������ɂ���
		this->MoveUp();				//��ֈړ�
	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_S))	//���j���[�`�撆�łȂ��AS�L�[�������Ă���Ƃ�
	{
		this->IsKeyDown = true;		//�L�[���͂���
		this->Dist = FLONT;			//�ړ�������
		this->MoveDown();			//���ֈړ�
	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_A))	//���j���[�`�撆�łȂ��AA�L�[�������Ă���Ƃ�
	{
		this->IsKeyDown = true;		//�L�[���͂���
		this->Dist = LEFT;			//�ړ�������
		this->MoveLeft();			//���ֈړ�
	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_D))	//���j���[�`�撆�łȂ��AD�L�[�������Ă���Ƃ�
	{
		this->IsKeyDown = true;		//�L�[���͂���
		this->Dist = RIGHT;			//�ړ������E
		this->MoveRight();			//�E�ֈړ�
	}
	else
	{
		this->IsKeyDown = false;	//�L�[���͂Ȃ�
	}



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
				this->Anime->Draw(this->Collision->Left, this->Collision->Top, this->Dist, true);	//�A�j���[�V�����ŕ`��

			}
			else						//�L�[�{�[�h��������Ă��Ȃ��Ƃ�
			{
				this->Anime->Draw(this->Collision->Left, this->Collision->Top, this->Dist, false);	//�ʏ�`��
			}
		}
	}
}

//�U���G�t�F�N�g�`��
void PLAYER::DrawAtk(int x, int y)
{
		if (this->AtkEffect->GetIsAnimeStop() == false)	//�A�j���[�V�����`�悪�I����Ă��Ȃ��ꍇ
		{
			this->AtkEffect->DrawEffect(x, y);		//�A�j���[�V�����`��
		}
		else			//�A�j���[�V�����`�悪�I�������
		{
			this->EffectEnd = true;	//�G�t�F�N�g�`�揈���I��
		}
	return;
}

//���@�G�t�F�N�g�`��
void PLAYER::DrawMagic(int x, int y)
{

	static int cnt = 0;		//�t�F�[�h�A�E�g�p
	static int cntMax = 60;	//�t�F�[�h�A�E�g�p
	static bool flg = false;//�t�F�[�h�A�E�g�I���t���O

	//60�t���[�����A�҂�
	if (cnt < cntMax)
	{
		cnt++;	//�J�E���g�A�b�v
	}
	else
	{
		flg = true;	//�t�F�[�h�A�E�g�����I��
	}

	//�t�F�[�h�A�E�g�̏���
	double ToukaPercent = (cnt / 2) / (double)cntMax;//���߁������߂�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * 255);	//���߂�����
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);	//�^���Âȉ�ʂɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//���߂���߂�
	
	if (flg)	//�t�F�[�h�A�E�g���I�������
	{
		if (this->MagicEffect->GetIsAnimeStop() == false)	//�A�j���[�V�����`�悪�I����Ă��Ȃ��ꍇ
		{
			this->MagicEffect->DrawEffect(x, y);		//�A�j���[�V�����`��
		}
		else			//�A�j���[�V�����`�悪�I�������
		{
			this->EffectEnd = true;	//�G�t�F�N�g�`�揈���I��
			flg = false;	//�t�F�[�h�A�E�g�t���O���Z�b�g
			cnt = 0;		//�t�F�[�h�A�E�g�J�E���g���Z�b�g
		}

	}

	return;
}


//��ֈړ�
void PLAYER::MoveUp()
{
	if (this->Collision->Top - this->MoveSpeed >= GAME_TOP)
	{
		this->Collision->Top -= this->MoveSpeed;	//�����蔻��ƁA�`��ʒu����ֈړ�
	}

	return;
}

//���ֈړ�
void PLAYER::MoveDown()
{
	if (this->Collision->Bottom + this->MoveSpeed <= GAME_HEIGHT)
	{
		this->Collision->Top += this->MoveSpeed;	//���ֈړ�
	}
	return;
}

//���ֈړ�
void PLAYER::MoveLeft()
{
	if (this->Collision->Left - this->MoveSpeed >= GAME_LEFT)
	{
		this->Collision->Left -= this->MoveSpeed;	//���ֈړ�
	}
	return;
}

//�E�ֈړ�
void PLAYER::MoveRight()
{
	if (this->Collision->Right + this->MoveSpeed <= GAME_WIDTH)
	{
		this->Collision->Left += this->MoveSpeed;	//�E�ֈړ�
	}
	return;
}

//�_���[�W�v�Z
void PLAYER::DamegeCalc(ENEMY *enemy)
{
	//�������������������������������������� �����̍U�������������� ��������������������������������������������
	if (this->ATK > enemy->GetDEF())	//�����̍U���͂��G�̖h��͂��ゾ������
	{
		this->SendDamege = this->ATK - enemy->GetDEF();		//�_���[�W�ʂ��v�Z �����U���� - �G�h��͂̃_���[�W��^����
	}
	//�������������������������������������� �����̍U�����������܂� ��������������������������������������������



	//�������������������������������������� �G�̍U�������������� ��������������������������������������������
	if (enemy->GetATK() > this->DEF)		//�G�̍U���͂������̖h��͂��ゾ������
	{
		this->RecvDamege= enemy->GetATK() - this->DEF;	//�G�U���� - �����h��͂̃_���[�W��^����
	}
	//�������������������������������������� �G�̍U�����������܂� ��������������������������������������������

	return;
}
