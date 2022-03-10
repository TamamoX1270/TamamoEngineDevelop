#include "k2EngineLowPreCompile.h"
#include "SpriteRender.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {
	void SpriteRender::Init(const char* filePath, const float w, const float h, AlphaBlendMode alphaBlendMode)
	{
		SpriteInitData initData;
		//DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��B
		initData.m_ddsFilePath[0] = filePath;
		//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
		initData.m_fxFilePath = "Assets/shader/sprite.fx";
		//�X�v���C�g�̕��ƍ������w�肷��B
		initData.m_width = static_cast<UINT>(w);
		initData.m_height = static_cast<UINT>(h);
		initData.m_alphaBlendMode = alphaBlendMode;
		initData.m_colorBufferFormat[0] = DXGI_FORMAT_R16G16B16A16_FLOAT;
		//Sprite�������I�u�W�F�N�g���g�p���āASprite������������B
		m_sprite.Init(initData);
	}

	void SpriteRender::Draw(RenderContext& rc)
	{
		g_renderingEngine.AddRenderObject(this);
	}
}