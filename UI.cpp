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
	this->Yes_No = new SELECT("はい", "いいえ");	//はい、いいえの選択肢を生成
	this->EquipSelect = new SELECT("武器", "防具");	//武器、防具の選択肢を生成

	this->EquipSelect->SetSideMode(true);		//選択肢を横向きに並べる

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
	delete this->Yes_No;		//Yes_No破棄
	delete this->EquipSelect;	//EquipSelect破棄

	return;
}

//******************************** メニュー関係 *************************
//メニューウィンドウ描画
void UI::DrawMenu()
{

	this->DrawWindow(MENU_LIST_WIN_X, MENU_LIST_WIN_Y, MENU_LIST_WIN_WIDTH, MENU_LIST_WIN_HEIGHT);	//ウィンドウ描画
	this->MenuSelect->Draw(MENU_LIST_TEXT_X, MENU_LIST_TEXT_Y);										//メニュー画面の選択肢描画

	return;
}

//メニュー関係のメンバーをリセット
void UI::ResetMenu()
{
	this->MenuSelect->SetSelectFlg(false);	//選択していない
	this->MenuSelect->NowSelectReset();		//選択している内容をリセット

	this->Yes_No->Default();				//はい、いいえの選択肢をデフォルトの状態に戻す
	this->WeaponSelect->Default();			//武器の選択肢をデフォルトへ
	this->ArmorSelect->Default();			//防具の選択肢をデフォルトへ
	this->EquipSelect->Default();			//武器、防具の選択肢をデフォルトの状態に戻す

	this->Menu_Equip_dir = (MENU_EQUIP_SELECT_KIND);//装備画面の選択肢の段階を最初へ

}

//メニューの装備画面の選択肢の段階を取得
int UI::GetMenuEquipDir(void)
{
	return this->Menu_Equip_dir;
}

//メニューウィンドウでの確認の選択肢描画
void UI::DrawMenuCheck(void)
{

	this->UiImage->Draw(PLAY_WIN_X, PLAY_WIN_Y);	//ウィンドウ描画

	switch (this->MenuSelect->GetSelectNum())	//メニュー画面で選択した内容毎
	{

	case (int)MENU_ITEM:	//アイテムを選んだ場合

		DrawFormatString(PLAY_WIN_TEXT_X, PLAY_WIN_TEXT_Y, GetColor(255, 255, 255), "%sを使いますか？", this->ItemSelect->GetSelectText());	//確認メッセージ描画

		break;

	case (int)MENU_EQUIPMENT:	//装備を選んだ場合

		if (this->EquipSelect->GetSelectNum() == SELECT_EQUIP_WEAPON)	//武器だったら
		{
			DrawFormatString(PLAY_WIN_TEXT_X, PLAY_WIN_TEXT_Y, GetColor(255, 255, 255), "%sを装備しますか？", this->WeaponSelect->GetSelectText());	//確認メッセージ描画
		}
		else	//防具だったら
		{
			DrawFormatString(PLAY_WIN_TEXT_X, PLAY_WIN_TEXT_Y, GetColor(255, 255, 255), "%sを装備しますか？", this->ArmorSelect->GetSelectText());	//確認メッセージ描画
		}

		break;

	default:
		break;
	}

	int Height = GetFontSize();	//高さ取得

	this->Yes_No->Draw(PLAY_WIN_TEXT_X, PLAY_WIN_TEXT_Y + Height);	//はい、いいえの選択肢描画

	return;

}

//メニューのアイテム画面の処理
bool UI::MenuSelectItem(KEYDOWN *keydown, MUSIC *sys_se)
{
	if (this->ItemSelect->GetSelectKind() != 0)	//アイテムを一種類以上持っていた場合
	{
		this->ItemSelect->SelectOperation(keydown, sys_se);	//アイテムの選択肢キー操作

		if (this->ItemSelect->GetBackFlg())		//戻る選択をしたとき
		{
			this->ItemSelect->Default();			//アイテムの選択肢をデフォルト状態に
			this->ResetMenu();					//メニュー選択に戻る
		}

		if (this->ItemSelect->GetSelectFlg())		//アイテムを選んだら
		{
			this->ItemSelect->SetIsKeyOpe(false);	//アイテムの選択肢キー操作不可
			this->Yes_No->SetIsKeyOpe(true);			//はい、いいえの選択肢キー操作可能

			this->Yes_No->SelectOperation(keydown, sys_se);	//はい、いいえの選択肢キー操作

			if (this->Yes_No->GetSelectFlg())		//はいかいいえを選択したら
			{
				if (this->Yes_No->GetSelectNum() == (int)SELECT_YES)	//はいを選んだとき
				{
					return true;	//アイテムを選択した
				}
				this->Yes_No->Default();			//はい、いいえの選択肢デフォルトへ
				this->ItemSelect->Default();	//アイテムの選択肢デフォルトへ
			}

		}

	}

	return false;	//アイテムを選択していない

}

