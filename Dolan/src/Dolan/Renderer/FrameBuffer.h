#pragma once

#include "Dolan/Core/Base.h"

#include <glm/glm.hpp>

namespace Dolan {

	enum class FramebufferTextureFormat
	{
		None = 0,

		// Colour
		RGBA8,
		RED_INTEGER,

		// Depth/stencil
		DEPTH24STENCIL8,

		// Default
		Depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureSpec
	{
		FramebufferTextureSpec() = default;
		FramebufferTextureSpec(FramebufferTextureFormat format)
			: TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
	};

	struct FramebufferAttachmentSpec
	{
		FramebufferAttachmentSpec() = default;
		FramebufferAttachmentSpec(std::initializer_list<FramebufferTextureSpec> attachments)
			: Attachments(attachments) { }


		std::vector<FramebufferTextureSpec> Attachments;
	};

	struct FrameBufferSpec
	{
		uint32_t Width, Height;
		FramebufferAttachmentSpec Attachments;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		
		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual uint32_t GetColorAttachmentRendererId(uint32_t index = 0) const = 0;

		virtual const FrameBufferSpec& GetSpec() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpec& spec);
	};

}