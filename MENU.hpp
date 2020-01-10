//MENU.hpp
//メニューウィンドウ用クラス

#pragma once

//######################### ヘッダファイル読み込み ######################
#include "DxLib.h"
#include "PLAYER.hpp"
#include "ITEM.hpp"
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
	
	int X;			//メニューウィンドウの枠のX座標
	int Y;			//メニューウィンドウの枠のY座標

	int Width;		//メニューウィンドウの枠の横幅
	int Height;		//メニューウィンドウの枠の高さ

	int StrHeight;	//文字列の高さ

	bool IsChoise;	//選択されているか

public:

	MENU();			//コンストラクタ

	~MENU();		//デストラクタ

	void DrawChoise(int,PLAYER *,ITEM *[]);	//選んだ内容ごとの描画

	void Reset();	//選択要素をリセット

	void SetIsChoise(bool);	//選択されているか設定

	bool GetIsChoise(void);	//選択されているか取得

};
