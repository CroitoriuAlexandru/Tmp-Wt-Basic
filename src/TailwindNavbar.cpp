#include "include/TailwindNavbar.h"
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

TailwindNavbar::TailwindNavbar()
{
    addStyleClass("bg-gray-800");
    // Navbar
    auto navbar_wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());
    navbar_wrapper->addStyleClass(navbar_styles);
    auto navbar = navbar_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    navbar->addStyleClass(navbar_wrapper_styles);

    // Mobile Dropdown Btn
    auto navbar_mobileBtn_wrapper = navbar_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    navbar_mobileBtn_wrapper->addStyleClass(navbar_mobileBtn_styles);
    auto mobiBtn = navbar_mobileBtn_wrapper->addWidget(std::make_unique<Wt::WText>(dropdownBtn_XML, Wt::TextFormat::UnsafeXHTML));

    // Menus Wrapper
    auto navbar_menus_wrapper = navbar->addWidget(std::make_unique<Wt::WContainerWidget>());
    navbar_menus_wrapper->addStyleClass(navbar_menus_wrapper_styles);

    // Navbar Logo
    auto iconsWrapper = navbar_menus_wrapper->addWidget(std::make_unique<Wt::WText>(icons_XML, Wt::TextFormat::UnsafeXHTML));
    iconsWrapper->addStyleClass(navbar_menus_icons_wrapper_styles);


    
}
    
