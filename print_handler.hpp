#ifndef PRINT_HANDLER_HPP_
#define PRINT_HANDLER_HPP_

#include <iomanip>
#include <vector>

#include "IEEE_data_parser.hpp"

class PrintHandler
{
  public:
    static void PrintDataSet(const std::vector<RowData>& data_set);
    static void PrintFeaturesTable(const std::vector<std::size_t>& features);

  private:


};

#endif // PRINT_HANDLER_HPP_