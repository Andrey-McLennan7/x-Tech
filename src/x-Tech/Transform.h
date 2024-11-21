#include "Component.h"
#include <glm/glm.hpp>

namespace xTech
{
	class Transform : public Component
	{
	// Public data members
	public:

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;

	// Public member functions
	public:

		virtual void on_initialize() override;

		glm::mat4 model_matrix();
	};
}