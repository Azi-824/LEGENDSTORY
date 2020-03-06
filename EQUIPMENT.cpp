//EQUIPMENT.cpp
//装備関係のクラスの元になるクラス

//####################### ヘッダファイル読み込み #########################
#include "EQUIPMENT.h"

//####################### クラス定義 ##########################

//コンストラクタ
EQUIPMENT::EQUIPMENT()
{
	return;
}

//デストラクタ
EQUIPMENT::~EQUIPMENT()
{
	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->CodeNum.swap(v);		//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<int> v2;			//空のvectorを作成する
	this->PossessionNum.swap(v2);	//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<bool> v3;			//空のvectorを作成する
	this->EquipFlg.swap(v3);		//空と中身を入れ替える

	return;

}

//装備所持数設定
void EQUIPMENT::SetPossessionNum(int kind, int possesionnum)
{
	this->PossessionNum[kind] = possesionnum;	//所持数設定
	return;
}

//装備フラグ設定
void EQUIPMENT::SetEquipFlg(int kind, bool equipflg)
{
	this->EquipFlg[kind] = equipflg;	//装備フラグ設定
	return;
}

//コード番号取得
int EQUIPMENT::GetCodeNum(int kind)
{
	return this->CodeNum[kind];
}

//装備所持数取得
int EQUIPMENT::GetPossessionNum(int kind)
{
	return this->PossessionNum[kind];
}

//装備フラグ取得
bool EQUIPMENT::GetEquipFlg(int kind)
{
	return this->EquipFlg[kind];
}

//装備追加
void EQUIPMENT::Add(int codenum)
{
	this->CodeNum.push_back(codenum);		//コード番号追加
	this->PossessionNum.push_back(1);		//装備所持数を追加
	this->EquipFlg.push_back(false);		//追加した装備の装備状態を設定
	
	return;
}
