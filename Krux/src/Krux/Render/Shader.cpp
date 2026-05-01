#include "krxpch.h"
#include "Shader.h"

#include "Krux/Core/Core.h"

#include "Krux/Render/RenderAPI.h"

#include "RenderAPIs/OpenGL/OpenGLShader.h"

namespace Krux {
    Ref<Shader> Shader::Create(const std::filesystem::path& path)
    {
        switch (RenderAPI::API())
        {
        case Krux::RenderAPIType::None:
            KRX_CORE_ASSERT(false, "Current version does not support RenderAPIType::None!");
            return nullptr;
        case Krux::RenderAPIType::OpenGL:
            return Ref<OpenGLShader>::Create(path);
        }

        KRX_CORE_ASSERT(false, "Invalid RenderAPIType!");
        return nullptr;
    }
}
