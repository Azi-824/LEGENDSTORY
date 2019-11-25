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


//########## グローバルオブジェクト ##########
FPS *fps = new FPS(GAME_FPS_SPEED);							//FPSクラスのオブジェクトを生成
KEYDOWN *keydown = new KEYDOWN();							//KEYDOWNクラスのオブジェクトを生成
IMAGE *title;
IMAGE *back;		//背景画像
FONT *font;
PLAYER *player;
MAP *mapImage;		//マップデータ

//############## グローバル変数 ##############
int GameSceneNow = (int)GAME_SCENE_TITLE;	//現在のゲームシーン


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

	font = new FONT(MY_FONT_DIR, MY_FONT_NAME, FONT_NAME);			//フォントを生成
	if (font->GetIsLoad() == false) { return -1; }					//読み込み失敗時

	player = new PLAYER();
	if (player->SetImage(MY_IMG_DIR_CHARCTOR, MY_IMG_NAME_PLAYER) == false) { return -1; }	//読み込み失敗
	if (player->SetAnime(MY_ANIME_DIR_PLAYER, MY_ANIME_NAME_PLAYER, PLAYER_ALL_CNT, PLAYER_YOKO_CNT, PLAYER_TATE_CNT, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_ANI_SPEED, true) == false) { return -1; } //読み込み失敗
	player->SetInit();	//初期設定

	mapImage = new MAP();
	if (mapImage->LoadCsv(MY_MAP_DIR, MY_MAP_1) == false) { return -1; }		//読み込み失敗

	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 読み込み処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	while (TRUE)	//無限ループ
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了

		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		keydown->KeyDownUpdate();	//キーの入力状態を更新する

		fps->Update();				//FPSの処理[更新]

		keydown->IsKeyDown(KEY_INPUT_LEFT);

		//▼▼▼▼▼ゲームのシーンここから▼▼▼▼▼

		switch (GameSceneNow)
		{
		case (int)GAME_SCENE_TITLE:		//タイトル画面だったら
			
			Title();					//タイトル画面の処理

			break;

		case (int)GAME_SCENE_PLAY:		//プレイ画面だったら

			Play();						//プレイ画面の処理

			break;

		case (int)GAME_SCENE_END:		//エンド画面だったら

			End();						//エンド画面の処理

			break;

		default:
			break;

		}

		keydown->IsKeyDown(KEY_INPUT_UP);


		//▲▲▲▲▲ゲームのシーンここまで▲▲▲▲▲

		fps->Draw(0, 0);				//FPSの処理[描画]

		ScreenFlip();				//モニタのリフレッシュレートの速さで裏画面を再描画

		fps->Wait();				//FPSの処理[待つ]
	}

	delete title;			//titleを破棄
	delete fps;				//FPSを破棄
	delete keydown;			//keydownを破棄
	delete font;			//fontを破棄
	delete player;			//playerを破棄
	delete back;			//backを破棄

	DxLib_End();			//ＤＸライブラリ使用の終了処理

	return 0;
}

//タイトル画面の処理
void Title()
{

	back->Draw(0, 0);	//背景画像描画

	title->Draw(0, GAME_HEIGHT / 2 - title->GetHeight() / 2);		//画面中央にタイトル描画

	int width = font->GetWidth("PUSH ENTER");						//横幅取得

	font->Draw(GAME_WIDTH/2 - width/2, 500, "PUSH ENTER");			//文字列描画
	

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (keydown->IsKeyDown(KEY_INPUT_RETURN))
	{
		GameSceneNow = (int)GAME_SCENE_PLAY;	//プレイ画面へ
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 画面遷移の処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	return;
}

//プレイ画面の処理
void Play()
{

	mapImage->Draw();	//マップ描画

	int width = font->GetWidth("PUSH SPACE");						//横幅取得

	font->Draw(GAME_WIDTH / 2 - width / 2, 500, "PUSH SPACE");			//文字列描画


	player->Operation(keydown);	//プレイヤーキー操作
	player->DrawAnime();		//アニメーション描画

	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (keydown->IsKeyDown(KEY_INPUT_SPACE))
	{
		GameSceneNow = (int)GAME_SCENE_END;	//エンド画面へ
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 画面遷移の処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


	return;
}

//エンド画面の処理
void End()
{

	int width = font->GetWidth("PUSH BACK");						//横幅取得

	font->Draw(GAME_WIDTH / 2 - width / 2, 500, "PUSH BACK");			//文字列描画


	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 画面遷移の処理 ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (keydown->IsKeyDown(KEY_INPUT_BACK))
	{
		GameSceneNow = (int)GAME_SCENE_TITLE;	//タイトル画面へ
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 画面遷移の処理 ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	return;
}