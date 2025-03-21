#include "Texture.h"

#include "stb_image.h"

#include <stdexcept>

// Code source: https://brightspace.bournemouth.ac.uk/content/enforced/448954-TBC/labs/lab3/rend.zip?isCourseFile=true&ou=448954
// Navigation: rend->src->rend->Texture.cpp

namespace rend
{
    Texture::Texture()
    {
        this->size(256, 256);
    }

    Texture::Texture(const std::string& path)
    {
        this->load(path);
    }

    Texture::Texture(int width, int height)
    {
        this->size(width, height);
    }

    Texture::Texture(const Texture& copy) :
        m_data{ copy.m_data },
        m_width{ copy.m_width },
        m_height{ copy.m_height },
        m_dirty{ true },
        m_id{ 0 }
    { }

    Texture& Texture::operator=(const Texture& assign)
    {
        if (this == &assign) return *this;

        this->m_data = assign.m_data;
        this->m_width = assign.m_width;
        this->m_height = assign.m_height;
        this->m_dirty = true;

        return *this;
    }

    Texture::~Texture()
    {
        if (this->m_id)
        {
            glDeleteTextures(1, &this->m_id);
        }
    }

    void Texture::load(const std::string& path)
    {
        int width{ 0 };
        int height{ 0 };

        stbi_set_flip_vertically_on_load(1);

        float* data{ stbi_loadf(path.c_str(), &width, &height, NULL, 4) };

        stbi_set_flip_vertically_on_load(0);

        if (!data)
        {
            throw std::runtime_error("ERROR::FAILED TO LOAD TEXTURE::[" + path + "]");
        }

        this->size(width, height);

        for (int pi{ 0 }; pi < width * height * 4; ++pi)
        {
            this->m_data[pi] = data[pi];
        }

        free(data);
        this->m_dirty = true;
    }

    void Texture::load(const std::vector<unsigned char>& _data)
    {
        int width{ 0 };
        int height{ 0 };
        int rgba{ 0 };

        stbi_set_flip_vertically_on_load(1);
        float* data{ stbi_loadf_from_memory(&_data[0], _data.size(), &width, &height, NULL, 4) };
        stbi_set_flip_vertically_on_load(0);

        if (!data)
        {
            throw std::runtime_error("ERROR::FAILED TO LOAD TEXTURE::[unsigned char[]]");
        }

        size(width, height);

        for (int pi{ 0 }; pi < width * height * 4; ++pi)
        {
            this->m_data[pi] = data[pi];
        }

        free(data);
        this->m_dirty = true;
    }

    void Texture::size(int _width, int _height)
    {
        if (this->m_width == _width && this->m_height == _height)
        {
            return;
        }

        this->m_data.resize(_width * _height * 4);
        this->m_width = _width;
        this->m_height = _height;
        this->m_dirty = true;
    }

    glm::vec2 Texture::size() const
    {
        return glm::vec2(this->m_width, this->m_height);
    }

    int Texture::width() const
    {
        return this->m_width;
    }

    void Texture::width(int width)
    {
        this->m_width = width;
    }

    int Texture::height() const
    {
        return this->m_height;
    }

    void Texture::height(int height)
    {
        this->m_height = height;
    }

    void Texture::pixel(int x, int y, glm::vec4 pixel)
    {
        if (x < 0 || x >= this->m_width || y < 0 || y >= this->m_height)
        {
            throw std::runtime_error("ERROR::PIXEL OUTSIDE OF TEXTURE BOUNDS");
        }

        int offset{ this->m_width * y * 4 + x * 4 };

        this->m_data[offset]     = pixel.x;
        this->m_data[offset + 1] = pixel.y;
        this->m_data[offset + 2] = pixel.z;
        this->m_data[offset + 3] = pixel.w;
    }

    glm::vec4 Texture::pixel(int x, int y) const
    {
        if (x < 0 || x >= this->m_width || y < 0 || y >= this->m_height)
        {
            throw std::runtime_error("ERROR::PIXEL OUTSIDE OF TEXTURE BOUNDS");
        }

        int offset{ this->m_width * y * 4 + x * 4 };

        glm::vec4 rtn
        (
            this->m_data[offset],
            this->m_data[offset + 1],
            this->m_data[offset + 2],
            this->m_data[offset + 3]
        );

        return rtn;
    }

    GLuint Texture::ID()
    {
        if (!this->m_id)
        {
            glGenTextures(1, &this->m_id);

            if (!this->m_id)
            {
                throw std::runtime_error("ERROR::FAILED TO CREATE TEXTURE");
            }
        }

        if (this->m_dirty)
        {
            glBindTexture(GL_TEXTURE_2D, this->m_id);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_width, this->m_height, 0, GL_RGBA, GL_FLOAT, &this->m_data[0]);

            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, 0);
            this->m_dirty = false;
        }

        return this->m_id;
    }
}