#include "include/TemplateEditorDialog.h"
#include <Wt/WTree.h>
#include <Wt/WApplication.h>
#include <Wt/WDialog.h>
#include <Wt/WTemplate.h>
#include <Wt/WTreeNode.h>
#include <iostream>

TemplateEditorDialog::TemplateEditorDialog(std::string fileName, std::string templateName)
{
    setText("Stylus");
    setStyleClass("absolute -top-[15px] left-1/2 -translate-x-1/2 opacity-20 hover:opacity-60");
    sourcePath_ += fileName + ".xml";
    templateName_ = templateName;   

	clicked().connect(this, &TemplateEditorDialog::createDialog);
    
    createDialog();
}

TemplateEditorDialog::~TemplateEditorDialog()
{
}

void TemplateEditorDialog::createDialog()
{
	auto dialog = Wt::WApplication::instance()->addChild(std::make_unique<Wt::WDialog>("Modifier"));
	dialog->rejectWhenEscapePressed();
	dialog->setModal(false);
	dialog->setResizable(true);

	dialogTemp_ = dialog->contents()->addWidget(std::make_unique<Wt::WTemplate>(tr("stylus-dialog-template")));
    createDialogContent();

    dialog->finished().connect([=] {
        std::string selectedClasses = selectedElement->Attribute("class");
        auto found = selectedClasses.find("? ");
        while(found){
            selectedClasses.erase(found, 2);
            found = selectedClasses.find("? ");    
        }
        updateElementStyles(selectedClasses);

    });

	dialog->setHidden(false, Wt::WAnimation(Wt::AnimationEffect::SlideInFromTop, Wt::TimingFunction::Linear, 200));

}

void TemplateEditorDialog::createDialogContent()
{
    parseMessageAndDoc();
	auto saveBtn = dialogTemp_->bindWidget("save-elem-btn", std::make_unique<Wt::WPushButton>("Save"));
	auto add_sibling_element = dialogTemp_->bindWidget("add-elem-sibling-btn", std::make_unique<Wt::WPushButton>("+ sibling"));
	auto add_child_element = dialogTemp_->bindWidget("add-elem-child-btn", std::make_unique<Wt::WPushButton>("+ child"));
	auto remove_element = dialogTemp_->bindWidget("delete-elem-btn", std::make_unique<Wt::WPushButton>("- delete"));

	saveBtn->clicked().connect(this, &TemplateEditorDialog::saveStyles);
	add_sibling_element->clicked().connect(this, &TemplateEditorDialog::addSiblingElement);
	add_child_element->clicked().connect(this, &TemplateEditorDialog::addChildElement);
	remove_element->clicked().connect(this, &TemplateEditorDialog::removeElement);

	// stylus tree here
	auto tree = dialogTemp_->bindWidget("tree-view", std::make_unique<Wt::WTree>());
	tree->addStyleClass("max-w-[125px] min-w-[125px]");
	tree->setSelectionMode(Wt::SelectionMode::Single);
	
	auto rootPtr = std::make_unique<Wt::WTreeNode>(templateName_); 

	selectedElement = tempMessage->FirstChildElement();
    bool firstChildCheck = true;
    Wt::WTreeNode* firstChildNode;
    auto nextChild = selectedElement->NextSiblingElement();
    while(nextChild){
        if(firstChildCheck){
            firstChildNode = rootPtr->addChildNode(createNodeTree(selectedElement));
            firstChildCheck = false;
        }
        rootPtr->addChildNode(createNodeTree(nextChild));
        nextChild = nextChild->NextSiblingElement();
    }
    // createNodeTree();
	Wt::WTreeNode *root = rootPtr.get(); 
	tree->setTreeRoot(std::move(rootPtr));
	root->setSelectable(false); 
	root->label()->setTextFormat(Wt::TextFormat::Plain);
	root->setLoadPolicy(Wt::ContentLoading::NextLevel);
	root->expand();	
	
	tree->select(firstChildNode);

	// text areas for default and dark classes
	default_styles_textarea_ = dialogTemp_->bindWidget("default-styles", std::make_unique<Wt::WTextArea>());
	dark_styles_textarea_ = dialogTemp_->bindWidget("dark-styles", std::make_unique<Wt::WTextArea>());

}

std::unique_ptr<Wt::WTreeNode> TemplateEditorDialog::createNodeTree(tinyxml2::XMLElement* element)
{
	std::unique_ptr<Wt::WTreeNode> node;
	// if(strcmp(element->Name(), "message") == 0){
		// node = std::make_unique<Wt::WTreeNode>(templateName_);
	// }else {
    node = std::make_unique<Wt::WTreeNode>(element->Name());
	// }
    // element->SetAttribute("class", " ");
	node->label()->setTextFormat(Wt::TextFormat::Plain);
	node->setLoadPolicy(Wt::ContentLoading::NextLevel);

	// Check if the element has child elements
	tinyxml2::XMLElement* child = element->FirstChildElement();
	if (child) {
        
		// child valid and node can be added
		while (child) {
			auto nodePtr = node->addChildNode(createNodeTree(child));
			nodePtr->selected().connect(this, [=](){ 
				std::string classString = selectedElement->Attribute("class");
				// remove whitespace from start 
				while(classString[0] == ' ' && classString.size() > 0){
					classString.erase(0, 1);
				}
				// search to see if the selected element has "?" class
				// if it does, remove it
				auto found = classString.find("?");
				if(found != std::string::npos){
					classString.erase(found, 2);
					updateElementStyles(classString);
				}
				selectedElement = child;
				classString = selectedElement->Attribute("class");
				updateElementStyles("? " + classString);
				setElement(selectedElement);
			});
			child = child->NextSiblingElement();
		}
	} else {
	}
	return node;
}

