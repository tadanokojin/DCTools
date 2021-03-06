/*
 *	Copyright (C) 2018 Kojin
 *	https://github.com/tadanokojin
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "pch.h"
#include "Pak.h"

using namespace std;
using namespace DC;

void print_help()
{
	cout << "usage: repak DIRECTORY\n";
	cout << "\n";
	cout << "2018 Kojin <kojin@protonmail.com>\n"; 
	cout << "https://github.com/tadanokojin";
	getchar();
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		print_help();
		return 0;
	}

	cout << "Opening Files...\n";

	auto pak = Pak::Create(argv[1]);

	if (!pak->Write())
	{
		delete pak;

		cout << "Error writing file\n";
		getchar();

		return 1;
	}

	delete pak;

	cout << "Pak file sucessfully created.\n";
	getchar();

	return 0;
}