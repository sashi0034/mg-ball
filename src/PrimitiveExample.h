#ifndef PRIMITIVEEXAMPLE_H
#define PRIMITIVEEXAMPLE_H

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Shaders/PhongGL.h>
#include "Magnum/Trade/MeshData.h"

namespace MgBall
{
    using namespace Magnum;

    using namespace Math::Literals;

    class PrimitivesExample
    {
    public:
        PrimitivesExample() = default;
        explicit PrimitivesExample(Vector2 windowSize);

        void drawEvent();
        void mouseReleaseEvent();
        void mouseMoveEvent(Vector2 delta);

    private:
        GL::Mesh _mesh;
        Shaders::PhongGL _shader;

        Matrix4 _transformation;
        Matrix4 _projection;
        Color3 _color;
    };

    inline PrimitivesExample::PrimitivesExample(Vector2 windowSize)
    {
        GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
        GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);

        _mesh = MeshTools::compile(Primitives::cubeSolid());

        _transformation =
            Matrix4::rotationX(30.0_degf) * Matrix4::rotationY(40.0_degf);
        _projection =
            Matrix4::perspectiveProjection(
                35.0_degf, Vector2{windowSize}.aspectRatio(), 0.01f, 100.0f) *
            Matrix4::translation(Vector3::zAxis(-10.0f));
        _color = Color3::fromHsv({35.0_degf, 1.0f, 1.0f});
    }

    inline void PrimitivesExample::drawEvent()
    {
        _shader.setLightPositions({{1.4f, 1.0f, 0.75f, 0.0f}})
               .setDiffuseColor(_color)
               .setAmbientColor(Color3::fromHsv({_color.hue(), 1.0f, 0.3f}))
               .setTransformationMatrix(_transformation)
               .setNormalMatrix(_transformation.normalMatrix())
               .setProjectionMatrix(_projection)
               .draw(_mesh);
    }

    inline void PrimitivesExample::mouseReleaseEvent()
    {
        _color = Color3::fromHsv({_color.hue() + 50.0_degf, 1.0f, 1.0f});
    }

    inline void PrimitivesExample::mouseMoveEvent(Vector2 delta)
    {
        _transformation =
            Matrix4::rotationX(Rad{delta.y()}) *
            _transformation *
            Matrix4::rotationY(Rad{delta.x()});

        // Z軸上で手前に移動
        const Vector3 translationVector(0.0f, 0.0f, (delta.y()));
        _transformation = Matrix4::translation(translationVector) * _transformation;
    }
}

#endif // PRIMITIVEEXAMPLE_H
