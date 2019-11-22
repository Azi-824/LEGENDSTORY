//FONT.hpp
//フォントクラス

#pragma once

//################# ヘッダファイル読み込み ######################
#include "DxLib.h"
#include <string>


//################ マクロ定義 ファイルパスと名前 ###############
#define MY_FONT_DIR		R"(.\MY_FONT)"						//フォントファイルの場所

#define MY_FONT_NAME	R"(\GD-DOTFONT-DQ-OTF.otf)"			//フォントの名前

//############### マクロ定義 ##################
#define FONT_NAME		("GD-DOTFONT-DQ-OTF")				//フォントの正式名称
#define DEFAULT_FONTSIZE	32								//デフォルトのフォントサイズ



//################ マクロ定義 エラーメッセージ #################
#define FONT_ERROR_TITLE "FONT_ERROR"						//エラータイトル
#define FONT_ERROR_MSG	"フォントが読み込めませんでした"	//エラーメッセージ

//################ クラスの定義 ##################
class FONT {

private:
	std::string FilePath;	//パス
	std::string FileName;	//名前

	int Handle;				//ハンドル
	int Width;				//文字列の横幅

	bool Isload;			//読み込めた

public:

	FONT(const char *,const char *,const char *);		//コンストラクタ
	 
	~FONT();								//デストラクタ

	bool GetIsLoad();						//読み込めたか

	void SetSize(int);						//フォントサイズ設定

	void Draw(int ,int ,const char *);		//文字描画

	int GetWidth(const char *);				//文字列の横幅を取得する

};
