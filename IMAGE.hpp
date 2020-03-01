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
#define MY_IMG_DIR_BATTLE	R"(.\MY_IMG\BATTLE)"			//戦闘画面の背景画像

#define MY_ING_NAME_TITLE	R"(\Title_Logo.png)"			//タイトル画像の名前
#define MY_IMG_NAME_PLAYER	R"(\yh032.png)"					//主人公の画像の名前

//背景
#define MY_IMG_NAME_BACK_TITLE	R"(\title_back.jpg)"		//タイトルの背景画像の名前
#define MY_IMG_NAME_BACK_END R"(\end_back.jpg)"				//エンドの背景画像の名前

//戦闘画面背景
#define IMG_NAME_BT_SOUGEN	R"(\battle_sougen.jpg)"			//戦闘画面（草原）の背景画像の名前
#define IMG_NAME_BT_FOREST	R"(\battle_forest.jpg)"			//戦闘画面（森）の背景画像の名前
#define IMG_NAME_BT_OCEAN	R"(\battle_ocean.jpg)"			//戦闘画面（海）の背景画像の名前
#define IMG_NAME_BT_AUTUMN	R"(\battle_autumn.jpg)"			//戦闘画面（秋）の背景画像の名前
#define IMG_NAME_BT_BOSS	R"(\battle_boss.jpg)"			//戦闘画面（ボス）の背景画像の名前
#define IMG_NAME_BT_SPRING	R"(\battle_spring.jpg)"			//戦闘画面（春）の背景画像の名前
#define IMG_NAME_BT_WINTER	R"(\battle_winter.jpg)"			//戦闘画面（冬）の背景画像の名前
#define IMG_NAME_BT_REMAINS	R"(\battle_remains.jpg)"		//戦闘画面（遺跡）の背景画像の名前
#define IMG_NAME_BT_CASTLE	R"(\battle_castle.jpg)"			//戦闘画面（城）の背景画像の名前

#define SETUMEI_NAME			R"(\setumei_dumy.jpg)"		  //説明画像の名前

//########## マクロ定義：エラーメッセージ##########
#define IMAGE_ERROR_TITLE "IMAGE_ERROR"					//エラータイトル
#define IMAGE_ERROR_MSG	"画像が読み込めませんでした"	//エラーメッセージ

//########## 列挙型 ################
enum BACK_IMAGE
{
	TITLE_BACK,		//タイトル画面の背景画像
	END_BACK		//エンド画面の背景画像
};

enum BATTLE_BACK
{
	BT_BACK_SOUGEN,			//戦闘画面の背景画像（草原）
	BT_BACK_FOREST,			//戦闘画面の背景画像（森）
	BT_BACK_OCEAN,			//戦闘画面の背景画像（海）
	BT_BACK_AUTUMN,			//戦闘画面の背景画像（秋）
	BT_BACK_BOSS,			//戦闘画面の背景画像（ボス）
	BT_BACK_SPRING,			//戦闘画面の背景画像（春）
	BT_BACK_WINTER,			//戦闘画面の背景画像（冬）
	BT_BACK_REMAINS,		//戦闘画面の背景画像（遺跡）
	BT_BACK_CASTLE			//戦闘画面の背景画像（城）
};

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

	int ImageKind;			//読み込んだ画像の種類

	bool IsLoad;			//読み込めたか？

public:
	IMAGE(const char *,const char *);	//コンストラクタ
	virtual ~IMAGE();					//デストラクタ

	std::string GetFileName(void);	//名前を取得

	void SetSize(void);				//サイズをセット

	int GetWidth(int);				//幅を取得
	int GetHeight(int);				//高さを取得

	int GetWidth();					//幅を取得（引数なし）
	int GetHeight();				//高さを取得（引数なし）

	bool GetIsLoad(void);			//読み込めた？

	void Draw(int,int);				//画像を描画

	void Draw(int, int, int);		//指定された画像を描画

	bool AddImage(const char *, const char *,int);	//画像を追加

	void ChengeImage(int);				//描画する画像を変更

};

