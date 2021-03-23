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
#include "/home/silas/root/include/TLegend.h"
#include "/home/silas/root/include/TCanvas.h"
#include "/home/silas/root/include/TStyle.h"
#include "/home/silas/root/include/TPaveText.h"

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
std::vector < std::pair < float, std::vector < std::vector<float> > > > rearange_data (std::vector < std::pair < std::vector<float>, std::vector <std::vector<float> > > >data)
{
	std::vector <std::pair < float, std::vector<std::vector<float>> > > vals (data.at(0).second.size()); //needs to go ttZ then lab then xsec, finaly the val of the pit of interest
	std::vector < std::vector<std::vector<float> > > dummy (data.at(0).second.size(), std::vector<std::vector<float>>(data.size())); //each top level vector in here is all ctG values at a single asympt
	std::vector<std::vector<float>> all_vals; 
		
	for (int i =0; i<data.size(); i++)
	{
		float ctg=data.at(i).first.at(0);
		float xsec=data.at(i).first.at(1);
		for(int j=0; j<data.at(i).second.size(); j++)
		{
			std::vector<float> val;
			float atz=data.at(i).second.at(j).at(1), al=data.at(i).second.at(j).at(2);
			int asymval=data.at(i).second.at(j).at(0)*10;
			val.push_back(asymval);
			val.push_back(ctg);
			val.push_back(xsec);
			val.push_back(atz);
			val.push_back(al);
			all_vals.push_back(val);
	//		val.delete();
//			std::cout<< "for element aysm=" <<asymval <<" ctg =" <<ctgnumb <<"dummy has size " <<dummy.at(asymnumb).at(ctgnumb).size() <<std::endl;
		}
		//std::cout<<"is it empty at asym of 0? " <<dummy.at(0).at(i).size() <<std::endl;
	}
//	std::cout<<"why ?" <<all_vals[2].size() <<std::endl; //so this is the problem, dummy is reseting to zero and I dont know why?
	for(int i=0; i<all_vals.size(); i++)
	{
		int abin=all_vals[i][0];
		int ctgbin=all_vals[i][1]*10+10;
		abin=abin+9;
		std::cout<<"Bins are " <<abin <<",  and ctgbin " <<ctgbin <<"with ctgval " <<all_vals[i][1] <<std::endl;
		if(abin > dummy.size() || ctgbin >data.size() ) std::cout<<"there is a problem wiht values " <<abin <<" , " <<ctgbin <<std::endl;
		std::vector<float> sval(4);
		sval[0]= all_vals[i][1];
		sval[1]= all_vals[i][2];
		sval[2]= all_vals[i][3];
		sval[3]= all_vals[i][4];
		dummy.at(abin).at(ctgbin)=sval;
	}
	std::cout<<"is this working? " <<dummy[1][2].size() <<std::endl;
	for (int i=0; i<data.at(0).second.size(); i++)
	{
		//std::string asympt=std::to_string(data.at(0).second.at(i).at(0));
		std::pair <float, std::vector <std::vector<float> > > p;
		p.first=data.at(0).second.at(i).at(0);
		p.second=dummy.at(i);
		vals.at(i)= p;
	}
	return vals;
}
		
	
void make_graphs ( std::vector <std::pair<float, std::vector<std::vector<float>> > > data)
{
	TCanvas* c=new TCanvas();
	TLegend* l=new TLegend();
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TPaveText* t = new TPaveText(0, 0.9, 1,1, "NB");
	t->AddText("Asymmetry Samples on b4 in the ttZ frame");
	t->Draw(); 
	l->SetHeader("Asymmetries (normalized in respect to SM) in b4 in ttZ frame", "C");
	for(int j=0; j<data.size(); j++){
		int asval=data.at(j).first*10;
		std::string d, d1= std::to_string(data.at(j).first);
		if(asval<0) d="ctG_minus_" + std::to_string(asval);
		if(asval==0) d="sm";
		if(asval>0) d="ctG_plus_" + std::to_string(asval);
		std::string namet="b4_tt_Z_"+d, titlet="Asymmetery on b4 (ttZ) around "+d1;
		std::string namel="b4_lab_"+d, titlel="Asymmetery on b4 (lab) around "+d1;
		TH1F* b4_ttZ = new TH1F(namet.c_str(),titlet.c_str(), 21, -1, 1);
		TH1F* b4_lab=new TH1F(namel.c_str(), titlel.c_str(), 21, -1, 1);
		//std::string xs="xsec"+data.at(j).first;
		TH1F* xsec=new TH1F ("xsec", "Cross Section", 21, -1, 1);
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
			int ctg=d.at(0);
			xsec->SetBinContent(i+1, d.at(1)/ref_vals.at(1));
			b4_ttZ->SetBinContent(i+1, d.at(2)/ref_vals.at(2));
			b4_lab->SetBinContent(i+1, d.at(3)/ref_vals.at(3));
		}
		xsec->GetXaxis()->SetTitle("ctG");
		xsec->GetYaxis()->SetTitle("Normalized to 1");
		xsec->SetLineWidth(7);
		if(j==2) xsec->Write();
		b4_ttZ->Write();
		b4_lab->Write();
		if (j==0) xsec->Draw("c");
		if(j%5==0){
		b4_ttZ->SetLineColor(j+1);
		b4_ttZ->Draw("same c");
		}
		if(j==0) l->AddEntry(xsec, "Cross Section for process");
		if(j%5==0) l->AddEntry(b4_ttZ);
	}
	l->Draw();	 
	c->Print("b4_ttZ_graphs.pdf");
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
	make_graphs(data_to_output);
	f->Write();
	f->Close();
	std::cout<<"root files are made"<<std::endl;
	std::ofstream output("data_from_ctG_asymm_sweep.csv");
	output<<"Asymmetry value , ctG value, Ab4(ttZ), Ab4(lab), xsec, Ab4(ttZ) [norm], Ab4(lab)[norm], xsec [norm]" <<std::endl;
		
	for(int i=0; i<data_to_output.size(); i++)
	{
		std::string as=std::to_string(data_to_output.at(i).first);
		float xn=data_to_output.at(i).second.at(10).at(1), atz=data_to_output.at(i).second.at(10).at(2), al=data_to_output.at(i).second.at(10).at(3);
		try{
		for (int j=0; j< data_to_output.at(i).second.size(); j++)
		{
			auto d = data_to_output.at(i).second.at(j);
			output << as <<"," <<d.at(0) <<"," << d.at(2) <<"," <<d.at(3) <<"," <<d.at(1) <<",";
			output<< d.at(2)/atz <<"," <<d.at(3)/al <<"," <<d.at(1)/xn  <<std::endl;
		}
		}
		catch(std::exception& e){std::cout<<"failed at a thing" <<std::endl;}
	}
	output.close();
	return 0;
}
