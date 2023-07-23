#include "include/StylusTreeView.h"

TreeNode::TreeNode(const Wt::WString& labelText, std::unique_ptr<Wt::WIconPair> labelIcon)
	: Wt::WTreeNode(labelText, std::move(labelIcon))
{
	setSelectable(true);
	setLoadPolicy(Wt::ContentLoading::NextLevel);
	label()->setTextFormat(Wt::TextFormat::Plain);
	expand();

	labelArea()->setStyleClass("flex flex-row items-center");
	// auto labelAreaStart = labelArea()->insertAfter(std::make_unique<Wt::WContainerWidget>(), label());
	auto labelAreaStart = labelArea()->addWidget(std::make_unique<Wt::WContainerWidget>());
	auto labelAreaEnd = labelArea()->addWidget(std::make_unique<Wt::WContainerWidget>());

	remove_btn = labelArea()->insertBefore(std::make_unique<Wt::WPushButton>(""), label());
	move_right_btn = labelAreaStart->addWidget(std::make_unique<Wt::WPushButton>(""));
	move_up_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WPushButton>(""));
	move_down_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WPushButton>(""));
	add_child_first_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WPushButton>(""));
	add_child_last_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WPushButton>(""));
	add_sibling_before_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WPushButton>(""));
	add_sibling_after_btn = labelAreaEnd->addWidget(std::make_unique<Wt::WPushButton>(""));

	labelAreaEnd->setStyleClass("ms-auto");
	labelAreaStart->setStyleClass("me-auto");
	Wt::WString btns_styles = "!p-2 !my-0 !ms-0 bg-cover rounded full bg-opacity-20 inline ";
	remove_btn->addStyleClass(btns_styles + " bg-[url(trash.svg)]");
	move_right_btn->addStyleClass(btns_styles + " bg-[url(arrow-right-down.svg)] me-2");
	move_up_btn->addStyleClass(btns_styles + " bg-[url(arrow-up.svg)] me-2");
	move_down_btn->addStyleClass(btns_styles + " bg-[url(arrow-down.svg)] me-2");
	add_sibling_after_btn->addStyleClass(btns_styles + " bg-[url(parent.svg)] me-2");
	add_sibling_before_btn->addStyleClass(btns_styles + " bg-[url(parent.svg)] me-2");
	add_child_first_btn->addStyleClass(btns_styles + " bg-[url(kid.svg)] me-2");
	add_child_last_btn->addStyleClass(btns_styles + " bg-[url(kid.svg)] me-2");

}

StylusTreeView::StylusTreeView(std::shared_ptr<StylusState> stylusState)
    : Wt::WTree(),
    stylusState_(stylusState)
{
    // set defaults
	setSelectionMode(Wt::SelectionMode::Single);
	addStyleClass("w-auto h-auto");


}

StylusTreeView::~StylusTreeView()
{
	// std::cout << "\n\n StylusTreeView destructor called \n\n";
}

void StylusTreeView::createTree()
{
	selectedTreeNode = nullptr;
	// tree root node
	auto rootNode = std::make_unique<TreeNode>(stylusState_->selectedTemplate->ToElement()->Attribute("id"));
	rootNode->move_up_btn->addStyleClass("hidden");
	rootNode->move_down_btn->addStyleClass("hidden");
	rootNode->move_right_btn->addStyleClass("hidden");
	rootNode->add_sibling_before_btn->addStyleClass("hidden");
	rootNode->add_sibling_after_btn->addStyleClass("hidden");
	rootNode->remove_btn->addStyleClass("hidden");
	
	rootNode->add_child_first_btn->doubleClicked().connect(this, [=](){
		addChildElementFirst(stylusState_->selectedTemplate->ToElement());
		templateModified_.emit();
	});
	rootNode->add_child_last_btn->doubleClicked().connect(this, [=](){
		addChildElementLast(stylusState_->selectedTemplate->ToElement());
        templateModified_.emit();
	});
    setTreeRoot(std::move(rootNode));


    auto element = stylusState_->selectedTemplate->FirstChildElement();
    while(element){
		selectedNodeFound = false;
        if(element->Attribute("class") == NULL){
            element->SetAttribute("class", "");
        }
		if(element->GetText() == NULL){
			element->SetText("");
		}
        treeRoot()->addChildNode(createNodeTree(element));
		selectedNodeFound = false;
        element = element->NextSiblingElement();

    }

	if(selectedTreeNode != nullptr){
		// std::cout << "\n selectedTreeNode found \n";
		select(selectedTreeNode, true);
	}else if(treeRoot()->childNodes().size() > 0) {
		// std::cout << "\n\n selectedTreeNode not found \n\n";
		select(treeRoot()->childNodes()[0],  true);
		stylusState_->selectedElement = stylusState_->selectedTemplate->FirstChildElement();
		selectionChanged_.emit(stylusState_->selectedElement);
	}else {
		select(treeRoot(), true);
		stylusState_->selectedElement = stylusState_->selectedTemplate->ToElement();
	}

}

