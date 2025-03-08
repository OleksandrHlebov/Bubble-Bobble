#pragma once

class Command
{
public:
	Command() = default;
	virtual ~Command() = 0;

	virtual void Execute() = 0;

private:

};