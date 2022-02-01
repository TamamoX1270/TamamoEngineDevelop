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
		};
		struct PointLightST
		{
			// step-1 ライト構造体にポイントライト用のメンバ変数を追加する
			Vector3 ptPosition;		//位置。
			float pad2;					//パディング。
			Vector3 ptColor;			//カラー。
			float ptRange;				//影響範囲。
		};
		struct AmbientLightST
		{
			Vector3 eyePos;         // 視点の位置
			float pad3;
			Vector3 ambientLight;   // アンビエントライト
		};
	public:
		DirectionLight();
		~DirectionLight();
		/// <summary>
		/// ディレクションライトの方向を設定
		/// </summary>
		/// <param name="lig"></param>
		void SetLigDirection(const Vector3& lig)
		{
			m_directionLig.ligDirection = lig;
		}
		/// <summary>
		/// ディレクションライトの色を設定
		/// </summary>
		/// <param name="col"></param>
		void SetLigColor(const Vector3& col)
		{
			m_directionLig.ligColor = col;
		}
		/// <summary>
		/// ポイントライトの位置を設定
		/// </summary>
		/// <param name="col"></param>
		void SetPointPos(const Vector3& pos)
		{
			m_pointLig.ptPosition = pos;
		}
		/// <summary>
		/// ポイントライトの色を設定
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
		DirectionLightST            m_directionLig;				//ディレクションライトのデータを作成する。
		PointLightST                m_pointLig;                 //ポイントライトのデータを作成する。
		AmbientLightST              m_ambientLig;               //環境光のデータを作成する。
	};

	//他の場所でも読み込めるようにグローバルにする。
	extern DirectionLight g_directionLig;
}