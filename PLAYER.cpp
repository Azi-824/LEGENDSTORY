//PLAYER.cpp
//プレイヤークラス

//############## ヘッダファイル読み込み ################
#include "PLAYER.hpp"

//############## クラス定義 ##################

//コンストラクタ
PLAYER::PLAYER()
{

	this->Collision = new COLLISION();		//当たり判定の領域を作成

	this->sikaku_draw = new SIKAKU();		//描画領域を作成

	this->Weapon = new WEAPON();			//武器を生成
	this->Armor = new ARMOR();				//防具を生成

	this->Item = new ITEM();				//アイテムを生成

	return;
}

//デストラクタ
PLAYER::~PLAYER()
{
	delete this->Anime;				//Animeを破棄
	delete this->Collision;			//Collisionを破棄
	delete this->Ilast;				//Ilastを破棄
	delete this->sikaku_draw;		//sikaku_drawを破棄
	delete this->Weapon;			//Weaponを破棄
	delete this->Armor;				//Armorを破棄
	delete this->Item;				//Itemを破棄

	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Skil.swap(v);		//空と中身を入れ替える

	return;
}

//初期設定
bool PLAYER::SetInit()
{
	this->Dist = (int)FLONT;	//初期向き設定
	this->MoveSpeed = 2;//初期移動速度設定
	this->InKeyKind = -1;	//押されていないときはー1

	this->ChoiseSkil = this->Skil[0];	//最初は通常攻撃を使用するスキルとして設定する

	this->RecvDamege = 0;	//受けるダメージ0

	//装備関係
	this->EquipAtk = 0;		//装備攻撃力0
	this->EquipDef = 0;		//装備防御力0
	this->Equip_WeaponCode = -1;	//装備している武器のコード番号
	this->Equip_ArmorCode = -1;		//装備している防具のコード番号

	this->Ilast->SetInit();	//画像初期設定
	this->IsKeyDown = false;//キーボード押されていない
	this->IsMenu = false;	//メニューウィンドウ描画されていない
	this->IsActMsg = false;		//行動メッセージ表示していない
	this->IsBattleWin = false;	//戦闘に勝っていない
	this->LevUpMsgStart_flg = false;	//レベルアップメッセージを表示していない
	this->ChengeMapKind = (int) MAP_CHENGE_NONE;			//マップ切り替えなし

	this->BoostPoint = START_BP;		//BPの初期値設定
	this->UseBP = 0;					//使用するBP

	this->Anime->SetSize();			//画像のサイズ設定

	//描画領域作成
	this->sikaku_draw->SetValue(this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->Anime->GetWidth(),
		this->Anime->GetHeight());

	//当たり判定領域作成
	this->Collision->SetValue(this->sikaku_draw->Left + RECT_STAGGER,
		this->sikaku_draw->Top,
		this->Anime->GetWidth() - RECT_STAGGER * 2,
		this->Anime->GetHeight());

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

//現在のMP設定
void PLAYER::SetMP(int mp)
{
	this->NowMP = mp;
}

//使用するスキル設定
void PLAYER::SetChoiseSkil(int type)
{
	this->ChoiseSkil = this->Skil[type];		//指定されたスキルを、使用するスキルとして設定
	return;
}

//キー入力ありか設定
void PLAYER::SetIsKeyDown(bool Iskeydown)
{
	this->IsKeyDown = Iskeydown;
}

//位置を設定
//引数：int：X位置を相対的に指定
//引数：int：Y位置を相対的に指定
void PLAYER::SetPosRelative(int x, int y)
{
	this->Collision->Left += x;	//X位置を設定
	this->Collision->Top += y;	//Y位置を設定

	this->sikaku_draw->Left += x;
	this->sikaku_draw->Top += y;

	//描画領域再設定
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);


	//領域再設定
	this->Collision->SetValue(
		this->Collision->Left,
		this->Collision->Top,
		this->Collision->Width,
		this->Collision->Height);

	return;
}

//位置を設定
//引数：int：X位置を絶対値で指定
//引数：int：Y位置を絶対値で指定
void PLAYER::SetPosAbsolute(int x, int y)
{
	this->Collision->Left = x;	//X位置を設定
	this->Collision->Top = y;	//Y位置を設定

	this->sikaku_draw->Left = x;
	this->sikaku_draw->Top = y;

	//描画領域再設定
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);


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

