#include "Component.h"
#include "glm.hpp"

namespace dae
{
	class Collision2DComponent final : public Component
	{
	public:
		Collision2DComponent() = delete;
		Collision2DComponent(GameObject* owner) : Component(owner) {}
		~Collision2DComponent() = default;
		
		Collision2DComponent(const Collision2DComponent&) 				= delete;
		Collision2DComponent(Collision2DComponent&&) noexcept 			= delete;
		Collision2DComponent& operator=(const Collision2DComponent&) 	 	= delete;
		Collision2DComponent& operator=(Collision2DComponent&&) noexcept 	= delete;

		void Start() override;

	private:
		glm::vec2 m_Size;

	};
}