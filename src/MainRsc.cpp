#include "MainRsc.h"

#include "MainContext.h"
#include "Magnum/Trade/AbstractImporter.h"

namespace MgBall
{
    MainRsc& MainRsc::Instance()
    {
        return MainContext::Instance().GetMainRsc();
    }

    MainRsc::MainRsc()
    {
        m_pngImporter = m_pluginManager.loadAndInstantiate("PngImporter");
        if (!m_pngImporter) std::exit(1);

        loadPng(&m_images.beatrice_32x32, "beatrice_32x32.png");
        loadPng(&m_images.stone1, "stone1.png");
        loadPng(&m_images.stone2, "stone2.png");
    }

    void MainRsc::loadPng(Containers::Optional<Trade::ImageData2D>* out, const std::string& fileName)
    {
        if (!m_pngImporter->openData(m_resource.getRaw(fileName))) std::exit(-1);
        *out = m_pngImporter->image2D(0);
        CORRADE_INTERNAL_ASSERT(*out);
    }
}
