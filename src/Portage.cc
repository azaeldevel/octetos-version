
#include <octetos/coreutils/Apishell.hh>
#include <regex>

#include "Portage.hh"

namespace octetos
{
namespace version
{


bool Portage::getVersion(const std::string& package,octetos::core::Semver& ver)
{
	std::string category,name;

	//separando nombre de paquete en categoria y paquete
	std::regex regex("/");
	std::vector<std::string> regexout(
					std::sregex_token_iterator(package.begin(), package.end(), regex, -1),
					std::sregex_token_iterator()
					);

	if(regexout.size() == 2)
	{
		category = regexout[0];
		name = regexout[1];
	}
	else
	{
		//es necesario poner el nombre completo del paquete.
		return false;
	}
	
	coreutils::Apishell shell;
	shell.cd(db+category);	
	std::list<std::string> dirs;
	if(!shell.ls(dirs)) return false;

	bool findedPk = false;
	std::string pkname;
	for(std::string d : dirs)
	{
		if(d.find(name + "-") == 0 )
		{
			findedPk = true;
			pkname = d;
		}
	}

	if(!findedPk) return false;

	std::string verpk = pkname.substr(name.size() + 1);
	if(!ver.extractNumbers(verpk)) return false;
	
	return true;
}
Portage::Portage(int argc, char *argv[]):Version(argc,argv)
{
	db = "/var/db/pkg/";
}

}
}