#include "include/ComboBoxClassWithCustoms.h"
#include <iostream>
#include <regex>

ComboBoxClassWithCustoms::ComboBoxClassWithCustoms(std::vector<std::string> classNames)
{
	setStyleClass("flex justify-betwen items-center w-full");

	btn_reset_ = addWidget(std::make_unique<Wt::WPushButton>("↺"));
	auto select_container = addWidget(std::make_unique<Wt::WContainerWidget>());
	auto custom_container = addWidget(std::make_unique<Wt::WContainerWidget>());
	checkbox_custom_value_ = addWidget(std::make_unique<Wt::WCheckBox>());

	btn_prev_ = select_container->addWidget(std::make_unique<Wt::WPushButton>("<"));
	comboBox_class = select_container->addWidget(std::make_unique<Wt::WComboBox>());
	btn_next_ = select_container->addWidget(std::make_unique<Wt::WPushButton>(">"));
	lineEdit_size_custom_ = custom_container->addWidget(std::make_unique<Wt::WLineEdit>());

	btn_prev_->setThemeStyleEnabled(false);
	btn_next_->setThemeStyleEnabled(false);
	btn_reset_->setThemeStyleEnabled(false);

	std::string wrappers_styles = "flex w-full border border-gray-600 border-solid rounded-md overflow-hidden";
	select_container->setStyleClass(wrappers_styles);
	custom_container->setStyleClass(wrappers_styles);
	btn_prev_->setStyleClass("rounded-r-none rounded-l-md border-r border-gray-600 border-solid px-1 bg-neutral-800 hover:bg-neutral-900");
	btn_next_->setStyleClass("rounded-l-none rounded-r-md border-l border-gray-600 border-solid px-1 bg-neutral-800 hover:bg-neutral-900");
	btn_reset_->setStyleClass("rounded-none pr-1 m-0");
	comboBox_class->setStyleClass("p-px w-full rounded-none m-0 h-full w-full bg-neutral-800 appearance-none focus-visible:outline-none hover:bg-neutral-900");
	lineEdit_size_custom_->setStyleClass("p-px w-full ps-1 rounded-none m-0 h-full bg-neutral-800 w-full text-center appearance-none ps-1 focus-visible:outline-none hover:bg-neutral-900");
	checkbox_custom_value_->setStyleClass("ml-1");
	// iterate over classnames and add them to the combobox
	
	btn_prev_->clicked().connect(this, [=](){
		comboBox_class->setCurrentIndex(comboBox_class->currentIndex() - 1);
		comboBox_class->activated().emit(comboBox_class->currentIndex());
	});
	btn_next_->clicked().connect(this, [=](){
		comboBox_class->setCurrentIndex(comboBox_class->currentIndex() + 1);
		comboBox_class->activated().emit(comboBox_class->currentIndex());
	});
	btn_reset_->clicked().connect(this, [=](){
		checkbox_custom_value_->setChecked(false);
		checkbox_custom_value_->clicked().emit(Wt::WMouseEvent());
		comboBox_class->setCurrentIndex(comboBox_class->findText("none", Wt::MatchFlag::StringExactly));
		comboBox_class->activated().emit(comboBox_class->currentIndex());
	});

	custom_container->toggleStyleClass("hidden", true, true);

	checkbox_custom_value_->clicked().connect(this, [=](){
		if(checkbox_custom_value_->isChecked()){
			select_container->toggleStyleClass("hidden", true, true);
			custom_container->toggleStyleClass("hidden", false, true);
		}else{
			select_container->toggleStyleClass("hidden", false, true);
			custom_container->toggleStyleClass("hidden", true, true);
		}
	});

	// emit signal when something changes
	comboBox_class->activated().connect(this, [=](){
		classChanged_.emit();
	});
	lineEdit_size_custom_->enterPressed().connect(this, [=](){
		classChanged_.emit();
	});
}

void ComboBoxClassWithCustoms::setComboBoxValues(std::vector<std::string> classNames)
{
	for(auto& className : classNames){
		comboBox_class->addItem(className);
	}
	if(comboBox_class->findText("none", Wt::MatchFlag::StringExactly) == -1){
		std::cout << "\n\n none not found ========================================== \n\n";
	}
	setValue("none");
}

std::string ComboBoxClassWithCustoms::getValue()
{
	std::string selectedClass = "";

	if(checkbox_custom_value_->isChecked() && lineEdit_size_custom_->text().toUTF8() != ""){
		selectedClass = custom_start_.toUTF8() + "[" + lineEdit_size_custom_->valueText().toUTF8() + "]";
	}else{
		selectedClass = comboBox_class->currentText().toUTF8();
	}
	// std::cout << "\n selectedClass: " << selectedClass << "\n";
return selectedClass;
}

void ComboBoxClassWithCustoms::setValue(std::string className)
{
	if(className.find("]") != std::string::npos) {
		std::cout << "\n\n custom value :" << className << "\n\n";
		checkbox_custom_value_->setChecked(true);
		checkbox_custom_value_->clicked().emit(Wt::WMouseEvent());
		// find the next '[' position in className
		int pos = className.find("[");
		if(pos != std::string::npos){
			// find the next ']' position in className
			int pos2 = className.find("]");
			if(pos2 != std::string::npos){
				// get the value between '[' and ']'
				std::string value = className.substr(pos+1, pos2-pos-1);
				lineEdit_size_custom_->setText(value);
			}
		}

	}else {
		// std::cout << "\n\n default value :" << className << "\n\n";
		checkbox_custom_value_->setChecked(false);
		checkbox_custom_value_->clicked().emit(Wt::WMouseEvent());
		comboBox_class->setCurrentIndex(comboBox_class->findText(className, Wt::MatchFlag::StringExactly));
	}

}

