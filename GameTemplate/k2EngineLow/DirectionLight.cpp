#include "k2EngineLowPreCompile.h"
#include "DirectionLight.h"

namespace nsK2EngineLow {
	//他の場所でも読み込めるようにグローバルにする。
	DirectionLight g_directionLig;
	DirectionLight::DirectionLight()
	{
		
		//視点の位置を設定する。
		m_light.m_ambientLig.eyePos = (Vector3{ 0.0f, 0.0f, 1.0f });//g_camera3D->GetPosition();

		// 環境光
		m_light.m_ambientLig.ambientLight.x = 0.3f;
		m_light.m_ambientLig.ambientLight.y = 0.3f;
		m_light.m_ambientLig.ambientLight.z = 0.3f;
		

		/*
		//初期座標はX = 0、Y = 50、Z = 0にする。
		m_light.m_spotLig.spPosition.x = 0.0f;
		m_light.m_spotLig.spPosition.y = 0.0f;
		m_light.m_spotLig.spPosition.y = 50.0f;
		*/
		//ライトのカラーを設定。R = 10、G = 10、B = 10にする。
		m_light.m_spotLig.spColor.x = .0f;
		m_light.m_spotLig.spColor.y = .0f;
		m_light.m_spotLig.spColor.z = .0f;
		

		//初期方向は斜め下にする。
		m_light.m_spotLig.spDirection.x = 0.0f;
		m_light.m_spotLig.spDirection.y = -1.0f;
		m_light.m_spotLig.spDirection.z = 0.0f;
		//方向データなので、大きさを１にする必要があるので正規化する。
		m_light.m_spotLig.spDirection.Normalize();

		//射出範囲は300
		m_light.m_spotLig.spRange = 500.0f;
		//射出角度は25度。
		m_light.m_spotLig.spAngle = Math::DegToRad(125.0f);


		//ポイントライトの初期座標を設定する。
		m_light.m_pointLig.ptPosition.x = 0.0f;
		m_light.m_pointLig.ptPosition.y = 50.0f;
		m_light.m_pointLig.ptPosition.z = 50.0f;
		
		//ポイントライトの初期カラーを設定する
		m_light.m_pointLig.ptColor.x = 0.0f;
		m_light.m_pointLig.ptColor.y = 0.0f;
		m_light.m_pointLig.ptColor.z = 0.0f;

		//ポイントライトの影響範囲を設定する
		m_light.m_pointLig.ptRange = 100.0f;
		
		//ライトは斜め上から当たっている。
		m_light.m_directionLig.ligDirection.x = 1.0f;
		m_light.m_directionLig.ligDirection.y = 0.0f;
		m_light.m_directionLig.ligDirection.z = -1.0f;
		
		//正規化する。
		m_light.m_directionLig.ligDirection.Normalize();
		
		//ライトのカラーは灰⾊。
		
		m_light.m_directionLig.ligColor.x = 0.0f;
		m_light.m_directionLig.ligColor.y = 0.0f;
		m_light.m_directionLig.ligColor.z = 0.0f;
		
		
		
	}
	DirectionLight::~DirectionLight()
	{

	}
	void DirectionLight::Update()
	{
		//Y軸周りの回転クォータニオンを計算する。
		Quaternion qRotY;
		qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f);
		//計算したクォータニオンでライトの方向を回す。
		qRotY.Apply(m_light.m_spotLig.spDirection);

		//X軸周りの回転クォータニオンを計算する。
		Vector3 rotAxis;
		rotAxis.Cross(g_vec3AxisY, m_light.m_spotLig.spDirection);
		Quaternion qRotX;
		qRotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.01f);
		//計算したクォータニオンでライトの方向を回す。
		qRotX.Apply(m_light.m_spotLig.spDirection);
		g_directionLig.SetSpotDir(m_light.m_spotLig.spDirection);//スポットライトの方向を設定
	}
}