//MENU.cpp
//メニューウィンドウ用のクラス

//############ ヘッダファイル読み込み ##################
#include "MENU.hpp"

//########### クラス定義 ###################

//コンストラクタ
MENU::MENU()
{
	this->X = 0;		
	this->Y = 0;		

	this->Width = 0;	
	this->Height = 0;	

	this->StrHeight = GetFontSize();	//高さを取得

	this->IsChoise = false;		//選択されていない

	return;

}

//デストラクタ
MENU::~MENU()
{
	return;
}


//選んだ内容ごとの描画
void MENU::DrawChoise(int choise,PLAYER *player,ITEM *item[])
{

	switch (choise)			//選んだ内容ごとに処理を分ける
	{

	case (int)MENU_STATUS:	//ステータスを選んだ時の処理ここから

		//ステータス描画処理
		//DrawString(400, 300, "ステータス描画", GetColor(255, 255, 255));	//文字描画

		//ステータス描画
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%s\nHP %d/%d\nMP %d/%d\nATK %d\nDEF %d\nSPD %d",
			player->GetName(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetATK(), player->GetDEF(), player->GetSPD());

		break;				//ステータスを選んだ時の処理ここまで

	case (int)MENU_ITEM:	//アイテムを選んだ時の処理ここから

		//アイテム描画処理
		//DrawString(400, 300, "アイテム描画", GetColor(255, 255, 255));	//文字描画

		for (int cnt = 0; cnt < ITEM_KIND; ++cnt)
		{
			DrawFormatString(0, cnt * MENU_SPACE, GetColor(255, 255, 255), "%s %s\n", item[cnt]->GetName(), item[cnt]->GetDescription());
		}

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

//選択要素をリセット
void MENU::Reset()
{
	//this->Menu_itr = this->Menu.begin();
	this->IsChoise = false;
	return;
}
//選択されているか設定
void MENU::SetIsChoise(bool Ischoise)
{
	this->IsChoise = Ischoise;
	return;
}

//選択されているか取得
bool MENU::GetIsChoise(void)
{
	return this->IsChoise;
}
