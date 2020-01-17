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
#define BT_MSG_DRAW_X 15	//�퓬��ʂ̃��b�Z�[�W�̕`��ʒu(X)
#define BT_MSG_DRAW_Y 370	//�퓬��ʂ̃��b�Z�[�W�̕`��ʒu(Y)

#define RESULT_MSG_KIND	3	//���U���g��ʂ̃��b�Z�[�W�̎��

#define MSG_KIND	2	//���b�Z�[�W�̎��

//################ �񋓌^ ########################
enum MSG_STEP
{
	WIN_MSG,		//�퓬�ɏ����������b�Z�[�W
	EXP_MSG,		//�o���l�̃��b�Z�[�W
	LEVELUP_MSG		//���x���A�b�v���b�Z�[�W
};

enum MSG_TYPE
{
	MSG_BATTLE,		//�o�g�����b�Z�[�W
	MSG_RESULT		//���U���g���b�Z�[�W
};

//################ �N���X��` ####################
class MESSAGE
{
private:

	std::vector<std::string> Msg;		//���b�Z�[�W�i�[�p
	std::vector<std::string>::iterator Msg_itr;	//Msg�̃C�e���[�^

	int X;		//X�`��ʒu
	int Y;		//Y�`��ʒu

	bool IsLastMsg;	//�Ō�̃��b�Z�[�W��

	int ResultMsgStep;		//���U���g���b�Z�[�W�̕\���i�K

	bool IsResultMsgEnd;	//���U���g��ʂ̃��b�Z�[�W�\�����I��������
	bool IsDrawMsg;			//���b�Z�[�W�`�撆��
	bool IsMsgEnd;			//���b�Z�[�W�`��I����

public:

	MESSAGE();		//�R���X�g���N�^

	~MESSAGE();		//�f�X�g���N�^

	void DrawBattleMsg(int,int,int,PLAYER *,ENEMY *,bool);		//�퓬��ʂł̃��b�Z�[�W�`��

	void DrawDamage(int,int);			//�_���[�W�`��

	void DrawName(const char *);		//���O�`��

	void SetIsResultMsgEnd(bool);		//���U���g���b�Z�[�W�̕\�����I���������ݒ�
	void ResetResultMsg();				//���U���g���b�Z�[�W�֌W�̃����o�[�����Z�b�g
	void SetIsDrawMsg(bool);			//���b�Z�[�W�`�撆���ݒ�

	bool GetIsResultMsgEnd(void);		//���U���g���b�Z�[�W�̕\�����I���������擾
	int GetDrawMsgKind(void);			//�ǂ̃��b�Z�[�W��`�悵�Ă����Ԃ��擾
	bool GetIsDrawMsg(void);			//���b�Z�[�W�`�撆���擾

	void SetMsg(const char *);			//�������ݒ肷��
	void AddMsg(const char *);			//�������ǉ�����
	void NextMsg(void);					//���̃��b�Z�[�W�ֈړ�����
	void BackMsg(void);					//�O�̃��b�Z�[�W�ֈړ�����

	void DrawMsg(int, int,unsigned int);				//���b�Z�[�W�`��
	bool GetIsLastMsg(void);				//�Ō�̃��b�Z�[�W���ǂ����擾
	bool GetIsEmpty(void);					//�󂩂ǂ����擾
	bool GetIsMsgEnd(void);					//���b�Z�[�W�`�����擾

};
