//MAP.hpp
//マップクラス

#pragma once

//####################### ヘッダファイル読み込み #######################
#include "DxLib.h"
#include "MAPIMAGE.hpp"
#include "PLAYER.hpp"
#include "COLLISION.hpp"
#include <string>

//###################### マクロ定義：ファイルパス、名前 ##################
#define MY_MAP_DIR		R"(.\MY_MAP\map_csv\)"			//マップcsvのファイルの場所

#define MY_MAP_1_1		R"(map_1.csv)"				//マップcsvの名前
#define MY_MAP_1_2		R"(map_1_2.csv)"			//マップcsvの名前
#define MY_MAP_2_1		R"(map_2_1.csv)"			//マップcsvの名前
#define MY_MAP_2_2		R"(map_2_2.csv)"			//マップcsvの名前
#define MY_MAP_3_1		R"(map_3_1.csv)"			//マップcsvの名前
#define MY_MAP_3_2		R"(map_3_2.csv)"			//マップcsvの名前
#define MY_MAP_4_1		R"(map_4_1.csv)"			//マップcsvの名前
#define MY_MAP_4_2		R"(map_4_2.csv)"			//マップcsvの名前



#define MAP_LAYER_KIND	2							//マップデータのレイヤー数
#define MAP_DATA_KIND	4							//マップデータの種類数
#define MAP_DATA_YOKO_KIND	2						//マップデータの横方向の種類数
#define MAP_DATA_TATE_KIND	2						//マップデータの縦方の種類数

#define MAPPOS_X	MapNowPos[0]						//マップのX位置
#define MAPPOS_Y	MapNowPos[1]						//マップのY位置

#define POS_X	0									//X座標
#define POS_Y	1									//Y座標
//##################### マクロ定義：エラーメッセージ ####################

//##################### 列挙型 #########################
enum MAP_LAYER
{
	FIRST_LAYER,		//一層目
	SECOND_LAYER		//二層目
};

enum MAP_KIND
{
	MAP_1,				//一マップ目
	MAP_2,				//ニマップ目
	MAP_3,				//三マップ目
	MAP_4				//四マップ目
};

//##################### マクロ定義 ########################
#define MAP_YOKO		20			//マップの数（横）
#define MAP_TATE		15			//マップの数（縦）



//##################### クラス定義 ###################
class MAP
{
private:
	std::string FilePath;				//パス
	std::string FileName;				//名前

	int MapData[MAP_TATE][MAP_YOKO];		//マップデータ

	FILE *fp_map_csv;						//マップファイルのポインタ

public :
	
	MAP();				//コンストラクタ

	~MAP();				//デストラクタ

	bool LoadCsv(const char *, const char *);	//csvデータ読み込み

	void ChengeMap(PLAYER *,int *);				//マップを切り替える

	//int GetMapNow();						//現在のマップを取得

	void Draw(int *);		//描画

};
