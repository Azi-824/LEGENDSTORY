//FONT.hpp
//フォントクラス

#pragma once

//################# ヘッダファイル読み込み ######################
#include "DxLib.h"
#include <string>
#include <vector>


//################ マクロ定義 ファイルパスと名前 ###############
#define MY_FONT_DIR		R"(.\MY_FONT)"						//フォントファイルの場所

#define MY_FONT_NAME	R"(\GD-DOTFONT-DQ-OTF.otf)"			//フォントの名前
#define MY_FONT_NAME2	R"(\PixelMplus10-Regular.ttf)"			//フォントの名前

//############### マクロ定義 ##################
#define FONT_NAME		("GD-DOTFONT-DQ-OTF")				//フォントの正式名称
#define FONT_NAME2		("PixelMplus10 Regular")			//フォント2の正式名称
#define DEFAULT_FONTSIZE	20								//デフォルトのフォントサイズ
#define	MSG_FONTSIZE		40								//メッセージのフォントサイズ
#define BIG_FONTSIZE		64								//フォントサイズ大

#define FONT_KIND			2								//フォントの種類

//################ マクロ定義 エラーメッセージ #################
#define FONT_ERROR_TITLE "FONT_ERROR"						//エラータイトル
#define FONT_ERROR_MSG	"フォントが読み込めませんでした"	//エラーメッセージ

//################ 列挙型 ################
enum FONT_TYPE
{
	TITLE_FONT,		//タイトル等で使用するフォント
	TEXT_FONT		//テキスト等で使用するフォント
};

//################ クラスの定義 ##################
class FONT {

private:
	std::vector<std::string> FilePath;				//パス
	std::vector<std::string>::iterator Path_itr;	//パスのイテレータ
	std::vector<std::string> FileName;				//名前
	std::vector<std::string>::iterator Name_itr;	//名前のイテレータ

	int LoadFontNow;		//読み込んだフォントの数

	bool Isload;			//読み込めた

public:

	FONT(const char *,const char *,const char *);		//コンストラクタ

	FONT();									//デフォルトコンストラクタ
	 
	~FONT();								//デストラクタ

	bool GetIsLoad();						//読み込めたか

	void SetSize(int);						//フォントサイズ設定

	void AddFont(const char *, const char *, const char *);	//フォント追加

	void ChengFont(int);					//フォント変更

};
