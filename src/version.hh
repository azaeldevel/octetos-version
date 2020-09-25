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
	private:
		bool op_help;
		bool op_compare;//activa la operacion de coparacion
		bool op_indicators;//activa las opciones de visualizacion mas adecuado para hacer comprensible el texto
		bool op_getver;
		bool op_warning;
		bool op_error;
		bool op_platform;
		bool autohelp;
		bool unknowOption;
		std::string msgUnknowOption;

	protected:
		
		bool jump(const std::string& directory,const std::string&  name)const;

	public:
		enum Platform
		{
			None,
			portage,
			pacman,
			apt
		};
		Version(int argc, char *argv[]);
		Version();
		void help();
		virtual bool getVersion(const std::string& package,octetos::core::Semver& ver) = 0;
		virtual Platform getPlatform()const = 0;
		virtual bool compare(const std::string& package,const std::string& op,octetos::core::Semver& ver);
		virtual bool compare(const std::string& package,const std::string& op,octetos::core::Semver& verrq,octetos::core::Semver& verfound);
		bool getop_help()const;
		bool getop_compare()const;
		bool getop_indicators()const;
		bool getop_version()const;
		bool getop_platform()const;
		bool get_autohelp()const;

		bool get_unknowOption() const;
		const std::string& getmsg_unknowOption()const;
	};
	
	bool getVersion(const std::string& package,octetos::core::Semver& ver);
}
}

#endif
