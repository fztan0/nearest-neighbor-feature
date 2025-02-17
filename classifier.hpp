#ifndef CLASSIFIER_HPP_
#define CLASSIFIER_HPP_

#include <vector>
#include <cmath>

#include "IEEE_data_parser.hpp"

class Classifier
{
  public:
    Classifier(const std::vector<RowData>& data_set);

    std::vector<RowData>& GetTrainingDataSet();
    void SetTrainingDataSet(const std::vector<RowData>& training_data_set);

    std::vector<std::size_t> GetAllFeatureColumnIndices() const;
    void SetAllFeatureColumnIndices(const std::vector<std::size_t>& all_feature_indices);

    std::vector<std::size_t> GetCustomFeatureIndices() const;
    void SetCustomFeatureIndices(const std::vector<std::size_t>& custom_feature_indices);

    double GetEuclideanDistance(const RowData& r1, const RowData& r2, const std::vector<std::size_t>& feature_indices);


    int GetNearestNeighborIndex(const RowData& test_row);
    double LeaveOneOutCrossValidation();

    double CalculateNearestNeighborLeaveOneOutCrossValidation();


    void NearestNeighborClassifier();


  private:
    std::vector<RowData> training_data_set_;
    std::vector<std::size_t> all_feature_column_indices_;
    std::vector<std::size_t> custom_feature_indices_;
};

#endif // CLASSIFIER_HPP_