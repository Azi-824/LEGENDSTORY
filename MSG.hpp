//MSG.hpp
//メッセージクラス

#pragma once

//################ ヘッダファイル読み込み ##################
#include "DxLib.h"
#include "main.hpp"
#include "UI.hpp"
#include "PLAYER.hpp"
#include "ENEMY.hpp"

//################ マクロ定義 ####################
#define MSG_DRAW_X 0		//メッセージの描画位置(X)
#define MSG_DRAW_Y 400		//メッセージの描画位置(Y)

//################ クラス定義 ####################
class MESSAGE
{
private:

	int X;		//X描画位置
	int Y;		//Y描画位置

public:

	MESSAGE();		//コンストラクタ

	~MESSAGE();		//デストラクタ

	void DrawBattleMsg(int,int,int,PLAYER *,ENEMY *);		//戦闘画面でのメッセージ描画

	void DrawDamage(int,int);			//ダメージ描画

	void DrawName(const char *);		//名前描画

};
