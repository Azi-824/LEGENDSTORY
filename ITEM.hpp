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

	std::vector<int> Code;			//アイテムコード
	std::vector<int> Possession;	//所持数
	std::vector<int> Recovery;		//回復量

	bool Add_flg;					//追加したかどうか

public:

	ITEM();				//コンストラクタ

	~ITEM();			//デストラクタ

	//セッタ
	void SetCode(int);				//アイテムコード設定
	void IncreasePossession(int);	//所持数増加
	void DecreasePossession(int);	//所持数減少
	void SetRecovery(int);			//回復量設定
	void SetAddFlg(bool);			//追加したか設定

	//ゲッタ
	int GetCode(int);				//アイテムコード取得
	int GetPossession(int);			//所持数取得
	int GetRecovery(int);			//回復量設定
	int GetSize();					//要素数を取得
	bool GetAddFlg(void);			//追加したか取得

};
