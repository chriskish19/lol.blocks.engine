#include "base.hpp"
/***************************************
*  File: base.cpp
*
*  Purpose: base.hpp definitions
*
*  Project: engine
* *************************************/

#include ENGINE_NAMES_INCLUDE
#include ENGINE_BASE_PHYSICS_INCLUDE_PATH

void engine::dx11::physics::update(float dt) {

}

std::vector<DirectX::XMFLOAT3> engine::dx11::physics::x_move(float x, const std::vector<DirectX::XMFLOAT3>& v)
{
    std::vector<DirectX::XMFLOAT3> result;
    result.reserve(v.size());
    for (const auto& pos : v) {
        result.emplace_back(pos.x + x, pos.y, pos.z);
    }
    return result;
}

std::vector<DirectX::XMFLOAT3> engine::dx11::physics::y_move(float y, const std::vector<DirectX::XMFLOAT3>& v)
{
    std::vector<DirectX::XMFLOAT3> result;
    result.reserve(v.size());
    for (const auto& pos : v) {
        result.emplace_back(pos.x, pos.y + y, pos.z);
    }
    return result;
}

std::vector<DirectX::XMFLOAT3> engine::dx11::physics::z_move(float z, const std::vector<DirectX::XMFLOAT3>& v)
{
    std::vector<DirectX::XMFLOAT3> result;
    result.reserve(v.size());
    for (const auto& pos : v) {
        result.emplace_back(pos.x, pos.y, pos.z + z);
    }
    return result;
}

std::vector<DirectX::XMFLOAT3> engine::dx11::physics::move(DirectX::XMFLOAT3 direction, const std::vector<DirectX::XMFLOAT3>& vertices)
{
    std::vector<DirectX::XMFLOAT3> result;
    result.reserve(vertices.size());
    for (const auto& pos : vertices) {
        result.emplace_back(pos.x + direction.x, pos.y + direction.y, pos.z + direction.z);
    }
    return result;
}
