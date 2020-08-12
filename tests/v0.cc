#include <iostream>
#include <CUnit/Basic.h>
#include <Portage.hh>
#include <regex>
#include <string.h>


bool writeParamschar (const std::string& arg, int* argc, char ***argv)
{
	std::regex regex(" ");
	std::vector<std::string> regexout(
		std::sregex_token_iterator(arg.begin(), arg.end(), regex, -1),
		std::sregex_token_iterator()
	);
	
	if(*argv != NULL)
	{
		for(int i = 0; (*argv)[i] != NULL; i++)
		{
			free((*argv)[i]);
		}
		(*argv)[regexout.size()] = NULL;
	}
	
	(*argv) = (char**)malloc(regexout.size());
	std::vector<std::string>::iterator it = regexout.begin();
	for(int i = 0; i < regexout.size(); i++,it++)
	{
		(*argv)[i] = (char*)malloc(strlen(it->c_str())+1);
		strcpy((*argv)[i],it->c_str());
	}

	//
	*argc = regexout.size();

	/*for(int i = 0; i < regexout.size() ; i++)
	{
		std::cout << argv[0][i] << "\n";
	}*/
	
	return true;
}

void comparations()
{
	char **argv=NULL;
	int argc=0;
	writeParamschar("version -ci make g= 2.0",&argc,&argv);
	
	octetos::version::Portage cmdver(argc,argv);
	if(cmdver.getop_compare())
	{
		octetos::core::Semver verrq,verfound;
		if(!verrq.set(argv[4]))
		{
			std::cerr << "Fallo el parseo de la version indicada '" << argv[4] << "'\n.";;
		}
		if(cmdver.compare(argv[2],argv[3],verrq,verfound))
		{
			if(cmdver.getop_indicators())
			{
				std::cout << argv[2] << " : pass(" << (std::string)verfound << ")\n";				
			}
			else
			{
				std::cout << "true\n";
			}
			CU_ASSERT(true);
		}
		else 
		{
			if(cmdver.getop_indicators())
			{
				std::cout << argv[2] << " : reject\n";				
			}
			else
			{
				std::cout << "false\n";
			}
			CU_ASSERT(false);
		}
	}	
}

void generic()
{
}


int init(void)
{
	return 0;
}
int clean(void)
{
	return 0;
}
int main(int argc, char *argv[])
{
	/*octetos::core::Artifact packinfo;
	octetos::core::getPackageInfo(packinfo);
	if(octetos::core::Error::check())
	{
		std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
		return EXIT_FAILURE;
	}
	
	int majorNumber = 2;
	if(majorNumber != packinfo.version.getMajor())
	{
		std::cerr << "Cree un nuevo archivo para la version '" << majorNumber << "' estas en la version'" << (std::string)packinfo.version << "'\n";
		return EXIT_FAILURE;
	}*/
	
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	/*std::string& pkName = packinfo.name;
	std::string headerTest = pkName + " " + (std::string)packinfo.version + "\n" + packinfo.licence.getText() + "\n" + packinfo.brief + "\n";*/
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Testing version.", init, clean);
	if (NULL == pSuite) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Testing portage.", comparations)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();	
}