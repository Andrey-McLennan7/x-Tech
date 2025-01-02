#include "Model.h"
#include "Shader.h"

namespace xTech
{
    void Model::on_load()
    {
        this->m_model = std::make_shared<rend::Model>(this->get_path() + ".obj");
    }

    void Model::draw(std::shared_ptr<Shader> shader)
    {
        this->m_model->draw(shader->shader());
    }
}