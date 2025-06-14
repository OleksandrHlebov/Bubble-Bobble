#include "LevelInstanceComponent.h"
#include "Health.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::LevelInstance::Start()
{
	GameEvent::Bind("OnDeath", &m_DeathHandler);
	GameEvent::Bind("OnEnemyDeath", &m_EnemyDeathHandler);
}

void dae::LevelInstance::Update(float deltaTime)
{
	if (m_StartedEndSequence)
	{
		if (m_EndTimer >= m_EndDelay)
		{
			SceneManager& sceneManager = SceneManager::GetInstance();
			if (!sceneManager.LoadScene(sceneManager.GetCurrent()->GetID() + 1))
				sceneManager.LoadScene("End");
		}
		m_EndTimer += deltaTime;
	}
}

void dae::LevelInstance::End()
{
	GameEvent::UnBind("OnDeath", &m_DeathHandler);
	GameEvent::UnBind("OnEnemyDeath", &m_EnemyDeathHandler);
}

void dae::LevelInstance::HandleDeath(GameEvent*)
{
	SceneManager::GetInstance().LoadScene("End");
}

void dae::LevelInstance::HandleEnemyDeath(GameEvent*)
{
	--m_AmountOfEnemies;
	if (m_AmountOfEnemies <= 0)
		m_StartedEndSequence = true;
}