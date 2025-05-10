/***************************************
*  File: file.hpp (file logger)
*
*  Purpose: send logs to a file
*
*  Project: logger
* *************************************/

#pragma once
#include LOGGER_NAMES_INCLUDE
#include LOGGER_DEPENDS_INCLUDE_PATH
#include LOGGER_CODES_INCLUDE_PATH
#include LOGGER_BASE_INCLUDE_PATH
#include LOGGER_LOG_API_INCLUDE_PATH



namespace logger {
	class file {
	public:
		file() = default;
		file(const fs::path& folder,const string& file_name);
		
		// opens file for writing
		codes load();

		// writes a log buffer to out_file
		codes write_buffer(std::vector<log>* buffer);

		// write a single message to out_file
		codes write_message(const string& message);
	protected:
		fs::path m_out_file_path; // full path to out file
		ofstream out_file; // output file stream file object
	};
}