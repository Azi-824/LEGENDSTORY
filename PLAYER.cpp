//PLAYER.cpp
//プレイヤークラス

//############## ヘッダファイル読み込み ################
#include "PLAYER.hpp"

//############## クラス定義 ##################

//コンストラクタ
PLAYER::PLAYER()
{
	return;
}

//デストラクタ
PLAYER::~PLAYER()
{
	delete Anime;
	delete Collision;
	delete Ilast;
	return;
}

//初期設定
bool PLAYER::SetInit()
{
	this->HP = 100;		//初期HP設定
	this->ATK = 10;		//初期攻撃力設定
	this->DEF = 10;		//初期防御力設定
	this->SPD = 10;		//初期速度設定
	this->Dist = FLONT;	//初期向き設定
	this->MoveSpeed = 5;//初期移動速度設定

	this->Ilast->SetInit();	//画像初期設定
	this->IsKeyDown = false;//キーボード押されていない

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

//画像設定
bool PLAYER::SetImage(const char *dir, const char *name)
{
	this->Ilast = new CHARACTOR();
	if (this->Ilast->SetImage(dir, name) == false) { return false; }//読み込み失敗

	return true;

}

//HP設定
void PLAYER::SetHP(int hp)
{
	this->HP = hp;
	return;
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

//体力取得
int PLAYER::GetHP(void)
{
	return this->HP;
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

//操作
void PLAYER::Operation(KEYDOWN *keydown)
{

	if (keydown->IsKeyDown(KEY_INPUT_W))		//Wキーを押しているとき
	{
		this->IsKeyDown = true;
		this->MoveUp();							//上へ移動
	}
	else if (keydown->IsKeyDown(KEY_INPUT_S))	//Sキーを押しているとき
	{
		this->IsKeyDown = true;
		this->MoveDown();						//下へ移動
	}
	else if (keydown->IsKeyDown(KEY_INPUT_A))	//Aキーを押しているとき
	{
		this->IsKeyDown = true;
		this->MoveLeft();						//左へ移動
	}
	else if (keydown->IsKeyDown(KEY_INPUT_D))	//Dキーを押しているとき
	{
		this->IsKeyDown = true;
		this->MoveRight();						//右へ移動
	}
	else
	{
		this->IsKeyDown = false;
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

	if (this->IsKeyDown)		//キーボードが押されているとき
	{
		this->Anime->Draw(this->Collision->Left, this->Collision->Top, this->Dist, true);	//アニメーションで描画

	}
	else						//キーボードが押されていないとき
	{
		this->Anime->Draw(this->Collision->Left, this->Collision->Top, this->Dist, false);	//通常描画
	}
}

//上へ移動
void PLAYER::MoveUp()
{
	if (this->Collision->Top - this->MoveSpeed >= GAME_TOP)
	{
		this->Collision->Top -= this->MoveSpeed;	//当たり判定と、描画位置を上へ移動
		this->Dist = BACK;	//移動方向を上にする
	}

	return;
}

//下へ移動
void PLAYER::MoveDown()
{
	if (this->Collision->Bottom + this->MoveSpeed <= GAME_HEIGHT)
	{
		this->Collision->Top += this->MoveSpeed;	//下へ移動
		this->Dist = FLONT;	//移動方向下
	}
	return;
}

//左へ移動
void PLAYER::MoveLeft()
{
	if (this->Collision->Left - this->MoveSpeed >= GAME_LEFT)
	{
		this->Collision->Left -= this->MoveSpeed;	//左へ移動
		this->Dist = LEFT;	//移動方向左
	}
	return;
}

//右へ移動
void PLAYER::MoveRight()
{
	if (this->Collision->Right + this->MoveSpeed <= GAME_WIDTH)
	{
		this->Collision->Left += this->MoveSpeed;	//右へ移動
		this->Dist = RIGHT;	//移動方向右
	}
	return;
}

