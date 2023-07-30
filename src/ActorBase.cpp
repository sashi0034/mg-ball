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

    void ActorBase::Draw(const DrawingContext& context)
    {
        if (m_children == nullptr) return;
        m_children->Draw(context);
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
