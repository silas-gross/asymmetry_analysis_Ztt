#include <fsteam>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include "TH1.h"
#include "TFile.h"
#include "THistPainter.h"

std::vector < float > get_vals_of_Ab4 (std::fstream* f)
{
	//This function will output a pair giving the value of AB4 in lab/ttZ frame for a particluar asymm
	//the file will be read in as Asym val* 10 \n A b2 (ttZ)=val   A b4 (ttZ)= val \n etc
	std::string line;
	bool ready_to_read=false;
	float datapts[3]; //point around which we take the asymm, b4 at ttZ, b4 at lab
	std::vector < float > data;
	while(f->is_open() && !f->eof())
	{
		while(getline(f, line))
		{
			std::stringstream part_vals(line), subpart;
			std::string part, sub;
			if (getline(part_vals, part, ' '))
			{
				if(part.find('=')==std::string::npos) datapts[0]=std::stof(part)/10;
				if(part.find("b4") != std::string::npos)
				{
					if (part.find("ttZ") !==std::string::npos)
					{
						subpart(part);
						if(getline(subpart, sub, '=') && sub.find("(")==std::string::npos) datapts[1]=std::stof(sub);
					}
				

					if (part.find("lab") !==std::string::npos)
					{
						subpart(part);
						if(getline(subpart, sub, '=') && sub.find("(")==std::string::npos) datapts[2]=std::stof(sub);
						ready_to_read=true;
					}
				}
			}
			if(ready_to_read)
			{
				data.push_back(datapts);
				read_to_read=false;
			}
		}
	}
	return data;
}
void make_graphs ( std::vector < std::pair <float, std::vector <float > > >)
{
	shshsdh
}
int main(int argc, char** argv)
{
	std::fstream input_filenames;
	input_filenames.open(argv[1]);
	std::vector < std::fstream > data_files;
	std::string line;
	while( input_filename.is_open() && !input_filenames.eof() )
	{
		getline(input_filename, line);
		data_files.push_back( std::fstream file(line));
	}
	
}