std::unique_ptr<TreeNode> StylusTreeView::createNodeTree(tinyxml2::XMLElement* element)
{

	// std::cout << "\n StylusTreeView::createNodeTree \n";
	auto node = std::make_unique<TreeNode>(element->Name());
	auto nodePtr = node.get();
	node->selected().connect(this, [=](){
		selectionChanged_.emit(element);
		nodePtr->expand();
	});

	// signal connections for controling element
    node->move_up_btn->doubleClicked().connect(this, [=](){
        moveElementUp(element);
        templateModified_.emit();
    });
    node->move_down_btn->doubleClicked().connect(this, [=](){
        moveElementDown(element);
        templateModified_.emit();
    });
    node->add_sibling_after_btn->doubleClicked().connect(this, [=](){
        addSiblingElementAfter(element);
        templateModified_.emit();
    });
    node->add_sibling_before_btn->doubleClicked().connect(this, [=](){
        addSiblingElementBefore(element);
        templateModified_.emit();
    });
    node->add_child_first_btn->doubleClicked().connect(this, [=](){
        addChildElementFirst(element);
        templateModified_.emit();
    });
    node->add_child_last_btn->doubleClicked().connect(this, [=](){
        addChildElementLast(element);
        templateModified_.emit();
    });
    node->remove_btn->doubleClicked().connect(this, [=](){
        removeElement(element);
        templateModified_.emit();
    });

    if(element->NextSiblingElement()){
        if(element->NextSiblingElement()->FirstChildElement()){
            node->move_right_btn->doubleClicked().connect(this, [=](){
                moveElementRight(element);
                templateModified_.emit();
            });
        }else {
            node->move_right_btn->addStyleClass("hidden");
        }
    }else {
        node->move_right_btn->addStyleClass("hidden");
    }

	auto elementClass = element->Attribute("class");
	bool hasQuestionmark = std::string(elementClass).find("?") != std::string::npos;
	if(hasQuestionmark){
		selectedTreeNode = node.get();
		stylusState_->selectedElement = element;
		selectedNodeFound = true;
	}

	// Check if the element has child elements
	tinyxml2::XMLElement* child = element->FirstChildElement();
	while (child) {
		node->addChildNode(createNodeTree(child));
		child = child->NextSiblingElement();
	}

	if(!selectedNodeFound)
		node->collapse();

	return node;
}

// handle adding and removing elements
void StylusTreeView::moveElementUp(tinyxml2::XMLElement* element)
{
	std::cout << "\n StylusTreeView::moveElementUp \n";
	auto newElement = element->DeepClone(&stylusState_->doc);

	if(element->PreviousSiblingElement()){
		std::cout << "\n ----- Prev sibling valid \n\n";
		if(element->PreviousSiblingElement()->PreviousSiblingElement()){
			std::cout << "\n ----- Prev Prev sibling valid" << element->PreviousSiblingElement()->PreviousSiblingElement()->GetText() << "\n\n";
			element->Parent()->InsertAfterChild(element->PreviousSibling()->PreviousSibling(), newElement);
		}else {
			std::cout << "\n ----- Prev Prev sibling NOT valid " << " \n\n";
			element->Parent()->InsertFirstChild(newElement);
		}
	}else if(element->Parent() != stylusState_->selectedTemplate){
		std::cout << "\n ----- np previus siblings and Parent is temp message NOT \n\n";

		if(element->Parent()->PreviousSiblingElement()){
			std::cout << "\n ----- Parent has previus sibling \n\n";
			element->Parent()->Parent()->InsertAfterChild(element->Parent()->PreviousSibling(), newElement);
		}else {
			std::cout << "\n ----- Parent has NO previus sibling \n\n";
			element->Parent()->Parent()->InsertFirstChild(newElement);
		}
	}else {
		std::cout << "\n ----- no previus siblings and Parent is temp message \n\n";
		return;
	}

	stylusState_->selectedElement = newElement->ToElement();
	removeElement(element);
}

