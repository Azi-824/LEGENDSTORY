//DATA.cpp
//データクラス

//#################### ヘッダファイル読み込み #################
#include "DATA.hpp"

//#################### クラス定義 #########################

/*
コンストラクタ
//引数：const char *：ファイルのパス
//引数：const char *：名前
*/
DATA::DATA()
{
	return;
}

//デストラクタ
DATA::~DATA()
{
	return;
}

//読み込み(味方のデータ)
bool DATA::LoadPlayer(PLAYER *player,const char *dir,const char *name)
{

	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;	//読み込み失敗

	}


	std::string buf;

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	player->SetName(buf.c_str());	//名前読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	player->SetLevel(atoi(buf.c_str()));	//レベル読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	player->SetMaxEXP(atoi(buf.c_str()));	//経験値の最大値読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	player->SetEXP(atoi(buf.c_str()));	//現在の経験値読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	player->SetMaxHP(atoi(buf.c_str()));	//最大HP読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	player->SetHP(atoi(buf.c_str()));	//現在のHP読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	player->SetMaxMP(atoi(buf.c_str()));	//最大MP読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	player->SetMP(atoi(buf.c_str()));	//現在のMP読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	player->SetATK(atoi(buf.c_str()));	//ATK読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	player->SetDEF(atoi(buf.c_str()));	//DEF読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	player->SetSPD(atoi(buf.c_str()));	//SPD読み込み

	static int x = 0, y = 0;
	std::getline(ifs, buf, ',');	//カンマまで読み込み
	x = atoi(buf.c_str());			//X位置格納
	std::getline(ifs, buf,',');		//カンマまで読み込み
	y = atoi(buf.c_str());			//Y位置格納
	player->SetNowPos(x, y);		//現在位置設定

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	player->SetSkil(atoi(buf.c_str()));	//Skil1読み込み

	std::getline(ifs, buf, '\n');	//最後は改行まで読み込み
	player->SetSkil(atoi(buf.c_str()));	//Skil2読み込み

	return true;	//読み込み成功
}

//読み込み（敵データ）
bool DATA::LoadEnemy(ENEMY *enemy[],const char *dir,const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;
	
	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;	//読み込み失敗

	}


	std::string buf;
	//1行目を読み込んで飛ばす
	std::getline(ifs, buf);	//1行読み込み

		for (int i = 0; i < ENEMY_KIND; ++i)				//敵の種類分読み込み
		{
			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetName(buf.c_str());	//名前読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetMaxHP(atoi(buf.c_str()));	//HP読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetATK(atoi(buf.c_str()));	//ATK読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetDEF(atoi(buf.c_str()));	//DEF読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetSPD(atoi(buf.c_str()));	//SPD読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetEXP(atoi(buf.c_str()));	//EXP読み込み
			
			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetSkil(atoi(buf.c_str()));	//Skil1読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetSkil(atoi(buf.c_str()));	//Skil2読み込み

			std::getline(ifs, buf, ',');	//カンマまで読み込み
			enemy[i]->SetEncounteRate(atoi(buf.c_str()));	//遭遇率読み込み

			std::getline(ifs, buf, '\n');	//最後は改行まで読み込み
			enemy[i]->SetEmergenceMap(atoi(buf.c_str()));	//出現MAP読み込み

		}

		return true;	//読み込み成功

}

//読み込み（アイテムデータ）
bool DATA::LoadItem(ITEM *item[], const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;	//読み込み失敗

	}


	std::string buf;
	//1行目を読み込んで飛ばす（1行目は説明文のため）
	std::getline(ifs, buf);	//1行読み込み

	for (int i = 0; i < ITEM_KIND; ++i)				//アイテムの種類分読み込み
	{

		std::getline(ifs, buf, ',');			//カンマまで読み込み
		item[i]->SetName(buf.c_str());			//名前読み込み

		std::getline(ifs, buf, '\n');			//最後は改行まで読み込み
		item[i]->SetDescription(buf.c_str());	//説明文読み込み

	}

	return true;	//読み込み成功

}

//読み込み（メッセージデータ）
bool DATA::LoadMsg(MESSAGE *msg, const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;	//読み込み失敗

	}


	std::string buf;

		std::getline(ifs, buf);					//1行読み込み
		msg->SetMsg(buf.c_str());				//文字列読み込み

		while (!ifs.eof())	//最後の行まで読み込み
		{
			std::getline(ifs, buf);	//1行読み込み
			msg->AddMsg(buf.c_str());	//文字列追加
		}

		return true;	//読み込み成功

}

//読み込み（現在のマップ位置）
bool DATA::LoadNowMap(int *nowmapdrawkind, int *nowmapkind, const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;	//読み込み失敗

	}

	std::string buf;

	std::getline(ifs, buf, ',');			//カンマまで読み込み
	*nowmapdrawkind = atoi(buf.c_str());	//現在の描画マップの種類

	std::getline(ifs, buf, ',');			//改行まで読み込み
	nowmapkind[0] = atoi(buf.c_str());		//現在のマップの種類
	std::getline(ifs, buf, '\n');			//改行まで読み込み
	nowmapkind[1] = atoi(buf.c_str());		//現在のマップの種類

	return true;			//読み込み成功

}

//セーブ
bool DATA::Save(PLAYER *player ,const char *dir,const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;
	
	std::ofstream ofs(LoadFile.c_str(),std::ios_base::ate);	//ファイルオープン

	if (!ofs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;		//セーブ失敗

	}

	//プレイヤー情報を書き出す
	ofs << player->GetName() << ',';		//名前書き出し
	ofs << player->GetLevel() << ',';		//レベル
	ofs << player->GetMaxEXP() << ',';		//経験値の最大値
	ofs << player->GetEXP() << ',';			//現在の経験値

	ofs << player->GetMaxHP() << ',';		//最大HP
	ofs << player->GetHP() << ',';			//現在のHP
	ofs << player->GetMaxMP() << ',';		//最大MP
	ofs << player->GetMP() << ',' ;			//現在のMP

	ofs << player->GetATK() << ',';			//攻撃力
	ofs << player->GetDEF() << ',';			//防御力
	ofs << player->GetSPD() << ',';			//速さ

	static int x = 0, y = 0;
	player->GetNowPos(&x, &y);	//現在位置取得
	ofs << x << ',' << y << ',';	//現在位置セーブ

	std::vector<int> skil = player->GetSkil();	//スキル一覧を取得

	for (int i = 0; i < skil.size(); ++i)		//スキルの数分書き込む
	{

		ofs << skil[i];					//スキル書き込み

		if (i != skil.size() - 1)		//最後の要素じゃないときは
		{
			ofs << ',';			//カンマで区切る
		}
		else					//最後の要素の時は
		{
			ofs << std::endl;	//改行
		}
	}

	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	skil.swap(v);				//空と中身を入れ替える

	return true;		//セーブ成功
}

//現在のマップ位置をセーブ
bool DATA::SaveMap(int nowmapdrawkind, int nowmapkind[],const char *dir,const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ofstream ofs(LoadFile.c_str(), std::ios_base::ate);	//ファイルオープン

	if (!ofs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(DATA_ERROR_TTILE),
			MB_OK);

		return false;		//セーブ失敗

	}

	//現在のマップ位置を書き出す
	ofs << nowmapdrawkind << ',';		//現在の描画マップの種類
	ofs << nowmapkind[0] << ',' ;		//現在のマップの種類
	ofs << nowmapkind[1] << std::endl;

	return true;		//セーブ成功

}
