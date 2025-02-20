#include <iostream>
#include <iomanip> // Include this header for std::setprecision

#include "print_handler.hpp"
#include "classifier.hpp"
#include "chrono_benchmark.hpp"


/*

  SMALL: 46
  BIG: 81

*/

int main()
{
  IEEEParser parser;
  std::string file_path;

  std::cout << "Welcome to Jeff Tan's Feature Selection Algorithm.\nType in the file name to test:\n><>";
  std::cin >> file_path;
  std::cout << "\n";

  if ( parser.SetInputFileStream(file_path) != 0 )
  {
    std::cerr << "bad file path: " << file_path << "\n";
    return -1;
  }


  int algorithm_choice;
  std::cout << "Type the number of the algorithm you want to use:\n    1. Forward Selection\n    2. Backward Elimination\n><>";
  std::cin >> algorithm_choice;
  std::cout << "\n";

  Classifier classifier{parser.ParseDataSet()};
  switch (algorithm_choice)
  {
    case 1:
      std::cout << "This dataset has " << classifier.GetTrainingDataSet()[0].feature_values.size() << " features (not including the class label attribute), with " << classifier.GetTrainingDataSet().size() << " instances.\n\n";
      std::cout << "Running nearest neighbor with all " << classifier.GetTrainingDataSet()[0].feature_values.size() << " features using \"leaving-one-out\" evaluation. I get an accuracy of " << classifier.CalculateLeaveOneOutValidation(classifier.GetAllFeatureColumnIndices()) << ".\n\n";
      std::cout << "Beginning search...\n\n";


      classifier.ForwardSelection();
      break;

    case 2:
      std::cout << "This dataset has " << classifier.GetTrainingDataSet()[0].feature_values.size() << " features (not including the class label attribute), with " << classifier.GetTrainingDataSet().size() << " instances.\n";


      classifier.BackwardElimination();
      break;

    default:
      std::cerr << "Invalid choice. Please select 1 or 2.\n";
      return -1;
  }




  std::cout << std::fixed << std::setprecision(2);
  std::cout << "K-Fold on entire feature index, the accuracy is: " << classifier.CalculateLeaveOneOutValidation(classifier.GetAllFeatureColumnIndices()) << "\n";




  // classifier.BackwardElimination();


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