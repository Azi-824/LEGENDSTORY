//UI.cpp
//ゲーム内で使用するUIを管理するクラス

//####################### ヘッダファイル読み込み ########################
#include "UI.hpp"

//####################### クラス定義 ################################

//コンストラクタ
UI::UI()
{

	this->UiImage = new IMAGE(UI_DIR, UI_WINDOW_NAME);	//uiの画像作成

	this->menuwindow = new MENU();			//メニューウィンドウ作成

	this->MenuSelect = new SELECT("ステータス", "アイテム", "装備", "操作説明", "セーブ");	//メニューの選択肢生成
	this->BattleCommand = new SELECT("こうげき", "ぼうぎょ", "まほう", "アイテム", "にげる");	//バトルコマンドの選択肢生成

	this->BattleCommadType = -1;			//選択したバトルコマンドの種類を初期化

	this->ChoiseMenu = -1;					//メニュー画面での選択内容を初期化

	this->IsDrawUIAnime = true;				//UIのアニメーションを描画してよい

	//アニメーション画像を生成（テキストポーズ）
	this->UiAnime = new ANIMATION(TXT_POSE_DIR, TXT_POSE_NAME, TXT_POSE_ALL_CNT, TXT_POSE_YOKO_CNT, TXT_POSE_TATE_CNT, TXT_POSE_WIDTH, TXT_POSE_HEIGHT, TXT_POSE_SPEED, true);

	return;
}

//デストラクタ
UI::~UI()
{
	delete this->menuwindow;	//menuwindow破棄
	delete this->UiImage;		//Ui破棄
	delete this->UiAnime;		//uianime破棄

	//vectorのメモリ解放を行う
	std::vector<std::string> v;			//空のvectorを作成する
	this->Str.swap(v);					//空と中身を入れ替える


	return;
}

