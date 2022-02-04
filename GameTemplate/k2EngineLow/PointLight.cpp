#include "k2EngineLowPreCompile.h"
#include "PointLight.h"

namespace nsK2EngineLow {
	//他の場所でも読み込めるようにグローバルにする。
	PointLight g_pointLig;
	PointLight::PointLight()
	{

		//step-2 ポイントライトの初期座標を設定する。
		m_pointLig.ptPosition.x = 0.0f;
		m_pointLig.ptPosition.y = 50.0f;
		m_pointLig.ptPosition.z = 50.0f;

		// step-3 ポイントライトの初期カラーを設定する
		m_pointLig.ptColor.x = 10.0f;
		m_pointLig.ptColor.y = 0.0f;
		m_pointLig.ptColor.z = 0.0f;

		// step-4 ポイントライトの影響範囲を設定する
		m_pointLig.ptRange = 100.0f;

	}
	PointLight::~PointLight()
	{

	}
}