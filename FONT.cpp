//FONT.cpp
//フォントクラス

//############### ヘッダファイル読み込み ####################
#include "FONT.hpp"

//############### クラスの定義 #####################

//コンストラクタ
//引　数：const char *：フォントのディレクトリ
//引　数：const char *：フォントの名前
//引　数：const char *：フォントの正式名称
FONT::FONT(const char *dir,const char *filename,const char *name)
{
	//メンバー変数初期化

	this->FileName = "";		//パス
	this->FilePath = "";		//名前
	this->Handle = -1;			//ハンドル

								
	//フォントを読み込み
	std::string LoadFilePath;		//フォントのパスを作成

	LoadFilePath += dir;
	LoadFilePath += filename;
	
	if (AddFontResourceEx(LoadFilePath.c_str(), FR_PRIVATE, NULL) <= 0)		//読み込み失敗
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


	ChangeFont(name, DX_CHARSET_DEFAULT);							//指定されたフォントに変更
	this->SetSize(DEFAULT_FONTSIZE);								//フォントサイズをデフォルトの数字に設定

	this->FilePath = LoadFilePath;
	this->FileName = filename;

	this->Isload = true;		//読み込めた

	return;

}

FONT::FONT()
{
	return;
}

//デストラクタ	
FONT::~FONT()
{

	if (RemoveFontResourceEx(this->FilePath.c_str(), FR_PRIVATE, NULL) == 0)	//失敗時
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
