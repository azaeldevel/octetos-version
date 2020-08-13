
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
bool Version::jump(const std::string& directory,const std::string& name)const
{
	//std::cout << "jump:Step 1.\n";
	//std::cout << directory << " - " << name << ".\n";
	
	//descartar los directorio que empiezan con '.'
	if(directory[0] == '.') return true;
	
	//descartar los directorio que semejantes
	std::size_t f = directory.find(name);//revizar el el nombre del paquete esta contenido en el directorio
	std::string strremanente;
	if(f == 0)
	{
		//std::cout << "D: " << directory << " " << " C:" << directory[name.size() + 1] << " \n";
		strremanente = directory.substr (name.size() + 1,directory.size());
	}
	else if (std::string::npos == f)
	{
		return false;
	}
	else
	{
		return false;
	}
	
	octetos::core::Semver ver;
	//std::cout << "R: " << strremanente << ".\n";
	if(!ver.extractNumbers(strremanente))
	{//el remanten es una version por lo que no se filtra
		return true;
	}
	
	return false;
}
bool Version::compare(const std::string& package,const std::string& op,octetos::core::Semver& verrq,octetos::core::Semver& verfound)
{
	//std::cout << "compare:Step 1.\n";	
	//std::cout << "Pk: " << package << " Op:" << op << "\n";
	if(!getVersion(package,verfound)) return false;
	//std::cout << "compare:Step 2.\n";
	
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
		//std::cout << "comparado las versiones\n";
		//std::cout << (std::string)verfound << ">=" << (std::string)verrq <<":compare\n";
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




}
}