//メニューウィンドウ描画
void UI::DrawMenu(int x,int y)
{
	//プレイヤーの位置によって描画位置を変える
	if (x <= MENU_WINDOW_CHENGE_POSX && y >= MENU_WINDOW_CHENGE_POSY)	//左上にいるときは
	{
		//プレイヤーの右上にメニューウィンドウを表示
		this->DrawWindow(x + MENU_WINDOW_RELATIVE_X - TRIANGLE_MINI_SIZE, y + (-MENU_WINDOW_RELATIVE_Y), MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画
		this->MenuSelect->Draw(x + MENU_WINDOW_RELATIVE_X, y + (-MENU_WINDOW_RELATIVE_Y), 1);
	}
	else if (x <= MENU_WINDOW_CHENGE_POSX && y <= MENU_WINDOW_CHENGE_POSY)	//左側にいるときは
	{
		//プレイヤーの右下にメニューウィンドウを表示
		this->DrawWindow((x + MENU_WINDOW_RELATIVE_X) - TRIANGLE_MINI_SIZE, y + MENU_WINDOW_RELATIVE_Y, MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画
		this->MenuSelect->Draw(x + MENU_WINDOW_RELATIVE_X, y + MENU_WINDOW_RELATIVE_Y, 1);
	}
	else if (x >= MENU_WINDOW_CHENGE_POSX && y <= MENU_WINDOW_CHENGE_POSY)	//上側にいるときは
	{
		//プレイヤーの左下にメニューウィンドウを表示
		this->DrawWindow(x + (-MENU_WINDOW_RELATIVE_X) - TRIANGLE_MINI_SIZE, y + MENU_WINDOW_RELATIVE_Y, MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画
		this->MenuSelect->Draw(x + (-MENU_WINDOW_RELATIVE_X), y + MENU_WINDOW_RELATIVE_Y, 1);
	}
	else			//それ以外の時は
	{
		//プレイヤーの左上にメニューウィンドウを表示
		this->DrawWindow(x + (-MENU_WINDOW_RELATIVE_X) - TRIANGLE_MINI_SIZE, y + (-MENU_WINDOW_RELATIVE_Y), MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画
		this->MenuSelect->Draw(x + (-MENU_WINDOW_RELATIVE_X), y + (-MENU_WINDOW_RELATIVE_Y), 1);
	}

	return;
}

//メニューで選んだ内容を設定
void UI::SetChoiseMenu(std::vector<std::string>::iterator itr)
{

	if (*itr == "ステータス")		//ステータスを選んだ場合
	{
		this->ChoiseMenu = (int)MENU_STATUS;	//ステータス
		//return;
	}
	else if (*itr == "アイテム")	//アイテムを選んだ場合
	{
		this->ChoiseMenu = (int)MENU_ITEM;		//アイテム
		//return;
	}
	else if (*itr == "装備")			//装備を選んだ場合
	{
		this->ChoiseMenu = (int)MENU_SOUBI;		//装備
		//return;
	}
	else if (*itr == "操作説明")			//操作説明を選んだ場合
	{
		this->ChoiseMenu = (int)MENU_SETUMEI;	//操作説明
	}
	else if (*itr == "セーブ")			//セーブを選んだ場合
	{
		this->ChoiseMenu = (int)MENU_SAVE;		//セーブ
		//return;
	}

	this->menuwindow->SetIsChoise(true);
		
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
	//this->Str_itr = this->Str.begin();	//先頭要素へ
	this->NowSelectReset((int)UI_SELECT_MENU);	//選択している要素をリセット
	this->menuwindow->Reset();	//選択内容リセット
}

//選択されているか取得
bool UI::GetIsChoise(void)
{
	return this->menuwindow->GetIsChoise();
}

//バトルコマンドで使用する要素を初期化する
void UI::BattleInit()
{
	this->BattleCommadType = -1;	//選択したコマンド内容リセット
}

//戦闘画面で選んだコマンドを設定する
void UI::SetBattleFlg()
{

	auto choise_itr = this->BattleCommand->GetNowSelect();

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

//バトルコマンド描画
void UI::DrawCommand()
{
	this->DrawWindow(CMD_WIN_X, CMD_WIN_Y, CMD_WIN_WIDTH, CMD_WIN_HEIGHT);	//ウィンドウ描画

	//選択肢描画
	this->BattleCommand->Draw(CMD_TXT_X, CMD_TXT_Y, 1);

	return;
}

//ステータスウィンドウ描画
void UI::DrawStateWindow(PLAYER *player)
{

	this->DrawWindow(STA_WIN_X, STA_WIN_Y,STA_WIN_WIDTH, STA_WIN_HEIGHT, GetColor(0, 0, 255));	//ウィンドウ描画
	

	//ステータス描画
	DrawFormatString(STA_TXT_X, STA_TXT_Y, GetColor(255,255,255), "%s Lv:%d HP:%d MP:%d",player->GetName(), player->GetLevel(), player->GetHP(), player->GetMP());
	DrawFormatString(STA_TXT_X, STA_TXT_Y + STA_SPACE, GetColor(255, 255, 255), "%s Lv:%d HP:%d MP:%d", player->GetName(), player->GetLevel(), player->GetHP(), player->GetMP());
	DrawFormatString(STA_TXT_X, STA_TXT_Y + STA_SPACE * 2, GetColor(255, 255, 255), "%s Lv:%d HP:%d MP:%d", player->GetName(), player->GetLevel(), player->GetHP(), player->GetMP());
	DrawFormatString(STA_TXT_X, STA_TXT_Y + STA_SPACE * 3, GetColor(255, 255, 255), "%s Lv:%d HP:%d MP:%d", player->GetName(), player->GetLevel(), player->GetHP(), player->GetMP());

}

//ウィンドウを描画する
void UI::DrawWindow(int x, int y, int width, int height)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率80％に設定

	DrawBox(x, y, x + width, y + height, GetColor(0, 0, 0), TRUE);	//塗りつぶしありで四角形を描画

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//描画モードを通常に戻す

}

//ウィンドウを描画する(色指定)
void UI::DrawWindow(int x,int y,int width,int height,unsigned int color)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率80％に設定

	DrawBox(x, y, x + width, y + height, color, TRUE);	//塗りつぶしありで四角形を描画

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

//指定された選択肢のキー操作を行う
void UI::SelectOperation(KEYDOWN *keydown, MUSIC *se, int kind)
{
	switch (kind)
	{

	case (int)UI_SELECT_MENU:		//メニュー画面

		this->MenuSelect->SelectOperation(keydown, se);	//メニュー画面キー操作

		break;

	case (int)UI_SELECT_BATTLE_CMD:		//バトルコマンド

		this->BattleCommand->SelectOperation(keydown, se);	//バトルコマンドのキー操作

		break;

	default:
		break;
	}

	return;
}

//指定された選択肢の現在選択している要素を取得する
std::vector<std::string>::iterator UI::GetNowSelect(int kind)
{
	switch (kind)
	{

	case (int)UI_SELECT_MENU:			//メニュー画面の時

		return this->MenuSelect->GetNowSelect();

		break;

	case (int)UI_SELECT_BATTLE_CMD:			//バトルコマンドの時

		return this->BattleCommand->GetNowSelect();

		break;

	default:
		break;
	}
}

//選択肢の内容をクリアする
void UI::SelectClear(int kind)
{

	switch (kind)
	{

	case (int)UI_SELECT_MENU:			//メニュー画面の時

		this->MenuSelect->SelectClear();	//選択肢削除

		break;

	case (int)UI_SELECT_BATTLE_CMD:			//バトルコマンドの時

		return this->BattleCommand->SelectClear();	//選択肢削除

		break;

	default:
		break;
	}


	return;
}

//現在選択している内容を最初の要素に戻す
void UI::NowSelectReset(int kind)
{
	switch (kind)
	{

	case (int)UI_SELECT_MENU:			//メニュー画面の時

		this->MenuSelect->NowSelectReset();	//選択肢削除

		break;

	case (int)UI_SELECT_BATTLE_CMD:			//バトルコマンドの時

		return this->BattleCommand->NowSelectReset();	//選択肢削除

		break;

	default:
		break;
	}

	return;
}

//アニメーション画像追加
bool UI::AddUiAnime(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	
	return this->UiAnime->Add(dir, name, SplitNumALL,SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
}

//UIアニメ描画
void UI::DrawUiAnime(int x,int y)
{
	if (this->IsDrawUIAnime)	//描画してよい時は
	{
		this->UiAnime->DrawAnime(x, y);	//アニメーション描画
	}

	return;
}

//アニメーション画像を描画してよいか設定
void UI::SetIsDrawUIAnime(bool Isdrawuianime)
{
	this->IsDrawUIAnime = Isdrawuianime;
	return;
}

//アニメーション画像を描画してよいか取得
bool UI::GetIsDrawUIAnime(void)
{
	return this->IsDrawUIAnime;
}
