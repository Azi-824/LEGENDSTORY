//MENU.cpp
//メニューウィンドウ用のクラス

//############ ヘッダファイル読み込み ##################
#include "MENU.hpp"

//########### クラス定義 ###################

//コンストラクタ
MENU::MENU()
{
	this->X = 0;		
	this->Y = 0;		

	this->Width = 0;	
	this->Height = 0;	

	this->StrHeight = GetFontSize();	//高さを取得

	this->IsChoise = false;		//選択されていない

	return;

}

//デストラクタ
MENU::~MENU()
{
	return;
}

//選択要素をリセット
void MENU::Reset()
{
	this->IsChoise = false;
	return;
}
//選択されているか設定
void MENU::SetIsChoise(bool Ischoise)
{
	this->IsChoise = Ischoise;
	return;
}

//選択されているか取得
bool MENU::GetIsChoise(void)
{
	return this->IsChoise;
}
