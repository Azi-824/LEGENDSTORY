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

	this->ChoiseMenu = -1;					//メニュー画面での選択内容を初期化

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

		//コマンド決定処理
		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーが押された瞬間
		{
			auto itr = this->menuwindow->GetChoiseMenu();	//メニュー画面の選択内容を取得
			this->SetChoiseMenu(itr);						//選択内容を設定
		}

	}
	return;
}

//メニューウィンドウ描画
void UI::DrawMenu()
{
	this->menuwindow->Draw();	//メニュー描画
	return;
}

//メニューで選んだ内容を設定
void UI::SetChoiseMenu(std::vector<std::string>::iterator itr)
{

	if (*itr == "ステータス")		//ステータスを選んだ場合
	{
		this->ChoiseMenu = (int)MENU_STATUS;	//ステータス
		return;
	}
	else if (*itr == "アイテム")	//アイテムを選んだ場合
	{
		this->ChoiseMenu = (int)MENU_ITEM;		//アイテム
		return;
	}
	else if (*itr == "装備")			//装備を選んだ場合
	{
		this->ChoiseMenu = (int)MENU_SOUBI;		//装備
		return;
	}
	else if (*itr == "セーブ")			//セーブを選んだ場合
	{
		this->ChoiseMenu = (int)MENU_SAVE;		//セーブ
		return;
	}
		
	return;
}

//メニュー画面での選択内容を取得
int UI::GetChoiseMenu()
{
	return this->ChoiseMenu;
}

//メニュー関係のメンバーをリセット
void UI::ResetMenu()
{
	this->ChoiseMenu = -1;		//選択内容をリセット
	this->menuwindow->Reset();	//選択内容リセット
}

//選んだ内容ごとのメニューを描画
void UI::DrawChoiseMenu()
{
	this->menuwindow->DrawChoise(this->ChoiseMenu);
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
void UI::SetStateWindow(int level ,int hp,int mp)
{
	std::vector<int> set;
	set.push_back(level);	//レベル取得
	set.push_back(hp);//HP取得
	set.push_back(mp);//MP取得
	this->StateWindow->SetText(set);	//Level、HP、MPを設定
	return;
}

//ステータスウィンドウ描画
void UI::DrawStateWindow()
{
	this->StateWindow->Draw();	//描画
}

//ウィンドウを描画する
void UI::DrawWindow()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率80％に設定

	DrawBox(0, 380, 0 + 800,380 + 100, GetColor(0, 0, 0), TRUE);	//塗りつぶしありで四角形を描画

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//描画モードを通常に戻す

}
