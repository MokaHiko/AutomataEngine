#ifndef CORE_H
#define CORE_H

#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

// Engine Type Definitions
typedef glm::vec4 Vector4;
typedef glm::vec3 Vector3;
typedef glm::vec2 Vector2;
typedef glm::mat4 Matrix4;

#define MatrixTranslate(model, position) glm::translate(model, position);
#define MatrixScale(model, factor)		 glm::scale(model, factor);

#endif