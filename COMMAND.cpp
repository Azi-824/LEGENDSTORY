//COMMAND.cpp
//バトルコマンドクラス

//####################### ヘッダファイル読み込み ###########################
#include "COMMAND.hpp"

//####################### クラス定義 ##############################

//コンストラクタ
COMMAND::COMMAND()
{
	this->Command = { "こうげき","ぼうぎょ","まほう","アイテム","にげる" };	//バトルウィンドウの文字列を設定
	this->Command_itr = this->Command.begin();								//先頭のアドレスを入れる

	this->X = 0;		//初期位置を設定
	this->Y = 380;		//初期位置を設定

	this->Width = 800;	//初期幅を設定
	this->Height = 100;	//初期高さを設定


	this->StrHeight = GetFontSize();	//高さを取得
	this->GetWidth();					//先頭文字列の横幅を取得


	return;

}


//デストラクタ
COMMAND::~COMMAND()
{
	//vectorのメモリ解放を行う
	std::vector<std::string> v;			//空のvectorを作成する
	this->Command.swap(v);				//空と中身を入れ替える

	return;

}

//描画
void COMMAND::Draw()
{

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率80％に設定

		DrawBox(this->X, this->Y, this->X + this->Width, this->Y + this->Height, GetColor(0, 0, 0), TRUE);	//塗りつぶしありで四角形を描画

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//描画モードを通常に戻す

		int cnt = 0;	//描画位置用

		auto w_itr = this->Command_itr;	//退避用

		SetFontSize(this->StrHeight * 2);	//フォントサイズを二倍にする

		for (this->Command_itr = this->Command.begin(); this->Command_itr != this->Command.end(); ++this->Command_itr)
		{
			if (w_itr == this->Command_itr)			//選択中の要素だったら
			{
				DrawFormatString(this->X + cnt * COMMAND_SPACE, this->Y + 10, GetColor(255, 255, 255), "%s\n", this->Command_itr->c_str());	//右にずらして描画
			}
			else
			{
				DrawFormatString(this->X + cnt * COMMAND_SPACE, this->Y, GetColor(255, 255, 255), "%s\n", this->Command_itr->c_str());	//文字描画
			}
			cnt++;
		}

		this->Command_itr = w_itr;		//選択要素を元に戻す

		SetFontSize(this->StrHeight);	//フォントサイズを元に戻す


	return;

}

//ダメージ量の描画
void COMMAND::DamegeDraw(const char *name, int damege)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//描画モードを透過ありに変更、透過率80％に設定

	DrawBox(this->X, this->Y, this->X + this->Width, this->Y + this->Height, GetColor(0, 0, 0), TRUE);	//塗りつぶしありで四角形を描画

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//描画モードを通常に戻す

	DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%sのこうげき！\n%dのダメージを受けた", name, damege);	//ダメージテキスト描画

	return;

}

//横幅取得
int COMMAND::GetWidth()
{
	int Strlen = 0;		//文字列の長さ取得用

	Strlen = strlen(this->Command_itr->c_str());

	this->StrWidth = GetDrawStringWidth(this->Command_itr->c_str(), Strlen);	//横幅取得

	return this->StrWidth;

}

//選択しているコマンドを取得
std::vector <std::string>::iterator COMMAND:: GetCommand()
{
	return this->Command_itr;
}

//選択要素を次へ移動
void COMMAND::Next()
{
	if (this->Command_itr != this->Command.end() - 1)	//最後の要素で無ければ
	{
		this->Command_itr++;	//次の要素へ
	}
	return;
}

//選択要素を前へ移動
void COMMAND::Back()
{
	if (this->Command_itr != this->Command.begin())	//最初の要素でなければ
	{
		this->Command_itr--;	//前の要素へ
	}
	return;
}

//初期化する
void COMMAND::Init()
{
	this->Command_itr = this->Command.begin();	//選択要素を最初の要素にする
}
