//LIST.cpp
//魔法やスキルの一覧を管理するクラス

//################### ヘッダファイル読み込み ###########################
#include "LIST.hpp"

//################### クラス定義 ############################

//コンストラクタ
/*
引数：const char *：リストのファイル名
引数：const char *：リストの名前
*/
LIST::LIST(const char *dir, const char *name)
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

		this->IsLoad = false;	//読み込み失敗

		return;	//読み込み失敗

	}


	std::string buf;
	//1行目を読み込んで飛ばす
	std::getline(ifs, buf);	//1行読み込み

	while (!ifs.eof())		//ファイル終端まで読み込み
	{
		std::getline(ifs, buf, ',');		//カンマまで読み込み
		this->Name.push_back(buf.c_str());		//技名読み込み
		
		std::getline(ifs, buf,'\n');		//改行まで読み込み
		this->Cost.push_back(atoi(buf.c_str()));//消費MP読み込み

	}

	this->IsLoad = true;	//読み込み成功

	return;

}

//デストラクタ
LIST::~LIST()
{
	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Cost.swap(v);			//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<std::string> v2;			//空のvectorを作成する
	this->Name.swap(v2);					//空と中身を入れ替える

	return;
}

//名前取得
const char * LIST::GetName(int kind)
{
	return this->Name[kind].c_str();
}

//消費MP取得
int LIST::GetCost(int kind)
{
	return this->Cost[kind];
}

//読み込めたか取得
bool LIST::GetIsLoad(void)
{
	return this->IsLoad;
}
