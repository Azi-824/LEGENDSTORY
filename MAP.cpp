//MAP.cpp
//�}�b�v�N���X

//################## �w�b�_�t�@�C���ǂݍ��� #####################
#include "MAP.hpp"

//################## �N���X��` #####################
//�R���X�g���N�^
MAP::MAP()
{
	for (int tate = 0; tate < MAP_TATE; ++tate)
	{
		for (int yoko = 0; yoko < MAP_YOKO; ++yoko)
		{
			this->RectOK[tate][yoko] = new COLLISION();	//�����蔻��̗̈���쐬(�ʍs�ł���)
			this->RectNG[tate][yoko] = new COLLISION();	//�����蔻��̗̈���쐬(�ʍs�ł��Ȃ�)

			//�����蔻�菉����
			this->RectOK[tate][yoko]->SetValue(0, 0, MAP_YOKO_SIZE, MAP_TATE_SIZE);

			this->RectNG[tate][yoko]->SetValue(0, 0, MAP_YOKO_SIZE, MAP_TATE_SIZE);

		}
	}
	return;
}

//�f�X�g���N�^
MAP::~MAP()
{
	for (int tate = 0; tate < MAP_TATE; ++tate)
	{
		for (int yoko = 0; yoko < MAP_YOKO; ++yoko)
		{
			delete this->RectOK[tate][yoko];	//�����蔻���j��(�ʍs�ł���)
			delete this->RectNG[tate][yoko];	//�����蔻���j��(�ʍs�ł��Ȃ�)
		}
	}

	return;
}

//csv�t�@�C����ǂݍ���
//�����Fconst char * �}�b�vcsv�̃t�@�C����
//�����Fconst char * �}�b�vcsv�̖��O
bool MAP::LoadCsv(const char *dir, const char *name)
{

	std::string LoadFilePath;
	LoadFilePath += dir;
	LoadFilePath += name;

	if ((this->fp_map_csv = fopen(LoadFilePath.c_str(), "r")) == NULL)		//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	{
		return false;//�ُ�I��
	}

	//�������琳��ɓǂݍ��߂��Ƃ��̏���****************************************

	int result = 0;			//�t�@�C���̍Ōォ�`�F�b�N
	int LoopCnt = 0;		//���[�v�J�E���^

	while (result != EOF)		//EOF End Of File(�t�@�C���̍Ō�)�ł͂Ȃ��Ƃ��J��Ԃ�
	{
		//�t�@�C�����琔�l����ǂݍ���(%d,)�A�z��Ɋi�[����
		result = fscanf(this->fp_map_csv, "%d,", &this->MapData[LoopCnt / MAP_YOKO][LoopCnt % MAP_YOKO]);

		LoopCnt++;
	}

	fclose(this->fp_map_csv);	//�t�@�C�������

	this->FilePath = LoadFilePath;
	this->FileName = name;

	return true;

}