//メニュー画面の装備描画処理
void UI::DrawMenuEquip(WEAPON *weapon, ARMOR *armor)
{

	static int Height = 0;	//高さ
	Height = GetFontSize();	//高さ取得

	this->EquipSelect->Draw(MENU_TEXT_X, MENU_TEXT_TOP_Y);		//装備選択描画

	this->WeaponSelect->Draw(MENU_TEXT_X, MENU_TEXT_Y);			//武器の選択肢描画

	for (int i = 0; i < weapon->GetSize(); ++i)	//武器の種類分繰り返す
	{
		DrawFormatString(MENU_TEXT_X + MENU_EQUIP_NAME_SPACE, //X位置
			MENU_TEXT_Y + i * Height,	//Y位置
			GetColor(255, 255, 255),	//描画色
			"%d個", weapon->GetPossession(weapon->GetCode(i)));	//所持している武器の数を描画

		DrawFormatString(MENU_TEXT_X + MENU_EQUIP_NAME_SPACE + MENU_WQUIP_POSSESSION_SPACE,
			MENU_TEXT_Y + i * Height,
			GetColor(255, 255, 255),
			"ATK+%d", weapon->GetAtk(weapon->GetCode(i)));	//攻撃力を描画

	}

	this->ArmorSelect->Draw(MENU_TEXT_X + (MENU_WINDOW_WIDTH / 2), MENU_TEXT_Y);	//防具の選択肢描画

	for (int i = 0; i < armor->GetSize(); ++i)	//防具の種類分繰り返す
	{
		DrawFormatString((MENU_TEXT_X + (MENU_WINDOW_WIDTH / 2)) + MENU_EQUIP_NAME_SPACE,
			MENU_TEXT_Y + i * Height,
			GetColor(255, 255, 255),
			"%d個", armor->GetPossession(armor->GetCode(i)));	//所持している防具の数を描画

		DrawFormatString((MENU_TEXT_X + (MENU_WINDOW_WIDTH / 2)) + MENU_EQUIP_NAME_SPACE + MENU_WQUIP_POSSESSION_SPACE,
			MENU_TEXT_Y + i * Height,
			GetColor(255, 255, 255),
			"DEF+%d", armor->GetDef(armor->GetCode(i)));	//防御力を描画

	}

	return;

}

