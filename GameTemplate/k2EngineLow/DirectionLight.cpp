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
		
		//step-2 ポイントライトの初期座標を設定する。
		m_light.m_pointLig.ptPosition.x = 0.0f;
		m_light.m_pointLig.ptPosition.y = 50.0f;
		m_light.m_pointLig.ptPosition.z = 50.0f;
		
		// step-3 ポイントライトの初期カラーを設定する
		m_light.m_pointLig.ptColor.x = 10.0f;
		m_light.m_pointLig.ptColor.y = 0.0f;
		m_light.m_pointLig.ptColor.z = 0.0f;

		// step-4 ポイントライトの影響範囲を設定する
		m_light.m_pointLig.ptRange = 100.0f;
		
		//ライトは斜め上から当たっている。
		m_light.m_directionLig.ligDirection.x = 1.0f;
		m_light.m_directionLig.ligDirection.y = -1.0f;
		m_light.m_directionLig.ligDirection.z = -1.0f;
		
		//正規化する。
		m_light.m_directionLig.ligDirection.Normalize();
		
		//ライトのカラーは灰⾊。
		
		m_light.m_directionLig.ligColor.x = 0.5f;
		m_light.m_directionLig.ligColor.y = 0.5f;
		m_light.m_directionLig.ligColor.z = 0.5f;
		
		
		
	}
	DirectionLight::~DirectionLight()
	{

	}
}