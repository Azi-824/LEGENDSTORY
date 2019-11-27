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
	delete Anime;
	delete Collision;
	delete Ilast;
	return;
}

//�����ݒ�
bool PLAYER::SetInit()
{
	this->HP = 100;		//����HP�ݒ�
	this->ATK = 10;		//�����U���͐ݒ�
	this->DEF = 10;		//�����h��͐ݒ�
	this->SPD = 10;		//�������x�ݒ�
	this->Dist = FLONT;	//���������ݒ�
	this->MoveSpeed = 5;//�����ړ����x�ݒ�

	this->Ilast->SetInit();	//�摜�����ݒ�
	this->IsKeyDown = false;//�L�[�{�[�h������Ă��Ȃ�

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

//�摜�ݒ�
bool PLAYER::SetImage(const char *dir, const char *name)
{
	this->Ilast = new CHARACTOR();
	if (this->Ilast->SetImage(dir, name) == false) { return false; }//�ǂݍ��ݎ��s

	return true;

}

//HP�ݒ�
void PLAYER::SetHP(int hp)
{
	this->HP = hp;
	return;
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

//�̗͎擾
int PLAYER::GetHP(void)
{
	return this->HP;
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

//����
void PLAYER::Operation(KEYDOWN *keydown)
{

	if (keydown->IsKeyDown(KEY_INPUT_W))		//W�L�[�������Ă���Ƃ�
	{
		this->IsKeyDown = true;
		this->MoveUp();							//��ֈړ�
	}
	else if (keydown->IsKeyDown(KEY_INPUT_S))	//S�L�[�������Ă���Ƃ�
	{
		this->IsKeyDown = true;
		this->MoveDown();						//���ֈړ�
	}
	else if (keydown->IsKeyDown(KEY_INPUT_A))	//A�L�[�������Ă���Ƃ�
	{
		this->IsKeyDown = true;
		this->MoveLeft();						//���ֈړ�
	}
	else if (keydown->IsKeyDown(KEY_INPUT_D))	//D�L�[�������Ă���Ƃ�
	{
		this->IsKeyDown = true;
		this->MoveRight();						//�E�ֈړ�
	}
	else
	{
		this->IsKeyDown = false;
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

	if (this->IsKeyDown)		//�L�[�{�[�h��������Ă���Ƃ�
	{
		this->Anime->Draw(this->Collision->Left, this->Collision->Top, this->Dist, true);	//�A�j���[�V�����ŕ`��

	}
	else						//�L�[�{�[�h��������Ă��Ȃ��Ƃ�
	{
		this->Anime->Draw(this->Collision->Left, this->Collision->Top, this->Dist, false);	//�ʏ�`��
	}
}

//��ֈړ�
void PLAYER::MoveUp()
{
	if (this->Collision->Top - this->MoveSpeed >= GAME_TOP)
	{
		this->Collision->Top -= this->MoveSpeed;	//�����蔻��ƁA�`��ʒu����ֈړ�
		this->Dist = BACK;	//�ړ���������ɂ���
	}

	return;
}

//���ֈړ�
void PLAYER::MoveDown()
{
	if (this->Collision->Bottom + this->MoveSpeed <= GAME_HEIGHT)
	{
		this->Collision->Top += this->MoveSpeed;	//���ֈړ�
		this->Dist = FLONT;	//�ړ�������
	}
	return;
}

//���ֈړ�
void PLAYER::MoveLeft()
{
	if (this->Collision->Left - this->MoveSpeed >= GAME_LEFT)
	{
		this->Collision->Left -= this->MoveSpeed;	//���ֈړ�
		this->Dist = LEFT;	//�ړ�������
	}
	return;
}

//�E�ֈړ�
void PLAYER::MoveRight()
{
	if (this->Collision->Right + this->MoveSpeed <= GAME_WIDTH)
	{
		this->Collision->Left += this->MoveSpeed;	//�E�ֈړ�
		this->Dist = RIGHT;	//�ړ������E
	}
	return;
}

