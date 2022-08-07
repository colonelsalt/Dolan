#pragma once

#include "Dolan/Core/Base.h"

namespace Dolan {

	struct FrameBufferSpec
	{
		uint32_t Width, Height;
		
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		
		virtual uint32_t GetColorAttachmentRendererId() const = 0;

		virtual const FrameBufferSpec& GetSpec() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpec& spec);
	};

}