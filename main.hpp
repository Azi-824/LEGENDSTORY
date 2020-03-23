/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* main.hpp     																				　 */
/*       																						　 */

#pragma once

//########## ヘッダーファイル読み込み ##########


//########## マクロ定義 ##########
#define GAME_LEFT	  0		//画面の横の始点
#define GAME_TOP	  0		//画面の縦の始点
#define GAME_WIDTH	880		//画面の横の大きさ
#define GAME_HEIGHT	640		//画面の縦の大きさ
#define GAME_COLOR	32		//画面のカラービット

#define GAME_WINDOW_NAME	"LEGEND STORY"		//ウィンドウのタイトル
#define GAME_WINDOW_MODECHANGE	TRUE			//TRUE：ウィンドウモード / FALSE：フルスクリーン

#define SET_WINDOW_ST_MODE_DEFAULT			0	//デフォルト
#define SET_WINDOW_ST_MODE_TITLE_NONE		1	//タイトルバーなし
#define SET_WINDOW_ST_MODE_TITLE_FLAME_NONE	2	//タイトルバーとフレームなし
#define SET_WINDOW_ST_MODE_FLAME_NONE		3	//フレームなし

#define GAME_FPS_SPEED					   60

#define GAME_WAITCNT_MAX				   60	//待ち時間のカウントマックス値

#define GAME_ICON_ID					   333	//アイコンのID

#define ENCOUNT_TXT_KIND	3

//テキスト関係
#define SAVE_TEXT			"セーブ中です。"	//セーブ時のテキスト
#define GAME_CLEAR_TEXT		"ゲームクリア！"	//ゲームクリア時のテキスト
#define GAME_OVER_TEXT		"ゲームオーバー…"	//ゲームオーバー時のテキスト
#define ENCOUNT_TEXT_1		"バイト帰りの"		//敵に遭遇した時のテキスト1個め
#define ENCOUNT_TEXT_2		"肥満体の"			//敵に遭遇した時のテキスト2個め
#define ENCOUNT_TEXT_3		"疲れ果てた"		//敵に遭遇した時のテキスト3個め


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
	WAIT_ACT,			//行動選択待ち状態
	DAMEGE_CALC,		//ダメージ計算状態
	ACT_MSG,			//行動メッセージ表示状態
	DRAW_EFFECT,		//エフェクト表示状態
	DRAW_DAMEGE,		//ダメージ描画状態
	RESULT_MSG			//リザルトメッセージ描画状態
};

enum TURN
{
	MY_TURN,		//味方のターン
	ENEMY_TURN		//敵のターン
};

enum ENCOUNT_TXT_TYPE
{
	ENCOUNT_TXT_PATARN1,	//遭遇した時のテキスト種類1個め
	ENCOUNT_TXT_PATARN2,	//遭遇した時のテキスト種類2個め
	ENCOUNT_TXT_PATARN3		//遭遇した時のテキスト種類3個め
};

enum TITLE_SELECT
{
	TITLE_SELECT_START,	//スタート
	TITLE_SELECT_END	//終了
};

enum END_SELECT
{
	END_SELECT_TITLE,	//タイトルへ
	END_SELECT_PLAY,	//プレイ画面へ
	END_SELECT_END,		//終了
};

//############## プロトタイプ宣言 #############

void Load();				//ロード画面の処理
void Title();				//タイトル画面の処理
void Play();				//プレイ画面の処理
void Battle();				//戦闘画面の処理
void End();					//エンド画面の処理
void Chenge();				//シーン遷移画面の処理

void Init();				//初期化処理
void BattleInit();			//戦闘画面関係初期化
void SceneChenge(int, int);	//シーンを変更する処理

void Load_Draw();			//ロード画面の描画処理
void Title_Draw();			//タイトル画面の描画処理
void Play_Draw();			//プレイ画面の描画処理
void Battle_Draw();			//戦闘画面の描画処理
void End_Draw();			//エンド画面の描画処理

void Enconte();				//敵との遭遇処理
bool Wait();				//待つ処理
void Delete_Class();		//クラスを削除する処理
bool LoadGameData();		//ゲームで使用するデータ等を読み込む処理
void SetGameInit();			//ゲームの初期設定を行う処理
void SetSize();				//画像等のサイズ設定を行う処理
bool GameMainLoop();		//無限ループ内のゲーム処理

//戦闘画面の処理
void Bt_WaitAct();			//戦闘画面行動待ち状態の処理
void Bt_DamegeCalc();		//戦闘画面ダメージ計算状態の処理
void Bt_ActMsg();			//戦闘画面行動メッセージ描画状態の処理
void Bt_DrawEffect();		//戦闘画面エフェクト描画状態の処理
void Bt_DrawDamege();		//戦闘画面ダメージ描画状態の処理
void Bt_ResultMsg();		//戦闘画面リザルトメッセージ描画状態の処理

const char * JudgeDrop();	//ドロップした物の種類を判別する

//########## クラスの定義 ##########