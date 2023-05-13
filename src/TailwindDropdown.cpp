#include "include/TailwindDropdown.h"


namespace Tailwind {

    Dropdown::Dropdown()
        : Wt::WContainerWidget()
    {
        addWidget(std::make_unique<Wt::WContainerWidget>());
    }

} // namespace Tailwind