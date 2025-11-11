//
// Created by Amin on 8/22/24.
//

#include "CSV_Editor.h"
#include <iostream>

void CSVEdit::Folder_Parser(const std::string& target_folder_path)
{
    for (const auto& entry : std::filesystem::directory_iterator(target_folder_path))
    {
        target_csv_files.emplace_back(entry.path().string());
    }

    std::erase_if(target_csv_files, [](const std::string& target_csv_filename_path) {
        return target_csv_filename_path.substr(target_csv_filename_path.size() - 4) != ".csv";
    });

    for (const auto& a : target_csv_files)
    {
        std::cout << a << std::endl;
    }
}

int CSVEdit::CSV_Reader(const std::string& target_csv_path)
{

    std::ifstream inputFile(target_csv_path);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file " << target_csv_path << std::endl;
        return 1;
    }
    std::string line{};
    int line_number = 0;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue; // Skip empty lines
        }
        if (line_number == 0) {
            line_number++;
            continue; // Skip first line
        }
        csv_data.push_back(line);
    }
    inputFile.close();

    return 0;
}

void CSVEdit::File_Display() const
{
    for(const auto & i : csv_data)
    {
        std::cout  << i << std::endl;
    }
}

void CSVEdit::Saving_Path_Allocator()
{
    for(auto it : target_csv_files)
    {
        paths_for_saving_data.push_back(it.insert(49,std::string("Cleaned results/")));
    }
}

void CSVEdit::CSV_Data_Cleaner()
{
    for( auto & i : csv_data)
    {
        std::string str;
        const size_t pos = i.find(",");
        str = i.substr(0,pos+1);
        i = i.substr(pos+1);
        i.erase(i.rfind(",")-3,3);
        i.append(str);
        const size_t ipos_start = i.find(",");
        //Two possible senario comparing common mz or comparing names appeared in LCMS results:
        //const size_t ipos_end = i.find( ",", i.find(",")+1);
        if(cleaned_csv_data.empty())
        {
            cleaned_csv_data.emplace_back(i);
        } else
        {
            //Two possible senario comparing common mz or comparing names appeared in LCMS results:
            std::string i_part_for_comprison = i.substr(0, ipos_start);
            //std::string i_part_for_comprison = i.substr(ipos_start, ipos_end-ipos_start+1);
            size_t num = 0;
            for ( auto & j : cleaned_csv_data)
            {
                const size_t jpos_start = j.find(",");
                //Two possible senario comparing common mz or comparing names appeared in LCMS results:
                //const size_t jpos_end = j.find( ",", j.find(",")+1);
                std::string j_part_for_comprison = j.substr(0, jpos_start);
                //std::string j_part_for_comprison = j.substr(jpos_start, jpos_end-jpos_start+1);
                num++;
                if(i_part_for_comprison==j_part_for_comprison)
                {
                    if(j.find(str)!=std::string::npos)
                    {
                        break;
                    }
                    j.append(str);
                    break;
                }
                if(i_part_for_comprison!=j_part_for_comprison && num >= cleaned_csv_data.size())
                {
                    cleaned_csv_data.emplace_back(i);

                }
            }
        }

    }
}

void CSVEdit::Cleaned_File_Display() const
{
    for(const auto & i : cleaned_csv_data)
    {
        std::cout  << i << std::endl;
    }
}

void CSVEdit::CSV_File_Creator(const std::string& filename)
{
    if (std::ofstream outputFile(filename); outputFile.is_open()) {
        outputFile << "mzname" << ","
            << "common_mz" << ","
            << "LCMS mz" << ","
            << "MALDI mz" << ","
            << "MALDI max_intensity" << ","
            << "fold change" << ","
            << "p_value"  << ","
            <<"Animal" << std::endl;

        outputFile.close();
        std::cout << "Data written to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
}

void CSVEdit::CSV_Writer(const std::string& filename) const
{
    std::ofstream outputFile(filename, std::ios::app);

    if (outputFile.is_open()) {
        for (const auto & i : cleaned_csv_data) {
            outputFile << i << std::endl;
        }
        outputFile.close();
        std::cout << "Data written to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
    outputFile.close();
}

void CSVEdit::CSV_Attribute_Restarter()
{
    csv_data.clear();
    cleaned_csv_data.clear();
}