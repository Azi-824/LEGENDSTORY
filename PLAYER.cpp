//PLAYER.cpp
//プレイヤークラス

//############## ヘッダファイル読み込み ################
#include "PLAYER.hpp"

//############## クラス定義 ##################

//コンストラクタ
PLAYER::PLAYER()
{
	this->Skil.push_back(NOMAL_ATACK);	//通常攻撃のスキル
	this->Skil.push_back(MAGIC_2);		//魔法2のスキル
	return;
}

//デストラクタ
PLAYER::~PLAYER()
{
	delete this->Anime;
	delete this->AtkEffect;
	delete this->Collision;
	delete this->Ilast;

	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Skil.swap(v);		//空と中身を入れ替える

	return;
}

//初期設定
bool PLAYER::SetInit()
{
	this->Level = 1;		//初期レベル設定
	this->MaxHP = 100;		//初期最大HP設定
	this->NowHP = this->MaxHP;//初期現在のHP設定
	this->MP = 100;		//初期MP設定
	this->ATK = 10;		//初期攻撃力設定
	this->DEF = 10;		//初期防御力設定
	this->SPD = 10;		//初期速度設定
	this->Dist = FLONT;	//初期向き設定
	this->MoveSpeed = 5;//初期移動速度設定

	this->ChoiseSkil = this->Skil[0];	//最初は通常攻撃を使用するスキルとして設定する

	this->SendDamege = 0;	//与えるダメージ0
	this->RecvDamege = 0;	//受けるダメージ0

	this->Ilast->SetInit();	//画像初期設定
	this->IsKeyDown = false;//キーボード押されていない
	this->IsMenu = false;	//メニューウィンドウ描画されていない
	this->EffectEnd = false;	//エフェクト描画処理終了していない
	this->IsActMsg = false;		//行動メッセージ表示していない

	this->Collision = new COLLISION();		//当たり判定の領域を作成
	this->Collision->SetValue(GAME_LEFT, GAME_TOP, this->Anime->GetWidth(),this->Anime->GetHeight());	//当たり判定の領域を設定

	return true;
}