//戦闘に勝ったか取得
void PLAYER::SetIsBattleWin(bool isbattlewin)
{
	this->IsBattleWin = isbattlewin;
	return;
}

//レベルアップメッセージをスタートしたか取得
void PLAYER::SetLevUpMsgStartFlg(bool start_flg)
{
	this->LevUpMsgStart_flg = start_flg;
	return;
}

//マップ切り替えの種類リセット
void PLAYER::ResetChengeMapKind(void)
{
	this->ChengeMapKind = -1;
	return;
}

//マップ切り替えをしたときにプレイヤーの位置を設定
//引数：int：切り替えた方向
void PLAYER::SetChengePos(int kind)
{
	switch (kind)	//切り替え方向毎に処理
	{

	case (int)MAP_CHENGE_UP:	//上へ切り替えるとき、ここから

		this->SetPosRelative(0, GAME_HEIGHT - (this->Collision->Height + RECT_STAGGER));	//位置を修正

		break;

	case (int)MAP_CHENGE_DOWN:	//下へ切り替えるとき、ここから

		this->SetPosRelative(0, -(this->Collision->Top - RECT_STAGGER));	//位置を修正

		break;

	case (int)MAP_CHENGE_LEFT:	//左へ切り替えるとき、ここから

		this->SetPosRelative(GAME_WIDTH - (this->Collision->Width + RECT_STAGGER), 0);	//位置を修正

		break;

	case (int)MAP_CHENGE_RIGHT:	//右へ切り替えるとき、ここから

		this->SetPosRelative(-(this->Collision->Left - RECT_STAGGER), 0);	//位置を修正

		break;

	default:
		break;
	}

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

//経験値の最大値取得
int PLAYER::GetMaxEXP(void)
{
	return this->MaxEXP;
}

//現在の経験値取得
int PLAYER::GetEXP(void)
{
	return this->NowEXP;
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

//最大MP取得
int PLAYER::GetMaxMP(void)
{
	return this->MaxMP;
}

//現在のMP取得
int PLAYER::GetMP(void)
{
	return this->NowMP;
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

//装備攻撃力取得
int PLAYER::GetEquipAtk(void)
{
	return this->EquipAtk;	//装備攻撃力取得
}

//装備防御力取得
int PLAYER::GetEquipDef(void)
{
	return this->EquipDef;	//装備防御力取得
}

//使用するスキルを取得
int PLAYER::GetChoiseSkil(void)
{
	return this->ChoiseSkil;	
}

//スキル一覧取得
std::vector<int> PLAYER::GetSkil(void)
{
	return this->Skil;
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

//メニュー描画中か取得
bool PLAYER::GetIsMenu()
{
	return this->IsMenu;
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

//戦闘に勝ったか取得
bool PLAYER::GetIsBattleWin()
{
	return this->IsBattleWin;
}

//レベルアップメッセージを表示しているか取得
bool PLAYER::GetLevUpMsgStartFlg()
{
	return this->LevUpMsgStart_flg;
}

//キー入力があるか取得
bool PLAYER::GetIsKeyDown()
{
	return this->IsKeyDown;
}

//切り替えるマップの種類を取得
int PLAYER::GetChengeMapKind()
{
	return this->ChengeMapKind;
}

//操作
void PLAYER::Operation(KEYDOWN *keydown, COLLISION *map[][MAP_YOKO])
{

	static int x = 0, y = 0;	//当たった場所を取得

	if (this->IsMenu ==false && keydown->IsKeyDown(KEY_INPUT_W))		//メニュー描画中でなく、Wキーを押しているとき
	{
		this->IsKeyDown = true;		//キー入力あり
		this->Dist = BACK;			//移動方向を上にする
		this->InKeyKind = (int)KEY_UP;	//キー入力の種類、上

		//領域を少し上へずらす
		this->Collision->Top -= RECT_STAGGER;
		this->Collision->Bottom -= RECT_STAGGER;

		//マップとの当たり判定
		if (this->CheckDetectionMap(map, &x, &y) == false)	//通行できるなら
		{
			this->MoveUp();				//上へ移動
		}

	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_S))	//メニュー描画中でなく、Sキーを押しているとき
	{
		this->IsKeyDown = true;		//キー入力あり
		this->Dist = FLONT;			//移動方向下
		this->InKeyKind = (int)KEY_DOWN;	//キー入力の種類、下

		//領域を少し下へずらす
		this->Collision->Top += RECT_STAGGER;
		this->Collision->Bottom += RECT_STAGGER;

		//マップとの当たり判定
		if (this->CheckDetectionMap(map, &x, &y) == false)	//通行できるなら
		{
			this->MoveDown();				//下へ移動
		}


	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_A))	//メニュー描画中でなく、Aキーを押しているとき
	{
		this->IsKeyDown = true;		//キー入力あり
		this->Dist = LEFT;			//移動方向左
		this->InKeyKind = (int)KEY_LEFT;	//キー入力の種類、左

		//領域を少し左へずらす
		this->Collision->Left -= RECT_STAGGER;
		this->Collision->Right -= RECT_STAGGER;

		//マップとの当たり判定
		if (this->CheckDetectionMap(map, &x, &y) == false)	//通行できるなら
		{
			this->MoveLeft();				//左へ移動
		}

	}
	else if (this->IsMenu == false && keydown->IsKeyDown(KEY_INPUT_D))	//メニュー描画中でなく、Dキーを押しているとき
	{
		this->IsKeyDown = true;		//キー入力あり
		this->Dist = RIGHT;			//移動方向右
		this->InKeyKind = (int)KEY_RIGHT;	//キー入力の種類、右

		//領域を少し右へずらす
		this->Collision->Left += RECT_STAGGER;
		this->Collision->Right += RECT_STAGGER;

		//マップとの当たり判定
		if (this->CheckDetectionMap(map, &x, &y) == false)	//通行できるなら
		{
			this->MoveRight();				//右へ移動
		}

	}
	else
	{
		this->IsKeyDown = false;	//キー入力なし
	}

	//描画領域再設定
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);

	//領域再設定
	this->Collision->SetValue(this->sikaku_draw->Left + RECT_STAGGER,
		this->sikaku_draw->Top,
		this->Anime->GetWidth() - RECT_STAGGER * 2,
		this->Anime->GetHeight());


	return;

}

//描画
void PLAYER::DrawWalk()
{
	if (this->IsDraw)		//描画してよい時
	{
		if (this->IsArive)	//生きているとき
		{
			if (this->IsKeyDown)		//キーボードが押されているとき
			{
				this->Anime->Draw(this->sikaku_draw->Left, this->sikaku_draw->Top, this->Dist, true);	//アニメーションで描画

			}
			else						//キーボードが押されていないとき
			{
				this->Anime->Draw(this->sikaku_draw->Left, this->sikaku_draw->Top, this->Dist, false);	//通常描画
			}
		}
	}
}

//上へ移動
void PLAYER::MoveUp()
{
	if (this->sikaku_draw->Top - this->MoveSpeed >= GAME_TOP)
	{
		this->sikaku_draw->Top -= this->MoveSpeed;	//当たり判定と、描画位置を上へ移動
	}
	else
	{
		this->ChengeMapKind = (int)MAP_CHENGE_UP;//切り替え方向、上
	}

	return;
}

//下へ移動
void PLAYER::MoveDown()
{
	if (this->sikaku_draw->Bottom + this->MoveSpeed <= GAME_HEIGHT)
	{
		this->sikaku_draw->Top += this->MoveSpeed;	//下へ移動
	}
	else
	{
		this->ChengeMapKind = (int)MAP_CHENGE_DOWN;	//切り替え方向、下
	}
	return;
}

//左へ移動
void PLAYER::MoveLeft()
{
	if (this->sikaku_draw->Left - this->MoveSpeed >= GAME_LEFT)
	{
		this->sikaku_draw->Left -= this->MoveSpeed;	//左へ移動
	}
	else
	{
		this->ChengeMapKind = (int)MAP_CHENGE_LEFT;	//切り替え方向、左
	}
	return;
}

//右へ移動
void PLAYER::MoveRight()
{
	if (this->sikaku_draw->Right + this->MoveSpeed <= GAME_WIDTH)
	{
		this->sikaku_draw->Left += this->MoveSpeed;	//右へ移動
	}
	else
	{
		this->ChengeMapKind = (int)MAP_CHENGE_RIGHT;	//切り替え方向、右
	}
	return;
}

//ダメージ計算
void PLAYER::DamegeCalc(ENEMY *enemy,int choiecommand)
{
	switch (choiecommand)		//選択したコマンド
	{

	case(int)COMMANDE_ATACK:				//攻撃を選んだ時の処理ここから

		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 味方の攻撃処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
		if ((this->ATK + this->EquipAtk) > enemy->GetDEF())	//自分の攻撃力が敵の防御力より上だったら
		{
			//this->SendDamege = (this->ATK + this->EquipAtk) - enemy->GetDEF();		//ダメージ量を計算 自分攻撃力(攻撃+装備攻撃) - 敵防御力のダメージを与える
			enemy->SetRecvDamege((this->ATK + this->EquipAtk) - enemy->GetDEF());	//ダメージ量を計算 自分攻撃力(攻撃+装備攻撃) - 敵防御力のダメージを与える
		}
		else								//自分の攻撃力が敵の防御力より下だったら、
		{
			//this->SendDamege = 0;			//与えるダメージは0
			enemy->SetRecvDamege(0);		//敵、受けるダメージ0
		}
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 味方の攻撃処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲



		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 敵の攻撃処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
		if (enemy->GetATK() > (this->DEF + this->EquipDef))		//敵の攻撃力が自分の防御力より上だったら
		{
			this->RecvDamege = enemy->GetATK() - (this->DEF + this->EquipDef);	//敵攻撃力 - 自分防御力(防御+装備防御)のダメージを与える
		}
		else									//敵の攻撃力が自分の防御力より下だったら、
		{
			this->RecvDamege = 0;				//受けるダメージ0
		}
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 敵の攻撃処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


		break;					//攻撃を選んだ時の処理ここまで

	case (int)COMMANDE_DEFENSE:			//防御を選んだ時の処理ここから

		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 味方の攻撃処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
		//this->SendDamege = 0;	//防御を選んだ時はダメージを与えない
		enemy->SetRecvDamege(0);		//敵、受けるダメージ0
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 味方の攻撃処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲



		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 敵の攻撃処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

		//防御力を強化してダメージ計算
		if (enemy->GetATK() > ((this->DEF + this->EquipDef) * DEF_BOOST))		//敵の攻撃力が自分の防御力より上だったら
		{
			this->RecvDamege = enemy->GetATK() - ((this->DEF + this->EquipDef) * DEF_BOOST);	//敵攻撃力 - 自分防御力(防御+装備防御)のダメージを与える
		}
		else									//敵の攻撃力が自分の防御力より下だったら、
		{
			this->RecvDamege = 0;				//受けるダメージ0
		}
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 敵の攻撃処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


		break;					//防御を選んだ時の処理ここまで

	case (int)COMMANDE_MAGIC:			//魔法を選んだ時の処理ここから

		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 味方の攻撃処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼

		//自分の攻撃力を強化してダメージ計算
		//魔法攻撃力を追加して、通常攻撃と分ける予定
		if (((this->ATK + this->EquipAtk)* ATK_BOOST) > enemy->GetDEF())	//自分の攻撃力が敵の防御力より上だったら
		{
			//this->SendDamege = ((this->ATK + this->EquipAtk) * ATK_BOOST) - enemy->GetDEF();		//ダメージ量を計算 自分攻撃力(攻撃+装備攻撃) - 敵防御力のダメージを与える
			enemy->SetRecvDamege(((this->ATK + this->EquipAtk) * ATK_BOOST) - enemy->GetDEF());	//ダメージ量を計算 自分攻撃力(攻撃+装備攻撃) - 敵防御力のダメージを与える
		}
		else								//自分の攻撃力が敵の防御力より下だったら、
		{
			//this->SendDamege = 0;			//与えるダメージは0
			enemy->SetRecvDamege(0);		//敵、受けるダメージ0
		}
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 味方の攻撃処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲



		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 敵の攻撃処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
		if (enemy->GetATK() > (this->DEF + this->EquipDef))		//敵の攻撃力が自分の防御力より上だったら
		{
			this->RecvDamege = enemy->GetATK() - (this->DEF + this->EquipDef);	//敵攻撃力 - 自分防御力(防御+装備防御)のダメージを与える
		}
		else									//敵の攻撃力が自分の防御力より下だったら、
		{
			this->RecvDamege = 0;				//受けるダメージ0
		}
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 敵の攻撃処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


		break;					//魔法を選んだ時の処理ここまで

	case(int)COMMANDE_ITEM:				//アイテムを選んだ時の処理ここから

		//this->SendDamege = 0;		//与えるダメージ0
		enemy->SetRecvDamege(0);		//敵、受けるダメージ0

		//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ 敵の攻撃処理ここから ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
		if (enemy->GetATK() > (this->DEF + this->EquipDef))		//敵の攻撃力が自分の防御力より上だったら
		{
			this->RecvDamege = enemy->GetATK() - (this->DEF + this->EquipDef);	//敵攻撃力 - 自分防御力(防御+装備防御)のダメージを与える
		}
		else									//敵の攻撃力が自分の防御力より下だったら、
		{
			this->RecvDamege = 0;				//受けるダメージ0
		}
		//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ 敵の攻撃処理ここまで ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲


		break;					//アイテムを選んだ時の処理ここまで

	default:
		break;
	}

	return;
}

//ダメージを与える
void PLAYER::DamegeSend(void)
{
	this->NowHP -= this->RecvDamege;	//現在のHPから、受けるダメージを引く

	if (this->NowHP <= 0)	//HPが0以下になったら
	{
		this->NowHP = 0;		//HPは0
		this->IsArive = false;	//死亡
	}

	return;

}

//経験値追加処理
void PLAYER::AddExp(int exp)
{
	this->NowEXP += exp;	//現在の経験値に加算する

	if (this->NowEXP >= this->MaxEXP)		//現在の経験値が経験値の最大値以上になったら
	{
		int work = 0;	//退避用変数
		work = this->NowEXP - this->MaxEXP;	//最大値を超過した分を保管

		this->MaxEXP += EXP_INCREASE_VALUE * this->Level;	//経験値の最大値を増やす(経験値の増え幅 * 現在のレベル)
		this->NowEXP = 0;		//現在の経験値を0に戻す
		this->NowEXP += work;	//超過した分の経験値を加算する

		//ステータスの増加処理
		this->MaxHP += HP_INCREASE_VALUE;	//最大HPを増やす
		this->MaxMP += MP_INCREASE_VALUE;	//最大MPを増やす
		this->ATK += ATK_INCREASE_VALUE;	//攻撃力を増やす
		this->DEF += DEF_INCREASE_VALUE;	//防御力を増やす
		this->SPD += SPD_INCREASE_VALUE;	//速さを増やす

		//HPとMPを全回復させる
		this->NowHP = this->MaxHP;
		this->NowMP = this->MaxMP;

		this->Level++;			//レベルを一つ上げる
		this->LevUpMsgStart_flg = true;	//レベルアップメッセージの表示をスタートする
	}
	return;
}

//現在の位置を取得
/*
引数：int *：X位置をセットする
引数：int *：Y位置をセットする
*/
void PLAYER::GetNowPos(int *x, int *y)
{
	*x = this->sikaku_draw->Left;	//X位置設定
	*y = this->sikaku_draw->Top;	//Y位置設定
	return;
}

//現在の位置を設定
/*
引数：int：現在のX位置
引数：int：現在のY位置
*/
void PLAYER::SetNowPos(int x, int y)
{
	this->sikaku_draw->Left = x;
	this->sikaku_draw->Top = y;

	//描画領域再設定
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);

	//領域再設定
	this->Collision->SetValue(
		this->sikaku_draw->Left + RECT_STAGGER,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width - RECT_STAGGER * 2,
		this->sikaku_draw->Height);


}

//現在のキー入力の種類を取得
int PLAYER::GetInKeyKind(void)
{
	return this->InKeyKind;
}

//マップとの当たり判定(当たった場所を取得する)
bool PLAYER::CheckDetectionMap(COLLISION * map[][MAP_YOKO], int *detectionX, int *detectionY)
{

	for (int tate = 0; tate < MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO; yoko++)
		{
			//キャラクターの当たっている場所を取得
			if (map[tate][yoko]->DetectionCheck(this->Collision))
			{
				*detectionY = tate;	//atariYのアドレスが指し示す先の場所に、当たったモノの縦の位置を入れる
				*detectionX = yoko;	//atariXのアドレスが指し示す先の場所に、当たったモノの横の位置を入れる

				return true;
			}
		}
	}

	return false;
}

