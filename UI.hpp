//UI.hpp
//ゲーム内で使用するUIを管理するクラス

#pragma once

//######################### ヘッダファイル読み込み #############################
#include "DxLib.h"
#include "PLAYER.hpp"
#include "SELECT.hpp"
#include "LIST_ITEM.hpp"
#include "LIST_ARMOR.hpp"
#include "LIST_WEAPON.hpp"

//######################### マクロ定義 #####################################
#define UI_DIR	R"(.\MY_IMG\Ui\)"	//UI画像のフォルダ名

#define UI_WINDOW_NAME	R"(window.png)"		//ウィンドウの名前

//ステータスウィンドウ関係
#define STA_WIN_X		0			//ステータスウィンドウ描画開始X位置
#define STA_WIN_Y		540			//ステータスウィンドウ描画開始Y位置
#define STA_WIN_WIDTH	350			//ステータスウィンドウの横幅
#define STA_WIN_HEIGHT	100			//ステータスウィンドウの高さ
#define STA_TXT_X		10			//ステータスの文字の描画開始X位置
#define STA_TXT_Y		540			//ステータスの文字の描画開始Y位置
#define STA_SPACE		20			//ステータス文字の間隔
#define STA_HP_BAR_X	90			//HPバーの描画開始X位置
#define	STA_HP_BAR_Y	590			//HPバーの描画開始Y位置
#define	STA_HP_BAR_WIDTH 100		//HPバーの描画幅
#define STA_HP_BAR_HEIGHT 15		//HPバーの描画高さ
#define STA_MP_BAR_X	90			//MPバーの描画開始X位置
#define	STA_MP_BAR_Y	615			//MPバーの描画開始Y位置
#define	STA_MP_BAR_WIDTH 100		//MPバーの描画幅
#define STA_MP_BAR_HEIGHT 15		//MPバーの描画高さ

//メニュー一覧
#define MENU_LIST_WINDOW_RELATIVE_X	100	//メニューウィンドウ(一覧)の相対位置(X)
#define MENU_LIST_WINDOW_RELATIVE_Y	100	//メニューウィンドウ(一覧)の相対位置(Y)
#define MENU_LIST_WINDOW_WIDTH	150		//メニューウィンド(一覧)の幅
#define MENU_LIST_WINDOW_HEIGHT	180		//メニューウィンド(一覧)の高さ
#define MENU_WINDOW_CHENGE_POSX	100		//メニューウィンドウ(一覧)を左右どちらに表示するか判断するときのX位置
#define MENU_WINDOW_CHENGE_POSY	85		//メニューウィンドウ(一覧)を左右どちらに表示するか判断するときのY位置

//メニュー毎
#define MENU_WINDOW_X	200				//選んだメニュー毎のウィンドウの描画開始X位置
#define MENU_WINDOW_Y	50				//選んだメニュー毎のウィンドウの描画開始Y位置
#define MENU_TEXT_X		220				//選んだメニュー毎の内容の描画開始X位置
#define MENU_TEXT_Y		85				//選んだメニュー毎の内容の描画開始Y位置
#define MENU_TEXT_TOP_Y	55				//選んだメニュー毎の先頭要素の描画開始Y位置
#define MENU_WINDOW_WIDTH	600			//選んだメニュー毎のウィンドウの横幅
#define MENU_WINDOW_HEIGHT	500			//選んだメニュー毎のウィンドウの高さ

#define MENU_ITEM_NAME_SPACE	200		//アイテム画面の名前と所持数の表示間隔
#define MENU_EQUIP_NAME_SPACE	200		//装備画面の名前と所持数の表示間隔

//バトルコマンド関係
#define CMD_WIN_X		350			//バトルコマンドのウィンドウの描画開始X位置
#define	CMD_WIN_Y		540			//バトルコマンドのウィンドウの描画開始Y位置
#define CMD_WIN_WIDTH	120			//バトルコマンドのウィンドウの横幅
#define CMD_WIN_HEIGHT	100			//バトルコマンドのウィンドウの高さ
#define CMD_TXT_X		370			//バトルコマンドの文字の描画開始X位置
#define CMD_TXT_Y		540			//バトルコマンドの文字の描画開始Y位置

