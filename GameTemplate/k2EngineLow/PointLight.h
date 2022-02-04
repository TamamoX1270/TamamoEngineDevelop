#pragma once
namespace nsK2EngineLow {

	class PointLight
	{
	public:
		// ポイントライト用の構造体を定義する。
		struct PointLightST
		{
			// step-1 ライト構造体にポイントライト用のメンバ変数を追加する
			Vector3 ptPosition;		//位置。
			float pad2;					//パディング。
			Vector3 ptColor;			//カラー。
			float ptRange;				//影響範囲。
		};
	public:
		PointLight();
		~PointLight();
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
		PointLightST& GetPointLight()
		{
			return m_pointLig;
		}
	private:
		PointLightST                m_pointLig;                 //ポイントライトのデータを作成する。
	};

	//他の場所でも読み込めるようにグローバルにする。
	extern PointLight g_pointLig;
}