//マップとの当たり判定(当たった場所を取得しない)
bool PLAYER::CheckDetectionMap(COLLISION * map[][MAP_YOKO])
{

	for (int tate = 0; tate < MAP_TATE; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO; yoko++)
		{
			//キャラクターの当たっている場所を取得
			if (map[tate][yoko]->DetectionCheck(this->Collision))
			{
				return true;
			}
		}
	}

	return false;
}

//回復させる
void PLAYER::Recovery(void)
{
	this->NowHP = this->MaxHP;	//HP回復
	this->NowMP = this->MaxMP;	//MP回復

	this->IsArive = true;		//生きている

	return;
}

//武器を装備する
void PLAYER::EquipWeapon(int element)
{

	this->Equip_WeaponCode = this->Weapon->GetCode(element);	//装備のコード番号を取得

	this->EquipAtk = this->Weapon->GetAtk(this->Equip_WeaponCode);	//装備コードを基に、装備の攻撃力を取得

	this->Weapon->SetEquipFlg(this->Equip_WeaponCode, true);	//武器を装備している

	return;

}

//武器クラスを取得
WEAPON * PLAYER::GetWeaponClass(void)
{
	return this->Weapon;
}

//武器の攻撃力を設定
void PLAYER::SetWeaponAtk(LIST_WEAPON *list_weapon)
{

	for (int i = 0; i < this->Weapon->GetSize(); ++i)	//武器数分繰り返し
	{
		this->Weapon->SetAtk(list_weapon->GetPower(this->Weapon->GetCode(i)));	//武器攻撃力設定
	}

	return;
}

