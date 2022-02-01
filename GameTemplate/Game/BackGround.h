#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Render(RenderContext& rc);
	/// <summary>
	/// ���W��ݒ肷��B
	/// </summary>
	/// <param name="position">���W�B</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// �傫����ݒ肷��B
	/// </summary>
	/// <param name="scale">�傫���B</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// ��]��ݒ肷��B
	/// </summary>
	/// <param name="rotation">��]�B</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

private:
	ModelRender m_backGround;                    //���f�������_�\�B
	Vector3						m_position;						//���W�B
	Vector3						m_scale = Vector3::One;			//�傫���B
	Quaternion					m_rotation;						//��]�B
	PhysicsStaticObject m_physicsStaticObject;  //�ÓI�����I�u�W�F�N�g�B

	int worldstate = 0;//�O����,�P����
};