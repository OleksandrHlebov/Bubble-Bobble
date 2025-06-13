#pragma once
#include "AudioLocator.h"
#include "Sound.h"

namespace dae
{
	class MuteSoundCommand final : public Command
	{
	public:
		MuteSoundCommand() = default;
		~MuteSoundCommand() = default;

		MuteSoundCommand(const MuteSoundCommand&) = delete;
		MuteSoundCommand(MuteSoundCommand&&) noexcept = delete;
		MuteSoundCommand& operator=(const MuteSoundCommand&) = delete;
		MuteSoundCommand& operator=(MuteSoundCommand&&) noexcept = delete;

		void Execute(float) override
		{
			AudioLocator::GetService()->SetMasterVolume(0);
		}

	private:

	};
}