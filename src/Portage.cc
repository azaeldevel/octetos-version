
#include <octetos/coreutils/Apishell.hh>
#include <regex>

#include "Portage.hh"

namespace octetos
{
namespace version
{

bool Portage::deductCategory(const std::string& name,std::string& category)
{
	//std::cout << "deductCategory:Step 0.\n";
	
	//int countmatch = 0;
	coreutils::Apishell shell;
	std::string prevCat = "";
	
	if(!shell.cd(db))	
	{
		std::cerr << "Fallo la lectura de la base de datos.\n";
		return false;
	}
	//std::cout << "deductCategory:Step 1. \n";
	std::list<std::string> dirs;
	if(!shell.ls(dirs)) 
	{
		std::cerr << "Fallo la lectura de la base de datos.\n";
		return false;
	}
	//std::cout << "deductCategory:Step 2. \n";
	
	coreutils::Apishell shell2;
	std::list<std::string> dirs2;
	for(std::string cat : dirs)
	{
		//std::cout << "deductCategory:Step 2.1. \n";
		dirs2.clear();
		
		//std::cout << "deductCategory:Step 2.2. \n";
		//std::cout << db+cats << ".\n";
		if(!shell2.cd(db+cat+"/"))
		{
			std::cerr << "Fallo la lectura de la base de datos.\n";
			return false;
		}	
		//std::cout << "deductCategory:Step 2.1. \n";
		if(!shell2.ls(dirs2)) 
		{
			std::cerr << "Fallo la lectura de la base de datos.\n";
			return false;
		}
		//std::cout << "deductCategory:Step 2.4. \n";
		for(std::string pk : dirs2)
		{
			if(pk.find(name) == 0)
			{
				//std::cout << cat << "/" << pk << "(" << name << ")" << ".\n";
				//¿que pasa si se repite el nombe del paquete en la categoria?
				prevCat = cat;
			}
		}
	}

	category = prevCat;
	return true;
}
bool Portage::getVersion(const std::string& package,octetos::core::Semver& ver)
{
	//std::cout << "getVersion:Step 0. \n";
	std::string category,name;

	//separando nombre de paquete en categoria y paquete
	std::regex regex("/");
	std::vector<std::string> regexout(
					std::sregex_token_iterator(package.begin(), package.end(), regex, -1),
					std::sregex_token_iterator()
					);
	//std::cout << "getVersion:Step 1. \n";
	if(regexout.size() == 2)
	{
		category = regexout[0];
		name = regexout[1];
	}
	else if(regexout.size() == 1)
	{
		//std::cout << "getVersion:Step 1.1.\n";
		name = package;
		if(deductCategory(name,category))
		{
			
		}
		else
		{
			//es necesario poner el nombre completo del paquete.
			std::cerr << "Deve indicar el nombre completo del paqauete.\n";
			return false;
		}
		//std::cout << "Step 1.2. \n";
	}
	else
	{
		std::cerr << "Deve indicar el nombre completo del paqauete.\n";
		return false;
	}
	
	//std::cout << "Step 2. \n";
	coreutils::Apishell shell;
	if(!shell.cd(db+category))	
	{
		std::cerr << "Fallo la lectura de la base de datos.\n";
		return false;
	}
	std::list<std::string> dirs;
	if(!shell.ls(dirs)) 
	{
		std::cerr << "Fallo la lectura de la base de datos.\n";
		return false;
	}
	//std::cout << "Step 2. \n";
	bool findedPk = false;
	std::string pkname;
	std::size_t with_flver = name.find("-");//si el paquete incluye informacion de version
	//std::size_t with_flslah = package.rfind("/");//si el paquete incluye informacion de version
	int counpk_match = 0;
	//std::cout << "Step 3. \n";
	for(std::string d : dirs)
	{	
		//std::cout << "Step 4.1. \n";
		//descartar los paquetes parecido
		char c = d[name.size()+2];
		if(c <= 48 and c >= 57) //si no es un nmbero lo salta.
		{
			continue;
		}
		//		
		//std::cout << "Step 4.2. \n";
		if(std::string::npos != with_flver)
		{
			if(d.find(name) == 0 )
			{
				findedPk = true;
				pkname = d;
				counpk_match++;
			}
		}
		else
		{
			if(d.find(name + "-" ) == 0 )
			{
				findedPk = true;
				pkname = d;
				counpk_match++;
			}
		}	
		//std::cout << "Step 4.3. \n";
	}

	//std::cout << "Step 5. \n";
	if(!findedPk) 
	{
		std::cerr << "Paquete no encontrado, puede deverse a que no existe o no esta instalado.\n";
		return false;
	}
	if(counpk_match > 1) 
	{
		std::cerr << "Nombre ambiguo, agrege informacion de version si hay puede haber diferentes version del mismmo paquete.\n";
		for(std::string d : dirs)
		{
			if(d.find(name + "-" ) == 0 )
			{
				std::cerr << "\t" << d << ".\n";
			}
		}
		return false;
	}

	std::string verpk;
	if(std::string::npos != with_flver) verpk = pkname.substr(with_flver + 1);
	else verpk = pkname.substr(name.size() + 1);
	if(!ver.extractNumbers(verpk)) 
	{
		std::cerr << "Fallo al parsear la version '" << verpk << "'.\n";
		return false;
	}
	
	return true;
}
Portage::Portage(int argc, char *argv[]):Version(argc,argv)
{
	db = "/var/db/pkg/";
}

}
}