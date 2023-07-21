#include "include/StylusEdditor2.h"
#include <Wt/WTree.h>
#include <Wt/WApplication.h>
#include <Wt/WTemplate.h>
#include <Wt/WTreeNode.h>
#include <iostream>
#include <Wt/WCheckBox.h>
#include <Wt/WPushButton.h>



StylusClassComboBox::StylusClassComboBox(std::vector<std::string> classNames)
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
	// comboBox_->se
	// iterate over classnames and add them to the combobox
	for(auto& className : classNames){
		comboBox_->addItem(className);
	}
	btn_prev_->clicked().connect(this, [=](){
		comboBox_->setCurrentIndex(comboBox_->currentIndex() - 1);
	});
	btn_next_->clicked().connect(this, [=](){
		comboBox_->setCurrentIndex(comboBox_->currentIndex() + 1);
	});
}


// some utilities
std::string StylusEdditor2::getNextWord(const std::string& input, size_t& currentPosition) {
    std::stringstream ss(input.substr(currentPosition));
    std::string word;
    ss >> word;
    currentPosition += word.length(); // +1 to account for the space or newline character
    return word;
}

std::string StylusEdditor2::cleanStringStartEnd(const std::string& input)
{
	std::string newString = input;
	auto found = newString.find("?");
	while(found != std::string::npos){
		newString.erase(found, 1);
		found = newString.find("?");
	}
	// remove newline from start
	while(newString[0] == '\n'){
		newString.erase(0, 1);
	}
	// remove newline from the end
	while(newString[newString.size() - 1] == '\n'){
		newString.erase(newString.size() - 1, 1);
	}
	// remove whitespace from start
	while(newString[0] == ' '){
		newString.erase(0, 1);
	}
	// remove whitespace from the end
	while(newString[newString.size() - 1] == ' '){
		newString.erase(newString.size() - 1, 1);
	}
	return newString;
}

StylusEdditor2::StylusEdditor2(std::string fileName, std::string templateName, Wt::WTemplate* parent_template)
{

	setStyleClass("stylus w-[320px] h-[100vh]");
	setMinimumSize(300, 300);
	setMaximumSize(Wt::WLength(500, Wt::LengthUnit::Pixel), Wt::WLength(100, Wt::LengthUnit::ViewportHeight));
	setOffsets(0, Wt::Side::Top | Wt::Side::Left | Wt::Side::Bottom);
	setOffsets(Wt::WLength::Auto, Wt::Side::Right);
	Wt::WApplication::instance()->root()->toggleStyleClass("ms-[340px]", true, true);

    sourcePath_ += fileName;
    templateName_ = templateName;

	// rejectWhenEscapePressed();
	setModal(false);
	setMovable(false);
	setResizable(false);

	titleBar()->clear();

	treeview_temp_ = titleBar()->addWidget(std::make_unique<Wt::WTemplate>(tr("stylus2.edditor")));
	titleBar()->setStyleClass("!p-0");

	parseMessageAndDoc();
	createTitleBarControls();
	createDialogTreeView();
    createDialogContent();
	
	updateFile();
	updateView();
	
	setHidden(false, Wt::WAnimation(Wt::AnimationEffect::SlideInFromRight, Wt::TimingFunction::Linear, 350));


}

// get the correct message from the xml file and template id (message id)
void StylusEdditor2::parseMessageAndDoc()
{
	std::cout << "\n\n parse message and doc got called with path " << sourcePath_ << "\n\n";
	stylusState_ = std::make_shared<StylusState>();
	auto result = stylusState_->doc.LoadFile(sourcePath_.toUTF8().c_str());
	if(result != tinyxml2::XML_SUCCESS){
		std::cout << "\n\n STYLUS EDDITOR error opening xml file \n\n";
		std::cout << " file path: " << sourcePath_.toUTF8() << "\n\n";
		return;
	}
	tinyxml2::XMLElement* root = stylusState_->doc.RootElement();
	if(!root) {
		std::cout << "\n\n STYLUS EDDITOR error getting <messages> element \n\n";
		return;
	}
	stylusState_->selectedTemplate = root->FirstChildElement("message");
	while(stylusState_->selectedTemplate->ToElement()->Attribute("id") != templateName_.toUTF8()){
		stylusState_->selectedTemplate = stylusState_->selectedTemplate->NextSiblingElement("message");
	}
	std::cout << "\n\n STYLUS EDDITOR found template with id: " << templateName_.toUTF8() << "\n\n";

}

void StylusEdditor2::createTitleBarControls()
{
	auto move_left_btn = treeview_temp_->bindWidget("move-left-btn", std::make_unique<Wt::WPushButton>());
	auto move_right_btn = treeview_temp_->bindWidget("move-right-btn", std::make_unique<Wt::WPushButton>());
	auto refresh_btn = treeview_temp_->bindWidget("refresh-btn", std::make_unique<Wt::WPushButton>());

	move_left_btn->setDisabled(true);

	move_left_btn->clicked().connect(this, [=](){
		move_left_btn->setDisabled(true);
		move_right_btn->setDisabled(false);
		setOffsets(0, Wt::Side::Top | Wt::Side::Left | Wt::Side::Bottom);
		setOffsets(Wt::WLength::Auto, Wt::Side::Right);
		Wt::WApplication::instance()->root()->toggleStyleClass("me-[340px]", false, true);
		Wt::WApplication::instance()->root()->toggleStyleClass("ms-[340px]", true, true);
	});

	move_right_btn->clicked().connect(this, [=](){
		move_left_btn->setDisabled(false);
		move_right_btn->setDisabled(true);
		setOffsets(0, Wt::Side::Top | Wt::Side::Right | Wt::Side::Bottom);
		setOffsets(Wt::WLength::Auto, Wt::Side::Left);
		Wt::WApplication::instance()->root()->toggleStyleClass("ms-[340px]", false, true);
		Wt::WApplication::instance()->root()->toggleStyleClass("me-[340px]", true, true);
	});

	refresh_btn->clicked().connect(this, [=](){
		createDialogTreeView();
	});

}

