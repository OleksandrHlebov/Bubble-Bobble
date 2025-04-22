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

void dae::Logger::SetMasterVolume(float volume)
{
	std::cout << "Set master volume from " << m_Service->GetMasterVolume() <<  " to " << volume << '\n';
	m_Service->SetMasterVolume(volume);
}

float dae::Logger::GetMasterVolume()
{
	std::cout << "Accessed master volume with value " << m_Service->GetMasterVolume() << '\n';
	return m_Service->GetMasterVolume();
}
