//ENEMY.hpp
//敵の情報を管理するクラス

#pragma once

//############### ヘッダファイル読み込み ###################
#include "DxLib.h"
#include "CHARACTOR.hpp"
#include "ANIMATION.hpp"
#include "main.hpp"
#include "EFFECT.hpp"
#include <vector>

//############### マクロ定義：ファイルパス、名前 ################
#define ENEMY_DIR		R"(.\MY_IMG\ENEMY\)"	//敵の画像のファイル

#define ENEMY_NAME_SLIME	R"(sraim.png)"			//スライムの画像の名前
#define ENEMY_NAME_YADOKARI	R"(yadokari.png)"		//ヤドカリの画像の名前

//############## マクロ定義：エラーメッセージ ###################

//############## マクロ定義 ###################
#define ENEMY_KIND 2			//敵の種類

//############## 列挙型 ########################
enum ENEMY_TYPE
{
	SLIME,				//スライム
	YADOKARI			//ヤドカリ
};

//############## クラス定義 #####################
class ENEMY :public CHARACTOR		//キャラクタークラスを継承
{
private:

	std::string Name;	//名前

	int HP;		//体力
	int ATK;	//攻撃力
	int DEF;	//防御力
	int SPD;	//はやさ
	std::vector<int> Skil;	//スキル

	bool IsLoad;	//読み込めたか

public:

	ENEMY(const char *,const char *,const char *);			//コンストラクタ

	~ENEMY();			//デストラクタ

	void SetName(const char *);	//名前設定
	void SetHP(int);		//体力設定
	void SetATK(int);		//攻撃力設定
	void SetDEF(int);		//防御力設定
	void SetSPD(int);		//速度設定

	void StateSetInit();	//敵ステータス初期設定

	const char * GetName();			//名前取得
	int GetHP();			//体力取得
	int GetATK();			//攻撃力取得
	int GetDEF();			//防御力取得
	int GetSPD();			//速度取得
	int GetSkil();			//使用するスキルの種類を取得

	bool GetIsLoad();		//読み込めたかを取得

};
