//BATTLE.hpp
//バトルの流れを管理するクラス

#pragma once

//#################### ヘッダファイル読み込み ###########################
#include "DxLib.h"

//#################### マクロ定義 ############################

//#################### 列挙型 ###############################
enum TURN
{
	MY_TURN,		//味方のターン
	ENEMY_TURM		//敵のターン
};

//################# クラス定義 #####################
class BATTLE
{
private:

	int Turn;		//どちらのターンか

	bool IsActMsg;		//行動メッセージ表示中か
	bool IsDamegeCalc;	//ダメージ計算中か

public:

	BATTLE();		//コンストラクタ
	
	~BATTLE();		//デストラクタ

	bool GetIsActMsg();	//行動メッセージ表示中か取得
	bool GetIsDamegeCalc();	//ダメージ計算中か

	void SetIsActMsg(bool);	//行動メッセージ表示中か設定

};
