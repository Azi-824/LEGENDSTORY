//MUSIC.hpp
//音楽用クラス

#pragma once

//##################### ヘッダファイル読み込み #######################
#include "DxLib.h"
#include <string>
#include <vector>

//##################### マクロ定義：ファイルパス、名前 ###################
#define MY_MUSIC_DIR_BGM	R"(.\MY_MUSIC\BGM)"		  //BGMのファイル名
#define MY_MUSIC_DIR_BT_SE	R"(.\MY_MUSIC\SE\battle)" //戦闘のSEのファイル名
#define MY_MUSIC_DIR_SYS_SE	R"(.\MY_MUSIC\SE\system)" //システムのSEのファイル名

#define MY_BGM_NAME_TITLE	R"(\bgm_op.mp3)"		//BGMの名前
#define MY_BGM_NAME_FIELD	R"(\field.mp3)"			//フィールドのBGMの名前
#define MY_BGM_NAME_CITY	R"(\city.mp3)"			//街のBGMの名前
#define MY_BGM_NAME_BATTLE	R"(\battle.mp3)"		//戦闘画面のBGMの名前
#define MY_BGM_NAME_END		R"(\end.mp3)"			//エンド画面のBGMの名前

#define MY_SE_NAME_LEVUP	R"(\levelup.mp3)"		//SE（レベルアップ）の名前
#define MY_SE_NAME_SLASH	R"(\slash.mp3)"			//斬るときの音の名前
#define MY_SE_NAME_THUNDER	R"(\thunder.mp3)"		//雷の音の名前
#define MY_SE_NAME_NIGERU	R"(\nigeru.mp3)"		//逃げるときの音の名前
#define MY_SE_NAME_DAMEGE	R"(\damege.wav)"		//ダメージの音の名前

#define MY_SE_NAME_CURSOR	R"(\select.mp3)"		//カーソルの移動音の名前
#define MY_SE_NAME_CANSEL	R"(\cancel.wav)"		//キャンセル音の名前
#define MY_SE_NAME_KETTEI	R"(\kettei.mp3)"		//決定の音の名前
#define MY_SE_NAME_MENU		R"(\menu.mp3)"			//メニューを開いた時の音
#define MY_SE_NAME_ENCOUNT	R"(\encount.mp3)"		//敵と遭遇した時の音
#define MY_SE_NAME_SAVE		R"(\save.wav)"			//セーブ音

//##################### マクロ定義：エラーメッセージ ######################
#define MUSIC_ERROR_TITLE "MUSIC_ERROR"					//エラータイトル
#define MUSIC_ERROR_MSG	"音が読み込めませんでした"		//エラーメッセージ

//##################### マクロ定義 ##########################
#define BGM_KIND	5	//BGMの種類
#define BT_SE_KIND	5	//バトルで使用するSEの種類
#define SYS_SE_KIND	6	//システムのSEの種類

//##################### 列挙型 #########################
enum BGM_TYPE
{
	BGM_TITLE,		//タイトル画面のBGM
	BGM_FIELD,		//フィールドのBGM
	BGM_CITY,		//街のBGM
	BGM_BATTLE,		//戦闘画面のBGM
	BGM_END			//エンド画面のBGM
};

enum BT_SE_TYPE
{
	BT_SE_LEVELUP,		//レベルアップのSE
	BT_SE_SLASH,		//斬るときの音
	BT_SE_THUNDER,		//雷の音
	BT_SE_NIGERU,		//逃げる時の音
	BT_SE_DAMEGE		//ダメージ音
};

enum SYS_SE_TYPE
{
	SYS_SE_CURSOR,		//カーソルの移動音
	SYS_SE_CANSEL,		//キャンセル音
	SYS_SE_KETTEI,		//決定音
	SYS_SE_MENU,		//メニューを開いた時の音
	SYS_SE_ENCOUNT,		//敵と遭遇した時の音
	SYS_SE_SAVE			//セーブ音
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

	std::vector<bool>IsPlayed;	//再生済みか

public:

	MUSIC(const char *, const char *,int);		//コンストラクタ

	~MUSIC();								//デストラクタ

	bool GetIsLoad();						//読み込めたかを取得する
	bool GetIsPlay(int );					//音が再生されているか取得する

	void ChengePlayType(int);				//音の再生方法を変更する

	void ChengeVolume(int,int);				//音量を変更する

	void Play(int);							//音を再生する

	void Stop();							//音を止める(全て)
	void Stop(int);							//音を止める(指定されたものだけ)

	bool Add(const char*, const char*, int);//音を追加する

	void SetIsPlayed(int,bool);				//再生済みか設定

	bool GetIsPlayed(int);					//再生済みか取得

	void Reset(void);						//再生状態リセット

};
