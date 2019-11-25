//TEXTSTR.cpp
//文字列、文章を管理する

//###################### ヘッダファイル読み込み ######################
#include "TEXTSTR.hpp"

//###################### クラス定義 ####################


TEXTSTR::TEXTSTR()
{
	font = new FONT(MY_FONT_DIR, MY_FONT_NAME, FONT_NAME);			//フォントを生成
	if (font->GetIsLoad() == false) { this->IsFontLoad = false; } 	//読み込み失敗時

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


