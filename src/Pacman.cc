#include <iostream>
#include <list>
#include <string>
#include <octetos/coreutils/Apishell.hh>


#include "Pacman.hh"


namespace octetos
{
namespace version
{


Pacman::Pacman(int argc, char *argv[]):Version(argc,argv)
{
	db = "/var/lib/pacman/local/";
}
bool Pacman::getVersion(const std::string& package,octetos::core::Semver& ver)
{
	coreutils::Apishell shell;
	shell.cd(db);	
	std::list<std::string> dirs;
	if(!shell.ls(dirs)) return false;
	
	bool findedPk = false;
	std::string pkname;
	for(std::string d : dirs)
	{
		//std::cout << "Cat : " << d << ".\n";
		if(d.find(package + "-") == 0 )
		{
			//std::cout << "Pk : " << d << ".\n";
			findedPk = true;
			pkname = d;
		}
	}

	if(!findedPk) return false;
	
	std::string verpk = pkname.substr(package.size() + 1);
	if(!ver.extractNumbers(verpk)) return false;
	
	return true;
}
}
}