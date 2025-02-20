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

std::size_t Classifier::GetNearestNeighborIndex(const std::size_t current_testing_index)
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
                                                  all_feature_column_indices_);

    // update nearest distance label
    if ( recent_distance < nearest_distance_so_far )
    {
      nearest_distance_so_far = recent_distance;
      nearest_label_index_so_far = i;
    }
  }

  return nearest_label_index_so_far;
}

double Classifier::CalculateLeaveOneOutValidation()
{
  // arbitrarily large distance to start
  std::size_t nearest_distance_index{};
  int correct_classifications{};

  // for every row in the data set, look for its nearest neighbor
  for ( std::size_t i = 0; i < training_data_set_.size(); ++i )
  {
    nearest_distance_index = GetNearestNeighborIndex(i);

    // if the nearest object is the same class as the current row increment
    if ( training_data_set_.at(i).class_label == training_data_set_.at(nearest_distance_index).class_label )
    {
      ++correct_classifications;
    }
  }

  std::cout << correct_classifications << "\n";

  // make sure to cast to double of all values involved
  return ( (correct_classifications / static_cast<double>(RowData::GetNumberOfLabels(training_data_set_))) * 100.0 );
}

FeatureSetAccuracy Classifier::ForwardSelection()
{
  FeatureSetAccuracy best_feature_set{};




  return best_feature_set;
}
