#include "include/PageTwo.h"
#include <Wt/WText.h>
#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>

PageTwo::PageTwo()
    : WContainerWidget()
{
    addStyleClass("page-two");

    addWidget(std::make_unique<Wt::WTemplate>(tr("test")));

}
