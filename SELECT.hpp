//SELECT.hpp
//選択肢を管理するクラス

#pragma once

//###################### ヘッダファイル読み込み ##############################
#include "DxLib.h"
#include "KEYDOWN.hpp"
#include "MUSIC.hpp"
#include "IMAGE.hpp"
#include <vector>
#include <string>

//###################### マクロ定義 ###########################
#define SELECT_DIR	R"(.\MY_IMG\Select\)"	//UI画像のフォルダ名

#define	SELECT_TRIANGLENAME		  R"(triangle1.png)"	//横向き三角の名前
#define	SELECT_TRIANGLE_MINI_NAME R"(triangle2.png)"	//横向き三角（ミニ）の名前

#define IMAGE_SPACE	10			//ui画像（横向き三角）の位置調整用数値
#define IMAGE_MINI_SPACE 5		//ミニサイズ版

#define TRIANGLE_MINI_SIZE	14	//横向き三角（ミニ）のサイズ

#define SELECT_SIDE_SPACE	300	//選択肢を横向きに並べたときの間隔

//##################### 列挙型 #############################
enum SELECT_IMAGE_TYPE
{
	SELECT_TRIANGLE,		//横向き三角の画像
	SELECT_TRIANGLE_MINI	//横向き三角（ミニ）の画像
};

//###################### クラス定義 ###########################
class SELECT
{
private:

	std::vector<std::string> Str;				//文字列格納用
	std::vector<std::string>::iterator Str_itr;	//イテレータ

	IMAGE *image_ui;	//UI画像

	bool IsKeyOpe;		//キー操作可能か
	bool SelectFlg;		//選択したか
	bool IsDrawImage;	//UI画像を描画してよいか
	bool Side_Mode;		//横向き描画か
	bool BackFlg;		//戻るを選んだか

	bool DefIsKeyOpe;		//キー操作可能か、デフォルト値
	bool DefIsDrawImage;	//UI画像を描画してよいか、デフォルト値


public:

	//コンストラクタ
	/*
	引数：Args：描画文字列
	*/
	template<typename...Args>
	SELECT(Args...args)		
	{

		this->image_ui = new IMAGE(SELECT_DIR, SELECT_TRIANGLENAME);	//UI画像生成
		this->image_ui->AddImage(SELECT_DIR, SELECT_TRIANGLE_MINI_NAME, 1);	//UI画像追加

		this->Str = { args... };			//展開
		this->Str_itr = this->Str.begin();	//先頭要素

		this->IsKeyOpe = true;				//キー操作可能
		this->SelectFlg = false;			//選択されていない
		this->IsDrawImage = true;			//UI画像描画してよい
		this->Side_Mode = false;			//縦向きに選択肢を並べる
		this->BackFlg = false;				//戻る選択はされていない

		this->DefIsKeyOpe = true;		//デフォルトはキー操作可能
		this->DefIsDrawImage = true;	//デフォルトはUI表示

		return;
	}
	
	/*
	選択肢の内容を設定せずにオブジェクトの生成のみを行う
	*/
	SELECT();			//コンストラクタのオーバーロード

	~SELECT();		//デストラクタ

	void SelectOperation(KEYDOWN *,MUSIC *);	//選択肢のキー操作

	std::vector<std::string>::iterator GetNowSelect();		//現在選択中の要素を取得
	int GetSelectNum(void);					//選択した要素の要素番号を取得する

	void SelectClear();						//選択肢の内容を消去する
	void NowSelectReset();					//現在選択中の要素を最初に戻す

	void Draw(int, int,int ,unsigned int color = GetColor(255, 255, 255),int side_space= SELECT_SIDE_SPACE);			//選択肢の内容を描画する
	void DrawCenter(int, int,int , unsigned int color = GetColor(255, 255, 255));	//選択肢の内容を中央に描画する

	void SetSize(void);						//画像サイズ設定
	void Add(const char *);					//選択肢の内容を追加

	void SetIsKeyOpe(bool);					//キー操作可能か設定する
	bool GetIsKeyOpe(void);					//キー操作可能か取得する

	void SetSelectFlg(bool);				//選択したか設定
	bool GetSelectFlg(void);				//選択したか取得

	void SetIsDrawImage(bool);				//UI画像を描画してよいか設定
	bool GetIsDrawImage(void);				//UI画像を描画してよいか取得

	void SetSideMode(bool);					//選択肢を横向きに並べるか設定
	bool GetSideMode(void);					//選択肢を横向きに並べるか取得

	void ChengeDefault(bool, bool);			//デフォルトの状態を設定
	void Default();							//デフォルトの状態に戻す

	void SetBackFlg(bool);					//戻るを選択したか設定
	bool GetBackFlg(void);					//戻るを選択したか取得


	//選択肢の内容を変更する
	//引数：Args：描画文字列
	template<typename...Args>
	void ChengeSelect(Args...args)			
	{
		this->SelectClear();	//現在の選択肢をクリア
		this->Str = { args... };	//展開
		this->Str_itr = this->Str.begin();	//先頭要素
		return;
	}


};
