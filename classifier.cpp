#include "classifier.hpp"

Classifier::Classifier(const std::vector<RowData>& data_set)
{
  training_data_set_ = data_set;

  // // initialize all feature indices
  // for ( std::size_t i = 0; i < training_data_set_.size(); ++i )
  // {
  //   for ( std::size_t j = 0; j < training_data_set_.at(i).feature_values.size(); ++j )
  //   {
  //     all_feature_indices_.push_back(j);
  //   }
  // }

  // initialize all feature indices
  for ( std::size_t i = 0; i < training_data_set_.at(0).feature_values.size(); ++i )
  {
    all_feature_column_indices_.push_back(i);
  }

}


std::vector<RowData> &Classifier::GetTrainingDataSet()
{
  return training_data_set_;
}

void Classifier::SetTrainingDataSet(const std::vector<RowData>& training_data_set)
{
  training_data_set_ = training_data_set;
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

  return sqrt(euclidean_distance);
}

double Classifier::CalculateNearestNeighborLeaveOneOutCrossValidation()
{
  // arbitrarily large distance to start
  double nearest_distance_so_far = std::numeric_limits<double>::max();
  std::size_t nearest_distance_index{};
  int correct_classifications{};
  double recent_distance{};

  // for every row in the data set, look for its nearest neighbor
  for ( std::size_t i = 0; i < training_data_set_.size(); ++i )
  {
    for ( std::size_t j = 0; j < training_data_set_.size(); ++j )
    {
      // skip current leave-one-out row
      if ( i == j )
        continue;

      // calculate the distance between two objects through all of its indices
      recent_distance = GetEuclideanDistance(training_data_set_.at(i), training_data_set_.at(j), all_feature_column_indices_);

      // update the nearest distance
      if (recent_distance < nearest_distance_so_far)
      {
        nearest_distance_so_far = recent_distance;
        nearest_distance_index = j;
      }
    }

    // by here, we've found the nearest object TO the current row

    // if the nearest object is the same class as the current row increment
    if (training_data_set_.at(i).class_label == training_data_set_.at(nearest_distance_index).class_label)
    {
      ++correct_classifications;
    }

    nearest_distance_so_far = std::numeric_limits<double>::max();
  }

  // std::cout << correct_classifications << "\n";

  // make sure to cast to double of all values involved
  return ( (correct_classifications / static_cast<double>(RowData::GetNumberOfLabels(training_data_set_))) * 100.0 );
}
