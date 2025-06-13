#pragma once
#include "SceneManager.h"
#include "Scene.h"

namespace dae
{
	class NextSceneCommand final : public Command
	{
	public:
		NextSceneCommand() = default;
		~NextSceneCommand() = default;

		NextSceneCommand(const NextSceneCommand&) = delete;
		NextSceneCommand(NextSceneCommand&&) noexcept = delete;
		NextSceneCommand& operator=(const NextSceneCommand&) = delete;
		NextSceneCommand& operator=(NextSceneCommand&&) noexcept = delete;

		void Execute(float) override
		{
			SceneManager& sceneManager = SceneManager::GetInstance();
			const int currentID = sceneManager.GetCurrent()->GetID();
			sceneManager.LoadScene(currentID + 1);
		}

	private:

	};
}