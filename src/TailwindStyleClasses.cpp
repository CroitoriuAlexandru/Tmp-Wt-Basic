#include "include/TailwindStyleClasses.h"
#include <iostream>
#include <regex>

ClassComboBox::ClassComboBox(std::vector<std::string> classNames, std::string selectedClass)
{
	btn_prev_ = addWidget(std::make_unique<Wt::WPushButton>("<"));
	comboBox_ = addWidget(std::make_unique<Wt::WComboBox>());
	btn_next_ = addWidget(std::make_unique<Wt::WPushButton>(">"));

	btn_prev_->setThemeStyleEnabled(false);
	btn_next_->setThemeStyleEnabled(false);

	Wt::WString btns_classes = "p-1 pb-px rounded-lg m-0 flex border-gray-200 ";
	btn_prev_->setStyleClass(btns_classes + "rounded-r-none");
	btn_next_->setStyleClass(btns_classes + "rounded-l-none");
	comboBox_->setStyleClass("p-px rounded-none m-0 !h-full border-gray-200 appearance-none w-[45px] h-[24px] ps-1 focus-visible:outline-none");
	comboBox_->addItem("none");

	// iterate over classnames and add them to the combobox
	for(auto& className : classNames){
		comboBox_->addItem(className);
		if((selectedClass.compare(className)) == 0){
			std::cout << "\n\n found selected class: " << className << "\n\n";
			comboBox_->setCurrentIndex(comboBox_->count());
		}
	}
	btn_prev_->clicked().connect(this, [=](){
		comboBox_->setCurrentIndex(comboBox_->currentIndex() - 1);
		comboBox_->activated().emit(comboBox_->currentIndex());
	});
	btn_next_->clicked().connect(this, [=](){
		comboBox_->setCurrentIndex(comboBox_->currentIndex() + 1);
		comboBox_->activated().emit(comboBox_->currentIndex());
	});
}

SpacingStyleClasses::SpacingStyleClasses()
{
	spacingSize = { "px", "0", "0.5", "1", "1.5", "2", "2.5", "3", "3.5", "4", "5", "6", "8", "10", "11", "12", "14", "16", "20", "24", "28", "32", "36", "40", "44", "48", "52", "56", "64", "72", "80", "96" };
	// create posible classes for margin and padding
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

		// width_classes.push_back("w-" + step);
		// width_min_classes.push_back("min-w-" + step);
		// width_max_classes.push_back("max-w-" + step);

		// height_classes.push_back("h-" + step);
		// height_min_classes.push_back("min-h-" + step);
		// height_max_classes.push_back("max-h-" + step);
		
		// position_top_classes.push_back("top-" + step);
		// position_right_classes.push_back("right-" + step);
		// position_bottom_classes.push_back("bottom-" + step);
		// position_left_classes.push_back("left-" + step);
	}
};

ElementStyleClasses::ElementStyleClasses()
	: Wt::WTemplate(tr("stylus2.edditor.margin.padding"))
{
	// currentStyles_ = "";
	margin_all_widget_ = bindWidget("margin.all.control", std::make_unique<ClassComboBox>(spacingClasses_.margin_all_classes, "m-4"));
	margin_vertical_widget_ = bindWidget("margin.vertical.control", std::make_unique<ClassComboBox>(spacingClasses_.margin_vertical_classes));
	margin_horizontal_widget_ = bindWidget("margin.horizontal.control", std::make_unique<ClassComboBox>(spacingClasses_.margin_horizontal_classes));
	margin_top_widget_ = bindWidget("margin.top.control", std::make_unique<ClassComboBox>(spacingClasses_.margin_top_classes));
	margin_right_widget_ = bindWidget("margin.right.control", std::make_unique<ClassComboBox>(spacingClasses_.margin_right_classes));
	margin_bottom_widget_ = bindWidget("margin.bottom.control", std::make_unique<ClassComboBox>(spacingClasses_.margin_bottom_classes));
	margin_left_widget_ = bindWidget("margin.left.control", std::make_unique<ClassComboBox>(spacingClasses_.margin_left_classes));

	padding_all_widget_ = bindWidget("padding.all.control", std::make_unique<ClassComboBox>(spacingClasses_.padding_all_classes));
	padding_vertical_widget_ = bindWidget("padding.vertical.control", std::make_unique<ClassComboBox>(spacingClasses_.padding_vertical_classes));
	padding_horizontal_widget_ = bindWidget("padding.horizontal.control", std::make_unique<ClassComboBox>(spacingClasses_.padding_horizontal_classes));
	padding_top_widget_ = bindWidget("padding.top.control", std::make_unique<ClassComboBox>(spacingClasses_.padding_top_classes));
	padding_right_widget_ = bindWidget("padding.right.control", std::make_unique<ClassComboBox>(spacingClasses_.padding_right_classes));
	padding_bottom_widget_ = bindWidget("padding.bottom.control", std::make_unique<ClassComboBox>(spacingClasses_.padding_bottom_classes));
	padding_left_widget_ = bindWidget("padding.left.control", std::make_unique<ClassComboBox>(spacingClasses_.padding_left_classes));

	margin_all_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});
	margin_vertical_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});
	margin_horizontal_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});
	margin_top_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});
	margin_right_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});
	margin_bottom_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});
	margin_left_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});

	padding_all_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});
	padding_vertical_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});
	padding_horizontal_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});
	padding_top_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});
	padding_right_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});
	padding_bottom_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});
	padding_left_widget_->comboBox_->activated().connect(this, [=](){
		styleChanged_.emit(getElementStyles());
	});


};

