#include "Mesh.h"
#include "Shader.h"

namespace rend
{
	Mesh::Mesh(std::vector<vertex> vertices, std::vector<GLuint> indicies, std::vector<texture> textures) :
		m_vertices{ vertices },
		m_indecies{ indicies },
		m_textures{ textures }
	{
		this->setup_mesh();
	}

	void Mesh::setup_mesh()
	{
		glGenVertexArrays(1, &this->m_vao);
		glGenBuffers(1, &this->m_vbo);
		glGenBuffers(1, &this->m_ebo);

		glBindVertexArray(this->m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
		glBufferData(GL_ARRAY_BUFFER, this->m_vertices.size() * sizeof(vertex), &this->m_vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_indecies.size() * sizeof(GLuint), &this->m_indecies[0], GL_STATIC_DRAW);

		// Position Attribute 
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);

		// Normals Attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, Normals));

		// Texture Attribute 
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, TexCoords));
	}

	void Mesh::draw(std::shared_ptr<rend::Shader> shader)
	{
		GLuint diffuseNr{ 1 };
		GLuint specularNr{ 1 };

		int index{ 0 };
		std::vector<texture>::iterator itr;
		for (itr = this->m_textures.begin(); itr != this->m_textures.end(); ++itr)
		{
			glActiveTexture(GL_TEXTURE0 + index);

			std::string name{ (*itr).type };
			std::string number;

			if (name == "texture_diffuse")
			{
				number = std::to_string(diffuseNr++);
			}
			else if (name == "texture_specular")
			{
				number = std::to_string(specularNr++);
			}

			shader->set_float(("materail." + name + number).c_str(), index);
			glBindTexture(GL_TEXTURE_2D, (*itr).id);

			++index;
		}

		glActiveTexture(GL_TEXTURE0);

		// Draw Mesh
		shader->use();
		glBindVertexArray(this->m_vao);
		glDrawElements(GL_TRIANGLES, this->m_indecies.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		shader->unuse();
	}
}