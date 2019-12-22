//MSG.cpp
//メッセージクラス

//################# ヘッダファイル読み込み ######################
#include "MSG.hpp"

//################# クラス定義 ############################

//コンストラクタ
MESSAGE::MESSAGE()
{
	this->X = MSG_DRAW_X;	//描画位置(X)
	this->Y = MSG_DRAW_Y;	//描画位置(Y)

	return;
}

//デストラクタ
MESSAGE::~MESSAGE()
{
	return;
}

//戦闘画面のメッセージ描画
/*
引数：int：現在のバトル状態
引数：int：現在のターン
引数：int：選んだコマンド
*/
void MESSAGE::DrawBattleMsg(int battlestage,int turn,int command,PLAYER *player,ENEMY *enemy)
{
	switch (battlestage)	//バトル状態によって表示する文字列を変える
	{

	case (int)ACT_MSG:		//行動メッセージ表示状態だったら

		if (turn == (int)MY_TURN)	//味方のターンだったら
		{
			if (command == (int)ESCAPE)	//選んだコマンドが逃げるだったら
			{
				DrawString(this->X, this->Y, "上手く逃げ切れた！", GetColor(255, 255, 255));	//文字描画
			}
			else
			{
				this->DrawName(player->GetName());		//名前描画
			}
		}
		else if (turn == (int)ENEMY_TURN)	//敵のターンの時
		{
			this->DrawName(enemy->GetName());		//名前描画
		}

		break;			//行動メッセージ表示状態の処理ここから

	case(int)DRAW_DAMEGE:			//ダメージ描画状態だったら

		if (turn == (int)MY_TURN)		//味方のターンだったら
		{
			this->DrawDamage(turn,player->GetSendDamege());		//与えたダメージ表示
		}
		else if (turn = (int)ENEMY_TURN)	//敵のターンだったら
		{
			this->DrawDamage(turn,player->GetRecvDamege());		//受けたメッセージ表示
		}

		break;				//ダメージ描画状態の処理ここまで

	default:
		break;
	}

	return;
}

//ダメージ描画
void MESSAGE::DrawDamage(int turn, int damege)
{
	if (turn == (int)MY_TURN)		//味方のターンの時
	{
		DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%dのダメージをあたえた", damege);	//ダメージテキスト描画
	}
	else if (turn == (int)ENEMY_TURN)	//敵のターンの時
	{
		DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%dのダメージを受けた", damege);	//ダメージテキスト描画
	}
	return;
}

//名前描画
void MESSAGE::DrawName(const char *name)
{
	DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%sのこうげき！", name);	//敵の名前描画
}
