#pragma once

#include "Dolan/Renderer/FrameBuffer.h"

namespace Dolan {

	class OpenGlFrameBuffer : public FrameBuffer
	{
	public:
		OpenGlFrameBuffer(const FrameBufferSpec& spec);
		virtual ~OpenGlFrameBuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererId() const override { return m_ColorAttachment; };

		virtual const FrameBufferSpec& GetSpec() const override { return m_Spec; }
	private:
		uint32_t m_RendererId;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FrameBufferSpec m_Spec;
	};

}