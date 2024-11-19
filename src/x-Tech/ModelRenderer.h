#include <x-Tech/Component.h>
#include <rend/rend.h>

namespace xTech
{
	class Shader;
	class Model;
	class Texture;

	class ModelRenderer : public Component
	{
	private:

		std::shared_ptr<rend::Shader> m_shader;
		//std::shared_ptr<rend::Model> m_model;
		std::shared_ptr<rend::Texture> m_texture;

	public:

		virtual void on_display() override;

		void shader(std::shared_ptr<rend::Shader> shader);
		//void model(std::shared_ptr<rend::Model> model);
		void texture(std::shared_ptr<rend::Texture> texture);
	};
}