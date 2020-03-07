//EQUIPMENT.hpp
//装備関係の元になるクラス

#pragma once

//##################### ヘッダファイル読み込み #######################
#include "DxLib.h"
#include <vector>
#include <string>

//##################### マクロ定義 #########################

//##################### クラス定義 #########################
class EQUIPMENT
{
private:

	//std::vector<std::string> Name;			//装備名
	std::vector<int> CodeNum;				//コード番号
	std::vector<int> PossessionNum;			//装備の所持数
	std::vector<bool> EquipFlg;				//装備しているかどうか
	int Size;								//要素数
	//std::vector<std::string> Description;	//説明文

public:

	EQUIPMENT();							//コンストラクタ
	~EQUIPMENT();							//デストラクタ

	//セッタ
	//void SetName(int,const char *);			//装備名設定
	//void SetCodeNum(int,int);				//コード番号設定
	void SetPossessionNum(int,int);			//装備所持数設定
	void SetEquipFlg(int, bool);			//装備しているかどうか設定
	void SetSize();							//要素数設定
	//void SetDescription(int, const char *);	//説明文設定

	//ゲッタ
	//const char * GetName(int);				//装備名取得
	int GetCodeNum(int);					//コード番号取得
	int GetPossessionNum(int);				//装備所持数取得
	bool GetEquipFlg(int);					//装備しているか取得
	int GetSize();							//要素数取得
	//const char * GetDescription(int);		//説明文取得

	void Add(int);							//装備情報追加
	void AddPossession(int);				//装備所持数増加処理

};
