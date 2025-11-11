//
// Created by Amin on 8/22/24.
//

#ifndef CSV_EDITOR_H
#define CSV_EDITOR_H
#include <fstream>
#include <string>
#include <vector>


class CSVEdit {
    std::vector<std::string> target_csv_files{};
    std::vector<std::string> paths_for_saving_data{};
    std::vector<std::string> csv_data;
    std::vector<std::string> cleaned_csv_data;


public:
    void Folder_Parser(const std::string& );
    [[nodiscard]] std::vector<std::string>& CSV_Files_Path_Lists() {return target_csv_files;}
    [[nodiscard]] std::vector<std::string>& Saving_Paths_List_Accessor() {return paths_for_saving_data;}
    int CSV_Reader(const std::string&);
    void File_Display() const;
    void CSV_Data_Cleaner();
    void Saving_Path_Allocator();
    void Cleaned_File_Display() const;
    void CSV_Attribute_Restarter();
    static void CSV_File_Creator(const std::string& );
    void CSV_Writer( const std::string& ) const;

};



#endif //CSV_EDITOR_H
