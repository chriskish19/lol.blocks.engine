/***************************************
*  File: base.hpp (base logger)
*
*  Purpose: handles underlying log system
*
*
* *************************************/

#pragma once
#include NAMES_INCLUDE
#include DEPENDS_INCLUDE_PATH

#define LOG_LENGTH 512

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
	protected:
		std::vector<log>* m_logs_v = nullptr;

		std::size_t m_index = 0;
	};
}