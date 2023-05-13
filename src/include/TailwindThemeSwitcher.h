#include <Wt/WText.h>
#include <Wt/WString.h>

namespace Tailwind {
// Tailwind::ThemeSwitcher
//  A widget that changes the theme of the application between light and dark mode by changing the html class to "dark" or "".


    class ThemeSwitcher : public Wt::WText
    {
    public:
        ThemeSwitcher(bool isDarkMode = false, int size = 5);
        void switchTheme();
        void setSize(int size);

    private:

        bool isDarkMode_;
        int size_ = 4;
        void setLightTheme();
        void setDarkTheme();
        // size should be a number between 2 and 8
        
        Wt::WString darkIcon = R"(<svg 
            xmlns="http://www.w3.org/2000/svg" 
            fill="none" viewBox="0 0 24 24" 
            class="stroke-slate-100">
                <path 
                stroke-linecap="round" 
                stroke-linejoin="round" 
                stroke-width="2" 
                d="M20.354 15.354A9 9 0 018.646 3.646 9.003 9.003 0 0012 21a9.003 9.003 0 008.354-5.646z" />
            </svg>)";

        Wt::WString lightIcon = R"(<svg xmlns="http://www.w3.org/2000/svg"
            fill="none" 
            viewBox="0 0 24 24" 
            class="stroke-slate-100">
                <path 
                stroke-linecap="round"
                stroke-linejoin="round" 
                stroke-width="2" 
                d="M12 3v1m0 16v1m9-9h-1M4 12H3m15.364 6.364l-.707-.707M6.343 6.343l-.707-.707m12.728 0l-.707.707M6.343 17.657l-.707.707M16 12a4 4 0 11-8 0 4 4 0 018 0z" />
            </svg>)";

        Wt::WString thisClasses_ = "rounded-full bg-white transition duration-300 focus:outline-none shadow inline";
        Wt::WString togglerClasses_ = "relative rounded-full transition duration-500";

        Wt::WString lightClass_ = "bg-yellow-500";
        Wt::WString darkClass_ = "bg-gray-500";
    };

}
