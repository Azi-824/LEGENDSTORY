//MAP.cpp
//マップクラス

//################## ヘッダファイル読み込み #####################
#include "MAP.hpp"

//################## クラス定義 #####################
//コンストラクタ
MAP::MAP()
{
	//メンバ変数初期化
	this->FilePath = "";		//ファイルパス
	this->FileName = "";		//ファイル名

	for (int i = 0; i < MAP_BUN_TATE * MAP_BUN_YOKO; i++)
	{
		this->Handle[i] = 0;	//ハンドル
		this->X[i] = 0;			//X位置
		this->Y[i] = 0;			//Y位置
		this->Width[i] = 0;		//幅
		this->Height[i] = 0;	//高さ
	}

	for (int tate = 0; tate < MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO; yoko++)
		{
			MapData[tate][yoko] = 0;	//マップデータ
		}
	}

	//マップ画像を読み込み
	std::string LoadfilePath;		//画像のファイルパスを作成
	LoadfilePath += MY_MAP_IMG_DIR;
	LoadfilePath += MY_MAP_IMAGE;

	//画像を分割して読み込み
	LoadDivGraph(LoadfilePath.c_str(), MAP_BUN_TATE * MAP_BUN_YOKO, MAP_BUN_YOKO, MAP_BUN_TATE, MAP_YOKO_SIZE, MAP_TATE_SIZE, &this->Handle[0]);

	if (this->Handle[0] == -1)	//画像が読み込めなかったとき
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

	for (int i = 0; i < MAP_BUN_TATE * MAP_BUN_YOKO; i++)
	{
		GetGraphSize(
			this->Handle[0],	//このハンドルの画像の大きさを取得
			&this->Width[0],		//Widthのアドレスを渡す
			&this->Height[0]		//Heightのアドレスを渡す
		);

	}
	return;
}

//デストラクタ
MAP::~MAP()
{
	for (int i = 0; i < MAP_BUN_TATE * MAP_BUN_YOKO; i++)
	{
		DeleteGraph(this->Handle[i]);	//ハンドル削除
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

//描画
void MAP::Draw()
{
	for (int tate = 0; tate < MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO; yoko++)
		{
			DrawGraph(yoko*MAP_YOKO_SIZE, tate*MAP_TATE_SIZE, this->Handle[this->MapData[tate][yoko]], TRUE);	//マップ描画
		}
	}

	return;
}
