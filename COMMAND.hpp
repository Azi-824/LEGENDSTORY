//COMMAND.hpp
//バトルコマンドクラス

#pragma once

//##################### ヘッダファイル読み込み ####################
#include "DxLib.h"
#include <vector>
#include <string>

//#################### マクロ定義 ########################
#define COMMAND_SPACE		30		//コマンド間の間隔

//#################### クラス定義 ########################
class COMMAND
{
private:

	std::vector<std::string> Command;					//コマンドウィンドウの文字列
	std::vector<std::string>::iterator Command_itr;		//文字列のハンドル

	int X;			//コマンドウィンドウの枠のX座標
	int Y;			//コマンドウィンドウの枠のY座標

	int Width;		//コマンドウィンドウの枠の横幅
	int Height;		//コマンドウィンドウの枠の高さ

	int StrHeight;	//文字列の高さ

public:

	COMMAND();			//コンストラクタ

	~COMMAND();			//デストラクタ

	void Draw();		//描画

	void Next();		//次の要素へ

	void Back();		//前の要素へ

};
