/*!
 * @brief	シンプルなモデルシェーダー。
 */

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

//ディレクションライト用の構造体を定義する。
struct DirectionLightST
{
    float3 ligDirection; //ライトの方向
	float3 ligColor;
   
};
//ポイントライト用の構造体を定義する。
struct PointLightST
{
	//ライト構造体にポイントライト用のメンバ変数を追加する
    float3 ptPosition; //位置。
    float3 ptColor; //カラー。
    float ptRange; //影響範囲。
};
//スポットライト用の構造体を定義する。
struct SpotLightST
{
    float3 spPosition; //スポットライトの位置。
    float3 spColor; //スポットライトのカラー。
    float spRange; //スポットライトの射出範囲。
    float3 spDirection; //スポットライトの射出方向。
    float spAngle; //スポットライトの射出角度。
};
struct AmbientLightST
{
    float3 eyePos; // 視点の位置
    float3 ambientLight; // アンビエントライト
};


cbuffer Light : register(b1)
{
    DirectionLightST m_directionLig;     //ディレクションライトのデータを作成する。
    PointLightST     m_pointLig;         //ポイントライトのデータを作成する。
    SpotLightST      m_spotLig;          //スポットライトのデータを作成する。
    AmbientLightST   m_ambientLig;       //環境光のデータを作成する。
};

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
    float3 normal   : NORMAL;
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
    float3 normal       : NORMAL;
	float2 uv 			: TEXCOORD0;	//uv座標。
    float3 worldPos		: TEXCOORD1;
    // step-1 ピクセルシェーダーへの入力にカメラ空間の法線を追加する
    float3 normalInView : TEXCOORD2; //カメラ空間の法線。
};


///////////////////////////////////////////
// 関数宣言
///////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float3 CalcLigFromToonLig(float3 ligDirection,float3 normal);
float3 CalcLigFromPointLight(SPSIn psIn);
float3 CalcLigFromDirectionLight(SPSIn psIn);
float3 CalcLigFromSpotLight(SPSIn psIn);

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
    psIn.worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);
    
    psIn.normal = mul(m, vsIn.normal); //法線を回転させる。
    psIn.normal = normalize(psIn.normal);
	psIn.uv = vsIn.uv;
    
    // step-2 カメラ空間の法線を求める
    psIn.normalInView = mul(mView, psIn.normal); //カメラ空間の法線を求める。
    psIn.normalInView = normalize(psIn.normalInView);

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain( SPSIn psIn ) : SV_Target0
{
	// ディレクションライトによるライティングを計算する
    float3 directionLig = CalcLigFromDirectionLight(psIn);
    // ポイントライトによるライティングを計算する
    float3 m_pointLig = CalcLigFromPointLight(psIn);
    // スポットライトによるライティングを計算する
    float3 m_spotLig = CalcLigFromSpotLight(psIn);
    
    // リムライトの強さを求める
    // step-3 サーフェイスの法線と光の入射方向に依存するリムの強さを求める
    float power1 = 1.0f - max(0.0f, dot(m_directionLig.ligDirection, psIn.normal));
    // step-4 サーフェイスの法線と視線の方向に依存するリムの強さを求める
    float power2 = 1.0f - max(0.0f, psIn.normalInView.z * -1.0f);
    // step-5 最終的なリムの強さを求める
    float limPower = power1 * power2;
    //pow()を使用して、強さの変化を指数関数的にする。
    limPower = pow(limPower, 1.3f);
    // step-6 最終的な反射光にリムライトの反射光を合算する
    //まずはリムライトのカラーを計算する。
    float3 limColor = limPower * m_directionLig.ligColor;
    
    float3 toonPoint = CalcLigFromToonLig(
    m_directionLig.ligDirection,
    psIn.normal		//サーフェイスの法線
);
    
    // ディレクションライト+ポイントライト+環境光+スポットライトして、最終的な光を求める
    float3 lig = directionLig;
                //+ m_pointLig
                //+ m_ambientLig.ambientLight
                //+ m_spotLig;
    
    //最終的な反射光にリムの反射光を合算する。
    //lig += limColor;
    
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
    // テクスチャカラーに求めた光を乗算して最終出力カラーを求める
   // albedoColor.xyz *= lig;
    albedoColor.xyz *= toonPoint;
	return albedoColor;
}

/// <summary>
/// Lambert拡散反射光を計算する
/// </summary>
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    // ピクセルの法線とライトの方向の内積を計算する
    float t = dot(normal, lightDirection) * -1.0f;

    // 内積の値を0以上の値にする
    t = max(0.0f, t);

    // 拡散反射光を計算する
    return lightColor * t;
}

/// <summary>
/// Phong鏡面反射光を計算する
/// </summary>
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    // 反射ベクトルを求める
    float3 refVec = reflect(lightDirection, normal);

    // 光が当たったサーフェイスから視点に伸びるベクトルを求める
    float3 toEye = m_ambientLig.eyePos - worldPos;
    toEye = normalize(toEye);

    // 鏡面反射の強さを求める
    float t = dot(refVec, toEye);

    // 鏡面反射の強さを0以上の数値にする
    t = max(0.0f, t);

    // 鏡面反射の強さを絞る
    t = pow(t, 5.0f);

    // 鏡面反射光を求める
    return lightColor * t;
}

