//ITEM.hpp
//アイテムクラス

#pragma once

//#################### ヘッダファイル読み込み ########################
#include "DxLib.h"
#include <vector>
#include <string>

//#################### マクロ定義 ############################
#define ITEM_KIND 2		//アイテムの種類

#define ITME_YAKUSOU_RECOVERY_AMOUNT 30	//薬草の回復量

//#################### クラス定義 ############################
class ITEM
{
private:

	std::string Name;				//アイテム名

	std::string Description;		//アイテムの説明文

public:

	ITEM();				//コンストラクタ

	~ITEM();			//デストラクタ

	void SetName(const char *);				//アイテム名設定

	void SetDescription(const char *);		//説明文を設定

	const char * GetName(void);				//名前取得

	const char * GetDescription(void);		//説明文取得

};
