//ENEMY.cpp
//敵のクラス

//###################### ヘッダファイル読み込み ######################
#include "ENEMY.hpp"

//###################### クラス定義 ##########################

//コンストラクタ
ENEMY::ENEMY(const char *dir,const char *name,const char *charaname)
{
	//メンバ変数初期化
	this->Name = "";
	this->HP = 0;
	this->ATK = 0;
	this->DEF = 0;
	this->SPD = 0;
	this->IsLoad = false;	
	this->IsEffectEnd = false;

	//画像設定
	if (this->SetImage(dir, name))	//画像が読み込めていたら
	{
		this->IsLoad = true;	//読み込めた
	}
	else		//画像が読み込めていなかったら
	{
		this->IsLoad = false;
	}

	this->SetInit();	//初期設定

	this->StateSetInit();	//ステータス初期設定

	this->SetKeyOperation(false);	//キーボードで操作不可

	this->Name = charaname;			//名前設定

	this->SetImagePos(GAME_WIDTH / 2 - this->GetWidth() / 2, GAME_HEIGHT / 2 - this->GetHeight() / 2);	//位置調整(画面中央)

	return;
}

//デストラクタ
ENEMY::~ENEMY()
{
	delete this->AtkEffect;	//AtkEffect破棄
	return;
}

//名前設定
void ENEMY::SetName(const char *name)
{
	this->Name += name;
	return;
}

//HP設定
void ENEMY::SetHP(int hp)
{
	this->HP = hp;
	return;
}

//攻撃力設定
void ENEMY::SetATK(int atk)
{
	this->ATK = atk;
	return;
}

//防御力設定
void ENEMY::SetDEF(int def)
{
	this->DEF = def;
	return;
}

//速度設定
void ENEMY::SetSPD(int spd)
{
	this->SPD = spd;
	return;
}

//敵ステータス初期設定
void ENEMY::StateSetInit()
{
	this->HP = 10;	
	this->ATK = 50;
	this->DEF = 5;
	this->SPD = 5;

	this->SetIsArive(true);	//生きている

	return;
}

//エフェクト設定
bool ENEMY::SetAtkEffect(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop)
{
	this->AtkEffect = new ANIMATION(dir, name, SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, changeSpeed, IsLoop);
	if (this->AtkEffect->GetIsLoad() == false) { return false; }		//読み込み失敗

	return true;

}

//エフェクト関連リセット
void ENEMY::ResetEffect()
{
	this->IsEffectEnd = false;
	this->AtkEffect->ResetIsAnime();
	return;
}

//名前取得
const char * ENEMY::GetName(void)
{
	return this->Name.c_str();
}

//体力取得
int ENEMY::GetHP(void)
{
	return this->HP;
}

//攻撃力取得
int ENEMY::GetATK(void)
{
	return this->ATK;
}

//防御力取得
int ENEMY::GetDEF(void)
{
	return this->DEF;
}

//速度取得
int ENEMY::GetSPD(void)
{
	return this->SPD;
}

//読み込めたかを取得
bool ENEMY::GetIsLoad()
{
	return this->IsLoad;
}

//エフェクト描画終了したか取得
bool ENEMY::GetIeEffectEnd()
{
	return this->IsEffectEnd;
}

//エフェクト描画
void ENEMY::DrawEffect(int x,int y)
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

	if (flg)
	{
		if (this->AtkEffect->GetIsAnimeStop() == false)	//アニメーションが終わってなければ
		{
			this->AtkEffect->DrawEffect(x, y);		//エフェクト描画
		}
		else
		{
			this->IsEffectEnd = true;	//エフェクト描画終了
			flg = false;	//フェードアウトフラグリセット
			cnt = 0;		//フェードアウトカウントリセット
		}

	}

	return;
}