//メニューの装備画面の処理
int UI::MenuSelectEquip(KEYDOWN *keydown, MUSIC *sys_se)
{

	switch (this->Menu_Equip_dir)		//選択肢の段階
	{

	case (int)MENU_EQUIP_SELECT_KIND:		//武器か防具か選択する段階

		this->EquipSelect->SelectOperation(keydown, sys_se);	//武器か防具かの選択肢のキー操作

		if (this->EquipSelect->GetBackFlg())	//戻る選択をしたら
		{
			this->ResetMenu();					//メニュー選択に戻る
			this->EquipSelect->Default();		//武器防具の選択肢をデフォルトに
		}

		if (this->EquipSelect->GetSelectFlg())	//武器か防具かを選択したら
		{
			this->EquipSelect->SetIsKeyOpe(false);	//武器防具の選択肢のキー操作不可
			this->EquipSelect->SetIsDrawImage(false);//UI非表示
			this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_EQUIP;	//選択肢の段階を次へ
		}

		break;	//武器か防具か選択する段階ここまで

	case (int)MENU_EQUIP_SELECT_EQUIP:		//装備する武器、もしくは防具を選択する段階

		switch (this->EquipSelect->GetSelectNum())		//武器か、防具かどちらを選んだか
		{

		case (int)SELECT_EQUIP_WEAPON:		//武器を選んだとき

			this->WeaponSelect->SetIsKeyOpe(true);						//武器の選択肢、キー操作可能
			this->WeaponSelect->SetIsDrawImage(true);					//武器の選択UI表示
			this->WeaponSelect->SelectOperation(keydown, sys_se);		//武器の選択キー操作

			//************* 戻る選択をした時の処理 *****************
			if (this->WeaponSelect->GetBackFlg())	//戻る選択をしたら
			{
				this->WeaponSelect->Default();			//武器の選択肢、デフォルト値へ
				this->EquipSelect->Default();			//武器、防具の選択を可能へ
				this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_KIND;	//選択肢の段階を前へ
			}

			//************** 装備する武器選択後の処理 ******************
			if (this->WeaponSelect->GetSelectFlg())		//装備する武器を選んだら
			{
				this->WeaponSelect->SetIsKeyOpe(false);		//武器の選択はできないように設定
				this->WeaponSelect->SetIsDrawImage(false);	//防具の選択肢UI非表示

				this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_DECISION;	//選択肢の段階を次へ

			}

			break;	//武器を選んだときここまで

		case (int)SELECT_EQUIP_ARMOR:		//防具を選んだとき

			this->ArmorSelect->SetIsKeyOpe(true);					//防具の選択肢、キー操作可能
			this->ArmorSelect->SetIsDrawImage(true);				//防具の選択UI表示
			this->ArmorSelect->SelectOperation(keydown, sys_se);	//防具の選択キー操作

			//************* 戻る選択をした時の処理 *****************
			//修正点あり
			if (this->ArmorSelect->GetBackFlg())	//戻る選択をしたら
			{
				this->ArmorSelect->Default();		//防具の選択肢、デフォルト値へ
				this->EquipSelect->Default();			//武器、防具の選択を可能へ
				this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_KIND;	//選択肢の段階を前へ
			}


			//************** 装備する防具選択後の処理 ******************
			if (this->ArmorSelect->GetSelectFlg())		//装備する防具を選んだら
			{
				this->ArmorSelect->SetIsKeyOpe(false);	//防具の選択はできないように設定
				this->ArmorSelect->SetIsDrawImage(false);//防具の選択肢UI非表示
				this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_DECISION;	//選択肢の段階を次へ

			}

			break;	//防具を選んだとき

		default:
			break;
		}


		break;	//装備する武器、もしくは防具を選択する段階ここまで

	case (int)MENU_EQUIP_SELECT_DECISION:	//装備するか決定する段階(はい、いいえ)

		this->Yes_No->SetIsKeyOpe(true);					//はい、いいえの選択肢の操作可能に
		this->Yes_No->SelectOperation(keydown, sys_se);	//はい、いいえの選択肢のキー操作

		if (this->Yes_No->GetSelectFlg())					//装備するか選択したら
		{
			if (this->Yes_No->GetSelectNum() == (int)SELECT_YES)		//はい、を選択したら
			{
				this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_EQUIP;	//選択肢の段階を一つ前へ
				this->Yes_No->Default();								//はい、いいえの選択肢デフォルトへ
				sys_se->Play((int)SYS_SE_EQUIP);						//装備した時の音を鳴らす

				return this->EquipSelect->GetSelectNum();	//武器、防具のどちらを選択したかを返す
			}

			this->Yes_No->Default();								//はい、いいえの選択肢デフォルトへ
			this->ArmorSelect->Default();							//防具の選択肢デフォルトへ
			this->WeaponSelect->Default();							//武器の選択肢デフォルトへ
			this->Menu_Equip_dir = (int)MENU_EQUIP_SELECT_EQUIP;	//選択肢の段階を一つ前へ

		}


		break;	//装備するか決定する段階(はい、いいえ)ここまで

	default:
		break;
	}

	return SELECT_NONE;	//装備するものを選ばなかった場合-1を返す

}

//******************************* バトル関係 *******************************
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
	this->BattleCommand->Draw(CMD_TXT_X, CMD_TXT_Y);

	return;
}