//ドロップした武器の追加
void PLAYER::AddDropWeapon(int code, int value)
{
	//武器登録
	if (this->Weapon->Add(code))		//未登録だったら
	{
		this->Weapon->SetAtk(value);	//攻撃力登録
	}
	return;
}

//防具を装備する
void PLAYER::EquipArmor(int element)
{

	this->Equip_ArmorCode = this->Armor->GetCode(element);	//装備のコード番号を取得

	this->EquipDef = this->Armor->GetDef(this->Equip_ArmorCode);	//装備コードを基に、装備の防御力を取得

	this->Armor->SetEquipFlg(this->Equip_ArmorCode, true);	//防具を装備している

	return;

}

//防具クラスを取得
ARMOR * PLAYER::GetArmorClass(void)
{
	return this->Armor;
}

//防具の防御力設定
void PLAYER::SetArmorDef(LIST_ARMOR *list_armor)
{
	for (int i = 0; i < this->Armor->GetSize(); ++i)	//防具数分繰り返し
	{
		this->Armor->SetDef(list_armor->GetDefense(this->Armor->GetCode(i)));	//防具防御力設定
	}
	return;
}

//ドロップした防具の追加
void PLAYER::AddDropArmor(int code, int value)
{
	//防具登録
	if (this->Armor->Add(code))	//防具が未登録だったら
	{
		this->Armor->SetDef(value);	//防御力設定
	}
	return;
}

