//SCENE.cpp
//シーンクラス

#pragma once

//############### ヘッダーファイル読み込み ################
#include <DxLib.h>

//############### 列挙型 ###############
enum GAME_SCENE {
	GAME_SCENE_TITLE,	//タイトル画面
	GAME_SCENE_PLAY,	//プレイ画面
	GAME_SCENE_END		//エンド画面
};

//############## クラスの定義 ################
class SCENE
{
private:
	static int GameSceneNow;			//現在のシーン

public:
	SCENE();					//コンストラクタ

	~SCENE();					//デストラクタ

	void SetScene(int);			//指定されたシーンをセットする
};
