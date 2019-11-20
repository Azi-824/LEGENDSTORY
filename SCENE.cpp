//SCENE.cpp

//############### ヘッダーファイル読み込み #################
#include "SCENE.hpp"

//############### クラスの定義 ##################

//コンストラクタ
SCENE::SCENE()
{
	return;
}

//デストラクタ
SCENE::~SCENE()
{
	return;
}

//指定されたシーンをセットする
void SCENE::SetScene(int Nextscene)
{
	this->GameSceneNow = Nextscene;	//指定されたシーンをセット
}