#include "Model.h"

namespace xTech
{
    void Model::on_load()
    {
        this->m_model = std::make_shared<rend::Model>(this->get_path());
    }

    std::shared_ptr<rend::Model> Model::ID() const
    {
        return this->m_model;
    }
}