#define HASHSCALE3 float3(0.1031, 0.1030, 0.0973)

float2 hash22(float2 p)
{
    float3 p3 = frac(p.xyx * HASHSCALE3);
    float tem =  dot(p3, p3.yzx + float3(19.19, 19.19, 19.19));
    p3 = p3 + float3(tem, tem, tem);
    return frac((p3.xx + p3.yz) * p3.zy);
}

float wnoise(float2 p, float time) 
{
    float2 n = floor(p);
    float2 f = frac(p);
    float md = 5.0;
    float2 m = float2(0.0 ,0.0);
    for (int i = -1; i <= 1; i++) 
    {
        for (int j = -1; j <= 1; j++) 
        {
            float2 g = float2(i, j);
            float2 o = hash22(n + g);
            o = float2(0.5, 0.5) + 0.5* sin(float2(time, time) + 6.28 * o);
            float2 r = g + o - f;
            float d = dot(r, r);
            if (d < md) 
            {
                md = d;
                m = n + g + o;
            }
        }
    }
    return md;
}