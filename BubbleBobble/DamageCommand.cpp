#include "DamageCommand.h"
#include "Health.h"
#include "GameObject.h"
#include <iostream>

void dae::DamageCommand::Execute(float)
{
	Health* healthComp = GetGameObject()->GetComponent<Health>();
	if (healthComp)
		healthComp->ApplyHealth(-m_Damage);
}
