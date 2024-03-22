Shader "Custom/Test"
{
    CGINCLUDE

#define PI 3.14159265

    /// <summary>
    /// フラワー関数
    /// </summary>
    /// p:uv
    /// n:波の数
    /// radius:半径
    /// angle:回転速度
    /// waveAmp:波の深さ
    float flower(float2 p, float n, float radius, float angle, float waveAmp)
    {
        float theta = atan2(p.y, p.x);
        float d = length(p) - radius + sin(theta * n + angle) * waveAmp;
        float b = 0.01 / abs(d);
        return b;
    }

    float4 paint(float2 uv) 
    {
        // 時間経過で色変化
        /*float t = _Time.y;
        float3 col = float3 (
            sin(t*2),
            sin(t*1.2+1.3),
            sin(-t*2.1-2));
        col = col * 0.5 + 0.5;
        return float4(col,1);*/

        // UV座標
        //return float4(uv, 0, 1);


        // 座標の原点を中心点に持っていく
        //float2 p = uv * 2. - 1.;
        //// 円の半径
        //float d = length(p) - .5;
        //// 絶対値
        //float b = 0.01 / abs(d);
        //return b;

        float rad1 = 0.8;
        float rad2 = 0.5;
        float rad3 = 0.2;


        // 波
        float2 p = uv * 2. - 1.;
        float3 col = 0;
        col += flower(p, 6.0, rad1, _Time.y * 10.5, 0.1) * float3(0.0, 0.5, 1.0);
        col += flower(p, 6.0, rad2, _Time.y * -8.5, 0.05) * float3(0.0, 0.5, 1.0);
        col += flower(p, 6.0, rad3, _Time.y * 5.5, 0.01) * float3(0.0, 0.5, 1.0);
        return float4(col, 1);

    }

    ENDCG

    SubShader
    {
        Pass
        {
            CGPROGRAM

            #pragma vertex vert
            #pragma fragment frag

            #include "UnityCG.cginc"

            // 構造体の定義
            struct appdata // vert関数の入力
            {
                float4 vertex : POSITION;
                float2 texcoord : TEXCOORD0;
            };

            struct fin
            {
                float4 vertex : SV_POSITION;
                float2 texcoord : TEXCOORD0;
            };

            fin vert(appdata v)// 構造体を使用した入出力
            {
                fin o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.texcoord = v.texcoord;
                return o;
            }

            float4 frag(fin FIN) : SV_TARGET// 構造体finを使用した入力
            {
                return paint(FIN.texcoord.xy);
            }

            ENDCG
        }
    }
}