void StylusEdditor2::createDialogTreeView()
{
	auto treeView = treeview_temp_->bindWidget("tree-view", std::make_unique<StylusTreeView>(stylusState_));
	treeView->templateModified().connect(this, [=](){
		updateFile();
		updateView();
		createDialogTreeView();
	});
	treeView->selectionChanged().connect(this, &StylusEdditor2::nodeSelected);
}

void StylusEdditor2::createDialogContent()
{
	std::vector<std::string> spacingSteps = { "px", "0", "1", "1.5", "2", "2.5", "3", "3.5", "4", "5", "6", "8", "10", "11", "12", "14", "16", "20", "24", "28", "32", "36", "40", "44", "48", "52", "56", "64", "72", "80", "96" };
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

	// create posible classes for margin and padding
	for(auto& step : spacingSteps){
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
	}

	auto margin_padding_edditor = treeview_temp_->bindWidget("stylus2.edditor.margin.padding", std::make_unique<Wt::WTemplate>(tr("stylus2.edditor.margin.padding")));

	auto margin_top = margin_padding_edditor->bindWidget("margin.top.control", std::make_unique<StylusClassComboBox>(margin_top_classes));
	auto margin_right = margin_padding_edditor->bindWidget("margin.right.control", std::make_unique<StylusClassComboBox>(margin_right_classes));
	auto margin_bottom = margin_padding_edditor->bindWidget("margin.bottom.control", std::make_unique<StylusClassComboBox>(margin_bottom_classes));
	auto margin_left = margin_padding_edditor->bindWidget("margin.left.control", std::make_unique<StylusClassComboBox>(margin_left_classes));
	auto margin_vertical = margin_padding_edditor->bindWidget("margin.vertical.control", std::make_unique<StylusClassComboBox>(margin_vertical_classes));
	auto margin_horizontal = margin_padding_edditor->bindWidget("margin.horizontal.control", std::make_unique<StylusClassComboBox>(margin_horizontal_classes));
	auto margin_all = margin_padding_edditor->bindWidget("margin.all.control", std::make_unique<StylusClassComboBox>(margin_all_classes));

	auto padding_top = margin_padding_edditor->bindWidget("padding.top.control", std::make_unique<StylusClassComboBox>(padding_top_classes));
	auto padding_right = margin_padding_edditor->bindWidget("padding.right.control", std::make_unique<StylusClassComboBox>(padding_right_classes));
	auto padding_bottom = margin_padding_edditor->bindWidget("padding.bottom.control", std::make_unique<StylusClassComboBox>(padding_bottom_classes));
	auto padding_left = margin_padding_edditor->bindWidget("padding.left.control", std::make_unique<StylusClassComboBox>(padding_left_classes));
	auto padding_vertical = margin_padding_edditor->bindWidget("padding.vertical.control", std::make_unique<StylusClassComboBox>(padding_vertical_classes));
	auto padding_horizontal = margin_padding_edditor->bindWidget("padding.horizontal.control", std::make_unique<StylusClassComboBox>(padding_horizontal_classes));
	auto padding_all = margin_padding_edditor->bindWidget("padding.all.control", std::make_unique<StylusClassComboBox>(padding_all_classes));


}

void StylusEdditor2::nodeSelected(tinyxml2::XMLNode* node)
{
	std::cout << "\n\n node selected \n\n";
	if(outline_selected_on){
		toggleOutline(false);
		stylusState_->selectedElement = node->ToElement();
		toggleOutline(true);
		updateFile();
		updateView();
	}else {
		stylusState_->selectedElement = node->ToElement();
	}

	// setDisplayElement(node->ToElement());
}

void StylusEdditor2::toggleOutline(bool on)
{
	std::string currentStyles = cleanStringStartEnd(stylusState_->selectedElement->ToElement()->Attribute("class"));

	if(on){
		currentStyles = "? " + currentStyles;
	}else {
		currentStyles = cleanStringStartEnd(currentStyles);
	}

	stylusState_->selectedElement->ToElement()->SetAttribute("class", currentStyles.c_str());

}


void StylusEdditor2::saveStyles()
{
	

	// selectedElement->SetAttribute("class", elementStyles.c_str());
	// updateFile();
	// updateView();
	// setDisplayElement(element);
}


// set element display from element xml
void StylusEdditor2::setDisplayElement(tinyxml2::XMLElement* element)
{

	// std::string classString = cleanStringStartEnd(element->Attribute("class"));
	// std::string defaultClasses_string = "";
	// std::string defaultHoverClasses_string = "";
	// std::string darkClasses_string = "";
	// std::string darkHoverClasses_string = "";
	// std::cout << "\n\n class string: " << classString << "\n\n";

}

// update file and view
void StylusEdditor2::updateFile()
{
	stylusState_->doc.SaveFile(sourcePath_.toUTF8().c_str());
}

void StylusEdditor2::updateView()
{
	auto app  = Wt::WApplication::instance();
	app->messageResourceBundle().keys("");
	app->refresh();
}


