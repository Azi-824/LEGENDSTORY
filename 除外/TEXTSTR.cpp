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
	this->Str.swap(v);					//空と中身を入れ替える

	return;
}

//幅を取得する
int TEXTSTR::GetWidth()
{

	int Strlen = 0;		//文字列の長さ取得用

	std::string MaxStr;	//最も長い文字列

	MaxStr = this->Str[0].c_str();	//最も長い文字列に最初の文字列をセット

	for (int i = 0; i < this->Str.size(); i++)
	{
		if (MaxStr < this->Str[i].c_str())	//現在の最大文字列よりも大きければ
		{
			MaxStr = this->Str[i].c_str();	//最大文字列を更新
		}
	}

	//文字列の長さを取得
	Strlen = strlen(MaxStr.c_str());

	this->Width = GetDrawStringWidth(MaxStr.c_str(), Strlen);		//横幅取得

	return this->Width;
}

//高さを取得する
int TEXTSTR::GetHeight()
{
	this->Height = GetFontSize();	//フォントサイズ取得
	return this->Height;
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
void TEXTSTR::Draw(int x, int y,int num,bool arrow)
{

	for (int cnt = 0; cnt < num; cnt++)
	{
		if (this->Str.size() == 1)			//要素数が一個（選択肢なし）だったら
		{
			DrawFormatString(x, y + cnt * this->GetHeight(), GetColor(0, 0, 0), "%s", this->Str[cnt].c_str());	//通常描画
		}
		else
		{
			if (*this->Pos == this->Str[cnt])	//選択状態だったら
			{
				if (arrow)					//矢印付きだったら
				{
					DrawFormatString(x, y + cnt * this->GetHeight(), GetColor(0, 0, 0), "→%s", this->Str[cnt].c_str());	//矢印付きで描画
				}
				else
				{
					DrawFormatString(x + 50, y + cnt * this->GetHeight(), GetColor(0, 0, 0), "%s", this->Str[cnt].c_str());	//矢印なしで描画
				}
			}
			else				//非選択状態だったら
			{
				DrawFormatString(x, y + cnt * this->GetHeight(), GetColor(0, 0, 0), "%s", this->Str[cnt].c_str());	//描画

			}

		}

	}
	return;
}

//描画
//引数：int：X位置
//引数：int：Y位置
//引数：int：要素数
//引数；unsigned int ：描画色
void TEXTSTR::Draw(int x, int y, int num ,bool arrow,unsigned int color)
{
	for (int cnt = 0; cnt < num; cnt++)
	{
		if (this->Str.size() == 1)				//要素数が一個（選択肢なし）だったら
		{
			DrawFormatString(x, y + cnt * this->GetHeight(), color, "%s", this->Str[cnt].c_str());	//通常描画
		}
		else
		{
			if (*this->Pos == this->Str[cnt])	//選択状態だったら
			{
				if (arrow)						//矢印付きだったら
				{
					DrawFormatString(x, y + cnt * this->GetHeight(), color, "→%s", this->Str[cnt].c_str());	//矢印付きで描画
				}
				else
				{
					DrawFormatString(x + 50, y + cnt * this->GetHeight(), color, "%s", this->Str[cnt].c_str());	//矢印なしで描画
				}
			}
			else								//非選択状態だったら
			{
				DrawFormatString(x, y + cnt * this->GetHeight(), color, "%s", this->Str[cnt].c_str());	//描画
			}

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

//現在選択している文字列のポインタを取得する
std::vector<std::string>::iterator TEXTSTR::GetPos()
{
	return this->Pos;
}
