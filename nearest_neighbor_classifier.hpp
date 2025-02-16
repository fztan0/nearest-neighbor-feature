#ifndef NEAREST_NEIGHBOR_CLASSIFIER_HPP_
#define NEAREST_NEIGHBOR_CLASSIFIER_HPP_

#include <vector>

#include "IEEE_data_parser.hpp"

class NearestNeighborClassifier
{
  public:
    NearestNeighborClassifier(const std::vector<RowData>& training_data_set) : training_data_set_(training_data_set) { }
    ~NearestNeighborClassifier() { }

    std::vector<RowData> GetTrainingDataSet() const;
    void SetTrainingDataSet(const std::vector<RowData>& training_data_set);


  private:
    std::vector<RowData> training_data_set_;

};

#endif  // NEAREST_NEIGHBOR_CLASSIFIER_HPP_