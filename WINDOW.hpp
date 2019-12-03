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

	std::vector<std::string> Window;					//ウィンドウ内に描画する文字列
	std::vector<std::string>::iterator Window_itr;		//文字列のハンドル

	int X;			//ウィンドウの枠のX座標
	int Y;			//ウィンドウの枠のY座標

	int Width;		//ウィンドウの枠の横幅
	int Height;		//ウィンドウの枠の高さ

	int StrHeight;	//文字列の高さ
	int StrWidth;	//文字列の幅

public:

	WINDOW();				//コンストラクタ

	~WINDOW();				//デストラクタ

	void SetText(const char*);			//ウィンドウ内に描画する文字をセットする

	void Draw();			//描画

};
