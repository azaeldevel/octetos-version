
#include <iostream>
#include <list>
#include <string>
#include <octetos/coreutils/Apishell.hh>
#include <regex>


#include "version.hh"



namespace octetos
{

namespace version
{

void Version::help()
{
	std::cout << "version [options] parameters.\n";
	std::cout << "version -h|--help.\n";
	std::cout << "version -g|--get.\n";
	std::cout << "version -c packagename operator version.\n";
}

Version::Version()
{
	
}




bool Portage::compare(const std::string& package,const std::string& op,octetos::core::Semver& ver)
{
	octetos::core::Semver ver1;
	getVersion(package,ver1);
		
	if(op.compare("==") == 0)
	{
		return (ver1==ver);
	}
	else if(op.compare(">") == 0)
	{
		return (ver1>ver);
	}
	else if(op.compare("<") == 0)
	{
		return (ver1<ver);
	}
	else if(op.compare(">=") == 0)
	{
		return (ver1>=ver);
	}
	else if(op.compare("<=") == 0)
	{
		return (ver1<=ver);
	}
	else if(op.compare("!=") == 0)
	{
		return (ver1!=ver);
	}
	else
	{
		return false;
	}
}
bool Portage::getVersion(const std::string& package,octetos::core::Semver& ver)
{
	std::string category,name;

	//separando nombre de paquete en categoria y paquete
	std::regex regex("/");
	std::vector<std::string> regexout(
					std::sregex_token_iterator(package.begin(), package.end(), regex, -1),
					std::sregex_token_iterator()
					);

	/*for (std::string str: regexout) {
		std::cout << str << '\n';
	}*/
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
		//std::cout << "Cat : " << d << ".\n";
		if(d.find(name + "-") == 0 )
		{
			//std::cout << "Cat : " << d << ".\n";
			findedPk = true;
			pkname = d;
		}
	}

	std::string verpk = pkname.substr(name.size() + 1);
	if(!ver.extractNumbers(verpk)) return false;
	
	return true;
}
Portage::Portage()
{
	db = "/var/db/pkg/";
}


}
}

