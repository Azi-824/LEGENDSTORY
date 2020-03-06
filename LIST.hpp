//LIST.hpp
//スキルや魔法の一覧を管理するクラス

#pragma once

//################ ヘッダファイル読み込み ######################
#include "DxLib.h"
#include <vector>
#include <string>
#include <fstream>

//################ マクロ定義 #########################
#define LIST_DIR		R"(.\MY_DATA\List\)"			//リストのディレクトリ名

//############## マクロ定義：エラーメッセージ ###################
#define LIST_ERROR_TTILE	"LIST_ERROR"						//エラータイトル
#define LIST_ERROR_MSG		"リストが読み込めませんでした"		//エラーメッセージ

//################ クラス定義 #########################
class LIST
{
private:

	std::vector <std::string> Name;		//名前

	std::vector<int> CodeNum;			//コード番号

	int Size;							//リストの要素数

	bool IsLoad;						//読み込めたか

public:	

	LIST();								//コンストラクタ
	~LIST();							//デストラクタ

	//セッタ
	void SetName(std::string);			//名前設定
	void SetCodeNum(int);				//コード番号設定
	void SetSize();						//リストの要素数設定
	void SetIsLoad(bool);				//読み込めたか設定

	//ゲッタ
	const char * GetName(int);			//技名取得
	bool GetIsLoad(void);				//読み込めたか
	int GetListSize(void);				//リストの要素数を取得
	int GetCodeNum(int);				//コード番号取得

};
