//MAP.cpp
//マップクラス

//################## ヘッダファイル読み込み #####################
#include "MAP.hpp"

//################## クラス定義 #####################
//コンストラクタ
MAP::MAP()
{
	for (int tate = 0; tate < MAP_TATE; ++tate)
	{
		for (int yoko = 0; yoko < MAP_YOKO; ++yoko)
		{
			this->RectOK[tate][yoko] = new COLLISION();	//当たり判定の領域を作成(通行できる)
			this->RectNG[tate][yoko] = new COLLISION();	//当たり判定の領域を作成(通行できない)

			//当たり判定初期化
			this->RectOK[tate][yoko]->SetValue(0, 0, MAP_YOKO_SIZE, MAP_TATE_SIZE);

			this->RectNG[tate][yoko]->SetValue(0, 0, MAP_YOKO_SIZE, MAP_TATE_SIZE);

		}
	}
	return;
}

//デストラクタ
MAP::~MAP()
{
	for (int tate = 0; tate < MAP_TATE; ++tate)
	{
		for (int yoko = 0; yoko < MAP_YOKO; ++yoko)
		{
			delete this->RectOK[tate][yoko];	//当たり判定を破棄(通行できる)
			delete this->RectNG[tate][yoko];	//当たり判定を破棄(通行できない)
		}
	}

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

	return true;

}

