//BATTLE.hpp
//�o�g���̗�����Ǘ�����N���X

#pragma once

//#################### �w�b�_�t�@�C���ǂݍ��� ###########################
#include "DxLib.h"

//#################### �}�N����` ############################

//#################### �񋓌^ ###############################
enum TURN
{
	MY_TURN,		//�����̃^�[��
	ENEMY_TURM		//�G�̃^�[��
};

//################# �N���X��` #####################
class BATTLE
{
private:

	int Turn;		//�ǂ���̃^�[����

	bool IsActMsg;		//�s�����b�Z�[�W�\������
	bool IsDamegeCalc;	//�_���[�W�v�Z����

public:

	BATTLE();		//�R���X�g���N�^
	
	~BATTLE();		//�f�X�g���N�^

	bool GetIsActMsg();	//�s�����b�Z�[�W�\�������擾
	bool GetIsDamegeCalc();	//�_���[�W�v�Z����

	void SetIsActMsg(bool);	//�s�����b�Z�[�W�\�������ݒ�

};
