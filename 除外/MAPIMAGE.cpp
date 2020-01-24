//MAPIMAGE.cpp
//使用するマップチップのクラス

//######################## ヘッダファイル読み込み #####################
#include "MAPIMAGE.hpp"

//####################### クラス定義 ########################

//コンストラクタ
MAPIMAGE::MAPIMAGE()
{
	//メンバ変数初期化
	this->FilePath = "";		//ファイルパス
	this->FileName = "";		//ファイル名

	this->IsLoad = false;

	for (int kind = 0; kind < MAP_IMAGE_KIND; kind++)
	{
		for (int i = 0; i < MAP_BUN_TATE * MAP_BUN_YOKO; i++)
		{
			this->Handle[kind][i] = 0;		//ハンドル
			this->X[kind][i] = 0;			//X位置
			this->Y[kind][i] = 0;			//Y位置
			this->Width[kind][i] = 0;		//幅
			this->Height[kind][i] = 0;		//高さ
		}

	}


	for (int kind = 0; kind < MAP_IMAGE_KIND; kind++)
	{
		//マップ画像を読み込み
		std::string LoadfilePath;		//画像のファイルパスを作成
		LoadfilePath += MY_MAP_IMG_DIR;
		LoadfilePath += MY_MAP_IMAGE;

		//画像を分割して読み込み
		LoadDivGraph(LoadfilePath.c_str(), MAP_BUN_TATE * MAP_BUN_YOKO, MAP_BUN_YOKO, MAP_BUN_TATE, MAP_YOKO_SIZE, MAP_TATE_SIZE, &this->Handle[kind][0]);

		if (this->Handle[kind][0] == -1)	//画像が読み込めなかったとき
		{
			std::string ErrorMsg(MAP_ERROR_MSG);	//エラーメッセージ作成
			ErrorMsg += TEXT('\n');						//改行
			ErrorMsg += LoadfilePath;					//画像のパス

			MessageBox(
				NULL,
				ErrorMsg.c_str(),	//char * を返す
				TEXT(MAP_ERROR_TTILE),
				MB_OK);

			return;
		}

	}

	//サイズ取得
	for (int kind = 0; kind < MAP_IMAGE_KIND; kind++)
	{
		for (int i = 0; i < MAP_BUN_TATE * MAP_BUN_YOKO; i++)
		{
			GetGraphSize(
				this->Handle[kind][i],	//このハンドルの画像の大きさを取得
				&this->Width[kind][i],		//Widthのアドレスを渡す
				&this->Height[kind][i]		//Heightのアドレスを渡す
			);

		}

	}
	this->IsLoad = true;
	return;
}

MAPIMAGE::~MAPIMAGE()
{
	for (int kind = 0; kind < MAP_IMAGE_KIND; kind++)
	{
		for (int i = 0; i < MAP_BUN_TATE * MAP_BUN_YOKO; i++)
		{
			DeleteGraph(this->Handle[kind][i]);	//ハンドル削除
		}

	}
	return;
}

int * MAPIMAGE::GetHandle(int kind)
{
	return &this->Handle[kind][0];		//指定されたマップチップの画像情報を返す
}

bool MAPIMAGE::GetIsLoad(void)
{
	return this->IsLoad;	//読み込めたか
}