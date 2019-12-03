//WINDOW.cpp
//ゲーム内で描画するウィンドウのクラス

//########################## ヘッダファイル読み込み #########################
#include "WINDOW.hpp"

//########################## クラス定義 ##############################

//コンストラクタ
WINDOW::WINDOW()
{
	//メンバ変数初期化
	this->Window = { "" };	//文字列を初期化
	this->Window_itr = this->Window.begin();	//先頭アドレス

	this->Width = 100;		//幅を初期化
	this->Height = 100;		//高さを初期化

	this->X = 100;			//X位置を初期化
	this->Y = 100;			//Y位置を初期化

	this->StrHeight = GetFontSize();	//高さを取得

}

//デストラクタ
WINDOW::~WINDOW()
{
	//vectorのメモリ解放を行う
	std::vector<std::string> v;			//空のvectorを作成する
	this->Window.swap(v);				//空と中身を入れ替える

	return;

}

//ウィンドウ内に描画する文字をセットする
void WINDOW::SetText(const char *text)
{
	//this->Window_itr->push_back(*text);	//文字列を追加
	*this->Window_itr = text;
	return;
}

//描画
void WINDOW::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率80％に設定

	DrawBox(this->X, this->Y, this->X + this->Width, this->Y + this->Height, GetColor(0, 0, 0), TRUE);	//塗りつぶしありで四角形を描画

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//描画モードを通常に戻す

	DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%s", this->Window_itr->c_str());	//文字描画

	return;

}
