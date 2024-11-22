
#include "DebugManager.hpp"

static std::ostream dump(0);
static std::ostream * ptr;

void DebugManager::SetOut(bool debug)
{
	if (debug)
	{
		ptr = &std::cout;
	}
	else
	{
		ptr = &dump;
	}
}

std::ostream & DebugManager::GetOut()
{
	return *ptr;
}
