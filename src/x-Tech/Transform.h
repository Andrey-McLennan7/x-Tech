#include "Component.h"
#include <glm/glm.hpp>

namespace xTech
{
	class Transform : public Component
	{
	// Private data members
	private:

		

	// Public data members
	public:

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;

		glm::mat4 m_model_matrix;

	// Public member functions
	public:

		virtual void on_initialize() override;
		virtual void on_tick() override;

	};
}