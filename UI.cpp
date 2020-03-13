//UI.cpp
//ゲーム内で使用するUIを管理するクラス

//####################### ヘッダファイル読み込み ########################
#include "UI.hpp"

//####################### クラス定義 ################################

//コンストラクタ
UI::UI()
{

	this->UiImage = new IMAGE(UI_DIR, UI_WINDOW_NAME);	//uiの画像作成

	this->MenuSelect = new SELECT("ステータス", "アイテム", "装備", "操作説明", "セーブ");	//メニューの選択肢生成
	this->BattleCommand = new SELECT("こうげき", "ぼうぎょ", "まほう", "アイテム", "にげる");	//バトルコマンドの選択肢生成

	this->ItemSelect = new SELECT();	//アイテムの選択肢を生成
	this->WeaponSelect = new SELECT();	//武器の選択肢を生成
	this->ArmorSelect = new SELECT();	//防具の選択肢を生成

	this->IsDrawUIAnime = true;				//UIのアニメーションを描画してよい

	//アニメーション画像を生成（テキストポーズ）
	this->UiAnime = new ANIMATION(TXT_POSE_DIR, TXT_POSE_NAME, TXT_POSE_ALL_CNT, TXT_POSE_YOKO_CNT, TXT_POSE_TATE_CNT, TXT_POSE_WIDTH, TXT_POSE_HEIGHT, TXT_POSE_SPEED, true);

	return;
}

//デストラクタ
UI::~UI()
{
	delete this->UiImage;		//Ui破棄
	delete this->UiAnime;		//uianime破棄
	delete this->MenuSelect;	//menuselect破棄
	delete this->BattleCommand;	//battlecommand破棄
	delete this->ItemSelect;	//ItemSelect破棄
	delete this->WeaponSelect;	//WeaponSelect破棄
	delete this->ArmorSelect;	//ArmorSelect破棄

	return;
}

//メニューウィンドウ描画
void UI::DrawMenu(int x,int y)
{
	//プレイヤーの位置によって描画位置を変える
	if (x <= MENU_WINDOW_CHENGE_POSX && y >= MENU_WINDOW_CHENGE_POSY)	//左上にいるときは
	{
		//プレイヤーの右上にメニューウィンドウを表示
		this->DrawWindow(x + MENU_LIST_WINDOW_RELATIVE_X - TRIANGLE_MINI_SIZE, y + (-MENU_LIST_WINDOW_RELATIVE_Y), MENU_LIST_WINDOW_WIDTH, MENU_LIST_WINDOW_HEIGHT);	//ウィンドウ描画
		this->MenuSelect->Draw(x + MENU_LIST_WINDOW_RELATIVE_X, y + (-MENU_LIST_WINDOW_RELATIVE_Y), 1);
	}
	else if (x <= MENU_WINDOW_CHENGE_POSX && y <= MENU_WINDOW_CHENGE_POSY)	//左側にいるときは
	{
		//プレイヤーの右下にメニューウィンドウを表示
		this->DrawWindow((x + MENU_LIST_WINDOW_RELATIVE_X) - TRIANGLE_MINI_SIZE, y + MENU_LIST_WINDOW_RELATIVE_Y, MENU_LIST_WINDOW_WIDTH, MENU_LIST_WINDOW_HEIGHT);	//ウィンドウ描画
		this->MenuSelect->Draw(x + MENU_LIST_WINDOW_RELATIVE_X, y + MENU_LIST_WINDOW_RELATIVE_Y, 1);
	}
	else if (x >= MENU_WINDOW_CHENGE_POSX && y <= MENU_WINDOW_CHENGE_POSY)	//上側にいるときは
	{
		//プレイヤーの左下にメニューウィンドウを表示
		this->DrawWindow(x + (-MENU_LIST_WINDOW_RELATIVE_X) - TRIANGLE_MINI_SIZE, y + MENU_LIST_WINDOW_RELATIVE_Y, MENU_LIST_WINDOW_WIDTH, MENU_LIST_WINDOW_HEIGHT);	//ウィンドウ描画
		this->MenuSelect->Draw(x + (-MENU_LIST_WINDOW_RELATIVE_X), y + MENU_LIST_WINDOW_RELATIVE_Y, 1);
	}
	else			//それ以外の時は
	{
		//プレイヤーの左上にメニューウィンドウを表示
		this->DrawWindow(x + (-MENU_LIST_WINDOW_RELATIVE_X) - TRIANGLE_MINI_SIZE, y + (-MENU_LIST_WINDOW_RELATIVE_Y), MENU_LIST_WINDOW_WIDTH, MENU_LIST_WINDOW_HEIGHT);	//ウィンドウ描画
		this->MenuSelect->Draw(x + (-MENU_LIST_WINDOW_RELATIVE_X), y + (-MENU_LIST_WINDOW_RELATIVE_Y), 1);
	}

	return;
}

