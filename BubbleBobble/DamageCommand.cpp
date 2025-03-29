#include "DamageCommand.h"
#include "Health.h"
#include "GameObject.h"
#include <iostream>

void dae::DamageCommand::Execute()
{
	Health* healthComp = GetGameObject()->GetComponent<Health>();
	if (healthComp)
		healthComp->ApplyHealth(-m_Damage);
	else
		std::cerr << "Missing health component on object to damage\n";
}
