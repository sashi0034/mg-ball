#pragma once
#include <Corrade/Containers/Optional.h>
#include <Corrade/Containers/Pointer.h>
#include <Corrade/PluginManager/Manager.h>
#include <Corrade/Utility/Resource.h>
#include <Magnum/Trade/ImageData.h>

#include "ConstParam.h"
#include "Shaders/BasicShader.h"
#include "Shaders/TextureShader.h"

namespace Magnum
{
    namespace Trade
    {
        class AbstractImporter;
    }
}

namespace MgBall
{
    using namespace Corrade;
    using namespace Magnum;

    struct ShaderResource
    {
        Shaders::BasicShader basicShader{};
        Shaders::TextureShader textureShader{};
    };

    struct ImageResource
    {
        Containers::Optional<Trade::ImageData2D> beatrice_32x32;
        Containers::Optional<Trade::ImageData2D> stone1;
        Containers::Optional<Trade::ImageData2D> stone2;
    };

    class MainRsc
    {
    public:
        static MainRsc& Instance();
        MainRsc();

        ImageResource& Images() { return m_images; }
        ShaderResource& Shaders() { return m_shaders; }

    private:
        Utility::Resource m_resource{ConstParam::RscMgBall};
        PluginManager::Manager<Trade::AbstractImporter> m_pluginManager{};
        Containers::Pointer<Trade::AbstractImporter> m_pngImporter;

        ImageResource m_images{};
        ShaderResource m_shaders{};

        void loadPng(Containers::Optional<Trade::ImageData2D>* out, const std::string& fileName);
    };
}
