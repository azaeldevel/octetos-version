/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2020 Azael R. <azael.devel@gmail.com>
 * 
 * octetos-version is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * octetos-version is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string.h>


#ifdef PORTAGE
	#include "Portage.hh"
#elif defined PACMAN
	#include "Pacman.hh"
#elif defined APT
	#include <apt-pkg/cachefile.h>
	#include <apt-pkg/pkgcache.h>
	#include "Apt.hh"
#else 
#error "Plateforma desconocida."
#endif

int main(int argc, char *argv[])
{
#ifdef PORTAGE
	octetos::version::Portage cmdver(argc,argv);
#elif defined PACMAN
	octetos::version::Pacman cmdver(argc,argv);
#elif defined APT
	octetos::version::Apt cmdver(argc,argv);

	pkgInitConfig(*_config);
    pkgInitSystem(*_config, _system);

    pkgCacheFile cache_file;
    pkgCache* cache = cache_file.GetPkgCache();

    for (pkgCache::PkgIterator package = cache->PkgBegin(); !package.end(); package++) {
        std::cout << package.Name() << std::endl;
    }
	
#else 
#error "Plataforma desconocida."
#endif
	if(cmdver.get_unknowOption())
	{
		std::cout << cmdver.getmsg_unknowOption() << "\n";
	}

	//>>>>>>>>>>>>>>>>>>>>>generic operations	
	if(cmdver.getop_help() or cmdver.get_autohelp())
	{
		if(argc == 1)
		{
			std::cout << "Es necesario especificar una opción.\n";
		}
		else if(argc > 2)
		{
			std::cerr << "Opciones ambiguas, la opción ayuda no puede mesclarse con otras opciones.\n";
			return EXIT_FAILURE;
		}
		cmdver.help();
		return EXIT_SUCCESS;
	}

	//
	if(cmdver.getop_platform())
	{
		switch(cmdver.getPlatform())
		{
			case octetos::version::Version::Platform::portage:
				std::cout << "Portage\n";
				break;
			case octetos::version::Version::Platform::pacman:
				std::cout << "Pacman\n";
				break;
			case octetos::version::Version::Platform::apt:
				std::cout << "APT\n";
				break;
			default:
				std::cout << "Desconocido\n";
				return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}
	
	//>>>>>>>>>>>>>>>>>>>>>operation
	if(cmdver.getop_version())
	{
		octetos::core::Semver verpk;
		if(cmdver.getVersion(argv[2],verpk))
		{
			std::cout << (std::string)verpk << "\n";
			return EXIT_SUCCESS;
		}
		else 
		{
			return EXIT_FAILURE;
		}
	}
	
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
			return EXIT_SUCCESS;
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
			return EXIT_FAILURE;
		}
	}
	
	std::cerr << "Unknow parameters.\n";
	return EXIT_FAILURE;
}

