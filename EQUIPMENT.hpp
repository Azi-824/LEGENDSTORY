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

	std::vector<int> CodeNum;				//コード番号
	std::vector<int> PossessionNum;			//装備の所持数
	std::vector<bool> EquipFlg;				//装備しているかどうか
	std::vector<bool> IsDraw;				//描画してよいか
	int Size;								//要素数
	bool Chenge_flg;						//装備を変更したかどうか

public:

	EQUIPMENT();							//コンストラクタ
	~EQUIPMENT();							//デストラクタ

	//セッタ
	//void SetPossessionNum(int,int);			//装備所持数設定
	void IncreasePossession(int);			//所持数増加
	void DecreasePossession(int);			//所持数減少
	void SetEquipFlg(int, bool);			//装備しているかどうか設定
	void SetSize();							//要素数設定
	void SetChengeFlg(bool);				//装備を変更したか設定

	//ゲッタ
	int GetCodeNum(int);					//コード番号取得
	int GetPossessionNum(int);				//装備所持数取得
	std::vector<int> GetPossessionNum();	//装備所持数取得（すべて）
	bool GetEquipFlg(int);					//装備しているか取得
	int GetSize();							//要素数取得
	bool GetChengeFlg();					//装備を変更したか取得

	void Add(int);							//装備情報追加
	//void AddPossession(int);				//装備所持数増加処理

	bool GetIsDraw(int);					//描画してよいか取得

};