void TemplateEditorDialog::parseMessageAndDoc()
{
	auto result = doc.LoadFile(sourcePath_.toUTF8().c_str());
	if(result != tinyxml2::XML_SUCCESS){
		std::cout << "\n\n error opening document of the message template \n\n";
	}
	tinyxml2::XMLElement* root = doc.RootElement();
	if(!root) {
		std::cout << "\n\n error getting root element of the message template \n\n";
	}
	tempMessage = root->FirstChildElement("message");
	while(tempMessage->Attribute("id") != templateName_.toUTF8()){
		tempMessage = tempMessage->NextSiblingElement("message");
	}
}



void TemplateEditorDialog::addSiblingElement()
{
	std::cout << "\n\n add sibling element got called \n\n";
    selectedElement->Parent()->InsertEndChild(doc.NewElement("div"));
    doc.SaveFile(sourcePath_.toUTF8().c_str());
    auto app  = Wt::WApplication::instance();
    app->messageResourceBundle().keys("");
    app->refresh();
    createDialogContent();
}

void TemplateEditorDialog::addChildElement()
{
	std::cout << "\n\n add child element got called \n\n";
    selectedElement->InsertNewChildElement("asta");
    doc.SaveFile(sourcePath_.toUTF8().c_str());
    auto app  = Wt::WApplication::instance();
    app->messageResourceBundle().keys("");
    app->refresh();
    createDialogContent();
}

void TemplateEditorDialog::removeElement()
{
	std::cout << "\n\n remove element got called \n\n";
    doc.DeleteNode(selectedElement);
    doc.SaveFile(sourcePath_.toUTF8().c_str());
    auto app  = Wt::WApplication::instance();
    app->messageResourceBundle().keys("");
    app->refresh();
    createDialogContent();
}


void TemplateEditorDialog::saveStyles()
{
	auto darkClasses = dark_styles_textarea_->text().toUTF8();
	auto defaultClasses = default_styles_textarea_->text().toUTF8();
	auto darkPrefix = "dark:";
	std::vector<std::string> darkClassesVec;
	// replace newline with whitespace
	for(auto& c : defaultClasses){
		if(c == '\n'){
			c = ' ';
		}
	}
	std::string temp;
	for(auto& c : darkClasses){
		if(c == '\n'){
			c = ' ';
		}
	}
	// trim whitespace from the start
	while(defaultClasses[0] == ' '){
		defaultClasses.erase(0, 1);
	}
	while(darkClasses[0] == ' '){
		darkClasses.erase(0, 1);
	}
	// trim whitespace from the end
	while(darkClasses[darkClasses.size() - 1] == ' '){
		darkClasses.erase(darkClasses.size() - 1, 1);
	}
	// separate the dark classes by whitespace
	for(auto c : darkClasses){
		if(c == ' '){
			darkClassesVec.push_back(darkPrefix + temp);
			temp = "";
		}else{
			temp += c;
		}
	}


	// recreate darkClasses string 
	darkClasses = "";
	for(auto c : darkClassesVec){
		darkClasses += c + " ";
	}

	std::string elementStyles = defaultClasses + darkClasses;
	
	updateElementStyles(elementStyles);
}

void TemplateEditorDialog::setElement(tinyxml2::XMLElement* element)
{
	std::string classString = element->Attribute("class");

	// separate the classString by witespace
	std::vector<std::string> classes;
	std::vector<std::string> defaultClasses;
    std::vector<std::string> darkClasses;

	std::string temp;
	for(auto c : classString){
		if(c == ' '){
			classes.push_back(temp);
			temp = "";
		}else{
			temp += c;
		}
	}
	classes.push_back(temp);

	// separate the classes with 'dark:' at the start into the darkString
	// and the rest into the defaultString
	for(auto c : classes){
		if(c.substr(0, 5) == "dark:"){
			darkClasses.push_back(c.substr(5) + "\n");
		}else{
			defaultClasses.push_back(c + "\n");
		}
	}

	std::string darkString;
	std::string defaultString;

	for(auto c : darkClasses){
		darkString += c;
	}
	for(auto c : defaultClasses){
		defaultString += c;
	}

	default_styles_textarea_->setText(defaultString);
	dark_styles_textarea_->setText(darkString);
}

void TemplateEditorDialog::updateElementStyles(std::string elementStyles)
{
	std::cout << "\n\n element styles: " << elementStyles << "\n\n";
	selectedElement->SetAttribute("class", elementStyles.c_str());
	doc.SaveFile(sourcePath_.toUTF8().c_str());
	auto app  = Wt::WApplication::instance();
	app->messageResourceBundle().keys("");
	app->refresh();
}