void StylusTreeView::moveElementDown(tinyxml2::XMLElement* element)
{
	std::cout << "\n StylusTreeView::moveElementDown \n";
	auto newElement = element->DeepClone(&stylusState_->doc);

	if(!element->NextSiblingElement() && element->Parent() == stylusState_->selectedTemplate)
		return;
	else if(element->NextSiblingElement()){
		element->Parent()->InsertAfterChild(element->NextSiblingElement(), newElement);
	} else {
		element->Parent()->Parent()->InsertAfterChild(element->Parent(), newElement);
	}
	stylusState_->selectedElement = newElement->ToElement();
	removeElement(element);
}

void StylusTreeView::moveElementRight(tinyxml2::XMLElement* element)
{
	std::cout << "\n StylusTreeView::moveElementRight \n";
	auto newElement = element->DeepClone(&stylusState_->doc);
	if(!element->NextSiblingElement()){
		std::cout << "\n StylusTreeView::moveElementRight but no next sibling \n";
		return;
	}
	if(!element->NextSiblingElement()->FirstChildElement()){
		std::cout << "\n\n StylusTreeView::moveElementRight but next sibling has no child \n\n";
		return;
	}
	
	element->NextSiblingElement()->InsertFirstChild(newElement);
	stylusState_->selectedElement = newElement->ToElement();	
	removeElement(element);
	
}

void StylusTreeView::addSiblingElementBefore(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement)
{
	std::cout << "\n StylusTreeView::addSiblingElementBefore \n";
	if(newElement == nullptr){
		newElement = stylusState_->doc.NewElement("div");
		newElement->SetAttribute("class", "");
		newElement->SetText("siblings before");
	}

	// add it to the selected element
	if(element->PreviousSiblingElement())
		element->Parent()->InsertAfterChild(element->PreviousSiblingElement(), newElement);
	else
		element->Parent()->InsertFirstChild(newElement);
}

void StylusTreeView::addSiblingElementAfter(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement)
{
	std::cout << "\n StylusTreeView::addSiblingElementAfter \n";
	if(newElement == nullptr){
		// create element <div class="text-center">header</div>
		newElement = stylusState_->doc.NewElement("div");
		newElement->SetAttribute("class", "");
		newElement->SetText("siblings after");
	}
	// add it to the selected element
	stylusState_->selectedElement->Parent()->InsertAfterChild(element, newElement);
}

void StylusTreeView::addChildElementFirst(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement)
{
	std::cout << "\nStylusTreeView::addChildElementFirst\n";
	if(newElement == nullptr){
		// create element <div class="text-center">header</div>
		newElement = stylusState_->doc.NewElement("div");
		newElement->SetAttribute("class", "");
		newElement->SetText("child before");
	}
	// add it to the selected element
	element->InsertFirstChild(newElement);

	if(element == stylusState_->selectedTemplate->ToElement()){
		stylusState_->selectedElement = newElement;
	}
}

void StylusTreeView::addChildElementLast(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement)
{
	std::cout << "\nStylusTreeView::addChildElementLast\n";	
	if(newElement == nullptr){
		// create element <div class="text-center">header</div>
		newElement = stylusState_->doc.NewElement("div");
		newElement->SetAttribute("class", "");
		newElement->SetText("child after");
	}
	element->InsertEndChild(newElement);

	if(element == stylusState_->selectedTemplate->ToElement()){
		stylusState_->selectedElement = newElement;
	}

}

void StylusTreeView::removeElement(tinyxml2::XMLElement* element)
{
	std::cout << "\n StylusTreeView::removeElement \n";
    stylusState_->doc.DeleteNode(element);
	stylusState_->selectedElement = nullptr;
}