#include "Model.h"
#include "Shader.h"

namespace xTech
{
    void Model::on_load()
    {
        this->m_model = std::make_shared<rend::Model>(this->get_path() + ".obj");
    }
}