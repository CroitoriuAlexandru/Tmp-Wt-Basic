#include <Wt/WContainerWidget.h>
#include <Wt/WString.h>

class TailwindPopup : public Wt::WContainerWidget
{
public:
  TailwindPopup();
  void showMenu();
private:

  Wt::WString menu_wrapper_styles = "absolute right-0 z-10 mt-2 w-56 origin-top-right rounded-md bg-white shadow-lg ring-1 ring-black ring-opacity-5 focus:outline-none";
  Wt::WString menu_styles = "py-1";
  Wt::WString menuItem_styles = "text-gray-700 block px-4 py-2 text-sm";

  Wt::WString hamburger_XML = 
    R"(<button 
      class="btn" 
        <!-- --!>
        <svg class="block h-6 w-6" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" >
          <path stroke-linecap="round" stroke-linejoin="round" d="M3.75 6.75h16.5M3.75 12h16.5m-16.5 5.25h16.5" />
        </svg>
        <!-- --!>
        <svg class="hidden h-6 w-6" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor">
          <path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" />
        </svg>
      <!-- --!>
    </button>)";

    Wt::WString arrow_btn_XML = R"(
      <button type="button" class="btn flex items-center" 
      id="menu-button" aria-expanded="true" aria-haspopup="true">
        ${text}
        <svg class="-mr-1 h-5 w-5 text-gray-400" viewBox="0 0 20 20" fill="currentColor" aria-hidden="true">
          <path fill-rule="evenodd" d="M5.23 7.21a.75.75 0 011.06.02L10 11.168l3.71-3.938a.75.75 0 111.08 1.04l-4.25 4.5a.75.75 0 01-1.08 0l-4.25-4.5a.75.75 0 01.02-1.06z" clip-rule="evenodd" />
        </svg>
      </button>
    )";
};