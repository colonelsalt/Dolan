#pragma once

#include "Dolan/Renderer/FrameBuffer.h"

namespace Dolan {

	class OpenGlFrameBuffer : public FrameBuffer
	{
	public:
		OpenGlFrameBuffer(const FrameBufferSpec& spec);
		virtual ~OpenGlFrameBuffer();

		void Invalidate();

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererId(uint32_t index = 0) const override
		{
			DN_CORE_ASSERT(index < m_ColorAttachments.size(), "");
			return m_ColorAttachments[index];
		}

		virtual const FrameBufferSpec& GetSpec() const override { return m_Spec; }
	private:
		uint32_t m_RendererId = 0;
		FrameBufferSpec m_Spec;

		std::vector<FramebufferTextureSpec> m_ColorAttachmentSpecs;
		FramebufferTextureSpec m_DepthAttachmentSpec = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment;
	};

}