//UI.cpp
//ゲーム内で使用するUIを管理するクラス

//####################### ヘッダファイル読み込み ########################
#include "UI.hpp"

//####################### クラス定義 ################################

//コンストラクタ
UI::UI()
{

	this->UiImage = new IMAGE(UI_DIR, UI_NAME);	//uiの画像作成

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
	delete this->UiImage;			//Ui破棄

	//vectorのメモリ解放を行う
	std::vector<std::string> v;			//空のvectorを作成する
	this->Str.swap(v);						//空と中身を入れ替える


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

		//コマンド決定処理
		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーが押された瞬間
		{
			auto itr = this->menuwindow->GetChoiseMenu();	//メニュー画面の選択内容を取得
			this->SetChoiseMenu(itr);						//選択内容を設定
			this->menuwindow->SetIsChoise(true);
		}

	}
	return;
}

//メニューウィンドウ描画
void UI::DrawMenu(int x,int y)
{
	//プレイヤーの位置によって描画位置を変える
	if (x <= MENU_WINDOW_CHENGE_POSX && y >= MENU_WINDOW_CHENGE_POSY)	//左上にいるときは
	{
		//プレイヤーの右上にメニューウィンドウを表示
		this->DrawWindow(x + MENU_WINDOW_RELATIVE_X, y + (-MENU_WINDOW_RELATIVE_Y), MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画
		//this->menuwindow->Draw(x + MENU_WINDOW_RELATIVE_X, y + (-MENU_WINDOW_RELATIVE_Y));	//メニュー描画
		this->ChoiseDraw(x + MENU_WINDOW_RELATIVE_X, y + (-MENU_WINDOW_RELATIVE_Y),false ,GetColor(255,255,255),"ステータス", "アイテム", "装備", "セーブ");

	}
	else if (x <= MENU_WINDOW_CHENGE_POSX && y <= MENU_WINDOW_CHENGE_POSY)	//左側にいるときは
	{
		//プレイヤーの右下にメニューウィンドウを表示
		this->DrawWindow(x + MENU_WINDOW_RELATIVE_X, y + MENU_WINDOW_RELATIVE_Y, MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画
		this->menuwindow->Draw(x + MENU_WINDOW_RELATIVE_X, y + MENU_WINDOW_RELATIVE_Y);	//メニュー描画
	}
	else if (x >= MENU_WINDOW_CHENGE_POSX && y <= MENU_WINDOW_CHENGE_POSY)	//上側にいるときは
	{
		//プレイヤーの左下にメニューウィンドウを表示
		this->DrawWindow(x + (-MENU_WINDOW_RELATIVE_X), y + MENU_WINDOW_RELATIVE_Y, MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画
		this->menuwindow->Draw(x + (-MENU_WINDOW_RELATIVE_X), y + MENU_WINDOW_RELATIVE_Y);	//メニュー描画
	}
	else			//それ以外の時は
	{
		//プレイヤーの左上にメニューウィンドウを表示
		this->DrawWindow(x + (-MENU_WINDOW_RELATIVE_X), y + (-MENU_WINDOW_RELATIVE_Y), MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画
		this->menuwindow->Draw(x + (-MENU_WINDOW_RELATIVE_X), y + (-MENU_WINDOW_RELATIVE_Y));	//メニュー描画
	}

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
void UI::DrawChoiseMenu(PLAYER *player,ITEM *item[])
{
	this->DrawWindow(0, 0, GAME_WIDTH, GAME_HEIGHT);
	this->menuwindow->DrawChoise(this->ChoiseMenu,player,item);
	return;
}

//選択されているか取得
bool UI::GetIsChoise(void)
{
	return this->menuwindow->GetIsChoise();
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
		this->BattleCommadType = COMMANDE_ATACK;	//攻撃
		return;
	}
	else if (*choise_itr == "ぼうぎょ")		//防御を選んだ場合
	{
		this->BattleCommadType = COMMANDE_DEFENSE;	//防御
		return;
	}
	else if (*choise_itr == "まほう")			//魔法を選んだ場合
	{
		this->BattleCommadType = COMMANDE_MAGIC;	//魔法
		return;
	}
	else if (*choise_itr == "アイテム")		//アイテムを選んだ場合
	{
		this->BattleCommadType = COMMANDE_ITEM;	//アイテム
		return;
	}
	else if (*choise_itr == "にげる")			//逃げるを選んだ場合
	{
		this->BattleCommadType = COMMANDE_ESCAPE;	//逃げる
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
void UI::DrawWindow(int x,int y,int width,int height)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率80％に設定

	DrawBox(x, y, x + width, y + height, GetColor(0, 0, 0), TRUE);	//塗りつぶしありで四角形を描画

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//描画モードを通常に戻す

}

//ui画像を描画する
void UI::DrawUiImage(int x, int y,int type)
{
	this->UiImage->Draw(x, y,type);
	return;
}

//ui画像を追加する
bool UI::AddUiImage(const char *dir, const char *name,int type)
{
	if (this->UiImage->AddImage(dir, name,type))	//読み込み成功したら
	{
		return true;	//読み込み成功
	}
	else
	{
		return false;	//読み込み失敗
	}
	
}

//ui画像の幅を取得
int UI::GetUiImageWidth(int type)
{
	return this->UiImage->GetWidth(type);
}

//ui画像の高さ取得
int UI::GetUiImageHeight(int type)
{
	return this->UiImage->GetHeight(type);
}

//選択肢のキー操作を行う
void UI::ChoiseOperation(KEYDOWN *keydown)
{
	if (keydown->IsKeyDownOne(KEY_INPUT_W))		//Wキーを押されたら
	{
		if (this->Str_itr != this->Str.begin())	//最初の要素を選択していなければ
		{
			--this->Str_itr;		//前の要素へ
		}
	}
	else if (keydown->IsKeyDownOne(KEY_INPUT_S))	//Sキーを押されたら
	{
		if (this->Str_itr != this->Str.end() - 1)	//最後の要素を選択していなければ
		{
			++this->Str_itr;		//次の要素へ
		}
	}
	return;
}

//現在選択している要素を取得する
std::vector<std::string>::iterator UI::GetNowChoise()
{
	return this->Str_itr;
}

//選択肢の内容をクリアする
void UI::ChoiseClear(void)
{
	this->Str.clear();
	this->Str_itr = this->Str.begin();
	return;
}
