//MAP.cpp
//マップクラス

//################## ヘッダファイル読み込み #####################
#include "MAP.hpp"

//################## クラス定義 #####################
//コンストラクタ
MAP::MAP(const char *dir,const char *name)
{

	this->Map_Image = new IMAGE(dir, name);	//マップ画像作成

	this->MapOKKind[0] = (int)MAP_OK_KIND1;	//通行できるマップの種類
	this->MapEncountKind[0] = (int)MAP_OK_KIND_ENCOUNT;	//通行できるマップの種類(敵と遭遇する)
	this->MapNGKind[0] = (int)MAP_NG_KIND1;			//通行できないマップの種類

	for (int tate = 0; tate < MAP_TATE; ++tate)
	{
		for (int yoko = 0; yoko < MAP_YOKO; ++yoko)
		{
			this->RectOK[tate][yoko] = new COLLISION();	//当たり判定の領域を作成(通行できる)
			this->RectEncount[tate][yoko] = new COLLISION();//当たり判定の領域を作成(敵と遭遇する)
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
			delete this->RectEncount[tate][yoko];//当たり判定を破棄(敵と遭遇する)
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

	this->CreateRect();			//当たり判定作成

	return true;

}

//マップを切り替える
//引数：int	  ：マップ切り替えの種類
//引数：int	　：現在のマップのX座標とY座標の情報
int MAP::ChengeMap(int kind,int *mapnowpos)
{

	switch (kind)	//マップ変更の種類
	{

	case (int)MAP_CHENGE_UP:	//上へ切り替えるとき、ここから

		if ((mapnowpos[POS_Y]) > 0)	//上のマップがある場合は
		{
			mapnowpos[POS_Y]--;	//上のマップへ

			return (int)MAP_CHENGE_UP;//切り替え方向、上
		}

		break;	//上へ切り替えるとき、ここまで

	case (int)MAP_CHENGE_DOWN:	//下へ切り替えるとき、ここから

		if ((mapnowpos[POS_Y]) < MAP_DATA_TATE_KIND - 1)	//下のマップがある場合は
		{
			mapnowpos[POS_Y]++;	//下のマップへ

			return (int)MAP_CHENGE_DOWN;	//切り替え方向、下
		}

		break;	//下へ切り替えるとき、ここまで

	case (int)MAP_CHENGE_LEFT:	//左へ切り替えるとき、ここから

			if (mapnowpos[POS_X] - 1 >= 0)	//横にマップがある場合は
			{
				mapnowpos[POS_X]--;	//左のマップへ

				return (int)MAP_CHENGE_LEFT;	//切り替え方向、左

			}

		break;	//下へ切り替えるとき、ここまで

	case (int)MAP_CHENGE_RIGHT:	//右へ切り替えるとき、ここから

			if (mapnowpos[POS_X] + 1 < MAP_DATA_YOKO_KIND)	//横にマップがある場合は
			{
				mapnowpos[POS_X]++;	//右のマップへ

				return (int)MAP_CHENGE_RIGHT;	//切り替え方向、右

			}

		break;	//右へ切り替えるとき、ここまで

	default:
		break;
	}

	return (int)MAP_CHENGE_NONE;	//切り替えなし
}

//描画
void MAP::Draw()
{
	this->Map_Image->Draw(0, 0);

	return;
}

//当たり判定の領域を作成
/*
引数：int *：通行できるマップのナンバー
引数：int *：通行できないマップのナンバー
*/
void MAP::CreateRect()
{
	for (int tate = 0; tate < MAP_TATE; ++tate)
	{
		for (int yoko = 0; yoko < MAP_YOKO; ++yoko)
		{
			
			//当たり判定の領域を作成(通行できる)
			for (int cnt = 0; cnt < MAP_OK_KIND; ++cnt)
			{
				if (this->MapData[tate][yoko] == this->MapOKKind[cnt])
				{
					this->RectOK[tate][yoko]->Left = yoko * this->RectOK[tate][yoko]->Width;
					this->RectOK[tate][yoko]->Top = tate * this->RectOK[tate][yoko]->Height;
					this->RectOK[tate][yoko]->Right = (yoko + 1) * this->RectOK[tate][yoko]->Width;
					this->RectOK[tate][yoko]->Bottom = (tate + 1)*this->RectOK[tate][yoko]->Height;

				}
			}

			//当たり判定の領域を作成(敵と遭遇する)
			for (int cnt = 0; cnt < MAP_ENCOUNT_KIND; ++cnt)
			{
				if (this->MapData[tate][yoko] == this->MapEncountKind[cnt])
				{
					this->RectEncount[tate][yoko]->Left = yoko * this->RectEncount[tate][yoko]->Width;
					this->RectEncount[tate][yoko]->Top = tate * this->RectEncount[tate][yoko]->Height;
					this->RectEncount[tate][yoko]->Right = (yoko + 1) * this->RectEncount[tate][yoko]->Width;
					this->RectEncount[tate][yoko]->Bottom = (tate + 1)*this->RectEncount[tate][yoko]->Height;

				}
			}

			//当たり判定の領域を作成(通行できない)
			for (int cnt = 0; cnt < MAP_NG_KIND; ++cnt)
			{
				if (this->MapData[tate][yoko] == this->MapNGKind[cnt])
				{
					this->RectNG[tate][yoko]->Left = yoko * this->RectNG[tate][yoko]->Width;
					this->RectNG[tate][yoko]->Top = tate * this->RectNG[tate][yoko]->Height;
					this->RectNG[tate][yoko]->Right = (yoko + 1) * this->RectNG[tate][yoko]->Width;
					this->RectNG[tate][yoko]->Bottom = (tate + 1)*this->RectNG[tate][yoko]->Height;
				}
			}

		}
	}

	return;

}
