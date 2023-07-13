#pragma once
#include <Wt/WPushButton.h>
#include <Wt/WTextArea.h>
#include <Wt/WString.h>
#include <Wt/WTreeNode.h>
#include <Wt/WTemplate.h>
#include "tinyxml2.h"

class TemplateEditorDialog : public Wt::WPushButton
{
public:
    TemplateEditorDialog(std::string fileName, std::string templateName);
    ~TemplateEditorDialog();
private:
    void parseMessageAndDoc();
    Wt::WTextArea* default_styles_textarea_;
    Wt::WTextArea* dark_styles_textarea_;

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* tempMessage;

    tinyxml2::XMLElement* selectedElement;

    Wt::WString sourcePath_ = "resources/templates/";
    Wt::WString templateName_ = "";

    void createDialog();
    Wt::WTemplate* dialogTemp_;
    void createDialogContent();
    
    std::unique_ptr<Wt::WTreeNode> createNodeTree(tinyxml2::XMLElement* element);
    void updateElementStyles(std::string elementStyles);

    void saveStyles();
    void setElement(tinyxml2::XMLElement* element);
    
    void addSiblingElement();
    void addChildElement();
    void removeElement();
};