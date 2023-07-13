// #include "include/TailwindTemplate.h"
// #include <Wt/WPushButton.h>
// #include <Wt/WApplication.h>
// #include <Wt/WMessageResourceBundle.h>
// #include <Wt/WContainerWidget.h>
// #include <Wt/WLocale.h>
// #include <Wt/WDialog.h>
// #include <Wt/WText.h>
// #include <Wt/WTree.h>

// TailwindTemplate::TailwindTemplate()
// {
// 	std::cout << "\n\n test template constructor \n\n";

// 	setTemplateText(tr(templateName.toUTF8()));
// 	setCondition("first", true);
// 	setStyleClass("m-5 bg-green-200 min-h-[500px]");
// 	auto controls = bindWidget("controls", createControlsBar());

// 	parseMessageAndDoc();	
// 	createModifierDialog();

// }

// void TailwindTemplate::parseMessageAndDoc()
// {
// 	auto result = doc.LoadFile(sourcePath.toUTF8().c_str());
// 	if(result != tinyxml2::XML_SUCCESS){
// 		std::cout << "\n\n error opening document of the message template \n\n";
// 	}
// 	tinyxml2::XMLElement* root = doc.RootElement();
// 	if(!root) {
// 		std::cout << "\n\n error getting root element of the message template \n\n";
// 	}
// 	tempMessage = root->FirstChildElement("message");
// 	while(tempMessage->Attribute("id") != templateName.toUTF8()){
// 		tempMessage = tempMessage->NextSiblingElement("message");
// 	}
// }

// TailwindTemplate::~TailwindTemplate()
// {
// 	std::string selectedElementStyles = selectedElement->Attribute("class");
// 	auto found = selectedElementStyles.find("? ");
// 	while(found){
// 		selectedElementStyles.erase(found, 2);
// 		found = selectedElementStyles.find("? ");
// 	}
// 	updateElementStyles(selectedElementStyles);
// }

// std::unique_ptr<Wt::WContainerWidget> TailwindTemplate::createControlsBar()
// {
// 	auto controls = std::make_unique<Wt::WContainerWidget>();
	
// 	if(!hasStyleClass("relative")) addStyleClass("relative");
// 	controls->setStyleClass("absolute -top-[15px] left-1/2 -translate-x-1/2 opacity-20 hover:opacity-60");
// 	auto openStylesBtn = controls->addWidget(std::make_unique<Wt::WPushButton>("stylus"));


// 	openStylesBtn->clicked().connect(this, &TailwindTemplate::createModifierDialog);
// 	return controls;
// }

// void TailwindTemplate::createModifierDialog()
// {
// 	auto dialog = Wt::WApplication::instance()->addChild(std::make_unique<Wt::WDialog>("Modifier"));
// 	dialog->rejectWhenEscapePressed();
// 	dialog->setModal(false);
// 	dialog->setResizable(true);

// 	auto dialogTemp = dialog->contents()->addWidget(std::make_unique<Wt::WTemplate>(tr("stylus-dialog-template")));

// 	auto saveBtn = dialogTemp->bindWidget("save-elem-btn", std::make_unique<Wt::WPushButton>("Save"));
// 	auto add_sibling_element = dialogTemp->bindWidget("add-elem-sibling-btn", std::make_unique<Wt::WPushButton>("+ sibling"));
// 	auto add_child_element = dialogTemp->bindWidget("add-elem-child-btn", std::make_unique<Wt::WPushButton>("+ child"));
// 	auto remove_element = dialogTemp->bindWidget("delete-elem-btn", std::make_unique<Wt::WPushButton>("- delete"));

// 	saveBtn->clicked().connect(this, &TailwindTemplate::saveStyles);
// 	add_sibling_element->clicked().connect(this, &TailwindTemplate::addSiblingElement);
// 	add_child_element->clicked().connect(this, &TailwindTemplate::addChildElement);
// 	remove_element->clicked().connect(this, &TailwindTemplate::removeElement);

// 	// stylus tree here
// 	auto tree = dialogTemp->bindWidget("tree-view", std::make_unique<Wt::WTree>());
// 	tree->addStyleClass("max-w-[125px] min-w-[125px]");
// 	tree->setSelectionMode(Wt::SelectionMode::Single);
	

// 	selectedElement = tempMessage->NextSiblingElement();
// 	auto rootPtr = createNodeTree(tempMessage);
// 	Wt::WTreeNode *root = rootPtr.get(); 
// 	tree->setTreeRoot(std::move(rootPtr));
// 	// root->setSelectable(false); 
// 	root->label()->setTextFormat(Wt::TextFormat::Plain);
// 	root->setLoadPolicy(Wt::ContentLoading::NextLevel);
// 	root->expand();	
	
// 	tree->select(root);

// 	// text areas for default and dark classes
// 	default_styles = dialogTemp->bindWidget("default-styles", std::make_unique<Wt::WTextArea>());
// 	dark_styles = dialogTemp->bindWidget("dark-styles", std::make_unique<Wt::WTextArea>());

// 	dialog->setHidden(false, Wt::WAnimation(Wt::AnimationEffect::SlideInFromTop, Wt::TimingFunction::Linear, 200));
// }

// std::unique_ptr<Wt::WTreeNode> TailwindTemplate::createNodeTree(tinyxml2::XMLElement* element)
// {
// 	std::unique_ptr<Wt::WTreeNode> node;
// 	if(strcmp(element->Name(), "message") == 0){
// 		node = std::make_unique<Wt::WTreeNode>(templateName);
// 	}else {
// 		node = std::make_unique<Wt::WTreeNode>(element->Name());
// 	}

