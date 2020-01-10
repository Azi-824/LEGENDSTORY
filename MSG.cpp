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
	this->IsResultMsgEnd = false;	//リザルトメッセージ表示終了していない
	this->ResultMsgStep = (int)WIN_MSG;	//表示段階は最初

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
void MESSAGE::DrawBattleMsg(int battlestage,int turn,int command,PLAYER *player,ENEMY *enemy,bool push_enter)
{
	switch (battlestage)	//バトル状態によって表示する文字列を変える
	{

	case (int)ACT_MSG:		//行動メッセージ表示状態だったら

		if (turn == (int)MY_TURN)	//味方のターンだったら
		{
			if (command == (int)COMMANDE_ESCAPE)	//選んだコマンドが逃げるだったら
			{
				DrawString(this->X, this->Y, "上手く逃げ切れた！", GetColor(255, 255, 255));	//文字描画
			}
			else if (command == (int)COMMANDE_DEFENSE)	//防御を選んだ時は
			{
				DrawString(this->X, this->Y, "防御している！", GetColor(255, 255, 255));		//文字描画
			}
			else								//それ以外の時は
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
			if (command == (int)COMMANDE_DEFENSE)	//防御を選んだ時は
			{
				DrawString(this->X, this->Y, "防御している！",GetColor(255, 255, 255));		//文字描画
			}
			else						//それ以外の時は
			{
				this->DrawDamage(turn, player->GetSendDamege());		//与えたダメージ表示
			}
		}
		else if (turn == (int)ENEMY_TURN)	//敵のターンだったら
		{
			this->DrawDamage(turn,player->GetRecvDamege());		//受けたダメージ表示
		}

		break;				//ダメージ描画状態の処理ここまで

	case(int)RESULT_MSG:			//リザルトメッセージ表示状態だったら

		if (player->GetIsBattleWin())			//戦闘に勝利していたら
		{
			switch (this->ResultMsgStep)		//リザルトメッセージの表示段階に合わせて表示する文字を変える
			{

			case (int)WIN_MSG:		//戦闘に勝利したメッセージ

				DrawString(this->X, this->Y, "モンスターをやっつけた！", GetColor(255, 255, 255));	//文字描画

				break;

			case (int)EXP_MSG:		//経験値のメッセージ

				DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%dの経験値をゲットした！", enemy->GetEXP());	//取得経験値の表示

				break;

			case(int)LEVELUP_MSG:	//レベルアップのメッセージ

				DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "レベルが上がった！\nレベル%dになった！", player->GetLevel());

				break;

			default:
				break;
			}
			if (push_enter)		//エンターキーを押されたら
			{
				if (player->GetLevUpMsgStartFlg())	//レベルアップしたときは
				{
					if (this->ResultMsgStep < (int)LEVELUP_MSG)	//レベルアップメッセージまで
					{
						this->ResultMsgStep++;	//リザルトメッセージの表示段階を次へ
					}
					else										//それ以外なら
					{
						this->IsResultMsgEnd = true;			//メッセージ表示終了
						player->SetLevUpMsgStartFlg(false);		//レベルアップメッセージ終了
					}
				}
				else			//レベルアップしてないときは
				{
					if (this->ResultMsgStep < (int)EXP_MSG)	//経験値メッセージまで
					{
						this->ResultMsgStep++;	//リザルトメッセージの表示段階を次へ
					}
					else										//それ以外なら
					{
						this->IsResultMsgEnd = true;			//メッセージ表示終了
					}
				}
			}
		}
		else if (player->GetIsBattleWin() == false)	//戦闘に敗北していたら
		{
			DrawString(this->X, this->Y, "全滅してしまった・・・", GetColor(255, 255, 255));	//文字描画
			if (push_enter)	//エンターキーを押されたら
			{
				this->IsResultMsgEnd = true;			//メッセージ表示終了
			}
		}

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

//リザルトメッセージの表示が終了したか設定
void MESSAGE::SetIsResultMsgEnd(bool isend)
{
	this->IsResultMsgEnd = isend;
	return;
}

//リザルトメッセージ関係のメンバーをリセット
void MESSAGE::ResetResultMsg(void)
{
	this->IsResultMsgEnd = false;	//リザルトメッセージ表示終了していない
	this->ResultMsgStep = (int)WIN_MSG;	//表示段階は最初

	return;
}

//リザルトメッセージの表示が終了したか取得
bool MESSAGE::GetIsResultMsgEnd(void)
{
	return this->IsResultMsgEnd;
}

//どのメッセージを描画している状態か取得
int MESSAGE::GetDrawMsgKind(void)
{
	return this->ResultMsgStep;
}
