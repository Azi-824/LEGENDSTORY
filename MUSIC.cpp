//MUSIC.cpp
//音楽用クラス

//################### ヘッダファイル読み込み ####################
#include "MUSIC.hpp"

//################## クラス定義 ###########################

//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
MUSIC::MUSIC(const char *dir, const char *name)
{
	//メンバ変数を初期化
	this->FilePath = "";	//パス
	this->FileName = "";	//名前

	this->Handle = -1;		//ハンドル

	this->IsLoad = false;	//読み込めたか？

	//音を読み込み
	std::string LoadfilePath;	//音のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle = LoadSoundMem(LoadfilePath.c_str());	//音の読み込み

	if (this->Handle == -1)	//音が読み込めなかったとき
	{
		std::string ErroeMsg(MUSIC_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');					//改行
		ErroeMsg += LoadfilePath;				//音のパス

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * を返す
			TEXT(MUSIC_ERROR_TITLE),
			MB_OK);

		return;
	}

	this->FilePath = LoadfilePath;		//音のパスを設定
	this->FileName = name;				//音の名前を設定

	this->PlayType = DX_PLAYTYPE_LOOP;	//最初は再生方法をループ再生にする

	this->IsLoad = true;				//読み込み成功

	return;

}

//デストラクタ
MUSIC::~MUSIC()
{
	DeleteMusicMem(this->Handle);	//音のハンドルの削除
	return;
}

//読み込めたかどうかを取得
bool MUSIC::GetIsLoad()
{
	return this->IsLoad;
}

//音が再生されているか取得
//戻り値：再生中：true　再生中じゃない：false
bool MUSIC::GetIsPlay()
{
	if (CheckSoundMem(this->Handle) == 1)	//再生中なら
	{
		this->IsPlay = true;	//再生中
	}
	else									//再生中じゃなければ
	{
		this->IsPlay = false;	//再生中じゃない
	}
	return this->IsPlay;
}

//再生方法を変更する
void MUSIC::ChengePlayType(int type)
{
	this->PlayType = type;	
	return;
}

//音量を変更する
void MUSIC::ChengeVolume(int volume)
{
	ChangeVolumeSoundMem(volume, this->Handle);
	return;
}

//音を再生する
void MUSIC::Play()
{
	PlaySoundMem(this->Handle, this->PlayType);	//音の再生
	return;
}
