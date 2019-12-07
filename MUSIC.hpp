//MUSIC.hpp
//音楽用クラス

#pragma once

//##################### ヘッダファイル読み込み #######################
#include "DxLib.h"
#include <string>

//##################### マクロ定義：ファイルパス、名前 ###################
#define MY_MUSIC_DIR_BGM	R"(.\MY_MUSIC\BGM)"		//BGMのファイル名

#define MY_MUSIC_NAME_BGM	R"(\bgm_op.mp3)"		//BGMの名前

//##################### マクロ定義：エラーメッセージ ######################
#define MUSIC_ERROR_TITLE "MUSIC_ERROR"					//エラータイトル
#define MUSIC_ERROR_MSG	"音が読み込めませんでした"	//エラーメッセージ

//##################### クラス定義 ############################
class MUSIC
{
private:

	std::string FilePath;		//ファイルパス
	std::string FileName;		//名前

	int Handle;					//ハンドル
	int PlayType;				//音の再生方法

	bool IsLoad;				//読み込めたか
	bool IsPlay;				//再生中か

public:

	MUSIC(const char *, const char *);		//コンストラクタ

	~MUSIC();								//デストラクタ

	bool GetIsLoad();						//読み込めたかを取得する
	bool GetIsPlay();						//音が再生されているか取得する

	void ChengePlayType(int);				//音の再生方法を変更する

	void ChengeVolume(int);					//音量を変更する

	void Play();							//音を再生する

};
