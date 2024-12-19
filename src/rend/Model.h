#pragma once

#ifndef X_TECH_MODEL_H
#define X_TECH_MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <vector>

namespace rend
{
    struct Vertex
    {
        Vertex();

        glm::vec3 position;
        glm::vec2 texcoord;
        glm::vec3 normal;
    };

    struct Face
    {
        Vertex a;
        Vertex b;
        Vertex c;
    };

    class Model
    {
    // Private data members
    private:

        std::vector<Face> m_faces;

        GLuint m_vao;
        GLuint m_vbo;

        bool m_dirty;

    // Private member functions
    private:

        void split_string_whitespace(const std::string& input, std::vector<std::string>& output);
        void split_string(const std::string& input, char splitter, std::vector<std::string>& output);

    // Public member functions
    public:

        Model();
        Model(const std::string& path);

        Model(const Model& copy);
        Model& operator=(const Model& assign);
        virtual ~Model();

        GLsizei vertex_count() const;
        GLuint vao_id();
    };
}

#endif