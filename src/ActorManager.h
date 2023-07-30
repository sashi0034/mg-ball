#pragma once
#include <vector>

#include "ActorBase.h"
#include "Drawing.h"

namespace MgBall
{
    struct DrawingContext;
    class ActorBase;
    class CoroActor;

    class ActorManager
    {
    public:
        static ActorManager& Global();
        void Tick();
        void Draw3D(const DrawingContext& context);
        void Draw2D(const DrawingContext& context);
        void DrawGui(const DrawingContext& context);

        template <DrawingOrder order>
        void Draw(const DrawingContext& context);

        void Clear();
        void Birth(ActorBase* actor);

        template <typename T>
        std::shared_ptr<T> BirthAs(T* actor)
        {
            auto product = std::shared_ptr<T>(actor);
            m_actorList.push_back(product);
            return product;
        }

        std::vector<std::shared_ptr<ActorBase>>& ActorList();

    private:
        std::vector<std::shared_ptr<ActorBase>> m_actorList{};
        void sortActorList();
        template <DrawingOrder order> void drawInternal(const DrawingContext& context);
    };

    template <DrawingOrder order>
    void ActorManager::Draw(const DrawingContext& context)
    {
        if constexpr (order == DrawingOrder::TwoD)
        {
            Draw2D(context);
        }
        else if constexpr (order == DrawingOrder::ThreeD)
        {
            Draw3D(context);
        }
        else if constexpr (order==DrawingOrder::Gui)
        {
            DrawGui(context);
        }
    }
}