//マップを切り替える
//引数：PLAYER：主人公の情報
//引数：int	　：現在のマップのX座標とY座標の情報
void MAP::ChengeMap(PLAYER *player,int *mapnowpos)
{
	COLLISION *player_collision = player->GetCollision();	//プレイヤーの当たり判定を取得

	if (player_collision->Bottom >= GAME_HEIGHT)	//画面の下に来たら
	{
		if ((mapnowpos[POS_Y]) < MAP_DATA_TATE_KIND - 1)	//下のマップがある場合は
		{
			mapnowpos[POS_Y]++;	//下のマップへ
			player->SetPosition(0, -(player_collision->Top - 5));	//位置を修正
		}
	}
	else if (player_collision->Top <= GAME_TOP)		//画面の上に来たら
	{
		if ((mapnowpos[POS_Y]) > 0)	//上のマップがある場合は
		{
			mapnowpos[POS_Y]--;	//上のマップへ
			player->SetPosition(0, GAME_HEIGHT- (player_collision->Height + 5));	//位置を修正
		}

	}
	else if (player_collision->Right >= GAME_WIDTH)	//画面の右に来たら
	{
		if ((mapnowpos[POS_X]) + MAP_DATA_TATE_KIND <= MAP_DATA_TATE_KIND)	//横にマップがある場合は
		{
			(mapnowpos[POS_X]) += (MAP_DATA_TATE_KIND - 1);	//右のマップへ
			player->SetPosition(-(player_collision->Left - 5), 0);	//位置を修正
		}
	}
	else if (player_collision->Left <= GAME_LEFT)		//画面の左に来たら
	{
		if ((mapnowpos[POS_X]) - (MAP_DATA_TATE_KIND - 1) >= 0)			//左のマップがある場合は
		{
			(mapnowpos[POS_X]) -= (MAP_DATA_TATE_KIND - 1);	//左のマップへ
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

//当たり判定の領域を作成
void MAP::CreateRect(int *ok_kind,int *ng_kind)
{
	for (int tate = 0; tate < MAP_TATE; ++tate)
	{
		for (int yoko = 0; yoko < MAP_YOKO; ++yoko)
		{

			//当たり判定の領域を作成(通行できる)
			for (int cnt = 0; cnt < MAP_OK_KIND; ++cnt)
			{
				if (this->MapData[tate][yoko] == ok_kind[cnt])
				{
					this->RectOK[tate][yoko]->Left = yoko * this->RectOK[tate][yoko]->Width + 1;
					this->RectOK[tate][yoko]->Top = tate * this->RectOK[tate][yoko]->Height + 1;
					this->RectOK[tate][yoko]->Right = (yoko + 1) * this->RectOK[tate][yoko]->Width - 1;
					this->RectOK[tate][yoko]->Bottom = (tate + 1)*this->RectOK[tate][yoko]->Height - 1;

					//this->RectOK[tate][yoko]->SetValue(yoko * this->RectOK[tate][yoko]->Width + 1,
					//	tate * this->RectOK[tate][yoko]->Height + 1,
					//	MAP_YOKO_SIZE - 1, MAP_TATE_SIZE - 1);

				}
			}

			//当たり判定の領域を作成(通行できない)
			for (int cnt = 0; cnt < MAP_NG_KIND; ++cnt)
			{
				if (this->MapData[tate][yoko] == ng_kind[cnt])
				{
					this->RectNG[tate][yoko]->Left = yoko * this->RectOK[tate][yoko]->Width + 1;
					this->RectNG[tate][yoko]->Top = tate * this->RectOK[tate][yoko]->Height + 1;
					this->RectNG[tate][yoko]->Right = (yoko + 1) * this->RectOK[tate][yoko]->Width - 1;
					this->RectNG[tate][yoko]->Bottom = (tate + 1)*this->RectOK[tate][yoko]->Height - 1;
				}
			}

		}
	}

	return;

}

//プレイヤーとマップが当たっているか確認
bool MAP::CheckDetectionPlayer(COLLISION *player,int keykind, int *detectionX, int *detectionY)
{

	auto CollisionInit = player;

	switch (keykind)		//キー入力の種類で判別
	{

	case (int)KEY_UP:		//上キーの時

		//領域を少し上へずらす
		player->Top -= RECT_STAGGER;
		player->Bottom -= RECT_STAGGER;

		for (int tate = 0; tate < MAP_TATE; tate++)
		{
			for (int yoko = 0; yoko < MAP_YOKO; yoko++)
			{
				//キャラクターの当たっている場所を取得
				if (this->RectNG[tate][yoko]->DetectionCheck(player))
				{
					*detectionY = tate;	//atariYのアドレスが指し示す先の場所に、当たったモノの縦の位置を入れる
					*detectionX = yoko;	//atariXのアドレスが指し示す先の場所に、当たったモノの横の位置を入れる

					player = CollisionInit;	//ずらした分を元に戻す

					return true;
				}
			}
		}


		break;	//上キーの時ここまで

	case (int)KEY_DOWN:		//下キーの時

		//領域を少し下へずらす
		player->Top += RECT_STAGGER;
		player->Bottom += RECT_STAGGER;

		for (int tate = 0; tate < MAP_TATE; tate++)
		{
			for (int yoko = 0; yoko < MAP_YOKO; yoko++)
			{
				//キャラクターの当たっている場所を取得
				if (this->RectNG[tate][yoko]->DetectionCheck(player))
				{
					*detectionY = tate;	//atariYのアドレスが指し示す先の場所に、当たったモノの縦の位置を入れる
					*detectionX = yoko;	//atariXのアドレスが指し示す先の場所に、当たったモノの横の位置を入れる

					player = CollisionInit;	//ずらした分を元に戻す

					return true;
				}
			}
		}


		break;		//下キーの時ここまで

	case(int)KEY_LEFT:		//左キーの時

		//領域を少し左へずらす
		player->Left -= RECT_STAGGER;
		player->Right -= RECT_STAGGER;

		for (int tate = 0; tate < MAP_TATE; tate++)
		{
			for (int yoko = 0; yoko < MAP_YOKO; yoko++)
			{
				//キャラクターの当たっている場所を取得
				if (this->RectNG[tate][yoko]->DetectionCheck(player))
				{
					*detectionY = tate;	//atariYのアドレスが指し示す先の場所に、当たったモノの縦の位置を入れる
					*detectionX = yoko;	//atariXのアドレスが指し示す先の場所に、当たったモノの横の位置を入れる

					player = CollisionInit;	//ずらした分を元に戻す

					return true;
				}
			}
		}


		break;		//左キーの時ここまで

	case(int)KEY_RIGHT:		//右キーの時

		//領域を少し右へずらす 
		player->Left += RECT_STAGGER;
		player->Right += RECT_STAGGER;

		for (int tate = 0; tate < MAP_TATE; tate++)
		{
			for (int yoko = 0; yoko < MAP_YOKO; yoko++)
			{
				//キャラクターの当たっている場所を取得
				if (this->RectNG[tate][yoko]->DetectionCheck(player))
				{
					*detectionY = tate;	//atariYのアドレスが指し示す先の場所に、当たったモノの縦の位置を入れる
					*detectionX = yoko;	//atariXのアドレスが指し示す先の場所に、当たったモノの横の位置を入れる

					player = CollisionInit;	//ずらした分を元に戻す

					return true;
				}
			}
		}


		break;		//右キーの時ここまで


	default:
		break;
	}


	player = CollisionInit;	//ずらした分を元に戻す

	return false;

}
