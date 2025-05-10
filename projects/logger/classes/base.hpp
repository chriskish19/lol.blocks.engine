/***************************************
*  File: base.hpp (base logger)
*
*  Purpose: handles underlying log system
*
*  Project: logger
* *************************************/

#pragma once
#include LOGGER_NAMES_INCLUDE
#include LOGGER_DEPENDS_INCLUDE_PATH
#include LOGGER_LOG_API_INCLUDE_PATH


#define LOGGER_LINES 1000
#define LOG_LENGTH 512
#define LOGGER_FONT_SIZE 14

namespace logger {
	struct log {
		log() {
			message->reserve(LOG_LENGTH);
		}

		string* message = new string;
		RECT* window_position = new RECT;

		~log() {
			if (message != nullptr) {
				delete message;
				message = nullptr;
			}

			if (window_position != nullptr) {
				delete window_position;
				window_position = nullptr;
			}
		}
	};


	class LOGS_API base {
	public:
		// nol : number of logs
		base(std::size_t nol);
		~base();

		// log a message
		void set_message(const string& message);

		// get index position in logs vec
		std::size_t get_index() { return m_index; }

		// get logs_V pointer
		std::vector<log*>* get_buffer() { return m_logs_v; }
	protected:
		std::vector<log*>* m_logs_v = nullptr;

		std::size_t m_index = 0;
	};
}