//アイテム使用処理
bool PLAYER::UseItem(int code)
{
	if (this->Item->GetItemType(code) == ITEM_TYPE_HP)	//アイテムタイプがHP回復の場合
	{

		if (this->NowHP == this->MaxHP)	//現在のHPが満タンだったら
		{
			return false;		//アイテムは使用できない
		}

		this->NowHP += this->Item->GetRecovery(code);	//回復量を取得し、現在のHPに加える

		if (this->NowHP > this->MaxHP)	//最大HPより多くなったら
		{
			this->NowHP = this->MaxHP;	//現在のHPを最大HPと同じにする
		}

	}
	else if (this->Item->GetItemType(code) == ITEM_TYPE_MP)	//アイテムタイプがMP回復の場合
	{

		if (this->NowMP == this->MaxMP)		//現在のMPが満タンだったら
		{
			return false;		//アイテムは使用できない
		}

		this->NowMP += this->Item->GetRecovery(code);	//回復量を取得し、現在のMPに加える

		if (this->NowMP > this->MaxMP)		//最大MPより多くなったら
		{
			this->NowMP = this->MaxMP;		//現在のMPを最大MPと同じにする
		}
	}

	this->Item->DecreasePossession(code);	//アイテムの所持数を減らす

	return true;
}

//アイテムクラスを取得
ITEM * PLAYER::GetItemClass(void)
{
	return this->Item;
}

