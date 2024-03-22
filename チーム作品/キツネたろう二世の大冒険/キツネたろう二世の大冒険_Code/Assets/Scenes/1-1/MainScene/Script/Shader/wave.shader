Shader "Custom/wave"
{
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 200

        CGPROGRAM
        // Physically based Standard lighting model, and enable shadows on all light types
        #pragma surface surf Standard 

        // Use shader model 3.0 target, to get nicer looking lighting
        #pragma target 3.0

        struct Input
        {
            float3 worldPos;
        };

        void surf (Input IN, inout SurfaceOutputStandard o)
        {
            float dist = distance(fixed3(21, 3.5, 7), IN.worldPos);
            float val = abs(sin(dist * 5.0f - _Time * 100));
            if (val > 0.98){
                o.Albedo = fixed4(0 / 225.0, 0 / 255.0f, 255 / 255.0, 1);
            }
            else {
                o.Albedo = fixed4(225 / 225.0, 255 / 255.0f, 0 / 255.0, 1);
            }
        }
        ENDCG
    }
    FallBack "Diffuse"
}
