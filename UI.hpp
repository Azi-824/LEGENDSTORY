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


public:

	UI();					//コンストラクタ

	~UI();					//デストラクタ

	//メニューウィンドウ関連
	void MenuOperation(KEYDOWN *,bool);	//メニューウィンドウのキーボード操作
	void DrawMenu();				//メニューウィンドウ描画

	//バトルコマンド関連
	void SetBattleFlg(std::vector<std::string>::iterator);	//戦闘画面で選んだコマンドのフラグを設定する
	int GetChoiseCommamd();									//選択したコマンドの種類を取得
	void DrawCommand();										//バトルコマンド描画
	void BattleOperation(KEYDOWN *);						//戦闘画面の操作
	void ResetBattleMember();								//戦闘画面で使用する変数などをリセットする

	//ステータスウィンドウ関連
	void SetStateWindow(PLAYER *);	//ステータスウィンドウの設定をする
	void DrawStateWindow();			//ステータスウィンドウ描画

};
