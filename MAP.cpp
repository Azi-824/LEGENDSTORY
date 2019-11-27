//MAP.cpp
//マップクラス

//################## ヘッダファイル読み込み #####################
#include "MAP.hpp"

//################## クラス定義 #####################
//コンストラクタ
MAP::MAP()
{
	return;
}

//デストラクタ
MAP::~MAP()
{
	return;
}

//csvファイルを読み込む
//引数：const char * マップcsvのファイル名
//引数：const char * マップcsvの名前
bool MAP::LoadCsv(const char *dir, const char *name)
{

	std::string LoadFilePath;
	LoadFilePath += dir;
	LoadFilePath += name;

	if ((this->fp_map_csv = fopen(LoadFilePath.c_str(), "r")) == NULL)		//ファイルを読み込みモード(r)で開く
	{
		return false;//異常終了
	}

	//ここから正常に読み込めたときの処理****************************************

	int result = 0;			//ファイルの最後かチェック
	int LoopCnt = 0;		//ループカウンタ

	while (result != EOF)		//EOF End Of File(ファイルの最後)ではないとき繰り返す
	{
		//ファイルから数値を一つ読み込み(%d,)、配列に格納する
		result = fscanf(this->fp_map_csv, "%d,", &this->MapData[LoopCnt / MAP_YOKO][LoopCnt % MAP_YOKO]);

		LoopCnt++;
	}

	fclose(this->fp_map_csv);	//ファイルを閉じる

	this->FilePath = LoadFilePath;
	this->FileName = name;

	//this->MapNow = MAP_1;		//1マップ目を現在のマップに指定

	return true;

}

////現在のマップを取得
//int MAP::GetMapNow()
//{
//	this->MapNow;
//}

//マップを切り替える
void MAP::ChengeMap(PLAYER *player,int *mapnow)
{
	COLLISION *player_collision = player->GetCollision();	//プレイヤーの当たり判定を取得

	if (player_collision->Bottom >= GAME_HEIGHT)	//画面の下に来たら
	{
		*mapnow =MAP_2 ;	//次のマップへ
		player->SetPosition(0, -player_collision->Top);	//位置を修正
	}
	return;
}

//描画
void MAP::Draw(int *handle)
{
	for (int tate = 0; tate < MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO; yoko++)
		{
			DrawGraph(yoko*MAP_YOKO_SIZE, tate*MAP_TATE_SIZE, handle[this->MapData[tate][yoko]], TRUE);	//マップ描画
		}
	}

	return;
}
