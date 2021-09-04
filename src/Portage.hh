#ifndef COTETOS_VERSION_PORTAGE_HH
#define COTETOS_VERSION_PORTAGE_HH

#include "version.hh"

namespace oct
{
namespace version
{

	class Portage : public Version
	{
	private:
		std::string db;

		bool deductCategory(const std::string& package,std::string& cantegory);
	public:
		Portage(int argc, char *argv[]);
		Portage();
		virtual bool getVersion(const std::string& package,oct::core::Semver& ver);
		virtual Version::Platform getPlatform()const;
	}; 

}
}

#endif 
