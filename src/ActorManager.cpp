#include "ActorManager.h"

#include <algorithm>

#include "MainContext.h"

namespace MgBall
{
    ActorManager& ActorManager::Global()
    {
        return MainContext::Instance().GetActorManager();
    }

    void ActorManager::sortActorList()
    {
        std::ranges::stable_sort(
            m_actorList,
            [](const std::shared_ptr<ActorBase>& left, const std::shared_ptr<ActorBase>& right)
            {
                return left->OrderPriority() < right->OrderPriority();
            });
    }

    void ActorManager::Tick()
    {
        for (int i = m_actorList.size() - 1; i >= 0; --i)
        {
            auto&& actor = m_actorList[i];
            if (actor->IsDead()) m_actorList.erase(m_actorList.begin() + i);
        }

        // sortActorList();

        // 更新
        for (int i = 0; i < m_actorList.size(); ++i)
        {
            auto&& actor = m_actorList[i];
            if (actor->IsActive() == false) continue;
            actor->Tick();
        }
    }

    template <DrawingOrder order>
    void ActorManager::drawInternal(const DrawingContext& context)
    {
        // 優先度が高いほど後から描画するように並び変える
        sortActorList();

        // 描画
        for (int i = 0; i < m_actorList.size(); ++i)
        {
            auto&& actor = m_actorList[i];
            if (actor->IsActive() == false) continue;
            actor->Draw<order>(context);
        }
    }

    void ActorManager::Draw3D(const DrawingContext& context)
    {
        drawInternal<DrawingOrder::ThreeD>(context);
    }

    void ActorManager::Draw2D(const DrawingContext& context)
    {
        drawInternal<DrawingOrder::TwoD>(context);
    }

    void ActorManager::DrawGui(const DrawingContext& context)
    {
        drawInternal<DrawingOrder::Gui>(context);
    }

    void ActorManager::Clear()
    {
        m_actorList.clear();
    }

    void ActorManager::Birth(ActorBase* actor)
    {
        m_actorList.push_back(std::shared_ptr<ActorBase>(actor));
    }

    std::vector<std::shared_ptr<ActorBase>>& ActorManager::ActorList()
    {
        return m_actorList;
    }
}
