//PLAYER.hpp
//プレイヤークラス

#pragma once

//################## ヘッダファイル読み込み #####################
#include "DxLib.h"
#include "ANIMATION.hpp"
#include "CHARACTOR.hpp"
#include "COLLISION.hpp"
#include "ENEMY.hpp"

//################# マクロ定義 #######################
#define EXP_INCREASE_VALUE	5		//経験値の最大値の増え幅
#define HP_INCREASE_VALUE	5		//体力の増え幅
#define MP_INCREASE_VALUE	5		//MPの増え幅
#define ATK_INCREASE_VALUE	2		//攻撃力の増え幅
#define DEF_INCREASE_VALUE	2		//防御力の増え幅
#define SPD_INCREASE_VALUE	2		//速さの増え幅

#define	DEF_BOOST	1.7				//防御を選んだ時の防御力の強化倍率
#define ATK_BOOST	2				//攻撃力の強化倍率


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
	
	COLLISION *Collision;	//当たり判定
	CHARACTOR *Ilast;		//立ち絵

	std::string Name;		//キャラの名前

	int Level;				//レベル
	int MaxEXP;				//経験値の最大値
	int NowEXP;				//現在の経験値

	int MaxHP;				//HPの最大値
	int NowHP;				//現在のHP
	int MaxMP;				//MPの最大値
	int NowMP;				//MP
	int ATK;				//攻撃力
	int DEF;				//防御力
	int SPD;				//速度

	std::vector<int> Skil;	//スキル一覧
	int ChoiseSkil;			//使用するスキル

	int SendDamege;			//与えるダメージ
	int RecvDamege;			//受けるダメージ

	int MoveSpeed;			//移動速度
	int Dist;				//移動向き

	bool IsArive;			//生きているか
	bool IsDraw;			//描画してよいか
	bool IsKeyOperation;	//キーボードで操作できるか
	bool IsKeyDown;			//キーボードが押されているか
	bool IsMenu;			//メニューウィンドウが描画されているか
	bool IsActMsg;			//行動メッセージ表示中か
	bool IsBattleWin;		//戦闘に勝ったか
	bool LevUpMsgStart_flg;	//レベルアップメッセージスタートフラグ


public:
	PLAYER();				//コンストラクタ
	~PLAYER();				//デストラクタ

	bool SetInit();			//初期設定
	bool SetAnime(const char *, const char *, int, int, int, int, int, double, bool);	//アニメーション画像の設定
	bool SetImage(const char *, const char *);		//画像の設定
	
	void SetName(const char *);//名前設定

	void SetLevel(int);		//レベル設定
	void SetMaxEXP(int);	//経験値の最大値設定
	void SetEXP(int);		//現在の経験値設定

	void SetMaxHP(int);		//最大体力設定
	void SetHP(int);		//現在の体力設定
	void SetMaxMP(int);		//最大MP設定
	void SetMP(int);		//MP設定
	void SetATK(int);		//攻撃力設定
	void SetDEF(int);		//防御力設定
	void SetSPD(int);		//速度設定

	void SetSkil(int);		//スキル一覧を設定
	void SetChoiseSkil(int);//使用するスキル設定

	void SetMoveSpeed(int);	//移動速度設定
	void SetIsArive(bool);	//生きているかを設定
	void SetIsDraw(bool);	//描画してよいかを設定
	void SetKeyOperation(bool); //キーボードで操作できるか設定
	void SetIsKeyDown(bool);	//キー入力ありか設定
	void SetPosition(int, int);	//位置を設定
	void SetIsMenu(bool);		//メニュー描画中か設定
	void SetIsBattleWin(bool);	//戦闘に勝ったか設定
	void SetLevUpMsgStartFlg(bool);	//レベルアップメッセージスタートのフラグを設定


	//ステータス関係
	const char *GetName();	//名前取得

	int GetLevel();			//レベル取得
	int GetMaxEXP();		//経験値の最大値取得
	int GetEXP();			//現在の経験値取得

	int GetMaxHP();			//最大体力取得
	int GetHP();			//現在の体力取得
	int GetMaxMP();			//最大MP取得
	int GetMP();			//MP取得
	int GetATK();			//攻撃力取得
	int GetDEF();			//防御力取得
	int GetSPD();			//速度取得
	int GetChoiseSkil();	//使用するスキル取得
	std::vector<int> GetSkil();		//スキル一覧の先頭要素取得

	int GetMoveSpeed();		//移動速度取得
	bool GetIsArive();		//生きているか取得
	bool GetIsDraw();		//描画できるか取得
	bool GetKeyOperation();		//キーボードで操作できるか取得
	COLLISION * GetCollision();	//当たり判定を取得
	bool GetIsMenu();			//メニュー描画中か取得
	int GetSendDamege();		//与えたダメージを取得
	int GetRecvDamege();		//受けたダメージを取得
	bool GetIsActMsg();			//行動メッセージ表示中か取得
	bool GetIsMove();			//移動中かどうか取得
	bool GetIsBattleWin();		//戦闘に勝ったか取得
	bool GetLevUpMsgStartFlg();	//レベルアップスタートメッセージフラグを取得

	void DrawAnime();			//描画

	void Operation(KEYDOWN *);	//操作

	void MoveUp();				//上へ移動
	void MoveDown();			//下へ移動
	void MoveLeft();			//左へ移動
	void MoveRight();			//右へ移動

	void DamegeCalc(ENEMY *,int);			//ダメージ計算

	void AddExp(int);			//経験値追加処理

	void GetNowPos(int *, int *);	//現在の位置を取得

};
