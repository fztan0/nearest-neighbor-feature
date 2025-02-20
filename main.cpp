#include <iostream>
#include <iomanip> // Include this header for std::setprecision

#include "print_handler.hpp"
#include "classifier.hpp"

// int main(int argc, char* argv[])
int main()
{
  // CHANGE THIS  TO CLI ARG INPUT AFTER FINISHING
  std::string file_path = "input-data/CS170_Small_Data__125.txt";

  IEEEParser parser{};

  if ( parser.SetInputFileStream(file_path) != 0 )
  {
    std::cerr << "bad file path: " << file_path << "\n";
    return -1;
  }

  Classifier classifier{parser.ParseDataSet()};

  PrintHandler::PrintDataSet(classifier.GetTrainingDataSet());

  // PrintHandler::PrintFeaturesTable(classifier.GetAllFeatureColumnIndices());

  std::cout << "K-Fold: " << classifier.CalculateLeaveOneOutValidation() << "\n";




  // std::cout << "Accessing feature_values[492]:\n";
  // for ( const auto& feature : classifier.GetTrainingDataSet()[492].feature_values )
  // {
  //   std::cout << feature << " ";
  // }
  // std::cout << "\n";

  // RowData test1;
  // RowData test2;

  // test1.feature_values = {-1.5808788, 0.6725764, 0.9258087};
  // test2.feature_values = {-0.9510147, -0.5513586, -0.0666014};

  // std::cout << classifier.GetEuclideanDistance( test1, test2, {1, 2} ) << "\n";


  return 0;
}