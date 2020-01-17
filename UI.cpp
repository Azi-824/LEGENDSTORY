//UI.cpp
//ゲーム内で使用するUIを管理するクラス

//####################### ヘッダファイル読み込み ########################
#include "UI.hpp"

//####################### クラス定義 ################################

//コンストラクタ
UI::UI()
{

	this->UiImage = new IMAGE(UI_DIR, UI_TRIANGLENAME);	//uiの画像作成

	this->menuwindow = new MENU();			//メニューウィンドウ作成

	this->BattleCommadType = -1;			//選択したバトルコマンドの種類を初期化

	this->ChoiseMenu = -1;					//メニュー画面での選択内容を初期化

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
		this->DrawWindow(x + MENU_WINDOW_RELATIVE_X - this->UiImage->GetWidth((int)UI_TRIANGLE_MINI), y + (-MENU_WINDOW_RELATIVE_Y), MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画
		this->ChoiseDraw(x + MENU_WINDOW_RELATIVE_X, y + (-MENU_WINDOW_RELATIVE_Y),(int)UI_TRIANGLE_MINI,false ,GetColor(255,255,255),"ステータス", "アイテム", "装備", "操作説明","セーブ");

	}
	else if (x <= MENU_WINDOW_CHENGE_POSX && y <= MENU_WINDOW_CHENGE_POSY)	//左側にいるときは
	{
		//プレイヤーの右下にメニューウィンドウを表示
		this->DrawWindow((x + MENU_WINDOW_RELATIVE_X) - this->UiImage->GetWidth((int)UI_TRIANGLE_MINI), y + MENU_WINDOW_RELATIVE_Y, MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画
		this->ChoiseDraw(x + MENU_WINDOW_RELATIVE_X, y + MENU_WINDOW_RELATIVE_Y, (int)UI_TRIANGLE_MINI,false, GetColor(255, 255, 255), "ステータス", "アイテム", "装備", "操作説明", "セーブ");
	}
	else if (x >= MENU_WINDOW_CHENGE_POSX && y <= MENU_WINDOW_CHENGE_POSY)	//上側にいるときは
	{
		//プレイヤーの左下にメニューウィンドウを表示
		this->DrawWindow(x + (-MENU_WINDOW_RELATIVE_X) - this->UiImage->GetWidth((int)UI_TRIANGLE_MINI), y + MENU_WINDOW_RELATIVE_Y, MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画
		this->ChoiseDraw(x + (-MENU_WINDOW_RELATIVE_X), y + MENU_WINDOW_RELATIVE_Y, (int)UI_TRIANGLE_MINI, false, GetColor(255, 255, 255), "ステータス", "アイテム", "装備", "操作説明", "セーブ");

	}
	else			//それ以外の時は
	{
		//プレイヤーの左上にメニューウィンドウを表示
		this->DrawWindow(x + (-MENU_WINDOW_RELATIVE_X) - this->UiImage->GetWidth((int)UI_TRIANGLE_MINI), y + (-MENU_WINDOW_RELATIVE_Y), MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT);	//ウィンドウ描画
		this->ChoiseDraw(x + (-MENU_WINDOW_RELATIVE_X), y + (-MENU_WINDOW_RELATIVE_Y), (int)UI_TRIANGLE_MINI, false, GetColor(255, 255, 255), "ステータス", "アイテム", "装備", "操作説明", "セーブ");
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
	this->Str_itr = this->Str.begin();	//先頭要素へ
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

	auto choise_itr = this->Str_itr;
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
	this->ChoiseDraw(CMD_TXT_X, CMD_TXT_Y, (int)UI_TRIANGLE_MINI, false, GetColor(255, 255, 255), "こうげき", "ぼうぎょ", "まほう", "アイテム", "にげる");

	return;
}

//ステータスウィンドウ描画
void UI::DrawStateWindow(PLAYER *player)
{

	this->DrawWindow(STA_WIN_X, STA_WIN_Y,STA_WIN_WIDTH, STA_WIN_HEIGHT, GetColor(255, 0, 0));	//ウィンドウ描画
	
	DrawString(STA_TXT_X, STA_TXT_Y, "名前  Lev HP  MP", GetColor(255, 255, 255));	//ステータス目次描画

	//ステータス描画
	DrawFormatString(STA_TXT_X, STA_TXT_Y + STA_SPACE, GetColor(255, 255, 255), "%s%d %d %d",player->GetName(), player->GetLevel(), player->GetHP(), player->GetMP());
	DrawFormatString(STA_TXT_X, STA_TXT_Y + STA_SPACE*2, GetColor(255, 255, 255), "%s%d %d %d", player->GetName(), player->GetLevel(), player->GetHP(), player->GetMP());
	DrawFormatString(STA_TXT_X, STA_TXT_Y + STA_SPACE*3, GetColor(255, 255, 255), "%s%d %d %d", player->GetName(), player->GetLevel(), player->GetHP(), player->GetMP());
	DrawFormatString(STA_TXT_X, STA_TXT_Y + STA_SPACE*4, GetColor(255, 255, 255), "%s%d %d %d", player->GetName(), player->GetLevel(), player->GetHP(), player->GetMP());

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

//アニメーション画像追加
bool UI::AddUiAnime(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	
	return this->UiAnime->Add(dir, name, SplitNumALL,SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
}

//UIアニメ描画
void UI::DrawUiAnime(int x,int y)
{
	this->UiAnime->DrawAnime(x, y);	//アニメーション描画
}
