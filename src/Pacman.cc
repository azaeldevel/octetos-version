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
	std::size_t with_flver = package.find("-");//si el paquete incluye informacion de version
	int counpk_match = 0;
	for(std::string d : dirs)
	{
		//descartar los paquetes parecido
		char c = d[package.size()+2];
		if(c <= 48 and c >= 57) //si no es un nmbero lo salta.
		{
			continue;
		}
		//
		if(std::string::npos != with_flver)
		{
			if(d.find(package) == 0 )
			{
				findedPk = true;
				pkname = d;
				counpk_match++;
			}
		}
		else
		{			
			if(d.find(package + "-" ) == 0 )
			{
				findedPk = true;
				pkname = d;
				counpk_match++;
			}
		}
	}

	if(!findedPk) return false;
	if(counpk_match > 1) return false;

	std::string verpk;
	if(std::string::npos != with_flver) verpk = pkname.substr(with_flver + 1);
	else verpk = pkname.substr(package.size() + 1);
	if(!ver.extractNumbers(verpk)) return false;
	
	return true;
}
}
}