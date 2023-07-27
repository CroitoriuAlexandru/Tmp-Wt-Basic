#pragma once
#include "StylusTreeView.h"
#include "ElementClassEdditor.h"

#include <Wt/WTextArea.h>
#include <Wt/WLineEdit.h>
#include <Wt/WString.h>
#include <Wt/WTreeNode.h>
#include <Wt/WTemplate.h>
#include "tinyxml2.h"
#include <Wt/WDialog.h>
#include <fstream>
#include <iostream>

class StylusEdditor2 : public Wt::WDialog
{
public:
    StylusEdditor2(std::string fileName, std::string templateName, Wt::WTemplate* parent_template = nullptr);
    ~StylusEdditor2();
    std::string cleanStringStartEnd(const std::string& input);
    std::string getNextWord(const std::string& input, size_t& currentPosition);

private:
    void parseMessageAndDoc();

    std::shared_ptr<StylusState> stylusState_;
    ElementClassEdditor* elementClassEdditor_;

    Wt::WString sourcePath_ = "resources/xml/";

    Wt::WString templateName_ = "";
    Wt::WTemplate* treeview_temp_;

    void createTitleBarControls();
    void createDialogTreeView();
    void createDialogContent();
    
    void nodeSelected(tinyxml2::XMLNode* node);
    void updateDisplayElement();
    
    void toggleOutline(bool on = true);
    bool outline_selected_on = true;    

    void saveStyles(std::string newStyles);

    void updateFile();
    void updateView();
    void dialogResized(int width, int height);
    int applicationWidthClass;
    std::unique_ptr<Wt::WPushButton> createThemeSwitcher();
};