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

	bool IsLastMsg;	//�Ō�̃��b�Z�[�W��
	bool IsMsgEnd;			//���b�Z�[�W�`��I����

public:

	MESSAGE();		//�R���X�g���N�^

	~MESSAGE();		//�f�X�g���N�^

	void SetMsg(const char *);			//�������ݒ肷��
	void AddMsg(const char *);			//�������ǉ�����
	void NextMsg(void);					//���̃��b�Z�[�W�ֈړ�����
	void BackMsg(void);					//�O�̃��b�Z�[�W�ֈړ�����

	void DrawMsg(int, int,unsigned int);				//���b�Z�[�W�`��
	bool GetIsLastMsg(void);				//�Ō�̃��b�Z�[�W���ǂ����擾
	bool GetIsEmpty(void);					//�󂩂ǂ����擾
	bool GetIsMsgEnd(void);					//���b�Z�[�W�`�����擾
	void ResetFlg(void);					//�t���O�֌W���Z�b�g

};
