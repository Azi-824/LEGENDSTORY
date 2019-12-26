//UI.hpp
//ゲーム内で使用するUIを管理するクラス

#pragma once

//######################### ヘッダファイル読み込み #############################
#include "DxLib.h"
#include "STATEWINDOW.hpp"
#include "COMMAND.hpp"
#include "PLAYER.hpp"

//######################### マクロ定義 #####################################

//######################### クラス定義 #####################################
class UI
{
private:

	MENU *menuwindow;				//メニューウィンドウ

	COMMAND *BattleCommand;			//バトルコマンド

	STATEWINDOW *StateWindow;		//ステータスウィンドウ

	int BattleCommadType;			//選択したバトルコマンドの種類

	int ChoiseMenu;					//メニュー画面で選択した内容

public:

	UI();					//コンストラクタ

	~UI();					//デストラクタ

	//メニューウィンドウ関連
	void MenuOperation(KEYDOWN *,bool);	//メニューウィンドウのキーボード操作
	void DrawMenu();				//メニューウィンドウ描画
	void SetChoiseMenu(std::vector<std::string>::iterator);	//メニューで選んだ内容を設定する
	int GetChoiseMenu();				//メニュー画面での選択内容を取得
	void ResetMenu();					//メニュー関係のメンバーをリセット
	void DrawChoiseMenu();				//選んだメニュー内容ごとの描画

	//バトルコマンド関連
	void SetBattleFlg(std::vector<std::string>::iterator);	//戦闘画面で選んだコマンドのフラグを設定する
	int GetChoiseCommamd();									//選択したコマンドの種類を取得
	void DrawCommand();										//バトルコマンド描画
	void BattleOperation(KEYDOWN *);						//戦闘画面の操作
	void BattleInit();										//バトルコマンドで使用する要素を初期化する

	//ステータスウィンドウ関連
	void SetStateWindow(int,int,int);	//ステータスウィンドウの設定をする
	void DrawStateWindow();			//ステータスウィンドウ描画

	

	void DrawWindow();				//ウィンドウを描画する

};
