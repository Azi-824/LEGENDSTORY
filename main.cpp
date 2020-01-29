/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* main.cpp     																				　 */

//##########ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"
#include "FONT.hpp"
#include "PLAYER.hpp"
#include "MAP.hpp"
#include "MUSIC.hpp"
#include "ENEMY.hpp"
#include "UI.hpp"
#include "DATA.hpp"
#include "EFFECT.hpp"
#include "MSG.hpp"
#include "ITEM.hpp"

//########## グローバルオブジェクト ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPSクラスのオブジェクトを生成
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWNクラスのオブジェクトを生成

IMAGE *title;						//タイトル画像
IMAGE *back;						//背景画像
IMAGE *back_battle;					//戦闘画面の背景画像
IMAGE *setumei;						//説明画像
IMAGE *map_i;//マップ画像

MUSIC *bgm;							//BGM
MUSIC *bt_se;						//戦闘で使用するSE

EFFECT *Magic_effect;				//魔法エフェクト
EFFECT *Atack_effect;				//攻撃エフェクト
EFFECT *Enemy_Atk_effect;			//敵攻撃エフェクト

FONT *font;							//フォント
UI *ui;								//UI
DATA *data;							//データ
MESSAGE *bt_msg[BT_MSG_KIND];		//戦闘画面のメッセージ
MESSAGE *msg;		//メッセージ

PLAYER *player;						//主人公

ENEMY *enemy[ENEMY_KIND];			//敵

ITEM *item[ITEM_KIND];				//アイテム

MAP *mapdata_field[DRAW_MAP_KIND][MAP_DATA_KIND];		//マップデータ（フィールド）

//############## グローバル変数 ##############
int GameSceneNow = (int)GAME_SCENE_TITLE;	//現在のゲームシーン
int GameSceneBefor;							//前のゲームシーン
int GameSceneNext;							//次のゲームシーン

int BattleStageNow = (int)WAIT_ACT;	//バトルシーンの現在の状態
int BattleActMsgCnt = 0;		//行動メッセージカウント
int BattleActMsgCntMax = 60;	//行動メッセージの表示時間

int MapKind[MAP_DATA_TATE_KIND][MAP_DATA_YOKO_KIND];			//マップの種類
int MapNowPos[2] = {0};											//現在のマップのX位置とY位置を格納
int NowDrawMapKind = (int)DRAW_FILED;							//現在の描画マップの種類(最初はフィールドマップ)
bool IsChengeDrawMap = false;									//描画するマップの種類を切り替えるか

int ChengeDrawCount = 0;	//フェードアウト処理に使用

int EncounteEnemyType = 0;	//遭遇した敵の種類
int Turn = (int)MY_TURN;	//ターン

bool GameEnd_Flg = false;	//ゲーム終了フラグ

