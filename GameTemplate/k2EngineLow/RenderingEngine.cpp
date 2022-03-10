#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	RenderingEngine g_renderingEngine;
	void RenderingEngine::SpriteRenderDraw(RenderContext& rc)
	{
		for (auto& renderObj : m_Spriterenders) {
			renderObj->OnRender2D(rc);
		}
		//登録されてる描画オブジェクトをクリア
		m_Spriterenders.clear();
	}
	
	void RenderingEngine::FontRenderDraw(RenderContext& rc)
	{
		for (auto& renderObj : m_Fontrenders) {
			renderObj->OnRender2D(rc);
		}
		//登録されてる描画オブジェクトをクリア
		m_Fontrenders.clear();
	}
	
}