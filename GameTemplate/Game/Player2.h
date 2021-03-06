#pragma once
class Player2 : public IGameObject
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

public:
	/// <summary>
	/// プレイヤーの座標を取得する。
	/// </summary>
	/// <returns>プレイヤーの座標。</returns>
	const Vector3 & GetPlayer2Position() const
	{
		return m_position;
	}

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// アニメーション管理
	/// </summary>
	void AnimationState();

private:
	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : 待機アニメーション、
		enAnimClip_Run,		// 1 : 走りアニメーション。
		enAnimClip_Num,		// 2 :アニメーションクリップの数。
	};
	Model m_model;
	ModelRender m_player2;                             //プレイヤー
	Animation m_animation;	// アニメーション
	AnimationClip m_animationClipArray[enAnimClip_Num];	// アニメーションクリップ
	CharacterController m_characterController;       //キャラクターコントローラー。
	Vector3 m_position = Vector3::Zero;				   // 座標
	Quaternion m_rotation = Quaternion::Identity;;     // 回転
	Vector3 m_scale = Vector3::One;	                   // 拡大率
};