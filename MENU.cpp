//MENU.cpp
//メニューウィンドウ用のクラス

//############ ヘッダファイル読み込み ##################
#include "MENU.hpp"

//########### クラス定義 ###################

//コンストラクタ
MENU::MENU()
{
	this->Menu = { "ステータス","アイテム","そうび","セーブ" };	//メニューウィンドウの文字列を設定
	this->Menu_itr = this->Menu.begin();	//先頭のアドレスを入れる

	this->X = 100;		//初期位置を100で設定
	this->Y = 100;		//初期位置を100で設定

	this->Width = 100;	//初期幅を100で設定
	this->Height = 180;	//初期高さを180で設定

	this->StrHeight = GetFontSize();	//高さを取得

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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率80％に設定

	DrawBox(this->X, this->Y, this->X + this->Width, this->Y + this->Height, GetColor(0, 0, 0), TRUE);	//塗りつぶしありで四角形を描画

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//描画モードを通常に戻す

	int cnt = 0;	//描画位置用
	
	auto w_itr = this->Menu_itr;	//退避用

	for (this->Menu_itr=this->Menu.begin();this->Menu_itr!=this->Menu.end();++this->Menu_itr)
	{
		if (w_itr == this->Menu_itr)			//選択中の要素だったら
		{
			DrawFormatString(this->X + 10, this->Y + cnt * MENU_SPACE, GetColor(255, 255, 255), "%s\n", this->Menu_itr->c_str());	//右にずらして描画
		}
		else
		{
			DrawFormatString(this->X, this->Y + cnt * MENU_SPACE, GetColor(255, 255, 255), "%s\n", this->Menu_itr->c_str());	//文字描画
		}
		cnt++;
	}

	this->Menu_itr = w_itr;		//選択要素を元に戻す

	return;

}

//選択要素を次へ移動
void MENU::Next()
{
	if (this->Menu_itr != this->Menu.end() - 1)	//最後の要素で無ければ
	{
		this->Menu_itr++;	//次の要素へ
	}
	return;
}

//選択要素を前へ移動
void MENU::Back()
{
	if (this->Menu_itr != this->Menu.begin())	//最初の要素でなければ
	{
		this->Menu_itr--;	//前の要素へ
	}
	return;
}

//選択した項目を取得
std::vector<std::string>::iterator MENU::GetChoiseMenu()
{
	return this->Menu_itr;
}
