#include "LevelInstanceComponent.h"
#include "Health.h"
#include "SceneManager.h"

void dae::LevelInstance::Start()
{
	GameEvent::Bind("OnDeath", &m_DeathHandler);
}

void dae::LevelInstance::End()
{
	GameEvent::UnBind("OnDeath", &m_DeathHandler);
}

void dae::LevelInstance::HandleDeath(GameEvent*)
{
	SceneManager::GetInstance().LoadScene("End");
}
