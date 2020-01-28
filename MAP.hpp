//MAP.hpp
//マップクラス

#pragma once

//####################### ヘッダファイル読み込み #######################
#include "DxLib.h"
#include "COLLISION.hpp"
#include "IMAGE.hpp"
#include <string>

//###################### マクロ定義：ファイルパス、名前 ##################
#define MY_MAP_FIELD_CSV_DIR	R"(.\MY_MAP\map_csv\field\)"	//マップcsvのファイルの場所(フィールド)
#define MY_MAP_CITY_CSV_DIR		R"(.\MY_MAP\map_csv\city\)"		//マップのcsvファイルの場所(街)

#define IMG_DIR_MAP_FIELD		R"(.\MY_MAP\map_image\field\)"	//マップの画像ファイルの場所(フィールド)
#define IMG_DIR_MAP_CITY		R"(.\MY_MAP\map_image\city\)"	//マップの画像ファイルの場所(街)

//フィールドマップ
#define IMG_NAME_MAP_SOUGEN	R"(sougen.png)"			//草原の画像の名前
#define IMG_NAME_MAP_FOREST	R"(forest.png)"			//森の画像の名前
#define IMG_NAME_MAP_OCEAN	R"(ocean.png)"			//海の画像の名前
#define IMG_NAME_MAP_SPRING	R"(spring.png)"			//春の画像の名前
#define IMG_NAME_MAP_AUTUMN	R"(autumn.png)"			//秋の画像の名前
#define IMG_NAME_MAP_WINTER	R"(winter.png)"			//冬の画像の名前
#define IMG_NAME_MAP_REMAINS R"(remains.png)"		//遺跡の画像の名前
#define IMG_NAME_MAP_CASTLE	R"(castle.png)"			//魔王城の画像の名前

//街マップ
#define IMG_NAME_MAP_CITY_NW R"(city_NW.png)"			//街、北西の画像の名前
#define IMG_NAME_MAP_CITY_W	 R"(city_W.png)"			//街、西の画像の名前
#define IMG_NAME_MAP_CITY_SW R"(city_SW.png)"			//街、南西の画像の名前
#define IMG_NAME_MAP_CITY_N	 R"(city_N.png)"			//街、北の画像の名前
#define IMG_NAME_MAP_CITY_CENTER R"(city_center.png)"	//街、中央の画像の名前
#define IMG_NAME_MAP_CITY_S	 R"(city_S.png)"			//街、南の画像の名前
#define IMG_NAME_MAP_CITY_NE R"(city_NE.png)"			//街、北東の画像の名前
#define IMG_NAME_MAP_CITY_E	 R"(city_E.png)"			//街、東の画像の名前
#define IMG_NAME_MAP_CITY_SE R"(city_SE.png)"			//街、南東の画像の名前

#define MY_MAP_TEST3		R"(test_3.png)"			//テスト用
#define MY_MAP_TEST4		R"(test_4.png)"			//テスト用

//フィールドマップ
#define MY_MAP_SOUGEN_ATARI	R"(sougen_atari.csv)"	//草原の当たり判定
#define MY_MAP_FOREST_ATARI	R"(forest_atari.csv)"	//森の当たり判定
#define MY_MAP_OCEAN_ATARI	R"(ocean_atari.csv)"	//海の画像の当たり判定
#define MY_MAP_SPRING_ATARI	R"(spring_atari.csv)"	//春の画像の当たり判定
#define MY_MAP_AUTUMN_ATARI	R"(autumn_atari.csv)"	//秋の画像の当たり判定
#define MY_MAP_WINTER_ATARI	R"(winter_atari.csv)"	//冬の画像の当たり判定
#define MY_MAP_REMAINS_ATARI R"(remains_atari.csv)"	//遺跡の画像の当たり判定
#define MY_MAP_CASTLE_ATARI	R"(castle_atari.csv)"	//魔王城の画像の当たり判定

//街のマップ
#define MY_MAP_CITY_NW_ATARI R"(city_NW_atari.csv)"	//街、北西の当たり判定
#define MY_MAP_CITY_W_ATARI R"(city_W_atari.csv)"	//街、西の当たり判定
#define MY_MAP_CITY_SW_ATARI R"(city_SW_atari.csv)"	//街、南西の当たり判定
#define MY_MAP_CITY_N_ATARI R"(city_N_atari.csv)"	//街、北の当たり判定
#define MY_MAP_CITY_CENTER_ATARI R"(city_center_atari.csv)"	//街、中央の当たり判定
#define MY_MAP_CITY_S_ATARI	 R"(city_S_atari.csv)"	//街、南の当たり判定
#define MY_MAP_CITY_NE_ATARI R"(city_NE_atari.csv)"	//街、北東の当たり判定
#define MY_MAP_CITY_E_ATARI R"(city_E_atari.csv)"	//街、東の当たり判定
#define MY_MAP_CITY_SE_ATARI R"(city_SE_atari.csv)"	//街、南東の当たり判定

