#pragma once
#include <Wt/WTree.h>
#include <Wt/WTreeNode.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>

#include "tinyxml2.h"
#include <Wt/WSignal.h>

struct StylusState {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLNode* selectedTemplate;
    tinyxml2::XMLElement* selectedElement;
};

class TreeNode : public Wt::WTreeNode
{
public:
    TreeNode(const Wt::WString& labelText, std::unique_ptr<Wt::WIconPair> labelIcon = nullptr);
    Wt::WPushButton* move_up_btn;
    Wt::WPushButton* move_down_btn;
    Wt::WPushButton* move_right_btn;
    Wt::WPushButton* add_sibling_after_btn;
    Wt::WPushButton* add_sibling_before_btn;
    Wt::WPushButton* add_child_first_btn;
    Wt::WPushButton* add_child_last_btn;
    Wt::WPushButton* remove_btn;
protected:
private:
};


class StylusTreeView : public Wt::WTree
{
public:
    StylusTreeView(std::shared_ptr<StylusState> stylusState);
    ~StylusTreeView();
    Wt::WTreeNode* selectedTreeNode;
    bool selectedNodeFound;
    
    Wt::Signal<>& templateModified() { return templateModified_; }
    Wt::Signal<tinyxml2::XMLElement*>& selectionChanged() { return selectionChanged_; }

    void createTree();
    std::unique_ptr<TreeNode> createNodeTree(tinyxml2::XMLElement* element);
private:
    std::shared_ptr<StylusState> stylusState_;


    void moveElementUp(tinyxml2::XMLElement* element);
    void moveElementDown(tinyxml2::XMLElement* element);
    void moveElementRight(tinyxml2::XMLElement* element);
    void addSiblingElementAfter(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement = nullptr);
    void addSiblingElementBefore(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement = nullptr);
    void addChildElementFirst(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement = nullptr);
    void addChildElementLast(tinyxml2::XMLElement* element, tinyxml2::XMLElement* newElement = nullptr);
    void removeElement(tinyxml2::XMLElement* element);

    Wt::Signal<> templateModified_;
    Wt::Signal<tinyxml2::XMLElement*> selectionChanged_;

};