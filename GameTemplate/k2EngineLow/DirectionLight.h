#pragma once
namespace nsK2EngineLow {

	class DirectionLight
	{
	public:
		//ディレクションライト用の構造体を定義する。
		struct DirectionLightST {
			Vector3 ligDirection; //ライトの方向
			//HLSL側の定数バッファのfloat3型の変数は16の倍数のアドレスに配置されるため、C++側にはパディングを埋めておく。
			float pad;
			Vector3 ligColor;
			float pad1;
		};
		struct PointLightST
		{
			//ライト構造体にポイントライト用のメンバ変数を追加する
			Vector3 ptPosition;		//位置。
			float pad2;					//パディング。
			Vector3 ptColor;			//カラー。
			float ptRange;				//影響範囲。
		};
		struct SpotLightST
		{
			//ライト構造体にスポットライト用のメンバ変数を追加する
			Vector3 spPosition;		//位置。
			float pad3;					//パディング。
			Vector3 spColor;			//カラー。
			float spRange;				//影響範囲。
			Vector3 spDirection;	//射出方向。
			float spAngle;				//射出角度。
		};
		struct AmbientLightST
		{
			Vector3 eyePos;         // 視点の位置
			float pad4;
			Vector3 ambientLight;   // アンビエントライト
		};

		struct Light
		{
			DirectionLightST            m_directionLig;				//ディレクションライトのデータを作成する。
			PointLightST                m_pointLig;                 //ポイントライトのデータを作成する。
			SpotLightST					m_spotLig;					//スポットライトのデータを作成する。
			AmbientLightST              m_ambientLig;               //環境光のデータを作成する。
		};

	public:
		DirectionLight();
		~DirectionLight();
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update();
		/// <summary>
		/// ディレクションライトの方向を設定
		/// </summary>
		/// <param name="lig"></param>
		void SetLigDirection(const Vector3& lig)
		{
			m_light.m_directionLig.ligDirection = lig;
		}
		/// <summary>
		/// ディレクションライトの色を設定
		/// </summary>
		/// <param name="col"></param>
		void SetLigColor(const Vector3& col)
		{
			m_light.m_directionLig.ligColor = col;
		}
		/// <summary>
		/// ポイントライトの位置を設定
		/// </summary>
		/// <param name="col"></param>
		void SetPointPos(const Vector3& pos)
		{
			m_light.m_pointLig.ptPosition = pos;
		}
		/// <summary>
		/// ポイントライトの色を設定
		/// </summary>
		/// <param name="col"></param>
		void SetPointColor(const Vector3& col)
		{
			m_light.m_pointLig.ptColor = col;
		}
		/// <summary>
		/// ポイントライトの射出範囲を設定
		/// </summary>
		/// <param name="range"></param>
		void SetSpotRange(const float& ptrange)
		{
			m_light.m_pointLig.ptRange = ptrange;
		}
		/// <summary>
		/// スポットライトの位置を設定
		/// </summary>
		/// <param name="col"></param>
		void SetSpotPos(const Vector3& pos)
		{
			m_light.m_spotLig.spPosition = pos;
		}
		/// <summary>
		/// スポットライトの色を設定
		/// </summary>
		/// <param name="col"></param>
		void SetSpotColor(const Vector3& col)
		{
			m_light.m_spotLig.spColor = col;
		}
		/// <summary>
		/// スポットライトの射出方向を設定
		/// </summary>
		/// <param name="dil"></param>
		void SetSpotDir(const Vector3& dil)
		{
			m_light.m_spotLig.spDirection = dil;
		}

		/// <summary>
		/// スポットライトの射出角度を設定
		/// </summary>
		/// <param name="range"></param>
		void SetSpotAngle(const int& spangle)
		{
			m_light.m_spotLig.spAngle = Math::DegToRad(spangle);
		}
		Light& GetLight()
		{
			return m_light;
		}
	private:
		Light m_light;
	};

	//他の場所でも読み込めるようにグローバルにする。
	extern DirectionLight g_directionLig;
}