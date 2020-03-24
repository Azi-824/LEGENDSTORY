//NPC.hpp
//NPCを管理するクラス

#pragma once

//################### ヘッダファイル読み込み ####################
#include "DxLib.h"
#include "IMAGE.hpp"
//#include "MSG.hpp"
#include <vector>
#include <string>
#include <fstream>

//#################### マクロ定義 ######################
#define NPC_DATA_DIR			R"(.\MY_DATA\NPC\)"		//NPCデータのファイル名
#define NPC_IMAGE_DIR			R"(.\MY_IMG\NPC\)"		//NPCの画像データのファイル名

#define NPC_DATA_NAME			R"(NPC_Data.csv)"		//NPCデータの名前
#define NPC_IMAGE_DATA_NAME		R"(NPC1.png)"			//NPCの画像の名前

//############## マクロ定義：エラーメッセージ ###################
#define NPC_DATA_ERROR_TTILE	"NPC_DATA_ERROR"						//エラータイトル
#define NPC_DATA_ERROR_MSG		"NPCデータが読み込めませんでした"		//エラーメッセージ


//#################### クラス定義 ######################
class NPC
{
private :

	IMAGE *Image;							//NPCの画像
	//MESSAGE *Text;							//NPCの会話テキスト

	std::vector<std::string> Name;			//NPCの名前

	std::vector<int>	DrawMapKind;		//NPCを描画するマップの種類
	std::vector<int>	DrawMap_Num;		//NPCの描画マップ番号
	std::vector<int>	Draw_X;				//NPCの描画X位置
	std::vector<int>	Draw_Y;				//NPCの描画Y位置

	bool ImageIsLoad;						//画像を読み込めたか

public:	

	NPC(const char *, const char *);		//コンストラクタ
	~NPC();									//デストラクタ

	bool GetImageIsLoad();					//画像を読み込めたか取得

	void DrawNPC(int,int);					//NPCを描画する
	//void DrawNPCText(int);					//指定されたNPCの会話テキストを描画する

	bool Load(const char *, const char *);	//NPCデータを読み込む

};
