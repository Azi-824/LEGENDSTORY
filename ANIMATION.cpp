/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* ANIMATION.cpp     																			　 */
/* アニメーションクラス 																		　 */

//########## ヘッダーファイル読み込み ##########
#include "ANIMATION.hpp"

//########## クラスの定義 ##########

//コンストラクタ
//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
//引　数：int：画像の総分割数
//引　数：int：画像の横向きの分割数
//引　数：int：画像の縦向きの分割数
//引　数：int：画像の分割された横の大きさ
//引　数：int：画像の分割された縦の大きさ
//引　数：double：次の画像に変更する速さ
//引　数：bool：アニメーションをループするかどうか
ANIMATION::ANIMATION(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	//メンバ変数を初期化
	this->FilePath = "";	//パス
	this->FileName = "";	//名前

	this->Handle.resize(SplitNumALL);			//resize：vectorの要素数を変更する
	this->Handle_itr = this->Handle.begin();	//先頭のポインタを入れる

	this->ChangeMaxCnt = (int)(changeSpeed * fps->Getvalue());	//アニメーションするフレームの最大値
	this->ChangeCnt = 0;										//アニメーションするフレームのカウント

	this->IsAnimeLoop = IsLoop;		//アニメーションはループする？
	this->IsAnimeStop = false;		//アニメーションを動かす

	this->IsLoad = false;			//読み込めたか？

	//画像を読み込み
	std::string LoadfilePath;		//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	//画像を分割して読み込み
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &this->Handle[0]);

	if (this->Handle[0] == -1)	//画像が読み込めなかったとき
	{
		std::string ErrorMsg(ANIMATION_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadfilePath;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(ANIMATION_ERROR_TTILE),
			MB_OK);

		return;
	}

	this->FilePath = LoadfilePath;		//画像のパスを設定
	this->FileName = name;				//画像の名前を設定

	GetGraphSize(
		this->Handle[0],	//このハンドルの画像の大きさを取得
		&this->Width,		//Widthのアドレスを渡す
		&this->Height		//Heightのアドレスを渡す
	);

	this->NextChangeSpeed = changeSpeed;	//画像を変える速さ

	this->IsLoad = true;		//読み込めた

	return;
}

//デストラクタ
ANIMATION::~ANIMATION()
{
	//範囲ベースの for ループ
	//vectorなどのコンテナクラスで使用できる
	//auto：型推論：コンパイラが初期値から推論して型を決めてくれる
	for (int handle : this->Handle)
	{
		DeleteGraph(handle);
	}

	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Handle.swap(v);		//空と中身を入れ替える

	return;
}

//ファイルの名前を取得
std::string ANIMATION::GetFileName(void)
{
	return this->FileName;
}

//幅を取得
int ANIMATION::GetWidth(void)
{
	return this->Width;
}

//高さを取得
int ANIMATION::GetHeight(void)
{
	return this->Height;
}

//読み込めた？
bool ANIMATION::GetIsLoad(void)
{
	return this->IsLoad;
}

//アニメーションはストップしたかを取得
bool  ANIMATION::GetIsAnimeStop(void)
{
	return this->IsAnimeStop;
}

//画像を描画
void ANIMATION::Draw(int X, int Y)
{
	if (this->IsAnimeStop == false)	//アニメーションをストップさせないなら
	{
		DrawGraph(X, Y, *this->Handle_itr, TRUE);	//イテレータ(ポインタ)を使用して描画
	}

	if (this->ChangeCnt == this->ChangeMaxCnt)	//次の画像を表示する時がきたら
	{
		//this->Handle.end()は、最後の要素の１個次のイテレータを返すので、-1している。
		if (this->Handle_itr == this->Handle.end() - 1)	//イテレータ(ポインタ)が最後の要素のときは
		{
			//アニメーションをループしないなら
			if (this->IsAnimeLoop == false)
			{
				this->IsAnimeStop = true;	//アニメーションを止める
			}

			//次回の描画に備えて、先頭の画像に戻しておく
			this->Handle_itr = this->Handle.begin();	//イテレータ(ポインタ)を要素の最初に戻す
		}
		else
		{
			this->Handle_itr++;	//次のイテレータ(ポインタ)(次の画像)に移動する
		}

		this->ChangeCnt = 0;	//カウント初期化
	}
	else
	{
		this->ChangeCnt++;	//カウントアップ
	}

	return;
}