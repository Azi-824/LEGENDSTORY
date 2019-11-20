/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* ANIMATION.hpp     																			　 */
/* アニメーションクラス 																		　 */

#pragma once

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include <string>
#include <vector>

#include "FPS.hpp"

//########## マクロ定義：画像のファイルパスと名前 ##########
#define MY_ANIME_DIR_BAKU		R"(.\MY_ANIME\bakuhatsu\)"		//爆発の画像ファイルの場所

#define MY_ANIME_NAME_BAKU_1	R"(bakuhatsu_01.png)"			//爆発の画像の名前
#define BAKU_1_WIDTH	64	//分割する幅の大きさ
#define BAKU_1_HEIGHT	64	//分割する高さの大きさ

#define BAKU_1_YOKO_CNT	15
#define BAKU_1_TATE_CNT	1
#define BAKU_1_ALL_CNT	BAKU_1_YOKO_CNT * BAKU_1_TATE_CNT

#define BAKU_1_ANI_SPEED 0.1

//########## マクロ定義：エラーメッセージ##########
#define ANIMATION_ERROR_TTILE	"ANIMATION_ERROR"						//エラータイトル
#define ANIMATION_ERROR_MSG		"アニメーションが読み込めませんでした"	//エラーメッセージ

//########## クラスの定義 ##########
class ANIMATION
{
private:
	std::string FilePath;	//パス
	std::string FileName;	//名前

	std::vector<int> Handle;				//ハンドル
	std::vector<int>::iterator Handle_itr;	//ハンドルのイテレータ(ポインタ)

	int Width;					//幅
	int Height;					//高さ

	double NextChangeSpeed;		//アニメーションを変更する速さ(秒)
	int ChangeMaxCnt;			//アニメーションするフレームの最大値
	int ChangeCnt;				//アニメーションするフレームのカウント

	bool IsAnimeLoop;			//アニメーションはループする？
	bool IsAnimeStop;			//アニメーションはストップしたか？

	bool IsLoad;				//読み込めたか？
	
public:
	ANIMATION(const char *, const char *, int, int, int, int, int, double,bool);	//コンストラクタ
	virtual ~ANIMATION();	//デストラクタ

	std::string GetFileName(void);	//名前を取得

	int GetWidth(void);				//幅を取得
	int GetHeight(void);			//高さを取得

	bool GetIsLoad(void);			//読み込めた？

	bool GetIsAnimeStop(void);		//アニメーションはストップしたかを取得

	void Draw(int,int);				//画像を描画
};

