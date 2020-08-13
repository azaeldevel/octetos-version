#include <iostream>
#include <list>
#include <string>
#include <octetos/coreutils/Apishell.hh>


#include "Pacman.hh"


namespace octetos
{
namespace version
{

Version::Platform Pacman::getPlatform()const
{
	return Version::Platform::Pacman;
}
Pacman::Pacman(int argc, char *argv[]):Version(argc,argv)
{
	db = "/var/lib/pacman/local/";
}
bool Pacman::getVersion(const std::string& package,octetos::core::Semver& ver)
{
	//std::cout << "getVersion:Step 0\n";
	coreutils::Apishell shell;
	shell.cd(db);	
	std::list<std::string> dirs;
	//std::cout << "getVersion:Step 1\n";
	if(!shell.ls(dirs))
	{
		std::cerr << "Fallo la lectura de la base de datos.\n";
		return false;
	}
	//std::cout << "getVersion:Step 2\n";
	
	bool findedPk = false;
	std::string pkname;
	std::size_t with_flver = package.find("-");//si el paquete incluye informacion de version
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

	std::string verpk;
	if(std::string::npos != with_flver) verpk = pkname.substr(with_flver + 1);
	else verpk = pkname.substr(package.size() + 1);
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