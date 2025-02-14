#ifndef IEEE_PARSER_HPP_
#define IEEE_PARSER_HPP_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct RowData
{
  uint class_label;
  std::vector<double> feature_values;

  static int GetNumberOfFeatures(const std::vector<RowData>& data_set)
  {
    if ( data_set.empty() )
    {
      std::cout << "data_set empty\n";

      return -1;
    }

    return static_cast<int>(data_set[0].feature_values.size());
  }

  static int GetNumberOfLabels(const std::vector<RowData>& data_set)
  {
    if ( data_set.empty() )
    {
      std::cout << "data_set empty\n";

      return -1;
    }

    return static_cast<int>(data_set.size());
  }

};

class IEEEParser
{
  public:
    IEEEParser() { }
    ~IEEEParser() { }

    std::ifstream& GetInputFileStream();
    int SetInputFileStream(const std::string& file_path);
    std::vector<RowData> ParseDataSet();

  private:
    std::ifstream input_file_stream_;

};

#endif  // IEEE_PARSER_HPP_
