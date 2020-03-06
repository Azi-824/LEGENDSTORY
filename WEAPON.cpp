//WEAPON.cpp
//武器クラス

//################## ヘッダファイル読み込み ####################
#include "WEAPON.hpp"

//################## クラス定義 ########################

//コンストラクタ
WEAPON::WEAPON()
{
	return;
}

//デストラクタ
WEAPON::~WEAPON()
{
	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Atk.swap(v);			//空と中身を入れ替える

	return;
}

//攻撃力を設定
void WEAPON::SetAtk(int atk)
{
	this->Atk.push_back(atk);	//攻撃力追加
	return;
}

//攻撃力取得
int WEAPON::GetAtk(int kind)
{
	return this->Atk[kind];		//攻撃力取得
}
