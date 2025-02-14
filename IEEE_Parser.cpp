#include "IEEE_Parser.hpp"

// initialize static member

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
  double input_feature_value;
  RowData row_data;
  std::string string_for_string_stream;
  std::stringstream string_stream;
  std::vector<RowData> data_set;

  while ( std::getline(input_file_stream_, string_for_string_stream) )
  {
    // clear previous row data loading before processing new row
    row_data.feature_values.clear();
    string_stream.clear();
    string_stream.str(string_for_string_stream); // set new string for stream

    string_stream >> input_feature_value; // first get class label value

    row_data.class_label = static_cast<uint>(input_feature_value);

    while ( string_stream >> input_feature_value )
    {
      row_data.feature_values.push_back(input_feature_value);
    }

    data_set.push_back(row_data);

  }

  return data_set;
}