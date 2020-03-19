//SELECT.cpp
//�I�������Ǘ�����N���X


//###################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "SELECT.hpp"

//###################### �N���X��` ##########################

IMAGE* SELECT::image_ui;	//�C���X�g���N�^����

//�R���X�g���N�^�̃I�[�o�[���[�h
/*
�I�����̓��e��ݒ肹���ɃI�u�W�F�N�g�̐����݂̂��s��
*/
SELECT::SELECT()
{

	if (this->image_ui == NULL)	//UI�摜�𐶐����Ă��Ȃ����
	{
		this->image_ui = new IMAGE(SELECT_DIR, SELECT_TRIANGLENAME);		//UI�摜����
		this->image_ui->AddImage(SELECT_DIR, SELECT_TRIANGLE_MINI_NAME);	//UI�摜�ǉ�
	}


	this->IsKeyOpe = true;			//�L�[����\
	this->SelectFlg = false;		//�I������Ă��Ȃ�
	this->IsDrawImage = true;		//UI�摜��`�悵�Ă悢
	this->Side_Mode = false;		//�������ɑI��������ׂȂ�
	this->BackFlg = false;			//�߂�I���͂���Ă��Ȃ�

	this->DefIsKeyOpe = true;		//�f�t�H���g�̓L�[����\
	this->DefIsDrawImage = true;	//�f�t�H���g��UI�\��

	return;

}

//�f�X�g���N�^
SELECT::~SELECT()
{

	//delete this->image_ui;	//UI�摜�j��

	//vector�̃�����������s��
	std::vector<std::string> v;			//���vector���쐬����
	this->Str.swap(v);					//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<int> v2;			//���vector���쐬����
	this->Code.swap(v2);			//��ƒ��g�����ւ���

	return;

}

//�I�����̃L�[����
void SELECT::SelectOperation(KEYDOWN *keydown,MUSIC *se)
{

	if (this->IsKeyOpe)		//�L�[����\�Ȃ�
	{

		if (this->Side_Mode)	//�������ɑI����������ł���ꍇ��
		{
			//A�AD�L�[�ő���
			if (keydown->IsKeyDownOne(KEY_INPUT_A))		//A�L�[�������ꂽ��
			{
				if (this->Str_itr != this->Str.begin())	//�ŏ��̗v�f��I�����Ă��Ȃ����
				{
					//SE�̍Đ�
					se->Play((int)SYS_SE_CURSOR);					//�J�[�\���ړ���SE��炷
					--this->Str_itr;		//�O�̗v�f��

				}
			}
			else if (keydown->IsKeyDownOne(KEY_INPUT_D))	//D�L�[�������ꂽ��
			{
				if (this->Str_itr != this->Str.end() - 1)	//�Ō�̗v�f��I�����Ă��Ȃ����
				{
					//SE�̍Đ�
					se->Play((int)SYS_SE_CURSOR);					//�J�[�\���ړ���SE��炷
					++this->Str_itr;		//���̗v�f��
				}
			}


		}
		else					//�c�����ɑI����������ł���ꍇ��
		{
			//W�AS�L�[�ő���
			if (keydown->IsKeyDownOne(KEY_INPUT_W))		//W�L�[�������ꂽ��
			{
				if (this->Str_itr != this->Str.begin())	//�ŏ��̗v�f��I�����Ă��Ȃ����
				{
					//SE�̍Đ�
					se->Play((int)SYS_SE_CURSOR);					//�J�[�\���ړ���SE��炷
					--this->Str_itr;		//�O�̗v�f��

				}
			}
			else if (keydown->IsKeyDownOne(KEY_INPUT_S))	//S�L�[�������ꂽ��
			{
				if (this->Str_itr != this->Str.end() - 1)	//�Ō�̗v�f��I�����Ă��Ȃ����
				{
					//SE�̍Đ�
					se->Play((int)SYS_SE_CURSOR);					//�J�[�\���ړ���SE��炷
					++this->Str_itr;		//���̗v�f��
				}
			}

		}

		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ��
		{
			//SE�̍Đ�
			se->Play((int)SYS_SE_KETTEI);		//����̌��ʉ���炷
			keydown->KeyDownUpdate();			//�L�[���͂̏�Ԃ����Z�b�g

			this->SelectFlg = true;				//�I�����ꂽ

		}
		else if (keydown->IsKeyDownOne(KEY_INPUT_BACK))	//�o�b�N�X�y�[�X�L�[�������ꂽ��
		{
			//SE�̍Đ�
			se->Play((int)SYS_SE_CANSEL);		//�L�����Z���̌��ʉ���炷
			keydown->KeyDownUpdate();			//�L�[���͂̏�Ԃ����Z�b�g

			this->BackFlg = true;				//�߂�I��������
		}

	}

	return;

}

//���ݑI�𒆂̗v�f���擾
std::vector<std::string>::iterator SELECT::GetNowSelect()
{
	return this->Str_itr;
}

