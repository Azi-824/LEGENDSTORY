//PLAYER.hpp
//プレイヤークラス

#pragma once

//################## ヘッダファイル読み込み #####################
#include "DxLib.h"
#include "ANIMATION.hpp"
#include "CHARACTOR.hpp"
#include "ENEMY.hpp"
#include "MAP.hpp"
#include "WEAPON.hpp"
#include "ARMOR.hpp"
#include "ITEM.hpp"
#include <fstream>
#include "LIST_ITEM.hpp"
#include "LIST_WEAPON.hpp"
#include "LIST_ARMOR.hpp"

//################# マクロ定義 #######################
#define EXP_INCREASE_VALUE	5		//経験値の最大値の増え幅
#define HP_INCREASE_VALUE	5		//体力の増え幅
#define MP_INCREASE_VALUE	5		//MPの増え幅
#define ATK_INCREASE_VALUE	2		//攻撃力の増え幅
#define DEF_INCREASE_VALUE	2		//防御力の増え幅
#define SPD_INCREASE_VALUE	2		//速さの増え幅

#define	DEF_BOOST	1.7				//防御を選んだ時の防御力の強化倍率
#define ATK_BOOST	2				//攻撃力の強化倍率

#define MAX_BP		5				//BPの最大値
#define START_BP	1				//BPの初期値
#define MAX_USE_BP	3				//一回で使用することができるBPの最大値

#define DIST_KIND	4				//移動方向の種類

#define PLAYER_AF_CLEAR_POS_X		720	//クリア後のプレイヤーの位置
#define PLAYRT_AF_CLEAR_POS_Y		300	//クリア後のプレイヤーの位置

#define PLAYER_DATA_DIR			R"(.\MY_DATA\Player\)"		//プレイヤーのデータのファイル名
#define PLAYER_DATA_NAME		R"(Player_Data.csv)"		//プレイヤーのデータのcsvファイル
#define PLATER_DATA_INIT_NAME	R"(Player_Data_Init.csv)"	//プレイヤーの初期データのcsvファイル


//############## マクロ定義：エラーメッセージ ###################
#define PLAYER_DATA_ERROR_TTILE	"PLAYER_DATA_ERROR"								//エラータイトル
#define PLAYER_DATA_ERROR_MSG	"プレイヤーデータが読み込めませんでした"		//エラーメッセージ

//################# 列挙型 ######################
enum COMMANDTYPE
{
	COMMANDE_ATACK,		//攻撃
	COMMANDE_DEFENSE,	//防御
	COMMANDE_MAGIC,		//魔法
	COMMANDE_ITEM,		//アイテム
	COMMANDE_ESCAPE,	//逃げる
	COMMAND_NONE = -1		//コマンドを選んでいない
};	//選択したコマンドの種類

//################# クラス定義 ##################
class PLAYER
{
private:
	ANIMATION *Anime;		//歩行画像
	
	COLLISION *Collision;	//当たり判定
	SIKAKU *sikaku_draw;	//描画領域
	CHARACTOR *Ilast;		//立ち絵

	WEAPON *Weapon;			//武器
	ARMOR *Armor;			//防具
	ITEM *Item;				//アイテム

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

	int BoostPoint;			//ブーストポイント(BP)
	int UseBP;				//使用するBP

	int EquipAtk;			//装備の攻撃力
	int EquipDef;			//装備の防御力
	int Equip_WeaponCode;	//装備している武器のコード番号を格納しておく
	int Equip_ArmorCode;	//装備している防具のコード番号を格納しておく

	std::vector<int> Skil;	//スキル一覧
	int ChoiseSkil;			//使用するスキル

	int RecvDamege;			//受けるダメージ

	int MoveSpeed;			//移動速度
	int Dist;				//移動向き
	int InKeyKind;			//押されているキーボードの種類

	bool IsArive;			//生きているか
	bool IsDraw;			//描画してよいか
	bool IsKeyOperation;	//キーボードで操作できるか
	bool IsKeyDown;			//キーボードが押されているか
	bool IsMenu;			//メニューウィンドウが描画されているか
	bool IsActMsg;			//行動メッセージ表示中か
	bool IsBattleWin;		//戦闘に勝ったか
	bool LevUpMsgStart_flg;	//レベルアップメッセージスタートフラグ

	int ChengeMapKind;		//マップ切り替えの種類

public:
	PLAYER();				//コンストラクタ
	~PLAYER();				//デストラクタ

