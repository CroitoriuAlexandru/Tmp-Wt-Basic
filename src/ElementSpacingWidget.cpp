#include "include/ElementSpacingWidget.h"
#include <regex>


SpacingStyleClasses::SpacingStyleClasses()

{
	spacingSize = { "0", "px", "0.5", "1", "1.5", "2", "2.5", "3", "3.5", "4", "5", "6", "7", "8","9", "10", "11", "12", "14", "16", "20", "24", "28", "32", "36", "40", "44", "48", "52", "56", "64", "72", "80", "96" };

	// create posible classes for margin and padding
	for(auto i = spacingSize.size()-1; i > 2; i--){
		margin_all_classes.push_back("-m-" + spacingSize[i]);
		margin_vertical_classes.push_back("-my-" + spacingSize[i]);
		margin_horizontal_classes.push_back("-mx-" + spacingSize[i]);
		margin_top_classes.push_back("-mt-" + spacingSize[i]);
		margin_right_classes.push_back("-mr-" + spacingSize[i]);
		margin_bottom_classes.push_back("-mb-" + spacingSize[i]);
		margin_left_classes.push_back("-ml-" + spacingSize[i]);
	}

	// add none class witch tells the widget that this class should not be added
	padding_all_classes.push_back("none");
	padding_vertical_classes.push_back("none");
	padding_horizontal_classes.push_back("none");
	padding_top_classes.push_back("none");
	padding_right_classes.push_back("none");
	padding_bottom_classes.push_back("none");
	padding_left_classes.push_back("none");

	margin_all_classes.push_back("none");
	margin_vertical_classes.push_back("none");
	margin_horizontal_classes.push_back("none");
	margin_top_classes.push_back("none");
	margin_right_classes.push_back("none");
	margin_bottom_classes.push_back("none");
	margin_left_classes.push_back("none");

	space_vertical_classes.push_back("none");
	space_horizontal_classes.push_back("none");

	// auto classes just for margin
	margin_all_classes.push_back("m-auto"); 
	margin_vertical_classes.push_back("my-auto");
	margin_horizontal_classes.push_back("mx-auto");
	margin_top_classes.push_back("mt-auto");
	margin_right_classes.push_back("mr-auto");
	margin_bottom_classes.push_back("mb-auto");
	margin_left_classes.push_back("ml-auto");

	for(auto& step : spacingSize){
		padding_top_classes.push_back("pt-" + step);
		padding_right_classes.push_back("pr-" + step);
		padding_bottom_classes.push_back("pb-" + step);
		padding_left_classes.push_back("pl-" + step);
		padding_vertical_classes.push_back("py-" + step);
		padding_horizontal_classes.push_back("px-" + step);
		padding_all_classes.push_back("p-" + step);

		margin_top_classes.push_back("mt-" + step);
		margin_right_classes.push_back("mr-" + step);
		margin_bottom_classes.push_back("mb-" + step);
		margin_left_classes.push_back("ml-" + step);
		margin_vertical_classes.push_back("my-" + step);
		margin_horizontal_classes.push_back("mx-" + step);
		margin_all_classes.push_back("m-" + step);

		space_horizontal_classes.push_back("space-x-" + step);
		space_vertical_classes.push_back("space-y-" + step);

	}
};

