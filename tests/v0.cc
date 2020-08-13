#include <iostream>
#include <CUnit/Basic.h>
#include <regex>
#include <string.h>

#ifdef PORTAGE
	#include "Portage.hh"
#elif PACMAN
	#include "Pacman.hh"
#elif APT
#error "The backend for APT is in development"
#endif


bool writeParamschar (const std::string& arg, int* argc, char ***argv);



void comparations()
{
	char **argv=NULL;
	int argc=0;


//Generic test >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//test1
#ifdef PORTAGE
	if(writeParamschar("version -ci make g= 2.0",&argc,&argv))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	octetos::version::Portage cmdver_test1(argc,argv);
#elif PACMAN
	octetos::version::Pacman cmdver_test1(argc,argv);
#elif APT
#error "The backend for APT is in development"
#endif
	if(cmdver_test1.getop_compare())
	{
		octetos::core::Semver verrq,verfound;
		if(!verrq.set(argv[4]))
		{
			std::cerr << "Fallo el parseo de la version indicada '" << argv[4] << "'\n.";;
		}
		if(cmdver_test1.compare(argv[2],argv[3],verrq,verfound))
		{
			CU_ASSERT(true);
		}
		else 
		{
			CU_ASSERT(false);
		}
	}	
//test2
#ifdef PORTAGE
	//argv=NULL;
	//argc=0;
	if(writeParamschar("version -ci python-3.7 g= 2.0",&argc,&argv))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	octetos::version::Portage cmdver_test2(argc,argv);
#elif PACMAN
	octetos::version::Pacman cmdver_test2(argc,argv);
#elif APT
#error "The backend for APT is in development"
#endif
	if(cmdver_test2.getop_compare())
	{
		octetos::core::Semver verrq,verfound;
		if(!verrq.set(argv[4]))
		{
			std::cerr << "Fallo el parseo de la version indicada '" << argv[4] << "'\n.";;
		}
		if(cmdver_test2.compare(argv[2],argv[3],verrq,verfound))
		{
			CU_ASSERT(true);
		}
		else 
		{
			CU_ASSERT(false);
		}
	}	

//test3
#ifdef PORTAGE
	//argv=NULL;
	//argc=0;
	if(writeParamschar("version -ci gcc-9.2 g= 8.1",&argc,&argv))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	octetos::version::Portage cmdver_test3(argc,argv);
#elif PACMAN
	octetos::version::Pacman cmdver_test3(argc,argv);
#elif APT
#error "The backend for APT is in development"
#endif
	if(cmdver_test3.getop_compare())
	{
		octetos::core::Semver verrq,verfound;
		if(!verrq.set(argv[4]))
		{
			std::cerr << "Fallo el parseo de la version indicada '" << argv[4] << "'\n.";;
		}
		if(cmdver_test3.compare(argv[2],argv[3],verrq,verfound))
		{
			CU_ASSERT(true);
		}
		else 
		{
			CU_ASSERT(false);
		}
	}	


}


