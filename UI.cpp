//UI.cpp
//ゲーム内で使用するUIを管理するクラス

//####################### ヘッダファイル読み込み ########################
#include "UI.hpp"

//####################### クラス定義 ################################

//コンストラクタ
UI::UI()
{
	this->StateWindow = new STATEWINDOW();	//ステータスウィンドウ作成

	return;
}

//デストラクタ
UI::~UI()
{
	delete this->StateWindow;	//StateWindow破棄
	return;
}

//ステータスウィンドウの設定
void UI::SetStateWindow(PLAYER *player)
{
	this->StateWindow->SetText(player->GetHP());	//HPを設定
	return;
}

//ステータスウィンドウ描画
void UI::DrawStateWindow()
{
	this->StateWindow->Draw();	//描画
}
