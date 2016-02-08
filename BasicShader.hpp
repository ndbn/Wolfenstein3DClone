#pragma once

#include "Shader.hpp"


struct BasicShader : public Shader
{
	BasicShader();
	void updateUniforms(const Matrix4f& projectedMatrix, const Material& material) override;
};