ElementSpacingWidget::ElementSpacingWidget(std::string templateName)
	: WTemplate(tr(templateName))
{
	margin_all_widget_ = bindWidget("margin.all.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.margin_all_classes));
	margin_vertical_widget_ = bindWidget("margin.vertical.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.margin_vertical_classes));
	margin_horizontal_widget_ = bindWidget("margin.horizontal.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.margin_horizontal_classes));
	margin_top_widget_ = bindWidget("margin.top.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.margin_top_classes));
	margin_right_widget_ = bindWidget("margin.right.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.margin_right_classes));
	margin_bottom_widget_ = bindWidget("margin.bottom.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.margin_bottom_classes));
	margin_left_widget_ = bindWidget("margin.left.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.margin_left_classes));

	padding_all_widget_ = bindWidget("padding.all.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.padding_all_classes));
	padding_vertical_widget_ = bindWidget("padding.vertical.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.padding_vertical_classes));
	padding_horizontal_widget_ = bindWidget("padding.horizontal.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.padding_horizontal_classes));
	padding_top_widget_ = bindWidget("padding.top.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.padding_top_classes));
	padding_right_widget_ = bindWidget("padding.right.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.padding_right_classes));
	padding_bottom_widget_ = bindWidget("padding.bottom.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.padding_bottom_classes));
	padding_left_widget_ = bindWidget("padding.left.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.padding_left_classes));

	space_vertical_widget_ = bindWidget("space.vertical.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.space_vertical_classes));
	space_horizontal_widget_ = bindWidget("space.horizontal.control", std::make_unique<ComboBoxClassWithCustoms>(spacingClasses_.space_horizontal_classes));

	checkbox_space_x_reverse_ = bindWidget("space.horizontal.reverse.controle", std::make_unique<Wt::WCheckBox>("reverse"));
	checkbox_space_y_reverse_ = bindWidget("space.vertical.reverse.controle", std::make_unique<Wt::WCheckBox>("reverse"));

	// set regular expresion for custom value p-[10px]
	padding_all_widget_->setCustomValueString("p-");
	padding_vertical_widget_->setCustomValueString("px-");
	padding_horizontal_widget_->setCustomValueString("py-");
	padding_top_widget_->setCustomValueString("pt-");
	padding_right_widget_->setCustomValueString("pr-");
	padding_bottom_widget_->setCustomValueString("pb-");
	padding_left_widget_->setCustomValueString("pl-");


	margin_all_widget_->setCustomValueString("m-");
	margin_vertical_widget_->setCustomValueString("mx-");
	margin_horizontal_widget_->setCustomValueString("my-");
	margin_top_widget_->setCustomValueString("mt-");
	margin_right_widget_->setCustomValueString("mr-");
	margin_bottom_widget_->setCustomValueString("mb-");
	margin_left_widget_->setCustomValueString("ml-");

	space_vertical_widget_->setCustomValueString("space-y-");
	space_horizontal_widget_->setCustomValueString("space-x-");

	// set combo box values
	padding_all_widget_->setComboBoxValues(spacingClasses_.padding_all_classes);
	padding_vertical_widget_->setComboBoxValues(spacingClasses_.padding_vertical_classes);
	padding_horizontal_widget_->setComboBoxValues(spacingClasses_.padding_horizontal_classes);
	padding_top_widget_->setComboBoxValues(spacingClasses_.padding_top_classes);
	padding_right_widget_->setComboBoxValues(spacingClasses_.padding_right_classes);
	padding_bottom_widget_->setComboBoxValues(spacingClasses_.padding_bottom_classes);
	padding_left_widget_->setComboBoxValues(spacingClasses_.padding_left_classes);

	margin_all_widget_->setComboBoxValues(spacingClasses_.margin_all_classes);
	margin_vertical_widget_->setComboBoxValues(spacingClasses_.margin_vertical_classes);
	margin_horizontal_widget_->setComboBoxValues(spacingClasses_.margin_horizontal_classes);
	margin_top_widget_->setComboBoxValues(spacingClasses_.margin_top_classes);
	margin_right_widget_->setComboBoxValues(spacingClasses_.margin_right_classes);
	margin_bottom_widget_->setComboBoxValues(spacingClasses_.margin_bottom_classes);
	margin_left_widget_->setComboBoxValues(spacingClasses_.margin_left_classes);

	space_vertical_widget_->setComboBoxValues(spacingClasses_.space_vertical_classes);
	space_horizontal_widget_->setComboBoxValues(spacingClasses_.space_horizontal_classes);

	// signals for default classes for tailwind
	padding_all_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	padding_vertical_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	padding_horizontal_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	padding_top_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	padding_right_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	padding_bottom_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	padding_left_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });	

	margin_all_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	margin_vertical_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	margin_horizontal_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	margin_top_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	margin_right_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	margin_bottom_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	margin_left_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });

	space_vertical_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });
	space_horizontal_widget_->classChanged().connect(this, [=]() { styleChanged_.emit(); });

	checkbox_space_x_reverse_->changed().connect(this, [=]() { styleChanged_.emit(); });
	checkbox_space_y_reverse_->changed().connect(this, [=]() { styleChanged_.emit(); });

};

std::string ElementSpacingWidget::getStyles()
{
	std::string elementClasses;

	if(padding_all_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_all_widget_->getValue(); }
	if(padding_vertical_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_vertical_widget_->getValue(); }
	if(padding_horizontal_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_horizontal_widget_->getValue(); }
	if(padding_top_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_top_widget_->getValue(); }
	if(padding_right_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_right_widget_->getValue(); }
	if(padding_bottom_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_bottom_widget_->getValue(); }
	if(padding_left_widget_->getValue().compare("none") != 0){ elementClasses += " " + padding_left_widget_->getValue(); }

	if(margin_all_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_all_widget_->getValue(); }
	if(margin_vertical_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_vertical_widget_->getValue(); }
	if(margin_horizontal_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_horizontal_widget_->getValue(); }
	if(margin_top_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_top_widget_->getValue(); }
	if(margin_right_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_right_widget_->getValue(); }
	if(margin_bottom_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_bottom_widget_->getValue(); }
	if(margin_left_widget_->getValue().compare("none") != 0){ elementClasses += " " + margin_left_widget_->getValue(); }


	if(space_vertical_widget_->getValue().compare("none") != 0){ elementClasses += " " + space_vertical_widget_->getValue(); }
	if(space_horizontal_widget_->getValue().compare("none") != 0){ elementClasses += " " + space_horizontal_widget_->getValue(); }
	if(checkbox_space_x_reverse_->isChecked()){ elementClasses += " space-x-reverse"; }
	if(checkbox_space_y_reverse_->isChecked()){ elementClasses += " space-y-reverse"; }
	std::cout << "\n\n spacing classes : " << elementClasses << "\n\n";
	return elementClasses;

}

void ElementSpacingWidget::setClasses(SpacingData spacing)
{
	resetStyles();
	// std::cout << "\nElementSpacingWidget::setStyleClasses \n";

	for(auto& padding_class : spacing.padding){
		if(padding_class.find("p-") != std::string::npos){
			padding_all_widget_->setValue(padding_class);
		}else if(padding_class.find("py-") != std::string::npos){
			padding_vertical_widget_->setValue(padding_class);
		}else if(padding_class.find("px-") != std::string::npos){
			padding_horizontal_widget_->setValue(padding_class);
		}else if(padding_class.find("pt-") != std::string::npos){
			padding_top_widget_->setValue(padding_class);
		}else if(padding_class.find("pr-") != std::string::npos){
			padding_right_widget_->setValue(padding_class);
		}else if(padding_class.find("pb-") != std::string::npos){
			padding_bottom_widget_->setValue(padding_class);
		}else if(padding_class.find("pl-") != std::string::npos){
			padding_left_widget_->setValue(padding_class);
		}
	}

	for(auto& margin_class : spacing.margin){
		if(margin_class.find("m-") != std::string::npos){
			margin_all_widget_->setValue(margin_class);
		}else if(margin_class.find("my-") != std::string::npos){
			margin_vertical_widget_->setValue(margin_class);
		}else if(margin_class.find("mx-") != std::string::npos){
			margin_horizontal_widget_->setValue(margin_class);
		}else if(margin_class.find("mt-") != std::string::npos){
			margin_top_widget_->setValue(margin_class);
		}else if(margin_class.find("mr-") != std::string::npos){
			margin_right_widget_->setValue(margin_class);
		}else if(margin_class.find("mb-") != std::string::npos){
			margin_bottom_widget_->setValue(margin_class);
		}else if(margin_class.find("ml-") != std::string::npos){
			margin_left_widget_->setValue(margin_class);
		}
	}

	for(auto& space_class : spacing.space){
		if(space_class.find("space-x-") != std::string::npos){
			if(space_class.find("reverse") != std::string::npos){
				checkbox_space_x_reverse_->setChecked(true);
			}
			space_vertical_widget_->setValue(space_class);
		}else if(space_class.find("space-y-") != std::string::npos){
			space_horizontal_widget_->setValue(space_class);
			if(space_class.find("reverse") != std::string::npos){
				checkbox_space_y_reverse_->setChecked(true);
			}
		}
	}
}

void ElementSpacingWidget::resetStyles()
{
	// std::cout << "\n\n resetStyleClasses";
	padding_all_widget_->setValue();
	padding_vertical_widget_->setValue();
	padding_horizontal_widget_->setValue();
	padding_top_widget_->setValue();
	padding_right_widget_->setValue();
	padding_bottom_widget_->setValue();
	padding_left_widget_->setValue();
	
	margin_all_widget_->setValue();
	margin_vertical_widget_->setValue();
	margin_horizontal_widget_->setValue();
	margin_top_widget_->setValue();
	margin_right_widget_->setValue();
	margin_bottom_widget_->setValue();
	margin_left_widget_->setValue();

	space_vertical_widget_->setValue();
	space_horizontal_widget_->setValue();
	checkbox_space_x_reverse_->setChecked(false);
	checkbox_space_y_reverse_->setChecked(false);
}