#define MY_MAP_TEST3_ATARI	R"(test3_atari.csv)"
#define MY_MAP_TEST4_ATARI	R"(test4_atari.csv)"


#define MAP_NG_KIND		1	//通行できないマップの種類
#define MAP_OK_KIND		1	//通行できるマップの種類
#define MAP_ENCOUNT_KIND 1	//敵と遭遇するマップの種類

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

#define RECT_STAGGER	4	//領域をずらす量

//##################### 列挙型 #########################
enum MAP_FIELD_KIND
{
	MAP_SOUGEN,				//一マップ目(草原)
	MAP_FOREST,				//ニマップ目(森)
	MAP_OCEAN,				//三マップ目(海)
	MAP_AUTUMN,				//四マップ目(秋)
	MAP_CITY,				//五マップ目(街、南)
	MAP_SPRING,				//六マップ目(春)
	MAP_WINTER,				//七マップ目(冬)
	MAP_REMAINS,			//八マップ目(遺跡)
	MAP_CASTLE				//九マップ目(魔王城)
};//フィールドマップの種類

enum MAP_CITY_KIND
{
	MAP_CITY_NW,			//一マップ目（北西）
	MAP_CITY_W,				//二マップ目（西）
	MAP_CITY_SW,			//三マップ目（南西）
	MAP_CITY_N,				//四マップ目（北）
	MAP_CITY_CNETER,		//五マップ目（中央）
	MAP_CITY_S,				//六マップ目（南）
	MAP_CITY_NE,			//七マップ目（北東）
	MAP_CITY_E,				//八マップ目（東）
	MAP_CITY_SE				//九マップ目（南東)
};//街マップの種類

enum MAP_CHENGE_DIST
{
	MAP_CHENGE_UP,		//上のマップへ
	MAP_CHENGE_DOWN,	//下のマップへ
	MAP_CHENGE_LEFT,	//左のマップへ
	MAP_CHENGE_RIGHT,	//右のマップへ
	MAP_CHENGE_NONE = -1//マップ切り替えなし
};//どの方向へマップ切り替えるか

enum MAP_NUM_KIND
{
	MAP_NG,			//通行できない
	MAP_OK,			//通行できる
	MAP_ENCOUNT		//通行できる(敵と遭遇する)
};

enum MAP_NG_NUM
{
	MAP_NG_KIND1 =101		//通行できないマップの数字
};

enum MAP_OK_NUM
{
	MAP_OK_KIND1 = 51			//通行できるマップ(敵と遭遇しない)
};
enum MAP_ENCOOUNT_NUM
{
	MAP_OK_KIND_ENCOUNT = 151	//通行できるマップ(敵と遭遇する)
};

//enum MAPIMAGEKIND
//{
//	FILED		//フィールドのマップチップ画像
//};

//##################### グローバル変数 #################

//##################### クラス定義 ###################
class MAP
{
private:
	std::string FilePath;				//パス
	std::string FileName;				//名前

	int MapData[MAP_TATE][MAP_YOKO];		//マップデータ

	IMAGE *Map_Image;		//マップ画像

	COLLISION *RectOK[MAP_TATE][MAP_YOKO];		//当たり判定(通行できる)
	COLLISION *RectEncount[MAP_TATE][MAP_YOKO];	//当たり判定(敵と遭遇する)
	COLLISION *RectNG[MAP_TATE][MAP_YOKO];		//当たり判定（通行できない）

	FILE *fp_map_csv;						//マップファイルのポインタ

	int MapNGKind[MAP_NG_KIND];				//通行できないマップの種類
	int MapOKKind[MAP_OK_KIND];				//通行できるマップの種類
	int MapEncountKind[MAP_ENCOUNT_KIND];	//敵と遭遇するマップの種類

public :
	
	MAP(const char *,const char *);				//コンストラクタ

	~MAP();				//デストラクタ

	bool LoadCsv(const char *, const char *);	//csvデータ読み込み

	int ChengeMap(int,int *);			//マップを切り替える

	void Draw();		//描画

	void CreateRect();	//当たり判定の領域を作成

	//指定された領域を取得する
	auto GetRect(int kind)
	{
		switch (kind)
		{

		case (int)MAP_NG:		//通行できない時
			
			return this->RectNG;

			break;

		case (int)MAP_OK:		//通行できるとき

			return this->RectOK;

			break;

		case (int)MAP_ENCOUNT:	//敵と遭遇するとき

			return this->RectEncount;

			break;

		default:
			break;
		}
	}

};
