#include "dnpch.h"
#include "OpenGlTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace Dolan {

	OpenGlTexture2d::OpenGlTexture2d(const std::string& path)
		: m_Path(path)
	{
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

		DN_CORE_ASSERT(internalFormat & dataFormat, "Image format not supported.");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		// Allocate space on GPU for texture
		glTextureStorage2D(m_RendererId, 1, internalFormat, m_Width, m_Height);

		// Specify stretching policy to use if geometry is smaller or larger than texture resolution
		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Upload texture data to GPU
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGlTexture2d::~OpenGlTexture2d()
	{
		glDeleteTextures(1, &m_RendererId);
	}

	void OpenGlTexture2d::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererId);
	}

}