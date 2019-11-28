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
void MAP::ChengeMap(PLAYER *player,int *mapnowpos)
{
	COLLISION *player_collision = player->GetCollision();	//プレイヤーの当たり判定を取得

	if (player_collision->Bottom >= GAME_HEIGHT)	//画面の下に来たら
	{
		if ((mapnowpos[1]) < MAP_DATA_TATE_KIND - 1)	//下のマップがある場合は
		{
			(mapnowpos[1])++;	//下のマップへ
			player->SetPosition(0, -(player_collision->Top - 5));	//位置を修正
		}
	}
	else if (player_collision->Top <= GAME_TOP)		//画面の上に来たら
	{
		if ((mapnowpos[1]) > 0)	//上のマップがある場合は
		{
			(mapnowpos[1])--;	//上のマップへ
			player->SetPosition(0, GAME_HEIGHT- (player_collision->Height + 5));	//位置を修正
		}

	}
	else if (player_collision->Right >= GAME_WIDTH)	//画面の右に来たら
	{
		if ((mapnowpos[0]) + MAP_DATA_TATE_KIND <= MAP_DATA_KIND - 1)	//横にマップがある場合は
		{
			(mapnowpos[0]) += MAP_DATA_TATE_KIND;	//右のマップへ
			player->SetPosition(-(player_collision->Left - 5), 0);	//位置を修正
		}
	}
	else if (player_collision->Left <= GAME_LEFT)		//画面の左に来たら
	{
		if ((mapnowpos[0]) - MAP_DATA_TATE_KIND >= 0)			//左のマップがある場合は
		{
			(mapnowpos[0]) -= MAP_DATA_TATE_KIND;	//左のマップへ
			player->SetPosition(GAME_WIDTH - (player_collision->Width + 5), 0);	//位置を修正
		}
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