//アイテムの回復量を設定
void PLAYER::SetItemRecovery(LIST_ITEM *list_item)
{
	for (int i = 0; i < this->Item->GetSize(); ++i)	//アイテム数分繰り返し
	{
		this->Item->SetRecovery(list_item->GetRecovery(this->Item->GetCode(i)),	//アイテム回復量設定
			list_item->GetItemType(this->Item->GetCode(i)));					//アイテムタイプ設定	
	}
}

//アイテムの追加処理
void PLAYER::AddDropItem(int code, int value, char type)
{
	this->Item->AddItem(code, value, type);	//アイテム追加

	return;
}

//セーブデータ読み込み
bool PLAYER::LoadData(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ifstream ifs(LoadFile.c_str());	//ファイル読み取り

	if (!ifs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(PLAYER_DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(PLAYER_DATA_ERROR_TTILE),
			MB_OK);

		return false;	//読み込み失敗

	}


	std::string buf;

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->Name = buf.c_str();		//名前読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->Level = atoi(buf.c_str());//レベル読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->MaxEXP = atoi(buf.c_str());//経験値の最大値読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->NowEXP = atoi(buf.c_str());//現在の経験値読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->MaxHP = atoi(buf.c_str());//最大HP読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->NowHP = atoi(buf.c_str());//現在のHP読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->MaxMP = atoi(buf.c_str());//最大MP読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->NowMP = atoi(buf.c_str());//現在のMP読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->ATK = atoi(buf.c_str());	//ATK読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->DEF = atoi(buf.c_str());	//DEF読み込み

	std::getline(ifs, buf, ',');	//カンマまで読み込み
	this->SPD = atoi(buf.c_str());	//SPD読み込み

	int x = 0, y = 0;				//位置取得用
	std::getline(ifs, buf, ',');	//カンマまで読み込み
	x = atoi(buf.c_str());			//X位置格納
	std::getline(ifs, buf, ',');	//カンマまで読み込み
	y = atoi(buf.c_str());			//Y位置格納

	this->SetNowPos(x, y);			//現在位置設定

	int size = 0;					//要素数を入れる変数
	std::getline(ifs, buf, ',');	//カンマまで読み込み
	size = atoi(buf.c_str());		//スキルの数を取得

	for (int i = 0; i < size; ++i)	//スキルの数だけ繰り返し
	{
		std::getline(ifs, buf, ',');				//カンマで読み込み
		this->Skil.push_back(atoi(buf.c_str()));	//スキル読み込み
	}


	//******************* アイテムデータ読み込み ************************
	std::getline(ifs, buf, ',');	//カンマまで読み込み
	size = atoi(buf.c_str());		//アイテム数読み込み

	int code = 0, posse = 0;		//コード番号と所持数

	for (int i = 0; i < size; ++i)	//アイテム数だけ繰り返し
	{
		std::getline(ifs, buf, ',');	//カンマまで読み込み
		code = (atoi(buf.c_str()));		//アイテムコード読み込み
		std::getline(ifs, buf, ',');	//カンマまで読み込み
		posse = (atoi(buf.c_str()));		//所持数設定

		this->Item->LoadData(code, posse);	//読み込んだアイテムデータを設定
	}

	//************************ 武器データ読み込み ****************************
	std::getline(ifs, buf, ',');		//カンマまで読み込み
	size = atoi(buf.c_str());			//武器数読み込み

	for (int i = 0; i < size; ++i)	//武器数分繰り返し
	{
		std::getline(ifs, buf, ',');		//カンマまで読み込み
		code = atoi(buf.c_str());			//武器コード読み込み
		std::getline(ifs, buf, ',');		//カンマまで読み込み
		posse = atoi(buf.c_str());			//所持数読み込み

		this->Weapon->LoadData(code, posse);	//読み込んだデータを設定

	}

	//*********************** 防具データ読み込み ****************************
	std::getline(ifs, buf, ',');		//カンマまで読み込み
	size = atoi(buf.c_str());			//防具数読み込み
	int check = 0;						//改行が入っていないか確認するために使用
	for (int i = 0; i < size; ++i)	//防具数分繰り返し
	{
		std::getline(ifs, buf, ',');		//カンマまで読み込み
		code = atoi(buf.c_str());			//防具コード読み込み
		std::getline(ifs, buf, ',');		//カンマまで読み込み

		if (check = buf.find("\n"))	//読み込んだ文字列の中に改行文字が含まれていたら
		{
			buf[check] = '\0';	//改行を消す
		}

		posse = atoi(buf.c_str());			//所持数読み込み

		this->Armor->LoadData(code, posse);	//読み込んだデータを設定

	}


	return true;	//読み込み成功

}

