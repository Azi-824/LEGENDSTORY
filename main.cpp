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

//########## グローバルオブジェクト ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPSクラスのオブジェクトを生成
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWNクラスのオブジェクトを生成

IMAGE *title;						//タイトル画像
IMAGE *back;						//背景画像
IMAGE *back_battle;					//戦闘画面の背景画像

MUSIC *bgm;							//BGM

FONT *font;							//フォント
TEXTSTR *text;						//文字列
UI *ui;								//UI
DATA *data;	//データ

PLAYER *player;						//主人公

ENEMY *slime;						//スライム

MAPIMAGE *mapimage;					//マップチップのデータ
MAP *mapdata[MAP_DATA_KIND][MAP_LAYER_KIND];		//マップデータ

//############## グローバル変数 ##############
int GameSceneNow = (int)GAME_SCENE_TITLE;	//現在のゲームシーン
int GameSceneBefor;							//前のゲームシーン
int GameSceneNext;							//次のゲームシーン

int BattleStageNow = (int)WAIT_PLAYER_ACT;	//バトルシーンの現在の状態
int BattleActMsgCnt = 0;		//行動メッセージカウント
int BattleActMsgCntMax = 60;	//行動メッセージの表示時間

int MapKind[MAP_DATA_TATE_KIND][MAP_DATA_YOKO_KIND];			//マップの種類
int MapNowPos[2] = {0};								//現在のマップのX位置とY位置を格納

int ChengeDrawCount = 0;	//フェードイン処理に使用

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

	bgm = new MUSIC(MY_MUSIC_DIR_BGM, MY_MUSIC_NAME_BGM);			//BGMを生成
	if (bgm->GetIsLoad() == false) { return -1; }					//読み込み失敗時

	font = new FONT(MY_FONT_DIR, MY_FONT_NAME, FONT_NAME);			//フォントを生成
	if (font->GetIsLoad() == false) { return -1; }					//読み込み失敗時

	text = new TEXTSTR();	//テキスト作成
	data = new DATA(DATA_DIR, DATA_NAME);
	
	player = new PLAYER();
	if (player->SetImage(MY_IMG_DIR_CHARCTOR, MY_IMG_NAME_PLAYER) == false) { return -1; }	//読み込み失敗
	if (player->SetAnime(MY_ANIME_DIR_PLAYER, MY_ANIME_NAME_PLAYER, PLAYER_ALL_CNT, PLAYER_YOKO_CNT, PLAYER_TATE_CNT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_ANI_SPEED, true) == false) { return -1; } //読み込み失敗
	if (player->AddEffect(MY_ANIME_DIR_ATKEFECT, MY_ANIME_NAME_ATKEFECT, ATK_ALL_CNT, ATK_YOKO_CNT, ATK_TATE_CNT, ATK_WIDTH, ATK_HEIGHT, ATK_SPEED, false) == false) { return -1; }
	if (player->AddMagicEffect(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC2, MAGIC2_ALL_CNT, MAGIC2_YOKO_CNT, MAGIC2_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGICN_SPEED, false) == false) { return -1; }
	player->SetInit();	//初期設定
	player->SetName("アアア");	//名前設定

	ui = new UI();		//UI作成
	ui->SetStateWindow(player);	//描画HP設定

	slime = new ENEMY(ENEMY_DIR, ENEMY_NAME_SLIME);	//スライム作成
	if (slime->GetIsLoad() == false) { return -1; }	//読み込み失敗
	if (slime->SetAtkEffect(MY_ANIME_DIR_MAGIC, MY_ANIME_NAME_MAGIC, MAGIC_ALL_CNT, MAGIC_YOKO_CNT, MAGIC_TATE_CNT, MAGIC_WIDTH, MAGIC_HEIGHT, MAGICN_SPEED, false) == false) { return -1; }
	slime->SetImagePos(GAME_WIDTH / 2 - slime->GetWidth() / 2, GAME_HEIGHT / 2 - slime->GetHeight() / 2);	//スライムの位置調整(画面中央)
	slime->SetName("スライム");//名前設定

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

	delete title;			//titleを破棄
	delete fps;				//FPSを破棄
	delete keydown;			//keydownを破棄
	delete font;			//fontを破棄
	delete text;			//textを破棄
	delete bgm;				//bgmを破棄
	delete player;			//playerを破棄
	delete back;			//backを破棄
	delete back_battle;		//back_battleを破棄
	delete mapimage;		//mapimageを破棄
	delete data;			//dataを破棄

	for (int i = 0; i < MAP_DATA_KIND; i++)
	{
		for (int cnt = 0; cnt < MAP_LAYER_KIND; cnt++)
		{
			delete mapdata[i][cnt];	//mapdataを破棄
		}

	}

	DxLib_End();			//ＤＸライブラリ使用の終了処理

	return 0;
}

