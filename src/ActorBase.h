#pragma once
#include <memory>

#include "ActorManager.h"
#include "Magnum/Magnum.h"
#include "Magnum/GL/AbstractFramebuffer.h"

namespace MgBall
{
    using namespace Magnum;
    class ActorManager;

    struct DrawingContext
    {
        const GL::AbstractFramebuffer& frameBuffer;
    };
    
    class ActorBase
    {
    public:
        virtual ~ActorBase() = default;
        virtual void Tick();
        virtual void Draw(const DrawingContext& context);

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
    };
}
