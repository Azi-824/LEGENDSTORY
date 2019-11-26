//TEXTSTR.hpp
//文字列、文章を管理する

#pragma once

//###################### ヘッダファイル読み込み ####################
#include "DxLib.h"
#include <string>
#include <vector>


//###################### マクロ定義 #########################
#define STR_SPACE	100		//文字列間の空白

//###################### クラス定義 #########################
class TEXTSTR
{
private:

	int Width;							//文字列の横幅
	
	std::vector	<std::string> Str;	//文字列を管理する

	bool IsFontLoad;					//フォントは読み込めたか

public:

	TEXTSTR();		//コンストラクタ

	~TEXTSTR();		//デストラクタ	

	void SetText(std::vector<std::string>);	//文字列をセットする
	
	int GetWidth();									//文字列の横幅を取得

	void Draw(int, int, int);					//描画

	void Draw(int, int, int ,unsigned int);			//色を指定して描画

};
