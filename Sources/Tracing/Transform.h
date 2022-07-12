#pragma once
#include <glm/vec3.hpp>

class ITransformable
{
public:
	ITransformable() = default;
	ITransformable(const glm::vec3& pos): _position(pos) {}
	virtual ~ITransformable() = default;

	virtual void SetPosition(const glm::vec3& newPosition) { _position = newPosition; }
	const glm::vec3& GetPosition() const { return _position; }


private:
	glm::vec3 _position{0.f};
};
