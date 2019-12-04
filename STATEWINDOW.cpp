//STATEWINDOW.cpp
//ステータスウィンドウのクラス

//######################### ヘッダファイル読み込み #########################
#include "STATEWINDOW.hpp"

//######################### クラス定義 ############################

//コンストラクタ
STATEWINDOW::STATEWINDOW()
{
	return;
}

//デストラクタ
STATEWINDOW::~STATEWINDOW()
{
	return;
}

//描画
void STATEWINDOW::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率80％に設定

	DrawBox(this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight(), GetColor(255, 0, 0), TRUE);	//塗りつぶしありで四角形を描画

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//描画モードを通常に戻す

	auto itr = this->GetNumPos();	//描画数字取得

	//描画処理
 	DrawFormatString(this->GetX(), this->GetY(), GetColor(255, 255, 255), "HP:%d", *itr);	//HP描画
		
	++itr;	//次の要素へ

	DrawFormatString(this->GetX(), this->GetY() + 50, GetColor(255, 255, 255), "MP:%d", *itr);	//MP描画

}