std::string Work_Str;		//作業用文字列

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(GAME_WINDOW_MODECHANGE);					//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);			//指定の数値で画面を表示する

	SetWindowStyleMode(SET_WINDOW_ST_MODE_DEFAULT);				//タイトルバーあり

	SetMainWindowText(TEXT(GAME_WINDOW_NAME));					//タイトルの文字

	if (DxLib_Init() == -1) { return -1; }						//ＤＸライブラリ初期化処理

	SetDrawScreen(DX_SCREEN_BACK);								//Draw系関数は裏画面に描画

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 読み込み処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

	//画像関係
	title = new IMAGE(MY_IMG_DIR_TITLE, MY_ING_NAME_TITLE);			//タイトル画像を生成
	if (title->GetIsLoad() == false) { return -1; }					//読み込み失敗時

	back = new IMAGE(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK_TITLE);			//背景画像を生成
	if (back->GetIsLoad() == false) { return -1; }					//読み込み失敗時
	back->AddImage(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK_END, (int)END_BACK);	//エンド画面の背景画像読み込み
	if (back->GetIsLoad() == false) { return -1; }							//読み込み失敗

	back_battle = new IMAGE(MY_IMG_DIR_BATTLE, MY_IMG_NAME_BATTLE_NORMAL);	//戦闘画面の背景画像読み込み
	if (back_battle->GetIsLoad() == false) { return -1; }					//読み込み失敗
	back_battle->AddImage(MY_IMG_DIR_BATTLE, MY_IMG_NAME_BATTLE_NIGHT,(int)NIGHT);		//戦闘画面（夜）の背景画像の読み込み
	if (back_battle->GetIsLoad() == false) { return -1; }					//読み込み失敗

	setumei = new IMAGE(MY_IMG_DIR_BACK, SETUMEI_NAME);		//説明画像の読み込み
	if (setumei->GetIsLoad() == false) { return -1; }		//読み込み失敗

	//音関係
	bgm = new MUSIC(MY_MUSIC_DIR_BGM, MY_MUSIC_NAME_BGM,BGM_KIND);		//BGMを生成
	if (bgm->GetIsLoad() == false) { return -1; }						//読み込み失敗時

	bt_se = new MUSIC(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_LEVUP, BT_SE_KIND);	//SEを生成
	if (bt_se->GetIsLoad() == false) { return -1; }						//読み込み失敗時
	bt_se->ChengePlayType(DX_PLAYTYPE_BACK);							//再生方法変更
	//音の追加処理
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_SLASH, (int)BT_SE_SLASH) == false) { return -1; }	//斬るときの音追加
	if (bt_se->Add(MY_MUSIC_DIR_BT_SE, MY_SE_NAME_THUNDER, (int)BT_SE_THUNDER) == false) { return -1; }//雷の音追加

	//フォント関係
	font = new FONT(MY_FONT_DIR, MY_FONT_NAME, FONT_NAME);			//フォントを生成
	if (font->GetIsLoad() == false) { return -1; }					//読み込み失敗時

	data = new DATA();		//データ

	//メッセージ関係
	for (int cnt = 0; cnt < BT_MSG_KIND; ++cnt)
	{
		bt_msg[cnt] = new MESSAGE();	//メッセージ作成
	}
	msg = new MESSAGE();	//メッセージ作成
	if (data->LoadMsg(msg, MSG_DATA_DIR, MSG_DATA_NAME) == false) { return -1; }	//メッセージデータ読み込み

	//エフェクト関係
	//魔法エフェクト
	Magic_effect = new EFFECT(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC, MAGIC_ALL_CNT, MAGIC_YOKO_CNT, MAGIC_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC_SPEED, false, MAGIC_EFFECT_KIND);
	if (Magic_effect->GetIsLoad() == false) { return -1; }		//読み込み失敗
	if (Magic_effect->Add(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC2, MAGIC2_ALL_CNT, MAGIC2_YOKO_CNT, MAGIC2_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC_SPEED, false, (int)MAGIC_2) == false) { return -1; }	//読み込み失敗
	
	//攻撃エフェクト
	Atack_effect = new EFFECT(MY_ANIME_DIR_ATKEFECT, MY_ANIME_NAME_ATKEFECT, ATK_ALL_CNT, ATK_YOKO_CNT, ATK_TATE_CNT, ATK_WIDTH, ATK_HEIGHT, ATK_SPEED, false, ATACK_EFFECT_KIND);
	if (Atack_effect->GetIsLoad() == false) { return -1; }		//読み込み失敗

	//敵攻撃エフェクト
	Enemy_Atk_effect = new EFFECT(MY_ANIME_DIR_ENE_ATK, MY_ANIME_NAME_ENE_ATK_TUME, ENE_ATK_TUME_ALL_CNT, ENE_ATK_TUME_YOKO_CNT, ENE_ATK_TUME_TATE_CNT, ENE_ATK_TUME_WIDTH, ENE_ATK_TUME_HEIGHT, ENE_ATK_TUME_SPEED, false,ENE_ATK_EFFECT_KIND);
	if (Enemy_Atk_effect->GetIsLoad() == false) { return -1; }		//読み込み失敗
	//敵攻撃エフェクト追加
	if (Enemy_Atk_effect->Add(MY_ANIME_DIR_ENE_ATK, MY_ANIME_NAME_ENE_ATK_KIBA, ENE_ATK_KIBA_ALL_CNT, ENE_ATK_KIBA_YOKO_CNT, ENE_ATK_KIBA_TATE_CNT, ENE_ATK_KIBA_WIDTH, ENE_ATK_KIBA_HEIGHT, ENE_ATK_KIBA_SPEED, false, (int)ENE_ATK_KIBA) == false) { return -1; }	//読み込み失敗
	if (Enemy_Atk_effect->Add(MY_ANIME_DIR_ENE_ATK, MY_ANIME_NAME_ENE_ATK_TAIL_BIG, ENE_ATK_TAIL_BIG_ALL_CNT, ENE_ATK_TAIL_BIG_YOKO_CNT, ENE_ATK_TAIL_BIG_TATE_CNT, ENE_ATK_TAIL_BIG_WIDTH, ENE_ATK_TAIL_BIG_HEIGHT, ENE_ATK_TAIL_BIG_SPEED, false, (int)ENE_ATK_TAIL_BIG) == false) { return -1; }	//読み込み失敗

	//プレイヤー関係
	player = new PLAYER();		//プレイヤー生成
	if (player->SetImage(MY_IMG_DIR_CHARCTOR, MY_IMG_NAME_PLAYER) == false) { return -1; }	//読み込み失敗
	if (player->SetAnime(MY_ANIME_DIR_PLAYER, MY_ANIME_NAME_PLAYER, PLAYER_ALL_CNT, PLAYER_YOKO_CNT, PLAYER_TATE_CNT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_ANI_SPEED, true) == false) { return -1; } //読み込み失敗
	
	//プレイヤーのデータをcsvファイルから読み込み
	if (data->LoadPlayer(player, PLAYER_DATA_DIR, PLAYER_DATA_NAME) == false) { return -1; }	//読み込み失敗
	player->SetInit();	//初期設定

	//UI関係
	ui = new UI();		//UI作成
	if (ui->AddUiImage(UI_DIR, UI_TRIANGLE_MINI_NAME, (int)UI_TRIANGLE_MINI) == false) { return -1; }	//横向き三角（ミニ）の画像の追加
	if (ui->AddUiImage(UI_DIR, UI_WINDOW_NAME, (int)UI_WINDOW) == false) { return -1; }	//ウィンドウ


	//敵関係
	enemy[(int)SLIME] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SLIME);	//スライム作成
	if (enemy[(int)SLIME]->GetIsLoad() == false) { return -1; }	//読み込み失敗

	enemy[(int)YADOKARI]=new ENEMY(ENEMY_DIR, ENEMY_NAME_YADOKARI);	//ヤドカリ作成
	if (enemy[(int)YADOKARI]->GetIsLoad() == false) { return -1; }	//読み込み失敗

	enemy[(int)BAT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_BAT);	//こうもり作成
	if (enemy[(int)BAT]->GetIsLoad() == false) { return -1; }	//読み込み失敗

	enemy[(int)FARAO] = new ENEMY(ENEMY_DIR, ENEMY_NAME_FARAO);	//ファラオ作成
	if (enemy[(int)FARAO]->GetIsLoad() == false) { return -1; }	//読み込み失敗

	enemy[(int)GOBURIN] = new ENEMY(ENEMY_DIR, ENEMY_NAME_GOBURIN);	//ゴブリン作成
	if (enemy[(int)GOBURIN]->GetIsLoad() == false) { return -1; }	//読み込み失敗

	enemy[(int)AKUMA] = new ENEMY(ENEMY_DIR, ENEMY_NAME_AKUMA);	//デーモン作成
	if (enemy[(int)AKUMA]->GetIsLoad() == false) { return -1; }	//読み込み失敗

	enemy[(int)HARPY] = new ENEMY(ENEMY_DIR, ENEMY_NAME_HARPY);	//ハーピー作成
	if (enemy[(int)HARPY]->GetIsLoad() == false) { return -1; }	//読み込み失敗

	enemy[(int)IFRIT] = new ENEMY(ENEMY_DIR, ENEMY_NAME_IFRIT);	//イフリート作成
	if (enemy[(int)IFRIT]->GetIsLoad() == false) { return -1; }	//読み込み失敗

	//敵のデータをcsvファイルから読み込み
	if (data->LoadEnemy(enemy, ENEMY_DATA_DIR, ENEMY_DATA_NAME) == false) { return -1; }		//読み込み失敗
	//初期設定
	for (int i = 0; i < ENEMY_KIND; ++i)		//敵の数だけ初期設定
	{
		enemy[i]->StateSetInit();				//初期設定
	}

	//アイテム関係
	for (int i = 0; i < ITEM_KIND; ++i)	//アイテムの種類分だけ
	{
		item[i] = new ITEM();			//アイテム作成
	}
	//アイテムデータをcsvファイルから読み込み
	if (data->LoadItem(item, ITEM_DATA_DIR, ITEM_DATA_NAME) == false) { return -1; }		//読み込み失敗

	//マップ関係
	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ マップデータ読み込み開始 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	//フィールドマップ読み込み
	mapdata_field[(int)DRAW_FILED][(int)MAP_SOUGEN] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_SOUGEN);	//草原マップ生成
	if (mapdata_field[(int)DRAW_FILED][(int)MAP_SOUGEN]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_SOUGEN_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_FILED][(int)MAP_FOREST] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_FOREST);	//森マップ生成
	if (mapdata_field[(int)DRAW_FILED][(int)MAP_FOREST]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_FOREST_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_FILED][(int)MAP_OCEAN] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_OCEAN);		//海マップ生成
	if (mapdata_field[(int)DRAW_FILED][(int)MAP_OCEAN]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_OCEAN_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_FILED][(int)MAP_AUTUMN] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_AUTUMN);	//秋マップ生成
	if (mapdata_field[(int)DRAW_FILED][(int)MAP_AUTUMN]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_AUTUMN_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_FILED][(int)MAP_CITY] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_CITY_S);	//街、下マップ生成
	if (mapdata_field[(int)DRAW_FILED][(int)MAP_CITY]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_CITY_S_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_FILED][(int)MAP_SPRING] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_SPRING);			//春マップ生成
	if (mapdata_field[(int)DRAW_FILED][(int)MAP_SPRING]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_SPRING_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_FILED][(int)MAP_WINTER] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_WINTER);			//冬マップ生成
	if (mapdata_field[(int)DRAW_FILED][(int)MAP_WINTER]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_WINTER_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_FILED][(int)MAP_REMAINS] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_REMAINS);					//遺跡マップ生成
	if (mapdata_field[(int)DRAW_FILED][(int)MAP_REMAINS]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_REMAINS_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_FILED][(int)MAP_CASTLE] = new MAP(IMG_DIR_MAP_FIELD, IMG_NAME_MAP_CASTLE);					//魔王城マップ生成
	if (mapdata_field[(int)DRAW_FILED][(int)MAP_CASTLE]->LoadCsv(MY_MAP_FIELD_CSV_DIR, MY_MAP_CASTLE_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	//街マップ読み込み
	mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_NW] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_NW);	//北西マップ生成
	if (mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_NW]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_NW_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_W] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_W);	//西マップ生成
	if (mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_W]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_W_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_SW] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_SW);		//南西マップ生成
	if (mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_SW]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_SW_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_N] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_N);	//北マップ生成
	if (mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_N]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_N_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_CNETER] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_CENTER);	//中央マップ生成
	if (mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_CNETER]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_CENTER_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_S] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_S);			//南マップ生成
	if (mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_S]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_S_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_NE] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_NE);			//北東マップ生成
	if (mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_NE]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_NE_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_E] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_E);					//東マップ生成
	if (mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_E]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_E_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_SE] = new MAP(IMG_DIR_MAP_CITY, IMG_NAME_MAP_CITY_SE);					//南東マップ生成
	if (mapdata_field[(int)DRAW_CITY][(int)MAP_CITY_SE]->LoadCsv(MY_MAP_CITY_CSV_DIR, MY_MAP_CITY_SE_ATARI) == false) { return -1; }	//当たり判定読み込み失敗

	//マップの種類を二次元配列で管理
	for (int yoko = 0; yoko < MAP_DATA_YOKO_KIND; yoko++)
	{
		static int cnt = 0;
		for (int tate = 0; tate < MAP_DATA_TATE_KIND; tate++)
		{
			MapKind[tate][yoko] = cnt;
			cnt++;
		}
	}

	//現在のマップ位置を読み込んで設定
	if (data->LoadNowMap(&NowDrawMapKind, MapNowPos, MAPPOS_DATA_DIR, MAPPOS_DATA_NAME) == false) { return -1; }	//読み込み失敗
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ マップデータ読み込みここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 読み込み処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	while (TRUE)	//無限ループ
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了

		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		keydown->KeyDownUpdate();	//キーの入力状態を更新する

		fps->Update();				//FPSの処理[更新]

		if (GameEnd_Flg)		//ゲーム終了フラグが立っていたら
		{
			break;				//ループを抜け、ゲーム終了
		}

		//▼▼▼▼▼ゲームのシーンここから▼▼▼▼▼

		switch (GameSceneNow)
		{
		case (int)GAME_SCENE_TITLE:		//タイトル画面だったら
			
			Title();					//タイトル画面の処理

			break;

		case (int)GAME_SCENE_PLAY:		//プレイ画面だったら

			Play();						//プレイ画面の処理

			break;

		case (int)GAME_SCENE_BATTLE:	//戦闘画面だったら

			Battle();					//戦闘画面の処理

			break;

		case (int)GAME_SCENE_END:		//エンド画面だったら

			End();						//エンド画面の処理

			break;

		case (int)GAME_SCENE_CHENGE:	//シーン遷移画面だったら

			Chenge();					//シーン遷移画面の処理

			break;

		default:
			break;

		}


		//▲▲▲▲▲ゲームのシーンここまで▲▲▲▲▲

		//fps->Draw(0, 0);			//FPSの処理[描画]

		ScreenFlip();				//モニタのリフレッシュレートの速さで裏画面を再描画

		fps->Wait();				//FPSの処理[待つ]
	}

	Delete_Class();			//使用したクラスを破棄

	DxLib_End();			//ＤＸライブラリ使用の終了処理

	return 0;
}

