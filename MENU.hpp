//MENU.hpp
//メニューウィンドウ用クラス

#pragma once

//######################### ヘッダファイル読み込み ######################
#include "DxLib.h"
#include <vector>
#include <string>

//######################### マクロ定義 ###########################
#define MENU_SPACE	30		//文字と文字の間隔

//######################### クラス定義 ###########################
class MENU
{
private :
	
	std::vector<std::string> Menu;					//メニューウィンドウの文字列
	std::vector<std::string>::iterator Menu_itr;	//文字列のハンドル

	int X;			//メニューウィンドウの枠のX座標
	int Y;			//メニューウィンドウの枠のY座標

	int Width;		//メニューウィンドウの枠の横幅
	int Height;		//メニューウィンドウの枠の高さ

	int StrHeight;	//文字列の高さ

public:

	MENU();			//コンストラクタ

	~MENU();		//デストラクタ

	void Draw();	//描画

	void Next();	//選択要素を次へ移動

	void Back();	//選択要素を前へ移動

	std::vector<std::string>::iterator GetChoiseMenu();	//選択した項目を取得

};
