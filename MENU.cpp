//MENU.cpp
//メニューウィンドウ用のクラス

//############ ヘッダファイル読み込み ##################
#include "MENU.hpp"

//########### クラス定義 ###################

//コンストラクタ
MENU::MENU()
{
	this->Menu = { "ステータス","アイテム","装備","セーブ" };	//メニューウィンドウの文字列を設定
	this->Menu_itr = this->Menu.begin();	//先頭のアドレスを入れる

	this->X = 100;		//初期位置を100で設定
	this->Y = 100;		//初期位置を100で設定

	this->Width = 100;	//初期幅を100で設定
	this->Height = 180;	//初期高さを180で設定

	this->StrHeight = GetFontSize();	//高さを取得

	return;

}

//デストラクタ
MENU::~MENU()
{
	//vectorのメモリ解放を行う
	std::vector<std::string> v;			//空のvectorを作成する
	this->Menu.swap(v);					//空と中身を入れ替える

	return;

}

//描画
void MENU::Draw(int x,int y)
{

	//描画位置設定
	this->X = x;
	this->Y = y;

	int cnt = 0;	//描画位置用
	
	auto w_itr = this->Menu_itr;	//退避用

	for (this->Menu_itr=this->Menu.begin();this->Menu_itr!=this->Menu.end();++this->Menu_itr)
	{
		if (w_itr == this->Menu_itr)			//選択中の要素だったら
		{
			DrawFormatString(this->X + 10, this->Y + cnt * MENU_SPACE, GetColor(255, 255, 255), "%s\n", this->Menu_itr->c_str());	//右にずらして描画
		}
		else
		{
			DrawFormatString(this->X, this->Y + cnt * MENU_SPACE, GetColor(255, 255, 255), "%s\n", this->Menu_itr->c_str());	//文字描画
		}
		cnt++;
	}

	this->Menu_itr = w_itr;		//選択要素を元に戻す

	return;

}

//選んだ内容ごとの描画
void MENU::DrawChoise(int choise)
{

	switch (choise)			//選んだ内容ごとに処理を分ける
	{

	case (int)MENU_STATUS:	//ステータスを選んだ時の処理ここから

		//ステータス描画処理
		DrawString(400, 300, "ステータス描画", GetColor(255, 255, 255));	//文字描画

		break;				//ステータスを選んだ時の処理ここまで

	case (int)MENU_ITEM:	//アイテムを選んだ時の処理ここから

		//アイテム描画処理
		DrawString(400, 300, "アイテム描画", GetColor(255, 255, 255));	//文字描画

		break;				//アイテムを選んだときの処理ここまで

	case (int)MENU_SOUBI:	//装備を選んだ時の処理ここから

		//装備描画処理
		DrawString(400, 300, "装備描画", GetColor(255, 255, 255));	//文字描画

		break;				//装備を選んだ時の処理ここまで

	case (int)MENU_SAVE:	//セーブを選んだ時の処理ここから

		//セーブ時の描画処理
		DrawString(400, 300, "セーブ中です。", GetColor(255, 255, 255));	//文字描画

		break;				//セーブを選んだ時の処理ここまで

	default:
		break;
	}

	return;
}

//選択要素を次へ移動
void MENU::Next()
{
	if (this->Menu_itr != this->Menu.end() - 1)	//最後の要素で無ければ
	{
		this->Menu_itr++;	//次の要素へ
	}
	return;
}

//選択要素を前へ移動
void MENU::Back()
{
	if (this->Menu_itr != this->Menu.begin())	//最初の要素でなければ
	{
		this->Menu_itr--;	//前の要素へ
	}
	return;
}

//選択要素をリセット
void MENU::Reset()
{
	this->Menu_itr = this->Menu.begin();
	return;
}

//選択した項目を取得
std::vector<std::string>::iterator MENU::GetChoiseMenu()
{
	return this->Menu_itr;
}
