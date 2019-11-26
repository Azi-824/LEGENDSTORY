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
	this->Str.swap(v);				//空と中身を入れ替える

	return;
}

//幅を取得する
int TEXTSTR::GetWidth()
{

	int Strlen = 0;		//文字列の長さ取得用
	std::string TotalStr;
	for (unsigned int i = 0; i < this->Str.size(); i++)
	{
		TotalStr += this->Str[i].c_str();		//文字列をくっつける
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
	this->Str.resize(str.size());		//要素数を変更
	this->Str.swap(str);				//文字列をセット

	this->Pos = this->Str.begin();	//最初は一番最初の要素を選択状態にする	

	return;
}

//描画
//引数：int：X位置
//引数：int：Y位置
//引数：int：要素数
void TEXTSTR::Draw(int x, int y,int num)
{

	for (int cnt = 0; cnt < num; cnt++)
	{
		if (*this->Pos==this->Str[cnt])	//選択状態だったら
		{
			DrawString(x + cnt * 100, y - 50, this->Str[cnt].c_str(), GetColor(0, 0, 0));	//上にずらして描画
		}
		else				//非選択状態だったら
		{
			DrawString(x + cnt * 100, y, this->Str[cnt].c_str(), GetColor(0, 0, 0));	//描画

		}

	}
	return;
}

//描画
//引数：int：X位置
//引数：int：Y位置
//引数：int：要素数
//引数；unsigned int ：描画色
void TEXTSTR::Draw(int x, int y, int num ,unsigned int color)
{
	for (int cnt = 0; cnt < num; cnt++)
	{
		if (*this->Pos == this->Str[cnt])	//選択状態だったら
		{
			DrawString(x + cnt * 100, y - 50, this->Str[cnt].c_str(), color);	//上にずらして描画
		}
		else								//非選択状態だったら
		{
			DrawString(x + cnt * 100, y, this->Str[cnt].c_str(), color);		//描画

		}
	}

	return;
}

//選択している文字列を次の要素に変更する
void TEXTSTR::Next()
{
	if (this->Pos != this->Str.end()-1)	//最後の要素でなければ
	{
		this->Pos++;	//次の要素へ
	}
		return;
}

//選択している文字列を次の要素に変更する
void TEXTSTR::Back()
{
	if (this->Pos != this->Str.begin())	//最初の要素でなければ
	{
		this->Pos--;	//前の要素へ
	}
	return;
}