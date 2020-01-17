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
#define BT_MSG_DRAW_X 15	//戦闘画面のメッセージの描画位置(X)
#define BT_MSG_DRAW_Y 370	//戦闘画面のメッセージの描画位置(Y)

#define RESULT_MSG_KIND	3	//リザルト画面のメッセージの種類

//################ 列挙型 ########################
enum MSG_STEP
{
	WIN_MSG,		//戦闘に勝利したメッセージ
	EXP_MSG,		//経験値のメッセージ
	LEVELUP_MSG		//レベルアップメッセージ
};

//################ クラス定義 ####################
class MESSAGE
{
private:

	std::vector<std::string> Msg;		//メッセージ格納用
	std::vector<std::string>::iterator Msg_itr;	//Msgのイテレータ

	int X;		//X描画位置
	int Y;		//Y描画位置

	int ResultMsgStep;		//リザルトメッセージの表示段階

	bool IsResultMsgEnd;	//リザルト画面のメッセージ表示が終了したか
	bool IsDrawMsg;			//メッセージ描画中か

public:

	MESSAGE();		//コンストラクタ

	~MESSAGE();		//デストラクタ

	void DrawBattleMsg(int,int,int,PLAYER *,ENEMY *,bool);		//戦闘画面でのメッセージ描画

	void DrawDamage(int,int);			//ダメージ描画

	void DrawName(const char *);		//名前描画

	void SetIsResultMsgEnd(bool);		//リザルトメッセージの表示が終了したか設定
	void ResetResultMsg();				//リザルトメッセージ関係のメンバーをリセット
	void SetIsDrawMsg(bool);			//メッセージ描画中か設定

	bool GetIsResultMsgEnd(void);		//リザルトメッセージの表示が終了したか取得
	int GetDrawMsgKind(void);			//どのメッセージを描画している状態か取得
	bool GetIsDrawMsg(void);			//メッセージ描画中か取得

	void SetMsg(const char *);			//文字列を設定する
	void NextMsg(void);					//次のメッセージへ移動する
	void BackMsg(void);					//前のメッセージへ移動する

	void DrawMsg(int, int,unsigned int);				//メッセージ描画

};
