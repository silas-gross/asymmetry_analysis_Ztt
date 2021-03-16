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
std::vector < std::pair < std::string, std::vector < float > > > re_arange_data (std::vector < std::pair < float, std::vector <float > > >data)
{
	std::vector <std::pair < std::string, std::vector<float> > > vals [data.at(0).second().size()]; //needs to go ttZ then lab then xsec, finaly the val of the pit of interest
	std::vector < std::vector<float >> dummy [data.at(0).second.size()];
	
	for (int i =0; i<data.size(), i++)
	{
		float ctg=data.at(i).first()[0];
		float xsec=data.at(i).first()[1]
		float val[4];
		for(int j=0; j<data.at(i).second().size(); j++)
		{
			val[0]=ctg; 
			val[1]=xsec;
			val[2]=data.at(i).second().at(j)[1];
			val[3]=data.at(i).second().at(j)[2];
			dummy.at(j).push_back(val);
		}
	}
	for (int i=0; i<dummy.size(); i++)
	{
		std::string asympt=std::string::to_string(data.at(0).second().at(i)[0]);
		std::pair <std::string, std::vector <float > > p;
		p.first()=asympt;
		p.second()=dummy.at(i);
		vals.at(i)= p;
	}
	return vals;
}
		
	
void make_graphs ( std::vector <std::pair<std::string, std::vector<float> > > data)
{
	for(int j=0; j<data.size(); j++){
		std::string namet="b4_tt_Z_"+data.at(j).first(), titlet="Asymmetery on b4 (ttZ) around "+data.at(j).first();
		std::string namel="b4_lab_"+data.at(j).first(), titlel="Asymmetery on b4 (lab) around "+data.at(j).first();
		TH1F* b4_ttZ = new TH1F(namet.c_std(),titlet.c_std(), 21, -1, 1);
		TH1F* b4_lab=new TH1F(namel.c_std(), titlel.c_std(), 21, -1, 1);
		std::string xs="xsec"+data.at(j).first();
		TH1F* xsec=new TH1F (xs.c_std(), "Cross Section", 21, -1, 1);
		float ref_vals[4];
		for (int i=0; i <data.at(j).second().size(); i++)
		{
			if (data.at(j).second().at(i)[0]==0) ref_vals=data.at(j).second().at(i);
			else continue;
		}
		for (int i =0; i<data.at(j).second().size(); i++)
		{
			float d = data.at(j).second().at(i);
			xsec->SetBinContent(i, d[1]/ref_vals[1]);
			b4_ttZ->SetBinContent(i, d[2]/ref_vals[2]);
			b4_lab->SetBinContent(i, d[3]/ref_vals[3]);
		}
		xsec->Write();
		b4_ttZ->Write();
		b4_lab->Write();
	}	 
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
