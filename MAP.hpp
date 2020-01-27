//MAP.hpp
//マップクラス

#pragma once

//####################### ヘッダファイル読み込み #######################
#include "DxLib.h"
#include "COLLISION.hpp"
#include "IMAGE.hpp"
#include <string>

//###################### マクロ定義：ファイルパス、名前 ##################
#define MY_MAP_DIR		R"(.\MY_MAP\map_csv\)"		//マップcsvのファイルの場所
#define IMG_DIR_MAP		R"(.\MY_MAP\map_image\)"	//マップの画像ファイルの場所

#define IMG_NAME_MAP_SOUGEN	R"(sougen.png)"			//草原の画像の名前
#define IMG_NAME_MAP_FOREST	R"(forest.png)"			//森の画像の名前
#define IMG_NAME_MAP_OCEAN	R"(ocean.png)"			//海の画像の名前
#define IMG_NAME_MAP_SPRING	R"(spring.png)"			//春の画像の名前
#define IMG_NAME_MAP_AUTUMN	R"(autumn.png)"			//秋の画像の名前
#define IMG_NAME_MAP_WINTER	R"(winter.png)"			//冬の画像の名前
#define IMG_NAME_MAP_REMAINS R"(remains.png)"		//遺跡の画像の名前
#define IMG_NAME_MAP_CASTLE	R"(castle.png)"			//魔王城の画像の名前

#define IMG_NAME_MAP_CITY_UNDER	R"(city_under.png)"	//街、下の画像の名前

#define MY_MAP_TEST3		R"(test_3.png)"			//テスト用
#define MY_MAP_TEST4		R"(test_4.png)"			//テスト用

#define MY_MAP_SOUGEN_ATARI	R"(sougen_atari.csv)"	//草原の当たり判定
#define MY_MAP_FOREST_ATARI	R"(forest_atari.csv)"	//森の当たり判定
#define MY_MAP_OCEAN_ATARI	R"(ocean_atari.csv)"	//海の画像の当たり判定
#define MY_MAP_SPRING_ATARI	R"(spring_atari.csv)"	//春の画像の当たり判定
#define MY_MAP_AUTUMN_ATARI	R"(autumn_atari.csv)"	//秋の画像の当たり判定
#define MY_MAP_WINTER_ATARI	R"(winter_atari.csv)"	//冬の画像の当たり判定
#define MY_MAP_REMAINS_ATARI R"(remains_atari.csv)"	//遺跡の画像の当たり判定
#define MY_MAP_CASTLE_ATARI	R"(castle_atari.csv)"	//魔王城の画像の当たり判定

#define MY_MAP_CITY_UNDER_ATARI	R"(city_under_atari.csv)"	//街、下の当たり判定

#define MY_MAP_TEST3_ATARI	R"(test3_atari.csv)"
#define MY_MAP_TEST4_ATARI	R"(test4_atari.csv)"


#define MAP_NG_KIND		1	//通行できないマップの種類
#define MAP_OK_KIND		2	//通行できるマップの種類

//##################### マクロ定義：エラーメッセージ ####################

//##################### マクロ定義 ########################
#define MAP_YOKO		55			//マップの数（横）
#define MAP_TATE		40			//マップの数（縦）

#define MAP_YOKO_SIZE	16			//マップの大きさ（横）
#define MAP_TATE_SIZE	16			//マップの大きさ（縦）

#define MAP_DATA_KIND	MAP_DATA_YOKO_KIND * MAP_DATA_TATE_KIND	//マップデータの種類数
#define MAP_DATA_YOKO_KIND	3									//マップデータの横方向の種類数
#define MAP_DATA_TATE_KIND	3									//マップデータの縦方の種類数

#define MAPPOS_X	MapNowPos[0]						//マップのX位置
#define MAPPOS_Y	MapNowPos[1]						//マップのY位置

#define POS_X	0									//X座標
#define POS_Y	1									//Y座標

#define RECT_STAGGER	2	//領域をずらす量

//##################### 列挙型 #########################
enum MAP_KIND
{
	MAP_SOUGEN,				//一マップ目(草原)
	MAP_FOREST,				//ニマップ目(森)
	MAP_OCEAN,				//三マップ目(海)
	MAP_AUTUMN,				//四マップ目(秋)
	MAP_CITY_UNDER,			//五マップ目(街、下)
	MAP_SPRING,				//六マップ目(春)
	MAP_WINTER,				//七マップ目(冬)
	MAP_REMAINS,			//八マップ目(遺跡)
	MAP_CASTLE				//九マップ目(魔王城)
};

enum MAP_CHENGE_DIST
{
	MAP_CHENGE_UP,		//上のマップへ
	MAP_CHENGE_DOWN,	//下のマップへ
	MAP_CHENGE_LEFT,	//左のマップへ
	MAP_CHENGE_RIGHT,	//右のマップへ
	MAP_CHENGE_NONE = -1//マップ切り替えなし
};//どの方向へマップ切り替えるか

enum MAP_NG_NUM
{
	MAP_NG_KIND1 =101		//通行できないマップの数字
};

enum MAP_OK_NUM
{
	MAP_OK_KIND1 = 51,			//通行できるマップ(敵と遭遇しない)
	MAP_OK_KIND_ENCOUNT	=151	//通行できるマップ(敵と遭遇する)
};

//enum MAPIMAGEKIND
//{
//	FILED		//フィールドのマップチップ画像
//};

//##################### クラス定義 ###################
class MAP
{
private:
	std::string FilePath;				//パス
	std::string FileName;				//名前

	int MapData[MAP_TATE][MAP_YOKO];		//マップデータ

	IMAGE *Map_Image;		//マップ画像

	COLLISION *RectOK[MAP_TATE][MAP_YOKO];		//当たり判定(通行できる)
	COLLISION *RectNG[MAP_TATE][MAP_YOKO];		//当たり判定（通行できない）

	FILE *fp_map_csv;						//マップファイルのポインタ

public :
	
	MAP(const char *,const char *);				//コンストラクタ

	~MAP();				//デストラクタ

	bool LoadCsv(const char *, const char *);	//csvデータ読み込み

	int ChengeMap(int,int *);			//マップを切り替える

	void Draw();		//描画

	void CreateRect(int *,int *);	//当たり判定の領域を作成

	//通行できない領域を取得する
	auto GetRectNG(void)
	{
		return this->RectNG;
	}

};
