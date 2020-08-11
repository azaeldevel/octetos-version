#ifndef COTETOS_SOFTWARE_VERSION_HH
#define COTETOS_SOFTWARE_VERSION_HH

#include <iostream>

#include <octetos/core/Version.hh>


namespace octetos
{
namespace version
{
	class Version
	{

	public:
		Version();
		void help();
		virtual bool getVersion(const std::string& package,octetos::core::Semver& ver) = 0;
		virtual bool compare(const std::string& package,const std::string& op,octetos::core::Semver& ver) = 0;
	};
	
	class Portage : public Version
	{
	private:
		std::string db;
	public:
		Portage();
		virtual bool getVersion(const std::string& package,octetos::core::Semver& ver);
		virtual bool compare(const std::string& package,const std::string& op,octetos::core::Semver& ver);
	}; 

}
}

#endif
