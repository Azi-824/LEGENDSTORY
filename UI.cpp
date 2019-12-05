//UI.cpp
//ゲーム内で使用するUIを管理するクラス

//####################### ヘッダファイル読み込み ########################
#include "UI.hpp"

//####################### クラス定義 ################################

//コンストラクタ
UI::UI()
{
	this->menuwindow = new MENU();			//メニューウィンドウ作成

	this->StateWindow = new STATEWINDOW();	//ステータスウィンドウ作成

	this->BattleCommand = new COMMAND();	//バトルコマンド作成

	this->BattleCommadType = -1;			//選択したバトルコマンドの種類を初期化

	return;
}

//デストラクタ
UI::~UI()
{
	delete this->menuwindow;	//menuwindow破棄
	delete this->BattleCommand;	//BattleCommand破棄
	delete this->StateWindow;	//StateWindow破棄

	return;
}

//メニューウィンドウのキーボード操作
void UI::MenuOperation(KEYDOWN *keydown,bool ismenu)
{
	if (ismenu)	//メニュー描画中
	{
		if (keydown->IsKeyDownOne(KEY_INPUT_W))	//Wキーを押された瞬間
		{
			this->menuwindow->Back();	//前の要素へ
		}
		else if (keydown->IsKeyDownOne(KEY_INPUT_S))	//Sキーを押された瞬間
		{
			this->menuwindow->Next();	//次の要素へ
		}
		this->DrawMenu();	//メニューウィンドウ描画
	}
	return;
}

//メニューウィンドウ描画
void UI::DrawMenu()
{
	this->menuwindow->Draw();	//メニュー描画
	return;
}

//バトルコマンドで使用する要素を初期化する
void UI::BattleInit()
{
	this->BattleCommand->Init();	//選択要素の初期化
	this->BattleCommadType = -1;	//選択したコマンド内容リセット
}

//戦闘画面で選んだコマンドを設定する
void UI::SetBattleFlg(std::vector<std::string>::iterator choise_itr)
{
	if (*choise_itr == "こうげき")			//攻撃を選んだ場合
	{
		this->BattleCommadType = ATACK;	//攻撃
		return;
	}
	else if (*choise_itr == "ぼうぎょ")		//防御を選んだ場合
	{
		this->BattleCommadType = DEFENSE;	//防御
		return;
	}
	else if (*choise_itr == "まほう")			//魔法を選んだ場合
	{
		this->BattleCommadType = MAGIC;	//魔法
		return;
	}
	else if (*choise_itr == "アイテム")		//アイテムを選んだ場合
	{
		this->BattleCommadType = ITEM;	//アイテム
		return;
	}
	else if (*choise_itr == "にげる")			//逃げるを選んだ場合
	{
		this->BattleCommadType = ESCAPE;	//逃げる
		return;
	}
	return;
}

//選択したコマンドの種類を取得
int UI::GetChoiseCommamd()
{
	return this->BattleCommadType;
}

//戦闘画面の操作
void UI::BattleOperation(KEYDOWN *keydown)
{
	//コマンド選択処理
	if (keydown->IsKeyDownOne(KEY_INPUT_D))			//Dキーを押された瞬間
	{
		this->BattleCommand->Next();	//次の要素へ
	}
	else if (keydown->IsKeyDownOne(KEY_INPUT_A))	//Aキーを押された瞬間
	{
		this->BattleCommand->Back();	//前の要素へ
	}

	//コマンド決定処理
	if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーが押された瞬間
	{
		auto itr = this->BattleCommand->GetCommand();	//選択しているコマンドを取得
		this->SetBattleFlg(itr);	//バトルフラグ設定
	}

	return;
}

//バトルコマンド描画
void UI::DrawCommand()
{
	this->BattleCommand->Draw();	//描画
	return;
}


//ステータスウィンドウの設定
void UI::SetStateWindow(PLAYER *player)
{
	std::vector<int> set;
	set.push_back(player->GetHP());//HP取得
	set.push_back(player->GetMP());//MP取得
	this->StateWindow->SetText(set);	//HP.MPを設定
	return;
}

//ステータスウィンドウ描画
void UI::DrawStateWindow()
{
	this->StateWindow->Draw();	//描画
}
