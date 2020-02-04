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

#define MGC_LIST_NAME	R"(magic_list.csv)"				//魔法一覧のcsvデータの名前


//############## マクロ定義：エラーメッセージ ###################
#define LIST_ERROR_TTILE	"LIST_ERROR"						//エラータイトル
#define LIST_ERROR_MSG		"リストが読み込めませんでした"		//エラーメッセージ

//################ クラス定義 #########################
class LIST
{
private:

	std::vector<int> Cost;				//消費MP
	std::vector < std::string> Name;	//技名

	bool IsLoad;						//読み込めたか

public:	

	LIST(const char *,const char *);	//コンストラクタ
	
	~LIST();							//デストラクタ

	int GetCost(int);					//消費MP取得
	const char * GetName(int);			//技名取得
	bool GetIsLoad(void);				//読み込めたか


};
