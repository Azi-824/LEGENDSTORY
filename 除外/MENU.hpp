//MENU.hpp
//���j���[�E�B���h�E�p�N���X

#pragma once

//######################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "DxLib.h"
#include <vector>
#include <string>

//######################### �}�N����` ###########################



//######################### �񋓌^ ###############################

//######################### �N���X��` ###########################
class MENU
{
private :
	
	int X;			//���j���[�E�B���h�E�̘g��X���W
	int Y;			//���j���[�E�B���h�E�̘g��Y���W

	int Width;		//���j���[�E�B���h�E�̘g�̉���
	int Height;		//���j���[�E�B���h�E�̘g�̍���

	int StrHeight;	//������̍���

	bool IsChoise;	//�I������Ă��邩

public:

	MENU();			//�R���X�g���N�^

	~MENU();		//�f�X�g���N�^

	void Reset();	//�I��v�f�����Z�b�g

	void SetIsChoise(bool);	//�I������Ă��邩�ݒ�

	bool GetIsChoise(void);	//�I������Ă��邩�擾

};
