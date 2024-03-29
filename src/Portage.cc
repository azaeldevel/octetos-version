

#include <regex>

#include "Portage.hh"

namespace oct
{
namespace version
{

	Portage::Portage()
	{}
Version::Platform Portage::getPlatform()const
{
	return Version::Platform::portage;
}
bool Portage::deductCategory(const std::string& name,std::string& category)
{
	//std::cout << "deductCategory:Step 0.\n";
	
	//int countmatch = 0;
	
	std::string prevCat = "";
	
	try
	{
		shell.cd(db);
	}	
	catch(const std::exception& ex)
	{
		std::cerr << "No se encontro la base de datos.\n";
		return false;
	}
	//std::cout << "deductCategory:Step 1. \n";
	std::list<std::string> dirs;
	try
	{
		shell.ls(dirs); 
	}
	catch(const std::exception& ex)
	{
		std::cerr << "Fallo la lectura de la base de datos.\n";
		return false;
	}
	//std::cout << "deductCategory:Step 2. \n";
	
	core::Shell shell2;
	std::list<std::string> dirs2;
	for(std::string cat : dirs)
	{
		//std::cout << "deductCategory:Step 2.1. \n";
		dirs2.clear();
		
		//std::cout << "deductCategory:Step 2.2. \n";
		//std::cout << db+cats << ".\n";
		try
		{
			shell2.cd(db+cat+"/");
		}
		catch(const std::exception& e)
		{
			std::cerr << "No se encontro la base de datos.\n";
			return false;
		}	
		//std::cout << "deductCategory:Step 2.1. \n";
		try
		{
			shell2.ls(dirs2);
		} 
		catch(const std::exception& ex)
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
bool Portage::getVersion(const std::string& package,oct::core::Semver& ver)
{
	//std::cout << "getVersion:Step 1. \n";
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
	else if(regexout.size() < 2)
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
	core::Shell shell;
	try
	{
		shell.cd(db);//primero se prueba si esta la base de datos
	}
	catch(const std::exception& ex)
	{
		std::cerr << "No se encontro la base de datos en '" << db << "'.\n";
		return false;
	}
	//std::cout << "categoria '" << category << "'.\n";
	try
	{
		shell.cd(db+category);
	}
	catch(const std::exception& ex)	
	{
		std::cerr << "Se desconoce la categoria '" << category << "'.\n";
		return false;
	}
	std::list<std::string> dirs;
	try
	{
		shell.ls(dirs);
	} 
	catch(const std::exception& ex)
	{
		std::cerr << "Fallo la lectura de la base de datos.\n";
		return false;
	}
	//std::cout << "Step 2. \n";
	bool findedPk = false;
	std::string pkname;
	//std::size_t with_flver = name.find("-");//si el paquete incluye informacion de version
	int indexVer = -1;
	octetos::core::Semver verFlag;
	std::string strPureName = "",strPureVer;
	//std::size_t with_flslah = package.rfind("/");//si el paquete incluye informacion de version
	int counpk_match = 0;
	//std::cout << "Step 3. \n";
	for(std::string d : dirs)
	{	
		//std::cout << "getVersion:Step 4.1. \n";
		if(jump(d,name)) 
		{			
			//std::cout << "Jumping " << d << " because : " << name << "\n";
			continue;
		}
		
		//
		strPureName = "";
		strPureVer= "";
		std::regex regexcomps("-");
		std::vector<std::string> regexoutname(
						std::sregex_token_iterator(name.begin(), name.end(), regexcomps, -1),
						std::sregex_token_iterator()
						);
		//std::cout << d << " count : " << regexoutname.size() << "\n";
		//std::cout << name << "\n";
		for(int i = 0; i < regexoutname.size(); i++)
		{
			//std::cout << "Processing " << regexoutname[i] << "\n";
			if(verFlag.extractNumbers(regexoutname[i]))
			{
				indexVer = i;
				strPureVer = regexoutname[i];
				break;
			}
			if(strPureName.size() == 0)strPureName = regexoutname[i];
			else strPureName += "-" + regexoutname[i];
			//std::cout << "Final pure string " << strPureName << "\n";
		}
		
		//std::cout << "Step 4.2. \n";	
		if(indexVer > -1)//si se especifica version en el nombre de paquete
		{
			if(d.find(strPureName + "-" + strPureVer) == 0 )
			{
				//std::cout << " Macth " << d << " \n";
				findedPk = true;
				pkname = d;
				counpk_match++;
			}
		}
		else
		{
			//std::cout << " Name : " << name << " : Directory " << d << " \n";
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
	//std::cout << "Step 6. \n";
	if(counpk_match > 1) 
	{
		std::cerr << "Nombre ambiguo, agrege informacion de version si puede haber diferentes version del mismmo paquete.\n";
		for(std::string d : dirs)
		{
			if(d.find(name + "-" ) == 0 )
			{
				std::cerr << "\t" << d << ".\n";
			}
		}
		return false;
	}
	//std::cout << "Step 7. \n";

	std::string verpk;
	if(indexVer > -1) 
	{
		verpk = strPureVer;
	}
	else 
	{
		verpk = pkname.substr(name.size() + 1);
	}
	//std::cout << "version found : " << verpk << ".\n";
	if(!ver.extractNumbers(verpk)) 
	{
		std::cerr << "Fallo al parsear la version '" << verpk << "'.\n";
		return false;
	}
	//std::cout << "Step 8. \n";
	
	return true;
}
Portage::Portage(int argc, char *argv[]):Version(argc,argv)
{
	db = "/var/db/pkg/";
}

}
}