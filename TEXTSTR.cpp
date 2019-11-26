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

	//vectorのメモリ解放を行う
	std::vector<std::string> v;			//空のvectorを作成する
	this->Str_2.swap(v);				//空と中身を入れ替える

	return;
}

//幅を取得する
int TEXTSTR::GetWidth()
{

	int Strlen = 0;		//文字列の長さ取得用
	std::string TotalStr;
	for (unsigned int i = 0; i < this->Str_2.size(); i++)
	{
		TotalStr += this->Str_2[i].c_str();		//文字列をくっつける
	}

	//文字列の長さを取得
	Strlen = strlen(TotalStr.c_str());

	this->Width = GetDrawStringWidth(TotalStr.c_str(), Strlen);		//横幅取得

	return this->Width;
}

//文字列をセットする
//引数：vector<string>：セットする文字列
void TEXTSTR::SetText(std::vector<std::string> str)
{
	this->Str_2.swap(str);

	return;
}

//描画
//引数：int：X位置
//引数：int：Y位置
//引数：int：行数
//引数：int：要素数
void TEXTSTR::Draw(int x, int y,int row,int num)
{

	for (int cnt = 0; cnt < num; cnt++)
	{
		DrawString(x + cnt * 100, y, this->Str_2[cnt].c_str(), GetColor(0, 0, 0));	//描画
	}
	return;
}