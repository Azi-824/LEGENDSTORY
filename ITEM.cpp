//ITEM.cpp
//アイテムクラス

//##################### ヘッダファイル読み込み ######################
#include "ITEM.hpp"

//##################### クラス定義 ###########################

//コンストラクタ
ITEM::ITEM()
{
	return;
}

//デストラクタ
ITEM::~ITEM()
{
	return;
}

//名前設定
void ITEM::SetName(const char *name)
{
	this->Name = name;
	return;
}

//説明文設定
void ITEM::SetDescription(const char *desc)
{
	this->Description = desc;
	return;
}

//名前取得
const char * ITEM::GetName(void)
{
	return this->Name.c_str();
}

//説明文取得
const char * ITEM::GetDescription(void)
{
	return this->Description.c_str();
}
