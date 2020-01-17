//UI.hpp
//�Q�[�����Ŏg�p����UI���Ǘ�����N���X

#pragma once

//######################### �w�b�_�t�@�C���ǂݍ��� #############################
#include "DxLib.h"
#include "MENU.hpp"
#include "PLAYER.hpp"
//
//######################### �}�N����` #####################################
#define UI_DIR	R"(.\MY_IMG\Ui\)"	//UI�摜�̃t�H���_��

#define	UI_TRIANGLENAME		  R"(triangle1.png)"	//�������O�p�̖��O
#define	UI_TRIANGLE_MINI_NAME R"(triangle2.png)"	//�������O�p�i�~�j�j�̖��O
#define UI_WINDOW_NAME		  R"(window.png)"		//�E�B���h�E�̖��O

#define UI_IMAGE_SPACE	10			//ui�摜�i�������O�p�j�̈ʒu�����p���l
#define UI_IMAGE_MINI_SPACE 5		//�~�j�T�C�Y��
#define STR_SPACE		100			//������Ԃ̋�

//�X�e�[�^�X�E�B���h�E�֌W
#define STA_WIN_X		0			//�X�e�[�^�X�E�B���h�E�`��J�nX�ʒu
#define STA_WIN_Y		500			//�X�e�[�^�X�E�B���h�E�`��J�nY�ʒu
#define STA_WIN_WIDTH	190			//�X�e�[�^�X�E�B���h�E�̉���
#define STA_WIN_HEIGHT	100			//�X�e�[�^�X�E�B���h�E�̍���
#define STA_TXT_X		10			//�X�e�[�^�X�̕����̕`��J�nX�ʒu
#define STA_TXT_Y		500			//�X�e�[�^�X�̕����̕`��J�nY�ʒu
#define STA_SPACE		20			//�X�e�[�^�X�����̊Ԋu

//�o�g���R�}���h�֌W
#define CMD_WIN_X		190			//�o�g���R�}���h�̃E�B���h�E�̕`��J�nX�ʒu
#define	CMD_WIN_Y		500			//�o�g���R�}���h�̃E�B���h�E�̕`��J�nY�ʒu
#define CMD_WIN_WIDTH	120			//�o�g���R�}���h�̃E�B���h�E�̉���
#define CMD_WIN_HEIGHT	100			//�o�g���R�}���h�̃E�B���h�E�̍���
#define CMD_TXT_X		210			//�o�g���R�}���h�̕����̕`��J�nX�ʒu
#define CMD_TXT_Y		500			//�o�g���R�}���h�̕����̕`��J�nY�ʒu

//�E�B���h�E�֌W
#define BT_WINDOW_X		0			//�o�g����ʂ̃E�B���h�E�̕`��J�nX�ʒu
#define BT_WINDOW_Y		350			//�o�g����ʂ̃E�B���h�E�̕`��J�nY�ʒu

//�e�L�X�g�|�[�Y�֌W
#define BT_TXT_POSE_Y	470			//�o�g����ʂ̃e�L�X�g�|�[�Y�̕`��Y�ʒu

#define DEFAULT_TEXT_Y	450			//�f�t�H���g�̃e�L�X�g�`��ʒu�iY���W�j

//######################### �񋓌^ #################################
enum UI_IMAGE_TYPE
{
	UI_TRIANGLE,		//�������O�p�̉摜
	UI_TRIANGLE_MINI,	//�������O�p�i�~�j�j�̉摜
	UI_WINDOW			//�E�B���h�E
};

//######################### �N���X��` #####################################
class UI
{
private:

	MENU *menuwindow;				//���j���[�E�B���h�E

	IMAGE *UiImage;					//ui�̉摜

	ANIMATION *UiAnime;				//ui�̃A�j���[�V����

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
	bool GetIsChoise(void);				//�I������Ă��邩�擾

	//�o�g���R�}���h�֘A
	void SetBattleFlg();				//�퓬��ʂőI�񂾃R�}���h�̃t���O��ݒ肷��
	int GetChoiseCommamd();				//�I�������R�}���h�̎�ނ��擾
	void DrawCommand();					//�o�g���R�}���h�`��
	void BattleInit();					//�o�g���R�}���h�Ŏg�p����v�f������������

	//�X�e�[�^�X�E�B���h�E�֘A
	void DrawStateWindow(PLAYER *);				//�X�e�[�^�X�E�B���h�E�`��

	void DrawWindow(int, int, int, int);				//�E�B���h�E��`�悷��
	void DrawWindow(int,int,int,int,unsigned int);		//�E�B���h�E��`�悷��(�F�w��)

	//UI�摜�֌W
	void DrawUiImage(int, int,int);				//UI�̉摜��`�悷��
	bool AddUiImage(const char *, const char *,int);//ui�摜��ǉ�����
	int GetUiImageWidth(int);					//ui�摜�̉����擾
	int GetUiImageHeight(int);					//ui�摜�̍����擾

	//�I�����֌W
	void ChoiseOperation(KEYDOWN *);			//�I�����̃L�[������s��
	std::vector<std::string>::iterator GetNowChoise();	//���ݑI�����Ă���v�f���擾����
	void ChoiseClear();							//�I�����̓��e���N���A����

	//�A�j���[�V�����֌W
	bool AddUiAnime(const char *, const char *, int, int, int, int, int, double, bool);	//�A�j���[�V�����摜��ǉ�����
	void DrawUiAnime(int,int);			//�A�j���[�V�����摜��`�悷��

	//�I������`��
	/*
	�����Fint�Fx�ʒu
	�����Fint�Fy�ʒu
	�����Fint�F�`�悷��UI�摜�̎��
	�����Fbool�F�^�񒆂ɕ`�悷�邩
	�����Funsignd int�F�`��F
	�����FArgs�F�`�敶����
	*/
	template<typename...Args>
	void ChoiseDraw(int x,int y,int kind ,bool center,unsigned int color, Args...args)
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

		int ui_width = this->UiImage->GetWidth(kind);	//ui�摜�̉����擾
		//�������������������������������������� ���A�����擾���������܂� ����������������������������������������


		//�`�揈��
		for (int i = 0; i < Size; ++i)		//�v�f���̕����[�v
		{
			if (*this->Str_itr == work[i].c_str())		//�I�����Ă�����e��������
			{
				if (kind == (int)UI_TRIANGLE)	//�ʏ�T�C�Y�̏ꍇ
				{
					this->DrawUiImage(x - ui_width, y + i * Height + UI_IMAGE_SPACE, kind);	//ui�摜�`��
				}
				else							//�~�j�T�C�Y�̏ꍇ
				{
					this->DrawUiImage(x - ui_width, y + i * Height + UI_IMAGE_MINI_SPACE, kind);	//ui�摜�`��
				}
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
