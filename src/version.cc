
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

bool Version::compare(const std::string& package,const std::string& op,octetos::core::Semver& verrq,octetos::core::Semver& verfound)
{
	if(!getVersion(package,verfound)) return false;
		
	if(op.compare("==") == 0)
	{
		return (verfound==verrq);
	}
	else if(op.compare(">") == 0 or op.compare("g") == 0)
	{
		return (verfound>verrq);
	}
	else if(op.compare("<") == 0 or op.compare("s") == 0)
	{
		return (verfound<verrq);
	}
	else if(op.compare(">=") == 0 or op.compare("g=") == 0)
	{
		return (verfound>=verrq);
	}
	else if(op.compare("<=") == 0 or op.compare("s=") == 0)
	{
		return (verfound<=verrq);
	}
	else if(op.compare("!=") == 0)
	{
		return (verfound!=verrq);
	}
	else
	{
		return false;
	}
}
bool Version::compare(const std::string& package,const std::string& op,octetos::core::Semver& ver)
{
	octetos::core::Semver ver1;
	return compare(package,op,ver,ver1);
}
bool Version::getop_help()const
{
	return op_help;
}
void Version::help()
{
	std::cout << "version options parameters.			Generic format.\n";
	std::cout << "version -h.							For help.\n";
	std::cout << "version -g packagename				To get version form package.\n";
	std::cout << "version -c|-ci packagename operator version.			Compare package with version.\n";
}
Version::Version(int argc, char *argv[])
{
	op_help = false;
	op_compare = false;
	op_indicators = false;
	op_getver = false;
	op_warning = false;
	op_error = false;
	
	std::string ops = argv[1];

	for(char c : ops)
	{		
		if(c == 'h')
		{
			op_help = true;
		}
		else if(c == 'c')
		{
			op_compare = true;
		}
		else if(c == 'i')
		{
			op_indicators = true;
		}
		else if(c == 'g')
		{
			op_getver = true;
		}
		else if(c == 'w')
		{
			op_warning = true;
		}
		else if(c == 'e')
		{
			op_error = true;
		}
	}
}
bool Version::getop_compare()const
{
	return op_compare;
}
bool Version::getop_indicators()const
{
	return op_indicators;
}
bool Version::getop_version()const
{
	return op_getver;
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

