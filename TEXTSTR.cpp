//TEXTSTR.cpp
//文字列、文章を管理する

//###################### ヘッダファイル読み込み ######################
#include "TEXTSTR.hpp"

//###################### クラス定義 ####################

//コンストラクタ
TEXTSTR::TEXTSTR()
{
	return;
}

//デストラクタ
TEXTSTR::~TEXTSTR()
{
	return;
}

//幅を取得する
int TEXTSTR::GetWidth()
{

	int Strlen = 0;		//文字列の長さ取得用

	//文字列の長さを取得
	Strlen = strlen(this->Str_2.begin()->c_str());

	this->Width = GetDrawStringWidth(this->Str_2.begin()->c_str(), Strlen);		//横幅取得

	return this->Width;
}

//文字列をセットする
//引数：const char *：セットする文字列
//引数：int			：行
void TEXTSTR::SetText(std::vector<std::string> str, int row)
{
	//this->Str_2.push_back(str.front().c_str());
	//this->Str_2.assign(str.front().c_str(), str.back().c_str());
	this->Str_2.swap(str);
	return;
}

//描画
//引数：int：X位置
//引数：int：Y位置
void TEXTSTR::Draw(int x, int y,int row)
{

	for (int cnt = 0; cnt < row; cnt++)
	{
		DrawString(x+cnt*100, y, this->Str_2[cnt].c_str(), GetColor(255, 255, 255));
	}
	return;
}