#include "dnpch.h"
#include "OpenGlTexture.h"

#include <stb_image.h>

namespace Dolan {

	OpenGlTexture2d::OpenGlTexture2d(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		DN_PROFILE_FUNCTION();

		// Format OpenGl stores the image data in
		m_InternalFormat = GL_RGBA8;
		// Format our source image file is in
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		// Allocate space on GPU for texture
		glTextureStorage2D(m_RendererId, 1, m_InternalFormat, m_Width, m_Height);

		// Specify stretching policy to use if geometry is smaller or larger than texture resolution
		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}

	OpenGlTexture2d::OpenGlTexture2d(const std::string& path)
		: m_Path(path)
	{
		DN_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		DN_CORE_ASSERT(data, "Failed to load image.");

		m_Width = width;
		m_Height = height;

		// Format OpenGl stores the image data in
		GLenum internalFormat = 0;
		// Format our source image file is in
		GLenum dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		DN_CORE_ASSERT(internalFormat & dataFormat, "Image format not supported.");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		// Allocate space on GPU for texture
		glTextureStorage2D(m_RendererId, 1, internalFormat, m_Width, m_Height);

		// Specify stretching policy to use if geometry is smaller or larger than texture resolution
		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Upload texture data to GPU
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGlTexture2d::~OpenGlTexture2d()
	{
		DN_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererId);
	}

	void OpenGlTexture2d::SetData(void* data, uint32_t size)
	{
		DN_PROFILE_FUNCTION();

		// Data buffer has to fill entire texture
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		DN_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture.");
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGlTexture2d::Bind(uint32_t slot) const
	{
		DN_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_RendererId);
	}

}