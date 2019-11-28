//MENU.cpp
//メニューウィンドウ用のクラス

//############ ヘッダファイル読み込み ##################
#include "MENU.hpp"

//########### クラス定義 ###################

//コンストラクタ
MENU::MENU()
{
	this->Menu = { "ステータス","なかま","アイテム","そうび","セーブ" };	//メニューウィンドウの文字列を設定
	this->Menu_itr = this->Menu.begin();	//先頭のアドレスを入れる

	this->X = 100;		//初期位置を100で設定
	this->Y = 100;		//初期位置を100で設定

	this->Width = 100;	//初期幅を100で設定
	this->Height = 180;	//初期高さを180で設定

	return;

}

//デストラクタ
MENU::~MENU()
{
	//vectorのメモリ解放を行う
	std::vector<std::string> v;			//空のvectorを作成する
	this->Menu.swap(v);					//空と中身を入れ替える

	return;

}

//描画
void MENU::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率50％に設定

	DrawBox(this->X, this->Y, this->X + this->Width, this->Y + this->Height, GetColor(0, 0, 0), TRUE);	//塗りつぶしありで四角形を描画

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//描画モードを通常に戻す

	int cnt = 0;	//描画位置用
	
	for (this->Menu_itr=this->Menu.begin();this->Menu_itr!=this->Menu.end();++this->Menu_itr)
	{
		DrawFormatString(this->X, this->Y + cnt * MENU_SPACE, GetColor(255, 255, 255), "%s\n", this->Menu_itr->c_str());	//文字描画
		cnt++;
	}

	return;

}
