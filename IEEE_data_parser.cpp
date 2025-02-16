#include "IEEE_data_parser.hpp"

// initialize static member

int RowData::GetNumberOfFeatures(const std::vector<RowData>& data_set)
{
  if ( data_set.empty() )
  {
    std::cout << "data_set empty\n";

    return -1;
  }

  return static_cast<int>(data_set[0].feature_values.size());
}

int RowData::GetNumberOfLabels(const std::vector<RowData>& data_set)
{
  if ( data_set.empty() )
  {
    std::cout << "data_set empty\n";

    return -1;
  }

  return static_cast<int>(data_set.size());
}

std::ifstream& IEEEParser::GetInputFileStream()
{
  return input_file_stream_;
}

int IEEEParser::SetInputFileStream(const std::string& file_path)
{
  input_file_stream_.open(file_path);

  if ( !input_file_stream_.is_open() )
  {
    return -1;
  }

  return 0;
}

std::vector<RowData> IEEEParser::ParseDataSet()
{
  double IEEE_input_value;
  RowData row_data;

  std::string string_for_string_stream;
  std::stringstream string_stream;

  std::vector<RowData> data_set;

  while ( std::getline(input_file_stream_, string_for_string_stream) )
  {
    string_stream.str(string_for_string_stream);

    string_stream >> IEEE_input_value;
    row_data.class_label = static_cast<int>(IEEE_input_value);

    while (string_stream >> IEEE_input_value)
    {
      row_data.feature_values.push_back(IEEE_input_value);
    }

    data_set.push_back(row_data);

    string_stream.clear();
    row_data.feature_values.clear();
  }

  return data_set;
}