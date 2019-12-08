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
#define MY_ANIME_DIR_PLAYER		R"(.\MY_ANIME\walk\)"			//プレイヤーの画像ファイルの場所
#define MY_ANIME_DIR_ATKEFECT	R"(.\MY_ANIME\atack\)"			//攻撃エフェクトの画像ファイルの場所
#define MY_ANIME_DIR_MAGIC		R"(.\MY_ANIME\magic\)"			//魔法エフェクトの画像ファイルの場所

#define MY_ANIME_NAME_PLAYER	R"(player_walk.png)"			//プレイヤーの画像の名前
#define MY_ANIME_NAME_ATKEFECT	R"(atack.png)"					//攻撃エフェクトの画像の名前
#define MY_ANIME_NAME_MAGIC		R"(magic.png)"					//魔法エフェクトの画像の名前
#define MY_ANIME_NAME_MAGIC2	R"(magic2.png)"					//魔法エフェクト2の画像の名前

#define PLAYER_WIDTH	45	//分割する幅の大きさ
#define PLAYER_HEIGHT	45	//分割する高さの大きさ
#define ATK_WIDTH		120	//分割する幅の大きさ
#define ATK_HEIGHT		120	//分割する高さの大きさ
#define MAGIC_WIDTH		640	//分割する幅の大きさ
#define MAGIC_HEIGHT	480	//分割する高さの大きさ

#define PLAYER_YOKO_CNT	3
#define PLAYER_TATE_CNT	4
#define ATK_YOKO_CNT	9
#define ATK_TATE_CNT	1
#define MAGIC_YOKO_CNT	1
#define MAGIC_TATE_CNT	12
#define MAGIC2_YOKO_CNT	5
#define MAGIC2_TATE_CNT	5

#define PLAYER_ALL_CNT	PLAYER_YOKO_CNT * PLAYER_TATE_CNT
#define ATK_ALL_CNT	ATK_YOKO_CNT * ATK_TATE_CNT
#define MAGIC_ALL_CNT MAGIC_YOKO_CNT * MAGIC_TATE_CNT
#define MAGIC2_ALL_CNT	MAGIC2_YOKO_CNT * MAGIC2_TATE_CNT

#define PLAYER_ANI_SPEED 1.0
#define ATK_SPEED		 0.02
#define MAGICN_SPEED	 0.05

//########## マクロ定義：エラーメッセージ##########
#define ANIMATION_ERROR_TTILE	"ANIMATION_ERROR"						//エラータイトル
#define ANIMATION_ERROR_MSG		"アニメーションが読み込めませんでした"	//エラーメッセージ

//########## 列挙型 ############
enum DIST {
	FLONT=0,	//前向き
	LEFT=3,		//左向き
	RIGHT=6,	//右向き
	BACK=9		//後ろ向き
};

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
	int ChangeCntNow;			//チェンジカウント
	int ChangeCntMax;			//チェンジカウント最大値

	double EffectNextChangeSpeed;	//アニメーションを変更する速さ(秒)
	int EffectChangeCnt;			//アニメーションするフレームのカウント
	int EffectChangeMaxCnt;			//アニメーションするフレームの最大値

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

	void ResetIsAnime(void);		//アニメーションがストップしたかをリセット

	void Draw(int,int,int,bool);	//画像を描画

	void DrawEffect(int, int);		//エフェクトを描画
};

