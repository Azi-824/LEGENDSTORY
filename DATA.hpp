//DATA.hpp
//データクラス
//テキストファイルの文字コードをANSIにして保存する

#pragma once

//############## ヘッダファイル読み込み #################
#include "DxLib.h"
#include <string>
#include <vector>
#include <fstream>
#include "PLAYER.hpp"
#include "ENEMY.hpp"
#include "ITEM.hpp"
#include "MSG.hpp"


//############## マクロ定義：ファイル名、パス ###################
#define PLAYER_DATA_DIR	R"(.\MY_DATA\Player\)"	//プレイヤーのデータのファイル名
#define ENEMY_DATA_DIR	R"(.\MY_DATA\Enemy\)"	//敵のデータのファイル名
//#define ITEM_DATA_DIR	R"(.\MY_DATA\Item\)"	//アイテムのデータのファイル名
#define MSG_DATA_DIR	R"(.\MY_DATA\Msg\)"		//メッセージのデータのファイル名
#define MAPPOS_DATA_DIR R"(.\MY_DATA\MapPos\)"	//マップ位置のデータのファイル名

#define PLAYER_DATA_NAME	R"(Player_Data.csv)"//プレイヤーのデータのcsvファイル
#define PLATER_DATA_INIT_NAME R"(Player_Data_Init.csv)"//プレイヤーの初期データのcsvファイル
#define ENEMY_DATA_NAME		R"(Enemy_Data.csv)"	//敵のデータの名前
//#define ITEM_DATA_NAME		R"(Item_Data.csv)"	//アイテムのデータの名前
#define MSG_DATA_NAME		R"(Msg_Data.txt)"	//メッセージデータの名前
#define MAPPOS_DATA_NAME	R"(MapPos_Data.csv)"//マップ位置のデータの名前

//############## マクロ定義：エラーメッセージ ###################
#define DATA_ERROR_TTILE	"DATA_ERROR"						//エラータイトル
#define DATA_ERROR_MSG		"データが読み込めませんでした"		//エラーメッセージ

//############## クラス定義 #####################
class DATA
{
private:

public:

	DATA();		//コンストラクタ

	~DATA();								//デストラクタ

	bool LoadPlayer(PLAYER *,const char *, const char *);		//読み込み（味方データ）
	bool LoadEnemy(ENEMY *[],const char *, const char *);		//読み込み（敵データ）
	//bool LoadItem(ITEM *[], const char *, const char *);		//読み込み（アイテムデータ）
	bool LoadMsg(MESSAGE *, const char *, const char *);		//読み込み（メッセージデータ）
	bool LoadNowMap(int *, int *, const char *, const char *);	//読み込み（現在のマップ位置）
	bool Save(PLAYER *,const char *,const char *);				//セーブ
	bool SaveMap(int, int[],const char *,const char *);			//現在のマップ位置をセーブ

};
