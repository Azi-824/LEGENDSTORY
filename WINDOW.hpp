//WINDOW.hpp
//ゲーム内で描画するウィンドウの元になるクラス

#pragma once

//######################### ヘッダファイル読み込み ###########################
#include "DxLib.h"
#include <vector>
#include <string>

//######################### マクロ定義 ###############################

//######################### クラス定義 ###############################
class WINDOW
{
private:

	std::vector<std::string> Str;					//ウィンドウ内に描画する文字列
	std::vector<std::string>::iterator Str_itr;		//文字列のハンドル

	std::vector<int>Num;	//ウィンドウ内に表示する文字列（数字）
	std::vector<int>::iterator Num_itr;		//文字列（数字）のハンドル

	int X;			//ウィンドウの枠のX座標
	int Y;			//ウィンドウの枠のY座標

	int Width;		//ウィンドウの枠の横幅
	int Height;		//ウィンドウの枠の高さ

	int StrHeight;	//文字列の高さ
	int StrWidth;	//文字列の幅

public:

	WINDOW();				//コンストラクタ

	~WINDOW();				//デストラクタ

	void SetX(int);			//X位置設定
	void SetY(int);			//Y位置設定
	void SetWidth(int);		//横幅設定
	void SetHeight(int);	//高さ設定

	int GetX(void);			//X位置取得
	int GetY(void);			//Y位置取得
	int GetWidth(void);		//横幅取得
	int GetHeight(void);	//高さ取得

	int GetStrWidth(void);	//文字列の横幅取得
	int GetStrHeight(void);	//文字列の高さ取得

	std::vector<int>::iterator GetNumPos(void);	//文字列のアドレス取得

	void SetText(const char*);			//ウィンドウ内に描画する文字をセットする
	void SetText(int);					//ウィンドウ内に描画する数字をセットする

	virtual void Draw();			//描画

};