//ステータスウィンドウ描画
void UI::DrawStateWindow(PLAYER *player)
{

	this->DrawWindow(STA_WIN_X, STA_WIN_Y,STA_WIN_WIDTH, STA_WIN_HEIGHT);	//ウィンドウ描画
	

	//ステータス描画
	DrawFormatString(STA_TXT_X, STA_TXT_Y, GetColor(255,255,255), "%s\nLv:%d\nHP:%d\nMP:%d\n",player->GetName(), player->GetLevel(), player->GetHP(), player->GetMP());

	//HPバー描画処理
	DrawBox(STA_HP_BAR_X, STA_HP_BAR_Y, STA_HP_BAR_X + STA_HP_BAR_WIDTH, STA_HP_BAR_Y + STA_HP_BAR_HEIGHT, GetColor(0, 255, 0), FALSE);	//HPバー枠線描画
	static double hp_percent = 0.0;//HP割合
	static double hp_now = 0.0, hp_max = 0.0;	//現在のHPと最大HP
	static int draw_hp = 0;		//描画HP
	hp_now = player->GetHP();	//現在のHP
	hp_max = player->GetMaxHP();//最大のHP
	hp_percent = hp_now / hp_max;//HPの割合計算
	draw_hp = STA_HP_BAR_WIDTH * hp_percent;		//描画するHP量計算
	DrawBox(STA_HP_BAR_X, STA_HP_BAR_Y, STA_HP_BAR_X + draw_hp, STA_HP_BAR_Y + STA_HP_BAR_HEIGHT, GetColor(0, 255, 0), TRUE);	//HP描画

	//MPバー描画処理
	DrawBox(STA_MP_BAR_X, STA_MP_BAR_Y, STA_MP_BAR_X + STA_MP_BAR_WIDTH, STA_MP_BAR_Y + STA_MP_BAR_HEIGHT, GetColor(0, 0, 255), FALSE);	//HPバー枠線描画
	static double mp_percent = 0.0;//MP割合
	static double mp_now = 0.0, mp_max = 0.0;	//現在のMPと最大MP
	static int draw_mp = 0;		//描画HP
	mp_now = player->GetMP();	//現在のMP
	mp_max = player->GetMaxMP();//最大のMP
	mp_percent = mp_now / mp_max;//MPの割合計算
	draw_mp = STA_MP_BAR_WIDTH * mp_percent;		//描画するMP量計算
	DrawBox(STA_MP_BAR_X, STA_MP_BAR_Y, STA_MP_BAR_X + draw_mp, STA_MP_BAR_Y + STA_MP_BAR_HEIGHT, GetColor(0, 0, 255), TRUE);	//HP描画

	//BP描画処理
	for (int i = 0; i < MAX_BP; ++i)	//BPの最大値分繰り返す
	{
		//BPの数だけ、塗りつぶして描画する
		//BPがない場合は、枠線だけ描画する
		//使用するBPは色を変えて描画する
		if (i < player->GetUseBP())	//使用するBPより少なかったら
		{
			DrawCircle(STA_BP_X + i * STA_BP_INTERVAL, STA_BP_Y, STA_BP_DRAW_SIZE, GetColor(0, 255, 0), TRUE);	//使用するBP描画(色を変えて描画)
		}
		else if (i < player->GetBP())	//現在のBPより小さかったら
		{
			DrawCircle(STA_BP_X + i * STA_BP_INTERVAL, STA_BP_Y, STA_BP_DRAW_SIZE, GetColor(255, 0, 0), TRUE);	//BP描画(円の中を塗りつぶして描画)
		}

		DrawCircle(STA_BP_X + i * STA_BP_INTERVAL, STA_BP_Y, STA_BP_DRAW_SIZE, GetColor(255, 255, 255), FALSE);	//BP描画(枠線)

	}

	return;

}

//*************************** ウィンドウ関係 *******************************
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

//******************************* UI画像関係 *********************************
//ui画像を描画する
void UI::DrawUiImage(int x, int y,int type)
{
	this->UiImage->Draw(x, y,type);
	return;
}

