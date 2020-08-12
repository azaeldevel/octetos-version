#ifndef COTETOS_VERSION_HH
#define COTETOS_VERSION_HH

#include <iostream>
#include <octetos/core/Version.hh>


namespace octetos
{
namespace version
{
	class Version
	{
	protected:
		std::string db;

		bool op_help;
		bool op_compare;//activa la operacion de coparacion
		bool op_indicators;//activa las opciones de visualizacion mas adecuado para hacer comprensible el texto
		bool op_getver;
		bool op_warning;
		bool op_error;

	public:
		Version(int argc, char *argv[]);
		void help();
		virtual bool getVersion(const std::string& package,octetos::core::Semver& ver) = 0;
		virtual bool compare(const std::string& package,const std::string& op,octetos::core::Semver& ver);
		virtual bool compare(const std::string& package,const std::string& op,octetos::core::Semver& verrq,octetos::core::Semver& verfound);
		bool getop_help()const;
		bool getop_compare()const;
		bool getop_indicators()const;
		bool getop_version()const;
	};
	
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