//タイトル画面の処理
void Title()
{
	Init();		//初期化

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 音の再生処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (bgm->GetIsPlay() == false)	//再生中じゃないとき
	{
		bgm->ChengeVolume(255 * 50 / 100);	//BGMの音量を50%に変更
		bgm->Play();				//BGMを再生
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
	Init();		//初期化

	player->Operation(keydown);	//プレイヤーキー操作
	Play_Draw();		//描画処理

	if (keydown->IsKeyDownOne(KEY_INPUT_Q))		//Qキーを押された瞬間
	{
		player->SetIsMenu(true);		//メニュー描画開始
	}
	else if (keydown->IsKeyDownOne(KEY_INPUT_ESCAPE))	//Escキーを押された瞬間
	{
		player->SetIsMenu(false);		//メニュー描画終了
	}


	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (keydown->IsKeyDown(KEY_INPUT_SPACE))
	{
		SceneChenge(GameSceneNow, (int)GAME_SCENE_BATTLE);	//次の画面は戦闘画面
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
	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 味方のターンの処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

	case (int)WAIT_PLAYER_ACT:		//プレイヤーの行動選択待ち状態の時

		ui->BattleOperation(keydown);			//戦闘画面のキー操作

		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ バトルコマンド毎の処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
		switch (ui->GetChoiseCommamd())		//どのコマンドを選んだか
		{
		case (int)ATACK:					//攻撃を選んだ時

			BattleStageNow = (int)PLAYER_DAMEGE_CALC;	//バトル状態をダメージ計算状態へ

			break;

		case (int)DEFENSE:		//防御を選んだ時

			ui->BattleInit();	//バトルコマンドリセット

			break;

		case (int)MAGIC:		//魔法を選んだ時

			BattleStageNow = (int)PLAYER_DAMEGE_CALC;	//バトル状態をダメージ計算状態へ

			break;

		case (int)ITEM:			//アイテムを選んだ時

			ui->BattleInit();	//バトルコマンドリセット

			break;

		case (int)ESCAPE:		//逃げるを選んだ時

			data->Draw(200, 200);			//逃げるときのメッセージ描画
			ui->BattleInit();	//バトルコマンドリセット
			SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//次の画面はプレイ画面
			Init();									//初期化

			break;

		default:
			break;
		}
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ バトルコマンド毎の処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


		break;						//プレイヤーの行動選択待ち状態の処理ここまで

	case (int)PLAYER_DAMEGE_CALC:			//ダメージ計算状態の時

		player->DamegeCalc(slime);		//ダメージ計算

		BattleStageNow = (int)PLAYER_ACT_MSG;	//行動メッセージ表示状態へ

		break;						//ダメージ計算状態の時ここまで

	case (int)PLAYER_ACT_MSG:				//行動メッセージ表示状態


		if (BattleActMsgCnt == BattleActMsgCntMax)		//表示秒数になったら
		{
			BattleStageNow = (int)PLAYER_DRAW_EFFECT;			//エフェクト描画状態へ
		}
		else
		{
			BattleActMsgCnt++;	//カウントアップ
		}

		break;						//行動メッセージ表示状態ここまで

	case (int)PLAYER_DRAW_EFFECT:			//エフェクト描画状態

		if (ui->GetChoiseCommamd() == (int)ATACK)	//攻撃を選んでいたら
		{
			player->DrawAtk(350, 250);		//攻撃エフェクト描画
		}
		else if (ui->GetChoiseCommamd() == (int)MAGIC)	//魔法を選んでいたら
		{
			player->DrawMagic((GAME_WIDTH / 2 - MAGIC_WIDTH / 2), (GAME_HEIGHT / 2 - MAGIC_HEIGHT / 2));	//魔法エフェクト描画
		}

		if (player->GetEffectEnd())		//エフェクト描画が終了したら
		{
			
			player->EffectReset();			//エフェクト関連リセット

			BattleStageNow = (int)ENEMY_WAIT_ACT;		//敵の行動選択状態へ

			BattleActMsgCnt = 0;	//カウントリセット

			slime->SetHP((slime->GetHP() - player->GetSendDamege()));	//ダメージを与える

			if (slime->GetHP() <= 0)				//敵のHPが0になったら
			{
				slime->SetIsArive(false);		//敵死亡
			}

		}

		break;

	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 味方のターンの処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 敵のターンの処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

	case (int)ENEMY_WAIT_ACT:			//敵の行動選択待ち状態

		//敵の行動選択決定処理

		BattleStageNow = (int)ENEMY_DAMEGE_CALC;	//敵のダメージ計算へ

		break;

	case (int)ENEMY_DAMEGE_CALC:		//敵のダメージ計算状態

		//ダメージ計算

		BattleStageNow = (int)ENEMY_ACT_MSG;	//敵の行動メッセージ表示へ
		
		break;

	case (int)ENEMY_ACT_MSG:			//敵の行動メッセージ表示状態

		//敵の行動メッセージ表示
		if (BattleActMsgCnt == BattleActMsgCntMax)		//表示秒数になったら
		{
			BattleStageNow = (int)ENEMY_DRAW_EFFECT;			//敵のエフェクト描画状態へ
		}
		else
		{
			BattleActMsgCnt++;	//カウントアップ
		}

		break;

	case (int)ENEMY_DRAW_EFFECT:		//敵のエフェクト表示状態

		//敵のエフェクト表示
		slime->DrawEffect((GAME_WIDTH / 2 - MAGIC_WIDTH / 2),(GAME_HEIGHT / 2 - MAGIC_HEIGHT / 2));	//敵の攻撃エフェクト描画

		if (slime->GetIeEffectEnd())		//エフェクト描画が終了したら
		{
			BattleActMsgCnt = 0;	//カウントリセット

			slime->ResetEffect();	//エフェクト関連リセット

			player->SetHP(player->GetRecvDamege());		//味方にダメージを与える

			ui->SetStateWindow(player);		//描画ステータス更新

			ui->BattleInit();				//バトルコマンドリセット

			BattleStageNow = (int)WAIT_PLAYER_ACT;		//味方の行動選択待ち状態へ

			if (player->GetHP() <= 0)			//自分のHPが0になったら
			{
				player->SetIsArive(false);		//自分死亡
			}

		}

		break;

	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 敵のターンの処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


	default:

		break;


	}

	//生存判定
	if (slime->GetIsArive() == false)	//敵が死んだら
	{
		SceneChenge(GameSceneNow, (int)GAME_SCENE_PLAY);	//次の画面はプレイ画面

		BattleStageNow = (int)WAIT_PLAYER_ACT;		//味方の行動選択待ち状態へ

		Init();									//初期化

	}
	else if (player->GetIsArive() == false)	//自分が死んだら
	{
		SceneChenge(GameSceneNow, (int)GAME_SCENE_END);	//次の画面はエンド画面

		BattleStageNow = (int)WAIT_PLAYER_ACT;		//味方の行動選択待ち状態へ

		Init();									//初期化
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
	Init();	//初期化

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
	if (keydown->IsKeyDown(KEY_INPUT_BACK))
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

	//60フレーム分、待つ
	if (ChengeDrawCount < ChengeDrawCountMax)
	{
		ChengeDrawCount++;
	}
	else
	{
		GameSceneNow = GameSceneNext;	//次の画面にする
		StrSet_Flg = false;				//文字列未設定
	}

	//フェードアウトの処理
	double ToukaPercent = ChengeDrawCount / (double)ChengeDrawCountMax;//透過％を求める
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * 255);	//透過させる
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);	//真っ暗な画面にする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//透過をやめる

	return;

}

//初期化処理
void Init()
{
	ChengeDrawCount = 0;		//フェードイン用初期化

	slime->StateSetInit();		//敵初期化

	ui->BattleInit();			//バトルコマンド初期化

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


	slime->Draw();	//スライム描画

	if (BattleStageNow==(int)ENEMY_ACT_MSG)	//敵の行動メッセージ表示状態だったら
	{
		ui->EnemyDrawDamege(slime->GetName(), player->GetRecvDamege());		//受けたメッセージ表示
	}
	else if (BattleStageNow == (int)PLAYER_ACT_MSG)	//味方の行動メッセージ表示状態だったら
	{
		ui->MyDrawDamege(player->GetName(), player->GetSendDamege());		//与えたダメージ表示
	}
	else
	{
		ui->DrawCommand();						//バトルコマンド描画
	}

	ui->DrawStateWindow();					//ステータスウィンドウ描画

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
