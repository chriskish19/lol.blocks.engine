/***************************************
*  File: main.cpp
*
*  Purpose: main entry into the program
*
*  Project: core
* *************************************/



#include CORE_NAMES_INCLUDE
#include CORE_ALL_CORE_INCLUDE_PATH

#include ENGINE_NAMES_INCLUDE
#include ENGINE_ALL_ENGINE_INCLUDE_PATH

#include GUI_NAMES_INCLUDE
#include GUI_ALL_GUI_INCLUDE_PATH

#include LOGGER_NAMES_INCLUDE
#include LOGGER_ALL_LOGS_INCLUDE_PATH

#include TEST_NAMES_INCLUDE
#include TEST_ALL_TESTS_INCLUDE_PATH


#if MAIN_ENTRY

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
	std::unique_ptr<core::standard_window> window = nullptr;
	std::unique_ptr<engine::dx11::cube_demo> dx11_demo = nullptr;

	try {
		window = std::make_unique<core::standard_window>();
		{
			core::codes code = window->load();
			core::output_code(code);
			if (code != core::codes::success) {
				return static_cast<int>(code);
			}
		}

		dx11_demo = std::make_unique<engine::dx11::cube_demo>(window->handle(), window->width(), window->height());
		{
			engine::codes code = dx11_demo->load_content();
			engine::output_code(code);
			if (code != engine::codes::success) {
				return static_cast<int>(code);
			}
		}

		std::chrono::high_resolution_clock::time_point lastTime;
		MSG msg = { 0 };
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				auto now = std::chrono::high_resolution_clock::now();
				float deltaTime = std::chrono::duration<float>(now - lastTime).count();
				lastTime = now;

				dx11_demo->update(deltaTime);
				dx11_demo->render();
			}
		}
	}
	catch (const core::ce& e) {
		// core error exception
		core::output_co(e);
		return static_cast<int>(e.m_code);
	}
	catch (const engine::ee& e) {
		// engine lib error exception
		engine::output_co(e);
		return static_cast<int>(e.m_code);
	}
	catch (const std::exception& e) {
		// exception from c++ standard lib
#if WIDE
		core::string message = ROS("std exception, what: ") + core::to_wide_string(e.what());
#else
		core::string message = ROS("std exception, what: ") + e.what();
#endif

#if SYS_LOG_OUT
		logger::glb_sl->log_message(message + ROS('\n') + ROS("LOCATION: ") + core::gl());
#endif
#if STD_COUT
		COUT << message << '\n' << ROS("LOCATION: ") << core::gl();
#endif
#if VS_OUT_WINDOW
		message = message + "\n" + core::gl();
		OutputDebugString(message.c_str());
#endif
		return static_cast<int>(core::codes::std_exception_caught);
	}
	catch (...) {
		// any error
		core::output_code(core::codes::unknown_exception_caught);
		return static_cast<int>(core::codes::unknown_exception_caught);
	}

	return static_cast<int>(core::codes::success);
}

#elif TEST_ENTRY

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
	logger::glb_sl->get_terminal_p()->wait_until_init();

	logger::codes code = test::classic_log_terminal(10,1);
	return static_cast<int>(code);
}


// gives a terminal console
/*
int main() {
	// Prepare arguments for wWinMain
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	HINSTANCE hPrevInstance = nullptr;
	LPWSTR lpCmdLine = GetCommandLineW();
	int nShowCmd = SW_SHOW;

	// Call wWinMain
	return wWinMain(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}
*/


#endif