/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* main.hpp     																				　 */
/*       																						　 */

#pragma once

//########## ヘッダーファイル読み込み ##########


//########## マクロ定義 ##########
#define GAME_LEFT	  0		//画面の横の始点
#define GAME_TOP	  0		//画面の縦の始点
#define GAME_WIDTH	800		//画面の横の大きさ
#define GAME_HEIGHT	600		//画面の縦の大きさ
#define GAME_COLOR	32		//画面のカラービット

#define GAME_WINDOW_NAME	"GAME TITLE"		//ウィンドウのタイトル
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE：ウィンドウモード / FALSE：フルスクリーン

#define SET_WINDOW_ST_MODE_DEFAULT			0	//デフォルト
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//タイトルバーなし
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//タイトルバーとフレームなし
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//フレームなし

#define GAME_FPS_SPEED					   60

//############### 列挙型 ###############
enum GAME_SCENE {
	GAME_SCENE_TITLE,	//タイトル画面
	GAME_SCENE_PLAY,	//プレイ画面
	GAME_SCENE_BATTLE,	//戦闘画面
	GAME_SCENE_END,		//エンド画面
	GAME_SCENE_CHENGE	//シーン遷移画面
};

enum BATTLE_STAGE
{
	WAIT_PLAYER_ACT,		//プレイヤーの行動選択待ち状態
	PLAYER_DAMEGE_CALC,		//ダメージ計算状態
	PLAYER_ACT_MSG,			//行動メッセージ表示状態
	PLAYER_DRAW_EFFECT,		//エフェクト表示状態
	DRAW_DAMEGE,			//ダメージ描画状態
	ENEMY_WAIT_ACT,			//敵の行動選択待ち状態
	ENEMY_DAMEGE_CALC,		//敵のダメージ計算
	ENEMY_ACT_MSG,			//敵の行動メッセージ表示状態
	ENEMY_DRAW_EFFECT		//敵のエフェクト表示状態
};

//############## プロトタイプ宣言 #############

void Title();				//タイトル画面の処理
void Play();				//プレイ画面の処理
void Battle();				//戦闘画面の処理
void End();					//エンド画面の処理
void Chenge();				//シーン遷移画面の処理

void Init();				//初期化処理
void SceneChenge(int, int);	//シーンを変更する処理

void Title_Draw();			//タイトル画面の描画処理
void Play_Draw();			//プレイ画面の描画処理
void Battle_Draw();			//戦闘画面の描画処理
void End_Draw();			//エンド画面の描画処理

//########## クラスの定義 ##########