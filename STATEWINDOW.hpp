//STATEWINDOW.hpp
//ステータスウィンドウクラス

#pragma once

//######################## ヘッダファイル読み込み ##########################
#include "DxLib.h"
#include "WINDOW.hpp"

//######################## マクロ定義 ############################

//######################## クラス定義 ############################
class STATEWINDOW :public WINDOW		//WINDOWクラス継承
{
private:

public:

	STATEWINDOW();		//コンストラクタ

	~STATEWINDOW();		//デストラクタ

	void Draw();		//描画

};
