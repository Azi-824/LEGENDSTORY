//COMMAND.hpp
//バトルコマンドクラス

#pragma once

//##################### ヘッダファイル読み込み ####################
#include "DxLib.h"
#include <vector>
#include <string>

//#################### マクロ定義 ########################
#define COMMAND_SPACE		170		//コマンド間の間隔
#define COMMAND_KIND		5		//コマンドの種類

//#################### クラス定義 ########################
class COMMAND
{
private:

	std::vector<std::string> Command;					//コマンドウィンドウの文字列
	std::vector<std::string>::iterator Command_itr;		//文字列のハンドル

	int X;			//コマンドウィンドウの枠のX座標
	int Y;			//コマンドウィンドウの枠のY座標

	int Width;		//コマンドウィンドウの枠の横幅
	int Height;		//コマンドウィンドウの枠の高さ

	int StrHeight;	//文字列の高さ
	int StrWidth;	//文字列の幅

	bool IsDrawDamege;	//ダメージを表示してよいか


public:

	COMMAND();			//コンストラクタ

	~COMMAND();			//デストラクタ

	void Draw();		//描画
	void EnemyDamegeDraw(const char *, int);	//ダメージ量の描画
	void MyDamegeDraw(const char *,int);		//味方のダメージ量の描画

	int GetWidth();		//横幅取得
	std::vector < std::string>::iterator GetCommand();	//選択しているコマンドを取得

	void Next();		//次の要素へ

	void Back();		//前の要素へ

	void Init();		//初期化する

};
