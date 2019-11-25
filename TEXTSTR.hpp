//TEXTSTR.hpp
//文字列、文章を管理する

#pragma once

//###################### ヘッダファイル読み込み ####################
#include "DxLib.h"
#include "FONT.hpp"
#include <string>
#include <vector>

//###################### マクロ定義 #########################

//###################### クラス定義 #########################
class TEXTSTR
{
private:

	FONT *font;	//フォント

	int Width;						//文字列の横幅
	
	std::vector	<std::string> Str;	//文字列を管理する

	bool IsFontLoad;				//フォントは読み込めたか

public:

	TEXTSTR();		//コンストラクタ

	~TEXTSTR();		//デストラクタ	

	void SetText(char *, int);	//文字列をセットする
	
	int GetWidth();				//文字列の横幅を取得

	void Draw(int, int);		//描画

};
