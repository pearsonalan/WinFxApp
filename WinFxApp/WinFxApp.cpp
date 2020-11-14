#include "winfx.h"
#include "Resource.h"

class MainWindow : public winfx::Window {
public:
	MainWindow() : winfx::Window(L"MyMainWindow", winfx::loadString(IDS_APP_TITLE)) {}
	~MainWindow() override {}

	void modifyWndClass(WNDCLASSEXW& wc) override;
	LRESULT handleWindowMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	winfx::Size getDefaultWindowSize() override {
		return winfx::Size(400, 300);
	}

protected:
	void onCommand(HWND hwndParam, int id, HWND hwndCtl, UINT codeNotify);
	void onDestroy(HWND hwndParam);
};

class AboutDialog : public winfx::Dialog {
public:
	AboutDialog(Window* pwnd) : winfx::Dialog(pwnd, IDD_ABOUTBOX) {}
};

void MainWindow::modifyWndClass(WNDCLASSEXW& wc)  {
	wc.lpszMenuName = MAKEINTRESOURCE(IDC_WINFXAPP);
}

LRESULT MainWindow::handleWindowMessage(HWND hwndParam, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		HANDLE_MSG(hwndParam, WM_COMMAND, onCommand);
		HANDLE_MSG(hwndParam, WM_DESTROY, onDestroy);
	}
	return Window::handleWindowMessage(hwndParam, uMsg, wParam, lParam);
}

void MainWindow::onCommand(HWND hwndParam, int id, HWND hwndCtl, UINT codeNotify) {
	switch (id) {
	case IDM_ABOUT:
		AboutDialog(this).doDialogBox();
		break;

	case IDM_EXIT:
		destroy();
		break;
	}
}

void MainWindow::onDestroy(HWND hwndParam) {
	winfx::DebugOut(L"onDestroy\n");
	PostQuitMessage(0);
}

class TestApp : public winfx::App {
protected:
	MainWindow mainWindow;
public:
	virtual bool initWindow(LPWSTR pwstrCmdLine, int nCmdShow) ;
};

bool TestApp::initWindow(LPWSTR pwstrCmdLine, int nCmdShow) {
	return mainWindow.createAppWindow(pwstrCmdLine, nCmdShow);
}

TestApp testApp;
