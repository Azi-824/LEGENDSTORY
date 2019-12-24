/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* main.cpp     																				　 */

//##########ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "main.hpp"
#include "FPS.hpp"
#include "KEYDOWN.hpp"
#include "IMAGE.hpp"
#include "ANIMATION.hpp"
#include "FONT.hpp"
#include "CHARACTOR.hpp"
#include "COLLISION.hpp"
#include "PLAYER.hpp"
#include "MAP.hpp"
#include "MAPIMAGE.hpp"
#include "TEXTSTR.hpp"
#include "MUSIC.hpp"
#include "ENEMY.hpp"
#include "UI.hpp"
#include "DATA.hpp"
#include "EFFECT.hpp"
#include "MSG.hpp"

//########## グローバルオブジェクト ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPSクラスのオブジェクトを生成
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWNクラスのオブジェクトを生成

IMAGE *title;						//タイトル画像
IMAGE *back;						//背景画像
IMAGE *back_battle;					//戦闘画面の背景画像

MUSIC *bgm;							//BGM
MUSIC *se;							//SE

EFFECT *effect;						//エフェクト

FONT *font;							//フォント
TEXTSTR *text;						//文字列
UI *ui;								//UI
DATA *data;							//データ
MESSAGE *msg;						//メッセージ

PLAYER *player;						//主人公

ENEMY *enemy[ENEMY_KIND];			//敵

MAPIMAGE *mapimage;					//マップチップのデータ
MAP *mapdata[MAP_DATA_KIND][MAP_LAYER_KIND];		//マップデータ

//############## グローバル変数 ##############
int GameSceneNow = (int)GAME_SCENE_TITLE;	//現在のゲームシーン
int GameSceneBefor;							//前のゲームシーン
int GameSceneNext;							//次のゲームシーン

int BattleStageNow = (int)WAIT_ACT;	//バトルシーンの現在の状態
int BattleActMsgCnt = 0;		//行動メッセージカウント
int BattleActMsgCntMax = 60;	//行動メッセージの表示時間

int MapKind[MAP_DATA_TATE_KIND][MAP_DATA_YOKO_KIND];			//マップの種類
int MapNowPos[2] = {0};								//現在のマップのX位置とY位置を格納

int ChengeDrawCount = 0;	//フェードアウト処理に使用

int EncounteEnemyType = 0;	//遭遇した敵の種類
int Turn = (int)MY_TURN;	//ターン