//�}�b�v��؂�ւ���
//�����FPLAYER�F��l���̏��
//�����Fint	�@�F���݂̃}�b�v��X���W��Y���W�̏��
void MAP::ChengeMap(PLAYER *player,int *mapnowpos)
{
	COLLISION *player_collision = player->GetCollision();	//�v���C���[�̓����蔻����擾

	if (player_collision->Bottom >= GAME_HEIGHT)	//��ʂ̉��ɗ�����
	{
		if ((mapnowpos[POS_Y]) < MAP_DATA_TATE_KIND - 1)	//���̃}�b�v������ꍇ��
		{
			mapnowpos[POS_Y]++;	//���̃}�b�v��
			player->SetPosition(0, -(player_collision->Top - 5));	//�ʒu���C��
		}
	}
	else if (player_collision->Top <= GAME_TOP)		//��ʂ̏�ɗ�����
	{
		if ((mapnowpos[POS_Y]) > 0)	//��̃}�b�v������ꍇ��
		{
			mapnowpos[POS_Y]--;	//��̃}�b�v��
			player->SetPosition(0, GAME_HEIGHT- (player_collision->Height + 5));	//�ʒu���C��
		}

	}
	else if (player_collision->Right >= GAME_WIDTH)	//��ʂ̉E�ɗ�����
	{
		if ((mapnowpos[POS_X]) + MAP_DATA_TATE_KIND <= MAP_DATA_TATE_KIND)	//���Ƀ}�b�v������ꍇ��
		{
			(mapnowpos[POS_X]) += (MAP_DATA_TATE_KIND - 1);	//�E�̃}�b�v��
			player->SetPosition(-(player_collision->Left - 5), 0);	//�ʒu���C��
		}
	}
	else if (player_collision->Left <= GAME_LEFT)		//��ʂ̍��ɗ�����
	{
		if ((mapnowpos[POS_X]) - (MAP_DATA_TATE_KIND - 1) >= 0)			//���̃}�b�v������ꍇ��
		{
			(mapnowpos[POS_X]) -= (MAP_DATA_TATE_KIND - 1);	//���̃}�b�v��
			player->SetPosition(GAME_WIDTH - (player_collision->Width + 5), 0);	//�ʒu���C��
		}
	}
	return;
}

//�`��
void MAP::Draw(int *handle)
{
	for (int tate = 0; tate < MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO; yoko++)
		{
			DrawGraph(yoko*MAP_YOKO_SIZE, tate*MAP_TATE_SIZE, handle[this->MapData[tate][yoko]], TRUE);	//�}�b�v�`��
		}
	}

	return;
}

//�����蔻��̗̈���쐬
void MAP::CreateRect(int *ok_kind,int *ng_kind)
{
	for (int tate = 0; tate < MAP_TATE; ++tate)
	{
		for (int yoko = 0; yoko < MAP_YOKO; ++yoko)
		{

			//�����蔻��̗̈���쐬(�ʍs�ł���)
			for (int cnt = 0; cnt < MAP_OK_KIND; ++cnt)
			{
				if (this->MapData[tate][yoko] == ok_kind[cnt])
				{
					this->RectOK[tate][yoko]->Left = yoko * this->RectOK[tate][yoko]->Width + 1;
					this->RectOK[tate][yoko]->Top = tate * this->RectOK[tate][yoko]->Height + 1;
					this->RectOK[tate][yoko]->Right = (yoko + 1) * this->RectOK[tate][yoko]->Width - 1;
					this->RectOK[tate][yoko]->Bottom = (tate + 1)*this->RectOK[tate][yoko]->Height - 1;

					//this->RectOK[tate][yoko]->SetValue(yoko * this->RectOK[tate][yoko]->Width + 1,
					//	tate * this->RectOK[tate][yoko]->Height + 1,
					//	MAP_YOKO_SIZE - 1, MAP_TATE_SIZE - 1);

				}
			}

			//�����蔻��̗̈���쐬(�ʍs�ł��Ȃ�)
			for (int cnt = 0; cnt < MAP_NG_KIND; ++cnt)
			{
				if (this->MapData[tate][yoko] == ng_kind[cnt])
				{
					this->RectNG[tate][yoko]->Left = yoko * this->RectOK[tate][yoko]->Width + 1;
					this->RectNG[tate][yoko]->Top = tate * this->RectOK[tate][yoko]->Height + 1;
					this->RectNG[tate][yoko]->Right = (yoko + 1) * this->RectOK[tate][yoko]->Width - 1;
					this->RectNG[tate][yoko]->Bottom = (tate + 1)*this->RectOK[tate][yoko]->Height - 1;
				}
			}

		}
	}

	return;

}

