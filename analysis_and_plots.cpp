#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "TH1.h"
#include "TFile.h"
#include <vector>
#include <sstream>
#include <utility>
void calculate_assym()
{
	
}

void make_single_asym(std::ifstream* f, float asymm_pt)
{
	float sum_left=0, sum_right=0, sum_left_lab=0, sum_right_lab=0;
	std::string val;
	std::vector <float> col1, col2, col3;
	while (f->is_open() && !f->eof())
	{
		while(getline(*f, line, '\t'))
		{
			a
		}
}
int main()
{
	std::vector <std::ifstream> input_b2_data_files, input_b4_data_files;
	std::vector <std::string> repo_names;
	std::pair <float, float> ctg_vals_with_cross_section;
	std::fstream input_file;
	input_file.open("ctg_repo_names.txt");
	std::string file_loc="~/ctG_runs/"
	std::string line;
	while ( input_file.is_open()==true && ! input_file.eof())
	{
		while(getline(input_file, line)) repo_names.push_back(line);
	}
	for (int i =0; repo_names.size(), i++)
	{
		ifstream f2, f4;
		f2.open(file_loc+"b2_"+repo_names.at(i)+".dat");
		f4.open(file_loc+"b4_"+repo_names.at(i)+".dat");
		input_b2_data_files.push_back(f2);
		input_b4_data_files.push_back(f4);
		//this has loaded in the data files
		//need to grab the ctG value and the cross section here as well
	}
	

	return 0;

}
