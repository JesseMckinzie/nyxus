#include <arrow/api.h>
#include <arrow/io/api.h>
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>
#include <parquet/exception.h>

#include <vector>
#include <string>

#include <iostream>

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
        fields.push_back(arrow::field(header[2], arrow::int32()));

        for (int i = 3; i < header.size(); ++i) {
            fields.push_back(arrow::field(header[i], arrow::float64()));
        }

        std::cout << "number of schema fields: " << fields.size() << std::endl;

        auto schema = arrow::schema(fields);

        arrow::StringBuilder string_builder_0;

        PARQUET_THROW_NOT_OK(string_builder_0.AppendValues(
            std::vector<std::string>(string_columns.begin(), string_columns.begin() + number_of_rows)
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


        // add labels 
        arrow::Int32Builder labels_builder;

        std::vector<int> temp_vec;
        int num_columns = numeric_columns.size() / number_of_rows;
        for (int i = 0; i < numeric_columns.size(); i+= num_columns ) {
            temp_vec.push_back(numeric_columns[i]);
        }

        for (auto& v: temp_vec) {
            std::cout << v << ", ";
        }
        std::cout << std::endl;
        std::cout << std::endl;

        PARQUET_THROW_NOT_OK(labels_builder.AppendValues(
            temp_vec
        ));

        //PARQUET_THROW_NOT_OK(labels_builder.AppendValues(
        //    std::vector<int> (numeric_columns.begin() , numeric_columns.begin() + number_of_rows)
        //));
        
        std::shared_ptr<arrow::Array> array_2;

        PARQUET_THROW_NOT_OK(labels_builder.Finish(&array_2));
        arrays.push_back(array_2);

        
        int idx;
        for (int i = 1; i < num_columns; ++i) {
            arrow::DoubleBuilder builder;

            std::vector<double> temp;
        
            for (int j = 0; j < number_of_rows; ++j ) {
                temp.push_back(numeric_columns[i + (j*num_columns)]);
            }
        
            PARQUET_THROW_NOT_OK(builder.AppendValues(
                temp
            ));
            
            std::shared_ptr<arrow::Array> temp_array;

            PARQUET_THROW_NOT_OK(builder.Finish(&temp_array));
            arrays.push_back(temp_array);
        }

        std::cout << "number of fields in array: " << arrays.size() << std::endl;
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