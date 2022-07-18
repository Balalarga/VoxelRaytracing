#pragma once


struct Material
{
	Material() = default;
	Material(const glm::vec3& color, float spec = 1.f, float shining = 1.f):
		diffuseColor(color),
		ambientColor(color),
		specularColor(color),
		specularStrength(spec),
		shiningExponent(shining)
	{}
	
	Material(const glm::vec3& diffuse, const glm::vec3& ambient, const glm::vec3& specular, float spec = 1.f, float shining = 1.f)
		: diffuseColor(diffuse)
		, ambientColor(ambient)
		, specularColor(specular)
		, specularStrength(spec)
		, shiningExponent(shining)
	{}
	
	glm::vec3 diffuseColor{0};
	glm::vec3 ambientColor{0};
	glm::vec3 specularColor{0};
	float specularStrength = 1.f;
	float shiningExponent = 1.f;
};
