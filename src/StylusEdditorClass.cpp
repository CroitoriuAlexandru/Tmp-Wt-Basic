#include "include/StylusEdditorClass.h"
#include <Wt/WPushButton.h>


StylusEdditorClass::StylusEdditorClass()
    : Wt::WTemplate(Wt::WString::tr("stylus.edditor.class.view"))
{
    auto class_padding_edditor = bindWidget("stylus.class.padding", std::make_unique<Wt::WTemplate>(tr("stylus.class.spacing")));

}

StylusEdditorClass::~StylusEdditorClass()
{
}