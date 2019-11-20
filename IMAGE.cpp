/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* IMAGE.cpp     																				　 */
/*       																						　 */

//########## ヘッダーファイル読み込み ##########
#include "IMAGE.hpp"

//########## クラスの定義 ##########

//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
IMAGE::IMAGE(const char *dir,const char *name)
{
	//メンバ変数を初期化
	this->FilePath = "";	//パス
	this->FileName = "";	//名前

	this->Handle = -1;		//ハンドル

	this->IsLoad = false;	//読み込めたか？

	//画像を読み込み
	std::string LoadfilePath;	//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle = LoadGraph(LoadfilePath.c_str());	//画像を読み込み
	
	if (this->Handle == -1)	//画像が読み込めなかったとき
	{
		std::string ErroeMsg(IMAGE_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');					//改行
		ErroeMsg += LoadfilePath;				//画像のパス

		MessageBox(
			NULL, 
			ErroeMsg.c_str(),	//char * を返す
			TEXT(IMAGE_ERROR_TITLE),
			MB_OK);

		return;
	}

	this->FilePath = LoadfilePath;		//画像のパスを設定
	this->FileName = name;				//画像の名前を設定

	GetGraphSize(
		this->Handle,	//このハンドルの画像の大きさを取得
		&this->Width,	//Widthのアドレスを渡す
		&this->Height	//Heightのアドレスを渡す
	);

	this->IsLoad = true;		//読み込めた

	return;
}

//デストラクタ
IMAGE::~IMAGE()
{
	DeleteGraph(this->Handle);		//読み込んだ画像を削除
	return;
}

//ファイルの名前を取得
std::string IMAGE::GetFileName(void)
{
	return this->FileName;
}

//幅を取得
int IMAGE::GetWidth(void)
{
	return this->Width;
}

//高さを取得
int IMAGE::GetHeight(void)
{
	return this->Height;
}

//読み込めた？
bool IMAGE::GetIsLoad(void)
{
	return this->IsLoad;
}

//画像を描画
void IMAGE::Draw(int X,int Y)
{
	DrawGraph(X, Y, this->Handle, TRUE);


	return;
}

