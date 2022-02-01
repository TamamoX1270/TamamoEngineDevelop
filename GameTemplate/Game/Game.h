#pragma once
class Player;
class BackGround;

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
	ModelRender     m_modelRender;					//モデルレンダー
	Player*         m_player;						//プレイヤー
	Vector3         m_pointligpos;                  //ポイントライトの座標
	Vector3         m_directionligColor;		    //セットする色
};

