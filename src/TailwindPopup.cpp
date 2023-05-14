#include "include/TailwindPopup.h"
#include <Wt/WTemplate.h>
#include <Wt/WMenuItem.h>

TailwindPopup::TailwindPopup()
{
  setStyleClass("relative inline-block text-left mx-auto");
  auto btn_temp = addWidget(std::make_unique<Wt::WTemplate>(arrow_btn_XML.toXhtmlUTF8()));
  btn_temp->bindString("text", "Popup Button");

  auto menu_wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());
  menu_wrapper->addStyleClass(menu_wrapper_styles);
  menu_wrapper->setAttributeValue("role", "menu");
  menu_wrapper->setAttributeValue("aria-orientation", "vertical");
  menu_wrapper->setAttributeValue("aria-labelledby", "menu-button");
  menu_wrapper->setAttributeValue("tabindex", "-1");


  auto menu = menu_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
  menu->addStyleClass(menu_styles);

  auto menu_item = menu->addWidget(std::make_unique<Wt::WMenuItem>("Menu Item 1"));
  menu_item->addStyleClass(menuItem_styles);
}

void TailwindPopup::showMenu()
{
  auto menu_wrapper = dynamic_cast<Wt::WContainerWidget*>(children().at(1));
  menu_wrapper->show();
}