//�v���C���[�ƃ}�b�v���������Ă��邩�m�F
bool MAP::CheckDetectionPlayer(COLLISION *player,int keykind, int *detectionX, int *detectionY)
{

	auto CollisionInit = player;

	switch (keykind)		//�L�[���͂̎�ނŔ���
	{

	case (int)KEY_UP:		//��L�[�̎�

		//�̈��������ւ��炷
		player->Top -= RECT_STAGGER;
		player->Bottom -= RECT_STAGGER;

		for (int tate = 0; tate < MAP_TATE; tate++)
		{
			for (int yoko = 0; yoko < MAP_YOKO; yoko++)
			{
				//�L�����N�^�[�̓������Ă���ꏊ���擾
				if (this->RectNG[tate][yoko]->DetectionCheck(player))
				{
					*detectionY = tate;	//atariY�̃A�h���X���w��������̏ꏊ�ɁA�����������m�̏c�̈ʒu������
					*detectionX = yoko;	//atariX�̃A�h���X���w��������̏ꏊ�ɁA�����������m�̉��̈ʒu������

					player = CollisionInit;	//���炵���������ɖ߂�

					return true;
				}
			}
		}


		break;	//��L�[�̎������܂�

	case (int)KEY_DOWN:		//���L�[�̎�

		//�̈���������ւ��炷
		player->Top += RECT_STAGGER;
		player->Bottom += RECT_STAGGER;

		for (int tate = 0; tate < MAP_TATE; tate++)
		{
			for (int yoko = 0; yoko < MAP_YOKO; yoko++)
			{
				//�L�����N�^�[�̓������Ă���ꏊ���擾
				if (this->RectNG[tate][yoko]->DetectionCheck(player))
				{
					*detectionY = tate;	//atariY�̃A�h���X���w��������̏ꏊ�ɁA�����������m�̏c�̈ʒu������
					*detectionX = yoko;	//atariX�̃A�h���X���w��������̏ꏊ�ɁA�����������m�̉��̈ʒu������

					player = CollisionInit;	//���炵���������ɖ߂�

					return true;
				}
			}
		}


		break;		//���L�[�̎������܂�

	case(int)KEY_LEFT:		//���L�[�̎�

		//�̈���������ւ��炷
		player->Left -= RECT_STAGGER;
		player->Right -= RECT_STAGGER;

		for (int tate = 0; tate < MAP_TATE; tate++)
		{
			for (int yoko = 0; yoko < MAP_YOKO; yoko++)
			{
				//�L�����N�^�[�̓������Ă���ꏊ���擾
				if (this->RectNG[tate][yoko]->DetectionCheck(player))
				{
					*detectionY = tate;	//atariY�̃A�h���X���w��������̏ꏊ�ɁA�����������m�̏c�̈ʒu������
					*detectionX = yoko;	//atariX�̃A�h���X���w��������̏ꏊ�ɁA�����������m�̉��̈ʒu������

					player = CollisionInit;	//���炵���������ɖ߂�

					return true;
				}
			}
		}


		break;		//���L�[�̎������܂�

	case(int)KEY_RIGHT:		//�E�L�[�̎�

		//�̈�������E�ւ��炷 
		player->Left += RECT_STAGGER;
		player->Right += RECT_STAGGER;

		for (int tate = 0; tate < MAP_TATE; tate++)
		{
			for (int yoko = 0; yoko < MAP_YOKO; yoko++)
			{
				//�L�����N�^�[�̓������Ă���ꏊ���擾
				if (this->RectNG[tate][yoko]->DetectionCheck(player))
				{
					*detectionY = tate;	//atariY�̃A�h���X���w��������̏ꏊ�ɁA�����������m�̏c�̈ʒu������
					*detectionX = yoko;	//atariX�̃A�h���X���w��������̏ꏊ�ɁA�����������m�̉��̈ʒu������

					player = CollisionInit;	//���炵���������ɖ߂�

					return true;
				}
			}
		}


		break;		//�E�L�[�̎������܂�


	default:
		break;
	}


	player = CollisionInit;	//���炵���������ɖ߂�

	return false;

}
