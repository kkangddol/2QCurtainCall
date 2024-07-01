cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Proj;

    int NumLights;
    float4 vLightDir[8];
    float4 vLightColor[8];
    float4 vOutputColor;
}

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 main(PS_INPUT input) : SV_Target
{
  float4 finalColor = 0;

  //do NdotL lighting for N lights
  for (int i = 0; i < NumLights; i++)
  {
      finalColor += saturate(dot((float3)vLightDir[i],input.Norm) * vLightColor[i]);
  }
  finalColor.a = 1;
  return finalColor;
}