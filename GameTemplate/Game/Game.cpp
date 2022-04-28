#include "stdafx.h"
#include "Game.h"
#include "Player1.h"
#include "Player2.h"
#include "BackGround.h"
#include "GameCamera.h"

bool Game::Start()
{
	//m_spriteRender.Init("Assets/sprite/gameclear.dds", 300.0f, 200.0f);
	
	/*m_spriteHP.Init("Assets/sprite/hpbar.dds", 300.0f, 200.0f);
	m_spriteHP.SetPivot(Vector2(0.0f, 0.5f));
	m_spriteHP.SetPosition(Vector3(-150.0f, 200.0f, 0.0f));
	m_spriteHP.Update();*/

	//プレイヤーオブジェクトを作成する。
	m_player = NewGO<Player1>(0, "player1");
	//	m_player2 = NewGO<Player2>(0, "player2");
	//背景オブジェクトを作成する。
	m_backGround = NewGO<BackGround>(0, "background");
	
	//	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");

	return true;
}
void Game::Update()
{
	// 左スティック(キーボード：WASD)で平行移動。
	m_pointligpos.x += g_pad[0]->GetLStickXF();
	m_pointligpos.y += g_pad[0]->GetLStickYF();
	//	g_directionLig.SetPointPos(m_pointligpos);
	m_pointligpos.z += g_pad[0]->GetLStickYF();
	m_pointligpos.y = 50.0f;
	g_directionLig.SetPointPos(m_pointligpos);
	/*
	//ディレクションライトの当たる方向とカラーをセットできちゃいます
	g_directionLig.SetLigDirection({ 1.0f,-1.0f,-1.0f });
	g_directionLig.SetLigColor({ 0.5f,0.5f,0.5f });
	*/
	//g_directionLig.SetPointPos(m_pointligpos);
	g_directionLig.SetPointColor({ 0.5f,0.5f,0.5f });

	m_spPosition.x = 0000.0f;
	g_directionLig.SetSpotPos(m_spPosition);//スポットライトの位置を設定

	g_directionLig.SetLigColor({0.5f,0.5f,0.5f});

	//Aボタンを押したら,体力回復。
	if (g_pad[0]->IsPress(enButtonA))
	{
		m_hp += 1;
	}
	//Bボタンを押したら、体力を減らす。
	else if (g_pad[0]->IsPress(enButtonB))
	{
		m_hp -= 1;
	}
	//HPが0より減っていたら。
	if (m_hp < 0)
	{
		//HPを0にする。
		m_hp = 0;
	}
	Vector3 scale = Vector3::One;
	scale.x = float(m_hp) / float(m_Maxhp);

	m_spriteHP.SetScale(scale);
	//更新処理。
	m_spriteHP.Update();
}

void Game::Try()
{
	//アイテム選択
	if (g_pad[0]->IsTrigger(enButtonLB1))
	{
		switch (m_itemState) {
		case 0:
			m_itemState = 3;
			break;
		case 1:
			m_itemState = 0;
			break;
		case 2:
			m_itemState = 1;
			break;
		case 3:
			m_itemState = 2;
			break;
		}
	}

	if (g_pad[0]->IsTrigger(enButtonRB1))
	{
		switch (m_itemState) {
		case 0:
			m_itemState = 1;
			break;
		case 1:
			m_itemState = 2;
			break;
		case 2:
			m_itemState = 3;
			break;
		case 3:
			m_itemState = 0;
			break;
		}
	}

	//ゲージ4つ消費して使う技（固有スキル１）
	if (m_gage >= 4 && g_pad[0]->IsTrigger(enButtonA)) {
		m_gage -= 4;
	}

	//ゲージ3つ消費して使う技（固有スキル２）
	if (m_gage >= 3 && g_pad[0]->IsTrigger(enButtonB)) {
		m_gage -= 3;
	}

	//通常攻撃
	if (g_pad[0]->IsTrigger(enButtonX)) {

	}

	//アイテム使用
	if (g_pad[0]->IsTrigger(enButtonY)) {
		switch (m_itemState) {
		case 0:
			if (m_gari >= 1) {
				m_gari -= 1;
			}
			break;
		case 1:
			if (m_tea >= 1) {
				m_tea -= 1;
				m_hp += m_Maxhp / 10;
			}
			break;
		case 2:
			if (m_syoyu >= 1) {
				m_syoyu -= 1;
			}
			break;
		case 3:
			if (m_wasabi >= 1) {
				m_wasabi -= 1;
			}
			break;
		}
	}

	//ガード
	if (g_pad[0]->IsPress(enButtonLB2)) {

	}
}

void Game::Render(RenderContext& rc)
{
	//m_spriteRender.Draw(rc);                 //タイトルの描画
	//m_spriteHP.Draw(rc);
	//m_fontRender.Draw(rc);
}