//TEXTSTR.cpp
//������A���͂��Ǘ�����

//###################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "TEXTSTR.hpp"

//###################### �N���X��` ####################


TEXTSTR::TEXTSTR()
{
	font = new FONT(MY_FONT_DIR, MY_FONT_NAME, FONT_NAME);			//�t�H���g�𐶐�
	if (font->GetIsLoad() == false) { this->IsFontLoad = false; } 	//�ǂݍ��ݎ��s��

	return;
}

TEXTSTR::~TEXTSTR()
{
	delete font;

	return;
}

int TEXTSTR::GetWidth()
{
	return this->Width;
}


