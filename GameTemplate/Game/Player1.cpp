#include "stdafx.h"
#include "Player1.h"
#include "Game.h"
#include "GameCamera.h"

//CollisionObjectを使用するために、ファイルをインクルードする。
#include "CollisionObject.h"

bool Player1::Start()
{

	//モデルの読み込み
	m_player.Init("Assets/modelData/unityChan.tkm");

	m_position.z += -100.0f;
	
	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_rotation.SetRotationDegY(180.0f);
//	m_rotation.AddRotationDegZ(180.0f);
	m_player.SetRotation(m_rotation);
	m_player.SetPosition(m_position);

	return true;
}

void Player1::Update()
{
	m_player.Update();
}



void Player1::Render(RenderContext& rc)
{
	m_player.Draw(rc);
}