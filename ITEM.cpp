//ITEM.cpp
//アイテムクラス

//##################### ヘッダファイル読み込み ######################
#include "ITEM.hpp"

//##################### クラス定義 ###########################

//コンストラクタ
ITEM::ITEM()
{
	return;
}

//デストラクタ
ITEM::~ITEM()
{

	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Code.swap(v);			//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<int> v2;		//空のvectorを作成する
	this->Possession.swap(v2);	//空と中身を入れ替える


	//vectorのメモリ解放を行う
	std::vector<int> v3;			//空のvectorを作成する
	this->Recovery.swap(v3);		//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<bool> v4;			//空のvectorを作成する
	this->IsDraw.swap(v4);			//空と中身を入れ替える

	return;
}

//所持数増加
void ITEM::IncreasePossession(int kind)
{
	this->Possession[kind]++;	//所持数を増やす
	this->Chenge_flg = true;	//変更あり
	return;
}

//所持数減少
void ITEM::DecreasePossession(int kind)
{
	this->Possession[kind]--;			//所持数を減らす
	if (this->Possession[kind] <= 0)	//所持数が0以下になったら
	{
		this->IsDraw[kind] = false;		//描画してはいけない
		this->Possession[kind] = 0;		//0個より少なくしない
	}

	this->Chenge_flg = true;			//変更あり
	return;
}

//回復量設定
void ITEM::SetRecovery(int recovery)
{
	this->Recovery.push_back(recovery);
	return;
}

//追加したか設定
void ITEM::SetChengeFlg(bool add_flg)
{
	this->Chenge_flg = add_flg;
	return;
}

//アイテムコード取得
int ITEM::GetCode(int kind)
{
	return this->Code[kind];
}

//所持数取得
int ITEM::GetPossession(int code)
{
	return this->Possession[code];
}

//回復量取得
int ITEM::GetRecovery(int code)
{
	return this->Recovery[code];
}

//要素数を取得
int ITEM::GetSize(void)
{
	return this->Code.size();
}

//追加したか取得
bool ITEM::GetChengeFlg(void)
{
	return this->Chenge_flg;
}

//所持数取得
std::vector<int> ITEM::GetPossession(void)
{
	return this->Possession;
}

//描画してよいか取得
bool ITEM::GetIsDraw(int kind)
{
	return this->IsDraw[kind];
}

//アイテムを追加
void ITEM::AddItem(int code,int recovery)
{

	//指定されたコードが既に登録されているか判定
	for (int i = 0; i < this->Code.size(); ++i)	//コード番号の数分繰り返す
	{
		if (this->Code[i] == code)	//追加されたコードがすでに登録されている場合
		{
			this->Possession[i]++;			//所持数を増加
			this->IsDraw[i] = true;			//描画してよい
			this->Chenge_flg = true;		//装備変更フラグ
			return;							//追加処理終了
		}
	}

	//コードが登録されていなかった場合
	this->Code.push_back(code);			//コード追加
	this->Possession.push_back(1);		//所持数追加
	this->Recovery.push_back(recovery);	//回復量追加
	this->IsDraw.push_back(true);		//描画してよい
	this->Chenge_flg = true;			//変更あり

	return;

}

//セーブデータを読み込み
void ITEM::LoadData(int code, int possession)
{
	this->Code.push_back(code);					//コード追加
	this->Possession.push_back(possession);		//所持数追加

	if (possession == 0)	//所持数が0だったら
	{
		this->IsDraw.push_back(false);	//描画してはいけない
	}
	else					//0じゃなければ
	{
		this->IsDraw.push_back(true);	//描画してよい
	}

	this->Chenge_flg = true;	//変更あり

}
