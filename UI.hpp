//UI.hpp
//�Q�[�����Ŏg�p����UI���Ǘ�����N���X

#pragma once

//######################### �w�b�_�t�@�C���ǂݍ��� #############################
#include "DxLib.h"
#include "STATEWINDOW.hpp"
#include "COMMAND.hpp"
#include "MENU.hpp"
#include "PLAYER.hpp"
#include "ITEM.hpp"

//######################### �}�N����` #####################################
#define UI_DIR	R"(.\MY_IMG\Ui\)"	//UI�摜�̃t�H���_��

#define	UI_NAME R"(ui1.png)"		//ui�̖��O

#define UI_IMAGE_SPACE	10			//ui�摜�i�������O�p�j�̈ʒu�����p���l
#define STR_SPACE	100			//������Ԃ̋�

#define DEFAULT_TEXT_Y	450		//�f�t�H���g�̃e�L�X�g�`��ʒu�iY���W�j

//######################### �񋓌^ #################################
enum UI_IMAGE_TYPE
{
	UI_ARROW		//�I��p�̉摜
};

//######################### �N���X��` #####################################
class UI
{
private:

	MENU *menuwindow;				//���j���[�E�B���h�E

	COMMAND *BattleCommand;			//�o�g���R�}���h

	STATEWINDOW *StateWindow;		//�X�e�[�^�X�E�B���h�E

	IMAGE *UiImage;					//ui�̉摜

	int BattleCommadType;			//�I�������o�g���R�}���h�̎��

	int ChoiseMenu;					//���j���[��ʂőI���������e

	std::vector<std::string> Str;	//������i�[�p
	std::vector<std::string>::iterator Str_itr;	//�C�e���[�^

public:

	UI();					//�R���X�g���N�^

	~UI();					//�f�X�g���N�^

	//���j���[�E�B���h�E�֘A
	void DrawMenu(int ,int);				//���j���[�E�B���h�E�`��
	void SetChoiseMenu(std::vector<std::string>::iterator);	//���j���[�őI�񂾓��e��ݒ肷��
	int GetChoiseMenu();				//���j���[��ʂł̑I����e���擾
	void ResetMenu();					//���j���[�֌W�̃����o�[�����Z�b�g
	void DrawChoiseMenu(PLAYER *,ITEM *[]);	//�I�񂾃��j���[���e���Ƃ̕`��
	bool GetIsChoise(void);				//�I������Ă��邩�擾

	//�o�g���R�}���h�֘A
	void SetBattleFlg(std::vector<std::string>::iterator);	//�퓬��ʂőI�񂾃R�}���h�̃t���O��ݒ肷��
	int GetChoiseCommamd();									//�I�������R�}���h�̎�ނ��擾
	void DrawCommand();										//�o�g���R�}���h�`��
	void BattleOperation(KEYDOWN *);						//�퓬��ʂ̑���
	void BattleInit();										//�o�g���R�}���h�Ŏg�p����v�f������������

	//�X�e�[�^�X�E�B���h�E�֘A
	void SetStateWindow(int,int,int);	//�X�e�[�^�X�E�B���h�E�̐ݒ������
	void DrawStateWindow();			//�X�e�[�^�X�E�B���h�E�`��

	void DrawWindow(int,int,int,int);				//�E�B���h�E��`�悷��

	//UI�摜�֌W
	void DrawUiImage(int, int,int);				//UI�̉摜��`�悷��
	bool AddUiImage(const char *, const char *,int);//ui�摜��ǉ�����
	int GetUiImageWidth(int);					//ui�摜�̉����擾
	int GetUiImageHeight(int);					//ui�摜�̍����擾

	void ChoiseOperation(KEYDOWN *);			//�I�����̃L�[������s��
	std::vector<std::string>::iterator GetNowChoise();	//���ݑI�����Ă���v�f���擾����
	void ChoiseClear();							//�I�����̓��e���N���A����

	//�I������`��
	/*
	�����Fint�Fx�ʒu
	�����Fint�Fy�ʒu
	�����Fbool�F�^�񒆂ɕ`�悷�邩
	�����Funsignd int�F�`��F
	�����FArgs�F�`�敶����
	*/
	template<typename...Args>
	void ChoiseDraw(int x,int y,bool center,unsigned int color, Args...args)
	{
		
		int Size = sizeof...(args);	//�v�f���擾

		std::vector<std::string> work = { args... };		//�W�J
		std::vector<std::string>::iterator work_itr = work.begin();	//�擪�v�f

		if (this->Str.empty())	//�W�J�������e���i�[���Ă��Ȃ����
		{
			this->Str = work;	//�W�J�������e���i�[
			this->Str_itr = this->Str.begin();	//�擪�v�f
		}

		//������������������������������������ ���A�����擾������������ ������������������������������������
		int Width = 0;
		if (center)			//�^�񒆂ɕ`�悷��Ƃ���
		{
			int Strlen = 0;		//������̒����擾�p
			std::string MaxStr;	//�ł�����������

			MaxStr = work[0].c_str();	//�ł�����������ɍŏ��̕�������Z�b�g

			for (int i = 0; i < (int)work.size(); i++)
			{
				if (MaxStr < work[i].c_str())	//���݂̍ő啶��������傫�����
				{
					MaxStr = work[i].c_str();	//�ő啶������X�V
				}
			}

			//������̒������擾
			Strlen = strlen(MaxStr.c_str());

			Width = GetDrawStringWidth(MaxStr.c_str(), Strlen);	//�����擾

			x -= (Width / 2);	//�����̕��̔����������āA�^�񒆂ɕ`�悷��
		}

		int Height = GetFontSize();	//�����擾

		int ui_width = this->UiImage->GetWidth((int)UI_ARROW);	//ui�摜�̉����擾
		//�������������������������������������� ���A�����擾���������܂� ����������������������������������������


		//�`�揈��
		for (int i = 0; i < Size; ++i)		//�v�f���̕����[�v
		{
			if (*this->Str_itr == work[i].c_str())		//�I�����Ă�����e��������
			{
				this->DrawUiImage(x - ui_width, y + i * Height + UI_IMAGE_SPACE, (int)UI_ARROW);	//ui�摜�i�������O�p�j�`��
				DrawFormatString(x, y + i * Height, color, "%s", work[i].c_str());	//�����`��
			}
			else								//����ȊO��������
			{
				DrawFormatString(x, y + i * Height, color, "%s", work[i].c_str());	//�����`��
			}
		}

		//vector�̃�����������s��
		std::vector<std::string> v;			//���vector���쐬����
		work.swap(v);						//��ƒ��g�����ւ���

		return;

	}

};
