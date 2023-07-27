#include <Wt/WTemplate.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WComboBox.h>
#include "ComboBoxClassWithCustoms.h"

struct SpacingStyleClasses {
    SpacingStyleClasses();
    std::vector<std::string> spacingSize;

	std::vector<std::string> padding_top_classes;
	std::vector<std::string> padding_right_classes;
	std::vector<std::string> padding_bottom_classes;
	std::vector<std::string> padding_left_classes;
	std::vector<std::string> padding_vertical_classes;
	std::vector<std::string> padding_horizontal_classes;
	std::vector<std::string> padding_all_classes;

	std::vector<std::string> margin_top_classes;
	std::vector<std::string> margin_right_classes;
	std::vector<std::string> margin_bottom_classes;
	std::vector<std::string> margin_left_classes;
	std::vector<std::string> margin_vertical_classes;
	std::vector<std::string> margin_horizontal_classes;
	std::vector<std::string> margin_all_classes;

	std::vector<std::string> space_vertical_classes;
	std::vector<std::string> space_horizontal_classes;

};

struct SpacingData
{
	std::vector<std::string> padding;
	std::vector<std::string> margin;
	std::vector<std::string> space;
};

class ElementSpacingWidget : public Wt::WTemplate
{
public:
	ElementSpacingWidget(std::string templateName = "stylus2.spacing.template");
	// margin and padding at the moment

	void setClasses(SpacingData spacing);
    Wt::Signal<>& styleChanged() { return styleChanged_; }
	std::string getStyles();
	void resetStyles();

private:
	SpacingStyleClasses spacingClasses_;

	ComboBoxClassWithCustoms* margin_all_widget_;
    ComboBoxClassWithCustoms* margin_horizontal_widget_;
    ComboBoxClassWithCustoms* margin_vertical_widget_;
    ComboBoxClassWithCustoms* margin_top_widget_;
    ComboBoxClassWithCustoms* margin_right_widget_;
    ComboBoxClassWithCustoms* margin_bottom_widget_;
    ComboBoxClassWithCustoms* margin_left_widget_;

    ComboBoxClassWithCustoms* padding_all_widget_;
    ComboBoxClassWithCustoms* padding_horizontal_widget_;
    ComboBoxClassWithCustoms* padding_vertical_widget_;
    ComboBoxClassWithCustoms* padding_top_widget_;
    ComboBoxClassWithCustoms* padding_right_widget_;
    ComboBoxClassWithCustoms* padding_bottom_widget_;
    ComboBoxClassWithCustoms* padding_left_widget_;

	ComboBoxClassWithCustoms* space_vertical_widget_;
	ComboBoxClassWithCustoms* space_horizontal_widget_;

	Wt::Signal<> styleChanged_;

	Wt::WCheckBox* checkbox_space_x_reverse_;
	Wt::WCheckBox* checkbox_space_y_reverse_;

	std::regex regex_custom_padding =  std::regex("p[x,y,l,r,t,b]?-\\[[\\S]*\\]"); 
	std::regex regex_custom_margin =  std::regex("-?m[x,y,l,r,t,b]?-\\[[\\S]*\\]");
	std::regex regex_custom_space =  std::regex("space-[x|y]?-\\[[\\S]*\\]");
};
