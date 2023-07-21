#pragma once
#include <Wt/WTextArea.h>
#include <Wt/WLineEdit.h>
#include <Wt/WString.h>
#include <Wt/WTreeNode.h>
#include <Wt/WTemplate.h>
#include "tinyxml2.h"
#include <Wt/WDialog.h>
#include "StylusTreeView.h"



class StylusEdditor2 : public Wt::WDialog
{
public:
    StylusEdditor2(std::string fileName, std::string templateName, Wt::WTemplate* parent_template = nullptr);

    std::string cleanStringStartEnd(const std::string& input);
    std::string getNextWord(const std::string& input, size_t& currentPosition);
private:
    void parseMessageAndDoc();

    std::shared_ptr<StylusState> stylusState_;

    
    Wt::WString sourcePath_ = "resources/xml/";
    Wt::WString templateName_ = "";



    Wt::WTemplate* treeview_temp_;

    void createTitleBarControls();
    void createDialogTreeView();
    void createDialogContent();
    
    void nodeSelected(tinyxml2::XMLNode* node);
    void setDisplayElement(tinyxml2::XMLElement* element);
    
    void toggleOutline(bool on = true);
    bool outline_selected_on = true;    

    void saveStyles();

    void updateFile();
    void updateView();

};