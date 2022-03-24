#pragma once
class Player1;
class Player2;
class BackGround;
class GameCamera;

class Game : public IGameObject
{
public:
	/// <summary>
	/// 開始の処理
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;

private:
	BackGround* m_backGround;					    //背景。
	SpriteRender	m_spriteRender;
	FontRender      m_fontRender;					//フォントレンダー
	ModelRender     m_modelRender;					//モデルレンダー
	Player1*        m_player;						//プレイヤー1
	Player2*		m_player2;						//プレイヤー2
	Vector3         m_pointligpos;                  //ポイントライトの座標
	Vector3         m_directionligColor;		    //セットする色
	Vector3			m_spPosition;					//スポットライトのポジション
	Vector3			m_spDirection;                  //スポットライトの方向

	SpriteRender    m_spriteHP;					//HPばー
	//ここからは仮で追加したもの
private:
	void Try();

	int m_itemState = 0;

	int m_gage = 0;
	int m_gari = 0;
	int m_tea = 0;
	int m_syoyu = 0;
	int m_wasabi = 0;

	int m_hp=10;
	int m_Maxhp=10;


	GameCamera* m_gameCamera;
};

