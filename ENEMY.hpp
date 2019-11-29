//ENEMY.hpp
//敵の情報を管理するクラス

#pragma once

//############### ヘッダファイル読み込み ###################
#include "DxLib.h"
#include "CHARACTOR.hpp"

//############### マクロ定義：ファイルパス、名前 ################
#define ENEMY_DIR		R"(.\MY_IMG\ENEMY\)"	//敵の画像のファイル

#define ENEMY_NAME_SLIME	R"(sraim.png)"			//スライムの画像の名前

//############## マクロ定義：エラーメッセージ ###################


//############## クラス定義 #####################
class ENEMY :public CHARACTOR		//キャラクタークラスを継承
{
private:

	int HP;		//体力
	int ATK;	//攻撃力
	int DEF;	//防御力
	int SPD;	//はやさ

	bool IsLoad;	//読み込めたか

public:

	ENEMY(const char *,const char *);			//コンストラクタ

	~ENEMY();			//デストラクタ

	void SetHP(int);		//体力設定
	void SetATK(int);		//攻撃力設定
	void SetDEF(int);		//防御力設定
	void SetSPD(int);		//速度設定

	void StateSetInit();	//敵ステータス初期設定

	int GetHP();			//体力取得
	int GetATK();			//攻撃力取得
	int GetDEF();			//防御力取得
	int GetSPD();			//速度取得

	bool GetIsLoad();		//読み込めたかを取得



};
