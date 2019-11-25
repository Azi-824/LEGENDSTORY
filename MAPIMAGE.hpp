//MAPIMAGE.hpp
//使用するマップチップのクラス

#pragma once

//################### ヘッダファイル読み込み ####################
#include "DxLib.h"
#include <string>

//################### マクロ定義：ファイルパス、名前 ####################
#define MY_MAP_IMG_DIR	R"(.\MY_MAP\map_image\)"		//マップ画像のファイルの場所

#define MY_MAP_IMAGE	R"(pipo-map001.png)"			//マップ画像の名前

//##################### マクロ定義：エラーメッセージ ####################
#define MAP_ERROR_TTILE		"MAP_ERROR"						//エラータイトル
#define MAP_ERROR_MSG		"マップが読み込めませんでした"	//エラーメッセージ

//##################### マクロ定義 ###########################
#define MAP_BUN_YOKO	8			//マップの分割数（横）
#define MAP_BUN_TATE	11			//マップの分割数（縦）

#define MAP_IMAGE_KIND	1			//使用するマップイメージ画像の種類

#define MAP_YOKO_SIZE	40			//マップの大きさ（横）
#define MAP_TATE_SIZE	40			//マップの大きさ（縦）

//##################### 列挙型 ######################
enum MAPIMAGEKIND
{
	FILED		//フィールドのマップチップ画像
};

//##################### クラス定義 ############################
class MAPIMAGE
{
private:
	
	std::string FilePath;				//パス
	std::string FileName;				//名前

	int Handle[MAP_IMAGE_KIND][MAP_BUN_TATE * MAP_BUN_YOKO];		//ハンドル
	int X[MAP_IMAGE_KIND][MAP_BUN_TATE * MAP_BUN_YOKO];				//X位置
	int Y[MAP_IMAGE_KIND][MAP_BUN_TATE * MAP_BUN_YOKO];				//Y位置
	int Width[MAP_IMAGE_KIND][MAP_BUN_TATE * MAP_BUN_YOKO];			//幅
	int Height[MAP_IMAGE_KIND][MAP_BUN_TATE * MAP_BUN_YOKO];		//高さ

	bool IsLoad;						//読み込めたか

public:

	MAPIMAGE();					//コンストラクタ

	~MAPIMAGE();				//デストラクタ	

	int * GetHandle(int);		//指定したマップチップのハンドルを取得

	bool GetIsLoad();			//読み込めたか

};

