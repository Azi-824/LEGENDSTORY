//UI.hpp
//ゲーム内で使用するUIを管理するクラス

#pragma once

//######################### ヘッダファイル読み込み #############################
#include "DxLib.h"
#include "MENU.hpp"
#include "PLAYER.hpp"
#include "SELECT.hpp"

//######################### マクロ定義 #####################################
#define UI_DIR	R"(.\MY_IMG\Ui\)"	//UI画像のフォルダ名

#define UI_WINDOW_NAME	R"(window.png)"		//ウィンドウの名前

#define STR_SPACE		100			//文字列間の空白

//ステータスウィンドウ関係
#define STA_WIN_X		0			//ステータスウィンドウ描画開始X位置
#define STA_WIN_Y		540			//ステータスウィンドウ描画開始Y位置
#define STA_WIN_WIDTH	350			//ステータスウィンドウの横幅
#define STA_WIN_HEIGHT	100			//ステータスウィンドウの高さ
#define STA_TXT_X		10			//ステータスの文字の描画開始X位置
#define STA_TXT_Y		540			//ステータスの文字の描画開始Y位置
#define STA_SPACE		20			//ステータス文字の間隔

//バトルコマンド関係
#define CMD_WIN_X		350			//バトルコマンドのウィンドウの描画開始X位置
#define	CMD_WIN_Y		540			//バトルコマンドのウィンドウの描画開始Y位置
#define CMD_WIN_WIDTH	120			//バトルコマンドのウィンドウの横幅
#define CMD_WIN_HEIGHT	100			//バトルコマンドのウィンドウの高さ
#define CMD_TXT_X		370			//バトルコマンドの文字の描画開始X位置
#define CMD_TXT_Y		540			//バトルコマンドの文字の描画開始Y位置

//魔法一覧関係
#define MGC_WIN_X		470			//魔法一覧のウィンドウの描画開始X位置
#define MGC_WIN_Y		540			//魔法一覧のウィンドウの描画開始Y位置
#define MGC_WIN_WIDTH	100			//魔法一覧のウィンドウの横幅
#define MGC_WIN_HEIGHT	100			//魔法一覧のウィンドウの高さ
#define MGC_TXT_X		485			//魔法一覧の文字の描画開始X位置
#define MGC_TXT_Y		540			//魔法一覧の文字の描画開始Y位置

//ウィンドウ関係
#define BT_WINDOW_X		0			//バトル画面のウィンドウの描画開始X位置
#define BT_WINDOW_Y		390			//バトル画面のウィンドウの描画開始Y位置

//テキストポーズ関係
#define BT_TXT_POSE_Y	510			//バトル画面のテキストポーズの描画Y位置

#define DEFAULT_TEXT_Y	490			//デフォルトのテキスト描画位置（Y座標）
#define TXT_Y_3			450			//選択肢が3つの時のテキスト描画位置（Y座標）

//######################### 列挙型 #################################
enum UI_IMAGE_TYPE
{
	UI_WINDOW			//ウィンドウ
};

enum UI_SELECT_TYPE
{
	UI_SELECT_MENU,			//メニューの選択肢
	UI_SELECT_BATTLE_CMD	//バトルコマンドの選択肢
};

//######################### クラス定義 #####################################
class UI
{
private:

	MENU *menuwindow;				//メニューウィンドウ

	IMAGE *UiImage;					//uiの画像

	ANIMATION *UiAnime;				//uiのアニメーション

	SELECT *MenuSelect;				//メニューの選択肢
	SELECT *BattleCommand;			//バトルコマンドの選択肢

	int BattleCommadType;			//選択したバトルコマンドの種類

	int ChoiseMenu;					//メニュー画面で選択した内容

	std::vector<std::string> Str;	//文字列格納用
	std::vector<std::string>::iterator Str_itr;	//イテレータ

	bool IsDrawUIAnime;				//UIのアニメーションを描画してよいか

public:

	UI();					//コンストラクタ

	~UI();					//デストラクタ

	//メニューウィンドウ関連
	void DrawMenu(int ,int);				//メニューウィンドウ描画
	void SetChoiseMenu(std::vector<std::string>::iterator);	//メニューで選んだ内容を設定する
	int GetChoiseMenu();				//メニュー画面での選択内容を取得
	void ResetMenu();					//メニュー関係のメンバーをリセット
	bool GetIsChoise(void);				//選択されているか取得

	//バトルコマンド関連
	void SetBattleFlg();				//戦闘画面で選んだコマンドのフラグを設定する
	int GetChoiseCommamd();				//選択したコマンドの種類を取得
	void DrawCommand();					//バトルコマンド描画
	void BattleInit();					//バトルコマンドで使用する要素を初期化する

	//ステータスウィンドウ関連
	void DrawStateWindow(PLAYER *);				//ステータスウィンドウ描画
	void DrawWindow(int, int, int, int);				//ウィンドウを描画する
	void DrawWindow(int,int,int,int,unsigned int);		//ウィンドウを描画する(色指定)

	//UI画像関係
	void DrawUiImage(int, int,int);				//UIの画像を描画する
	bool AddUiImage(const char *, const char *,int);//ui画像を追加する
	int GetUiImageWidth(int);					//ui画像の横幅取得
	int GetUiImageHeight(int);					//ui画像の高さ取得

	//選択肢関係
	bool SelectOperation(KEYDOWN *, MUSIC *, int);			//指定された選択肢のキー操作を行う
	std::vector<std::string>::iterator GetNowSelect(int);	//指定された選択肢の現在選択している要素を取得する
	void SelectClear(int);									//指定された選択肢の内容をクリアする
	void NowSelectReset(int);								//指定された選択肢の現在選択している内容を、最初の要素に戻す

	//アニメーション関係
	bool AddUiAnime(const char *, const char *, int, int, int, int, int, double, bool);	//アニメーション画像を追加する
	void DrawUiAnime(int,int);			//アニメーション画像を描画する
	void SetIsDrawUIAnime(bool);		//アニメーション画像を描画してよいか設定
	bool GetIsDrawUIAnime(void);		//アニメーション画像を描画してよいか取得

};
