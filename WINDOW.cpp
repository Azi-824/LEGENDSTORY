//WINDOW.cpp
//ゲーム内で描画するウィンドウのクラス

//########################## ヘッダファイル読み込み #########################
#include "WINDOW.hpp"

//########################## クラス定義 ##############################

//コンストラクタ
WINDOW::WINDOW()
{
	//メンバ変数初期化
	this->Str = { "" };	//文字列を初期化
	this->Str_itr = this->Str.begin();	//先頭アドレス
	this->Num = { 0 };
	this->Num_itr = this->Num.begin();	//先頭アドレス

	this->Width = 200;		//幅を初期化
	this->Height = 120;		//高さを初期化

	this->X = 0;			//X位置を初期化
	this->Y = 480;			//Y位置を初期化

	this->StrHeight = GetFontSize();	//高さを取得

}

//デストラクタ
WINDOW::~WINDOW()
{
	//vectorのメモリ解放を行う
	std::vector<std::string> v;			//空のvectorを作成する
	this->Str.swap(v);				//空と中身を入れ替える

	std::vector<int> v2;			//空のvectorを作成する
	this->Num.swap(v2);				//空と中身を入れ替える

	return;

}

//X位置設定
void WINDOW::SetX(int x)
{
	this->X = x;
	return;
}

//Y位置設定
void WINDOW::SetY(int y)
{
	this->Y = y;
	return;
}

//横幅設定
void WINDOW::SetWidth(int width)
{
	this->Width = width;
	return;
}

//高さ設定
void WINDOW::SetHeight(int height)
{
	this->Height = height;
	return;
}

//X位置取得
int WINDOW::GetX(void)
{
	return this->X;
}

//Y位置取得
int WINDOW::GetY(void)
{
	return this->Y;
}

//横幅取得
int WINDOW::GetWidth(void)
{
	return this->Width;
}

//高さ取得
int WINDOW::GetHeight(void)
{
	return this->Height;
}

//文字列横幅取得
int WINDOW::GetStrWidth(void)
{
	int Strlen = 0;		//文字列の長さ取得用

	Strlen = strlen(this->Str_itr->c_str());

	this->StrWidth = GetDrawStringWidth(this->Str_itr->c_str(), Strlen);	//横幅取得

	return this->StrWidth;

}

//文字列高さ取得
int WINDOW::GetStrHeight(void)
{
	this->StrHeight = GetFontSize();	//高さ取得

	return this->StrHeight;
}

//文字列（数字）アドレスの取得
std::vector<int>::iterator WINDOW::GetNumPos()
{
	return this->Num_itr;
}

//ウィンドウ内に描画する文字をセットする
void WINDOW::SetText(const char *text)
{
	*this->Str_itr = text;
	return;
}

//ウィンドウ内に描画する文字（数字）をセットする
void WINDOW::SetText(int num)
{
	*this->Num_itr = num;
	return;
}

//描画
void WINDOW::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率80％に設定

	DrawBox(this->X, this->Y, this->X + this->Width, this->Y + this->Height, GetColor(255, 0, 0), TRUE);	//塗りつぶしありで四角形を描画

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//描画モードを通常に戻す

	DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%s", this->Str_itr->c_str());	//文字描画

	return;

}
