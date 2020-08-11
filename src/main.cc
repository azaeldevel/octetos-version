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

#include "version.hh"


int main(int argc, char *argv[])
{
	
#ifdef PORTAGE
	octetos::version::Portage cmdver;
#elif PACMAN
#error "The backend for PACMAN is in development"
#elif APT
#error "The backend for APT is in development"
#endif

	//>>>>>>>>>>>>>>>>>>>>>generic operations	
	if(strcmp(argv[1],"-h") == 0)
	{
		if(argc > 2)
		{
			std::cerr << "Ambiguos parameters, help can have more options.\n";
			return EXIT_FAILURE;
		}
		cmdver.help();
		return EXIT_SUCCESS;
	}
	else if(strcmp(argv[1],"--help") == 0)
	{
		cmdver.help();
		return EXIT_SUCCESS;
	}
	
	//>>>>>>>>>>>>>>>>>>>>>portage operation
	if(strcmp(argv[1],"-g") == 0)
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
	else if(strcmp(argv[1],"--get") == 0)
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
	
	if(strcmp(argv[1],"-c") == 0)
	{
		octetos::core::Semver verpk;
		verpk.set(argv[4]);
		if(cmdver.compare(argv[2],argv[3],verpk))
		{
			std::cout << "true\n";
			return EXIT_SUCCESS;
		}
		else 
		{
			std::cout << "false\n";
			return EXIT_FAILURE;
		}
	}		
	if(strcmp(argv[1],"-cf") == 0)
	{
		octetos::core::Semver verpk;
		verpk.set(argv[4]);
		if(cmdver.compare(argv[2],argv[3],verpk))
		{
			std::cout << argv[2] << ": pass\n";
			return EXIT_SUCCESS;
		}
		else 
		{
			std::cout << argv[2] << ": reject\n";
			return EXIT_FAILURE;
		}
	}
	std::cerr << "Unknow parameters.\n";
	return EXIT_FAILURE;
}

