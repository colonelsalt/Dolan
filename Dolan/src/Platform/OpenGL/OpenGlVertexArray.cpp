#include "dnpch.h"
#include "OpenGlVertexArray.h"

#include <glad/glad.h>

namespace Dolan {
	
	static GLenum ShaderDataTypeToOpenGlBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:  return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Mat3:   return GL_FLOAT;
			case ShaderDataType::Mat4:   return GL_FLOAT;
			case ShaderDataType::Int:    return GL_INT;
			case ShaderDataType::Int2:   return GL_INT;
			case ShaderDataType::Int3:   return GL_INT;
			case ShaderDataType::Int4:   return GL_INT;
			case ShaderDataType::Bool:   return GL_BOOL;
		}
		DN_CORE_ASSERT(false, "Unknown ShaderDataType.");
		return 0;
	}

	OpenGlVertexArray::OpenGlVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererId);
	}

	OpenGlVertexArray::~OpenGlVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}

	void OpenGlVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererId);
	}

	void OpenGlVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGlVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		DN_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout.");

		glBindVertexArray(m_RendererId);
		vertexBuffer->Bind();

		int index = 0;
		const BufferLayout& layout = vertexBuffer->GetLayout();
		for (const BufferElement& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGlBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGlVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererId);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}