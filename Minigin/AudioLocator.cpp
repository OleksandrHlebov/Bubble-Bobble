#include "AudioLocator.h"
#include "Sound.h"
#include <iostream>

void dae::Logger::Play(Sound* sound)
{
	m_Service->Play(sound);
	std::cout << "Played sound ID: " << sound->GetID() << ", loaded from " << sound->GetPath() << '\n';
}

void dae::Logger::Pause(Sound* sound)
{
	m_Service->Pause(sound);
	std::cout << "Paused sound ID: " << sound->GetID() << ", loaded from " << sound->GetPath() << '\n';
}

void dae::Logger::Resume(Sound* sound)
{
	m_Service->Resume(sound);
	std::cout << "Resume sound ID: " << sound->GetID() << ", loaded from " << sound->GetPath() << '\n';
}

void dae::Logger::Stop(Sound* sound)
{
	m_Service->Resume(sound);
	std::cout << "Resume sound ID: " << sound->GetID() << ", loaded from " << sound->GetPath() << '\n';
}

void dae::Logger::StopAllSounds()
{
	m_Service->StopAllSounds();
	std::cout << "Stopped all sounds\n";
}
