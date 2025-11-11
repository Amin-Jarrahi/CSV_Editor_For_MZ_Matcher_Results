#include <iostream>

#include "CSV_Editor.h"

int main()
{
    const std::string target_folder_path = "/Users/amin/Desktop/c++/MZ_Matcher/files/Results/";

    CSVEdit Test1;
    Test1.Folder_Parser(target_folder_path);
    Test1.Saving_Path_Allocator();
    for(int i=0; i<Test1.CSV_Files_Path_Lists().size(); i++)
    {
        CSVEdit::CSV_File_Creator(Test1.Saving_Paths_List_Accessor()[i]);
        Test1.CSV_Reader(Test1.CSV_Files_Path_Lists()[i]);
        Test1.CSV_Data_Cleaner();
        //Test1.file_display();
        //Test1.Cleaned_File_Display();
        Test1.CSV_Writer(Test1.Saving_Paths_List_Accessor()[i]);
        Test1.CSV_Attribute_Restarter();
    }

    return 0;
}
