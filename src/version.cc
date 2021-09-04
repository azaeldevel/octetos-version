
#include <iostream>
#include <list>
#include <string>
#include <regex>


#include "version.hh"



namespace oct
{
namespace version
{
	Version::Version()
	{}

	bool Version::get_unknowOption() const
	{
		return unknowOption;
	}
	const std::string& Version::getmsg_unknowOption()const
	{
		return msgUnknowOption;
	}
bool Version::get_autohelp()const
{
	return autohelp;
}

/**
 * \brief 
 * \return true si el directorio puede ser ignorado, false en otro caso.
 */
bool Version::jump(const std::string& directory,const std::string& name)const
{
	//std::cout << "jump:Step 1.\n";
	//std::cout << directory << " - " << name << ".\n";
	
	//descartar los directorio que empiezan con '.'
	if(directory[0] == '.') return true;
	//std::cout << "jump:Step 2\n";
	
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
	char c = directory[name.size() + 1];
	if( c < '0' or c > '9')
	{
		return true;
	}
	//std::cout << "jump:Step 3\n";
	
	oct::core::Semver ver;
	//std::cout << "R: " << strremanente << ".\n";
	if(!ver.extractNumbers(strremanente))
	{//el remanten es una version por lo que no se filtra
		return true;
	}
	//std::cout << "jump:Step 4\n";
	
	return false;
}
bool Version::compare(const std::string& package,const std::string& op,oct::core::Semver& verrq,oct::core::Semver& verfound)
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
bool Version::compare(const std::string& package,const std::string& op,oct::core::Semver& ver)
{
	oct::core::Semver ver1;
	return compare(package,op,ver,ver1);
}
bool Version::getop_help()const
{
	return op_help;
}
void Version::help()
{
	std::cout << "version opciones parámetros     Formato genérico.\n";
	std::cout << "version -h                      Ayuda, para desplegar este opctión.\n";
	std::cout << "version -g nombredepaquete      Para optener la version del paquete.\n";
	std::cout << "version -c|-ci nombredepaquete (==|s=|g=|s|g) version\n                                 Comparar la version del paquete con la \n                                 indicada en el ultimo parametro.\n";
	std::cout << "version -p                      Retorna informacion sobre la plataforma.\n";
}
Version::Version(int argc, char *argv[])
{	
	op_help = false;
	op_compare = false;
	op_indicators = false;
	op_getver = false;
	op_warning = false;
	op_error = false;
	op_platform = false;
	autohelp = false;
	unknowOption = false;
	msgUnknowOption = "";
	
	if(argc == 1) 
	{
		autohelp = true;
		return;//no es necesario parsear las opciones ya que no hay.
	}
	
	std::string ops = argv[1];

	for(char c : ops)
	{		
		if(c == '-')
		{
			
		}
		else if(c == 'h')
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
		else if(c == 'p')
		{
			op_platform = true;
		}
		else
		{
			unknowOption = true;
			if(msgUnknowOption.empty()) 
			{
				msgUnknowOption += "Opción '" + std::string(1,c) + "' es desconocida.";
			}
			else 
			{
				msgUnknowOption += "\nOpción '" + std::string(1,c) + "' es desconocida.";
			}
		}
	}
}
bool Version::getop_platform()const
{
	return op_platform;
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

