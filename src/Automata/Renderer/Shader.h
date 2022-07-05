#ifndef SHADER_H
#define SHADER_H
#pragma once

#include <glm/glm.hpp>

namespace Automata {
	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr); 
		~Shader();

		void use();
		void unuse();

		void setBool(const std::string& name, bool val) const;
		void setInt(const std::string& name,  int val) const;
		void setFloat(const std::string& name, float val) const;
		void setMat4(const std::string& name, glm::mat4 val) const;
		void setVec3(const std::string& name, glm::vec3 val) const;
		void setVec2(const std::string& name, glm::vec2 val) const;
	private:
		unsigned int ID;
		
		void compileShaders(const char* vCode, const char* fCode, const char* gCode = nullptr);
	};
}

#endif