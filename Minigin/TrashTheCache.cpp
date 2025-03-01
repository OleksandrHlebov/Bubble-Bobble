#include "TrashTheCache.h"
#include <iostream>
#include <chrono>
#include <numeric>

void ttc::TestInts(int sampleCount, std::vector<float>& output)
{
	output.clear();
	const int size{ 67108864 };
	int* buffer = new int[size] {};

	std::vector<std::vector<float>> results;
	results.resize(11);

	auto startTime = std::chrono::steady_clock::now();

	int stepIndex{};
	for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<float>& currentSampleVector{ results[stepIndex] };
		for (int sampleIndex{}; sampleIndex < sampleCount; ++sampleIndex)
		{
			for (int index{}; index < size; index += stepsize)
				buffer[index] *= 2;
			const auto completed = std::chrono::steady_clock::now();
			std::chrono::nanoseconds delta = (completed - startTime);
			std::cout << stepsize << " took " << delta.count() << std::endl;
			currentSampleVector.emplace_back(std::chrono::duration<float>(delta.count()).count());
			startTime = completed;
		}
		++stepIndex;
	}

	for (std::vector<float>& sample : results)
	{
		auto max = std::max_element(sample.begin(), sample.end());
		sample.erase(max);
		auto min = std::min_element(sample.begin(), sample.end());
		sample.erase(min);
		const float avg = std::accumulate(sample.begin(), sample.end(), .0f) / sample.size();
		output.emplace_back(avg);
	}
	delete[] buffer;
}

struct Transform
{
	float matrix[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
};

class GameObject
{
public:
	Transform local;
	int id{};
};

void ttc::TestObjects(int sampleCount, std::vector<float>& output)
{
	output.clear();
	const int size{ 67108864 };
	GameObject* buffer = new GameObject[size] {};

	std::vector<std::vector<float>> results;
	results.resize(11);

	auto startTime = std::chrono::steady_clock::now();

	int stepIndex{};
	for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<float>& currentSampleVector{ results[stepIndex] };
		for (int sampleIndex{}; sampleIndex < sampleCount; ++sampleIndex)
		{
			for (int index{}; index < size; index += stepsize)
				buffer[index].id *= 2;
			const auto completed = std::chrono::steady_clock::now();
			std::chrono::nanoseconds delta = (completed - startTime);
			std::cout << stepsize << " took " << delta.count() << std::endl;
			currentSampleVector.emplace_back(std::chrono::duration<float>(delta.count()).count());
			startTime = completed;
		}
		++stepIndex;
	}

	for (std::vector<float>& sample : results)
	{
		auto max = std::max_element(sample.begin(), sample.end());
		sample.erase(max);
		auto min = std::min_element(sample.begin(), sample.end());
		sample.erase(min);
		const float avg = std::accumulate(sample.begin(), sample.end(), .0f) / sample.size();
		output.emplace_back(avg);
	}
	delete[] buffer;
}

class GameObjectAlt
{
public:
	Transform* local;
	int id{};
};

void ttc::TestObjectsAlt(int sampleCount, std::vector<float>& output)
{
	output.clear();
	const int size{ 67108864 };
	GameObjectAlt* buffer = new GameObjectAlt[size] {};

	std::vector<std::vector<float>> results;
	results.resize(11);

	auto startTime = std::chrono::steady_clock::now();

	int stepIndex{};
	for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<float>& currentSampleVector{ results[stepIndex] };
		for (int sampleIndex{}; sampleIndex < sampleCount; ++sampleIndex)
		{
			for (int index{}; index < size; index += stepsize)
				buffer[index].id *= 2;
			const auto completed = std::chrono::steady_clock::now();
			std::chrono::nanoseconds delta = (completed - startTime);
			std::cout << stepsize << " took " << delta.count() << std::endl;
			currentSampleVector.emplace_back(std::chrono::duration<float>(delta.count()).count());
			startTime = completed;
		}
		++stepIndex;
	}

	for (std::vector<float>& sample : results)
	{
		auto max = std::max_element(sample.begin(), sample.end());
		sample.erase(max);
		auto min = std::min_element(sample.begin(), sample.end());
		sample.erase(min);
		const float avg = std::accumulate(sample.begin(), sample.end(), .0f) / sample.size();
		output.emplace_back(avg);
	}
	delete[] buffer;
}
