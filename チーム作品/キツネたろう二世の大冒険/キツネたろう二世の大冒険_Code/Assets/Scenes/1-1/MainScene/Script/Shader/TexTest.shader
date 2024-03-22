Shader "Custom/TexTest"
{
    Properties
    {
        _Tex("Tex", 2D) = ""{}
    }

    CGINCLUDE
    sampler2D _Tex;

    float4 paint(float2 uv)
    {
        return tex2D(_Tex, uv);
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

            float4 frag(fin IN) : SV_TARGET// 構造体finを使用した入力
            {
                return paint(IN.texcoord.xy);
            }

            ENDCG
        }
    }
}
