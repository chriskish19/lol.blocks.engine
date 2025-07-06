RWStructuredBuffer<float4> cubePositions : register(u0);
RWStructuredBuffer<float4> cubeVelocities : register(u1);

cbuffer TimeBuffer : register(b0)
{
    float deltaTime;
    float gravity; // e.g., -9.8
    float groundY; // e.g., 0
    float elasticity; // e.g., 0.8
};

[numthreads(256, 1, 1)]
void CSMain(uint3 DTid : SV_DispatchThreadID)
{
    uint id = DTid.x;

    float4 pos = cubePositions[id];
    float4 vel = cubeVelocities[id];

    // Apply gravity
    vel.y += gravity * deltaTime;

    // Integrate position
    pos.xyz += vel.xyz * deltaTime;

    // Simple ground collision
    if (pos.y < groundY)
    {
        pos.y = groundY;
        vel.y *= -elasticity; // bounce
    }

    // Write back
    cubePositions[id] = pos;
    cubeVelocities[id] = vel;
}
