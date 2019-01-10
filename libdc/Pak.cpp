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

#include "stdafx.h"
#include "Pak.h"

namespace DC 
{
	Pak* Pak::Create(std::string dir)
	{
		Pak* pak = new Pak(dir + ".pak");

		for (auto &path : filesystem::directory_iterator(dir))
		{
			pak->AddItem(path);
		}

		return pak;
	}

	Pak::Pak(std::string dir)
		: m_file(std::ofstream(dir,  std::ios::out | std::ios::binary))
	{}

	bool Pak::Write()
	{
		if (!IsValid())
			return false;

		for (auto &item : m_items)
		{
			item->Write(m_file);
		}

		m_file.close();

		return true;
	}

	bool Pak::IsValid()
	{
		return m_file.is_open();
	}

	void Pak::AddItem(filesystem::directory_entry item)
	{
		if (!filesystem::is_regular_file(item))
		{
			std::cout << "NOTICE: ";
			std::cout << item.path();
			std::cout << " is not a regular file (It's a directory, symlink, etc), ignoring...\n";

			return;
		}

		std::cout << item << std::endl;

		std::ifstream file(item, std::ios::binary);

		if (!file.is_open())
		{
			std::cout << "NOTICE: Couldn't read file";
			std::cout << item.path();
			std::cout << " ignoring...\n";
			return;
		}

		std::string name = item.path().filename().string();
		
		std::vector<char> data(
			(std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>()
		);

		Pak::Item* new_item = new Item(data, name);

		AddItem(new_item);
	}

	void Pak::AddItem(Pak::Item* item)
	{
		m_items.push_back(item);
	}

	Pak::~Pak()
	{
		for (auto &item : m_items)
		{
			delete item;
		}

		m_file.close();
	}

	Pak::Item::Item(std::vector<char> data, std::string name)
		: m_data(data), m_name(name)
	{}

	std::string Pak::Item::GetName()
	{
		return m_name;
	}

	size_t Pak::Item::Size()
	{
		return m_data.size();
	}

	void Pak::Item::Write(std::ofstream &file)
	{
		const uint32_t unk = 4; // donno about this value

		size_t size = Size();
		int pos = file.tellp();

		uint32_t next = HEADER_SIZE + size;

		std::cout << std::endl;

		std::cout << "Name: " << m_name << std::endl;
		std::cout << "Offset: " << HEADER_SIZE << std::endl;
		std::cout << "Size: "<< size << std::endl;
		std::cout << "End Offset: " << next << std::endl;
		std::cout << "Pad: " << unk << std::endl;

		// ugly casts
		file.write(m_name.c_str(), 64);
		file.write(reinterpret_cast<const char*>(&HEADER_SIZE), sizeof(uint32_t));
		file.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));
		file.write(reinterpret_cast<const char*>(&next), sizeof(uint32_t));
		file.write(reinterpret_cast<const char*>(&unk), sizeof(uint32_t));

		file.write(m_data.data(), size);
	}
}