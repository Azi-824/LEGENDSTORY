//MAP.hpp
//マップクラス

#pragma once

//####################### ヘッダファイル読み込み #######################
#include "DxLib.h"
#include <string>

//###################### マクロ定義：ファイルパス、名前 ##################
#define MY_MAP_DIR		R"(.\MY_MAP\map_csv\)"			//マップcsvのファイルの場所
#define MY_MAP_IMG_DIR	R"(.\MY_MAP\map_image\)"		//マップ画像のファイルの場所

#define MY_MAP_1		R"(map_1.csv)"				//マップcsvの名前
#define MY_MAP_IMAGE	R"(pipo-map001.png)"		//マップ画像の名前

//##################### マクロ定義：エラーメッセージ ####################
#define MAP_ERROR_TTILE		"MAP_ERROR"						//エラータイトル
#define MAP_ERROR_MSG		"マップが読み込めませんでした"	//エラーメッセージ

//##################### マクロ定義 ########################
#define MAP_YOKO		20			//マップの数（横）
#define MAP_TATE		15			//マップの数（縦）

#define MAP_BUN_YOKO	8			//マップの分割数（横）
#define MAP_BUN_TATE	11			//マップの分割数（縦）

#define MAP_YOKO_SIZE	40			//マップの大きさ（横）
#define MAP_TATE_SIZE	40			//マップの大きさ（縦）



//##################### クラス定義 ###################
class MAP
{
private:
	std::string FilePath;				//パス
	std::string FileName;				//名前

	int Handle[MAP_BUN_TATE * MAP_BUN_YOKO];		//ハンドル
	int X[MAP_BUN_TATE * MAP_BUN_YOKO];				//X位置
	int Y[MAP_BUN_TATE * MAP_BUN_YOKO];				//Y位置
	int Width[MAP_BUN_TATE * MAP_BUN_YOKO];			//幅
	int Height[MAP_BUN_TATE * MAP_BUN_YOKO];		//高さ

	int MapData[MAP_TATE][MAP_YOKO];		//マップデータ

	FILE *fp_map_csv;						//マップファイルのポインタ

public :
	
	MAP();				//コンストラクタ

	~MAP();				//デストラクタ

	bool LoadCsv(const char *, const char *);	//csvデータ読み込み

	void Draw();		//描画

};