std::string ElementStyleClasses::getElementStyles()
{
	std::string elementClasses;
	if(margin_all_widget_->getValue().compare("none") != 0){ elementClasses += margin_all_widget_->getValue() + " "; }
	if(margin_vertical_widget_->getValue().compare("none") != 0){ elementClasses += margin_vertical_widget_->getValue() + " "; }
	if(margin_horizontal_widget_->getValue().compare("none") != 0){ elementClasses += margin_horizontal_widget_->getValue() + " "; }
	if(margin_top_widget_->getValue().compare("none") != 0){ elementClasses += margin_top_widget_->getValue() + " "; }
	if(margin_right_widget_->getValue().compare("none") != 0){ elementClasses += margin_right_widget_->getValue() + " "; }
	if(margin_bottom_widget_->getValue().compare("none") != 0){ elementClasses += margin_bottom_widget_->getValue() + " "; }
	if(margin_left_widget_->getValue().compare("none") != 0){ elementClasses += margin_left_widget_->getValue() + " "; }

	if(padding_all_widget_->getValue().compare("none") != 0){ elementClasses += padding_all_widget_->getValue() + " "; }
	if(padding_vertical_widget_->getValue().compare("none") != 0){ elementClasses += padding_vertical_widget_->getValue() + " "; }
	if(padding_horizontal_widget_->getValue().compare("none") != 0){ elementClasses += padding_horizontal_widget_->getValue() + " "; }
	if(padding_top_widget_->getValue().compare("none") != 0){ elementClasses += padding_top_widget_->getValue() + " "; }
	if(padding_right_widget_->getValue().compare("none") != 0){ elementClasses += padding_right_widget_->getValue() + " "; }
	if(padding_bottom_widget_->getValue().compare("none") != 0){ elementClasses += padding_bottom_widget_->getValue() + " "; }
	if(padding_left_widget_->getValue().compare("none") != 0){ elementClasses += padding_left_widget_->getValue() + " "; }
	elementClasses += notFoundClasses;
	return elementClasses;
}

void ElementStyleClasses::setStyleClasses(std::string styleClasses)
{
	resetStyleClasses();
	std::cout << "\nElementStyleClasses::setStyleClasses \n";
	notFoundClasses = styleClasses;
	// get padding and margin classes from styleClasses
	std::string expresion = "[x,y,l,r,t,b]?-(?:96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|8|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px|[[\\S]*\\])";
	std::string padding_expresion = "p" + expresion;
	std::string margin_expresion = "m" + expresion;
	std::vector<std::string> padding_classes;
	std::vector<std::string> margin_classes;

	// add padding classes from styleClasses to padding_classes using regex
	std::regex padding_regex(padding_expresion);
	std::regex margin_regex(margin_expresion);

	// add padding classes from styleClasses to padding_classes using regex
	std::smatch padding_match;
	while (std::regex_search(styleClasses, padding_match, padding_regex)) {
		padding_classes.push_back(padding_match[0]);
		styleClasses = padding_match.suffix().str();
	}

	styleClasses = notFoundClasses;

	// add margin classes from styleClasses to margin_classes using regex
	std::smatch margin_match;
	while(std::regex_search(styleClasses, margin_match, margin_regex)){
		margin_classes.push_back(margin_match[0]);
		styleClasses = margin_match.suffix().str();
	}

	// remove the classes from margin and padding vector from notFoundClasses
	for(auto& padding_class : padding_classes){
		notFoundClasses = std::regex_replace(notFoundClasses, std::regex(padding_class), "");
	}
	for(auto& margin_class : margin_classes){
		notFoundClasses = std::regex_replace(notFoundClasses, std::regex(margin_class), "");
	}
	// remove extra whitespace from start and end
	notFoundClasses = std::regex_replace(notFoundClasses, std::regex("^\\s+"), "");
	notFoundClasses = std::regex_replace(notFoundClasses, std::regex("\\s+$"), "");


	std::cout << "\n ---- \n";
	std::cout << "styleClasses: " << styleClasses << "\n";
	std::cout << "notFoundClasses: " << notFoundClasses << "\n";
	std::cout << "\n ---- \n";

	// add padding classes to padding widgets
	for(auto& padding_class : padding_classes){
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
	// add margin classes to margin widgets
	for(auto& margin_class : margin_classes){
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

}

void ElementStyleClasses::resetStyleClasses()
{
	std::cout << "\n\n resetStyleClasses";
	padding_all_widget_->setClass("none");
	padding_vertical_widget_->setClass("none");
	padding_horizontal_widget_->setClass("none");
	padding_top_widget_->setClass("none");
	padding_right_widget_->setClass("none");
	padding_bottom_widget_->setClass("none");
	padding_left_widget_->setClass("none");
	
	margin_all_widget_->setClass("none");
	margin_vertical_widget_->setClass("none");
	margin_horizontal_widget_->setClass("none");
	margin_top_widget_->setClass("none");
	margin_right_widget_->setClass("none");
	margin_bottom_widget_->setClass("none");
	margin_left_widget_->setClass("none");
}

