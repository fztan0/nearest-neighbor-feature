#include "classifier.hpp"

Classifier::Classifier(const std::vector<RowData>& input_data_set)
{
  training_data_set_ = input_data_set;

  // initialize total number of feature column indices
  for ( std::size_t i = 0; i < training_data_set_.at(0).feature_values.size(); ++i )
  {
    all_feature_column_indices_.push_back(i);
  }

}


std::vector<RowData>& Classifier::GetTrainingDataSet()
{
  return training_data_set_;
}

void Classifier::SetTrainingDataSet(const std::vector<RowData>& data_set)
{
  training_data_set_ = data_set;
}

std::vector<std::size_t> Classifier::GetAllFeatureColumnIndices() const
{
  return all_feature_column_indices_;
}

void Classifier::SetAllFeatureColumnIndices(const std::vector<std::size_t> &all_feature_indices)
{
  all_feature_column_indices_ = all_feature_indices;
}


double Classifier::GetDefaultRate()
{
  std::unordered_map<int, int> label_count;

  for (const auto& row : training_data_set_)
  {
    ++label_count[row.class_label];
  }

  int max_count = 0;

  for (const auto& label : label_count)
  {
    if (label.second > max_count)
    {
      max_count = label.second;
    }
  }

  return static_cast<double>(max_count) / static_cast<double>(training_data_set_.size());
}

/*
  6__MachineLearning001.pdf
  page 84
*/
double Classifier::GetEuclideanDistance(const RowData &r1, const RowData &r2, const std::vector<std::size_t> &feature_indices)
{
  double dimension_difference{};
  double euclidean_distance{};

  // sum every dimensional space of the wanted feature space
  for ( std::size_t i = 0; i < feature_indices.size(); ++i )
  {
    dimension_difference = pow(r1.feature_values.at(feature_indices.at(i)) - r2.feature_values.at(feature_indices.at(i)), 2);

    euclidean_distance += dimension_difference;
  }

  return ( sqrt(euclidean_distance) );
}

std::size_t Classifier::GetNearestNeighborIndex(const std::size_t current_testing_index, const std::vector<std::size_t>& features_indices)
{
  double nearest_distance_so_far = std::numeric_limits<double>::max();
  std::size_t nearest_label_index_so_far{};

  for ( std::size_t i = 0; i < training_data_set_.size(); ++i )
  {
    // skip current testing row
    if ( current_testing_index == i )
    {
      continue;
    }

    // calculate the distance between two objects through all of its indices
    double recent_distance = GetEuclideanDistance(training_data_set_.at(current_testing_index),
                                                  training_data_set_.at(i),
                                                  features_indices);

    // update nearest distance label
    if ( recent_distance < nearest_distance_so_far )
    {
      nearest_distance_so_far = recent_distance;
      nearest_label_index_so_far = i;
    }
  }

  return nearest_label_index_so_far;
}

double Classifier::CalculateLeaveOneOutValidation(const std::vector<std::size_t>& feature_indices)
{
  // arbitrarily large distance to start
  std::size_t nearest_distance_index{};
  int correct_classifications{};

  // for every row in the data set, look for its nearest neighbor
  for ( std::size_t i = 0; i < training_data_set_.size(); ++i )
  {
    nearest_distance_index = GetNearestNeighborIndex(i, feature_indices);

    // if the nearest object is the same class as the current row increment
    if ( training_data_set_.at(i).class_label == training_data_set_.at(nearest_distance_index).class_label )
    {
      ++correct_classifications;
    }
  }

  // std::cout << correct_classifications << "\n";

  // make sure to cast to double of all values involved
  return ( (correct_classifications / static_cast<double>(RowData::GetNumberOfLabels(training_data_set_))) * 100.0 );
}

void FeatureSetAccuracy::PrintFeatureSetAccuracy(const FeatureSetAccuracy &feature_set_accuracy)
{
  std::cout << "{ ";

  for ( const auto& feature_index : feature_set_accuracy.feature_indices )
  {
    std::cout << feature_index + 1 << " ";
  }

  std::cout << "} ";

  std::cout << std::fixed << std::setprecision(1);
  std::cout << "with an accuracy: " << feature_set_accuracy.accuracy << "%\n\n";

  return;
}

void FeatureSetAccuracy::PrintFeatureSetAccuracy(const std::vector<std::size_t> &feature_indices, const double &accuracy)
{
  std::cout << "set: { ";

  for ( const auto& feature_index : feature_indices )
  {
    std::cout << feature_index + 1 << " ";
  }

  std::cout << "} ";

  std::cout << std::fixed << std::setprecision(1);
  std::cout << "     ACC: " << accuracy << "\n";


  return;
}

