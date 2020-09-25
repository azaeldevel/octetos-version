#ifndef COTETOS_VERSION_APT_HH
#define COTETOS_VERSION_APT_HH

#include "version.hh"

namespace octetos
{
namespace version
{

	class Apt : public Version
	{
	private:
		std::string db;

		bool deductCategory(const std::string& package,std::string& cantegory);
	public:
		Apt(int argc, char *argv[]);
		Apt();
		virtual bool getVersion(const std::string& package,octetos::core::Semver& ver);
		virtual Version::Platform getPlatform()const;
	}; 

}
}

#endif 
