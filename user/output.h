#ifndef OUTPUT_H
    #define OUTPUT_H
    #include <string>
    #include <fstream>  // for ofstream

    /**
     * @param string log_file_name
     * @param oftream program_info_msg
     */
    typedef struct __log_info {
        std::string log_file_name;
        std::ofstream program_info_msg;
    } log_info, *plog_info;

#endif