//ui画像を追加する
bool UI::AddUiImage(const char *dir, const char *name)
{
	if (this->UiImage->AddImage(dir, name))	//読み込み成功したら
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

//**************************** UIアニメーション関係 *******************************
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

//**************************** 設定関係 ****************************
//初期化処理
void UI::Init(void)
{

	this->IsDrawUIAnime = true;				//UIのアニメーションを描画してよい

	this->Menu_Equip_dir = (MENU_EQUIP_SELECT_KIND);//装備画面の選択肢の段階を最初へ

	//武器の選択肢
	this->WeaponSelect->ChengeDefault(false, false);//デフォルト値を変更（キー操作不可、UI非表示）
	this->WeaponSelect->Default();					//デフォルト値に設定
	//防具の選択肢
	this->ArmorSelect->ChengeDefault(false, false);	//デフォルト値を変更（キー操作不可、UI非表示）
	this->ArmorSelect->Default();					//デフォルト値に設定


	return;
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
	this->Yes_No->SetSize();		//はい、いいえの選択肢のサイズ設定
	this->EquipSelect->SetSize();	//武器防具の選択肢のサイズ設定
	
	return;
}

//*************************** アイテム関係 *****************************
//アイテムの選択肢を描画する
void UI::DrawItemSelect(int x,int y,ITEM *item)
{
	this->ItemSelect->Draw(x, y);	//アイテムの選択肢描画

	static int Height = 0;	//高さ
	int Cnt = 0;			//カウント用

	Height = GetFontSize();	//高さ取得

	for (int i = 0; i < item->GetSize(); ++i)	//アイテムの種類数分繰り返す
	{

		if (item->GetPossession(item->GetCode(i)) != 0)	//所持数が0個じゃなければ
		{
			DrawFormatString(x + MENU_ITEM_NAME_SPACE, y + Cnt * Height, GetColor(255, 255, 255), "%d個", item->GetPossession(item->GetCode(i)));	//所持しているアイテムの数を描画

			++Cnt;	//カウントアップ

		}

	}

	return;

}

//アイテムの選択肢を描画する(説明文付き)
void UI::DrawItemSelect(int x, int y,ITEM *item,LIST_ITEM *list_item)
{
	this->ItemSelect->Draw(x, y);	//アイテムの選択肢描画

	static int Height = 0;	//高さ
	int Cnt = 0;			//カウント用

	
	Height = GetFontSize();	//高さ取得

	for (int i = 0; i < item->GetSize(); ++i)	//アイテムの種類数分繰り返す
	{

		if (item->GetPossession(item->GetCode(i)) != 0)	//所持数が0個じゃなければ
		{
			DrawFormatString(x + MENU_ITEM_NAME_SPACE, y + Cnt * Height, GetColor(255, 255, 255), "%d個", item->GetPossession(item->GetCode(i)));	//所持しているアイテムの数を描画

			DrawFormatString(x + MENU_ITEM_NAME_SPACE + MENU_ITEM_POSSESSION_SPACE,
				y + Cnt * Height,
				GetColor(255, 255, 255),
				"%s", list_item->GetDescription(item->GetCode(i)));	//説明文描画

			++Cnt;	//カウントアップ

		}

	}

	return;

}

//**************************** 選択肢関係 *******************************
//選択肢の内容を更新する処理(アイテム)
void UI::SelectUpdate(ITEM *item, LIST_ITEM *item_list)
{

	if (item->GetChengeFlg())	//変更があったら
	{
		this->ItemSelect->SelectClear();	//現在の選択肢クリア

		for (int i = 0; i < item->GetSize(); ++i)	//持っているアイテムの種類分繰り返す
		{
			if (item->GetIsDraw(i))	//アイテムを持っている場合
			{
				this->ItemSelect->AddSelect(item_list->GetName(item->GetCode(i)), item->GetCode(i));	//新しい選択肢を追加し、名前とアイテムコードを渡す
			}
		}

		item->SetChengeFlg(false);	//変更なし

	}

	return;

}

//選択肢の内容を更新する処理(武器)
void UI::SelectUpdate(WEAPON *weapon, LIST_WEAPON *weapon_list)
{

	if (weapon->GetChengeFlg())	//変更があったら
	{
		this->WeaponSelect->SelectClear();	//現在の選択肢クリア

		for (int i = 0; i < weapon->GetSize(); ++i)	//持っている武器の種類分繰り返す
		{
			if (weapon->GetIsDraw(i))	//武器を持っている場合
			{
				this->WeaponSelect->AddSelect(weapon_list->GetName(weapon->GetCode(i)), weapon->GetCode(i));	//新しい選択肢を追加し、名前とアイテムコードを渡す
			}
		}

		weapon->SetChengeFlg(false);	//変更なし

	}

	return;

}

//選択肢の内容を更新する処理(防具)
void UI::SelectUpdate(ARMOR *armor, LIST_ARMOR *armor_list)
{

	if (armor->GetChengeFlg())	//変更があったら
	{
		this->ArmorSelect->SelectClear();	//現在の選択肢クリア

		for (int i = 0; i < armor->GetSize(); ++i)	//持っている防具の種類分繰り返す
		{
			if (armor->GetIsDraw(i))	//防具を持っている場合
			{
				this->ArmorSelect->AddSelect(armor_list->GetName(armor->GetCode(i)), armor->GetCode(i));	//新しい選択肢を追加し、名前とアイテムコードを渡す
			}
		}

		armor->SetChengeFlg(false);	//変更なし

	}

	return;

}

//確認の選択肢を描画する
void UI::DrawCheck(const char *check_msg)
{
	this->UiImage->Draw(PLAY_WIN_X, PLAY_WIN_Y);	//ウィンドウ描画
	
	DrawFormatString(PLAY_WIN_TEXT_X, PLAY_WIN_TEXT_Y, GetColor(255, 255, 255), "%s", check_msg);	//確認メッセージ描画

	int Height = GetFontSize();	//高さ取得

	this->Yes_No->Draw(PLAY_WIN_TEXT_X, PLAY_WIN_TEXT_Y + Height);	//はい、いいえの選択肢描画

	return;

}
