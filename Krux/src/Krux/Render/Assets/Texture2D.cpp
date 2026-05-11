#include "krxpch.h"
#include "Texture2D.h"

#include "Krux/Core/Core.h"

#include "Krux/Render/RenderAPI.h"

#include "RenderAPIs/OpenGL/Assets/OpenGLTexture2D.h"

namespace Krux {

    Ref<Texture2D> Texture2D::Create(const TextureSpecification& spec /*= {}*/)
    {
		switch (RenderAPI::API())
		{
        case Krux::RenderAPIType::None:
            KRX_CORE_ASSERT(false, "Current version does not support RenderAPIType::None!");
            return nullptr;
        case Krux::RenderAPIType::OpenGL:
            return Ref<OpenGLTexture2D>::Create(spec);
		}

        KRX_CORE_ASSERT(false, "Invalid RenderAPIType!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::filesystem::path& path, const TextureSpecification& spec /*= {}*/)
    {
        switch (RenderAPI::API())
        {
        case Krux::RenderAPIType::None:
            KRX_CORE_ASSERT(false, "Current version does not support RenderAPIType::None!");
            return nullptr;
        case Krux::RenderAPIType::OpenGL:
            return Ref<OpenGLTexture2D>::Create(path, spec);
        }

        KRX_CORE_ASSERT(false, "Invalid RenderAPIType!");
        return nullptr;
    }

}
