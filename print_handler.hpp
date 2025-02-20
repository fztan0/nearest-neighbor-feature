#ifndef PRINT_HANDLER_HPP_
#define PRINT_HANDLER_HPP_

#include <iomanip>
#include <vector>

#include "IEEE_data_parser.hpp"
#include "classifier.hpp"

class PrintHandler
{
  public:
    static void PrintDataSet(const std::vector<RowData>& data_set);
    static void PrintFeaturesTable(const std::vector<std::size_t>& features);

    static void PrintFeatureSetAccuracy(const FeatureSetAccuracy& feature_set_accuracy);

  private:


};

#endif // PRINT_HANDLER_HPP_