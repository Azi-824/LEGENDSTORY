//FONT.cpp
//フォントクラス

//############### ヘッダファイル読み込み ####################
#include "FONT.hpp"

//############### クラスの定義 #####################

//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
FONT::FONT(const char *dir,const char *name)
{
	//メンバー変数初期化

	this->FileName = "";		//パス
	this->FilePath = "";		//名前
	this->Handle = -1;			//ハンドル

								
	//フォントを読み込み
	std::string LoadFilePath;		//フォントのパスを作成

	LoadFilePath += dir;
	LoadFilePath += name;

	if (AddFontResourceEx(LoadFilePath.c_str(), FR_PRIVATE, NULL) < 0)		//読み込み失敗
	{
		std::string ErroeMsg(FONT_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');					//改行
		ErroeMsg += LoadFilePath;				//フォントのパス

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * を返す
			TEXT(FONT_ERROR_TITLE),
			MB_OK);

		return;

	}

	this->FilePath = LoadFilePath;
	this->FileName = name;

	this->Isload = true;		//読み込めた

	return;

}

//デストラクタ	
FONT::~FONT()
{
	std::string LoadfilePath;

	LoadfilePath += this->FilePath;

	if (RemoveFontResourceEx(LoadfilePath.c_str(), FR_PRIVATE, NULL) == 0)	//失敗時
	{

		MessageBox(NULL, "remove failure", "", MB_OK);				//エラーメッセージ

	}
}

//読み込めたか
bool FONT::GetIsLoad()
{
	return this->Isload;
}

//フォントサイズ設定
void FONT::SetSize(int size)
{

	SetFontSize(size);

	return;
}

