
#include "MemorySize.hpp"

std::string	mem_size_1000(size_t size)
{
	std::string suffix = "B";
	std::stringstream ss;

	if (size > 1000)
	{
		size /= 1000;
		suffix = "kB";
	}
	if (size > 1000)
	{
		size /= 1000;
		suffix = "MB";
	}
	if (size > 1000)
	{
		size /= 1000;
		suffix = "GB";
	}
	if (size > 1000)
	{
		size /= 1000;
		suffix = "TB";
	}

	ss << size;
	ss << " ";
	ss << suffix;
	return (ss.str());
}
std::string	mem_size_1024(size_t size)
{
	std::string suffix = "B";
	std::stringstream ss;

	if (size > 1024)
	{
		size /= 1024;
		suffix = "kiB";
	}
	if (size > 1024)
	{
		size /= 1024;
		suffix = "MiB";
	}
	if (size > 1024)
	{
		size /= 1024;
		suffix = "GiB";
	}
	if (size > 1024)
	{
		size /= 1024;
		suffix = "TiB";
	}

	ss << size;
	ss << " ";
	ss << suffix;

	return (ss.str());
}

std::string	mem_size_1000_original(size_t size)
{
	std::stringstream ss;

	ss << mem_size_1000(size);
	ss << " (";
	ss << size;
	ss << " B)";

	return (ss.str());
}
