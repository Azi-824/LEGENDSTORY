//PLAYER.hpp
//プレイヤークラス

#pragma once

//################## ヘッダファイル読み込み #####################
#include "DxLib.h"
#include "ANIMATION.hpp"
#include "CHARACTOR.hpp"
#include "COLLISION.hpp"

//################# マクロ定義: ファイルパス、名前 #######################
//#define ANIME_DIR_PLAYER R"(.\MY_ANIME\walk\)"		//プレイヤーの画像フォルダの名前
//
//#define ANIME_NAME_PLAYER R"(player_walk.png)"		//プレイヤーの画像の名前
//

//################# クラス定義 ##################
class PLAYER
{
private:
	ANIMATION *Anime;		//歩行画像
	COLLISION *Collision;	//当たり判定
	CHARACTOR *Ilast;		//立ち絵

	int HP;					//HP
	int ATK;				//攻撃力
	int DEF;				//防御力
	int SPD;				//速度

	int MoveSpeed;			//移動速度
	int Dist;				//移動向き

	bool IsArive;			//生きているか
	bool IsDraw;			//描画してよいか
	bool IsKeyOperation;	//キーボードで操作できるか
	bool IsKeyDown;			//キーボードが押されているか

public:
	PLAYER();				//コンストラクタ
	~PLAYER();				//デストラクタ

	bool SetInit();			//初期設定
	bool SetAnime(const char *, const char *, int, int, int, int, int, double, bool);	//アニメーション画像の設定
	bool SetImage(const char *, const char *);		//画像の設定
	
	void SetHP(int);		//体力設定
	void SetATK(int);		//攻撃力設定
	void SetDEF(int);		//防御力設定
	void SetSPD(int);		//速度設定
	void SetMoveSpeed(int);	//移動速度設定
	void SetIsArive(bool);	//生きているかを設定
	void SetIsDraw(bool);	//描画してよいかを設定
	void SetKeyOperation(bool); //キーボードで操作できるか設定



	int GetHP();			//体力取得
	int GetATK();			//攻撃力取得
	int GetDEF();			//防御力取得
	int GetSPD();			//速度取得
	int GetMoveSpeed();		//移動速度取得
	bool GetIsArive();		//生きているか取得
	bool GetIsDraw();		//描画できるか取得
	bool GetKeyOperation();		//キーボードで操作できるか取得
	COLLISION * GetCollision();	//当たり判定を取得



	void DrawAnime();			//描画

	void Operation(KEYDOWN *);	//操作

	void MoveUp();				//上へ移動
	void MoveDown();			//下へ移動
	void MoveLeft();			//左へ移動
	void MoveRight();			//右へ移動

};
