//MENU.hpp
//メニューウィンドウ用クラス

#pragma once

//######################### ヘッダファイル読み込み ######################
#include "DxLib.h"
#include <vector>
#include <string>

//######################### マクロ定義 ###########################
#define MENU_SPACE	30			//文字と文字の間隔

#define MENU_WINDOW_RELATIVE_X	100	//メニューウィンドウの相対位置(X)
#define MENU_WINDOW_RELATIVE_Y	100	//メニューウィンドウの相対位置(Y)
#define MENU_WINDOW_WIDTH	100	//メニューウィンドの幅
#define MENU_WINDOW_HEIGHT	180	//メニューウィンドの高さ
#define MENU_WINDOW_CHENGE_POSX	100		//メニューウィンドウを左右どちらに表示するか判断するときのX位置
#define MENU_WINDOW_CHENGE_POSY	85		//メニューウィンドウを左右どちらに表示するか判断するときのY位置

//######################### 列挙型 ###############################
enum MENU_COMMAND
{
	MENU_STATUS,		//ステータス
	MENU_ITEM,			//アイテム
	MENU_SOUBI,			//装備
	MENU_SAVE			//セーブ
};

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

	void Draw(int,int);	//描画
	void DrawChoise(int);	//選んだ内容ごとの描画

	void Next();	//選択要素を次へ移動

	void Back();	//選択要素を前へ移動

	void Reset();	//選択要素をリセット

	std::vector<std::string>::iterator GetChoiseMenu();	//選択した項目を取得

};
