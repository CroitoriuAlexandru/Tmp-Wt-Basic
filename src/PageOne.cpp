#include "include/PageOne.h"
#include <Wt/WText.h>
#include <Wt/WTemplate.h>

PageOne::PageOne()
    : WContainerWidget()
{
    addStyleClass("page-one");
    addWidget(std::make_unique<Wt::WText>("Page One"));
    auto testTmp = addWidget(std::make_unique<Wt::WTemplate>(tr("test-temp-1")));
    // testTmp->addStyleClass("");

}