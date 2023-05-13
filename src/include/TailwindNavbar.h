#include <Wt/WContainerWidget.h>

class TailwindNavbar : public Wt::WContainerWidget
{
public:
    TailwindNavbar();
    
private:
    Wt::WString navbar_wrapper_styles = "mx-auto max-w-7xl px-2 sm:px-6 lg:px-8";
    Wt::WString navbar_styles =         "relative flex items-center justify-between h-16";
    Wt::WString navbar_mobileBtn_styles = "absolute inset-y-0 left-0 flex items-center sm:hidden";
    Wt::WString navbar_menus_wrapper_styles = "flex flex-1 items-center justify-center sm:items-stretch sm:justify-start";
    Wt::WString navbar_menus_icons_wrapper_styles = "flex flex-shrink-0 items-center";



    Wt::WString dropdownSvg = 
    R"(<svg 
        class="block h-6 w-6" fill="none" 
        viewBox="0 0 24 24" 
        stroke-width="1.5" 
        stroke="currentColor" 
        aria-hidden="true">
            <path stroke-linecap="round" 
            stroke-linejoin="round" 
            d="M3.75 6.75h16.5M3.75 12h16.5m-16.5 5.25h16.5" />
    </svg>)";

    Wt::WString dropdownBtn_XML = 
    R"(<button class="inline-flex items-center justify-center rounded-md p-2 text-gray-400 hover:bg-gray-700 hover:text-white focus:outline-none focus:ring-2 focus:ring-inset focus:ring-white" 
          <!--
            Icon when menu is closed.

            Menu open: "hidden", Menu closed: "block"
          -->
          <svg class="block h-6 w-6" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" aria-hidden="true">
            <path stroke-linecap="round" stroke-linejoin="round" d="M3.75 6.75h16.5M3.75 12h16.5m-16.5 5.25h16.5" />
          </svg>
          <!--
            Icon when menu is open.

            Menu open: "block", Menu closed: "hidden"
          -->
          <svg class="hidden h-6 w-6" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" aria-hidden="true">
            <path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" />
          </svg>
        </button>)";

        Wt::WString icons_XML = R"(
            <img class="block h-8 w-auto lg:hidden" src="https://tailwindui.com/img/logos/mark.svg?color=indigo&shade=500" alt="Your Company">
            <img class="hidden h-8 w-auto lg:block" src="https://tailwindui.com/img/logos/mark.svg?color=indigo&shade=500" alt="Your Company">)";
};