	bool SetInit();			//初期設定
	bool SetAnime(const char *, const char *, int, int, int, int, int, double, bool);	//アニメーション画像の設定
	bool SetImage(const char *, const char *);		//画像の設定
	
	void SetMP(int);		//MP設定

	void SetChoiseSkil(int);//使用するスキル設定

	void SetIsKeyDown(bool);		//キー入力ありか設定
	void SetPosRelative(int, int);	//位置を設定(相対的)
	void SetPosAbsolute(int, int);	//位置を設定(絶対的)
	void SetIsMenu(bool);			//メニュー描画中か設定
	void SetIsBattleWin(bool);		//戦闘に勝ったか設定
	void SetLevUpMsgStartFlg(bool);	//レベルアップメッセージスタートのフラグを設定
	void ResetChengeMapKind(void);	//切り替えるマップの種類をリセット
	void SetChengePos(int);			//マップ切り替えをしたときにプレイヤーの位置を設定

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

	int GetEquipAtk();		//装備攻撃力取得
	int GetEquipDef();		//装備防御力取得

	int GetChoiseSkil();		//使用するスキル取得
	std::vector<int> GetSkil();	//スキル一覧取得

	int GetMoveSpeed();			//移動速度取得
	bool GetIsArive();			//生きているか取得
	bool GetIsDraw();			//描画できるか取得
	bool GetKeyOperation();		//キーボードで操作できるか取得
	COLLISION * GetCollision();	//当たり判定を取得
	bool GetIsMenu();			//メニュー描画中か取得
	int GetRecvDamege();		//受けたダメージを取得
	bool GetIsActMsg();			//行動メッセージ表示中か取得
	bool GetIsMove();			//移動中かどうか取得
	bool GetIsBattleWin();		//戦闘に勝ったか取得
	bool GetLevUpMsgStartFlg();	//レベルアップスタートメッセージフラグを取得
	bool GetIsKeyDown();		//キー入力があるか取得
	int GetChengeMapKind();		//切り替えるマップの種類を取得

	void DrawWalk();			//描画

	void Operation(KEYDOWN *, COLLISION *[][MAP_YOKO]);	//操作

	void MoveUp();				//上へ移動
	void MoveDown();			//下へ移動
	void MoveLeft();			//左へ移動
	void MoveRight();			//右へ移動

	void DamegeCalc(ENEMY *,int);	//ダメージ計算
	void DamegeSend();				//ダメージを与える

	void AddExp(int);	//経験値追加処理

	void GetNowPos(int *, int *);	//現在の位置を取得
	void SetNowPos(int, int);		//現在の位置を設定

	int GetInKeyKind(void);		//現在のキー入力の種類を取得

	bool CheckDetectionMap(COLLISION *[][MAP_YOKO], int *, int *);	//マップとの当たり判定をする
	bool CheckDetectionMap(COLLISION *[][MAP_YOKO]);				//マップとの当たり判定をする(当たった場所を取得しない)

	void Recovery(void);			//回復させる

	//武器関係
	void EquipWeapon(int);					//武器を装備する
	WEAPON * GetWeaponClass();				//武器クラスを取得
	void SetWeaponAtk(LIST_WEAPON *);		//武器の攻撃力設定
	void AddDropWeapon(int, int);			//ドロップした武器の追加

	////防具関係
	void EquipArmor(int);					//防具を装備する
	ARMOR * GetArmorClass();				//防具クラスを取得
	void SetArmorDef(LIST_ARMOR *);			//防具の防御力設定
	void AddDropArmor(int, int);			//ドロップした防具の追加

	//アイテム関係
	bool UseItem(int);						//アイテム使用処理
	ITEM * GetItemClass();					//アイテムクラスを取得
	void SetItemRecovery(LIST_ITEM *);		//アイテムの回復量設定
	void AddDropItem(int, int, char);		//アイテム追加処理

	//セーブデータ関係
	bool LoadData(const char *, const char *);	//セーブデータ読込
	bool Save(const char *, const char *);		//セーブ

	//BP関係
	int GetBP(void);		//BP取得
	void AddBP(void);		//BP加算
	int GetUseBP(void);		//使用するBPを取得
	void PlusUseBP(void);	//使用するBPを増やす
	void MinusUseBP(void);	//使用するBPを減らす

};
