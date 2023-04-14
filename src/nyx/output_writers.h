#include <arrow/api.h>
#include <arrow/io/api.h>
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>
#include <parquet/exception.h>

#include <vector>
#include <string>

class OutputWriter {
private:


public:

    std::shared_ptr<arrow::Table> generate_arrow_table(const std::vector<std::string>& header,
                                                       const std::vector<std::string>& string_columns,
                                                       const std::vector<double>& numeric_columns,
                                                       int number_of_rows) {

        std::vector<std::shared_ptr<arrow::Field>> fields;

        fields.push_back(arrow::field(header[0], arrow::utf8()));
        fields.push_back(arrow::field(header[1], arrow::utf8()));

        for (int i = 2; i < header.size(); ++i) {
            fields.push_back(arrow::field(header[i], arrow::float32()));
        }

        auto schema = arrow::schema(fields);

        arrow::StringBuilder string_builder_0;

        PARQUET_THROW_NOT_OK(string_builder_0.AppendValues(
            std::vector<std::string>(string_columns.begin(), string_columns.begin() + number_of_rows - 1)
        ));
        
        arrow::StringBuilder string_builder_1;

        PARQUET_THROW_NOT_OK(string_builder_1.AppendValues(
            std::vector<std::string>(string_columns.begin() + number_of_rows, string_columns.end())
        ));

        //std::shared_ptr<arrow::Array> array0, array1;
        std::shared_ptr<arrow::Array> array_0, array_1;
        
        PARQUET_THROW_NOT_OK(string_builder_0.Finish(&array_0));
        PARQUET_THROW_NOT_OK(string_builder_1.Finish(&array_1));

        std::vector<std::shared_ptr<arrow::Array>> arrays;

        arrays.push_back(array_0);
        arrays.push_back(array_1);

        int num_columns = numeric_columns.size() / number_of_rows;
        int idx;
        for (int i = 0; i < num_columns-1; ++i) {
            arrow::DoubleBuilder builder;

            PARQUET_THROW_NOT_OK(builder.AppendValues(
                std::vector<double> (numeric_columns.begin() + number_of_rows * i, numeric_columns.begin() + (number_of_rows * (i+1)) -1 )
            ));
            
            std::shared_ptr<arrow::Array> temp_array;

            PARQUET_THROW_NOT_OK(builder.Finish(&temp_array));
            arrays.push_back(temp_array);
        }

        return arrow::Table::Make(schema, arrays);
    }

    int write_to_parquet(const std::vector<std::string>& header,
                        const std::vector<std::string>& string_columns,
                        const std::vector<double>& numeric_columns,
                        int number_of_rows,
                        const std::string& output_path = "parquet-arrow-example.parquet"){
        
        auto table = generate_arrow_table(header, string_columns, numeric_columns, number_of_rows);

        std::shared_ptr<arrow::io::FileOutputStream> outfile;

        PARQUET_ASSIGN_OR_THROW(
            outfile, arrow::io::FileOutputStream::Open(output_path));

        PARQUET_THROW_NOT_OK(
            parquet::arrow::WriteTable(*table, arrow::default_memory_pool(), outfile, 3));
    }
};