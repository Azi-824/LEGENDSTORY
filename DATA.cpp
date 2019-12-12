//DATA.cpp
//データクラス

//#################### ヘッダファイル読み込み #################
#include "DATA.hpp"

//#################### クラス定義 #########################

/*
コンストラクタ
//引数：const char *：ファイルのパス
//引数：const char *：名前
*/
DATA::DATA(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;


	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return;

	}

	//ifs >> this->Text;		//ファイルからメンバー変数にデータを格納
	std::string buf;
	while (!ifs.eof())			//ファイルの終端まで読み込む
	{
		std::getline(ifs, buf);	//1行読み込み
		this->Text += buf + "\n";	//読み込んだデータを格納
	}

	return;

}

//デストラクタ
DATA::~DATA()
{
	return;
}

//描画
void DATA::Draw(int x, int y)
{
	DrawFormatString(x, y, GetColor(255, 255, 255), "%s", this->Text.c_str());	//文字描画
	return;
}
