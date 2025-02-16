#include "nearest_neighbor_classifier.hpp"

#include "nearest_neighbor_classifier.hpp"

void NearestNeighborClassifier::SetTrainingDataSet(const std::vector<RowData>& training_data_set)
{
  training_data_set_ = training_data_set;
}

std::vector<RowData>& NearestNeighborClassifier::GetTrainingDataSet()
{
  return training_data_set_;
}