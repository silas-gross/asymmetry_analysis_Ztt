#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include "/home/silas/root/include/TH1.h"
#include "/home/silas/root/include/TFile.h"


std::pair< std::vector<float>, std::vector < std::vector<float> > > get_vals_of_Ab4 (std::string name)
{
	//This function will output a pair giving the value of AB4 in lab/ttZ frame for a particluar asymm
	//the file will be read in as Asym val* 10 \n A b2 (ttZ)=val   A b4 (ttZ)= val \n etc
	std::string line;
	bool ready_to_read=false;
	std::vector<float> datapts(3); //point around which we take the asymm, b4 at ttZ, b4 at lab
	std::vector < std::vector<float> > data;
	std::vector<float> fixed (2);
	std::ifstream f; 
	f.open(name);
	while(f.is_open() && !f.eof())
	{
		try{
		while(std::getline(f, line))
		{
			std::stringstream part_vals(line), subpart;
			std::string part, sub;
			while (std::getline(part_vals, part, '\t'))
			{
				if(line.find('=')==std::string::npos)
				{
					if(line.find("section")==std::string::npos)
					{
						try{
							datapts.at(0)=std::stof(part)/10;
						}
						catch(std::exception& e){}
					}
					else
					{
						//std::cout<<"hello this line is " <<line <<std::endl;
						std::stringstream firstline(line), further;
						std::string subpart, subsub;
						int i=0;
						while(std::getline(firstline, subpart, '\t'))
						{
							i++;
							if (subpart.find("section")!=std::string::npos)
							{
								further<<subpart;
								while(std::getline(further, subsub, ':')){
									if(subsub.find("s")==std::string::npos)
									{
										//std::cout<<subsub<<std::endl;
										fixed.at(1)=std::stof(subsub);
										//std::cout<<fixed.at(1)<<std::endl;
									}
								}
							}
							if (i==2)
							{
								std::stringstream furthers(subpart);
								std::string ss;
								while(getline(furthers, ss, '#')){
									std::stringstream fs(ss);
									std::string s;
									while(getline(fs, s, ' ')){
										if(s.find("ctG")==std::string::npos && s.find("#")== std::string::npos&& s.find(".")!=std::string::npos) fixed.at(0)= std::stof(s);
									}
								//	std::cout<<"Value of ctG: " <<fixed.at(0) <<std::endl;
									if (fixed.at(0) >0 && fixed.at(0) <0.001) fixed.at(0)=0;
								}
								
							}
							if (i==3) datapts.at(0)=std::stof(subpart)/10;
						}
					}
				}
				if(part.find("b4") != std::string::npos)
				{
					if (part.find("ttZ") !=std::string::npos)
					{
						subpart<<part;
						while(getline(subpart, sub, '=')){
							if( sub.find("(")==std::string::npos) datapts.at(1)=std::stof(sub);
						}
					}
				

					if (part.find("lab") !=std::string::npos)
					{
						subpart<<part;
						//std::cout<<"this is a lab" <<std::endl;
						while(getline(subpart, sub, '=')){
							if( sub.find("(")==std::string::npos) datapts.at(2)=std::stof(sub);
						}
						ready_to_read=true;
					}
				}
			}
			if(ready_to_read)
			{
				data.push_back(datapts);
				ready_to_read=false;
			}
		}
		}
		catch(std::exception& e ){ }
	}
	std::pair < std::vector<float>, std::vector<std::vector <float>>> datap (fixed, data);
	return datap;
}
std::vector < std::pair < std::string, std::vector < std::vector<float> > > > rearange_data (std::vector < std::pair < std::vector<float>, std::vector <std::vector<float> > > >data)
{
	std::vector <std::pair < std::string, std::vector<std::vector<float>> > > vals (data.at(0).second.size()); //needs to go ttZ then lab then xsec, finaly the val of the pit of interest
	std::vector < std::vector<std::vector<float> > > dummy (data.at(0).second.size(), std::vector<std::vector<float>>(data.size())); //each top level vector in here is all ctG values at a single asympt
	std::vector <std::vector <float> > ctgval(data.size()); //this will hold the single values
		
	for (int i =0; i<data.size(); i++)
	{
		float ctg=data.at(i).first.at(0);
		float xsec=data.at(i).first.at(1);
		std::vector<float> val(4);
		for(int j=0; j<data.at(i).second.size(); j++)
		{
			val.at(0)=ctg; 
			val.at(1)=xsec;
			val.at(2)=data.at(i).second.at(j).at(1);
			val.at(3)=data.at(i).second.at(j).at(2);
			int asymval=data.at(i).second.at(j).at(0)*10;
			int asymnumb=9+asymval;
			int ctgnumb=ctg*1 +9;			
			dummy.at(asymnumb).at(ctgnumb)=val;
//			std::cout<< "for element aysm=" <<asymval <<" ctg =" <<ctgnumb <<"dummy has size " <<dummy.at(asymnumb).at(ctgnumb).size() <<std::endl;
		}
	}
	std::cout<<"why ?" <<dummy[11][2].size() <<std::endl; //so this is the problem, dummy is reseting to zero and I dont know why?
	for (int i=0; i<data.at(0).second.size(); i++)
	{
		std::string asympt=std::to_string(data.at(0).second.at(i).at(0));
		std::pair <std::string, std::vector <std::vector<float> > > p;
		p.first=asympt;
		p.second=dummy.at(i);
		vals.at(i)= p;
	}
	return vals;
}
		
	
void make_graphs ( std::vector <std::pair<std::string, std::vector<std::vector<float>> > > data)
{
	for(int j=0; j<data.size(); j++){
		std::string namet="b4_tt_Z_"+data.at(j).first, titlet="Asymmetery on b4 (ttZ) around "+data.at(j).first;
		std::string namel="b4_lab_"+data.at(j).first, titlel="Asymmetery on b4 (lab) around "+data.at(j).first;
		TH1F* b4_ttZ = new TH1F(namet.c_str(),titlet.c_str(), 21, -1, 1);
		TH1F* b4_lab=new TH1F(namel.c_str(), titlel.c_str(), 21, -1, 1);
		std::string xs="xsec"+data.at(j).first;
		TH1F* xsec=new TH1F (xs.c_str(), "Cross Section", 21, -1, 1);
		std::vector<float> ref_vals(4);
		for (int i=0; i <data.at(j).second.size(); i++)
		{
			if(data.at(j).second.at(i).size()==0) continue;
			if (data.at(j).second.at(i).at(0)==0) ref_vals=data.at(j).second.at(i);
			else continue;
		}
		for (int i =0; i<data.at(j).second.size(); i++)
		{
			if(data.at(j).second.at(i).size()==0) continue;
			std::vector<float> d = data.at(j).second.at(i);
			int ctg=d.at(0)*10;
			int bin= 11+ctg;
			xsec->SetBinContent(i, d.at(1)/ref_vals.at(1));
			b4_ttZ->SetBinContent(i, d.at(2)/ref_vals.at(2));
			b4_lab->SetBinContent(i, d.at(3)/ref_vals.at(3));
		}
		xsec->Write();
		b4_ttZ->Write();
		b4_lab->Write();
	}	 
}
int main(int argc, char** argv)
{
	std::ifstream input_filenames;
	input_filenames.open("fnames.txt");
	if (!input_filenames.is_open()) std::cout<<"failed to get list of files" <<std::endl;
	std::vector < std::string> data_files;
	std::string line;
	while(input_filenames.is_open() && !input_filenames.eof())
	{
		while(getline(input_filenames, line))
		{
			 data_files.push_back(line);
		}
		//data_files.back.open(line);
	}	
	std::vector <std::pair < std::vector<float>, std::vector<std::vector<float>>>> data_from_files;
	for(int i=0; i < data_files.size(); i++)
	{
		data_from_files.push_back(get_vals_of_Ab4(data_files.at(i)));
	}
	TFile* f= new TFile("all_data.root", "RECREATE");
	auto data_to_output=rearange_data(data_from_files);
	std::cout<<"THISSSS: " <<data_to_output.size()<<"," <<data_to_output[1].second.size() <<" test value" <<data_to_output[1].second[2].size() <<std::endl;
	make_graphs(data_to_output);
	f->Write();
	f->Close();
	std::cout<<"root files are made"<<std::endl;
	std::ofstream output("data_from_ctG_asymm_sweep.csv");
	output<<"Asymmetry value , ctG value, Ab4(ttZ), Ab4(lab), xsec, Ab4(ttZ) [norm], Ab4(lab)[norm], xsec [norm]" <<std::endl;
		
	for(int i=0; i<data_to_output.size(); i++)
	{
		std::string as=data_to_output.at(i).first;
		try{
		for (int j=0; j< data_to_output.at(i).second.size(); j++)
		{
			auto d = data_to_output.at(i).second.at(j);
			output << as <<"," <<d.at(0) <<"," << d.at(2) <<"," <<d.at(3) <<"," <<d.at(1) <<",";
		//	output<< d.at(2)/atz <<"," <<d.at(3)/al <<"," <<d.at(1)/xn  <<std::endl;
		}
		}
		catch(std::exception& e){std::cout<<"failed at a thing" <<std::endl;}
	}
	output.close();
	return 0;
}
