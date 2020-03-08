//SELECT.hpp
//�I�������Ǘ�����N���X

#pragma once

//###################### �w�b�_�t�@�C���ǂݍ��� ##############################
#include "DxLib.h"
#include "KEYDOWN.hpp"
#include "MUSIC.hpp"
#include "IMAGE.hpp"
#include <vector>
#include <string>

//###################### �}�N����` ###########################
#define SELECT_DIR	R"(.\MY_IMG\Select\)"	//UI�摜�̃t�H���_��

#define	SELECT_TRIANGLENAME		  R"(triangle1.png)"	//�������O�p�̖��O
#define	SELECT_TRIANGLE_MINI_NAME R"(triangle2.png)"	//�������O�p�i�~�j�j�̖��O

#define IMAGE_SPACE	10			//ui�摜�i�������O�p�j�̈ʒu�����p���l
#define IMAGE_MINI_SPACE 5		//�~�j�T�C�Y��

#define TRIANGLE_MINI_SIZE	14	//�������O�p�i�~�j�j�̃T�C�Y

//##################### �񋓌^ #############################
enum SELECT_IMAGE_TYPE
{
	SELECT_TRIANGLE,		//�������O�p�̉摜
	SELECT_TRIANGLE_MINI	//�������O�p�i�~�j�j�̉摜
};

//###################### �N���X��` ###########################
class SELECT
{
private:

	std::vector<std::string> Str;				//������i�[�p
	std::vector<std::string>::iterator Str_itr;	//�C�e���[�^

	IMAGE *image_ui;	//UI�摜

	bool IsKeyOpe;		//�L�[����\��
	bool SelectFlg;		//�I��������

public:

	//�R���X�g���N�^
	/*
	�����FArgs�F�`�敶����
	*/
	template<typename...Args>
	SELECT(Args...args)		
	{

		this->image_ui = new IMAGE(SELECT_DIR, SELECT_TRIANGLENAME);	//UI�摜����
		this->image_ui->AddImage(SELECT_DIR, SELECT_TRIANGLE_MINI_NAME, 1);	//UI�摜�ǉ�

		this->Str = { args... };			//�W�J
		this->Str_itr = this->Str.begin();	//�擪�v�f

		this->IsKeyOpe = true;				//�L�[����\
		this->SelectFlg = false;			//�I������Ă��Ȃ�

		return;
	}
	
	/*
	�I�����̓��e��ݒ肹���ɃI�u�W�F�N�g�̐����݂̂��s��
	�ŏ�����L�[����\���ǂ����ݒ�ł���
	�f�t�H���g�̓L�[����\
	*/
	SELECT(bool iskeyope = true);			//�R���X�g���N�^�̃I�[�o�[���[�h

	~SELECT();		//�f�X�g���N�^

	void SelectOperation(KEYDOWN *,MUSIC *);	//�I�����̃L�[����

	std::vector<std::string>::iterator GetNowSelect();		//���ݑI�𒆂̗v�f���擾
	int GetSelectNum(void);					//�I�������v�f�̗v�f�ԍ����擾����

	void SelectClear();						//�I�����̓��e����������
	void NowSelectReset();					//���ݑI�𒆂̗v�f���ŏ��ɖ߂�

	void Draw(int, int,int ,unsigned int color = GetColor(255, 255, 255));		//�I�����̓��e��`�悷��
	void DrawCenter(int, int,int , unsigned int color = GetColor(255, 255, 255));	//�I�����̓��e�𒆉��ɕ`�悷��

	void SetSize(void);						//�摜�T�C�Y�ݒ�
	void Add(const char *);					//�I�����̓��e��ǉ�

	void SetIsKeyOpe(bool);					//�L�[����\���ݒ肷��
	bool GetIsKeyOpe(void);					//�L�[����\���擾����

	void SetSelectFlg(bool);				//�I���������ݒ�
	bool GetSelectFlg(void);				//�I���������擾


	//�I�����̓��e��ύX����
	//�����FArgs�F�`�敶����
	template<typename...Args>
	void ChengeSelect(Args...args)			
	{
		this->SelectClear();	//���݂̑I�������N���A
		this->Str = { args... };	//�W�J
		this->Str_itr = this->Str.begin();	//�擪�v�f
		return;
	}


};