/// <summary>
/// トゥーン調のライティングを計算する
/// </summary>
float3 CalcLigFromToonLig(float3 lightDirection, float3 normal)
{
    // ピクセルの法線とライトの方向の内積を計算する
    float toon = dot(normal, lightDirection);
    
    if (toon >= -0.75f)
    {
  
        return float3(1.0f,1.0f,1.0f);
    }
    return float3(0.75f,0.75f,0.75f);
/*
    // 内積の値を0以上の値にする
        toon = max(0.0f, toon);

    // トゥーン調のライティングを計算する
    return lightColor * toon;*/
}

/// <summary>
/// ポイントライトによる反射光を計算
/// </summary>
/// <param name="psIn">ピクセルシェーダーに渡されている引数</param>
float3 CalcLigFromPointLight(SPSIn psIn)
{
    //サーフェイスに入射するポイントライトの光の向きを計算する
    float3 ligDir = psIn.worldPos - m_pointLig.ptPosition;
	//正規化して大きさ１のベクトルにする。
    ligDir = normalize(ligDir);
	// 減衰なしのLambert拡散反射光を計算する
    float3 diffPoint = CalcLambertDiffuse(
	ligDir, //ライトの方向
	m_pointLig.ptColor, //ライトのカラー
	psIn.normal		//サーフェイスの法線
);
	// 減衰なしのPhong鏡面反射光を計算する
    float3 specPoint = CalcPhongSpecular(
	m_directionLig.ligDirection, //ライトの方向。
	m_pointLig.ptColor, //ライトのカラー。
	psIn.worldPos, //サーフェイズのワールド座標。
	psIn.normal			//サーフェイズの法線。
);
    

	
    //距離による影響率を計算する
    //ポイントライトとの距離を計算する。
    float3 distance = length(psIn.worldPos - m_pointLig.ptPosition);

    //影響率は距離に比例して小さくなっていく。
    float affect = 1.0f - 1.0f / m_pointLig.ptRange * distance;
    //影響力がマイナスにならないように補正をかける。
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
    //影響の仕方を指数関数的にする。今回のサンプルでは3乗している。
    affect = pow(affect, 3.0f);
    
	//拡散反射光と鏡面反射光、トゥーンに影響率を乗算して影響を弱める
    diffPoint *= affect;
    specPoint *= affect;
    
	
    return diffPoint + specPoint ;
}

/// <summary>
/// ディレクションライトによる反射光を計算
/// </summary
/// <param name="psIn">ピクセルシェーダーからの入力。</param>
float3 CalcLigFromDirectionLight(SPSIn psIn)
{
    // ディレクションライトによるLambert拡散反射光を計算する
    float3 diffDirection = CalcLambertDiffuse(m_directionLig.ligDirection, m_directionLig.ligColor, psIn.normal);
    // ディレクションライトによるPhong鏡面反射光を計算する
    float3 specDirection = CalcPhongSpecular(m_directionLig.ligDirection, m_directionLig.ligColor, psIn.worldPos, psIn.normal);
    return diffDirection + specDirection;
}

/// <summary>
/// スポットライトによる反射光を計算
/// </summary
/// <param name="psIn">ピクセルシェーダーからの入力。</param>
float3 CalcLigFromSpotLight(SPSIn psIn)
{
    // スポットライトによるライティングを計算する
     // step-6 サーフェイスに入射するスポットライトの光の向きを計算する
    //ピクセルの座標 - スポットライトの座標を計算。
    float3 ligDir = psIn.worldPos - m_spotLig.spPosition;
    //正規化して大きさ１のベクトルにする。
    ligDir = normalize(ligDir);
    
    // step-7 減衰なしのLambert拡散反射光を計算する
    float3 diffSpotLight = CalcLambertDiffuse(
	ligDir, //ライトの方向
	m_spotLig.spColor, //ライトのカラー
	psIn.normal		//サーフェイスの法線
);
    
    // step-8 減衰なしのPhong鏡面反射光を計算する
    float3 specSpotLight = CalcPhongSpecular(
	ligDir, //ライトの方向。
	m_spotLig.spColor, //ライトのカラー。
	psIn.worldPos, //サーフェイズのワールド座標。
	psIn.normal			//サーフェイズの法線。
);
    // step-9 距離による影響率を計算する
    //スポットライトとの距離を計算する。
    float3 distance = length(psIn.worldPos - m_spotLig.spPosition);

    //影響率は距離に比例して小さくなっていく。
    float affect = 1.0f - 1.0f / m_spotLig.spRange * distance;
    //影響力がマイナスにならないように補正をかける。
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
    //影響の仕方を指数関数的にする。今回のサンプルでは3乗している。
    affect = pow(affect, 1.0f);
    // step-10 影響率を乗算して反射光を弱める
    diffSpotLight *= affect;
    specSpotLight *= affect;
    // step-11 入射光と射出方向の角度を求める
    //dot()を利用して内積を求める。
    float angle = dot(ligDir, m_spotLig.spDirection);
    //dot()で求めた値をacos()に渡して角度を求める。
    angle = abs(acos(angle));
    
    // step-12 角度による影響率を求める
    //角度に比例して小さくなっていく影響率を計算する。
    affect = 1.0f - 1.0f / m_spotLig.spAngle * angle;
    //影響力がマイナスにならないように補正をかける。
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
    //影響の仕方を指数関数的にする。今回のサンプルでは0.5乗している。
    affect = pow(affect, 0.5f);
    
    // step-13 角度による影響率を反射光に乗算して、影響を弱める
    diffSpotLight *= affect;
    specSpotLight *= affect;
    
    return diffSpotLight + specSpotLight;

}