#include <iostream>
#include <iomanip> // Include this header for std::setprecision

#include "print_handler.hpp"
#include "classifier.hpp"
#include "chrono_benchmark.hpp"


/* DATASET ASSIGNED

SMALL: 46
BIG: 81

*/

int main()
{
  FeatureSetAccuracy best_features_from_first_run;
  IEEEParser parser;
  int algorithm_choice;
  int rerun_choice;
  std::string file_path;
  std::vector<std::pair<std::size_t, FeatureSetAccuracy>> remove_one_best_results;

  std::cout << "Welcome to Jeff Tan's Feature Selection Algorithm.\nType in the file name to test:\n><>";
  std::cin >> file_path;
  std::cout << "\n";

  if ( parser.SetInputFileStream(file_path) != 0 )
  {
    std::cerr << "bad file path: " << file_path << "\n";
    return -1;
  }

  Classifier classifier{parser.ParseDataSet()};
  std::vector<std::size_t> full_indices_copy = classifier.GetAllFeatureColumnIndices();



  std::cout << "Type the number of the algorithm you want to use:\n    1. Forward Selection\n    2. Backward Elimination\n><>";
  std::cin >> algorithm_choice;
  std::cout << "\n";

  switch (algorithm_choice)
  {
    case 1:
      std::cout << "This dataset has " << classifier.GetTrainingDataSet()[0].feature_values.size() << " features (not including the class label attribute), with " << classifier.GetTrainingDataSet().size() << " instances.\n\n";
      std::cout << "Running nearest neighbor with all " << classifier.GetTrainingDataSet()[0].feature_values.size() << " features using \"leaving-one-out\" evaluation, I get an accuracy of " << classifier.CalculateLeaveOneOutValidation(classifier.GetAllFeatureColumnIndices()) << "%.\n\n";
      std::cout << "Beginning search...\n\n";

      best_features_from_first_run = classifier.ForwardSelection();

      break;

    case 2:
      std::cout << "This dataset has " << classifier.GetTrainingDataSet()[0].feature_values.size() << " features (not including the class label attribute), with " << classifier.GetTrainingDataSet().size() << " instances.\n\n";
      std::cout << "Running nearest neighbor with all " << classifier.GetTrainingDataSet()[0].feature_values.size() << " features using \"leaving-one-out\" evaluation, I get an accuracy of " << classifier.CalculateLeaveOneOutValidation(classifier.GetAllFeatureColumnIndices()) << "%.\n\n";
      std::cout << "Beginning search...\n\n";

      best_features_from_first_run = classifier.BackwardElimination();

      break;

    default:
      std::cerr << "Invalid choice. Please select 1 or 2.\n";
      return -1;
  }

  if (algorithm_choice == 1 || algorithm_choice == 2)
  {
    std::cout << "Type the number of operation you want to use next:\n    1. Remove Each Best and Restore\n    2. Find Weaker Features\n    3. Find Irrelevant Feature\n    4. Exit\n><>";
    std::cin >> rerun_choice;
    std::cout << "\n";


    switch (rerun_choice)
    {
      /*
      IDEA: Remove each feature in best set from total set and rerun individually for each removal
      */
      case 1:

        for ( auto& feature_index : best_features_from_first_run.feature_indices )
        {
          std::cout << "Removing " << feature_index << " and running selected algorithm...";

          classifier.RemoveFeatureIndices(std::vector<size_t>{feature_index});

          switch (algorithm_choice)
          {
            case 1:
              remove_one_best_results.push_back(std::pair<std::size_t, FeatureSetAccuracy>(feature_index, classifier.ForwardSelection()));
              break;
            case 2:
              remove_one_best_results.push_back(std::pair<std::size_t, FeatureSetAccuracy>(feature_index, classifier.BackwardElimination()));
              break;
            default:
              std::cout << "BAD CHOICE\n";
              return -1;
          }


          // restore the original feature set for the next iteration
          classifier.SetAllFeatureColumnIndices(full_indices_copy);
        }

        std::cout << "Results after removing each and restoring from the best set:\n";
        for (const auto& result : remove_one_best_results)
        {
          std::cout << "Feature removed: " << result.first + 1 << " -> Set and Accuracy: ";
          FeatureSetAccuracy::PrintFeatureSetAccuracy(result.second);
        }

        break;

      case 2:
        FeatureSetAccuracy::PrintFeatureSetAccuracy(best_features_from_first_run);
        classifier.RemoveFeatureIndices(best_features_from_first_run.feature_indices);

        std::cout << "Rerunning without best previous features...\n";

        switch (algorithm_choice)
        {
          case 1:
            classifier.ForwardSelection();
            break;
          case 2:
            classifier.BackwardElimination();
            break;
          default:
            std::cout << "BAD CHOICE\n";
            return -1;
        }
        break;

      case 3:
        std::cout << "Exiting...\n";
        break;

      default:
        std::cout << "Exiting...\n";
        break;
    }
  }




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