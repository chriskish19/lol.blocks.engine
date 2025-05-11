/***************************************
*  File: dx11_camera.cpp (direct x 11 camera)
*
*  Purpose: dx11_camera.hpp definitions
*
*  Project: engine
* *************************************/

#include ENGINE_NAMES_INCLUDE
#include ENGINE_DX11CAM_INCLUDE_PATH


engine::dx11::Camera::Camera(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
    m_position = DirectX::XMVectorSet(0, 0, -5, 1);
    m_pitch = 0.0f;
    m_yaw = 0.0f;

    m_projection = DirectX::XMMatrixPerspectiveFovLH(
        DirectX::XMConvertToRadians(fovDegrees), aspectRatio, nearZ, farZ
    );

    UpdateView();
}

void engine::dx11::Camera::UpdateView()
{
    // Clamp pitch to avoid flipping
    const float limit = DirectX::XM_PIDIV2 - 0.01f;
    m_pitch = std::clamp(m_pitch, -limit, limit);

    // Convert spherical coordinates to Cartesian forward vector
    DirectX::XMVECTOR forward = DirectX::XMVectorSet(
        cosf(m_pitch) * sinf(m_yaw),
        sinf(m_pitch),
        cosf(m_pitch) * cosf(m_yaw),
        0.0f
    );

    // Calculate target point
    DirectX::XMVECTOR target = DirectX::XMVectorAdd(m_position, forward);

    // Fixed world up
    DirectX::XMVECTOR up = DirectX::XMVectorSet(0, 1, 0, 0);

    // Rebuild view matrix
    m_view = DirectX::XMMatrixLookAtLH(m_position, target, up);
}

void engine::dx11::Camera::MoveForward(float amount)
{
    DirectX::XMVECTOR forward = DirectX::XMVectorSet(
        cosf(m_pitch) * sinf(m_yaw),
        0.0f,
        cosf(m_pitch) * cosf(m_yaw),
        0.0f
    );
    m_position = DirectX::XMVectorAdd(m_position, DirectX::XMVectorScale(forward, amount));
}

void engine::dx11::Camera::MoveRight(float amount)
{
    DirectX::XMVECTOR right = DirectX::XMVectorSet(
        cosf(m_yaw), 0.0f, -sinf(m_yaw), 0.0f
    );
    m_position = DirectX::XMVectorAdd(m_position, DirectX::XMVectorScale(right, amount));
}

void engine::dx11::Camera::MoveUp(float amount)
{
    m_position = DirectX::XMVectorAdd(m_position, DirectX::XMVectorSet(0, amount, 0, 0));
}

void engine::dx11::Camera::Rotate(float pitchDelta, float yawDelta)
{
    m_pitch += pitchDelta;
    m_yaw += yawDelta;
    UpdateView();
}

DirectX::XMMATRIX engine::dx11::Camera::GetViewMatrix() const
{
    return m_view;
}

DirectX::XMMATRIX engine::dx11::Camera::GetProjectionMatrix() const
{
    return m_projection;
}

DirectX::XMVECTOR engine::dx11::Camera::GetPosition() const
{
    return m_position;
}

