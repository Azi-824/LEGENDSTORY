//DATA.hpp
//データクラス
//テキストファイルの文字コードをANSIにして保存する

#pragma once

//############## ヘッダファイル読み込み #################
#include "DxLib.h"
#include <string>
#include <fstream>
#include "PLAYER.hpp"


//############## マクロ定義：ファイル名、パス ###################
#define DATA_DIR	R"(.\MY_TEXT\Message\)"		//メッセージテキストのファイル名
#define PLAYER_DATA_DIR	R"(.\MY_DATA\Player\)"	//プレイヤーのデータのファイル名

#define DATA_NAME	R"(msg.txt)"			//メッセージテキストの名前
#define PLAYER_DATA_NAME	R"(player.txt)"	//プレイヤーのデータの名前

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

	template<typename T>					//テンプレート化
	void Input(T);							//インプット
	void Output(PLAYER *,const char *,const char *);//アウトプット

	void Draw(int, int);					//描画

};
