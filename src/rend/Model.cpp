#include "Model.h"

#include <stdexcept>

namespace rend
{
    GLsizei Model::vertex_count() const
    {
        return (GLsizei)this->m_faces.size() * 3;
    }

    Vertex::Vertex() :
        position{ 0.0f },
        texcoord{ 0.0f },
        normal{ 0.0f }
    { }

    Model::Model() :
        m_vbo{ 0 },
        m_vao{ 0 },
        m_dirty{ false }
    { }

    Model::Model(const std::string& path) :
        m_vbo{ 0 },
        m_vao{ 0 },
        m_dirty{ false }
    {
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> tcs;
        std::vector<glm::vec3> normals;

        std::string currentline;

        std::ifstream file{ path.c_str() };

        if (!file.is_open())
        {
            throw std::runtime_error("ERROR::FAILED TO OPEN MODEL [" + path + "]");
        }

        while (!file.eof())
        {
            std::getline(file, currentline);
            if (currentline.length() < 1) continue;

            std::vector<std::string> tokens;
            split_string_whitespace(currentline, tokens);
            if (tokens.size() < 1) continue;

            if (tokens.at(0) == "v" && tokens.size() >= 4)
            {
                glm::vec3 p(atof(tokens.at(1).c_str()), atof(tokens.at(2).c_str()), atof(tokens.at(3).c_str()));

                positions.push_back(p);
            }
            else if (tokens.at(0) == "vt" && tokens.size() >= 3)
            {
                glm::vec2 tc(atof(tokens.at(1).c_str()), 1.0f - atof(tokens.at(2).c_str()));

                tcs.push_back(tc);
            }
            else if (tokens.at(0) == "vn" && tokens.size() >= 4)
            {
                glm::vec3 n(atof(tokens.at(1).c_str()), atof(tokens.at(2).c_str()), atof(tokens.at(3).c_str()));

                normals.push_back(n);
            }
            else if (tokens.at(0) == "f" && tokens.size() >= 4)
            {
                Face f;
                std::vector<std::string> sub;
                split_string(tokens.at(1), '/', sub);
                if (sub.size() >= 1) f.a.position = positions.at(atoi(sub.at(0).c_str()) - 1);
                if (sub.size() >= 2) f.a.texcoord = tcs.at(atoi(sub.at(1).c_str()) - 1);
                if (sub.size() >= 3) f.a.normal = normals.at(atoi(sub.at(2).c_str()) - 1);

                for (size_t ti = 2; ti + 1 < tokens.size(); ti++)
                {
                    split_string(tokens.at(ti), '/', sub);
                    if (sub.size() >= 1) f.b.position = positions.at(atoi(sub.at(0).c_str()) - 1);
                    if (sub.size() >= 2) f.b.texcoord = tcs.at(atoi(sub.at(1).c_str()) - 1);
                    if (sub.size() >= 3) f.b.normal = normals.at(atoi(sub.at(2).c_str()) - 1);

                    split_string(tokens.at(ti + 1), '/', sub);
                    if (sub.size() >= 1) f.c.position = positions.at(atoi(sub.at(0).c_str()) - 1);
                    if (sub.size() >= 2) f.c.texcoord = tcs.at(atoi(sub.at(1).c_str()) - 1);
                    if (sub.size() >= 3) f.c.normal = normals.at(atoi(sub.at(2).c_str()) - 1);

                    this->m_faces.push_back(f);
                    this->m_dirty = true;
                }
            }
        }
    }

    Model::~Model()
    {
        if (this->m_vao)
        {
            glDeleteVertexArrays(1, &this->m_vao);
        }

        if (this->m_vbo)
        {
            glDeleteBuffers(1, &this->m_vbo);
        }
    }

    Model::Model(const Model& copy):
        m_vao(0),
        m_vbo(0),
        m_faces(copy.m_faces),
        m_dirty(true)
    { }

