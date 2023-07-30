#pragma once
#include <vector>

#include "ActorBase.h"

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
		void Draw(const DrawingContext& context);
		void Clear();
		void Birth(ActorBase* actor);
		template <typename T> std::shared_ptr<T> BirthAs(T* actor)
		{
			auto product = std::shared_ptr<T>(actor);
			m_actorList.push_back(product);
			return product;
		}
		std::vector<std::shared_ptr<ActorBase>>& ActorList();
	private:
		std::vector<std::shared_ptr<ActorBase>> m_actorList{};
		void sortActorList();
	};
}
