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


#define LOGGER_LINES 1000
#define LOG_LENGTH 512
#define LOGGER_FONT_SIZE 14

namespace logger {
	struct log {
		log(std::size_t log_index):m_index(log_index) {
			message->reserve(LOG_LENGTH);
			
		}

		string* message = new string;
		RECT* window_position = new RECT(0,0,0,0);

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

		std::atomic<bool> m_fresh_message = true;
		const std::size_t m_index;
		std::size_t m_lines = 1;
		std::size_t m_height = LOGGER_FONT_SIZE;
	};


	class LOGS_API base {
	public:
		// nol : number of logs
		base(std::size_t nol);
		~base();

		// log a message
		void set_log(logger::log* log_p);

		// get next index position in logs vec for an unset log
		std::size_t get_v_index() { return m_v_index; }

		// get logs_V pointer
		std::vector<log*>* get_buffer() { return m_logs_v; }
	protected:
		// vector used for each log
		std::vector<log*>* m_logs_v = nullptr;

		// this index is always set to the next log
		// not the currently last set log
		// its a vector index
		std::size_t m_v_index = 0;

		// simple time stamp a message
		// returns the message with a time on it ([2025-05-09-14:00:30...])
		string time_stamped(const string& message);

		// prevent concurrent access to logs vec
		std::mutex m_v_mtx;
	};
}