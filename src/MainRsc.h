#pragma once
#include <Corrade/Containers/Optional.h>
#include <Corrade/Containers/Pointer.h>
#include <Corrade/PluginManager/Manager.h>
#include <Corrade/Utility/Resource.h>
#include <Magnum/Trade/ImageData.h>

#include "ConstParam.h"

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

    struct ImageResource
    {
        Containers::Optional<Trade::ImageData2D> beatrice_32x32;
    };

    class MainRsc
    {
    public:
        static MainRsc& Instance();
        MainRsc();

        ImageResource& Images() { return m_images; }

    private:
        Utility::Resource m_resource{ConstParam::RscMgBall};
        PluginManager::Manager<Trade::AbstractImporter> m_pluginManager{};
        Containers::Pointer<Trade::AbstractImporter> m_pngImporter;

        ImageResource m_images{};

        void loadPng(Containers::Optional<Trade::ImageData2D>* out, const std::string& fileName);
    };
}