//�I�������v�f�̗v�f�ԍ����擾����
int SELECT::GetSelectNum(void)
{
	for (int i = 0; i < this->Str.size(); ++i)
	{
		if (*this->Str_itr == this->Str[i])		//�I�����Ă���v�f�ԍ��ƁA��v������
		{
			return i;		//���݂̗v�f�ԍ���Ԃ�
		}
	}
}

//�I�����̓��e������
void SELECT::SelectClear()
{
	this->Str.clear();
	this->Str_itr = this->Str.begin();
	this->Code.clear();
	return;
}

//���ݑI�𒆂̗v�f���ŏ��ɖ߂�
void SELECT::NowSelectReset(void)
{
	this->Str_itr = this->Str.begin();
	return;
}

//�I�����̓��e��`�悷��
/*
�����Fint�F�`��X�ʒu
�����Fint�F�`��Y�ʒu
�����Funsigned int�F�`��F:�f�t�H���g�͔��F
*/
void SELECT::Draw(int x, int y,int kind,unsigned int color,int side_select)
{

	//***************************** �T�C�Y�擾���� *******************************
	static int Height = 0;		//�����擾
	static int Strlen = 0;		//������̒����擾�p
	static int MaxStrlen = 0;	//�ł�����������̒���
	static int Width = 0;		//������̕��擾�p

	std::string MaxStr;	//�ł�����������

	MaxStr = this->Str[0].c_str();	//�ł�����������ɍŏ��̕�������Z�b�g

	for (int i = 0; i < (int)this->Str.size(); i++)
	{
		Strlen = strlen(this->Str[i].c_str());	//������̒����擾

		if (MaxStrlen < Strlen)	//�ő啶��������������
		{
			MaxStrlen = Strlen;	//�ő啶������X�V
			MaxStr = this->Str[i].c_str();	//�ő啶������X

		}

	}

	
	Width = GetDrawStringWidth(MaxStr.c_str(), MaxStrlen);	//�����擾

	Height = GetFontSize();		//�����擾

	if (this->Side_Mode)		//�������ɑI��������ׂĂ���ꍇ
	{
		//******************************** �`�揈�� ***************************************
		for (int i = 0; i < this->Str.size(); ++i)
		{
			if (*this->Str_itr == this->Str[i])			//�I�𒆂̗v�f��������
			{

				if (this->IsDrawImage)	//�\�����Ă悯���
				{
					if (kind == (int)SELECT_TRIANGLE)	//�ʏ�T�C�Y�̏ꍇ
					{
						this->image_ui->Draw((x + i * side_select), y + IMAGE_SPACE, kind);		//�������O�p�`��
					}
					else							//�~�j�T�C�Y�̏ꍇ
					{
						this->image_ui->Draw((x + i * side_select), y + IMAGE_MINI_SPACE, kind);	//�������O�p�`��
					}

				}

				DrawFormatString((x + i * side_select) + this->image_ui->GetWidth(kind), y, color, "%s", this->Str[i].c_str());	//�I�����`��
			}
			else
			{
				DrawFormatString((x + i * side_select) + this->image_ui->GetWidth(kind), y, color, "%s", this->Str[i].c_str());	//�I�����`��
			}
		}

	}
	else						//���Č����ɑI���������ł���ꍇ
	{

		for (int i = 0; i < this->Str.size(); ++i)
		{
			if (*this->Str_itr == this->Str[i])			//�I�𒆂̗v�f��������
			{
				if (this->IsDrawImage)		//�\�����Ă悯���
				{
					if (kind == (int)SELECT_TRIANGLE)	//�ʏ�T�C�Y�̏ꍇ
					{
						this->image_ui->Draw(x, y + i * Height + IMAGE_SPACE, kind);		//�������O�p�`��
					}
					else							//�~�j�T�C�Y�̏ꍇ
					{
						this->image_ui->Draw(x, y + i * Height + IMAGE_MINI_SPACE, kind);	//�������O�p�`��
					}
				}


				DrawFormatString(x + this->image_ui->GetWidth(kind), y + i * Height, color, "%s", this->Str[i].c_str());	//�I�����`��
			}
			else
			{
				DrawFormatString(x + this->image_ui->GetWidth(kind), y + i * Height, color, "%s", this->Str[i].c_str());	//�I�����`��
			}
		}


	}


}