//一覧関係
#define BT_LIST_WIN_X		470		//魔法一覧のウィンドウの描画開始X位置
#define BT_LIST_WIN_Y		540		//魔法一覧のウィンドウの描画開始Y位置
#define BT_LIST_WIN_WIDTH	100		//魔法一覧のウィンドウの横幅
#define BT_LIST_WIN_HEIGHT	100		//魔法一覧のウィンドウの高さ
#define BT_LIST_TXT_X		485		//魔法一覧の文字の描画開始X位置
#define BT_LIST_TXT_Y		540		//魔法一覧の文字の描画開始Y位置

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

enum MENU_COMMAND
{
	MENU_STATUS,		//ステータス
	MENU_ITEM,			//アイテム
	MENU_EQUIPMENT,		//装備
	MENU_SETUMEI,		//操作説明
	MENU_SAVE			//セーブ
};

enum MENU_EQUIP_DIR
{
	MENU_EQUIP_SELECT_KIND,		//武器か防具かを選択する段階
	MENU_EQUIP_SELECT_EQUIP,	//装備する武器、もしくは防具を選択する段階
	MENU_EQUIP_SELECT_DECISION	//装備するか選択する段階（はい、か、いいえ）
};

//######################### クラス定義 #####################################
class UI
{
private:

	IMAGE *UiImage;					//uiの画像

	ANIMATION *UiAnime;				//uiのアニメーション

	bool IsDrawUIAnime;				//UIのアニメーションを描画してよいか

	int Menu_Equip_dir;				//装備画面の選択の段階を管理する変数

public:

	SELECT *MenuSelect;			//メニューの選択肢
	SELECT *BattleCommand;		//バトルコマンドの選択肢
	SELECT *ItemSelect;			//アイテムの選択肢
	SELECT *WeaponSelect;		//武器の選択肢
	SELECT *ArmorSelect;		//防具の選択肢
	SELECT *Yes_No;				//はい、いいえの選択肢
	SELECT *EquipSelect;		//武器か防具かの選択肢

	UI();					//コンストラクタ

	~UI();					//デストラクタ

	//メニューウィンドウ関連
	void DrawMenu(int ,int);			//メニューウィンドウ描画
	void ResetMenu();					//メニュー関係のメンバーをリセット
	int GetMenuEquipDir(void);			//メニューの装備画面の選択肢の段階を取得

	//バトルコマンド関連
	void DrawCommand();					//バトルコマンド描画
	void BattleInit();					//バトルコマンドで使用する要素を初期化する

	//ステータスウィンドウ関連
	void DrawStateWindow(PLAYER *);				//ステータスウィンドウ描画
	void DrawWindow(int, int, int, int);				//ウィンドウを描画する
	void DrawWindow(int,int,int,int,unsigned int);		//ウィンドウを描画する(色指定)
	void DrawWindowFrame(int, int, int, int);			//ウィンドウの枠を描画する

	//UI画像関係
	void DrawUiImage(int, int,int);				//UIの画像を描画する
	bool AddUiImage(const char *, const char *,int);//ui画像を追加する
	int GetUiImageWidth(int);					//ui画像の横幅取得
	int GetUiImageHeight(int);					//ui画像の高さ取得

	//アニメーション関係
	bool AddUiAnime(const char *, const char *, int, int, int, int, int, double, bool);	//アニメーション画像を追加する
	void DrawUiAnime(int,int);			//アニメーション画像を描画する
	void SetIsDrawUIAnime(bool);		//アニメーション画像を描画してよいか設定
	bool GetIsDrawUIAnime(void);		//アニメーション画像を描画してよいか取得

	void SetSize(void);					//画像サイズを設定する

	//アイテム関係
	void DrawItemSelect(int, int, std::vector<int>);	//アイテムの選択肢を描画する
	bool MenuSelectItem(KEYDOWN *,MUSIC *);				//メニューのアイテム画面の処理


	//装備関係
	void DrawMenuEquip(int, int, std::vector<int>, std::vector<int>);	//メニュー画面の装備描画処理
	int MenuSelectEquip(KEYDOWN *, MUSIC *);							//メニューの装備画面の処理

	//選択肢関係
	void SelectUpdate(ITEM *, LIST_ITEM *);		//選択肢の内容を更新する処理(アイテム)
	void SelectUpdate(WEAPON *, LIST_WEAPON *);	//武器
	void SelectUpdate(ARMOR *, LIST_ARMOR *);	//防具

};