//アニメーション画像設定
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
//引　数：int：画像の総分割数
//引　数：int：画像の横向きの分割数
//引　数：int：画像の縦向きの分割数
//引　数：int：画像の分割された横の大きさ
//引　数：int：画像の分割された縦の大きさ
//引　数：double：次の画像に変更する速さ
//引　数：bool：アニメーションをループするかどうか
bool PLAYER::SetAnime(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	this->Anime = new ANIMATION(dir, name, SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
	if (this->Anime->GetIsLoad() == false) { return false; }		//読み込み失敗

	return true;

}

//エフェクト画像設定
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
//引　数：int：画像の総分割数
//引　数：int：画像の横向きの分割数
//引　数：int：画像の縦向きの分割数
//引　数：int：画像の分割された横の大きさ
//引　数：int：画像の分割された縦の大きさ
//引　数：double：次の画像に変更する速さ
//引　数：bool：アニメーションをループするかどうか

bool PLAYER::AddEffect(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	this->AtkEffect = new ANIMATION(dir, name, SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
	if (this->AtkEffect->GetIsLoad() == false) { return false; }		//読み込み失敗

	return true;

}

//魔法エフェクトの画像設定
bool PLAYER::AddMagicEffect(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	this->MagicEffect = new ANIMATION(dir, name, SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
	if (this->MagicEffect->GetIsLoad() == false) { return false; }		//読み込み失敗

	return true;

}


//名前設定
void PLAYER::SetName(const char *name)
{
	this->Name = name;
	return;
}

//画像設定
bool PLAYER::SetImage(const char *dir, const char *name)
{
	this->Ilast = new CHARACTOR();
	if (this->Ilast->SetImage(dir, name) == false) { return false; }//読み込み失敗

	return true;

}

//エフェクト関連のリセット
void PLAYER::EffectReset()
{
	this->EffectEnd = false;			//エフェクト描画終了していない
	this->AtkEffect->ResetIsAnime();	//エフェクトのアニメーション処理リセット
	this->MagicEffect->ResetIsAnime();	//魔法エフェクトのアニメーション処理リセット
	return;
}

//レベル設定
void PLAYER::SetLevel(int level)
{
	this->Level = level;
	return;
}

//最大HP設定
void PLAYER::SetMaxHP(int hp)
{
	this->MaxHP = hp;
	return;
}

//現在のHP設定
void PLAYER::SetHP(int hp)
{
	this->NowHP -= hp;
	return;
}

//MP設定
void PLAYER::SetMP(int mp)
{
	this->MP += mp;
}

//攻撃力設定
void PLAYER::SetATK(int atk)
{
	this->ATK = atk;
	return;
}

//防御力設定
void PLAYER::SetDEF(int def)
{
	this->DEF = def;
	return;
}

//速度設定
void PLAYER::SetSPD(int spd)
{
	this->SPD = spd;
	return;
}

//使用するスキル設定
void PLAYER::SetChoiseSkil(int type)
{
	this->ChoiseSkil = this->Skil[type];		//指定されたスキルを、使用するスキルとして設定
	return;
}

//移動速度設定
void PLAYER::SetMoveSpeed(int movespeed)
{
	this->MoveSpeed = movespeed;
	return;
}

//生きているか設定
void PLAYER::SetIsArive(bool Isarive)
{
	this->IsArive = Isarive;
	return;
}

//キーボードで操作できるか設定
void PLAYER::SetKeyOperation(bool Iskeyoperation)
{
	this->IsKeyOperation = IsKeyOperation;
	return;
}


//描画できるか設定
void PLAYER::SetIsDraw(bool Isdraw)
{
	this->IsDraw = IsDraw;
	return;
}

//位置を設定
//引数：int：X位置を相対的に指定
//引数：int：Y位置を相対的に指定
void PLAYER::SetPosition(int x, int y)
{
	this->Collision->Left += x;	//X位置を設定
	this->Collision->Top += y;	//Y位置を設定

	//領域再設定
	this->Collision->SetValue(
		this->Collision->Left,
		this->Collision->Top,
		this->Collision->Width,
		this->Collision->Height);

	return;
}

//メニュー描画中か設定
void PLAYER::SetIsMenu(bool ismenu)
{
	this->IsMenu = ismenu;
	return;
}

//名前取得
const char * PLAYER::GetName(void)
{
	return this->Name.c_str();
}

//レベル取得
int PLAYER::GetLevel(void)
{
	return this->Level;
}

//最大体力取得
int PLAYER::GetMaxHP(void)
{
	return this->MaxHP;
}

//現在の体力取得
int PLAYER::GetHP(void)
{
	return this->NowHP;
}

//MP取得
int PLAYER::GetMP(void)
{
	return this->MP;
}

//攻撃力取得
int PLAYER::GetATK(void)
{
	return this->ATK;
}

//防御力取得
int PLAYER::GetDEF(void)
{
	return this->DEF;
}

//速度取得
int PLAYER::GetSPD(void)
{
	return this->SPD;
}

//使用するスキルを取得
int PLAYER::GetChoiseSkil(void)
{
	return this->ChoiseSkil;	
}

//移動速度取得
int PLAYER::GetMoveSpeed(void)
{
	return this->MoveSpeed;
}

//生きているか取得
bool PLAYER::GetIsArive()
{
	return this->IsArive;
}

//描画できるか取得
bool PLAYER::GetIsDraw()
{
	return this->IsDraw;
}

//キーボード操作できるか取得
bool PLAYER::GetKeyOperation()
{
	return this->IsKeyOperation;
}

//当たり判定を取得
COLLISION * PLAYER::GetCollision()
{
	return this->Collision;
}

//エフェクト描画処理が終了したか取得
bool PLAYER::GetEffectEnd()
{
	return this->EffectEnd;
}

//メニュー描画中か取得
bool PLAYER::GetIsMenu()
{
	return this->IsMenu;
}

//与えるダメージを取得
int PLAYER::GetSendDamege()
{
	return this->SendDamege;
}

//受けるダメージを取得
int PLAYER::GetRecvDamege()
{
	return this->RecvDamege;
}

//行動メッセージ表示中か取得
bool PLAYER::GetIsActMsg()
{
	return this->IsActMsg;
}

//移動中かどうか取得
bool PLAYER::GetIsMove()
{
	return this->IsKeyDown;
}

//操作
void PLAYER::Operation(KEYDOWN *keydown)
{

	if (this->IsMenu ==false && keydown->IsKeyDown(KEY_INPUT_W))		//メニュー描画中でなく、Wキーを押しているとき
	{
		this->IsKeyDown = true;		//キー入力あり
		this->Dist = BACK;			//移動方向を上にする
		this->MoveUp();				//上へ移動
	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_S))	//メニュー描画中でなく、Sキーを押しているとき
	{
		this->IsKeyDown = true;		//キー入力あり
		this->Dist = FLONT;			//移動方向下
		this->MoveDown();			//下へ移動
	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_A))	//メニュー描画中でなく、Aキーを押しているとき
	{
		this->IsKeyDown = true;		//キー入力あり
		this->Dist = LEFT;			//移動方向左
		this->MoveLeft();			//左へ移動
	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_D))	//メニュー描画中でなく、Dキーを押しているとき
	{
		this->IsKeyDown = true;		//キー入力あり
		this->Dist = RIGHT;			//移動方向右
		this->MoveRight();			//右へ移動
	}
	else
	{
		this->IsKeyDown = false;	//キー入力なし
	}



	//領域再設定
	this->Collision->SetValue(
		this->Collision->Left,
		this->Collision->Top,
		this->Collision->Width,
		this->Collision->Height);

	return;

}