void comparations_negatives()
{
	char **argv=NULL;
	int argc=0;


//Generic test >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//test1
#ifdef PORTAGE
	//argv=NULL;
	//argc=0;
	if(writeParamschar("version -ci make s= 2.0",&argc,&argv))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	octetos::version::Portage cmdver_test1(argc,argv);
#elif PACMAN
	octetos::version::Pacman cmdver_test1(argc,argv);
#elif APT
#error "The backend for APT is in development"
#endif
	if(cmdver_test1.getop_compare())
	{
		octetos::core::Semver verrq,verfound;
		if(!verrq.set(argv[4]))
		{
			std::cerr << "Fallo el parseo de la version indicada '" << argv[4] << "'\n.";;
		}
		if(cmdver_test1.compare(argv[2],argv[3],verrq,verfound))
		{
			CU_ASSERT(false);
		}
		else 
		{
			CU_ASSERT(true);
		}
	}	
//test2
#ifdef PORTAGE
	//argv=NULL;
	//argc=0;
	if(writeParamschar("version -ci python-3.7 s= 2.0",&argc,&argv))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	octetos::version::Portage cmdver_test2(argc,argv);
#elif PACMAN
	octetos::version::Pacman cmdver_test2(argc,argv);
#elif APT
#error "The backend for APT is in development"
#endif
	if(cmdver_test2.getop_compare())
	{
		octetos::core::Semver verrq,verfound;
		if(!verrq.set(argv[4]))
		{
			std::cerr << "Fallo el parseo de la version indicada '" << argv[4] << "'\n.";;
		}
		if(cmdver_test2.compare(argv[2],argv[3],verrq,verfound))
		{
			if(cmdver_test2.getop_indicators())
			{
				std::cout << argv[2] << " : pass(" << (std::string)verfound << ")\n";				
			}
			else
			{
				std::cout << "true\n";
			}
			CU_ASSERT(false);
		}
		else 
		{
			CU_ASSERT(true);
		}
	}	

//test3
#ifdef PORTAGE
	//argv=NULL;
	//argc=0;
	if(writeParamschar("version -ci gcc-9.2 s= 8.1",&argc,&argv))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	octetos::version::Portage cmdver_test3(argc,argv);
#elif PACMAN
	octetos::version::Pacman cmdver_test3(argc,argv);
#elif APT
#error "The backend for APT is in development"
#endif
	if(cmdver_test3.getop_compare())
	{
		octetos::core::Semver verrq,verfound;
		if(!verrq.set(argv[4]))
		{
			std::cerr << "Fallo el parseo de la version indicada '" << argv[4] << "'\n.";;
		}
		if(cmdver_test3.compare(argv[2],argv[3],verrq,verfound))
		{
			CU_ASSERT(false);
		}
		else 
		{
			CU_ASSERT(true);
		}
	}	


}

void comparations_portage()
{
	char **argv=NULL;
	int argc=0;


//Specific >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//test2
#ifdef PORTAGE
	if(writeParamschar("version -ci sys-devel/make g= 2.0",&argc,&argv))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	octetos::version::Portage cmdver_test2(argc,argv);
#elif PACMAN
	octetos::version::Pacman cmdver_test2(argc,argv);
#elif APT
#error "The backend for APT is in development"
#endif
	if(cmdver_test2.getop_compare())
	{
		octetos::core::Semver verrq,verfound;
		if(!verrq.set(argv[4]))
		{
			std::cerr << "Fallo el parseo de la version indicada '" << argv[4] << "'\n.";
		}	
		//std::cout << "test:Step 1\n.";	
		if(cmdver_test2.compare(argv[2],argv[3],verrq,verfound))
		{
			CU_ASSERT(true);
		}
		else 
		{
			CU_ASSERT(false);
		}
	}	
}





bool writeParamschar (const std::string& arg, int* argc, char ***argv)
{
	std::regex regex(" ");
	std::vector<std::string> regexout(
		std::sregex_token_iterator(arg.begin(), arg.end(), regex, -1),
		std::sregex_token_iterator()
	);
	
	if(argv[0] != NULL)
	{
		for(int i = 0; i < regexout.size()-1; i++)
		{
			free(argv[0][i]);
		}
		argv[0] = NULL;
	}
	
	argv[0] = (char**)malloc(sizeof(char*)*(regexout.size()+1));
	std::vector<std::string>::iterator it = regexout.begin();
	for(int i = 0; i < regexout.size(); i++,it++)
	{
		argv[0][i] = (char*)malloc(strlen(it->c_str())+1);
		strcpy((*argv)[i],it->c_str());
	}
	//argv[0][regexout.size()] = NULL;

	//
	argc[0] = regexout.size();

	/*for(int i = 0; i < regexout.size() ; i++)
	{
		std::cout << argv[0][i] << "\n";
	}*/
	
	return true;
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
	
	if ((NULL == CU_add_test(pSuite, "Comparing with generic names.", comparations)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}	
	if ((NULL == CU_add_test(pSuite, "Comparing with generic names negativas.", comparations_negatives)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "Comparing with portage names", comparations_portage)))
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