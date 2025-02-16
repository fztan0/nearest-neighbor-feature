#include "classifier.hpp"

void Classifier::SetTrainingDataSet(const std::vector<RowData>& training_data_set)
{
  training_data_set_ = training_data_set;
}

std::vector<RowData>& Classifier::GetTrainingDataSet()
{
  return training_data_set_;
}


/*
  6__MachineLearning001.pdf
  page 84
*/
double Classifier::GetEuclideanDistance(const RowData &r1, const RowData &r2, const std::vector<std::size_t> &feature_indices)
{
  double dimension_difference = 0.0;
  double euclidean_distance = 0.0;

  // sum every dimensional space of the wanted feature space
  for ( std::size_t i = 0; i < feature_indices.size(); ++i )
  {
    dimension_difference = pow(r1.feature_values.at(feature_indices.at(i)) - r2.feature_values.at(feature_indices.at(i)), 2);

    euclidean_distance += dimension_difference;
  }

  return sqrt(euclidean_distance);
}



