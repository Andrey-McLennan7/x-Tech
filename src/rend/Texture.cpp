#include "Texture.h"

#include "stb_image.h"

#include <stdexcept>

namespace rend
{
    Texture::Texture()
    {
        this->size(256, 256);
    }

    Texture::Texture(const std::string& _path)
    {
        this->load(_path);
    }

    Texture::Texture(int _width, int _height)
    {
        this->size(_width, _height);
    }

    Texture::Texture(const Texture& _copy)
        : m_data(_copy.m_data)
        , m_width(_copy.m_width)
        , m_height(_copy.m_height)
        , m_dirty(true)
    { }

    Texture& Texture::operator=(const Texture& _assign)
    {
        if (this == &_assign) return *this;

        this->m_data = _assign.m_data;
        this->m_width = _assign.m_width;
        this->m_height = _assign.m_height;
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

    void Texture::load(const std::string& _path)
    {
        int width{ 0 };
        int height{ 0 };

        stbi_set_flip_vertically_on_load(1);

        float* data{ stbi_loadf(_path.c_str(), &width, &height, NULL, 4) };

        stbi_set_flip_vertically_on_load(0);

        if (!data)
        {
            throw std::runtime_error("ERROR::FAILED TO LOAD TEXTURE::[" + _path + "]");
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

    void Texture::pixel(int _x, int _y, glm::vec4 _pixel)
    {
        if (_x < 0 || _x >= this->m_width || _y < 0 || _y >= this->m_height)
        {
            throw std::runtime_error("ERROR::PIXEL OUTSIDE OF TEXTURE BOUNDS");
        }

        int offset{ this->m_width * _y * 4 + _x * 4 };

        this->m_data[offset]     = _pixel.x;
        this->m_data[offset + 1] = _pixel.y;
        this->m_data[offset + 2] = _pixel.z;
        this->m_data[offset + 3] = _pixel.w;
    }

    glm::vec4 Texture::pixel(int _x, int _y) const
    {
        if (_x < 0 || _x >= this->m_width || _y < 0 || _y >= this->m_height)
        {
            throw std::runtime_error("ERROR::PIXEL OUTSIDE OF TEXTURE BOUNDS");
        }

        int offset{ this->m_width * _y * 4 + _x * 4 };

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