#ifndef COTETOS_VERSION_PORTAGE_HH
#define COTETOS_VERSION_PORTAGE_HH

#include "version.hh"

namespace octetos
{
namespace version
{

	class Portage : public Version
	{
	private:
		
	public:
		Portage(int argc, char *argv[]);
		virtual bool getVersion(const std::string& package,octetos::core::Semver& ver);
	}; 


}
}

#endif 
