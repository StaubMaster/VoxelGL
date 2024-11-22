
#ifndef DEBUGMANAGER_HPP
# define DEBUGMANAGER_HPP
# include <iostream>
# include <sstream>
# include <fstream>

class DebugManager
{
	public:
		static void SetOut(bool debug);
		static std::ostream & GetOut();
};

#endif
