#include <Wt/WContainerWidget.h>

class TailwindNavbar : public Wt::WContainerWidget
{
public:
    TailwindNavbar();
    void addThemeSwitcher();
private:
    // Wt::WContainerWidget* navbar_;

  Wt::WString dropdown_XML = 
    R"(<button 
      class="inline-flex items-center justify-center rounded-md p-1 bg-gray-600 text-gray-400 hover:bg-gray-700 hover:text-white focus:outline-none focus:ring-1 focus:ring-inset focus:ring-gray-700" 
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

        Wt::WString icons_XML = R"(
            <img class="block h-8 w-auto lg:hidden" src="https://tailwindui.com/img/logos/mark.svg?color=indigo&shade=500" alt="Your Company">
            <img class="hidden h-8 w-auto lg:block" src="https://tailwindui.com/img/logos/mark.svg?color=indigo&shade=500" alt="Your Company">)";
};