//EFFECT.hpp
//エフェクトクラス

#pragma once

//###################### ヘッダファイル読み込み #########################
#include "DxLib.h"
#include <vector>
#include <string>
#include "FPS.hpp"
#include "main.hpp"

//###################### マクロ定義：ファイルパス、名前 ######################
#define MY_ANIME_DIR_ATKEFECT	R"(.\MY_ANIME\atack\)"			//攻撃エフェクトの画像ファイルの場所
#define MY_ANIME_DIR_MAGIC		R"(.\MY_ANIME\magic\)"			//魔法エフェクトの画像ファイルの場所

#define MY_ANIME_NAME_ATKEFECT	R"(atack.png)"					//攻撃エフェクトの画像の名前
#define MY_ANIME_NAME_MAGIC		R"(magic.png)"					//魔法エフェクトの画像の名前
#define MY_ANIME_NAME_MAGIC2	R"(magic2.png)"					//魔法エフェクト2の画像の名前

//###################### マクロ定義：エラーメッセージ ########################
#define EFFECT_ERROR_TTILE	"EFFECT_ERROR"						//エラータイトル
#define EFFECT_ERROR_MSG	"エフェクトが読み込めませんでした"	//エラーメッセージ

//###################### マクロ定義 #################################
#define ATK_WIDTH		120	//分割する幅の大きさ
#define ATK_HEIGHT		120	//分割する高さの大きさ
#define MAGIC_WIDTH		880	//分割する幅の大きさ
#define MAGIC_HEIGHT	640	//分割する高さの大きさ

#define ATK_YOKO_CNT	9
#define ATK_TATE_CNT	1
#define MAGIC_YOKO_CNT	1
#define MAGIC_TATE_CNT	12
#define MAGIC2_YOKO_CNT	5
#define MAGIC2_TATE_CNT	5

#define ATK_ALL_CNT	ATK_YOKO_CNT * ATK_TATE_CNT
#define MAGIC_ALL_CNT MAGIC_YOKO_CNT * MAGIC_TATE_CNT
#define MAGIC2_ALL_CNT	MAGIC2_YOKO_CNT * MAGIC2_TATE_CNT

#define ATK_SPEED		 0.02
#define MAGIC_SPEED		 0.02

#define ATK_DRAW_X		375
#define ATK_DRAW_Y		290

#define MAGIC_EFFECT_KIND		2			//魔法エフェクトの種類
#define ATACK_EFFECT_KIND		1			//攻撃エフェクトの種類

//###################### 列挙型 ##########################
enum MAGIC_EFFECT_TYPE
{
	MAGIC_1,			//魔法１
	MAGIC_2				//魔法２
};

enum ATACK_EFFECT_TYPE
{
	NOMAL_ATACK		//通常攻撃
};

//###################### クラス定義 ################################
class EFFECT
{
private:

	std::vector<std::vector<int>> Handle;							//ハンドル
	std::vector<int>::iterator Handle_itr;				//ハンドルのイテレータ
	
	std::vector<int> Width;				//幅
	std::vector<int> Height;			//高さ

	double NextChangeSpeed;			//アニメーションを変更する速さ(秒)
	int ChangeCnt;					//アニメーションするフレームのカウント
	int ChangeMaxCnt;				//アニメーションするフレームの最大値

	std::vector<bool> IsAnimeLoop;			//アニメーションはループする？
	std::vector<bool> IsAnimeStop;			//アニメーションはストップしたか？

	bool IsDrawEnd;				//描画終了したか

	bool IsLoad;				//読み込めたか？

public:

	EFFECT(const char *, const char *, int, int, int, int, int, double, bool);	//コンストラクタ	

	~EFFECT();					//デストラクタ

	int GetWidth(int);				//幅を取得
	int GetHeight(int);			//高さを取得

	bool GetIsLoad(void);			//読み込めた？

	bool GetIsAnimeStop(int);		//アニメーションはストップしたかを取得

	bool GetIsDrawEnd();		//描画終了したか取得

	void SetIsDrawEnd(bool);	//描画終了したか設定

	void ResetIsAnime(int);		//アニメーションがストップしたかをリセット

	void Draw(int, int,int);			//描画

	bool Add(const char *, const char *, int, int, int, int, int, double, bool, int);	//エフェクト追加

};
