//PLAYER.hpp
//プレイヤークラス

#pragma once

//################## ヘッダファイル読み込み #####################
#include "DxLib.h"
#include "ANIMATION.hpp"
#include "CHARACTOR.hpp"
#include "COLLISION.hpp"
#include "MENU.hpp"
#include "COMMAND.hpp"
#include "ENEMY.hpp"
#include "STATEWINDOW.hpp"

//################# マクロ定義: ファイルパス、名前 #######################

//################# 列挙型 ######################
enum COMMANDTYPE
{
	ATACK,		//攻撃
	DEFENSE,	//防御
	MAGIC,		//魔法
	ITEM,		//アイテム
	ESCAPE,		//逃げる
};	//選択したコマンドの種類

//################# クラス定義 ##################
class PLAYER
{
private:
	ANIMATION *Anime;		//歩行画像
	ANIMATION *AtkEffect;	//攻撃エフェクト
	ANIMATION *MagicEffect;	//魔法エフェクト
	
	COLLISION *Collision;	//当たり判定
	CHARACTOR *Ilast;		//立ち絵

	std::string Name;		//キャラの名前

	int MaxHP;				//HPの最大値
	int NowHP;				//現在のHP
	int MP;					//MP
	int ATK;				//攻撃力
	int DEF;				//防御力
	int SPD;				//速度

	int SendDamege;			//与えるダメージ
	int RecvDamege;			//受けるダメージ

	int MoveSpeed;			//移動速度
	int Dist;				//移動向き

	bool IsArive;			//生きているか
	bool IsDraw;			//描画してよいか
	bool IsKeyOperation;	//キーボードで操作できるか
	bool IsKeyDown;			//キーボードが押されているか
	bool IsMenu;			//メニューウィンドウが描画されているか
	bool EffectEnd;			//エフェクト描画処理が終了したか
	bool IsActMsg;			//行動メッセージ表示中か


public:
	PLAYER();				//コンストラクタ
	~PLAYER();				//デストラクタ

	bool SetInit();			//初期設定
	bool SetAnime(const char *, const char *, int, int, int, int, int, double, bool);	//アニメーション画像の設定
	bool AddEffect(const char *, const char *, int, int, int, int, int, double, bool);	//エフェクト画像の設定
	bool AddMagicEffect(const char *, const char *, int, int, int, int, int, double, bool);	//魔法エフェクト画像の設定
	bool SetImage(const char *, const char *);		//画像の設定
	void EffectReset();		//エフェクト関連のリセット
	
	void SetName(const char *);//名前設定
	void SetMaxHP(int);		//最大体力設定
	void SetHP(int);		//現在の体力設定
	void SetMP(int);		//MP設定
	void SetATK(int);		//攻撃力設定
	void SetDEF(int);		//防御力設定
	void SetSPD(int);		//速度設定
	void SetMoveSpeed(int);	//移動速度設定
	void SetIsArive(bool);	//生きているかを設定
	void SetIsDraw(bool);	//描画してよいかを設定
	void SetKeyOperation(bool); //キーボードで操作できるか設定
	void SetPosition(int, int);	//位置を設定
	void SetIsMenu(bool);		//メニュー描画中か設定


	//ステータス関係
	const char *GetName();	//名前取得
	int GetMaxHP();			//最大体力取得
	int GetHP();			//現在の体力取得
	int GetMP();			//MP取得
	int GetATK();			//攻撃力取得
	int GetDEF();			//防御力取得
	int GetSPD();			//速度取得

	int GetMoveSpeed();		//移動速度取得
	bool GetIsArive();		//生きているか取得
	bool GetIsDraw();		//描画できるか取得
	bool GetKeyOperation();		//キーボードで操作できるか取得
	COLLISION * GetCollision();	//当たり判定を取得
	bool GetEffectEnd();		//エフェクトの描画処理が終了したか取得
	bool GetIsMenu();			//メニュー描画中か取得
	int GetSendDamege();		//与えたダメージを取得
	int GetRecvDamege();		//受けたダメージを取得
	bool GetIsActMsg();			//行動メッセージ表示中か取得


	void DrawAnime();			//描画
	void DrawAtk(int, int);		//攻撃エフェクト描画
	void DrawMagic(int, int);	//魔法エフェクト描画

	void Operation(KEYDOWN *);	//操作

	void MoveUp();				//上へ移動
	void MoveDown();			//下へ移動
	void MoveLeft();			//左へ移動
	void MoveRight();			//右へ移動

	void DamegeCalc(ENEMY *);			//ダメージ計算

};
