#include "include/TailwindThemeSwitcher.h"
#include <Wt/WText.h>
#include <Wt/WApplication.h>

namespace Tailwind {

    ThemeSwitcher::ThemeSwitcher(bool isDarkMode, int size)
        : WContainerWidget(),
        isDarkMode_(isDarkMode),
        size_(size)
    {
        toggler_ = addWidget(std::make_unique<Wt::WContainerWidget>());
        togglerIcon_ = toggler_->addWidget(std::make_unique<Wt::WText>(lightIcon, Wt::TextFormat::XHTML));
        
        this->setStyleClass(thisClasses_);
        toggler_->setStyleClass(togglerClasses_);
        toggler_->addStyleClass(lightClass_);
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
        toggler_->addStyleClass(lightClass_);
        toggler_->removeStyleClass(darkClass_);
        toggler_->removeStyleClass(movementClass_);
        togglerIcon_->setText(lightIcon);
        Wt::WApplication::instance()->setHtmlClass("");
    }

    void ThemeSwitcher::setDarkTheme()
    {
        std::cout << "\n\nSetting dark theme\n\n";
        toggler_->removeStyleClass(lightClass_);
        toggler_->addStyleClass(darkClass_);
        toggler_->addStyleClass(movementClass_);
        togglerIcon_->setText(darkIcon);
        Wt::WApplication::instance()->setHtmlClass("dark");
    }

    void ThemeSwitcher::setSize(int size)
    {
        if(size < 2 && size > 8) return;

        int lastSize = size_;
        size_ = size;

        this->removeStyleClass("w-" + std::to_string(lastSize * 2));
        toggler_->removeStyleClass("w-" + std::to_string(lastSize));
        toggler_->removeStyleClass("h-" + std::to_string(lastSize));

        this->addStyleClass("w-" + std::to_string(size_ * 2));
        toggler_->addStyleClass("w-" + std::to_string(size_));
        toggler_->addStyleClass("h-" + std::to_string(size_));

    }

}