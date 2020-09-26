#include <iostream>
#include <list>
#include <string>
#include <octetos/coreutils/shell.hh>
#include <regex>

#include "Pacman.hh"


namespace octetos
{
namespace version
{

Version::Platform Pacman::getPlatform()const
{
	return Version::Platform::pacman;
}
Pacman::Pacman()
{}
Pacman::Pacman(int argc, char *argv[]):Version(argc,argv)
{
	db = "/var/lib/pacman/local/";
}
bool Pacman::getVersion(const std::string& package,octetos::core::Semver& ver)
{
	//std::cout << "getVersion:Step 0\n";
	coreutils::Shell shell;
	shell.cd(db);	
	std::list<std::string> dirs;
	//std::cout << "getVersion:Step 1\n";
	if(!shell.ls(dirs))
	{
		std::cerr << "Fallo la lectura de la base de datos.\n";
		return false;
	}
	//std::cout << "getVersion:Step 2\n";

	std::string verpk;
	bool findedPk = false;
	bool findedVers = false;
	std::string pkname,pureName;
	//std::size_t with_flver = 0;
	std::regex regex("-");
	std::vector<std::string> regexout(
					std::sregex_token_iterator(package.begin(), package.end(), regex, -1),
					std::sregex_token_iterator()
					);
	if(regexout.size() > 1) 
	{
		verpk = regexout[regexout.size()-1];//el último valor
		octetos::core::Semver vercheck;
		if(vercheck.extractNumbers(verpk))
		{//tiene version
			findedVers = true;
		}
	}
	int counpk_match = 0;
	//std::cout << "getVersion:Step 3\n";
	for(std::string d : dirs)
	{
		//std::cout << "getVersion:Step 3.1\n";
		//descartar los paquetes parecido
		if(jump(d,package)) 
		{			
			//std::cout << "Jumping " << d << " because : " << package << "\n";
			continue;
		}
		//std::cout << "getVersion:Step 3.2\n";
		if(regexout.size() > 0 and findedVers)
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
		//std::cout << "getVersion:Step 3.3\n";
	}
	//std::cout << "getVersion:Step 4\n";

	if(!findedPk) 
	{
		std::cerr << "Paquete (" << package << ") no encontrado, puede deverse a que no existe o no esta instalado.\n";
		return false;
	}
	//std::cout << "getVersion:Step 5\n";
	if(counpk_match > 1)
	{
		std::cerr << "Nombre ambiguo, agrege informacion de version si puede haber diferentes version del mismmo paquete.\n";
		for(std::string d : dirs)
		{
			if(jump(d,package)) 
			{			
				//std::cout << "Jumping " << d << " because : " << package << "\n";
				continue;
			}
			if(d.find(package + "-" ) == 0 )
			{
				std::cerr << "\t" << d << ".\n";
			}
		}
		return false;
	}
	//std::cout << "getVersion:Step 6\n";

	
	
	verpk = pkname.substr(package.size() + 1);
	if(!ver.extractNumbers(verpk)) 
	{
		std::cerr << "Fallo al parsear la version '" << verpk << "'.\n";
		return false;
	}

	//std::cout << "getVersion:Step 7\n";
	return true;
}
}
}