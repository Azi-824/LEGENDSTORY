//MUSIC.hpp
//音楽用クラス

#pragma once

//##################### ヘッダファイル読み込み #######################
#include "DxLib.h"
#include <string>
#include <vector>

//##################### マクロ定義：ファイルパス、名前 ###################
#define MY_MUSIC_DIR_BGM	R"(.\MY_MUSIC\BGM)"		//BGMのファイル名
#define MY_MUSIC_DIR_SE		R"(.\MY_MUSIC\SE)"		//SEのファイル名

#define MY_MUSIC_NAME_BGM	R"(\bgm_op.mp3)"		//BGMの名前
#define MY_SE_NAME_LEVUP	R"(\LevelUp.mp3)"		//SE（レベルアップ）の名前

//##################### マクロ定義：エラーメッセージ ######################
#define MUSIC_ERROR_TITLE "MUSIC_ERROR"					//エラータイトル
#define MUSIC_ERROR_MSG	"音が読み込めませんでした"		//エラーメッセージ

//##################### マクロ定義 ##########################
#define BGM_KIND	1	//BGMの種類
#define SE_KIND		1	//SEの種類

//##################### 列挙型 #########################
enum BGM_TYPE
{
	TITLE_BGM		//タイトル画面のBGM
};

enum SE_TYPE
{
	LEVELUP_SE		//レベルアップのSE
};

//##################### クラス定義 ############################
class MUSIC
{
private:

	std::string FilePath;		//ファイルパス
	std::string FileName;		//名前

	std::vector<int> Handle;	//ハンドル
	int PlayType;				//音の再生方法

	bool IsLoad;				//読み込めたか
	std::vector<bool> IsPlay;	//再生中か

public:

	MUSIC(const char *, const char *,int);		//コンストラクタ

	~MUSIC();								//デストラクタ

	bool GetIsLoad();						//読み込めたかを取得する
	bool GetIsPlay(int );					//音が再生されているか取得する

	void ChengePlayType(int);				//音の再生方法を変更する

	void ChengeVolume(int,int);				//音量を変更する

	void Play(int);							//音を再生する

	bool Add(const char*, const char*, int);	//音を追加する

};
