#pragma once
#include <string>
#include <functional>

namespace dae
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		static consteval int GetGameWidth() { return LOGICAL_WINDOW_WIDTH; }
		static consteval int GetGameHeight() { return LOGICAL_WINDOW_HEIGHT; }

	private:
		inline static const int		WINDOW_WIDTH			{ 888 };
		inline static const int		WINDOW_HEIGHT			{ 672 };
		inline static const int		LOGICAL_WINDOW_WIDTH	{ 296 };
		inline static const int		LOGICAL_WINDOW_HEIGHT	{ 224 };
		inline static const int		PLAYER_COUNT			{ 2 };
		inline static const int		MS_PER_FRAME			{ 0 };
		inline static const bool	VSYNC_ON				{ 1 };
		inline static const float	FIXED_UPDATE_TIME		{ 1 / 30.f };
		inline static const float	DELTA_TIME_CAP			{ .2f };
		inline static const float	RESOURCES_UNLOAD_TIME	{ 60.f };
	};
}