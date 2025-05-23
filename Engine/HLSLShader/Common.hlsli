
// Lambert Consine Law
float CalcLambert(float3 worldNormal, float3 lightDirection)
{
    return saturate(dot(worldNormal, -lightDirection));
}

//Half CalcLambert

float CalcHalfLambert(
    float3 worldNormal, 
    float3 lightDirection,
    float param = 2)
{
    float nDotL = CalcLambert(worldNormal, lightDirection);
    return pow(nDotL * 0.5f + 0.5f, param);
}

float CalcPhong(
    float3 worldNormal,
    float3 lightDirection,
    float3 cameraDirection,
    float shineness = 16.0f)
{
    float nDotl = CalcLambert(worldNormal, lightDirection);

    float specular = 0;
    if (nDotl)
    {
        float3 reflection = reflect(lightDirection, worldNormal);
        float3 viewDirection = normalize(cameraDirection);
        float rDotv = saturate(dot(reflection, -viewDirection));
        specular = pow(rDotv, shineness);
    }
    
    return specular;
}

float CaluBlinnPhong(
    float3 worldNormal,
    float3 lightDirection,
    float3 cameraDirection,
    float shineness = 32.0f)
{
    float NoL = CalcLambert(worldNormal, lightDirection);
    
    float specular = 0;
    if (NoL > 0)
    {
        float3 viewDirection = normalize(cameraDirection);
        float halfVector = normalize((-lightDirection) + (-viewDirection));
        
        float NoH = saturate(dot(worldNormal, halfVector));
        specular = pow(NoH, shineness);
    }
    
   
    return specular;
}