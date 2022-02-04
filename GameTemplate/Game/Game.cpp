#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"

bool Game::Start()
{
	//プレイヤーオブジェクトを作成する。
	m_player = NewGO<Player>(0, "player");
	//背景オブジェクトを作成する。
	m_backGround = NewGO<BackGround>(0, "background");

	return true;
}
void Game::Update()
{

	//(*･ω･)/ﾊｰｲ
	// 左スティック(キーボード：WASD)で平行移動。
	m_pointligpos.x += g_pad[0]->GetLStickXF();
	m_pointligpos.z += g_pad[0]->GetLStickYF();
	m_pointligpos.y = 50.0f;

	g_directionLig.SetPointPos(m_pointligpos);
	//ディレクションライトの当たる方向とカラーをセットできちゃいます
	//g_directionLig.SetLigDirection({ 1.0f,-1.0f,-1.0f });
	//g_directionLig.SetLigColor({0.5f,0.5f,0.5f});
}
void Game::Render(RenderContext& rc)
{
}