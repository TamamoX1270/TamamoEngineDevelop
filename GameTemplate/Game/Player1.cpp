#include "stdafx.h"
#include "Player1.h"
#include "Game.h"
#include "GameCamera.h"

//CollisionObjectを使用するために、ファイルをインクルードする。
#include "CollisionObject.h"

bool Player1::Start()
{
	//アニメーションクリップをロードする。
	m_animationClipArray[enAnimClip_Idle].Load("Assets/purototype/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Run].Load("Assets/purototype/walk.tka");
	m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Guard].Load("Assets/purototype/guard.tka");
	m_animationClipArray[enAnimClip_Guard].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Punch].Load("Assets/purototype/punch.tka");
	m_animationClipArray[enAnimClip_Punch].SetLoopFlag(false);
	//モデルの読み込み
	m_player.Init("Assets/purototype/sushi.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);
	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, {0.0f, 0.0f, 0.0f});
	m_rotation.SetRotationDegX(-90.0f);

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	//座標をプレイヤーの位置に設定する。
	collisionPosition = m_position;
	collisionPosition.y = 50.0f;
	//球状のコリジョンを作成する。
	m_collisionObject->CreateSphere(collisionPosition,       //座標。
		Quaternion::Identity,                             //回転。
		20.0f);                                          //球の大きさ(半径)。
	//名前を付ける。
	m_collisionObject->SetName("player_hit");
	//自動で削除を無効にする(DeleteGOで削除する必要がある)。
	m_collisionObject->SetIsEnableAutoDelete(false);

	m_player.SetPosition(500.0f, 0.0f, 500.0f);
	m_player.Update(); 

	return true;
}

void Player1::Update()
{
	
	Move();
	AnimationState();
	ManageState();

	m_player.Update();
}

void Player1::Move()
{
	
	Vector3 moveSpeed;
	moveSpeed.x = g_pad[0]->GetLStickXF() * 120.0f;
	moveSpeed.z = g_pad[0]->GetLStickYF() * 120.0f;
	
	/*
	m_player.UpdateWorldMatrix(
		m_characterController.GetPosition(),
		m_rotation,
		g_vec3One
	);
	*/

	
	/* 左スティック(キーボード：WASD)で平行移動。
	m_position.x += g_pad[0]->GetLStickXF();
	m_position.y += g_pad[0]->GetLStickYF();
	
	// 右スティック(キーボード：上下左右)で回転。
	m_rotation.AddRotationY(g_pad[0]->GetRStickXF() * 0.05f);
	m_rotation.AddRotationX(g_pad[0]->GetRStickYF() * 0.05f);*/
	
	// 上下左右キー(キーボード：2, 4, 6, 8)で拡大
	if (g_pad[0]->IsPress(enButtonUp)) {
		m_scale.y += 0.02f;
	}
	if (g_pad[0]->IsPress(enButtonDown)) {
		m_scale.y -= 0.02f;
	}
	if (g_pad[0]->IsPress(enButtonRight)) {
		m_scale.x += 0.02f;
	}
	if (g_pad[0]->IsPress(enButtonLeft)) {
		m_scale.x -= 0.02f;
	}

	
	// 平行移動
	m_position.x += g_pad[0]->GetLStickXF();
	m_position.y += g_pad[0]->GetLStickYF();
	

	m_position=m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_player.SetScale(m_scale);
	m_player.SetPosition(m_position);
	m_player.SetRotation(m_rotation);
	m_player.Update();				 
}

void Player1::AnimationState()
{
	
	if (m_playerState == 3) {

		m_timer += g_gameTime->GetFrameDeltaTime();
		if (m_timer >= 0.7f) {
			m_playerState = 0;
		}
	}
	

	//通常攻撃
	if (g_pad[0]->IsTrigger(enButtonB)) {
		m_timer = 0.0f;
		m_playerState = 3;
	}

	if (m_playerState != 3) {

		if (g_pad[0]->IsPress(enButtonLB1) || g_pad[0]->IsPress(enButtonLB2)) {
			m_playerState = 2;
		}

		else if (g_pad[0]->GetLStickXF() || g_pad[0]->GetLStickYF()) {
			m_playerState = 1;
		}

		else {
			m_playerState = 0;
		}
	}
}

void Player1::ManageState()
{
	switch (m_playerState)
	{
	case 0:
		m_player.PlayAnimation(enAnimClip_Idle, 0.2f);
		break;
	case 1:
		m_player.PlayAnimation(enAnimClip_Run, 0.2f);
		break;
	case 2:
		m_player.PlayAnimation(enAnimClip_Guard, 0.2f);
		break;
	case 3:
		m_player.PlayAnimation(enAnimClip_Punch, 0.2f);
		break;
	}
}

void Player1::Render(RenderContext& rc)
{
	m_player.Draw(rc);
}