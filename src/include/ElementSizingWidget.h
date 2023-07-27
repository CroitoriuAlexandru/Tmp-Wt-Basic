#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxClassWithCustoms.h"

struct SizingStyleClasses {
    SizingStyleClasses();
    std::vector<std::string> sizingSize;
	std::vector<std::string> extraSizingWidth;

	std::vector<std::string> minSizing;
	
	std::vector<std::string> maxWidthSizing;
	std::vector<std::string> maxHeightSizing;

	std::vector<std::string> width_classes;
	std::vector<std::string> height_classes;

	std::vector<std::string> min_width_classes;
	std::vector<std::string> min_height_classes;

	std::vector<std::string> max_width_classes;
	std::vector<std::string> max_height_classes;
};

struct SizingData
{
	std::string width = "none";
	std::string minWidth = "none";
	std::string maxWidth = "none";

	std::string height = "none";
	std::string minHeight = "none";
	std::string maxHeight = "none";
};


class ElementSizingWidget : public Wt::WTemplate
{
public:
	ElementSizingWidget(std::string templateName = "stylus2.sizing.template");
	// margin and padding at the moment

	void setClasses(SizingData sizing);
    Wt::Signal<>& styleChanged() { return styleChanged_; }
	std::string getStyles();
	void resetStyles();

private:
	SizingStyleClasses sizingClasses_;

	ComboBoxClassWithCustoms* width_widget_;
	ComboBoxClassWithCustoms* minWidth_widget_;
	ComboBoxClassWithCustoms* maxWidth_widget_;

	ComboBoxClassWithCustoms* height_widget_;
	ComboBoxClassWithCustoms* minHeight_widget_;
	ComboBoxClassWithCustoms* maxHeight_widget_;

	Wt::Signal<> styleChanged_;

	// sizing custom regexp
	std::regex regex_custom_sizing =  std::regex("[w|h]-\\[[\\S]*\\]");
	std::regex regex_custom_min_max_sizing =  std::regex("[min|max]-w-\\[[\\S]*\\]");

};

