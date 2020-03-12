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

#define SELECT_SIDE_SPACE	300	//�I�������������ɕ��ׂ��Ƃ��̊Ԋu

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
	bool IsDrawImage;	//UI�摜��`�悵�Ă悢��
	bool Side_Mode;		//�������`�悩
	bool BackFlg;		//�߂��I�񂾂�

	bool DefIsKeyOpe;		//�L�[����\���A�f�t�H���g�l
	bool DefIsDrawImage;	//UI�摜��`�悵�Ă悢���A�f�t�H���g�l


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
		this->IsDrawImage = true;			//UI�摜�`�悵�Ă悢
		this->Side_Mode = false;			//�c�����ɑI��������ׂ�
		this->BackFlg = false;				//�߂�I���͂���Ă��Ȃ�

		this->DefIsKeyOpe = true;		//�f�t�H���g�̓L�[����\
		this->DefIsDrawImage = true;	//�f�t�H���g��UI�\��

		return;
	}
	
	/*
	�I�����̓��e��ݒ肹���ɃI�u�W�F�N�g�̐����݂̂��s��
	*/
	SELECT();			//�R���X�g���N�^�̃I�[�o�[���[�h

	~SELECT();		//�f�X�g���N�^

	void SelectOperation(KEYDOWN *,MUSIC *);	//�I�����̃L�[����

	std::vector<std::string>::iterator GetNowSelect();		//���ݑI�𒆂̗v�f���擾
	int GetSelectNum(void);					//�I�������v�f�̗v�f�ԍ����擾����

	void SelectClear();						//�I�����̓��e����������
	void NowSelectReset();					//���ݑI�𒆂̗v�f���ŏ��ɖ߂�

	void Draw(int, int,int ,unsigned int color = GetColor(255, 255, 255),int side_space= SELECT_SIDE_SPACE);			//�I�����̓��e��`�悷��
	void DrawCenter(int, int,int , unsigned int color = GetColor(255, 255, 255));	//�I�����̓��e�𒆉��ɕ`�悷��

	void SetSize(void);						//�摜�T�C�Y�ݒ�
	void Add(const char *);					//�I�����̓��e��ǉ�

	void SetIsKeyOpe(bool);					//�L�[����\���ݒ肷��
	bool GetIsKeyOpe(void);					//�L�[����\���擾����

	void SetSelectFlg(bool);				//�I���������ݒ�
	bool GetSelectFlg(void);				//�I���������擾

	void SetIsDrawImage(bool);				//UI�摜��`�悵�Ă悢���ݒ�
	bool GetIsDrawImage(void);				//UI�摜��`�悵�Ă悢���擾

	void SetSideMode(bool);					//�I�������������ɕ��ׂ邩�ݒ�
	bool GetSideMode(void);					//�I�������������ɕ��ׂ邩�擾

	void ChengeDefault(bool, bool);			//�f�t�H���g�̏�Ԃ�ݒ�
	void Default();							//�f�t�H���g�̏�Ԃɖ߂�

	void SetBackFlg(bool);					//�߂��I���������ݒ�
	bool GetBackFlg(void);					//�߂��I���������擾


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