FeatureSetAccuracy Classifier::ForwardSelection()
{
  FeatureSetAccuracy best_feature_set;
  std::unordered_set<std::size_t> selected_features; // keep track of already selected
  std::vector<std::size_t> current_feature_set;

  ChronoTimer timer{};

  // go through every feature index pass
  for ( std::size_t i = 0; i < all_feature_column_indices_.size(); ++i )
  {
    std::size_t feature_to_add = std::numeric_limits<std::size_t>::max();
    double best_accuracy = 0.0;

    // check potential features to add
    for ( std::size_t j = 0; j < all_feature_column_indices_.size(); ++j )
    {
      // skip if the feature already selected before
      if ( selected_features.count(all_feature_column_indices_[j]) > 0 )
      {
        continue;
      }

      // duplicate for checking
      std::vector<std::size_t> checking_feature_set = current_feature_set;


      // post-processing functions conflict with direct index value adding, do value at index instead
      checking_feature_set.push_back(all_feature_column_indices_[j]);

      double accuracy = CalculateLeaveOneOutValidation(checking_feature_set);

      std::cout << "    Using feature(s) { ";
      for ( auto& k : checking_feature_set )
      {
        std::cout << k + 1 << " "; // professor uses matlab, account for off by 1
      }

      std::cout << std::fixed << std::setprecision(1);
      std::cout << "} accuracy is: " << accuracy << "%\n";


      // every time a feature increases accuracy, set as new feature to add
      if ( accuracy > best_accuracy )
      {
        best_accuracy = accuracy;
        feature_to_add = all_feature_column_indices_[j];
      }
    }

    // by here we have best accuracy after internal loop scan

    current_feature_set.push_back(feature_to_add);
    selected_features.insert(feature_to_add);

    if ( best_accuracy > best_feature_set.accuracy )
    {
      best_feature_set.feature_indices = current_feature_set;
      best_feature_set.accuracy = best_accuracy;
    }

    // warn about decreasing instead
    if ( best_accuracy < best_feature_set.accuracy )
    {
      std::cout << "\n[WARNING] Accuracy has decreased! Continuing search in case of local maxima.";
    }

    std::cout << "\nFeature set { ";

    for ( auto& k : current_feature_set )
    {
      std::cout << k + 1 << " ";
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "} was best, accuracy is: " << best_accuracy << "%\n\n";

    // FeatureSetAccuracy::PrintFeatureSetAccuracy(current_feature_set, best_accuracy);
  }

  std::cout << "Finished search! The best subset is: ";
  FeatureSetAccuracy::PrintFeatureSetAccuracy(best_feature_set);

  return best_feature_set;
}


FeatureSetAccuracy Classifier::BackwardElimination()
{
  FeatureSetAccuracy best_feature_set;
  std::unordered_set<std::size_t> selected_features(all_feature_column_indices_.begin(), all_feature_column_indices_.end());
  std::vector<std::size_t> current_feature_set{ all_feature_column_indices_ };

  // init full feature list
  best_feature_set.feature_indices = current_feature_set;
  best_feature_set.accuracy = CalculateLeaveOneOutValidation(current_feature_set);

  std::cout << "Initial full feature set: { ";
  for (const auto& feature : current_feature_set)
  {
    std::cout << feature + 1 << " ";
  }
  std::cout << "} with accuracy: " << best_feature_set.accuracy << "%\n";

  ChronoTimer timer{};

  // going backwards, careful with empty index
  for ( std::size_t i = 0; i < all_feature_column_indices_.size() - 1; ++i )
  {
    std::size_t feature_to_remove = std::numeric_limits<std::size_t>::max();
    double best_accuracy = 0.0;

    // check each feature for removal
    for ( std::size_t j : selected_features )
    {
      std::vector<std::size_t> checking_feature_set = current_feature_set;
      checking_feature_set.erase( std::remove(checking_feature_set.begin(), checking_feature_set.end(), j), checking_feature_set.end() ); // remove what we are looking for instead of what is at the total

      double accuracy = CalculateLeaveOneOutValidation(checking_feature_set);

      std::cout << "    Using feature(s) { ";
      for ( auto& k : checking_feature_set )
      {
        std::cout << k + 1 << " ";
      }

      std::cout << std::fixed << std::setprecision(1);
      std::cout << "} accuracy is: " << accuracy << "%\n";

      if ( accuracy > best_accuracy )
      {
        best_accuracy = accuracy;
        feature_to_remove = all_feature_column_indices_[j];
      }
    }

    current_feature_set.erase( std::remove(current_feature_set.begin(), current_feature_set.end(), feature_to_remove), current_feature_set.end() );
    selected_features.erase(feature_to_remove);

    if ( best_accuracy > best_feature_set.accuracy )
    {
      best_feature_set.feature_indices = current_feature_set;
      best_feature_set.accuracy = best_accuracy;
    }

    if ( best_accuracy < best_feature_set.accuracy )
    {
      std::cout << "\n[WARNING] Accuracy has decreased! Continuing search in case of local maxima.";
    }

    std::cout << "\nFeature set { ";

    for ( auto& k : current_feature_set )
    {
      std::cout << k + 1 << " ";
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "} was best, accuracy is: " << best_accuracy << "%\n\n";

    // avoid removing empty
    if ( current_feature_set.size() <= 1 )
    {
      break;
    }
  }

  std::cout << "Finished search! The best subset is: ";
  FeatureSetAccuracy::PrintFeatureSetAccuracy(best_feature_set);

  return best_feature_set;
}

void Classifier::RemoveFeatureIndices(std::vector<std::size_t> feature_indices)
{
  std::cout << "Removing the best features ";

  std::cout << "{ ";
  for (const auto& index : feature_indices)
  {
    std::cout << index + 1 << " ";
  }
  std::cout << "} ";

  std::cout << "from indexed dataset...\n\n";

  std::cout << "Current feature indices before removal: { ";
  for (const auto& index : all_feature_column_indices_)
  {
    std::cout << index + 1 << " ";
  }
  std::cout << "}\n\n";


  for ( auto& feature_index : feature_indices )
  {
    all_feature_column_indices_.erase( std::remove(all_feature_column_indices_.begin(), all_feature_column_indices_.end(), feature_index), all_feature_column_indices_.end() );
  }

  std::cout << "Current feature indices after removal: { ";
  for (const auto& index : all_feature_column_indices_)
  {
    std::cout << index + 1 << " ";
  }
  std::cout << "}\n\n";
}