//セーブ
bool PLAYER::Save(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ofstream ofs(LoadFile.c_str(), std::ios_base::ate);	//ファイルオープン

	if (!ofs)		//ファイルオープン失敗時
	{
		std::string ErrorMsg(PLAYER_DATA_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadFile;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(PLAYER_DATA_ERROR_TTILE),
			MB_OK);

		return false;		//セーブ失敗

	}

	//プレイヤー情報を書き出す
	ofs << this->Name << ',';		//名前書き出し
	ofs << this->Level << ',';		//レベル
	ofs << this->MaxEXP << ',';		//経験値の最大値
	ofs << this->NowEXP << ',';		//現在の経験値

	ofs << this->MaxHP << ',';		//最大HP
	ofs << this->NowHP << ',';		//現在のHP
	ofs << this->MaxMP << ',';		//最大MP
	ofs << this->NowMP << ',';		//現在のMP

	ofs << this->ATK << ',';		//攻撃力
	ofs << this->DEF << ',';		//防御力
	ofs << this->SPD << ',';		//速さ

	int x = 0, y = 0;				//現在の位置取得用
	this->GetNowPos(&x, &y);		//現在位置取得
	ofs << x << ',' << y << ',';	//現在位置セーブ

	ofs << this->Skil.size() << ',';//スキル数書き込み

	for (int i = 0; i < this->Skil.size(); ++i)		//スキルの数分書き込む
	{
		ofs << this->Skil[i] << ',';			//スキル書き込み
	}

	//************************* アイテムデータ書き込み *******************************
	ofs << this->Item->GetSize() << ',';	//アイテム数書き込み

	for (int i = 0; i < this->Item->GetSize(); ++i)	//登録してあるアイテムの数分繰り返す
	{
		ofs << this->Item->GetCode(i) << ',';		//アイテムコード書き出し
		ofs << this->Item->GetPossession(i) << ',';	//所持数書き出し

	}

	//************************* 武器データ読み込み *********************************
	ofs << this->Weapon->GetSize() << ',';	//武器数書き出し

	for (int i = 0; i < this->Weapon->GetSize(); ++i)//武器の数分繰り返す
	{
		ofs << this->Weapon->GetCode(i) << ',';	//武器コード書き出し
		ofs << this->Weapon->GetPossession(i) << ',';	//所持数書き出し
	}

	//**************************** 防具データ読み込み ******************************
	ofs << this->Armor->GetSize() << ',';	//防具数書き出し

	for (int i = 0; i < this->Armor->GetSize(); ++i)	//防具数分繰り返す
	{
		ofs << this->Armor->GetCode(i) << ',';			//防具コード書き出し
		if (i == this->Armor->GetSize()-1)	//最後の書き込みだったら
		{
			ofs << this->Armor->GetPossession(i) << '\n';	//所持数書き出し(最後は改行)
		}
		else	//最後じゃなかったら
		{
			ofs << this->Armor->GetPossession(i) << ',';	//所持数書き出し(カンマで区切る)
		}
	}

	return true;		//セーブ成功

}

//BP取得
int PLAYER::GetBP(void)
{
	return this->BoostPoint;
}

//BP加算
void PLAYER::AddBP(void)
{
	if (this->BoostPoint < MAX_BP)	//現在のBPがBPの最大値より小さかったら
	{
		++this->BoostPoint;
	}
	return;
}

//使用するBPを取得
int PLAYER::GetUseBP(void)
{
	return this->UseBP;
}

//使用するBPを増やす
void PLAYER::PlusUseBP(void)
{
	if (this->UseBP < this->BoostPoint)	//使用するBPが現在持っているBPよりも少なかったら
	{
		if (this->UseBP < MAX_USE_BP)	//現在の使用BPが、一回で使用できるBPよりも少なかったら
		{
			++this->UseBP;	//使用するBPを増やす
		}
	}
	return;
}

//使用するBPを減らす
void PLAYER::MinusUseBP(void)
{
	if (this->UseBP > 0)	//使用するBPが0より多かったら
	{
		--this->UseBP;		//使用するBPを減らす
	}
	return;
}
