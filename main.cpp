#include <iostream>
#include <iomanip> // Include this header for std::setprecision

#include "print_handler.hpp"
#include "nearest_neighbor_classifier.hpp"

// int main(int argc, char* argv[])
int main()
{
  std::string file_path = "input-data/CS170_Small_Data__125.txt";
  IEEEParser parser{};

  if ( parser.SetInputFileStream(file_path) != 0 )
  {
    std::cerr << "bad file path: " << file_path << "\n";
    return -1;
  }

  NearestNeighborClassifier classifier{parser.ParseDataSet()};

  PrintHandler::PrintDataSet(classifier.GetTrainingDataSet());




  return 0;
}
