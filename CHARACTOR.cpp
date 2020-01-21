//CHARACTOR.cpp
//�L�����N�^�[�N���X

//################# �w�b�_�t�@�C���ǂݍ��� #####################
#include "CHARACTOR.hpp"

//################ �N���X��` ########################
//�R���X�g���N�^
CHARACTOR::CHARACTOR()
{
	return;
}

//�f�X�g���N�^
CHARACTOR::~CHARACTOR()
{
	delete this->collision;	//collision�폜
	delete this->image;		//image�폜
	delete this->sikaku_draw;	//sikaku_draw�폜

	return;
}

//��ֈړ�
void CHARACTOR::MoveUp()
{
	if (this->sikaku_draw->Top - this->Speed >= GAME_TOP)
	{
		this->sikaku_draw->Top -= this->Speed;	//�����蔻��ƁA�`��ʒu����ֈړ�
	}

	return;
}

//���ֈړ�
void CHARACTOR::MoveDown()
{
	if (this->sikaku_draw->Bottom + this->Speed <= GAME_HEIGHT)
	{
		this->sikaku_draw->Top += this->Speed;	//���ֈړ�
	}
	return;
}

//���ֈړ�
void CHARACTOR::MoveLeft()
{
	if (this->sikaku_draw->Left - this->Speed >= GAME_LEFT)
	{
		this->sikaku_draw->Left -= this->Speed;	//���ֈړ�
	}
	return;
}

//�E�ֈړ�
void CHARACTOR::MoveRight()
{
	if (this->sikaku_draw->Right + this->Speed <= GAME_WIDTH)
	{
		this->sikaku_draw->Left += this->Speed;	//�E�ֈړ�
	}
	return;
}

//�����Ă��邩�ݒ�
void CHARACTOR::SetIsArive(bool Isarive)
{
	this->IsArive = Isarive;
	return;
}

//�`��ł��邩�ݒ�
void CHARACTOR::SetIsDraw(bool Isdraw)
{
	this->IsDraw = IsDraw;
	return;
}

//�ړ����x��ݒ�
void CHARACTOR::SetSpeed(int speed)
{
	this->Speed = speed;
	return;
}

//�L�[�{�[�h�ő���ł��邩�ݒ�
void CHARACTOR::SetKeyOperation(bool Iskeyoperation)
{
	this->IsKeyOperation = IsKeyOperation;
	return;
}

//�摜��ݒ�
bool CHARACTOR::SetImage(const char *dir, const char *name)
{
	this->image = new IMAGE(dir, name);
	if (this->image->GetIsLoad() == false) { return false; }	//�ǂݍ��ݎ��s

	return true;

}

//�������擾
int CHARACTOR::GetWidth()
{
	return this->image->GetWidth();
}

//�������擾
int CHARACTOR::GetHeight()
{
	return this->image->GetHeight();
}

//�摜�̈ʒu��ݒ肷��
void CHARACTOR::SetImagePos(int x, int y)
{
	this->collision->Left = x;	//X���W
	this->collision->Top = y;	//Y���W

	this->sikaku_draw->Left = x;
	this->sikaku_draw->Top = y;

	//�`���
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height
	);

	//�̈�Đݒ�
	this->collision->SetValue(
		this->collision->Left,
		this->collision->Top,
		this->collision->Width,
		this->collision->Height
	);
}

//�����Ă��邩�擾
bool CHARACTOR::GetIsArive()
{
	return this->IsArive;
}

//�`��ł��邩�擾
bool CHARACTOR::GetIsDraw()
{
	return this->IsDraw;
}

//�ړ����x���擾
int CHARACTOR::GetSpeed()
{
	return this->Speed;
}

//�L�[�{�[�h����ł��邩�擾
bool CHARACTOR::GetKeyOperation()
{
	return this->IsKeyOperation;
}

//�����蔻����擾
COLLISION * CHARACTOR::GetCollision()
{
	return this->collision;
}

//����
void CHARACTOR::Operation(KEYDOWN *keydown)
{

	if (keydown->IsKeyDown(KEY_INPUT_W))		//W�L�[�������Ă���Ƃ�
	{
		this->MoveUp();							//��ֈړ�
	}
	else if (keydown->IsKeyDown(KEY_INPUT_S))	//S�L�[�������Ă���Ƃ�
	{
		this->MoveDown();						//���ֈړ�
	}
	else if (keydown->IsKeyDown(KEY_INPUT_A))	//A�L�[�������Ă���Ƃ�
	{
		this->MoveLeft();						//���ֈړ�
	}
	else if (keydown->IsKeyDown(KEY_INPUT_D))	//D�L�[�������Ă���Ƃ�
	{
		this->MoveRight();						//�E�ֈړ�
	}

	//�`��̈�Đݒ�
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);

	//�̈�Đݒ�
	this->collision->SetValue(
		this->collision->Left,
		this->collision->Top,
		this->collision->Width,
		this->collision->Height);

	return;
	
}

//�������ݒ�
bool CHARACTOR::SetInit()
{
	this->collision = new COLLISION();		//�����蔻��̗̈���쐬
	this->collision->SetValue(GAME_LEFT, GAME_TOP, this->image->GetWidth(0), this->image->GetHeight(0));	//�����蔻��̗̈��ݒ�

	this->sikaku_draw = new SIKAKU();		//�`��̈���쐬
	this->sikaku_draw->SetValue(GAME_LEFT, GAME_TOP, this->image->GetWidth(0), this->image->GetHeight(0));	//�����蔻��̗̈��ݒ�

	this->IsArive = true;	//�����Ă���
	this->IsDraw = true;	//�`�悵�Ă悢
	this->IsKeyOperation = true;	//�L�[�{�[�h����ł���

	return true;

}

//�`��
void CHARACTOR::Draw()
{
	if (this->IsArive)	//�����Ă����
	{
		if (this->IsDraw)	//�`��ł����
		{
			this->image->Draw(this->sikaku_draw->Left, this->sikaku_draw->Top);	//�摜�`��
		}
	}
}


