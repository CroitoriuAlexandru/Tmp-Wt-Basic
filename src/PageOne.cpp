#include "include/PageOne.h"
#include <Wt/WText.h>

PageOne::PageOne()
    : WContainerWidget()
{
    addStyleClass("page-one");
    addWidget(std::make_unique<Wt::WText>("Page One"));
}