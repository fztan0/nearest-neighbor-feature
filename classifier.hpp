#ifndef CLASSIFIER_HPP_
#define CLASSIFIER_HPP_

#include <cmath>
#include <iomanip>
#include <vector>
#include <unordered_set>
#include <algorithm>

#include "IEEE_data_parser.hpp"
#include "chrono_benchmark.hpp"


struct FeatureSetAccuracy
{
  static void PrintFeatureSetAccuracy(const FeatureSetAccuracy &feature_set_accuracy);
  static void PrintFeatureSetAccuracy(const std::vector<std::size_t>& feature_indices, const double& accuracy);

  FeatureSetAccuracy() : accuracy(0.0) {  }

  std::vector<std::size_t> feature_indices;
  double accuracy;
};

class Classifier
{
  public:
  Classifier(const std::vector<RowData>& data_set);

  std::vector<RowData>& GetTrainingDataSet();
  void SetTrainingDataSet(const std::vector<RowData>& training_data_set);

  std::vector<std::size_t> GetAllFeatureColumnIndices() const;
  void SetAllFeatureColumnIndices(const std::vector<std::size_t>& all_feature_indices);

  double GetEuclideanDistance(const RowData& r1, const RowData& r2, const std::vector<std::size_t>& feature_indices);
  std::size_t GetNearestNeighborIndex(const std::size_t current_testing_index, const std::vector<std::size_t>& features_indices);
  double CalculateLeaveOneOutValidation(const std::vector<std::size_t>& feature_indices);

  void ForwardSelection();
  void BackwardElimination();

  private:


    std::vector<RowData> training_data_set_;
    std::vector<std::size_t> all_feature_column_indices_;
};

#endif // CLASSIFIER_HPP_