    Model& Model::operator=(const Model& assign)
    {
        this->m_faces = assign.m_faces;
        this->m_dirty = true;

        return *this;
    }

    void Model::split_string_whitespace(const std::string& input, std::vector<std::string>& output)
    {
        std::string curr;

        output.clear();

        for (size_t i = 0; i < input.length(); i++)
        {
            if (input.at(i) == ' ' ||
                input.at(i) == '\r' ||
                input.at(i) == '\n' ||
                input.at(i) == '\t')
            {
                if (curr.length() > 0)
                {
                    output.push_back(curr);
                    curr = "";
                }
            }
            else
            {
                curr += input.at(i);
            }
        }

        if (curr.length() > 0)
        {
            output.push_back(curr);
        }
    }

    void Model::split_string(const std::string& input, char splitter, std::vector<std::string>& output)
    {
        std::string curr;

        output.clear();

        for (size_t i = 0; i < input.length(); i++)
        {
            if (input.at(i) == splitter)
            {
                output.push_back(curr);
                curr = "";
            }
            else
            {
                curr += input.at(i);
            }
        }

        if (curr.length() > 0)
        {
            output.push_back(curr);
        }
    }

    GLuint Model::vao_id()
    {
        if (!this->m_faces.size())
        {
            throw std::runtime_error("ERROR::MODEL IS EMPTY");
        }

        if (!this->m_vbo)
        {
            glGenBuffers(1, &this->m_vbo);

            if (!this->m_vbo)
            {
                throw std::runtime_error("ERROR::FAILED TO GENERATE VERTEX BUFFER");
            }
        }

        if (!this->m_vao)
        {
            glGenVertexArrays(1, &this->m_vao);

            if (!this->m_vao)
            {
                throw std::runtime_error("ERROR::FAILED TO GENERATE VERTEX ARRAY");
            }
        }

        if (this->m_dirty)
        {
            std::vector<GLfloat> data;

            for (size_t fi = 0; fi < this->m_faces.size(); ++fi)
            {
                data.push_back(this->m_faces[fi].a.position.x);
                data.push_back(this->m_faces[fi].a.position.y);
                data.push_back(this->m_faces[fi].a.position.z);
                data.push_back(this->m_faces[fi].a.texcoord.x);
                data.push_back(this->m_faces[fi].a.texcoord.y);
                data.push_back(this->m_faces[fi].a.normal.x);
                data.push_back(this->m_faces[fi].a.normal.y);
                data.push_back(this->m_faces[fi].a.normal.z);

                data.push_back(this->m_faces[fi].b.position.x);
                data.push_back(this->m_faces[fi].b.position.y);
                data.push_back(this->m_faces[fi].b.position.z);
                data.push_back(this->m_faces[fi].b.texcoord.x);
                data.push_back(this->m_faces[fi].b.texcoord.y);
                data.push_back(this->m_faces[fi].b.normal.x);
                data.push_back(this->m_faces[fi].b.normal.y);
                data.push_back(this->m_faces[fi].b.normal.z);

                data.push_back(this->m_faces[fi].c.position.x);
                data.push_back(this->m_faces[fi].c.position.y);
                data.push_back(this->m_faces[fi].c.position.z);
                data.push_back(this->m_faces[fi].c.texcoord.x);
                data.push_back(this->m_faces[fi].c.texcoord.y);
                data.push_back(this->m_faces[fi].c.normal.x);
                data.push_back(this->m_faces[fi].c.normal.y);
                data.push_back(this->m_faces[fi].c.normal.z);
            }

            glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), &data.at(0), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindVertexArray(this->m_vao);
            glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(data.at(0)), (void*)0);

            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(data.at(0)), (void*)(3 * sizeof(GLfloat)));

            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(data.at(0)), (void*)(5 * sizeof(GLfloat)));

            glEnableVertexAttribArray(2);

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            this->m_dirty = false;
        }

        return this->m_vao;
    }
}