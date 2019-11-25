//TEXTSTR.hpp
//文字列、文章を管理する

#pragma once

//###################### ヘッダファイル読み込み ####################
#include "DxLib.h"
#include <string>
#include <vector>

//###################### マクロ定義 #########################

//###################### クラス定義 #########################
class TEXTSTR
{
private:

	int Width;						//文字列の横幅
	
	//std::vector	<std::string> Str_2;	//文字列を管理する
	std::string Str;

	bool IsFontLoad;				//フォントは読み込めたか

public:

	TEXTSTR();		//コンストラクタ

	~TEXTSTR();		//デストラクタ	

	void SetText(const char*, int);	//文字列をセットする
	
	int GetWidth();				//文字列の横幅を取得

	void Draw(int, int,int);		//描画

};
