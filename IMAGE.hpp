/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* IMAGE.cpp     																				　 */
/* 画像クラス 																					　 */

#pragma once

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include <string>
#include <vector>

//########## マクロ定義：画像のファイルパスと名前 ##########
#define MY_IMG_DIR_TITLE	R"(.\MY_IMG\TITLE)"				//タイトルの画像のファイルの場所
#define MY_IMG_DIR_CHARCTOR	R"(.\MY_IMG\CHARACTOR)"			//キャラクターの画像のファイルの場所
#define MY_IMG_DIR_BACK		R"(.\MY_IMG\BACK)"				//背景画像のファイルの場所

#define MY_ING_NAME_TITLE	R"(\Title_Logo.png)"			//タイトル画像の名前
#define MY_IMG_NAME_PLAYER	R"(\yh032.png)"					//主人公の画像の名前
#define MY_IMG_NAME_BACK	R"(\title_back.jpg)"			//背景画像の名前

//########## マクロ定義：エラーメッセージ##########
#define IMAGE_ERROR_TITLE "IMAGE_ERROR"					//エラータイトル
#define IMAGE_ERROR_MSG	"画像が読み込めませんでした"	//エラーメッセージ

//########## クラスの定義 ##########

class IMAGE
{
private:
	std::string FilePath;	//パス
	std::string FileName;	//名前

	std::vector<int> Handle;				//ハンドル

	std::vector<int> Width;					//幅
	std::vector<int> Height;				//高さ

	std::vector<int>::iterator Handle_itr;	//ハンドルのイテレータ
	std::vector<int>::iterator Width_itr;	//幅のイテレータ
	std::vector<int>::iterator Height_itr;	//高さのイテレータ

	bool IsLoad;			//読み込めたか？

public:
	IMAGE(const char *,const char *);	//コンストラクタ
	virtual ~IMAGE();					//デストラクタ

	std::string GetFileName(void);	//名前を取得

	int GetWidth(int);				//幅を取得
	int GetHeight(int);			//高さを取得

	bool GetIsLoad(void);			//読み込めた？

	void Draw(int,int,int);				//画像を描画
};

