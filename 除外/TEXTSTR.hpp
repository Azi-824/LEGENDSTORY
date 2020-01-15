//TEXTSTR.hpp
//文字列、文章を管理する

#pragma once

//###################### ヘッダファイル読み込み ####################
#include "DxLib.h"
#include "KEYDOWN.hpp"
#include <string>
#include <vector>


//###################### マクロ定義 #########################
#define STR_SPACE	100			//文字列間の空白

#define DEFAULT_TEXT_Y	450		//デフォルトのテキスト描画位置（Y座標）

//###################### クラス定義 #########################
class TEXTSTR
{
private:

	int Width;							//文字列の横幅

	int Height;							//文字列の高さ
	
	std::vector	<std::string> Str;		//文字列を管理する
	
	std::vector <std::string> ::iterator Pos;	//文字列のハンドル
	
public:

	TEXTSTR();		//コンストラクタ

	~TEXTSTR();		//デストラクタ	

	void SetText(std::vector<std::string>);			//文字列をセットする
	
	int GetWidth();									//文字列の横幅を取得

	int GetHeight();								//文字列の高さを取得

	void Draw(int, int, int,bool);					//描画

	void Draw(int, int, int ,bool,unsigned int);	//色を指定して描画

	void Next();									//選択している文字列を次の要素に変更する

	void Back();									//選択している文字列を前の要素に変更する

	std::vector<std::string>::iterator GetPos();	//現在選択している文字列のポインタを取得する

};
