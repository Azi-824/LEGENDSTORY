//SCENE.cpp
//シーンクラス

#pragma once

//############### ヘッダーファイル読み込み ################
#include <DxLib.h>



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
