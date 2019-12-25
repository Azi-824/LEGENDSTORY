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
#define ENEMY_NAME_BAT		R"(bat.png)"			//こうもりの画像の名前
#define ENEMY_NAME_FARAO	R"(farao.png)"			//ファラオの画像の名前
#define ENEMY_NAME_GOBURIN	R"(goburin.png)"		//ゴブリンの画像の名前
#define ENEMY_NAME_AKUMA	R"(akuma.png)"			//悪魔の画像の名前
#define ENEMY_NAME_HARPY	R"(harpy.png)"			//ハーピーの画像の名前

//############## マクロ定義：エラーメッセージ ###################

//############## マクロ定義 ###################
#define ENEMY_KIND 7			//敵の種類

//############## 列挙型 ########################
enum ENEMY_TYPE
{
	SLIME,				//スライム
	YADOKARI,			//ヤドカリ
	BAT,				//こうもり
	FARAO,				//ファラオ
	GOBURIN,			//ゴブリン
	AKUMA,				//悪魔
	HARPY,				//ハーピー
};

//############## クラス定義 #####################
class ENEMY :public CHARACTOR		//キャラクタークラスを継承
{
private:

	std::string Name;	//名前

	int MaxHP;	//最大HP
	int HP;		//体力
	int ATK;	//攻撃力
	int DEF;	//防御力
	int SPD;	//はやさ
	
	int EXP;	//経験値

	int EmergenceMap;	//出現するMAPのNo
	int EncounteRate;	//遭遇率

	std::vector<int> Skil;	//スキル

	int EneType;	//敵の種類

	bool IsLoad;	//読み込めたか

public:

	ENEMY(const char *,const char *);			//コンストラクタ

	~ENEMY();			//デストラクタ

	void SetName(const char *);	//名前設定
	void SetMaxHP(int);		//最大体力設定
	void SetHP(int);		//体力設定
	void SetATK(int);		//攻撃力設定
	void SetDEF(int);		//防御力設定
	void SetSPD(int);		//速度設定
	void SetSkil(int);		//スキル設定
	void SetEXP(int);		//経験値設定

	void SetEmergenceMap(int);	//出現MAPNoの設定
	void SetEncounteRate(int);	//遭遇率設定

	void StateSetInit();	//敵ステータス初期設定

	const char * GetName();			//名前取得
	int GetHP();			//体力取得
	int GetATK();			//攻撃力取得
	int GetDEF();			//防御力取得
	int GetSPD();			//速度取得
	int GetSkil();			//使用するスキルの種類を取得
	int GetEXP();			//経験値取得
	
	int GetEmergenceMap();	//出現MAPNoの所得
	int GetEncounteRate();	//遭遇率の取得

	bool GetIsLoad();		//読み込めたかを取得

};
