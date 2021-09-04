
#ifdef PORTAGE
	#include "Portage.hh"
#elif defined PACMAN
	#include "Pacman.hh"
#elif defined APT
	#include "Apt.hh"
#else 
#error "Plataforma desconocida."
#endif

namespace octetos
{
namespace version
{
	bool getVersion(const std::string& package,oct::core::Semver& ver)
	{
#ifdef PORTAGE
		oct::version::Portage cmdver;
#elif defined PACMAN
		octetos::version::Pacman cmdver;
#elif defined APT
	octetos::version::Apt cmdver;
#else 
#error "Plataforma desconocida."
#endif
		return cmdver.getVersion(package,ver);
	}

}
}