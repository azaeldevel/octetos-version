
#include <octetos/coreutils/shell.hh>
#include <regex>

#include "Apt.hh"

namespace octetos
{
namespace version
{

Apt::Apt()
{

}

Version::Platform Apt::getPlatform()const
{
	return Version::Platform::apt;
}
bool Apt::deductCategory(const std::string& name,std::string& category)
{
	
	return true;
}
bool Apt::getVersion(const std::string& package,octetos::core::Semver& ver)
{
	
	return true;
}
Apt::Apt(int argc, char *argv[]):Version(argc,argv)
{
	db = "";
}

}
}