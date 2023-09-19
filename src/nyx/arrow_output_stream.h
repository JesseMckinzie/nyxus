#pragma once

#ifdef USE_ARROW
//#ifdef USE_ARROW
#include <string>
#include <memory>

#include "output_writers.h"
#include "helpers/helpers.h"

#include <arrow/table.h>

#if __has_include(<filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
  #include <experimental/filesystem> 
  namespace fs = std::experimental::filesystem;
#else
  error "Missing the <filesystem> header."
#endif

/**
 * @brief Class to write to Apache Arrow formats
 * 
 * This class provides methods for writing to the Arrow IPC and Parquet formats.
 * 
 */
class ArrowOutputStream {

private:

    std::string arrow_file_path_ = "";
	std::string parquet_file_path_ = "";
	std::shared_ptr<ApacheArrowWriter> writer_ = nullptr;
	std::string arrow_output_type_ = "";    


public:
    std::shared_ptr<ApacheArrowWriter> create_arrow_file(const std::string& arrow_file_type,
                                                         const std::string& arrow_file_path,
                                                         const std::vector<std::string>& header) {
        

        if(arrow_file_path != "" && !fs::is_directory(arrow_file_path) && !(Nyxus::ends_with_substr(arrow_file_path, ".arrow") || Nyxus::ends_with_substr(arrow_file_path, ".feather") || Nyxus::ends_with_substr(arrow_file_path, ".parquet"))) {
            throw std::invalid_argument("The arrow file path must end in \".arrow\"");
        }

        if (!(arrow_file_type == "ARROW" || arrow_file_type == "ARROWIPC" || arrow_file_type == "PARQUET")) {
            throw std::invalid_argument("The valid file types are ARROW, ARROWIPC, or PARQUET");
        }

        std::string extension = (arrow_file_type == "PARQUET") ? ".parquet" : ".arrow";

        if (arrow_file_path == "") {
            arrow_file_path_ = "NyxusFeatures" + extension;
        } else {
            arrow_file_path_ = arrow_file_path;
        }

        if (fs::is_directory(arrow_file_path)) {
            arrow_file_path_ += "/NyxusFeatures" + extension;
        } 

        writer_ = WriterFactory::create_writer(arrow_file_path_, header);

        return writer_;
    }


    std::shared_ptr<arrow::Table> get_arrow_table(const std::vector<std::string>& header,
                                                      const std::vector<std::string>& string_columns,
                                                      const std::vector<double>& results,
                                                      size_t num_rows) {
                                                        
        /*if (writer_ == nullptr) {
            //writer_ = WriterFactory::create_writer("out.arrow");

            writer_->generate_arrow_table(header, string_columns, results, num_rows);

            return writer_->get_arrow_table();
        }
        */

        auto table = writer_->get_arrow_table();

        return table;

    }

};
#endif