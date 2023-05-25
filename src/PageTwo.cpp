#include "include/PageTwo.h"
#include <Wt/WText.h>
#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>

PageTwo::PageTwo()
    : WContainerWidget()
{
    addStyleClass("page-two");

    // auto themeSwitcher = addWidget(std::make_unique<Wt::WPushButton>());
    // themeSwitcher->setTextFormat(Wt::TextFormat::XHTML);
    // themeSwitcher->setStyleClass("relative w-10 h-5 m-2 p-0 bg-white rounded-full shadow border-0");
    // themeSwitcher->setText(tr("sun-svg"));

    // themeSwitcher->clicked().connect(this, [=](){
    //     if(Wt::WApplication::instance()->htmlClass() == "dark"){
    //         themeSwitcher->setText(tr("sun-svg"));
    //         Wt::WApplication::instance()->setHtmlClass("");
    //      }else {
    //         themeSwitcher->setText(tr("moon-svg"));
    //         Wt::WApplication::instance()->setHtmlClass("dark");
    //     }
    // });

}
