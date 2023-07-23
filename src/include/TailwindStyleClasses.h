#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>

#include <Wt/WSignal.h>
#include <vector>
#include <string>
#include <Wt/WString.h>

class ClassComboBox : public Wt::WContainerWidget
{
public:
    ClassComboBox(std::vector<std::string> classNames, std::string selectedClass = "none");

    void setClass(std::string className) { comboBox_->setCurrentIndex(comboBox_->findText(className, Wt::MatchFlag::StringExactly)); };
    std::string getValue() { return comboBox_->currentText().toUTF8(); };
	void setValue(std::string className) { comboBox_->setCurrentIndex(comboBox_->findText(className, Wt::MatchFlag::StringExactly)); };
	
    Wt::WComboBox *comboBox_;
	
private:
    Wt::WPushButton *btn_prev_;
    Wt::WPushButton *btn_next_;
};

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

	// std::vector<std::string> width_classes;
	// std::vector<std::string> width_min_classes;
	// std::vector<std::string> width_max_classes;
	
	// std::vector<std::string> height_classes;
	// std::vector<std::string> height_min_classes;
	// std::vector<std::string> height_max_classes;

	// std::vector<std::string> position_top_classes;
	// std::vector<std::string> position_right_classes;
	// std::vector<std::string> position_bottom_classes;
	// std::vector<std::string> position_left_classes;
};

class ElementStyleClasses : public Wt::WTemplate
{
public:
	ElementStyleClasses();
	// margin and padding at the moment
	SpacingStyleClasses spacingClasses_;

	ClassComboBox* margin_all_widget_;
    ClassComboBox* margin_horizontal_widget_;
    ClassComboBox* margin_vertical_widget_;
    ClassComboBox* margin_top_widget_;
    ClassComboBox* margin_right_widget_;
    ClassComboBox* margin_bottom_widget_;
    ClassComboBox* margin_left_widget_;

    ClassComboBox* padding_all_widget_;
    ClassComboBox* padding_horizontal_widget_;
    ClassComboBox* padding_vertical_widget_;
    ClassComboBox* padding_top_widget_;
    ClassComboBox* padding_right_widget_;
    ClassComboBox* padding_bottom_widget_;
    ClassComboBox* padding_left_widget_;

	void setStyleClasses(std::string styleClasses);
	void resetStyleClasses();
	std::string getElementStyles();
	
    Wt::Signal<std::string>& styleChanged() { return styleChanged_; }
    std::string notFoundClasses = "";
private:
	Wt::Signal<std::string> styleChanged_;
};