//メニュー関係のメンバーをリセット
void UI::ResetMenu()
{
	this->MenuSelect->SetSelectFlg(false);		//選択していない
	this->MenuSelect->NowSelectReset();			//選択している内容をリセット

}

//バトルコマンドで使用する要素を初期化する
void UI::BattleInit()
{
	this->BattleCommand->NowSelectReset();	//コマンドの選択をリセット
	this->BattleCommand->SetSelectFlg(false);	//選択していない状態へ
}

//バトルコマンド描画
void UI::DrawCommand()
{
	this->DrawWindow(CMD_WIN_X, CMD_WIN_Y, CMD_WIN_WIDTH, CMD_WIN_HEIGHT);	//ウィンドウ描画

	//選択肢描画
	this->BattleCommand->Draw(CMD_TXT_X, CMD_TXT_Y, (int)UI_SELECT_BATTLE_CMD);

	return;
}

//ステータスウィンドウ描画
void UI::DrawStateWindow(PLAYER *player)
{

	this->DrawWindow(STA_WIN_X, STA_WIN_Y,STA_WIN_WIDTH, STA_WIN_HEIGHT);	//ウィンドウ描画
	

	//ステータス描画
	DrawFormatString(STA_TXT_X, STA_TXT_Y, GetColor(255,255,255), "%s\nLv:%d\nHP:%d\nMP:%d\n",player->GetName(), player->GetLevel(), player->GetHP(), player->GetMP());
	DrawBox(STA_HP_BAR_X, STA_HP_BAR_Y, STA_HP_BAR_X + STA_HP_BAR_WIDTH, STA_HP_BAR_Y + STA_HP_BAR_HEIGHT, GetColor(0, 255, 0), FALSE);	//HPバー枠線描画
	static double hp_percent = 0.0;//HP割合
	static double hp_now = 0.0, hp_max = 0.0;	//現在のHPと最大HP
	static int draw_hp = 0;		//描画HP
	hp_now = player->GetHP();	//現在のHP
	hp_max = player->GetMaxHP();//最大のHP
	hp_percent = hp_now / hp_max;//HPの割合計算
	draw_hp = STA_HP_BAR_WIDTH * hp_percent;		//描画するHP量計算
	DrawBox(STA_HP_BAR_X, STA_HP_BAR_Y, STA_HP_BAR_X + draw_hp, STA_HP_BAR_Y + STA_HP_BAR_HEIGHT, GetColor(0, 255, 0), TRUE);	//HP描画

	DrawBox(STA_MP_BAR_X, STA_MP_BAR_Y, STA_MP_BAR_X + STA_MP_BAR_WIDTH, STA_MP_BAR_Y + STA_MP_BAR_HEIGHT, GetColor(0, 0, 255), FALSE);	//HPバー枠線描画
	static double mp_percent = 0.0;//MP割合
	static double mp_now = 0.0, mp_max = 0.0;	//現在のMPと最大MP
	static int draw_mp = 0;		//描画HP
	mp_now = player->GetMP();	//現在のMP
	mp_max = player->GetMaxMP();//最大のMP
	mp_percent = mp_now / mp_max;//MPの割合計算
	draw_mp = STA_MP_BAR_WIDTH * mp_percent;		//描画するMP量計算
	DrawBox(STA_MP_BAR_X, STA_MP_BAR_Y, STA_MP_BAR_X + draw_mp, STA_MP_BAR_Y + STA_MP_BAR_HEIGHT, GetColor(0, 0, 255), TRUE);	//HP描画


}

