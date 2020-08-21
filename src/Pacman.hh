#ifndef COTETOS_VERSION_PACMAN_HH
#define COTETOS_VERSION_PACMAN_HH

#include "version.hh"

namespace octetos
{
namespace version
{

	class Pacman : public Version
	{
	private:
		std::string db;
		
	public:
		Pacman(int argc, char *argv[]);
		virtual bool getVersion(const std::string& package,octetos::core::Semver& ver);
		virtual Version::Platform getPlatform()const;
	}; 


}
}
#endif 
