//UI.hpp
//ゲーム内で使用するUIを管理するクラス

#pragma once

//######################### ヘッダファイル読み込み #############################
#include "DxLib.h"
#include "STATEWINDOW.hpp"
#include "PLAYER.hpp"

//######################### マクロ定義 #####################################

//######################### クラス定義 #####################################
class UI
{
private:

	STATEWINDOW *StateWindow;		//ステータスウィンドウ

public:

	UI();					//コンストラクタ

	~UI();					//デストラクタ

	void SetStateWindow(PLAYER *);	//ステータスウィンドウの設定をする

	void DrawStateWindow();			//ステータスウィンドウ描画

};
