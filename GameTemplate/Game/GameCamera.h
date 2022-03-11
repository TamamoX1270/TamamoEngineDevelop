#pragma once

class Player1;
class Player2;

class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	/// <summary>
	/// 2p時のカメラ位置のための仮置き
	/// </summary>
	void karioki();

public:
	/// <summary>
	/// 注視点のベクトルを取得する
	/// </summary>
	const Vector3& GetForwardVector() const
	{
		return m_toCameraPos;
	}

private:
	Player1* m_player;	//プレイヤー。
	Player2* m_player2;	//プレイヤー。
	Vector3 m_toCameraPos;	//注視点から視点に向かうベクトル。
	int m_CameraState = 0;
};