// 	node->label()->setTextFormat(Wt::TextFormat::Plain);
// 	node->setLoadPolicy(Wt::ContentLoading::NextLevel);

// 	// Check if the element has child elements
// 	tinyxml2::XMLElement* child = element->FirstChildElement();
// 	if (child) {

// 		// child valid and node can be added
// 		while (child) {
// 			auto nodePtr = node->addChildNode(createNodeTree(child));
// 			nodePtr->selected().connect(this, [=](){ 
// 				std::string classString = selectedElement->Attribute("class");
// 				// remove whitespace from start 
// 				while(classString[0] == ' '){
// 					classString.erase(0, 1);
// 				}
// 				// search to see if the selected element has "?" class
// 				// if it does, remove it
// 				auto found = classString.find("?");
// 				if(found != std::string::npos){
// 					classString.erase(found, 2);
// 					updateElementStyles(classString);
// 				}
// 				selectedElement = child;
// 				classString = selectedElement->Attribute("class");
// 				updateElementStyles("? " + classString);
// 				setElement(selectedElement);
// 			});
// 			child = child->NextSiblingElement();
// 		}
// 	} else {
// 	}
// 	return node;
// }

// void TailwindTemplate::saveStyles()
// {
// 	auto darkClasses = dark_styles->text().toUTF8();
// 	auto defaultClasses = default_styles->text().toUTF8();
// 	auto darkPrefix = "dark:";
// 	std::vector<std::string> darkClassesVec;
// 	// replace newline with whitespace
// 	for(auto& c : defaultClasses){
// 		if(c == '\n'){
// 			c = ' ';
// 		}
// 	}
// 	std::string temp;
// 	for(auto& c : darkClasses){
// 		if(c == '\n'){
// 			c = ' ';
// 		}
// 	}
// 	// trim whitespace from the start
// 	while(defaultClasses[0] == ' '){
// 		defaultClasses.erase(0, 1);
// 	}
// 	while(darkClasses[0] == ' '){
// 		darkClasses.erase(0, 1);
// 	}
// 	// trim whitespace from the end
// 	while(darkClasses[darkClasses.size() - 1] == ' '){
// 		darkClasses.erase(darkClasses.size() - 1, 1);
// 	}
// 	// separate the dark classes by whitespace
// 	for(auto c : darkClasses){
// 		if(c == ' '){
// 			darkClassesVec.push_back(darkPrefix + temp);
// 			temp = "";
// 		}else{
// 			temp += c;
// 		}
// 	}


// 	// recreate darkClasses string 
// 	darkClasses = "";
// 	for(auto c : darkClassesVec){
// 		darkClasses += c + " ";
// 	}

// 	std::string elementStyles = defaultClasses + darkClasses;
	
// 	updateElementStyles(elementStyles);
// }

// void TailwindTemplate::setElement(tinyxml2::XMLElement* element)
// {
// 	std::string classString = element->Attribute("class");

// 	// separate the classString by witespace
// 	std::vector<std::string> classes;
// 	std::vector<std::string> defaultClasses;
//     std::vector<std::string> darkClasses;

// 	std::string temp;
// 	for(auto c : classString){
// 		if(c == ' '){
// 			classes.push_back(temp);
// 			temp = "";
// 		}else{
// 			temp += c;
// 		}
// 	}
// 	classes.push_back(temp);

// 	// separate the classes with 'dark:' at the start into the darkString
// 	// and the rest into the defaultString
// 	for(auto c : classes){
// 		if(c.substr(0, 5) == "dark:"){
// 			darkClasses.push_back(c.substr(5) + "\n");
// 		}else{
// 			defaultClasses.push_back(c + "\n");
// 		}
// 	}

// 	std::string darkString;
// 	std::string defaultString;

// 	for(auto c : darkClasses){
// 		darkString += c;
// 	}
// 	for(auto c : defaultClasses){
// 		defaultString += c;
// 	}

// 	default_styles->setText(defaultString);
// 	dark_styles->setText(darkString);
// }

// void TailwindTemplate::updateElementStyles(std::string elementStyles)
// {
// 	std::cout << "\n\n element styles: " << elementStyles << "\n\n";
// 	selectedElement->SetAttribute("class", elementStyles.c_str());
// 	doc.SaveFile(sourcePath.toUTF8().c_str());
// 	auto app  = Wt::WApplication::instance();
// 	app->messageResourceBundle().keys("");
// 	app->refresh();
// }




// void TailwindTemplate::addSiblingElement()
// {
// 	std::cout << "\n\n add sibling element got called \n\n";
// }

// void TailwindTemplate::addChildElement()
// {
// 	std::cout << "\n\n add child element got called \n\n";
// }

// void TailwindTemplate::removeElement()
// {
// 	std::cout << "\n\n remove element got called \n\n";
// }



// 	// auto testBtn = elemStyles->addWidget(std::make_unique<Wt::WPushButton>("test"));

// 	// testBtn->clicked().connect(this, [=](){
// 	// 	auto div = tempMessage->FirstChildElement();
// 	// 	div->SetText("test from dialog");
// 	// 	doc.SaveFile(sourcePath.toUTF8().c_str());

// 	// 	auto app  = Wt::WApplication::instance();
// 	// 	Wt::WLocale locale = app->locale();

// 	// 	app->messageResourceBundle().keys("");
// 	// 	app->refresh();
// 	// });