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

	ChangeFont("GD-DOTFONT-DQ-OTF", DX_CHARSET_DEFAULT);			//指定されたフォントに変更
	this->SetSize(32);												//フォントサイズ32を初期値で設定

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

//文字描画
//引数1:描画するX位置
//引数2:描画するY位置
//引数3:描画する文字列
void FONT::Draw(int x,int y,const char *str)
{

	DrawString(x, y, str, GetColor(255, 255, 255));		//文字描画

	return;
}

//文字列の横幅を取得
//引数1:横幅を取得したい文字列
int FONT::GetWidth(const char *str)
{
	int Strlen = 0;		//文字列の長さ取得用
	
	//文字列の長さを取得
	Strlen = strlen(str);

	this->Width = GetDrawStringWidth(str, Strlen);		//横幅取得

	return this->Width;	//横幅を返す

}

