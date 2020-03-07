//SELECT.cpp
//選択肢を管理するクラス


//###################### ヘッダファイル読み込み ######################
#include "SELECT.hpp"

//###################### クラス定義 ##########################


//デストラクタ
SELECT::~SELECT()
{

	delete this->image_ui;	//UI画像破棄

	//vectorのメモリ解放を行う
	std::vector<std::string> v;			//空のvectorを作成する
	this->Str.swap(v);					//空と中身を入れ替える

	return;

}

//選択肢のキー操作
/*
戻り値：エンターキーを押されたら:true
戻り値：エンターキー押されていなければ:false
*/
bool SELECT::SelectOperation(KEYDOWN *keydown,MUSIC *se)
{

	if (this->IsKeyOpe)		//キー操作可能なら
	{
		if (keydown->IsKeyDownOne(KEY_INPUT_W))		//Wキーを押されたら
		{
			if (this->Str_itr != this->Str.begin())	//最初の要素を選択していなければ
			{
				//SEの再生
				se->Play((int)SYS_SE_CURSOR);					//カーソル移動のSEを鳴らす
				--this->Str_itr;		//前の要素へ

			}
		}
		else if (keydown->IsKeyDownOne(KEY_INPUT_S))	//Sキーを押されたら
		{
			if (this->Str_itr != this->Str.end() - 1)	//最後の要素を選択していなければ
			{
				//SEの再生
				se->Play((int)SYS_SE_CURSOR);					//カーソル移動のSEを鳴らす
				++this->Str_itr;		//次の要素へ
			}
		}
		else if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
		{
			//SEの再生
			se->Play((int)SYS_SE_KETTEI);		//決定の効果音を鳴らす
			keydown->KeyDownUpdate();			//キー入力の状態をリセット

			this->SelectFlg = true;				//選択された

			return true;
		}

	}

	return false;

}

//現在選択中の要素を取得
std::vector<std::string>::iterator SELECT::GetNowSelect()
{
	return this->Str_itr;
}

//選択した要素の要素番号を取得する
int SELECT::GetSelectNum(void)
{
	for (int i = 0; i < this->Str.size(); ++i)
	{
		if (*this->Str_itr == this->Str[i])		//選択している要素番号と、一致したら
		{
			return i;		//現在の要素番号を返す
		}
	}
}

//選択肢の内容を消去
void SELECT::SelectClear()
{
	this->Str.clear();
	this->Str_itr = this->Str.begin();
	return;
}

//現在選択中の要素を最初に戻す
void SELECT::NowSelectReset(void)
{
	this->Str_itr = this->Str.begin();
	return;
}

//選択肢の内容を描画する
/*
引数：int：描画X位置
引数：int：描画Y位置
引数：unsigned int：描画色:デフォルトは白色
*/
void SELECT::Draw(int x, int y,int kind,unsigned int color)
{
	static int Height = GetFontSize();	//高さ取得

	for (int i = 0; i < this->Str.size(); ++i)
	{
		if (*this->Str_itr == this->Str[i])			//選択中の要素だったら
		{

			if (kind == (int)SELECT_TRIANGLE)	//通常サイズの場合
			{
				this->image_ui->Draw(x - this->image_ui->GetWidth(kind), y + i * Height + IMAGE_SPACE, kind);		//横向き三角描画
			}
			else							//ミニサイズの場合
			{
				this->image_ui->Draw(x - this->image_ui->GetWidth(kind), y + i * Height + IMAGE_MINI_SPACE, kind);	//横向き三角描画
			}


			DrawFormatString(x, y + i * Height, color, "%s", this->Str[i].c_str());	//選択肢描画
		}
		else
		{
			DrawFormatString(x, y + i * Height, color, "%s", this->Str[i].c_str());	//選択肢描画
		}
	}

}

//選択肢の内容を中央に描画する
/*
引数：int：描画X位置
引数：int：描画Y位置
引数：unsigned int：描画色:デフォルトは白色
*/
void SELECT::DrawCenter(int x, int y,int kind, unsigned int color)
{

	static int Strlen = 0;		//文字列の長さ取得用
	static int Width = 0;		//文字列の幅取得用
	static int Height = 0;		//文字列の高さ取得用

	std::string MaxStr;	//最も長い文字列

	MaxStr = this->Str[0].c_str();	//最も長い文字列に最初の文字列をセット

	for (int i = 0; i < (int)this->Str.size(); i++)
	{
		if (MaxStr < this->Str[i].c_str())	//現在の最大文字列よりも大きければ
		{
			MaxStr = this->Str[i].c_str();	//最大文字列を更新
		}
	}

	//文字列の長さを取得
	Strlen = strlen(MaxStr.c_str());

	Width = GetDrawStringWidth(MaxStr.c_str(), Strlen);	//横幅取得

	x -= (Width / 2);	//文字の幅の半分を引いて、真ん中に描画する

	Height = GetFontSize();	//高さ取得

	for (int i = 0; i < this->Str.size(); ++i)
	{
		if (*this->Str_itr == this->Str[i])			//選択中の要素だったら
		{

			if (kind == (int)SELECT_TRIANGLE)	//通常サイズの場合
			{
				this->image_ui->Draw(x - this->image_ui->GetWidth(kind), y + i * Height + IMAGE_SPACE, kind);		//横向き三角描画
			}
			else							//ミニサイズの場合
			{
				this->image_ui->Draw(x - this->image_ui->GetWidth(kind), y + i * Height + IMAGE_MINI_SPACE, kind);	//横向き三角描画
			}

			DrawFormatString(x, y + i * Height, color, "%s", this->Str[i].c_str());	//選択肢描画
		}
		else
		{
			DrawFormatString(x, y + i * Height, color, "%s", this->Str[i].c_str());	//選択肢描画
		}
	}

}

//画像サイズを設定
void SELECT::SetSize(void)
{
	this->image_ui->SetSize();	//イメージ画像のサイズ設定

	return;
}

//選択肢の内容を追加
void SELECT::Add(const char *str)
{
	this->Str.push_back(str);	//選択肢追加
	this->Str_itr = this->Str.begin();	//最初の要素を選択状態へ
	return;
}

//キー操作可能か設定
void SELECT::SetIsKeyOpe(bool iskeyope)
{
	this->IsKeyOpe = iskeyope;
	return;
}

//キー操作可能か取得
bool SELECT::GetIsKeyOpe(void)
{
	return this->IsKeyOpe;
}

//選択したか設定
void SELECT::SetSelectFlg(bool selectflg)
{
	this->SelectFlg = selectflg;
	return;
}

//選択したか取得
bool SELECT::GetSelectFlg(void)
{
	return this->SelectFlg;
}
