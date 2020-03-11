//MENU.hpp
//メニューウィンドウ用クラス

#pragma once

//######################### ヘッダファイル読み込み ######################
#include "DxLib.h"
#include <vector>
#include <string>

//######################### マクロ定義 ###########################
#define MENU_SPACE	30			//文字と文字の間隔

//メニュー一覧
#define MENU_LIST_WINDOW_RELATIVE_X	100	//メニューウィンドウ(一覧)の相対位置(X)
#define MENU_LIST_WINDOW_RELATIVE_Y	100	//メニューウィンドウ(一覧)の相対位置(Y)
#define MENU_LIST_WINDOW_WIDTH	150		//メニューウィンド(一覧)の幅
#define MENU_LIST_WINDOW_HEIGHT	180		//メニューウィンド(一覧)の高さ
#define MENU_WINDOW_CHENGE_POSX	100		//メニューウィンドウ(一覧)を左右どちらに表示するか判断するときのX位置
#define MENU_WINDOW_CHENGE_POSY	85		//メニューウィンドウ(一覧)を左右どちらに表示するか判断するときのY位置

//メニュー毎
#define MENU_WINDOW_X	200				//選んだメニュー毎のウィンドウの描画開始X位置
#define MENU_WINDOW_Y	50				//選んだメニュー毎のウィンドウの描画開始Y位置
#define MENU_TEXT_X		220				//選んだメニュー毎の内容の描画開始X位置
#define MENU_TEXT_Y		75				//選んだメニュー毎の内容の描画開始Y位置
#define MENU_TEXT_IND_Y	55				//選んだメニュー毎の目次描画開始Y位置
#define MENU_WINDOW_WIDTH	600			//選んだメニュー毎のウィンドウの横幅
#define MENU_WINDOW_HEIGHT	500			//選んだメニュー毎のウィンドウの高さ


//######################### 列挙型 ###############################
enum MENU_COMMAND
{
	MENU_STATUS,		//ステータス
	MENU_ITEM,			//アイテム
	MENU_EQUIPMENT,		//装備
	MENU_SETUMEI,		//操作説明
	MENU_SAVE			//セーブ
};

enum MENU_EQUIP_DIR
{
	MENU_EQUIP_SELECT_KIND,		//武器か防具かを選択する段階
	MENU_EQUIP_SELECT_EQUIP,	//装備する武器、もしくは防具を選択する段階
	MENU_EQUIP_SELECT_DECISION	//装備するか選択する段階（はい、か、いいえ）
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

	void Reset();	//選択要素をリセット

	void SetIsChoise(bool);	//選択されているか設定

	bool GetIsChoise(void);	//選択されているか取得

};
