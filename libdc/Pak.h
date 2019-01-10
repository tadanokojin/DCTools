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

#pragma once
#include "stdafx.h"

namespace DC
{
	using namespace std::experimental;

	class Pak
	{
	public:
		class Item
		{
			public:
				static const uint32_t HEADER_SIZE = 80;

				std::string m_name;
				size_t m_size;
				std::vector<char> m_data;

				Item(std::vector<char> data, std::string name);
				virtual ~Item() {};

				size_t Size();
				void Write(std::ofstream &file);
				std::string GetName();
		};

		Pak(std::string dir);
		~Pak();

		static Pak* Create(std::string dir);

		bool Write();
		bool IsValid();
		void AddItem(filesystem::directory_entry item);
		void AddItem(Pak::Item* item);
	protected:
		bool m_valid;
		std::ofstream m_file;
		std::vector<Pak::Item*> m_items;
	};
}