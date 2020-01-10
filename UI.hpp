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

public:

	UI();					//�R���X�g���N�^

	~UI();					//�f�X�g���N�^

	//���j���[�E�B���h�E�֘A
	void MenuOperation(KEYDOWN *,bool);	//���j���[�E�B���h�E�̃L�[�{�[�h����
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

	//�I������`��
	template<typename...Args>
	void ChoiseDraw(Args...args)
	{
		
		std::vector<std::string> Str = { args... };

		DrawFormatString(400, 400, GetColor(255, 255, 255), "%s", Str[0].c_str());

		return;

	}

};
