//BATTLE.cpp
//バトルの流れを管理するクラス

//#################### ヘッダファイル読み込み ########################
#include "BATTLE.hpp"

//#################### クラス定義 #########################

//コンストラクタ
BATTLE::BATTLE()
{
	this->IsActMsg = false;		//行動メッセージ非表示
	this->IsDamegeCalc = false;	//ダメージ計算中じゃない
	return;
}

//デストラクタ
BATTLE::~BATTLE()
{
	return;
}

//行動メッセージ表示中か取得
bool BATTLE::GetIsActMsg()
{
	return this->IsActMsg;
}

//ダメージ計算中か取得
bool BATTLE::GetIsDamegeCalc()
{
	return this->IsDamegeCalc;
}

//行動メッセージ表示中か設定
void BATTLE::SetIsActMsg(bool Isactmsg)
{
	this->IsActMsg = Isactmsg;
	return;
}
