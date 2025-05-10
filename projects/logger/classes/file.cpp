
/***************************************
*  File: file.cpp
*
*  Purpose: file.hpp definitions
*
*  Project: logger
* *************************************/

#include LOGGER_NAMES_INCLUDE
#include LOGGER_FILE_INCLUDE_PATH

logger::file::file(const fs::path& folder, const string& file_name)
{
	m_out_file_path = folder / file_name;
}

logger::codes logger::file::load()
{
	out_file.open(m_out_file_path, std::ios::out | std::ios::trunc);

	if (!out_file.is_open()) {
		// Handle the error if the file couldn't be opened
		std::cerr << "Failed to open file: " << m_out_file_path << std::endl;
		return codes::file_open_error;
	}

	return codes::success;
}

logger::codes logger::file::write_buffer(std::vector<log>* buffer)
{
	
	string header = time_stamped(ROS("FULL BUFFER DUMP!"));

	try {
		out_file << header;
	}
	catch (const std::ios_base::failure& e) {
		// Handle the write error
		std::cerr << "Write error: " << e.what() << std::endl;
		return codes::write_to_file_error;
	}
	
	for (auto& log : *buffer) {
		auto& message = *log.message;
		
		try {
			out_file << message;
		}
		catch (const std::ios_base::failure& e) {
			// Handle the write error
			std::cerr << "Write error: " << e.what() << std::endl;
			return codes::write_to_file_error;
		}
	}
	
	string footer = time_stamped(ROS("END OF BUFFER DUMP!"));

	try {
		out_file << footer;
	}
	catch (const std::ios_base::failure& e) {
		// Handle the write error
		std::cerr << "Write error: " << e.what() << std::endl;
		return codes::write_to_file_error;
	}


	return codes::success;
}

logger::codes logger::file::write_message(const string& message)
{
	try {
		out_file << message;
	}
	catch (const std::ios_base::failure& e) {
		// Handle the write error
		std::cerr << "Write error: " << e.what() << std::endl;
		return codes::write_to_file_error;
	}
	return codes::success;
}
