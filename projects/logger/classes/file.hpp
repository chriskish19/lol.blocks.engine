/***************************************
*  File: file.hpp (file logger)
*
*  Purpose: send logs to a file
*
*
* *************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDS_INCLUDE_PATH

namespace logger {
	class LOGS_API file {
	public:
		file() = default;
		file(const fs::path& folder);


	protected:

	};
}