//描画
void PLAYER::DrawAnime()
{
	if (this->IsDraw)		//描画してよい時
	{
		if (this->IsArive)	//生きているとき
		{
			if (this->IsKeyDown)		//キーボードが押されているとき
			{
				this->Anime->Draw(this->Collision->Left, this->Collision->Top, this->Dist, true);	//アニメーションで描画

			}
			else						//キーボードが押されていないとき
			{
				this->Anime->Draw(this->Collision->Left, this->Collision->Top, this->Dist, false);	//通常描画
			}
		}
	}
}

//攻撃エフェクト描画
void PLAYER::DrawAtk(int x, int y)
{
		if (this->AtkEffect->GetIsAnimeStop() == false)	//アニメーション描画が終わっていない場合
		{
			this->AtkEffect->DrawEffect(x, y);		//アニメーション描画
		}
		else			//アニメーション描画が終わったら
		{
			this->EffectEnd = true;	//エフェクト描画処理終了
		}
	return;
}

//魔法エフェクト描画
void PLAYER::DrawMagic(int x, int y)
{

	static int cnt = 0;		//フェードアウト用
	static int cntMax = 60;	//フェードアウト用
	static bool flg = false;//フェードアウト終了フラグ

	//60フレーム分、待つ
	if (cnt < cntMax)
	{
		cnt++;	//カウントアップ
	}
	else
	{
		flg = true;	//フェードアウト処理終了
	}

	//フェードアウトの処理
	double ToukaPercent = (cnt / 2) / (double)cntMax;//透過％を求める
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * 255);	//透過させる
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);	//真っ暗な画面にする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//透過をやめる
	
	if (flg)	//フェードアウトが終わったら
	{
		if (this->MagicEffect->GetIsAnimeStop() == false)	//アニメーション描画が終わっていない場合
		{
			this->MagicEffect->DrawEffect(x, y);		//アニメーション描画
		}
		else			//アニメーション描画が終わったら
		{
			this->EffectEnd = true;	//エフェクト描画処理終了
			flg = false;	//フェードアウトフラグリセット
			cnt = 0;		//フェードアウトカウントリセット
		}

	}

	return;
}


//上へ移動
void PLAYER::MoveUp()
{
	if (this->Collision->Top - this->MoveSpeed >= GAME_TOP)
	{
		this->Collision->Top -= this->MoveSpeed;	//当たり判定と、描画位置を上へ移動
	}

	return;
}

//下へ移動
void PLAYER::MoveDown()
{
	if (this->Collision->Bottom + this->MoveSpeed <= GAME_HEIGHT)
	{
		this->Collision->Top += this->MoveSpeed;	//下へ移動
	}
	return;
}

//左へ移動
void PLAYER::MoveLeft()
{
	if (this->Collision->Left - this->MoveSpeed >= GAME_LEFT)
	{
		this->Collision->Left -= this->MoveSpeed;	//左へ移動
	}
	return;
}

//右へ移動
void PLAYER::MoveRight()
{
	if (this->Collision->Right + this->MoveSpeed <= GAME_WIDTH)
	{
		this->Collision->Left += this->MoveSpeed;	//右へ移動
	}
	return;
}

//ダメージ計算
void PLAYER::DamegeCalc(ENEMY *enemy)
{
	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 味方の攻撃処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (this->ATK > enemy->GetDEF())	//自分の攻撃力が敵の防御力より上だったら
	{
		this->SendDamege = this->ATK - enemy->GetDEF();		//ダメージ量を計算 自分攻撃力 - 敵防御力のダメージを与える
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 味方の攻撃処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲



	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 敵の攻撃処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	if (enemy->GetATK() > this->DEF)		//敵の攻撃力が自分の防御力より上だったら
	{
		this->RecvDamege= enemy->GetATK() - this->DEF;	//敵攻撃力 - 自分防御力のダメージを与える
	}
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 敵の攻撃処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲

	return;
}
