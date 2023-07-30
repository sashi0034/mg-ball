#include "ActorBase.h"
#include "ActorManager.h"

namespace MgBall
{
    void ActorBase::Kill()
    {
        m_isAlive = false;
    }

    bool ActorBase::IsDead() const
    {
        return !m_isAlive;
    }

    bool ActorBase::HasChildren() const
    {
        return m_children != nullptr;
    }

    ActorManager& ActorBase::AsParent()
    {
        if (m_children == nullptr) m_children.reset(new ActorManager());
        return *m_children;
    }

    void ActorBase::Tick()
    {
        if (m_children == nullptr) return;
        m_children->Tick();
    }

    template <DrawingOrder order>
    void ActorBase::drawInternal(const DrawingContext& context)
    {
        if (m_children == nullptr) return;
        m_children->Draw<order>(context);
    }

    void ActorBase::Draw3D(const DrawingContext& context)
    {
        drawInternal<DrawingOrder::ThreeD>(context);
    }

    void ActorBase::Draw2D(const DrawingContext& context)
    {
        drawInternal<DrawingOrder::TwoD>(context);
    }

    void ActorBase::DrawGui(const DrawingContext& context)
    {
        drawInternal<DrawingOrder::Gui>(context);
    }

    float ActorBase::OrderPriority()
    {
        return 0;
    }

    void ActorBase::SetActive(bool isActive)
    {
        m_isActive = isActive;
    }

    bool ActorBase::IsActive() const
    {
        return m_isActive;
    }
}