//ウィンドウを描画する
void UI::DrawWindow(int x, int y, int width, int height)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率80％に設定

	DrawBox(x, y, x + width, y + height, GetColor(0, 0, 0), TRUE);	//塗りつぶしありで四角形を描画

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//描画モードを通常に戻す

	this->DrawWindowFrame(x, y, width, height);				//ウィンドウの枠を描画

	return;
}

//ウィンドウを描画する(色指定)
void UI::DrawWindow(int x,int y,int width,int height,unsigned int color)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率80％に設定

	DrawBox(x, y, x + width, y + height, color, TRUE);	//塗りつぶしありで四角形を描画

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//描画モードを通常に戻す

	this->DrawWindowFrame(x, y, width, height);				//ウィンドウの枠を描画

	return;
}

//ウィンドウの枠を描画する
void UI::DrawWindowFrame(int x, int y, int width, int height)
{
	DrawBox(x, y, x + width, y + height, GetColor(255, 255, 255), FALSE);	//塗りつぶしなしで四角形を描画
	return;
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

//画像サイズを設定する
void UI::SetSize(void)
{
	this->UiImage->SetSize();		//UI画像サイズ設定
	this->UiAnime->SetSize();		//Uiアニメーション画像サイズ設定
	this->MenuSelect->SetSize();	//メニュー画面の選択肢のサイズ設定
	this->BattleCommand->SetSize();	//戦闘画面の選択肢のサイズ設定
	this->WeaponSelect->SetSize();	//武器の選択肢のサイズ設定
	this->ArmorSelect->SetSize();	//防具の選択肢のサイズ設定
	this->ItemSelect->SetSize();	//アイテムの選択肢のサイズ設定
	
	return;
}

//アイテムの選択肢を描画する
void UI::DrawItemSelect(int x, int y, std::vector<int> item_possession)
{
	this->ItemSelect->Draw(x, y);	//アイテムの選択肢描画

	static int Height = 0;	//高さ
	int Cnt = 0;			//カウント用

	Height = GetFontSize();	//高さ取得

	for (int i = 0; i < item_possession.size(); ++i)	//アイテムの種類数分繰り返す
	{

		if (item_possession[i] != 0)	//所持数が0個じゃなければ
		{
			DrawFormatString(x + MENU_ITEM_NAME_SPACE, y + Cnt * Height, GetColor(255, 255, 255), "%d個", item_possession[i]);	//所持しているアイテムの数を描画

			++Cnt;	//カウントアップ

		}

	}

	return;

}

//メニュー画面の装備描画処理
void UI::DrawMenuEquip(int x, int y, std::vector<int> wpn_possession, std::vector<int> amr_possession)
{

	static int Height = 0;	//高さ
	Height = GetFontSize();	//高さ取得

	this->WeaponSelect->Draw(x, y);								//武器の選択肢描画

	for (int i = 0; i < wpn_possession.size(); ++i)	//武器の種類分繰り返す
	{
		DrawFormatString(x + MENU_EQUIP_NAME_SPACE, y + i * Height, GetColor(255, 255, 255), "%d個", wpn_possession[i]);	//所持している武器の数を描画
	}

	this->ArmorSelect->Draw(x + (MENU_WINDOW_WIDTH / 2), y);	//防具の選択肢描画

	for (int i = 0; i < amr_possession.size(); ++i)	//防具の種類分繰り返す
	{
		DrawFormatString((x + (MENU_WINDOW_WIDTH / 2)) + MENU_EQUIP_NAME_SPACE, y + i * Height, GetColor(255, 255, 255), "%d個", amr_possession[i]);	//所持している防具の数を描画
	}

	return;

}
