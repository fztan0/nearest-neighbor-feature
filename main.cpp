#include <iostream>
#include <iomanip> // Include this header for std::setprecision

#include "IEEE_Parser.hpp"

int main()
{
  std::string file_path = "input-data/CS170_Large_Data__42.txt";
  IEEEParser parser;
  std::vector<RowData> data_set;

  if ( parser.SetInputFileStream(file_path) != 0 )
  {
    std::cerr << "bad file path: " << file_path << "\n";
    return -1;
  }

  data_set = parser.ParseDataSet();

  // set precision for std::cout to make sure input is accepting 8 precision
  std::cout << std::fixed << std::setprecision(8);

  for ( const auto& rowdata : data_set )
  {
    std::cout << rowdata.class_label << " ";

    for ( const auto& feature : rowdata.feature_values )
    {
      std::cout << feature << " ";
    }

    std::cout << "\n";
  }

  std::cout << "number of features: " << RowData::GetNumberOfFeatures(data_set) << "\n";
  std::cout << "number of features: " << RowData::GetNumberOfLabels(data_set) << "\n";


  return 0;
}
