#pragma once
#include <memory>

#include "Drawing.h"
#include "ActorManager.h"

namespace MgBall
{
    using namespace Magnum;
    class ActorManager;

    class ActorBase
    {
    public:
        virtual ~ActorBase() = default;
        virtual void Tick();
        virtual void Draw3D(const DrawingContext& context);
        virtual void Draw2D(const DrawingContext& context);
        virtual void DrawGui(const DrawingContext& context);

        template <DrawingOrder order>
        void Draw(const DrawingContext& context);

        virtual float OrderPriority();

        void SetActive(bool isActive);
        bool IsActive() const;

        void Kill();
        bool IsDead() const;

        bool HasChildren() const;
        [[nodiscard]] ActorManager& AsParent();

    private:
        bool m_isActive = true;
        bool m_isAlive = true;
        std::unique_ptr<ActorManager> m_children{};

        template <DrawingOrder order>
        void drawInternal(const DrawingContext& context);
    };

    template <DrawingOrder order>
    void ActorBase::Draw(const DrawingContext& context)
    {
        if constexpr (order == DrawingOrder::TwoD)
        {
            Draw2D(context);
        }
        else if constexpr (order == DrawingOrder::ThreeD)
        {
            Draw3D(context);
        }
        else if constexpr (order == DrawingOrder::Gui)
        {
            DrawGui(context);
        }
    }
}
