
#ifdef GENTOO
	#include "Portage.hh"
#elif defined ARCH
	#include "Pacman.hh"
#elif defined APT
#error "The backend for APT is in development"
#else 
#error "Plataforma desconocida."
#endif

namespace octetos
{
namespace version
{

	bool getVersion(const std::string& package,octetos::core::Semver& ver)
	{
#ifdef GENTOO
		octetos::version::Portage cmdver;
#elif defined ARCH
		octetos::version::Pacman cmdver;
#elif defined APT
#error "The backend for APT is in development"
#else 
#error "Plataforma desconocida."
#endif
		return cmdver.getVersion(package,ver);
	}

}
}