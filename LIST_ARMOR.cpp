//LIST_ARMOR.cpp
//LISTクラスからの派生
//防具一覧を管理するクラス

//################ ヘッダファイル読み込み ##################
#include "LIST_ARMOR.hpp"

//############### クラス定義 ######################

//コンストラクタ
/*
引数：const char *：読み込むデータのディレクトリ
引数：const char *：読み込むデータの名前
*/
LIST_ARMOR::LIST_ARMOR(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(LIST_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(LIST_ERROR_TTILE),
			MB_OK);

		this->SetIsLoad(false);	//読み込み失敗

		return;	//読み込み失敗

	}


	std::string buf;		//ファイル読み込み用

	//1行目を読み込んで飛ばす
	std::getline(ifs, buf);	//1行読み込み

	while (!ifs.eof())		//ファイル終端まで読み込み
	{

		std::getline(ifs, buf, ',');				//カンマまで読み込み
		this->SetCode(atoi(buf.c_str()));		//コード番号読み込み

		std::getline(ifs, buf, ',');				//カンマまで読み込み
		this->SetName(buf.c_str());					//名前読み込み

		std::getline(ifs, buf, '\n');				//改行まで読み込み
		this->Defense.push_back(atoi(buf.c_str()));	//防御力読み込み

	}

	this->SetSize();		//リストの要素数設定

	this->SetIsLoad(true);	//読み込み成功

	return;

}

//デストラクタ
LIST_ARMOR::~LIST_ARMOR()
{
	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Defense.swap(v);		//空と中身を入れ替える

}

//防御力取得
int LIST_ARMOR::GetDefense(int code)
{

	for (int i = 0; i < this->GetListSize(); ++i)	//リストのサイズ数分繰り返す
	{
		if (this->GetCode(i) == code)	//指定されたコードと一致したら
		{
			return this->Defense[i];	//防御力取得
		}
	}

}
