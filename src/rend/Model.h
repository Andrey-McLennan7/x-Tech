#pragma once

#ifndef REND_MODEL_H
#define REND_MODEL_H

#include "rend/rend.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <memory>

namespace rend
{
	GLuint TextureFromFile(const char* path, const std::string& directory);

	class Model
	{
	private:

		// Model data
		std::vector<texture> m_textures_loaded;
		std::vector<Mesh> m_meshes;
		std::string m_directory;

		void load_model(const std::string& path);
		void process_node(aiNode* node, const aiScene* scene);
		Mesh process_mesh(aiMesh* mesh, const aiScene* scene);

		std::vector<texture> load_material_texture(aiMaterial* mat, aiTextureType type, std::string typeName);

	public:

		Model(const std::string& path);
		void draw(std::shared_ptr<rend::Shader> shader);
	};
}

#endif