#include "dnpch.h"
#include "OpenGlFrameBuffer.h"

#include <glad/glad.h>

namespace Dolan {

	static const uint32_t s_MaxFramebufferSize = 8192;

	namespace Utils {

		static GLenum TextureTarget(bool isMultiSampled)
		{
			if (isMultiSampled)
				return GL_TEXTURE_2D_MULTISAMPLE;
			else
				return GL_TEXTURE_2D;
		}

		static void BindTexture(bool isMultiSampled, uint32_t id)
		{
			glBindTexture(TextureTarget(isMultiSampled), id);
		}

		static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)
		{
			bool isMultiSampled = samples > 1;
			if (isMultiSampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(isMultiSampled), id, 0);
		}

		static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool isMultiSampled = samples > 1;
			if (isMultiSampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(isMultiSampled), id, 0);
		}

		static void CreateTextures(bool isMultiSampled, uint32_t* outId, uint32_t count)
		{
			glCreateTextures(TextureTarget(isMultiSampled), count, outId);
		}

		static bool IsDepthFormat(FramebufferTextureFormat format)
		{
			switch (format)
			{
				case FramebufferTextureFormat::None:
					return true;
			}
			return false;
		}

		static GLenum DolanTextureFormatToGl(FramebufferTextureFormat format)
		{
			switch (format)
			{
				case FramebufferTextureFormat::RGBA8:
					return GL_RGBA8;
				case FramebufferTextureFormat::RED_INTEGER:
					return GL_RED_INTEGER;
			}
			DN_CORE_ASSERT(false, "Unknown format");
			return 0;
		}
	}


	OpenGlFrameBuffer::OpenGlFrameBuffer(const FrameBufferSpec& spec)
		: m_Spec(spec)
	{
		// Attachments
		for (auto spec : m_Spec.Attachments.Attachments)
		{
			if (!Utils::IsDepthFormat(spec.TextureFormat))
				m_ColorAttachmentSpecs.emplace_back(spec);
			else
				m_DepthAttachmentSpec = spec;
		}

		Invalidate();
	}

	OpenGlFrameBuffer::~OpenGlFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererId);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGlFrameBuffer::Invalidate()
	{
		if (m_RendererId)
		{
			glDeleteFramebuffers(1, &m_RendererId);
			glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}

		glCreateFramebuffers(1, &m_RendererId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererId);

		bool shouldMultiSample = m_Spec.Samples > 1;

		// Attachments
		if (m_ColorAttachmentSpecs.size())
		{
			m_ColorAttachments.resize(m_ColorAttachmentSpecs.size());
			Utils::CreateTextures(shouldMultiSample, m_ColorAttachments.data(), m_ColorAttachments.size());

			for (size_t i = 0; i < m_ColorAttachments.size(); i++)
			{
				Utils::BindTexture(shouldMultiSample, m_ColorAttachments[i]);
				switch (m_ColorAttachmentSpecs[i].TextureFormat)
				{
					case FramebufferTextureFormat::RGBA8:
						Utils::AttachColorTexture(m_ColorAttachments[i], m_Spec.Samples, GL_RGBA8, GL_RGBA,
												  m_Spec.Width, m_Spec.Height, i);
						break;
					case FramebufferTextureFormat::RED_INTEGER:
						Utils::AttachColorTexture(m_ColorAttachments[i], m_Spec.Samples, GL_R32I, GL_RED_INTEGER,
												  m_Spec.Width, m_Spec.Height, i);
						break;
				}
			}
		}

		if (m_DepthAttachmentSpec.TextureFormat != FramebufferTextureFormat::None)
		{
			Utils::CreateTextures(shouldMultiSample, &m_DepthAttachment, 1);
			Utils::BindTexture(shouldMultiSample, m_DepthAttachment);
			switch (m_DepthAttachmentSpec.TextureFormat)
			{
				case FramebufferTextureFormat::DEPTH24STENCIL8:
					Utils::AttachDepthTexture(m_DepthAttachment, m_Spec.Samples,
											  GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT,
											  m_Spec.Width, m_Spec.Height);
					break;
			}
		}

		if (m_ColorAttachments.size() > 1)
		{
			DN_CORE_ASSERT(m_ColorAttachments.size() <= 4, "");
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty())
		{
			// Only depth pass
			glDrawBuffer(GL_NONE);
		}

		DN_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete.");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGlFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			DN_CORE_WARN("Attempted to resize framebuffer to ({0}, {1})", width, height);
			return;
		}

		m_Spec.Width = width;
		m_Spec.Height = height;

		Invalidate();
	}

	int OpenGlFrameBuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		DN_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size(), "");

		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}

	void OpenGlFrameBuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		DN_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size(), "");

		FramebufferTextureSpec& spec = m_ColorAttachmentSpecs[attachmentIndex];

		glClearTexImage(m_ColorAttachments[attachmentIndex], 0,
						Utils::DolanTextureFormatToGl(spec.TextureFormat), GL_INT, &value);
	}

	void OpenGlFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererId);
		glViewport(0, 0, m_Spec.Width, m_Spec.Height);
	}

	void OpenGlFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}