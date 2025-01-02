#pragma once

#ifndef X_TECH_SHADER_H
#define X_TECH_SHADER_H

#include "Resource.h"
#include <rend/rend.h>

#include <memory>

namespace xTech
{
	class Shader : public Resource
	{
	// Private data members
	private:

		std::shared_ptr<rend::Shader> m_shader;

	// Public member functions
	public:

		virtual void on_load() override;

		void use();
		void unuse();

		void set_float(const std::string& attribute, float value) const;
		void set_int(const std::string& attribute, int value) const;
		void set_bool(const std::string& attribute, bool value) const;

		void set_vec3(const std::string& attribute, float x, float y, float z) const;
		void set_vec3(const std::string& attribute, const glm::vec3& value) const;
		void set_vec3(const std::string& attribute, const float* value) const;

		void set_vec4(const std::string& attribute, float x, float y, float z, float w) const;
		void set_vec4(const std::string& attribute, const glm::vec4& value) const;
		void set_vec4(const std::string& attribute, const float* value) const;

		void set_mat4(const std::string& attribute, const glm::mat4& value) const;

		std::shared_ptr<rend::Shader> shader() const;
	};
}

#endif