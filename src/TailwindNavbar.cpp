#include "include/TailwindNavbar.h"
#include "include/TailwindThemeSwitcher.h"
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

TailwindNavbar::TailwindNavbar()
: WContainerWidget()
{
    // class="flex align-middle"
    addStyleClass("flex items-center bg-gray-800 p-2");

    // Dropdown for mobile
    auto dropdown = addWidget(std::make_unique<Wt::WText>(dropdown_XML, Wt::TextFormat::UnsafeXHTML));
    dropdown->setStyleClass("sm:hidden me-auto");
    // Logo/Home Btn
    auto logo = addWidget(std::make_unique<Wt::WText>(icons_XML, Wt::TextFormat::UnsafeXHTML));

    addThemeSwitcher();
}

    
void TailwindNavbar::addThemeSwitcher() {
    auto themeSwitcher = addWidget(std::make_unique<Tailwind::ThemeSwitcher>(false, 4));
    themeSwitcher->addStyleClass("m-2 ms-auto p-1");
}