//タイトル画面の処理
void Title()
{
	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 音の再生処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (bgm->GetIsPlay((int)TITLE_BGM) == false)	//再生中じゃないとき
	{
		bgm->ChengeVolume(255 * 50 / 100, (int)TITLE_BGM);	//BGMの音量を50%に変更
		bgm->Play((int)TITLE_BGM);				//BGMを再生
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 音の再生処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


	Title_Draw();		//タイトル画面の描画処理

	ui->ChoiseOperation(keydown);	//選択肢のキー操作

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (keydown->IsKeyDown(KEY_INPUT_RETURN))				//エンターキーを押されたら
	{
		if (*ui->GetNowChoise() == "START")		//選択している文字列が"START"だったら
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//次の画面はプレイ画面
		}
		else
		{
			GameEnd_Flg = true;	//ゲーム終了
		}
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 画面遷移の処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	return;
}

//プレイ画面の処理
void Play()
{

	player->Operation(keydown, mapdata_field[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->GetRect((int)MAP_NG));	//プレイヤーキー操作

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ マップ切り替え処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (player->GetChengeMapKind() != -1)		//マップの端に来た時
	{
		int chengekind = (int)MAP_CHENGE_NONE;	//マップ切り替えの種類

		//街へ移動するときは
		if (player->CheckDetectionMap(mapdata_field[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->GetRect((int)MAP_WARP)))
		{
			if (NowDrawMapKind == (int)DRAW_FILED)		//描画マップがフィールドだったら
			{
				NowDrawMapKind = (int)DRAW_CITY;		//描画マップを街へ切り替える
			}
			else if (NowDrawMapKind == (int)DRAW_CITY)	//描画マップが街だったら
			{
				NowDrawMapKind = (int)DRAW_FILED;		//描画マップをフィールドへ切り替える
			}

			IsChengeDrawMap = true;	//描画マップを切り替える
		}
		else		//移動しないときは
		{
			IsChengeDrawMap = false;	//描画マップを切り替えない
		}

		//マップの切り替え処理
		chengekind = mapdata_field[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->ChengeMap(player->GetChengeMapKind(), MapNowPos, IsChengeDrawMap);

		if (chengekind != (int)MAP_CHENGE_NONE)	//マップ切り替えを行ったときは
		{

			player->SetChengePos(chengekind);		//プレイヤーの位置を修正

			player->ResetChengeMapKind();			//マップ切り替えの種類リセット

		}
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ マップ切り替え処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	Play_Draw();		//描画処理

	if (player->GetIsMenu() == true && keydown->IsKeyDownOne(KEY_INPUT_Q))		//メニュー描画中でQキーを押された瞬間
	{
		player->SetIsMenu(false);		//メニュー描画終了
	}
	else if (keydown->IsKeyDownOne(KEY_INPUT_Q))		//Qキーを押された瞬間
	{
		player->SetIsMenu(true);		//メニュー描画開始
	}

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ メニュー毎の処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (player->GetIsMenu())			//メニュー描画中だったら
	{
		ui->ChoiseOperation(keydown);		//メニューウィンドウキー操作

		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
		{
			ui->SetChoiseMenu(ui->GetNowChoise());		//選択した内容をセット

		}

		if (ui->GetIsChoise())	//選択していたら
		{
			if (ui->GetChoiseMenu() == (int)MENU_SAVE)	//セーブを選んだ時
			{
				if (Wait())			//待ち時間が過ぎたら
				{
					data->Save(player, PLAYER_DATA_DIR, PLAYER_DATA_NAME);		//プレイヤー情報のセーブ
					data->SaveMap(NowDrawMapKind, MapNowPos, MAPPOS_DATA_DIR, MAPPOS_DATA_NAME);	//マップ位置のセーブ
					player->SetIsMenu(false);		//メニュー描画終了
				}

			}

		}

	}
	else			//メニュー描画終了してたら
	{
		ui->ResetMenu();	//メニュー関係のリセット
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ メニュー毎の処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲



	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

	if (player->GetIsMove())			//プレイヤーが移動中だったら
	{
		static int NowX = 0, NowY = 0;	//当たった場所を取得する

		if (player->CheckDetectionMap(mapdata_field[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->GetRect((int)MAP_ENCOUNT)))	//敵と遭遇するマップだったら
		{
			Enconte();			//敵との遭遇判定
		}
	}

	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 画面遷移の処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


	return;
}

//戦闘画面の処理
void Battle()
{

	Battle_Draw();			//描画処理

	switch (BattleStageNow)		//現在のバトル状態
	{

	case (int)WAIT_ACT:		//プレイヤーの行動選択待ち状態の時

		if (Turn == (int)MY_TURN)		//味方のターンだったら
		{
			bt_msg[(int)BT_MSG_ACT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//メッセージ描画
			if (bt_msg[(int)BT_MSG_ACT]->GetIsLastMsg())	//最後のメッセージだったら
			{

				ui->SetIsDrawUIAnime(false);		//UIのアニメーション非表示

				ui->ChoiseOperation(keydown);		//バトルコマンドキー操作

				if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
				{
					ui->SetBattleFlg();	//選択したコマンドを設定

				}

			}
			else
			{
				if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
				{
					bt_msg[(int)BT_MSG_ACT]->NextMsg();				//次のメッセージへ
				}
			}


			//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ バトルコマンド毎の処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
			switch (ui->GetChoiseCommamd())		//どのコマンドを選んだか
			{
			case (int)COMMANDE_ATACK:					//攻撃を選んだ時

				BattleStageNow = (int)DAMEGE_CALC;	//バトル状態をダメージ計算状態へ

				break;

			case (int)COMMANDE_DEFENSE:		//防御を選んだ時

				BattleStageNow = (int)DAMEGE_CALC;	//バトル状態をダメージ計算状態へ

				break;

			case (int)COMMANDE_MAGIC:		//魔法を選んだ時

				player->SetChoiseSkil((int)MAGIC_1);//使用する魔法を設定する
				BattleStageNow = (int)DAMEGE_CALC;	//バトル状態をダメージ計算状態へ

				break;

			case (int)COMMANDE_ITEM:			//アイテムを選んだ時

				ui->BattleInit();	//バトルコマンドリセット

				break;

			case (int)COMMANDE_ESCAPE:		//逃げるを選んだ時

				Work_Str = "上手く逃げ切れた！";
				bt_msg[(int)BT_MSG_ACT]->SetMsg(Work_Str.c_str());	//文字列設定

				BattleStageNow = (int)ACT_MSG;	//メッセージ描画状態
				
				break;

			default:
				break;
			}
			//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ バトルコマンド毎の処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

		} 
		else if (Turn = (int)ENEMY_TURN)	//敵のターンだったら
		{
			//敵の行動選択決定処理
			enemy[EncounteEnemyType]->ActDecision();		//行動決定処理

			BattleStageNow = (int)DAMEGE_CALC;	//ダメージ計算へ

		}

		break;						//行動選択待ち状態の処理ここまで

	case (int)DAMEGE_CALC:			//ダメージ計算状態の時

		if (Turn == (int)MY_TURN)		//味方のターンだったら
		{
			player->DamegeCalc(enemy[EncounteEnemyType],ui->GetChoiseCommamd());		//ダメージ計算

			//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ メッセージ設定処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

			ui->SetIsDrawUIAnime(true);			//UIのアニメーション表示

			//味方
			if (ui->GetChoiseCommamd() == (int)COMMANDE_DEFENSE)	//防御を選んだ時
			{
				Work_Str = player->GetName();					//味方の名前取得
				Work_Str += "は防御している！";
				bt_msg[(int)BT_MSG_ACT]->SetMsg(Work_Str.c_str());	//文字列設定
				Work_Str = "防御に集中している！";
				bt_msg[(int)BT_MSG_ACT]->AddMsg(Work_Str.c_str());	//文字列設定
			}
			else					//それ以外の時
			{
				Work_Str = player->GetName();					//味方の名前取得
				Work_Str += "の攻撃!";
				bt_msg[(int)BT_MSG_ACT]->SetMsg(Work_Str.c_str());	//文字列設定
				Work_Str = std::to_string(player->GetSendDamege());	//与えたダメージ取得
				Work_Str += "のダメージを与えた";
				bt_msg[(int)BT_MSG_ACT]->AddMsg(Work_Str.c_str());	//文字列設定
			}

			//敵
			Work_Str = enemy[EncounteEnemyType]->GetName();	//敵の名前取得
			Work_Str += "の攻撃!";
			bt_msg[(int)BT_MSG_ACT]->AddMsg(Work_Str.c_str());	//文字列設定
			Work_Str = std::to_string(player->GetRecvDamege());	//受けたダメージ取得
			Work_Str += "のダメージを受けた";
			bt_msg[(int)BT_MSG_ACT]->AddMsg(Work_Str.c_str());	//文字列設定
			//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ メッセージ設定処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

			BattleStageNow = (int)ACT_MSG;	//行動メッセージ表示状態へ

			ui->NowChoiseReset();		//選択を最初の要素へ戻す

		}
		else if (Turn = (int)ENEMY_TURN)	//敵のターンだったら
		{
			//ダメージ計算
			BattleStageNow = (int)ACT_MSG;	//行動メッセージ表示へ

		}

		break;						//ダメージ計算状態の時ここまで

	case (int)ACT_MSG:				//行動メッセージ表示状態

		bt_msg[(int)BT_MSG_ACT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//メッセージ描画

		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたら
		{
			if (Turn == (int)MY_TURN)		//味方のターンだったら
			{
				if (ui->GetChoiseCommamd() == (int)COMMANDE_ESCAPE)		//逃げるを選んだら
				{
					SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//次の画面はプレイ画面
				}
			}

			if (ui->GetChoiseCommamd() == (int)COMMANDE_DEFENSE)		//防御を選んだら
			{
				Magic_effect->SetIsDrawEnd(true);	//描画処理を飛ばすために、描画終了フラグを立てる
			}
			bt_msg[(int)BT_MSG_ACT]->NextMsg();	//次のメッセージへ
			BattleStageNow = (int)DRAW_EFFECT;	//エフェクト表示状態へ
		}

		break;						//行動メッセージ表示状態ここまで

	case (int)DRAW_EFFECT:			//エフェクト描画状態

		if (Turn == (int)MY_TURN)		//味方のターンだったら
		{
			if (ui->GetChoiseCommamd() == (int)COMMANDE_ATACK)	//攻撃を選んでいたら
			{
				//フェードアウトなしで描画
				Atack_effect->DrawNormal(ATK_DRAW_X, ATK_DRAW_Y, (int)NOMAL_ATACK);	//攻撃エフェクト描画

				if (bt_se->GetIsPlayed((int)BT_SE_SLASH) == false)		//再生済みでなければ
				{
					if (bt_se->GetIsPlay((int)BT_SE_SLASH) == false)		//再生中じゃなければ
					{
						bt_se->Play((int)BT_SE_SLASH);						//斬るときのSEを鳴らす
						bt_se->SetIsPlayed((int)BT_SE_SLASH,true);			//再生済み
					}

				}

			}
			else if (ui->GetChoiseCommamd() == (int)COMMANDE_MAGIC)	//魔法を選んでいたら
			{
				//フェードアウトなしで描画
				Magic_effect->DrawNormal((GAME_WIDTH / 2 - MAGIC_WIDTH / 2), (GAME_HEIGHT / 2 - MAGIC_HEIGHT / 2), player->GetChoiseSkil());	//魔法エフェクト描画
			
				if (bt_se->GetIsPlayed((int)BT_SE_THUNDER) == false)		//再生済みでなければ
				{
					if (bt_se->GetIsPlay((int)BT_SE_THUNDER) == false)		//再生中じゃなければ
					{
						bt_se->Play((int)BT_SE_THUNDER);						//雷のSEを鳴らす
						bt_se->SetIsPlayed((int)BT_SE_THUNDER, true);			//再生済み
					}

				}


			}

			if (Magic_effect->GetIsDrawEnd()||Atack_effect->GetIsDrawEnd())		//エフェクト描画が終了したら
			{

				BattleStageNow = (int)DRAW_DAMEGE;		//ダメージ描画状態へ

				enemy[EncounteEnemyType]->SetHP((enemy[EncounteEnemyType]->GetHP() - player->GetSendDamege()));	//ダメージを与える

			}

		}
		else if (Turn = (int)ENEMY_TURN)	//敵のターンだったら
		{
			//敵のエフェクト表示
			Enemy_Atk_effect->Draw((GAME_WIDTH / 2 - Enemy_Atk_effect->GetWidth(enemy[EncounteEnemyType]->GetChoiseSkil()) / 2),
				(GAME_HEIGHT / 2 - Enemy_Atk_effect->GetHeight(enemy[EncounteEnemyType]->GetChoiseSkil()) / 2),
				enemy[EncounteEnemyType]->GetChoiseSkil());

			if (Enemy_Atk_effect->GetIsDrawEnd())		//エフェクト描画終了したら
			{
				player->SetHP((player->GetHP()) - (player->GetRecvDamege()));		//味方にダメージを与える

				if (player->GetHP() <= 0)			//HPが0以下になったら
				{
					player->SetHP(0);				//HPを0にする
				}

				BattleStageNow = (int)DRAW_DAMEGE;	//ダメージ描画状態へ

			}

		}

		break;

	case (int)DRAW_DAMEGE:				//ダメージ描画状態
		
		//ダメージ描画
		bt_msg[(int)BT_MSG_ACT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//メッセージ描画

		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
		{

			bt_se->Reset();	//SEの再生状態をリセット

			if (Turn == (int)MY_TURN)			//味方のターンの時
			{
				if (ui->GetChoiseCommamd() == (int)COMMANDE_ATACK)	//攻撃を選んだ時は
				{
					Atack_effect->ResetIsAnime((int)NOMAL_ATACK);		//攻撃エフェクトリセット
				}
				else							//攻撃以外を選んだ時は
				{
					Magic_effect->ResetIsAnime(player->GetChoiseSkil());//魔法エフェクトリセット
				}

				Turn = (int)ENEMY_TURN;				//敵のターンへ

			}
			else if (Turn == (int)ENEMY_TURN)			//敵のターンの時
			{

				Work_Str = "どうする？";
				bt_msg[(int)BT_MSG_ACT]->SetMsg(Work_Str.c_str());	//文字列設定

				Enemy_Atk_effect->ResetIsAnime(enemy[EncounteEnemyType]->GetChoiseSkil());		//エフェクトリセット
				Turn = (int)MY_TURN;				//味方のターンへ
			}

			if (player->GetHP() <= 0)			//自分のHPが0になったら
			{
				player->SetIsArive(false);		//自分死亡
				player->SetIsBattleWin(false);	//戦闘に敗北

				//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ リザルトメッセージ設定処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
				Work_Str = "全滅してしまった…";
				bt_msg[(int)BT_MSG_RESULT]->SetMsg(Work_Str.c_str());	//文字列設定
				//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ リザルトメッセージ設定処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

				BattleStageNow = (int)RESULT_MSG;		//リザルトメッセージ表示状態へ

			}
			else if (enemy[EncounteEnemyType]->GetHP() <= 0)				//敵のHPが0になったら
			{
				enemy[EncounteEnemyType]->SetIsArive(false);		//敵死亡
				player->SetIsBattleWin(true);						//戦闘に勝利
				player->AddExp(enemy[EncounteEnemyType]->GetEXP());	//経験値加算

				//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ リザルトメッセージ設定処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
				Work_Str = enemy[EncounteEnemyType]->GetName();
				Work_Str += "を倒した！";
				bt_msg[(int)BT_MSG_RESULT]->SetMsg(Work_Str.c_str());	//文字列設定
				Work_Str = std::to_string(enemy[EncounteEnemyType]->GetEXP());
				Work_Str += "の経験値を手に入れた！";
				bt_msg[(int)BT_MSG_RESULT]->AddMsg(Work_Str.c_str());	//文字列設定

				if (player->GetLevUpMsgStartFlg())		//レベルアップしたときは
				{
					Work_Str = "レベル";
					Work_Str += std::to_string(player->GetLevel());	//レベル取得
					Work_Str += "になった！";
					bt_msg[(int)BT_MSG_RESULT]->AddMsg(Work_Str.c_str());	//文字列設定
				}
				//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ リザルトメッセージ設定処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

				BattleStageNow = (int)RESULT_MSG;		//リザルトメッセージ表示状態へ

			}
			else
			{
				BattleStageNow = (int)WAIT_ACT;		//行動選択状態へ
			}

			bt_msg[(int)BT_MSG_ACT]->NextMsg();	//次のメッセージへ

			ui->BattleInit();				//バトルコマンドリセット

		}

		break;

	case (int)RESULT_MSG:		//戦闘終了後のメッセージを描画する状態

		bt_msg[(int)BT_MSG_RESULT]->DrawMsg(BT_MSG_DRAW_X, BT_MSG_DRAW_Y, GetColor(255, 255, 255));	//メッセージ描画

		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))		//エンターキーを押されたとき
		{

			bt_msg[(int)BT_MSG_RESULT]->NextMsg();	//次のメッセージへ

			if (bt_msg[(int)BT_MSG_RESULT]->GetIsLastMsg())		//最後のメッセージだったら
			{
				if (player->GetLevUpMsgStartFlg())			//レベルアップしていたら
				{
					if (bt_se->GetIsPlay((int)BT_SE_LEVELUP) == false)		//再生中じゃなければ
					{
						bt_se->Play((int)BT_SE_LEVELUP);	//レベルアップのSEを鳴らす
						bt_se->SetIsPlayed((int)BT_SE_SLASH,true);			//再生済み
						player->SetLevUpMsgStartFlg(false);	//レベルアップ終了
					}
				}

				if (bt_msg[(int)BT_MSG_RESULT]->GetIsMsgEnd())	//全てのメッセージ描画が終了したら
				{
					if (player->GetIsBattleWin())		//戦闘に勝利していたら
					{
						SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//次の画面はプレイ画面
					}
					else if (player->GetIsBattleWin() == false)	//戦闘に敗北していたら
					{
						SceneChenge(GameSceneNow, (int)GAME_SCENE_END);	//次の画面はエンド画面
					}

					BattleStageNow = (int)WAIT_ACT;		//行動選択待ち状態へ

				}

			}

		}

		break;					//戦闘終了後のメッセージを描画する状態の処理ここまで

	default:

		break;

	}

	if (keydown->IsKeyDown(KEY_INPUT_R))		//Rキー押されたら
	{
		back_battle->ChengeImage(NIGHT);		//背景画像を（夜）に変更
	}

	return;
}

//エンド画面の処理
void End()
{

	End_Draw();	//描画処理

	ui->ChoiseOperation(keydown);	//選択肢のキー操作

	player->Recovery();		//回復

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (keydown->IsKeyDown(KEY_INPUT_RETURN))	//エンターキーを押された瞬間
	{
		if (*ui->GetNowChoise() == "TITLE")		//選択している文字列が"TITLE"だったら
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_TITLE);	//次の画面はタイトル画面
		}
		else if (*ui->GetNowChoise() == "PLAY")	//プレイを選択したら
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//次の画面はプレイ画面
		}
		else
		{
			GameEnd_Flg = true;	//ゲーム終了
		}
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 画面遷移の処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	return;
}

//画面遷移の演出をする処理
void Chenge()
{
	static const int ChengeDrawCountMax = 60;	//フェードイン処理に使用

	switch (GameSceneBefor)		//どの画面からの遷移かで処理を分ける
	{
	case (int)GAME_SCENE_TITLE:	//タイトル画面からの遷移だったら

		Title_Draw();		//タイトル画面の描画処理

		break;

	case (int)GAME_SCENE_PLAY:	//プレイ画面からの遷移だったら

		Play_Draw();		//プレイ画面の描画処理

		break;

	case (int)GAME_SCENE_BATTLE://戦闘画面からの遷移だったら

		Battle_Draw();		//戦闘画面の描画処理

		break;

	case (int)GAME_SCENE_END:	//エンド画面からの遷移だったら

		End_Draw();			//エンド画面の描画処理

		break;

	default:
		break;
	}

	//フェードアウトの処理
	double ToukaPercent = ChengeDrawCount / (double)ChengeDrawCountMax;//透過％を求める
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * 255);	//透過させる
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);	//真っ暗な画面にする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//透過をやめる

	//60フレーム分、待つ
	if (ChengeDrawCount < ChengeDrawCountMax)
	{
		ChengeDrawCount++;
	}
	else
	{
		GameSceneNow = GameSceneNext;	//次の画面にする
		Init();							//初期化
		ui->ChoiseClear();				//選択肢の内容をクリアする
	}


	return;

}

//初期化処理
void Init()
{
	ChengeDrawCount = 0;		//フェードイン用初期化

	if (GameSceneBefor == (int)GAME_SCENE_BATTLE)	//戦闘画面から遷移した場合
	{
		enemy[EncounteEnemyType]->StateSetInit();		//遭遇した敵初期化

		ui->BattleInit();			//バトルコマンド初期化

		bt_se->Reset();				//SEの再生状態をリセット

		EncounteEnemyType = 0;		//遭遇した敵の種類をリセット

		BattleStageNow = (int)WAIT_ACT;	//バトル状態を、行動待ち状態へ

		Turn = (int)MY_TURN;		//ターンを味方のターンに設定

		for (int i = 0; i < BT_MSG_KIND; ++i)	//メッセージの種類分
		{
			bt_msg[i]->ResetFlg();		//フラグリセット
		}

	}
}

//シーンを変更する処理
void SceneChenge(int beforscene, int nextscene)
{
	GameSceneBefor = beforscene;				//現在のゲームシーンを前のゲームシーンとして保存
	GameSceneNow = (int)GAME_SCENE_CHENGE;		//遷移画面に変更
	GameSceneNext = nextscene;					//次のシーンを指定
	return;
}

//タイトル画面の描画処理
void Title_Draw()
{
	back->Draw(GAME_LEFT, GAME_TOP,(int)TITLE_BACK);	//背景画像描画

	title->Draw(GAME_LEFT, GAME_HEIGHT / 2 - title->GetHeight(0) / 2);		//画面中央にタイトル描画

	font->SetSize(BIG_FONTSIZE);		//フォントサイズを大きくする

	ui->ChoiseDraw(GAME_WIDTH / 2 , DEFAULT_TEXT_Y,(int)UI_TRIANGLE,true,GetColor(255,255,255),"START", "END");	//選択肢描画
	
	return;

}

//プレイ画面の描画処理
void Play_Draw()
{
	font->SetSize(DEFAULT_FONTSIZE);	//フォントサイズを標準に戻す

	mapdata_field[NowDrawMapKind][MapKind[MAPPOS_Y][MAPPOS_X]]->Draw();	//マップ描画

	player->DrawAnime();		//アニメーション描画

	static int Player_X = 0, Player_Y = 0;	//プレイヤーのX位置とY位置

	player->GetNowPos(&Player_X, &Player_Y);//プレイヤーの現在位置を取得

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ メニュー描画処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (player->GetIsMenu())	//メニュー描画中なら
	{
		ui->DrawMenu(Player_X,Player_Y);	//メニューウィンドウ描画

		if (ui->GetIsChoise())	//選択したら
		{

			ui->DrawWindow(GAME_LEFT, GAME_TOP, GAME_WIDTH, GAME_HEIGHT);	//ウィンドウ描画

			switch (ui->GetChoiseMenu())		//選んだ内容ごとに処理を分ける
			{

			case (int)MENU_STATUS:	//ステータスを選んだ時の処理ここから

				//ステータス描画
				DrawFormatString(GAME_LEFT, GAME_TOP, GetColor(255, 255, 255), "%s\nHP %d/%d\nMP %d/%d\nATK %d\nDEF %d\nSPD %d",
					player->GetName(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetATK(), player->GetDEF(), player->GetSPD());

				break;				//ステータスを選んだ時の処理ここまで

			case (int)MENU_ITEM:	//アイテムを選んだ時の処理ここから

				//アイテム描画処理
				for (int cnt = 0; cnt < ITEM_KIND; ++cnt)
				{
					DrawFormatString(GAME_LEFT, cnt * MENU_SPACE, GetColor(255, 255, 255), "%s %s\n", item[cnt]->GetName(), item[cnt]->GetDescription());
				}

				break;				//アイテムを選んだときの処理ここまで

			case (int)MENU_SOUBI:	//装備を選んだ時の処理ここから

				//装備描画処理
				DrawString(400, 300, "装備描画", GetColor(255, 255, 255));	//文字描画

				break;				//装備を選んだ時の処理ここまで

			case (int)MENU_SETUMEI:	//操作説明を選んだ時の処理ここから

				//操作説明描画処理
				setumei->Draw(GAME_LEFT, GAME_TOP);	//説明画像の描画
				if (keydown->IsKeyDownOne(KEY_INPUT_E))	//Eキーを押されたら
				{
					ui->ResetMenu();	//メニューリセット
				}

				break;				//操作説明を選んだ時の処理ここまで

			case (int)MENU_SAVE:	//セーブを選んだ時の処理ここから

				//セーブ時の描画処理
				DrawString(400, 300, "セーブ中です。", GetColor(255, 255, 255));	//文字描画

				break;				//セーブを選んだ時の処理ここまで

			default:
				break;
			}

		}
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ メニュー描画処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	return;

}

//戦闘画面の描画処理
void Battle_Draw()
{

	back_battle->Draw(GAME_LEFT, GAME_TOP);	//背景画像を描画

	enemy[EncounteEnemyType]->Draw();	//敵描画

	ui->DrawStateWindow(player);		//ステータスウィンドウ描画

	ui->DrawCommand();						//バトルコマンド描画

	ui->DrawUiImage(BT_WINDOW_X, BT_WINDOW_Y, (int)UI_WINDOW);	//メッセージウィンドウ描画

	ui->DrawUiAnime(ui->GetUiImageWidth((int)UI_WINDOW) / 2 - TXT_POSE_WIDTH / 2, BT_TXT_POSE_Y);		//テキストポーズ描画

	return;

}

//エンド画面の描画処理
void End_Draw()
{

	back->Draw(GAME_LEFT, GAME_TOP, (int)END_BACK);	//背景画像描画

	font->SetSize(BIG_FONTSIZE);	//フォントサイズを大きくする

	ui->ChoiseDraw(GAME_WIDTH / 2, TXT_Y_3, (int)UI_TRIANGLE,true ,GetColor(0,0,0),"TITLE","PLAY", "END");	//選択肢描画

	return;

}

//敵との遭遇処理
void Enconte()
{

	for (int i = 0; i < ENEMY_KIND; ++i)		//敵の分だけループする
	{
		if (enemy[i]->GetEmergenceMap() == MapKind[MAPPOS_Y][MAPPOS_X])		//敵の出現MAPが現在のMAPだったら
		{
			//ランダムで遭遇判定
			int rand = GetRand(enemy[i]->GetEncounteRate());		//遭遇率の範囲内で乱数を生成

			if (rand%enemy[i]->GetEncounteRate() == 0)			//敵と遭遇した時
			{

				player->SetIsKeyDown(false);			//プレイヤーの動きを止める

				EncounteEnemyType = i;		//遭遇した敵を設定

				//描画文字設定
				Work_Str = "バイト帰りの";
				Work_Str += enemy[EncounteEnemyType]->GetName();		//遭遇した敵の名前取得
				Work_Str += "が現れた！";
				bt_msg[(int)BT_MSG_ACT]->SetMsg(Work_Str.c_str());	//文字列設定
				Work_Str = "どうする？";
				bt_msg[(int)BT_MSG_ACT]->AddMsg(Work_Str.c_str());	//文字列設定

				SceneChenge(GameSceneNow, (int)GAME_SCENE_BATTLE);	//次の画面は戦闘画面

			}
		}
	}


	return;

}

//待つ処理
/*
戻り値：true：待つ時間が過ぎたら
戻り値：false：待っているとき
*/
bool Wait()
{
	static int WaitCnt = 0;		//カウント用
	static int WaitCntMax = 60;	//待つ最大値

	if (WaitCnt == WaitCntMax)		//待つ時間が過ぎたら
	{
		WaitCnt = 0;	//カウントリセット
		return true;
	}
	else
	{
		++WaitCnt;		//カウントアップ
		return false;
	}
}

//ゲーム内で使用したクラスを削除する処理
void Delete_Class()
{
	delete title;			//titleを破棄
	delete setumei;			//setumeiを破棄
	delete fps;				//FPSを破棄
	delete keydown;			//keydownを破棄
	delete font;			//fontを破棄
	delete bgm;				//bgmを破棄
	delete bt_se;				//seを破棄
	delete player;			//playerを破棄
	delete back;			//backを破棄
	delete back_battle;		//back_battleを破棄
	delete data;			//dataを破棄
	delete Magic_effect;			//effectを破棄

	delete msg;//msg破棄

	//メッセージの削除
	for (int i = 0; i < BT_MSG_KIND; ++i)
	{
		delete bt_msg[i];				//bt_msgを破棄
	}

	//マップデータの削除
	for (int cnt = 0; cnt < DRAW_MAP_KIND; ++cnt)
	{
		for (int i = 0; i < MAP_DATA_KIND; i++)	//マップの種類分
		{
			delete mapdata_field[cnt][i];	//mapdataを破棄
		}

	}

	//敵の削除
	for (int i = 0; i < ENEMY_KIND; ++i)	//敵の種類分
	{
		delete enemy[i];			//enemyを破棄
	}

	//アイテムの削除
	for (int i = 0; i < ITEM_KIND; ++i)	//アイテムの種類分
	{
		delete item[i];				//itemを破棄
	}

	return;

}
