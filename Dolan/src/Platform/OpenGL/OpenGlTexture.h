#pragma once

#include "Dolan/Renderer/Texture.h"

namespace Dolan {

	class OpenGlTexture2d : public Texture2d
	{
	public:
		OpenGlTexture2d(const std::string& path);
		virtual ~OpenGlTexture2d();

		virtual uint32_t GetWidth() const { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererId;
	};

}