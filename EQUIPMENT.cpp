//EQUIPMENT.cpp
//装備関係のクラスの元になるクラス

//####################### ヘッダファイル読み込み #########################
#include "EQUIPMENT.hpp"

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

//要素数設定
void EQUIPMENT::SetSize()
{
	this->Size = this->CodeNum.size();	//サイズ設定
	return;
}

//武器を追加したか設定
void EQUIPMENT::SetAddFlg(bool addflg)
{
	this->AddFlg = addflg;
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

//要素数取得
int EQUIPMENT::GetSize()
{
	return this->Size;
}

//装備を追加したかどうか取得
bool EQUIPMENT::GetAddFlg(void)
{
	return this->AddFlg;
}

//装備追加
void EQUIPMENT::Add(int codenum)
{
	this->CodeNum.push_back(codenum);		//コード番号追加

	//要素0にコード番号0を入れるために+1している
	if (this->PossessionNum.size() < codenum + 1)	//コード番号が要素数より少ない場合
	{
		this->PossessionNum.resize(codenum + 1);	//要素サイズを変更
		this->EquipFlg.resize(codenum + 1);			//要素サイズを変更
	}

	//要素数にコード番号を指定して登録
	this->PossessionNum[codenum] = 1;		//装備所持数を追加
	this->EquipFlg[codenum] = false;		//追加した装備の装備状態を設定

	this->Size = this->CodeNum.size();		//サイズ設定

	this->AddFlg = true;					//装備追加フラグ
	
	return;
}

//装備所持数増加処理
void EQUIPMENT::AddPossession(int kind)
{
	this->PossessionNum[kind]++;	//増加
	return;
}