bool StrSet_Flg = false;					//文字列設定フラグ
bool GameEnd_Flg = false;					//ゲーム終了フラグ


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

	title = new IMAGE(MY_IMG_DIR_TITLE, MY_ING_NAME_TITLE);			//タイトル画像を生成
	if (title->GetIsLoad() == false) { return -1; }					//読み込み失敗時

	back = new IMAGE(MY_IMG_DIR_BACK, MY_IMG_NAME_BACK);			//背景画像を生成
	if (back->GetIsLoad() == false) { return -1; }					//読み込み失敗時

	back_battle = new IMAGE(MY_IMG_DIR_BATTLE, MY_IMG_NAME_BATTLE_NORMAL);	//戦闘画面の背景画像読み込み
	if (back_battle->GetIsLoad() == false) { return -1; }					//読み込み失敗
	back_battle->AddImage(MY_IMG_DIR_BATTLE, MY_IMG_NAME_BATTLE_NIGHT);		//戦闘画面（夜）の背景画像の読み込み
	if (back_battle->GetIsLoad() == false) { return -1; }					//読み込み失敗

	//音関係
	bgm = new MUSIC(MY_MUSIC_DIR_BGM, MY_MUSIC_NAME_BGM,BGM_KIND);			//BGMを生成
	if (bgm->GetIsLoad() == false) { return -1; }					//読み込み失敗時
	se = new MUSIC(MY_MUSIC_DIR_SE, MY_SE_NAME_LEVUP, SE_KIND);			//SEを生成
	if (se->GetIsLoad() == false) { return -1; }						//読み込み失敗時
	se->ChengePlayType(DX_PLAYTYPE_BACK);								//再生方法変更

	font = new FONT(MY_FONT_DIR, MY_FONT_NAME2, FONT_NAME2);			//フォントを生成
	if (font->GetIsLoad() == false) { return -1; }					//読み込み失敗時

	text = new TEXTSTR();	//テキスト作成
	data = new DATA();
	msg = new MESSAGE();		//メッセージ

	//エフェクト関係
	effect = new EFFECT(MY_ANIME_DIR_ATKEFECT, MY_ANIME_NAME_ATKEFECT, ATK_ALL_CNT, ATK_YOKO_CNT, ATK_TATE_CNT, ATK_WIDTH, ATK_HEIGHT, ATK_SPEED, false);
	if (effect->GetIsLoad() == false) { return -1; }		//読み込み失敗
	if (effect->Add(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC, MAGIC_ALL_CNT, MAGIC_YOKO_CNT, MAGIC_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC_SPEED, false, (int)MAGIC_1) == false) { return -1; }	//読み込み失敗
	if (effect->Add(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC2, MAGIC2_ALL_CNT, MAGIC2_YOKO_CNT, MAGIC2_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGIC_SPEED, false, (int)MAGIC_2) == false) { return -1; }	//読み込み失敗
	
	//プレイヤー関係
	player = new PLAYER();		//プレイヤー生成
	if (player->SetImage(MY_IMG_DIR_CHARCTOR, MY_IMG_NAME_PLAYER) == false) { return -1; }	//読み込み失敗
	if (player->SetAnime(MY_ANIME_DIR_PLAYER, MY_ANIME_NAME_PLAYER, PLAYER_ALL_CNT, PLAYER_YOKO_CNT, PLAYER_TATE_CNT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_ANI_SPEED, true) == false) { return -1; } //読み込み失敗
	
	data->Load(player, PLAYER_DATA_DIR, PLAYER_DATA_NAME);	//プレイヤーのデータをcsvファイルから読み込み
	player->SetInit();	//初期設定

	ui = new UI();		//UI作成

	//敵関係
	enemy[SLIME] = new ENEMY(ENEMY_DIR, ENEMY_NAME_SLIME);	//スライム作成
	if (enemy[SLIME]->GetIsLoad() == false) { return -1; }	//読み込み失敗

	enemy[YADOKARI]=new ENEMY(ENEMY_DIR, ENEMY_NAME_YADOKARI);	//ヤドカリ作成
	if (enemy[YADOKARI]->GetIsLoad() == false) { return -1; }	//読み込み失敗

	data->Load(enemy, ENEMY_DATA_DIR, ENEMY_DATA_NAME);		//敵のデータをcsvファイルから読み込み
	enemy[SLIME]->StateSetInit();		//初期ステータス設定
	enemy[YADOKARI]->StateSetInit();	//初期ステータス設定

	//マップ関係
	mapimage = new MAPIMAGE();	//マップチップ生成
	if (mapimage->GetIsLoad() == false) { return -1; }	//読み込み失敗

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ マップデータ読み込み開始 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	mapdata[MAP_1][FIRST_LAYER] = new MAP();	//一層目のマップデータ生成
	if (mapdata[MAP_1][FIRST_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_1_1) == false) { return -1; }		//読み込み失敗

	mapdata[MAP_1][SECOND_LAYER] = new MAP();	//二層目のマップデータ生成
	if (mapdata[MAP_1][SECOND_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_1_2) == false) { return -1; }	//読み込み失敗

	mapdata[MAP_2][FIRST_LAYER] = new MAP();	//一層目のマップデータ生成
	if (mapdata[MAP_2][FIRST_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_2_1) == false) { return -1; }		//読み込み失敗

	mapdata[MAP_2][SECOND_LAYER] = new MAP();	//二層目のマップデータ生成
	if (mapdata[MAP_2][SECOND_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_2_2) == false) { return -1; }	//読み込み失敗

	mapdata[MAP_3][FIRST_LAYER] = new MAP();	//一層目のマップデータ生成
	if (mapdata[MAP_3][FIRST_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_3_1) == false) { return -1; }		//読み込み失敗

	mapdata[MAP_3][SECOND_LAYER] = new MAP();	//二層目のマップデータ生成
	if (mapdata[MAP_3][SECOND_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_3_2) == false) { return -1; }	//読み込み失敗

	mapdata[MAP_4][FIRST_LAYER] = new MAP();	//一層目のマップデータ生成
	if (mapdata[MAP_4][FIRST_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_4_1) == false) { return -1; }		//読み込み失敗

	mapdata[MAP_4][SECOND_LAYER] = new MAP();	//二層目のマップデータ生成
	if (mapdata[MAP_4][SECOND_LAYER]->LoadCsv(MY_MAP_DIR, MY_MAP_4_2) == false) { return -1; }	//読み込み失敗

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

		fps->Draw(0, 0);				//FPSの処理[描画]

		ScreenFlip();				//モニタのリフレッシュレートの速さで裏画面を再描画

		fps->Wait();				//FPSの処理[待つ]
	}

	data->Save(player, PLAYER_DATA_DIR, PLAYER_DATA_NAME);		//プレイヤー情報のセーブ

	delete title;			//titleを破棄
	delete fps;				//FPSを破棄
	delete keydown;			//keydownを破棄
	delete font;			//fontを破棄
	delete text;			//textを破棄
	delete bgm;				//bgmを破棄
	delete se;				//seを破棄
	delete player;			//playerを破棄
	delete back;			//backを破棄
	delete back_battle;		//back_battleを破棄
	delete mapimage;		//mapimageを破棄
	delete data;			//dataを破棄
	delete effect;			//effectを破棄
	delete msg;				//msgを破棄

	//マップデータの削除
	for (int i = 0; i < MAP_DATA_KIND; i++)
	{
		for (int cnt = 0; cnt < MAP_LAYER_KIND; cnt++)
		{
			delete mapdata[i][cnt];	//mapdataを破棄
		}

	}

	//敵の削除
	for (int i = 0; i < ENEMY_KIND; ++i)
	{
		delete enemy[i];			//enemyを破棄
	}

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

	if (keydown->IsKeyDown(KEY_INPUT_S))	//Sキーを押されたら
	{
		text->Next();	//選択を一つ次へ
	}
	else if (keydown->IsKeyDown(KEY_INPUT_W))	//Wキーを押されたら
	{
		text->Back();	//選択を一つ前へ
	}

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (keydown->IsKeyDown(KEY_INPUT_RETURN))				//エンターキーを押されたら
	{
		if (*text->GetPos() == "START")		//選択している文字列が"START"だったら
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
	player->Operation(keydown);	//プレイヤーキー操作

	Play_Draw();		//描画処理

	if (player->GetIsMenu() == true && keydown->IsKeyDownOne(KEY_INPUT_Q))		//メニュー描画中でQキーを押された瞬間
	{
		player->SetIsMenu(false);		//メニュー描画終了
	}
	else if (keydown->IsKeyDownOne(KEY_INPUT_Q))		//Qキーを押された瞬間
	{
		player->SetIsMenu(true);		//メニュー描画開始
	}

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

	if (player->GetIsMove())			//プレイヤーが移動中だったら
	{
		Enconte();			//敵との遭遇判定
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
			ui->BattleOperation(keydown);			//戦闘画面のキー操作

			//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ バトルコマンド毎の処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
			switch (ui->GetChoiseCommamd())		//どのコマンドを選んだか
			{
			case (int)ATACK:					//攻撃を選んだ時

				BattleStageNow = (int)DAMEGE_CALC;	//バトル状態をダメージ計算状態へ

				break;

			case (int)DEFENSE:		//防御を選んだ時

				ui->BattleInit();	//バトルコマンドリセット

				break;

			case (int)MAGIC:		//魔法を選んだ時

				player->SetChoiseSkil(1);			//使用するスキルを魔法に設定する
				BattleStageNow = (int)DAMEGE_CALC;	//バトル状態をダメージ計算状態へ

				break;

			case (int)ITEM:			//アイテムを選んだ時

				ui->BattleInit();	//バトルコマンドリセット

				break;

			case (int)ESCAPE:		//逃げるを選んだ時

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

			BattleStageNow = (int)DAMEGE_CALC;	//ダメージ計算へ

		}

		break;						//行動選択待ち状態の処理ここまで

	case (int)DAMEGE_CALC:			//ダメージ計算状態の時

		if (Turn == (int)MY_TURN)		//味方のターンだったら
		{
			player->DamegeCalc(enemy[EncounteEnemyType]);		//ダメージ計算

			BattleStageNow = (int)ACT_MSG;	//行動メッセージ表示状態へ

		}
		else if (Turn = (int)ENEMY_TURN)	//敵のターンだったら
		{
			//ダメージ計算

			BattleStageNow = (int)ACT_MSG;	//行動メッセージ表示へ

		}

		break;						//ダメージ計算状態の時ここまで

	case (int)ACT_MSG:				//行動メッセージ表示状態

		if (Wait())			//表示秒数になったら
		{
			if (Turn == (int)MY_TURN)		//味方のターンだったら
			{
				if (ui->GetChoiseCommamd() == (int)ESCAPE)		//逃げるを選んだら
				{
					SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//次の画面はプレイ画面
				}

			}

			BattleStageNow = (int)DRAW_EFFECT;			//エフェクト描画状態へ

		}

		break;						//行動メッセージ表示状態ここまで

	case (int)DRAW_EFFECT:			//エフェクト描画状態

		if (Turn == (int)MY_TURN)		//味方のターンだったら
		{
			if (ui->GetChoiseCommamd() == (int)ATACK)	//攻撃を選んでいたら
			{
				effect->Draw(350, 250, (int)NOMAL_ATACK);	//攻撃エフェクト描画
			}
			else if (ui->GetChoiseCommamd() == (int)MAGIC)	//魔法を選んでいたら
			{
				effect->Draw((GAME_WIDTH / 2 - MAGIC_WIDTH / 2), (GAME_HEIGHT / 2 - MAGIC_HEIGHT / 2), player->GetChoiseSkil());	//魔法エフェクト描画
			}

			if (effect->GetIsDrawEnd())		//エフェクト描画が終了したら
			{

				BattleStageNow = (int)DRAW_DAMEGE;		//ダメージ描画状態へ

				enemy[EncounteEnemyType]->SetHP((enemy[EncounteEnemyType]->GetHP() - player->GetSendDamege()));	//ダメージを与える

			}

		}
		else if (Turn = (int)ENEMY_TURN)	//敵のターンだったら
		{
			//敵のエフェクト表示
			effect->Draw((GAME_WIDTH / 2 - MAGIC_WIDTH / 2), (GAME_HEIGHT / 2 - MAGIC_HEIGHT / 2), enemy[EncounteEnemyType]->GetSkil());

			if (effect->GetIsDrawEnd())		//エフェクト描画終了したら
			{
				player->SetHP((player->GetHP()) - (player->GetRecvDamege()));		//味方にダメージを与える

				ui->SetStateWindow(player->GetLevel(),player->GetHP(),player->GetMP());	//描画ステータス更新

				BattleStageNow = (int)DRAW_DAMEGE;		//ダメージ描画状態へ

			}

		}

		break;

	case (int)DRAW_DAMEGE:				//ダメージ描画状態

		//ダメージ描画
		if (Wait())				//表示秒数になったら
		{
			if (Turn == (int)MY_TURN)			//味方のターンの時
			{
				if (ui->GetChoiseCommamd() == (int)ATACK)	//攻撃を選んだ時は
				{
					effect->ResetIsAnime((int)NOMAL_ATACK);		//エフェクトリセット
				}
				else							//攻撃以外を選んだ時は
				{
					effect->ResetIsAnime(player->GetChoiseSkil());		//エフェクトリセット
				}

				Turn = (int)ENEMY_TURN;				//敵のターンへ

			}
			else if (Turn == (int)ENEMY_TURN)			//敵のターンの時
			{
				effect->ResetIsAnime(enemy[EncounteEnemyType]->GetSkil());		//エフェクトリセット
				Turn = (int)MY_TURN;				//味方のターンへ

			}

			if (player->GetHP() <= 0)			//自分のHPが0になったら
			{
				player->SetIsArive(false);		//自分死亡

				player->SetIsBattleWin(false);	//戦闘に敗北

				BattleStageNow = (int)RESULT_MSG;		//リザルトメッセージ表示状態へ
			}
			else if (enemy[EncounteEnemyType]->GetHP() <= 0)				//敵のHPが0になったら
			{
				enemy[EncounteEnemyType]->SetIsArive(false);		//敵死亡

				player->SetIsBattleWin(true);		//戦闘に勝利

				player->AddExp(enemy[EncounteEnemyType]->GetEXP());	//経験値加算

				BattleStageNow = (int)RESULT_MSG;		//リザルトメッセージ表示状態へ
			}
			else
			{
				BattleStageNow = (int)WAIT_ACT;		//行動選択状態へ
			}

			ui->BattleInit();				//バトルコマンドリセット

		}

		break;

	case (int)RESULT_MSG:		//戦闘終了後のメッセージを描画する状態

		if (msg->GetDrawMsgKind()==(int)LEVELUP_MSG && se->GetIsPlayEnd()==false)	//レベルアップしたときは
		{
			if (se->GetIsPlay((int)LEVELUP_SE) == false)		//再生中じゃなければ
			{
				se->Play((int)LEVELUP_SE);		//レベルアップのSEを鳴らす
				se->SetIsPlayEnd(true);			//再生終了
			}
		}

		if (msg->GetIsResultMsgEnd())		//リザルトメッセージの表示が終了していたら
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

	if (keydown->IsKeyDown(KEY_INPUT_S))	//Sキーを押されたら
	{
		text->Next();	//選択を一つ次へ
	}
	else if (keydown->IsKeyDown(KEY_INPUT_W))	//Wキーを押されたら
	{
		text->Back();	//選択を一つ前へ
	}

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (keydown->IsKeyDown(KEY_INPUT_RETURN))	//エンターキーを押された瞬間
	{
		if (*text->GetPos() == "TITLE")		//選択している文字列が"TITLE"だったら
		{
			SceneChenge(GameSceneNow, (int)GAME_SCENE_TITLE);	//次の画面はタイトル画面
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
		StrSet_Flg = false;				//文字列未設定
	}


	return;

}

//初期化処理
void Init()
{
	ChengeDrawCount = 0;		//フェードイン用初期化

	ui->SetStateWindow(player->GetLevel(), player->GetHP(), player->GetMP());	//描画ステータス更新

	se->SetIsPlayEnd(false);	//SEの再生状態リセット

	if (GameSceneBefor == (int)GAME_SCENE_BATTLE)	//戦闘画面から遷移した場合
	{
		enemy[EncounteEnemyType]->StateSetInit();		//遭遇した敵初期化

		ui->BattleInit();			//バトルコマンド初期化

		EncounteEnemyType = 0;		//遭遇した敵の種類をリセット

		BattleStageNow = (int)WAIT_ACT;	//バトル状態を、行動待ち状態へ

		Turn = (int)MY_TURN;		//ターンを味方のターンに設定

		msg->ResetResultMsg();		//リザルトメッセージ関係のメンバーをリセット

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
	back->Draw(0, 0);	//背景画像描画

	title->Draw(0, GAME_HEIGHT / 2 - title->GetHeight(0) / 2);		//画面中央にタイトル描画

	std::vector<std::string> str = { "START","END" };

	if (StrSet_Flg == false)
	{
		text->SetText(str);		//描画文字セット

		StrSet_Flg = true;		//文字列設定

		font->SetSize(BIG_FONTSIZE);		//フォントサイズを大きくする
	}

	text->Draw(GAME_WIDTH / 2 - text->GetWidth() / 2, DEFAULT_TEXT_Y, str.size(), true);	//描画（矢印付き）
	
	return;

}

//プレイ画面の描画処理
void Play_Draw()
{
	font->SetSize(DEFAULT_FONTSIZE);	//フォントサイズを標準に戻す

	//マップ描画処理
	for (int cnt = 0; cnt < MAP_LAYER_KIND; cnt++)
	{
		mapdata[MapKind[MAPPOS_Y][MAPPOS_X]][cnt]->Draw(mapimage->GetHandle((int)FILED));		//マップ描画
		mapdata[MapKind[MAPPOS_Y][MAPPOS_X]][cnt]->ChengeMap(player, MapNowPos);					//マップの切り替え処理
	}

	player->DrawAnime();		//アニメーション描画
	ui->MenuOperation(keydown, player->GetIsMenu());	//メニュー画面操作

	return;

}

//戦闘画面の描画処理
void Battle_Draw()
{

	back_battle->Draw(0, 0);	//背景画像を描画

	enemy[EncounteEnemyType]->Draw();	//敵描画

	ui->DrawWindow();		//ウィンドウの描画

	//メッセージ関係描画
	msg->DrawBattleMsg(BattleStageNow, Turn, ui->GetChoiseCommamd(), player, enemy[EncounteEnemyType],keydown->IsKeyDownOne(KEY_INPUT_RETURN));

	if (BattleStageNow == (int)WAIT_ACT)		//行動選択状態の時
	{
		if (Turn == (int)MY_TURN)		//味方のターンだったら
		{
			ui->DrawCommand();						//バトルコマンド描画
		}
		else if (Turn = (int)ENEMY_TURN)	//敵のターンだったら
		{

		}

	}

	ui->DrawStateWindow();		//ステータスウィンドウ描画

	return;

}

//エンド画面の描画処理
void End_Draw()
{
	std::vector<std::string> str = { "TITLE","END" };

	if (StrSet_Flg == false)
	{
		text->SetText(str);		//描画文字セット

		StrSet_Flg = true;		//文字列設定
	}

	text->Draw(GAME_WIDTH / 2 - text->GetWidth() / 2, DEFAULT_TEXT_Y, str.size(), true, GetColor(255, 255, 255));	//文字列描画（色指定）（矢印あり）

	return;

}

//敵との遭遇処理
void Enconte()
{
	int battleRate;	//敵との遭遇率
	
	battleRate = 100;	//100回に1回遭遇する

	//ランダムで遭遇判定
	int rand = GetRand(battleRate);		//遭遇率の範囲内で乱数を生成

	if (rand%battleRate == 0)			//敵と遭遇した時
	{

		player->SetIsKeyDown(false);			//プレイヤーの動きを止める

		EncounteEnemyType = GetRand(ENEMY_KIND - 1);	//ランダムに敵の種類を決定

		SceneChenge(GameSceneNow, (int)GAME_SCENE_BATTLE);	//次の画面は戦闘画面


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
