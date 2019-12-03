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
	delete this->AtkEffect;
	delete this->Collision;
	delete this->Ilast;
	delete this->menuwindow;
	delete this->BattleCommand;

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
	this->IsMenu = false;	//���j���[�E�B���h�E�`�悳��Ă��Ȃ�
	this->EffectEnd = false;	//�G�t�F�N�g�`�揈���I�����Ă��Ȃ�

	this->Collision = new COLLISION();		//�����蔻��̗̈���쐬
	this->Collision->SetValue(GAME_LEFT, GAME_TOP, this->Anime->GetWidth(),this->Anime->GetHeight());	//�����蔻��̗̈��ݒ�

	this->menuwindow = new MENU();			//���j���[�E�B���h�E�쐬

	this->BattleCommand = new COMMAND();	//�o�g���R�}���h�쐬

	this->BattleCommadType = -1;			//�I�������o�g���R�}���h�̎�ނ�������

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


//�摜�ݒ�
bool PLAYER::SetImage(const char *dir, const char *name)
{
	this->Ilast = new CHARACTOR();
	if (this->Ilast->SetImage(dir, name) == false) { return false; }//�ǂݍ��ݎ��s

	return true;

}

//�o�g���R�}���h�̑I�������Z�b�g����
void PLAYER::BattleCommandReset()
{
	this->BattleCommadType = -1;	//���Z�b�g
	this->EffectEnd = false;		//�G�t�F�N�g�`��I�����Ă��Ȃ�
	this->AtkEffect->ResetIsAnime();	//�A�j���[�V�����������Z�b�g
	return;
}

//HP�ݒ�
void PLAYER::SetHP(int hp)
{
	this->HP -= hp;
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

//�퓬��ʂőI�񂾃R�}���h��ݒ肷��
void PLAYER::SetBattleFlg(std::vector<std::string>::iterator choise_itr)
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

//�I�������R�}���h�̎�ނ��擾
int PLAYER::GetChoiseCommamd()
{
	return this->BattleCommadType;
}

//�G�t�F�N�g�`�揈�����I���������擾
bool PLAYER::GetEffectEnd()
{
	return this->EffectEnd;
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
	else if (keydown->IsKeyDown(KEY_INPUT_Q))	//Q�L�[�������Ă���Ƃ�
	{
		this->IsMenu = true;		//���j���[�`��J�n
	}
	else
	{
		this->IsKeyDown = false;	//�L�[���͂Ȃ�
	}

	if (this->IsMenu)	//���j���[�`�撆
	{
		if (keydown->IsKeyDown(KEY_INPUT_ESCAPE))	//�G�X�P�[�v�L�[�������ꂽ��
		{
			this->IsMenu = false;	//���j���[�`��I��
		}
		else if (keydown->IsKeyDownOne(KEY_INPUT_W))	//W�L�[�������ꂽ�u��
		{
			this->menuwindow->Back();	//�O�̗v�f��
		}
		else if (keydown->IsKeyDownOne(KEY_INPUT_S))	//S�L�[�������ꂽ�u��
		{
			this->menuwindow->Next();	//���̗v�f��
		}
		this->DrawMenu();	//���j���[�E�B���h�E�`��
	}


	//�̈�Đݒ�
	this->Collision->SetValue(
		this->Collision->Left,
		this->Collision->Top,
		this->Collision->Width,
		this->Collision->Height);

	return;

}

//�퓬��ʂ̑���
void PLAYER::BattleOperation(KEYDOWN *keydown)
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

//���j���[�E�B���h�E�`��
void PLAYER::DrawMenu()
{
	this->menuwindow->Draw();	//���j���[�`��
	return;
}

//�o�g���R�}���h�`��
void PLAYER::DrawCommand()
{
	this->BattleCommand->Draw();	//�`��
	return;
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
		enemy->SetHP(this->ATK - enemy->GetDEF());	//�����U���� - �G�h��͂̃_���[�W��^����
		if (enemy->GetHP() <= 0)				//�G��HP��0�ɂȂ�����
		{
			enemy->SetIsArive(false);		//�G���S
		}
	}
	//�������������������������������������� �����̍U�����������܂� ��������������������������������������������



	//�������������������������������������� �G�̍U�������������� ��������������������������������������������
	if (enemy->GetATK() > this->DEF)		//�G�̍U���͂������̖h��͂��ゾ������
	{
		this->HP -= enemy->GetATK() - this->DEF;	//�G�U���� - �����h��͂̃_���[�W��^����
		if (this->HP <= 0)			//������HP��0�ɂȂ�����
		{
			this->IsArive = false;		//�������S
		}
	}
	//�������������������������������������� �G�̍U�����������܂� ��������������������������������������������

	return;
}
