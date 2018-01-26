#pragma once

#include "EverydayTools/UnusedVar.h"
#include "EverydayTools/Exception/CallAndRethrow.h"
#include "EverydayTools/Exception/PrintException.h"

#include <Windows.h>
#include <CommCtrl.h>


template<typename TChar>
using WndClass = std::conditional_t<
	std::is_same_v<std::decay_t<TChar>, char>,
	WNDCLASSA, WNDCLASSW>;

template<typename TChar>
using WndClassEx = std::conditional_t<
	std::is_same_v<std::decay_t<TChar>, char>,
	WNDCLASSEXA, WNDCLASSEXW>;

#define MakeFnWrapper($name)																\
	template<typename TChar>																\
	struct $name##_Wrap;																	\
																							\
	template<>																				\
	struct $name##_Wrap<char>																\
	{																						\
		static decltype($name##A)* GetFn() { return $name##A; }								\
	};																						\
																							\
	template<>																				\
	struct $name##_Wrap<wchar_t>															\
	{																						\
		static decltype($name##W)* GetFn() { return $name##W; }								\
	};

MakeFnWrapper(CreateWindowEx)
MakeFnWrapper(DefWindowProc)
MakeFnWrapper(DispatchMessage)
MakeFnWrapper(FormatMessage)
MakeFnWrapper(GetMessage)
MakeFnWrapper(GetWindowLongPtr)
MakeFnWrapper(LoadIcon)
MakeFnWrapper(MessageBox)
MakeFnWrapper(MessageBoxEx)
MakeFnWrapper(RegisterClass)
MakeFnWrapper(RegisterClassEx)
MakeFnWrapper(SetWindowLongPtr)
MakeFnWrapper(UnregisterClass)

#define WrappedFn($name) $name##_Wrap<TChar>::GetFn()
#define DefineLocalType($name) using $name = ::$name<TChar>

enum class WinCommonControlsGroup {
	Animate      = ICC_ANIMATE_CLASS,
	Bar          = ICC_BAR_CLASSES,
	Cool         = ICC_COOL_CLASSES,
	Date         = ICC_DATE_CLASSES,
	Hotkey       = ICC_HOTKEY_CLASS,
	Internet     = ICC_INTERNET_CLASSES,
	Link         = ICC_LINK_CLASS,
	ListView     = ICC_LISTVIEW_CLASSES,
	NativeFont   = ICC_NATIVEFNTCTL_CLASS,
	PageScroller = ICC_PAGESCROLLER_CLASS,
	Progress     = ICC_PROGRESS_CLASS,
	Standard     = ICC_STANDARD_CLASSES,
	Tab          = ICC_TAB_CLASSES,
	TreeView     = ICC_TREEVIEW_CLASSES,
	UpDown       = ICC_UPDOWN_CLASS,
	UserExt      = ICC_USEREX_CLASSES,
	Win95        = ICC_WIN95_CLASSES
};

enum class WinCommonControl {
	//ICC_ANIMATE_CLASS
	Animate,         //ANIMATE_CLASS

	//ICC_BAR_CLASSES
	Toolbar,         //TOOLBARCLASSNAME
	Statusbar,       //STATUSCLASSNAME
	Trackar,        //TRACKBAR_CLASS
	Tooltip,

	//ICC_COOL_CLASSES
	Rebar,           //REBARCLASSNAME

	//ICC_DATE_CLASSES
	DateTimePicker,  //DATETIMEPICK_CLASS

	//ICC_HOTKEY_CLASS
	Hotkey,          //HOTKEY_CLASS

	//ICC_INTERNET_CLASSES
	IP,              //WC_IPADDRESS

	//ICC_LINK_CLASS
	Link,            //WC_LINK

	//ICC_LISTVIEW_CLASSES
	ListView,        //WC_LISTVIEW
	Header,          //WC_HEADER

	//ICC_NATIVEFNTCTL_CLASS
	NativeFont,      //WC_NATIVEFONTCTL

	//ICC_PAGESCROLLER_CLASS
	PageScroller,    //WC_PAGESCROLLER

	//ICC_PROGRESS_CLASS
	ProgressBar,     //PROGRESS_CLASS

	//ICC_STANDARD_CLASSES
	Button,          //WC_BUTTON
	EditBox,         //WC_EDIT
	Static,          //WC_STATIC
	ListBox,         //WC_LISTBOX
	ComboBox,        //WC_COMBOBOX
	ScrollBar,       //WC_SCROLLBAR
	
	//ICC_TAB_CLASSES
	Tab,             //WC_TABCONTROL
	//Tooltip,         //TOOLTIPS_CLASS

	//ICC_TREEVIEW_CLASSES
	TreeView,        //WC_TREEVIEW
	//Tooltip

	//ICC_UPDOWN_CLASS
	UpDown,          //UPDOWN_CLASS

	//ICC_USEREX_CLASSES
	ComboBoxEx,      //WC_COMBOBOXEX

	//ICC_WIN95_CLASSES
	//Animate
	//Header
	//HotKey
	//ListView
	//ProgressBar
	//Statusbar
	//Tab
	//Tooltip
	//
};

WinCommonControlsGroup WinGetControlGroup(WinCommonControl control) {
#define _InternalMap($result, $a)               \
	case WinCommonControl::$a:                  \
		return WinCommonControlsGroup::$result; \
	break

	switch (control) {
		_InternalMap(Animate, Animate);
		_InternalMap(Bar, Toolbar);
		_InternalMap(Bar, Statusbar);
		_InternalMap(Bar, Trackar);
		_InternalMap(Bar, Tooltip);
		_InternalMap(Cool, Rebar);
		_InternalMap(Date, DateTimePicker);
		_InternalMap(Hotkey, Hotkey);
		_InternalMap(Internet, IP);
		_InternalMap(Link, Link);
		_InternalMap(ListView, ListView);
		_InternalMap(ListView, Header);
		_InternalMap(NativeFont, NativeFont);
		_InternalMap(PageScroller, PageScroller);
		_InternalMap(Progress, ProgressBar);
		_InternalMap(Standard, Button);
		_InternalMap(Standard, EditBox);
		_InternalMap(Standard, Static);
		_InternalMap(Standard, ListBox);
		_InternalMap(Standard, ComboBox);
		_InternalMap(Standard, ScrollBar);
		_InternalMap(Tab, Tab);
		_InternalMap(TreeView, TreeView);
		_InternalMap(UpDown, UpDown);
		_InternalMap(UserExt, ComboBoxEx);
	}

	throw std::runtime_error("Invalid input!");

#undef _InternalMap
}

template<typename Char, WinCommonControl ctrl>
struct WinCommonControlClassName;

#define MakeWinCommonControlClassNameChar(tchar, ctrl, name)            \
    template<>                                                          \
    struct WinCommonControlClassName<tchar, WinCommonControl::ctrl> {   \
        static constexpr auto ClassName = name;                       \
    }

#define MakeWinCommonControlClassName(ctrl, name_a, name_w)            \
	MakeWinCommonControlClassNameChar(char, ctrl, name_a);             \
	MakeWinCommonControlClassNameChar(wchar_t, ctrl, name_w);

MakeWinCommonControlClassName(Animate, ANIMATE_CLASSA, ANIMATE_CLASSW);
MakeWinCommonControlClassName(Toolbar, TOOLTIPS_CLASSA, TOOLTIPS_CLASSW);
MakeWinCommonControlClassName(Statusbar, STATUSCLASSNAMEA, STATUSCLASSNAMEW);
MakeWinCommonControlClassName(Trackar, TRACKBAR_CLASSA, TRACKBAR_CLASSW);
MakeWinCommonControlClassName(Tooltip, TOOLTIPS_CLASSA, TOOLTIPS_CLASSW);
MakeWinCommonControlClassName(Rebar, REBARCLASSNAMEA, REBARCLASSNAMEW);
MakeWinCommonControlClassName(DateTimePicker, DATETIMEPICK_CLASSA, DATETIMEPICK_CLASSW);
MakeWinCommonControlClassName(Hotkey, HOTKEY_CLASSA, HOTKEY_CLASSW);
MakeWinCommonControlClassName(IP,  WC_IPADDRESSA, WC_IPADDRESSW);
MakeWinCommonControlClassName(Link, "SysLink", WC_LINK);
MakeWinCommonControlClassName(ListView, WC_LISTVIEWA, WC_LISTVIEWW);
MakeWinCommonControlClassName(Header, WC_HEADERA, WC_HEADERW);
MakeWinCommonControlClassName(NativeFont, WC_NATIVEFONTCTLA, WC_NATIVEFONTCTLW);
MakeWinCommonControlClassName(PageScroller, WC_PAGESCROLLERA, WC_PAGESCROLLERW);
MakeWinCommonControlClassName(ProgressBar, PROGRESS_CLASSA, PROGRESS_CLASSW);
MakeWinCommonControlClassName(Button, WC_BUTTONA, WC_BUTTONW);
MakeWinCommonControlClassName(EditBox, WC_EDITA, WC_EDITW);
MakeWinCommonControlClassName(Static, WC_STATICA, WC_STATICW);
MakeWinCommonControlClassName(ListBox, WC_LISTBOXA, WC_LISTBOXW);
MakeWinCommonControlClassName(ComboBox, WC_COMBOBOXA, WC_COMBOBOXW);
MakeWinCommonControlClassName(ScrollBar, WC_SCROLLBARA, WC_SCROLLBARW);
MakeWinCommonControlClassName(Tab, WC_TABCONTROLA, WC_TABCONTROLW);
MakeWinCommonControlClassName(TreeView, WC_TREEVIEWA, WC_TREEVIEWW);
MakeWinCommonControlClassName(UpDown, UPDOWN_CLASSA, UPDOWN_CLASSW);
MakeWinCommonControlClassName(ComboBoxEx, WC_COMBOBOXEXA, WC_COMBOBOXEXW);

template<typename Char>
const char* WinGetControlClassName(WinCommonControl control) {
#define _InternalMap(in)                                                         \
	case WinCommonControl::in:                                                   \
		return WinCommonControlClassName<Char, WinCommonControl::in>::ClassName; \
	break

	switch (control) {
		_InternalMap(Animate);
		_InternalMap(Toolbar);
		_InternalMap(Statusbar);
		_InternalMap(Trackar);
		_InternalMap(Tooltip);
		_InternalMap(Rebar);
		_InternalMap(DateTimePicker);
		_InternalMap(Hotkey);
		_InternalMap(IP);
		_InternalMap(Link);
		_InternalMap(ListView);
		_InternalMap(Header);
		_InternalMap(NativeFont);
		_InternalMap(PageScroller);
		_InternalMap(ProgressBar);
		_InternalMap(Button);
		_InternalMap(EditBox);
		_InternalMap(Static);
		_InternalMap(ListBox);
		_InternalMap(ComboBox);
		_InternalMap(ScrollBar);
		_InternalMap(Tab);
		_InternalMap(TreeView);
		_InternalMap(UpDown);
		_InternalMap(ComboBoxEx);
	default:
		throw std::invalid_argument("WinGetControlClassName received invalid argument!");
	}

#undef _InternalMap
}

template<typename TChar>
class WinAPI {
public:
	DefineLocalType(WndClass);
	DefineLocalType(WndClassEx);

	static HWND CreateWindow_(const TChar* lpClassName, const TChar* lpWindowName, uint32_t dwStyle,
		int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, void* lpParam) {
		return WrappedFn(CreateWindowEx)(0L, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	static HWND CreateWindowEx_(uint32_t dwExStyle, const TChar* lpClassName, const TChar* lpWindowName, uint32_t dwStyle,
		int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, const void* lpParam) {
		return WrappedFn(CreateWindowEx)(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	static HWND CreateWindow_(WinCommonControl control, const TChar* lpWindowName, uint32_t dwStyle,
		int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, void* lpParam) {
		auto contolGroup = static_cast<uint32_t>(WinGetControlGroup(control));
		auto className = WinGetControlClassName<TChar>(control);
		State::Instance().InitializeClass(contolGroup);

		return WrappedFn(CreateWindowEx)(0L, className, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	static LRESULT DefWindowProc_(HWND hWnd, unsigned msg, WPARAM wParam, LPARAM lParam) {
		return WrappedFn(DefWindowProc)(hWnd, msg, wParam, lParam);
	}

	static LONG_PTR DispatchMessage_(const MSG* msg) {
		return WrappedFn(DispatchMessage)(msg);
	}

	static uint32_t FormatMessage_(uint32_t dwFlags, const void* source, uint32_t message, uint32_t language, TChar* buffer, uint32_t size, va_list* args) {
		return WrappedFn(FormatMessage)(dwFlags, source, message, language, buffer, size, args);
	}

	static bool GetMessage_(MSG* msg, HWND hWnd, unsigned wMsgFilterMin, unsigned wMsgFilterMax) {
		return WrappedFn(GetMessage)(msg, hWnd, wMsgFilterMin, wMsgFilterMax);
	}

	static LONG_PTR GetWindowLongPtr_(HWND hWnd, int nIndex) {
		return WrappedFn(GetWindowLongPtr)(hWnd, nIndex);
	}

	static HICON LoadIcon_(HINSTANCE hInstance, const TChar* iconName) {
		return WrappedFn(LoadIcon)(hInstance, iconName);
	}

	template<typename Input>
	inline static const TChar* MakeIntResource_(Input value) {
		return ((TChar*)((ULONG_PTR)((WORD)(value))));
	}

	static int MessageBox_(HWND hWnd, const TChar* lpText, const TChar* lpCaption, unsigned uType) {
		return WrappedFn(MessageBox)(hWnd, lpText, lpCaption, uType);
	}

	static int MessageBoxEx_(HWND hWnd, const TChar* lpText, const TChar* lpCaption, unsigned uType, uint16_t wLanguageId) {
		return WrappedFn(MessageBoxEx)(hWnd, lpText, lpCaption, uType, wLanguageId);
	}

	static uint16_t RegisterClass_(const WndClass* pClass) {
		return WrappedFn(RegisterClass)(pClass);
	}

	static uint16_t RegisterClassEx_(const WndClassEx* pClassEx) {
		return WrappedFn(RegisterClassEx)(pClassEx);
	}

	static LONG_PTR SetWindowLongPtr_(HWND hWnd, int nIndex, LONG_PTR dwNewLong) {
		return WrappedFn(SetWindowLongPtr)(hWnd, nIndex, dwNewLong);
	}

	static bool UnregisterClass_(const TChar* className, HINSTANCE hInstance) {
		return WrappedFn(UnregisterClass)(className, hInstance);
	}

	template<typename F>
	static bool HandleLastError(F&& onError)
	{
		//Get the error message, if any.
		uint32_t errorMessageID = ::GetLastError();

		//No error message has been recorded
		if (errorMessageID == 0)
			return false;

		TChar* messageBuffer = nullptr;
		auto size = FormatMessage_(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			0, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (TChar*)&messageBuffer, 0, nullptr);

		std::string message(messageBuffer, size);

		//Free the buffer.
		LocalFree(messageBuffer);

		onError(std::move(message));

		return true;
	}

	static void ThrowLastError() {
		HandleLastError([](std::string&& str) {
			throw std::runtime_error(std::move(str));
		});
	}

	static void LogLastError(std::ostream& output) {
		HandleLastError([&](std::string&& str) {
			output << str << std::endl;
		});
	}

private:
	struct State {
		static State& Instance() {
			static State instance;
			return instance;
		}

		void InitializeClass(uint32_t bits) {
			if ((bits | initInfo.dwICC) != initInfo.dwICC) {
				initInfo.dwICC |= bits;
				InitCommonControlsEx(&initInfo);
			}
		}

		INITCOMMONCONTROLSEX initInfo;
	};
};

template<
	typename TChar,
	template<typename TChar> typename Derived>
class WindowClass {
	using TDerived = Derived<TChar>;
public:
	using WA = WinAPI<TChar>;

	WindowClass(HINSTANCE module_) :
		m_module(module_) {
		CallAndRethrow("WindowClass::WindowClass(HINSTANCE) ", [&]() {
			typename WA::WndClassEx wndClass;
			wndClass.cbSize = sizeof(wndClass);
			wndClass.style = CS_HREDRAW | CS_VREDRAW;
			wndClass.lpfnWndProc = WndProc;
			wndClass.cbClsExtra = 0;
			wndClass.cbWndExtra = 0;
			wndClass.hInstance = m_module;
			wndClass.hIcon = WA::LoadIcon_(m_module, IDI_APPLICATION);
			wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wndClass.lpszMenuName = NULL;
			wndClass.lpszClassName = CastThis()->GetName();
			wndClass.hIconSm = LoadIcon(m_module, IDI_APPLICATION);

			if (!WA::RegisterClassEx_(&wndClass)) {
				WA::ThrowLastError();
			}
		});
	}

	decltype(auto) MakeWindow(const TChar* title) const {
		return CallAndRethrow("WindowClass::MakeWindow", [&]() {
			std::unique_ptr<typename TDerived::Window> wnd;
			wnd = std::make_unique<typename TDerived::Window>();
			auto hWnd = WA::CreateWindow_(
				CastThis()->GetName(),
				title,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,
				500, 100,
				NULL,
				NULL,
				m_module,
				wnd.get()
			);

			if (hWnd == nullptr) {
				WA::ThrowLastError();
			}

			wnd->SetHandle(hWnd);
			wnd->Initialize(m_module);

			return wnd;
		});
	}

	~WindowClass() {
		WA::UnregisterClass_(CastThis()->GetName(), m_module);
	}

protected:
	// Make this class friend to derived to make it possible to use it's protected and private methods
	friend WindowClass;

private:
	decltype(auto) CastThis() { return static_cast<TDerived*>(this); }
	decltype(auto) CastThis() const { return static_cast<const TDerived*>(this); }

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		using Wnd = typename TDerived::Window;
		Wnd* pWnd = nullptr;

		switch (msg) {
			case WM_CREATE: {
				auto pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
				pWnd = reinterpret_cast<Wnd*>(pCreateStruct->lpCreateParams);
				WA::SetWindowLongPtr_(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
				assert(WA::GetWindowLongPtr_(hWnd, GWLP_USERDATA) == reinterpret_cast<LONG_PTR>(pWnd));
				break;
			}

			default:
				pWnd = reinterpret_cast<Wnd*>(WA::GetWindowLongPtr_(hWnd, GWLP_USERDATA));
				break;
		}

		if (pWnd) {
			return pWnd->WndProc(hWnd, msg, wParam, lParam);
		}

		return WA::DefWindowProc_(hWnd, msg, wParam, lParam);
	}

	HINSTANCE m_module;
};

template<
	typename TChar,
	template<typename> typename Derived>
class Window {
public:
	using WA = WinAPI<TChar>;

	Window(HWND handle = nullptr) :
		m_handle(handle) {}

	~Window() {
		if (m_handle != nullptr) {
			auto res = DestroyWindow(m_handle);
			assert(res);
		}
	}

	HWND GetHandle() const {
		return m_handle;
	}

	void SetHandle(HWND handle) {
		assert(m_handle == nullptr);
		m_handle = handle;
	}

	void Show(int nCmdShow) {
		assert(m_handle != nullptr);
		ShowWindow(m_handle, nCmdShow);
	}

	void Update() {
		assert(m_handle != nullptr);
		UpdateWindow(m_handle);
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		return WA::DefWindowProc_(hWnd, msg, wParam, lParam);
	}

	HWND AddControl(WinCommonControl control, const TChar* lpWindowName, uint32_t dwStyle, int X, int Y, int nWidth, int nHeight, HMENU hMenu, HINSTANCE hInstance, void* lpParam) {
		RECT rcClient;
		GetClientRect(GetHandle(), &rcClient);
		auto handle = WA::CreateWindow_(control, lpWindowName, dwStyle, rcClient.left + X, rcClient.top + Y, nWidth, nHeight, GetHandle(), hMenu, hInstance, lpParam);
		if (!handle) {
			WA::ThrowLastError();
		}
		return handle;
	}

private:
	HWND m_handle;
};