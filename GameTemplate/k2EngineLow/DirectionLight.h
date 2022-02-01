#pragma once
namespace nsK2EngineLow {

	class DirectionLight
	{
	public:
		//�f�B���N�V�������C�g�p�̍\���̂��`����B
		struct DirectionLightST {
			Vector3 ligDirection; //���C�g�̕���
			//HLSL���̒萔�o�b�t�@��float3�^�̕ϐ���16�̔{���̃A�h���X�ɔz�u����邽�߁AC++���ɂ̓p�f�B���O�𖄂߂Ă����B
			float pad;
			Vector3 ligColor;
		};
		struct PointLightST
		{
			// step-1 ���C�g�\���̂Ƀ|�C���g���C�g�p�̃����o�ϐ���ǉ�����
			Vector3 ptPosition;		//�ʒu�B
			float pad2;					//�p�f�B���O�B
			Vector3 ptColor;			//�J���[�B
			float ptRange;				//�e���͈́B
		};
		struct AmbientLightST
		{
			Vector3 eyePos;         // ���_�̈ʒu
			float pad3;
			Vector3 ambientLight;   // �A���r�G���g���C�g
		};
	public:
		DirectionLight();
		~DirectionLight();
		/// <summary>
		/// �f�B���N�V�������C�g�̕�����ݒ�
		/// </summary>
		/// <param name="lig"></param>
		void SetLigDirection(const Vector3& lig)
		{
			m_directionLig.ligDirection = lig;
		}
		/// <summary>
		/// �f�B���N�V�������C�g�̐F��ݒ�
		/// </summary>
		/// <param name="col"></param>
		void SetLigColor(const Vector3& col)
		{
			m_directionLig.ligColor = col;
		}
		/// <summary>
		/// �|�C���g���C�g�̈ʒu��ݒ�
		/// </summary>
		/// <param name="col"></param>
		void SetPointPos(const Vector3& pos)
		{
			m_pointLig.ptPosition = pos;
		}
		/// <summary>
		/// �|�C���g���C�g�̐F��ݒ�
		/// </summary>
		/// <param name="col"></param>
		void SetPointColor(const Vector3& col)
		{
			m_pointLig.ptColor = col;
		}
		DirectionLightST& GetDirectionLight()
		{
			return m_directionLig;
		}
		PointLightST& GetPointLight()
		{
			return m_pointLig;
		}
	private:
		DirectionLightST            m_directionLig;				//�f�B���N�V�������C�g�̃f�[�^���쐬����B
		PointLightST                m_pointLig;                 //�|�C���g���C�g�̃f�[�^���쐬����B
		AmbientLightST              m_ambientLig;               //�����̃f�[�^���쐬����B
	};

	//���̏ꏊ�ł��ǂݍ��߂�悤�ɃO���[�o���ɂ���B
	extern DirectionLight g_directionLig;
}