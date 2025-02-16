#include "print_handler.hpp"

void PrintHandler::PrintDataSet(const std::vector<RowData>& data_set)
{
  // set precision for std::cout to make sure input is accepting 8 precision
  std::cout << std::fixed << std::setprecision(8);

  for ( const auto& row_data : data_set )
  {
    std::cout << row_data.class_label << " ";

    for ( const auto& feature : row_data.feature_values )
    {
      std::cout << feature << " ";
    }

    std::cout << "\n";
  }

  std::cout << "number of features: " << RowData::GetNumberOfFeatures(data_set) << "\n";
  std::cout << "number of labels: " << RowData::GetNumberOfLabels(data_set) << "\n";

  return;
}