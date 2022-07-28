#pragma once

#include <string>

#include "Dolan/Core/Core.h"

namespace Dolan {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2d : public Texture
	{
	public:
		static Ref<Texture2d> Create(const std::string& path);
	};

}