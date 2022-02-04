#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {

	ModelRender::ModelRender()
	{
	}
	ModelRender::~ModelRender()
	{

	}
	void ModelRender::Init(const char* filePath, AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		//モデルを初期化するための情報を設定。
		ModelInitData initData;

		//tkmファイルのファイルパスを指定する。
		initData.m_tkmFilePath = filePath;
		//シェーダーファイルのファイルパスを指定する。
		initData.m_fxFilePath = "Assets/shader/model.fx";

		// スケルトンを初期化。
		InitSkeleton(filePath);

		m_animationClips = animationClips;


		if (m_animationClips != nullptr)
		{
			//スケルトンを指定する。
			initData.m_skeleton = &m_skeleton;
			//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
			initData.m_vsSkinEntryPointFunc = "VSSkinMain";
			//モデルの上方向を指定する。
			//3dsMaxではデフォルトZアップになっているが、
			//ユニティちゃんはアニメーションでYアップに変更されている。
			initData.m_modelUpAxis = enModelUpAxisY;
		}
		else {
			//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
			initData.m_vsEntryPointFunc = "VSMain";
		}
		/*
		initData.m_expandConstantBuffer = &g_pointLig;
		initData.m_expandConstantBufferSize = sizeof(g_pointLig);
		*/
		initData.m_expandConstantBuffer = &g_directionLig.GetLight();
		initData.m_expandConstantBufferSize = sizeof(g_directionLig.GetLight());
		

		// アニメーションを初期化。
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
		//作成した初期化データをもとにモデルを初期化する。
		m_model.Init(initData);

		//Initの中にアップデートを入れることでInitするときにアップデートしなくてよくなる。
		Update();
	}
	void ModelRender::Update()
	{

		//スケルトンを更新。
		m_skeleton.Update(m_model.GetWorldMatrix());

		//アニメーションを進める。
		m_animation.Progress(g_gameTime->GetFrameDeltaTime());

		// ワールド行列を更新。
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	}
	void ModelRender::InitSkeleton(const char* filePath)
	{
		//スケルトンのデータを読み込み。
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr) {
			m_animation.Init(m_skeleton,
				m_animationClips,
				numAnimationClips);
		}
	}
	void ModelRender::Draw(RenderContext& rc)
	{
		m_model.Draw(rc);
	}
}