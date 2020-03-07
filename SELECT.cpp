//SELECT.cpp
//�I�������Ǘ�����N���X


//###################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "SELECT.hpp"

//###################### �N���X��` ##########################


//�f�X�g���N�^
SELECT::~SELECT()
{

	delete this->image_ui;	//UI�摜�j��

	//vector�̃�����������s��
	std::vector<std::string> v;			//���vector���쐬����
	this->Str.swap(v);					//��ƒ��g�����ւ���

	return;

}

//�I�����̃L�[����
/*
�߂�l�F�G���^�[�L�[�������ꂽ��:true
�߂�l�F�G���^�[�L�[������Ă��Ȃ����:false
*/
bool SELECT::SelectOperation(KEYDOWN *keydown,MUSIC *se)
{

	if (this->IsKeyOpe)		//�L�[����\�Ȃ�
	{
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
		else if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//�G���^�[�L�[�������ꂽ��
		{
			//SE�̍Đ�
			se->Play((int)SYS_SE_KETTEI);		//����̌��ʉ���炷
			keydown->KeyDownUpdate();			//�L�[���͂̏�Ԃ����Z�b�g

			this->SelectFlg = true;				//�I�����ꂽ

			return true;
		}

	}

	return false;

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
void SELECT::Draw(int x, int y,int kind,unsigned int color)
{
	static int Height = GetFontSize();	//�����擾

	for (int i = 0; i < this->Str.size(); ++i)
	{
		if (*this->Str_itr == this->Str[i])			//�I�𒆂̗v�f��������
		{

			if (kind == (int)SELECT_TRIANGLE)	//�ʏ�T�C�Y�̏ꍇ
			{
				this->image_ui->Draw(x - this->image_ui->GetWidth(kind), y + i * Height + IMAGE_SPACE, kind);		//�������O�p�`��
			}
			else							//�~�j�T�C�Y�̏ꍇ
			{
				this->image_ui->Draw(x - this->image_ui->GetWidth(kind), y + i * Height + IMAGE_MINI_SPACE, kind);	//�������O�p�`��
			}


			DrawFormatString(x, y + i * Height, color, "%s", this->Str[i].c_str());	//�I�����`��
		}
		else
		{
			DrawFormatString(x, y + i * Height, color, "%s", this->Str[i].c_str());	//�I�����`��
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

	static int Strlen = 0;		//������̒����擾�p
	static int Width = 0;		//������̕��擾�p
	static int Height = 0;		//������̍����擾�p

	std::string MaxStr;	//�ł�����������

	MaxStr = this->Str[0].c_str();	//�ł�����������ɍŏ��̕�������Z�b�g

	for (int i = 0; i < (int)this->Str.size(); i++)
	{
		if (MaxStr < this->Str[i].c_str())	//���݂̍ő啶��������傫�����
		{
			MaxStr = this->Str[i].c_str();	//�ő啶������X�V
		}
	}

	//������̒������擾
	Strlen = strlen(MaxStr.c_str());

	Width = GetDrawStringWidth(MaxStr.c_str(), Strlen);	//�����擾

	x -= (Width / 2);	//�����̕��̔����������āA�^�񒆂ɕ`�悷��

	Height = GetFontSize();	//�����擾

	for (int i = 0; i < this->Str.size(); ++i)
	{
		if (*this->Str_itr == this->Str[i])			//�I�𒆂̗v�f��������
		{

			if (kind == (int)SELECT_TRIANGLE)	//�ʏ�T�C�Y�̏ꍇ
			{
				this->image_ui->Draw(x - this->image_ui->GetWidth(kind), y + i * Height + IMAGE_SPACE, kind);		//�������O�p�`��
			}
			else							//�~�j�T�C�Y�̏ꍇ
			{
				this->image_ui->Draw(x - this->image_ui->GetWidth(kind), y + i * Height + IMAGE_MINI_SPACE, kind);	//�������O�p�`��
			}

			DrawFormatString(x, y + i * Height, color, "%s", this->Str[i].c_str());	//�I�����`��
		}
		else
		{
			DrawFormatString(x, y + i * Height, color, "%s", this->Str[i].c_str());	//�I�����`��
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
void SELECT::Add(const char *str)
{
	this->Str.push_back(str);	//�I�����ǉ�
	this->Str_itr = this->Str.begin();	//�ŏ��̗v�f��I����Ԃ�
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
