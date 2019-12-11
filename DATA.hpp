//DATA.hpp
//データクラス
//テキストファイルの文字コードをANSIにして保存する

#pragma once

//############## ヘッダファイル読み込み #################
#include "DxLib.h"
#include <string>
#include <fstream>


//############## マクロ定義：ファイル名、パス ###################
#define DATA_DIR	R"(.\MY_TEXT\Message\)"		//メッセージテキストのファイル名

#define DATA_NAME	R"(msg.txt)"			//メッセージテキストの名前

//############## マクロ定義：エラーメッセージ ###################
#define DATA_ERROR_TTILE	"DATA_ERROR"						//エラータイトル
#define DATA_ERROR_MSG		"データが読み込めませんでした"		//エラーメッセージ

//############## クラス定義 #####################
class DATA
{
private:

	std::string Text;		//文字データ

public:

	DATA(const char *, const char *);		//コンストラクタ

	~DATA();								//デストラクタ

	void Draw(int, int);					//描画

};
