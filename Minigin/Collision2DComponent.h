#include "Component.h"
#include "glm.hpp"
#include "GameEvent.h"

#include <vector>

namespace dae
{
	class Collision2DComponent final : public Component
	{
	public:
		struct OnOverlap final : public GameEvent
		{
			OnOverlap() = delete;
			OnOverlap(GameObject* first, Collision2DComponent* firstCollider, GameObject* second, Collision2DComponent* secondCollider, glm::vec2 overlap, glm::vec2 normal) 
				: GameEvent("OnOverlap")
				, Normal		{ normal }
				, First			{ first }
				, FirstCollider	{ firstCollider }
				, Second		{ second }
				, SecondCollider{ secondCollider }
				, Overlap		{ std::move(overlap) }
				{}

			const glm::vec2		Overlap;
			const glm::vec2		Normal;
			const GameObject*	First;
			Collision2DComponent* FirstCollider;
			const GameObject*	Second;
			Collision2DComponent* SecondCollider;

		};

		Collision2DComponent() = delete;
		Collision2DComponent(bool isDynamic, GameObject* owner);
		~Collision2DComponent() = default;
		
		Collision2DComponent(const Collision2DComponent&) 				= delete;
		Collision2DComponent(Collision2DComponent&&) noexcept 			= delete;
		Collision2DComponent& operator=(const Collision2DComponent&) 	 	= delete;
		Collision2DComponent& operator=(Collision2DComponent&&) noexcept 	= delete;

		void SetSize(float x, float y);
		void SetSize(const glm::vec2& size);

		void ProcessOverlaps();

		bool IsOverlapping(Collision2DComponent* other);
		bool IsDynamic() { return m_IsDynamic; }

		std::pair<glm::vec2, glm::vec2> GetBounds(); 

	private:
		glm::vec2 m_OriginalSize;
		bool m_IsDynamic;
	};
}