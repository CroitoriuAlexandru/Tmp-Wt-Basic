#include "include/TailwindThemeSwitcher.h"
#include <Wt/WText.h>
#include <Wt/WApplication.h>

namespace Tailwind {

    ThemeSwitcher::ThemeSwitcher(bool isDarkMode, int size)
    :   isDarkMode_(isDarkMode),
        size_(size)
    {
 
        this->setStyleClass(thisClasses_);
        setStyleClass(togglerClasses_);
        addStyleClass(lightClass_);
        clicked().connect(this, &ThemeSwitcher::switchTheme);

        if(isDarkMode_) setDarkTheme();
        else setLightTheme();

        setSize(size_);
    }

    void ThemeSwitcher::switchTheme()
    {
        std::cout << "\n\nSwitching theme\n\n";
        isDarkMode_ = !isDarkMode_;
        if(isDarkMode_) setDarkTheme();
        else setLightTheme();
    }

    void ThemeSwitcher::setLightTheme()
    {
        std::cout << "\n\nSetting light theme\n\n";
        addStyleClass(lightClass_);
        removeStyleClass(darkClass_);
        setText(lightIcon);
        Wt::WApplication::instance()->setHtmlClass("");
    }

    void ThemeSwitcher::setDarkTheme()
    {
        std::cout << "\n\nSetting dark theme\n\n";
        removeStyleClass(lightClass_);
        addStyleClass(darkClass_);
        setText(darkIcon);
        Wt::WApplication::instance()->setHtmlClass("dark");
    }

    void ThemeSwitcher::setSize(int size)
    {
        if(size < 2 && size > 8) return;

        int lastSize = size_;
        size_ = size;

        removeStyleClass("w-" + std::to_string(lastSize * 2));
        removeStyleClass("w-" + std::to_string(lastSize));

        addStyleClass("w-" + std::to_string(size_ * 2));
        addStyleClass("w-" + std::to_string(size_));

    }


}