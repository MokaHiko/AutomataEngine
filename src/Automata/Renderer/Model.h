#ifndef MODEL_H
#define MODEL_H
#pragma once

#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

namespace Automata{
	class Model
	{
	public:
		Model(std::string path) { loadModel(path); }
		~Model();

		void Draw(Shader& shader);
		std::vector<Mesh> Meshes;
		std::vector<Texture> textures_loaded;
	private:
		// model data
		std::string directory;

		void loadModel(std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);

		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
		unsigned int TextureFromFile(const char* texName, std::string directory);
	};
}

#endif