//�I�����̓��e�𒆉��ɕ`�悷��
/*
�����Fint�F�`��X�ʒu
�����Fint�F�`��Y�ʒu
�����Funsigned int�F�`��F:�f�t�H���g�͔��F
*/
void SELECT::DrawCenter(int x, int y,int kind, unsigned int color)
{

	static int Height = 0;		//�����擾
	static int Strlen = 0;		//������̒����擾�p
	static int MaxStrlen = 0;	//�ł�����������̒���
	static int Width = 0;		//������̕��擾�p

	std::string MaxStr;	//�ł�����������

	MaxStr = this->Str[0].c_str();	//�ł�����������ɍŏ��̕�������Z�b�g

	for (int i = 0; i < (int)this->Str.size(); i++)
	{
		Strlen = strlen(this->Str[i].c_str());	//������̒����擾

		if (MaxStrlen < Strlen)	//�ő啶��������������
		{
			MaxStrlen = Strlen;	//�ő啶������X�V
			MaxStr = this->Str[i].c_str();	//�ő啶������X

		}

	}

	Width = GetDrawStringWidth(MaxStr.c_str(), MaxStrlen);	//�����擾

	x -= (Width / 2);	//�����̕��̔����������āA�^�񒆂ɕ`�悷��

	Height = GetFontSize();	//�����擾

	for (int i = 0; i < this->Str.size(); ++i)
	{
		if (*this->Str_itr == this->Str[i])			//�I�𒆂̗v�f��������
		{

			if (kind == (int)SELECT_TRIANGLE)	//�ʏ�T�C�Y�̏ꍇ
			{
				this->image_ui->Draw(x , y + i * Height + IMAGE_SPACE, kind);		//�������O�p�`��
			}
			else							//�~�j�T�C�Y�̏ꍇ
			{
				this->image_ui->Draw(x, y + i * Height + IMAGE_MINI_SPACE, kind);	//�������O�p�`��
			}

			DrawFormatString(x + this->image_ui->GetWidth(kind), y + i * Height, color, "%s", this->Str[i].c_str());	//�I�����`��
		}
		else
		{
			DrawFormatString(x + this->image_ui->GetWidth(kind), y + i * Height, color, "%s", this->Str[i].c_str());	//�I�����`��
		}
	}

}

//�摜�T�C�Y��ݒ�
void SELECT::SetSize(void)
{
	this->image_ui->SetSize();	//�C���[�W�摜�̃T�C�Y�ݒ�

	return;
}

//�I�����̓��e��ǉ�
void SELECT::AddSelect(const char *str,int code)
{
	this->Str.push_back(str);	//�I�����ǉ�
	this->Str_itr = this->Str.begin();	//�ŏ��̗v�f��I����Ԃ�
	this->Code.push_back(code);			//�R�[�h�ԍ��ǉ�
	return;
}

//�L�[����\���ݒ�
void SELECT::SetIsKeyOpe(bool iskeyope)
{
	this->IsKeyOpe = iskeyope;
	return;
}

//�L�[����\���擾
bool SELECT::GetIsKeyOpe(void)
{
	return this->IsKeyOpe;
}

//�I���������ݒ�
void SELECT::SetSelectFlg(bool selectflg)
{
	this->SelectFlg = selectflg;
	return;
}

//�I���������擾
bool SELECT::GetSelectFlg(void)
{
	return this->SelectFlg;
}

//UI�摜��`�悵�Ă悢���ݒ�
void SELECT::SetIsDrawImage(bool isdraw)
{
	this->IsDrawImage = isdraw;
	return;
}

//UI�摜��`�悵�Ă悢���擾
bool SELECT::GetIsDrawImage(void)
{
	return this->IsDrawImage;
}

//�I�������������ɕ��ׂ邩�ݒ�
void SELECT::SetSideMode(bool side)
{
	this->Side_Mode = side;
	return;
}

//�I�������������ɕ��ׂ邩�擾
bool SELECT::GetSideMode(void)
{
	return this->Side_Mode;
}

//�f�t�H���g�̏�Ԃ�ݒ�
void SELECT::ChengeDefault(bool defiskey, bool defisdraw)
{
	this->DefIsKeyOpe = defiskey;		//�L�[����\���A�f�t�H���g�l
	this->DefIsDrawImage = defisdraw;	//UI�摜�`�悵�Ă悢���A�f�t�H���g�l
	return;
}

//�f�t�H���g�̒l�ɖ߂�
void SELECT::Default(void)
{
	this->IsKeyOpe = this->DefIsKeyOpe;			//�L�[������f�t�H���g�̏�Ԃ�
	this->IsDrawImage = this->DefIsDrawImage;	//UI�\�����f�t�H���g�̏�Ԃ�
	this->SelectFlg = false;					//�I�����Ă��Ȃ�
	this->BackFlg = false;						//�߂����ǂ��������Z�b�g
	this->NowSelectReset();						//���݂̑I�������Z�b�g
	return;
}

//�߂��I���������ݒ�
void SELECT::SetBackFlg(bool back_flg)
{
	this->BackFlg = back_flg;	
	return;
}

//�߂�I�����������擾
bool SELECT::GetBackFlg(void)
{
	return this->BackFlg;
}

//�w�肳�ꂽ�v�f�ɋ󔒂�����
void SELECT::InsertSpace(int element)
{
	this->Str[element] += " ";	//�󔒂�ǉ�
	return;
}

//�w�肳�ꂽ�v�f�̕�����ɕ�����������
void SELECT::AddText(int element, std::string add_text)
{
	this->Str[element] += add_text;
	return;
}

//�I�����̐����擾
int SELECT::GetSelectKind(void)
{
	return this->Str.size();
}

//�I�΂ꂽ�I�����̃R�[�h�ԍ����擾����
int SELECT::GetSelectCode(void)
{
	return this->Code[this->GetSelectNum()];	//�I�΂ꂽ�I�����̃R�[�h�ԍ����擾
}

//�I���������e���擾����
const char * SELECT::GetSelectText(void)
{
	return this->Str_itr->c_str();
}
