//UI.hpp
//ゲーム内で使用するUIを管理するクラス

#pragma once

//######################### ヘッダファイル読み込み #############################
#include "DxLib.h"
#include "MENU.hpp"
#include "PLAYER.hpp"
//
//######################### マクロ定義 #####################################
#define UI_DIR	R"(.\MY_IMG\Ui\)"	//UI画像のフォルダ名

#define	UI_TRIANGLENAME		  R"(triangle1.png)"	//横向き三角の名前
#define	UI_TRIANGLE_MINI_NAME R"(triangle2.png)"	//横向き三角（ミニ）の名前
#define UI_WINDOW_NAME		  R"(window.png)"		//ウィンドウの名前

#define UI_IMAGE_SPACE	10			//ui画像（横向き三角）の位置調整用数値
#define UI_IMAGE_MINI_SPACE 5		//ミニサイズ版
#define STR_SPACE		100			//文字列間の空白

//ステータスウィンドウ関係
#define STA_WIN_X		0			//ステータスウィンドウ描画開始X位置
#define STA_WIN_Y		500			//ステータスウィンドウ描画開始Y位置
#define STA_WIN_WIDTH	190			//ステータスウィンドウの横幅
#define STA_WIN_HEIGHT	100			//ステータスウィンドウの高さ
#define STA_TXT_X		10			//ステータスの文字の描画開始X位置
#define STA_TXT_Y		500			//ステータスの文字の描画開始Y位置
#define STA_SPACE		20			//ステータス文字の間隔

//バトルコマンド関係
#define CMD_WIN_X		190			//バトルコマンドのウィンドウの描画開始X位置
#define	CMD_WIN_Y		500			//バトルコマンドのウィンドウの描画開始Y位置
#define CMD_WIN_WIDTH	120			//バトルコマンドのウィンドウの横幅
#define CMD_WIN_HEIGHT	100			//バトルコマンドのウィンドウの高さ
#define CMD_TXT_X		210			//バトルコマンドの文字の描画開始X位置
#define CMD_TXT_Y		500			//バトルコマンドの文字の描画開始Y位置

//ウィンドウ関係
#define BT_WINDOW_X		0			//バトル画面のウィンドウの描画開始X位置
#define BT_WINDOW_Y		350			//バトル画面のウィンドウの描画開始Y位置

//テキストポーズ関係
#define BT_TXT_POSE_Y	470			//バトル画面のテキストポーズの描画Y位置

#define DEFAULT_TEXT_Y	450			//デフォルトのテキスト描画位置（Y座標）

//######################### 列挙型 #################################
enum UI_IMAGE_TYPE
{
	UI_TRIANGLE,		//横向き三角の画像
	UI_TRIANGLE_MINI,	//横向き三角（ミニ）の画像
	UI_WINDOW			//ウィンドウ
};

//######################### クラス定義 #####################################
class UI
{
private:

	MENU *menuwindow;				//メニューウィンドウ

	IMAGE *UiImage;					//uiの画像

	ANIMATION *UiAnime;				//uiのアニメーション

	int BattleCommadType;			//選択したバトルコマンドの種類

	int ChoiseMenu;					//メニュー画面で選択した内容

	std::vector<std::string> Str;	//文字列格納用
	std::vector<std::string>::iterator Str_itr;	//イテレータ

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
	void ChoiseOperation(KEYDOWN *);			//選択肢のキー操作を行う
	std::vector<std::string>::iterator GetNowChoise();	//現在選択している要素を取得する
	void ChoiseClear();							//選択肢の内容をクリアする

	//アニメーション関係
	bool AddUiAnime(const char *, const char *, int, int, int, int, int, double, bool);	//アニメーション画像を追加する
	void DrawUiAnime(int,int);			//アニメーション画像を描画する

	//選択肢を描画
	/*
	引数：int：x位置
	引数：int：y位置
	引数：int：描画するUI画像の種類
	引数：bool：真ん中に描画するか
	引数：unsignd int：描画色
	引数：Args：描画文字列
	*/
	template<typename...Args>
	void ChoiseDraw(int x,int y,int kind ,bool center,unsigned int color, Args...args)
	{
		
		int Size = sizeof...(args);	//要素数取得

		std::vector<std::string> work = { args... };		//展開
		std::vector<std::string>::iterator work_itr = work.begin();	//先頭要素

		if (this->Str.empty())	//展開した内容を格納していなければ
		{
			this->Str = work;	//展開した内容を格納
			this->Str_itr = this->Str.begin();	//先頭要素
		}

		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 幅、高さ取得処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
		int Width = 0;
		if (center)			//真ん中に描画するときは
		{
			int Strlen = 0;		//文字列の長さ取得用
			std::string MaxStr;	//最も長い文字列

			MaxStr = work[0].c_str();	//最も長い文字列に最初の文字列をセット

			for (int i = 0; i < (int)work.size(); i++)
			{
				if (MaxStr < work[i].c_str())	//現在の最大文字列よりも大きければ
				{
					MaxStr = work[i].c_str();	//最大文字列を更新
				}
			}

			//文字列の長さを取得
			Strlen = strlen(MaxStr.c_str());

			Width = GetDrawStringWidth(MaxStr.c_str(), Strlen);	//横幅取得

			x -= (Width / 2);	//文字の幅の半分を引いて、真ん中に描画する
		}

		int Height = GetFontSize();	//高さ取得

		int ui_width = this->UiImage->GetWidth(kind);	//ui画像の横幅取得
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 幅、高さ取得処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


		//描画処理
		for (int i = 0; i < Size; ++i)		//要素数の分ループ
		{
			if (*this->Str_itr == work[i].c_str())		//選択している内容だったら
			{
				if (kind == (int)UI_TRIANGLE)	//通常サイズの場合
				{
					this->DrawUiImage(x - ui_width, y + i * Height + UI_IMAGE_SPACE, kind);	//ui画像描画
				}
				else							//ミニサイズの場合
				{
					this->DrawUiImage(x - ui_width, y + i * Height + UI_IMAGE_MINI_SPACE, kind);	//ui画像描画
				}
				DrawFormatString(x, y + i * Height, color, "%s", work[i].c_str());	//文字描画
			}
			else								//それ以外だったら
			{
				DrawFormatString(x, y + i * Height, color, "%s", work[i].c_str());	//文字描画
			}
		}

		//vectorのメモリ解放を行う
		std::vector<std::string> v;			//空のvectorを作成する
		work.swap(v);						//空と中身を入れ替える

		return;

	}

};
