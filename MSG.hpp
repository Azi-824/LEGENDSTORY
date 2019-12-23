//MSG.hpp
//���b�Z�[�W�N���X

#pragma once

//################ �w�b�_�t�@�C���ǂݍ��� ##################
#include "DxLib.h"
#include "main.hpp"
#include "UI.hpp"
#include "PLAYER.hpp"
#include "ENEMY.hpp"

//################ �}�N����` ####################
#define MSG_DRAW_X 0		//���b�Z�[�W�̕`��ʒu(X)
#define MSG_DRAW_Y 400		//���b�Z�[�W�̕`��ʒu(Y)

#define RESULT_MSG_KIND	3	//���U���g��ʂ̃��b�Z�[�W�̎��

//################ �񋓌^ ########################
enum MSG_STEP
{
	WIN_MSG,		//�퓬�ɏ����������b�Z�[�W
	EXP_MSG,		//�o���l�̃��b�Z�[�W
	LEVELUP_MSG		//���x���A�b�v���b�Z�[�W
};

//################ �N���X��` ####################
class MESSAGE
{
private:

	int X;		//X�`��ʒu
	int Y;		//Y�`��ʒu

	int ResultMsgStep;		//���U���g���b�Z�[�W�̕\���i�K

	bool IsResultMsgEnd;	//���U���g��ʂ̃��b�Z�[�W�\�����I��������

public:

	MESSAGE();		//�R���X�g���N�^

	~MESSAGE();		//�f�X�g���N�^

	void DrawBattleMsg(int,int,int,PLAYER *,ENEMY *,bool);		//�퓬��ʂł̃��b�Z�[�W�`��

	void DrawDamage(int,int);			//�_���[�W�`��

	void DrawName(const char *);		//���O�`��

	void SetIsResultMsgEnd(bool);		//���U���g���b�Z�[�W�̕\�����I���������ݒ�
	void ResetResultMsg();				//���U���g���b�Z�[�W�֌W�̃����o�[�����Z�b�g

	bool GetIsResultMsgEnd(void);		//���U���g���b�Z�[�W�̕\�����I���������擾

};
