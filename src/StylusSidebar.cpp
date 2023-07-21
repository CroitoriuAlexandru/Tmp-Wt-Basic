#include "include/StylusSidebar.h"
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WPanel.h>

#include <Wt/WMenu.h>
#include <Wt/WMenuItem.h>

#include <boost/filesystem.hpp>

std::unique_ptr<Wt::WPushButton> createEdditor(Wt::WTemplate *parent_template, std::string fileName, std::string templateName)
{
    auto stylus_btn = std::make_unique<Wt::WPushButton>(Wt::WString::tr("svg.pencil"));
    stylus_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
    stylus_btn->setStyleClass("absolute top-0 right-0 opacity-30 hover:opacity-60");
    auto edditor_dialog = std::make_unique<StylusEdditor>(fileName, templateName);
    stylus_btn->clicked().connect([=](){
        auto dialog = Wt::WApplication::instance()->addChild(std::make_unique<StylusEdditor>(fileName, templateName, parent_template));
    });
    return stylus_btn;
}

StylusSidebar::StylusSidebar()
{
    setOffsets(10, Wt::Side::Left | Wt::Side::Bottom);
    contents()->setOverflow(Wt::Overflow::Scroll);
    setStyleClass("max-h-[50vh] min-h-[50vh] min-w-[275px] !p-0 overflow-y-scroll");
    contents()->setStyleClass("p-0");
	rejectWhenEscapePressed();
	setModal(false);
    setMovable(true);
	setResizable(true);
    titleBar()->clear();


    temp_titlebar_ = titleBar()->addWidget(std::make_unique<Wt::WTemplate>(tr("stylus.sidebar.titlebar")));
    temp_content_ = contents()->addWidget(std::make_unique<Wt::WTemplate>(tr("stylus.sidebar.content")));

    temp_titlebar_->setStyleClass("!p-0");

    temp_titlebar_->bindWidget("stylus", createEdditor(temp_titlebar_, "Stylus.xml", "stylus.sidebar.titlebar"));
    temp_content_->bindWidget("stylus", createEdditor(temp_content_, "Stylus.xml", "stylus.sidebar.content"));
    temp_content_->setStyleClass("overflow-scroll");

    // add file btn
    auto btn_add_file = temp_titlebar_->bindWidget("svg.plus", std::make_unique<Wt::WPushButton>(tr("svg.plus")));
    btn_add_file->setTextFormat(Wt::TextFormat::UnsafeXHTML);
    btn_add_file->clicked().connect(this, &StylusSidebar::createFile);
    

    

    createMenu();
	setHidden(false, Wt::WAnimation(Wt::AnimationEffect::SlideInFromRight, Wt::TimingFunction::Linear, 200));
}

StylusSidebar::~StylusSidebar()
{

}


std::vector<XmlFileData> StylusSidebar::getXmlFilesData(const std::string& path)
{
    std::vector<XmlFileData> xmlFilesData;
    std::vector<std::string> fileNames;
    // Iterate over each file in the directory
    XmlFileData xmlFileData;
    for (const auto& entry : boost::filesystem::directory_iterator(path)) {
        if (boost::filesystem::is_regular_file(entry)) {
            fileNames.push_back(entry.path().filename().string());
            xmlFileData.fileName = entry.path().filename().string();
            xmlFileData.messages = getXmlFileMessages(xml_folder_path + xmlFileData.fileName);
        }
        xmlFilesData.push_back(xmlFileData);
    }
    return xmlFilesData;
}

std::vector<std::string> StylusSidebar::getXmlFileMessages(const std::string& path)
{
    std::vector<std::string> messages;

    tinyxml2::XMLDocument doc;
    auto result = doc.LoadFile(path.c_str());
	if(result != tinyxml2::XML_SUCCESS){
		std::cout << "\n\n error opening document of the message template \n\n";
	}
    tinyxml2::XMLNode* root = doc.FirstChildElement("messages");
    if(root == nullptr){
        std::cout << "\n\n error opening messages in witch the template-mesage stay \n\n";
    }
    tinyxml2::XMLElement* message = root->FirstChildElement("message");
    while(message != nullptr){
        messages.push_back(message->Attribute("id"));
        message = message->NextSiblingElement("message");
    }
    return messages;
}

void StylusSidebar::createMenu()
{
    xml_files_data_ = getXmlFilesData(xml_folder_path);
    auto menu_content = temp_content_->bindWidget("container.wt", std::make_unique<Wt::WContainerWidget>());
    // iterate overvector xml_files_data_
    for(const auto fileData : xml_files_data_)
    {
        auto panel = menu_content->addWidget(std::make_unique<Wt::WPanel>());
        panel->setTitle(fileData.fileName);
        panel->addStyleClass("border border-solid border-gray-100 rounded-md m-1");
        panel->setCollapsible(true);
        panel->setCollapsed(true);
        panel->titleBarWidget()->setStyleClass("flex items-center");
        auto delete_file_btn = panel->titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>(tr("svg.trash")));
        delete_file_btn->setStyleClass("btn p-1 m-1 ms-auto");
        delete_file_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        delete_file_btn->doubleClicked().connect([=](){
            deleteFile(fileData.fileName);
        });

        auto add_message_btn = panel->titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>(tr("svg.plus")));
        add_message_btn->setStyleClass("btn p-1 m-1");
        add_message_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
        add_message_btn->doubleClicked().connect([=](){
            addMessageTemplate(fileData.fileName);
        });

        Wt::WAnimation animation(Wt::AnimationEffect::SlideInFromTop, Wt::TimingFunction::EaseOut, 100);
        panel->setAnimation(animation);
        
        auto messages_display = panel->setCentralWidget(std::make_unique<Wt::WContainerWidget>());
        for(const auto message : fileData.messages)
        {
            auto file_item = messages_display->addWidget(std::make_unique<Wt::WTemplate>(tr("stylus.sidebar.folder.item")));
            file_item->bindWidget("title", std::make_unique<Wt::WText>(message));
            
            auto del_message_btn = file_item->bindWidget("svg.trash", std::make_unique<Wt::WPushButton>(tr("svg.trash")));
            del_message_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
            del_message_btn->doubleClicked().connect([=](){
                deleteMessageTemplate(fileData.fileName, message);
            });

            auto open_edditor_btn = file_item->bindWidget("svg.pencil", std::make_unique<Wt::WPushButton>(tr("svg.pencil")));
            open_edditor_btn->setTextFormat(Wt::TextFormat::UnsafeXHTML);
            open_edditor_btn->doubleClicked().connect([=](){
                auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<StylusEdditor>(fileData.fileName, message));
                dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
            });

        }
    }
}




void StylusSidebar::createFile()
{
    auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("File Name ?"));
    dialog->setStyleClass("p-0");
    dialog->contents()->setStyleClass("flex");
    dialog->titleBar()->clear();
    dialog->setOffsets(20, Wt::Side::Top);
    dialog->rejectWhenEscapePressed();
    auto input = dialog->contents()->addWidget(std::make_unique<Wt::WLineEdit>());
    input->setPlaceholderText("File Name");
    input->setFocus();
    input->setStyleClass("input-style-1 text-md");
    input->enterPressed().connect([=](){
        if(input->text().toUTF8() != ""){
            dialog->accept();
        }else {
            input->addStyleClass("bg-red-100");
            dialog->contents()->addWidget(std::make_unique<Wt::WText>("Please enter a file name"));
            
        }
    });

    dialog->finished().connect([=](){
        if(dialog->result() == Wt::DialogCode::Accepted){
            std::ofstream file;
            std::string filePath = xml_folder_path + input->text().toUTF8() + ".xml";
            file.open(filePath);
            if(file.is_open()){
                file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
                file << "<messages>\n";
                file << "</messages>\n";
                file.close();
                xml_files_data_ = getXmlFilesData(xml_folder_path);
                createMenu();
            }else {
                std::cout << "\n\n error creating file \n\n";
            }
        }
    });
    dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
}

void StylusSidebar::deleteFile(std::string fileName)
{
    std::string filePath = xml_folder_path + fileName;
    
    auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Are you sure ?"));
    dialog->rejectWhenEscapePressed();
    dialog->contents()->addWidget(std::make_unique<Wt::WText>(fileName));
    auto delete_btn = dialog->contents()->addWidget(std::make_unique<Wt::WPushButton>("Delete"));
    delete_btn->setStyleClass("btn");
    delete_btn->clicked().connect([=](){
        dialog->accept();
    });
    delete_btn->setFocus();
    dialog->finished().connect([=](){
        if(dialog->result() == Wt::DialogCode::Accepted){
            std::cout << "\n\n" << filePath << "\n\n";
            if (std::remove(filePath.c_str()) != 0) {
                std::cout << "\n\nFailed to delete the file\n\n";
            }
            else {
                std::cout << "\n\nFile successfully deleted\n\n";
                createMenu();
            }
        }
    });
    dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
}

void StylusSidebar::deleteMessageTemplate(std::string fileName, std::string tempMessageId)
{
    tinyxml2::XMLDocument doc;
    auto result = doc.LoadFile((xml_folder_path + fileName).c_str());
    if(result != tinyxml2::XML_SUCCESS){
        std::cout << "\n\n error opening document of the message template \n\n";
        auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Error"));
        dialog->rejectWhenEscapePressed();
        dialog->contents()->addWidget(std::make_unique<Wt::WText>("Error opening document of the message template"));
        return;
    }
    auto messages = doc.FirstChildElement("messages");
    auto messageTemplate = messages->FirstChildElement("message");
    while(messageTemplate != nullptr){
        if(messageTemplate->Attribute("id") == tempMessageId){
            auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Are you sure ?"));
            dialog->rejectWhenEscapePressed();
            dialog->contents()->addWidget(std::make_unique<Wt::WText>(tempMessageId));
            auto delete_btn = dialog->contents()->addWidget(std::make_unique<Wt::WPushButton>("Delete"));
            delete_btn->setStyleClass("btn ");
            delete_btn->clicked().connect([=](){
                dialog->accept();
            });
            delete_btn->setFocus();
            dialog->finished().connect([=](){
                if(dialog->result() == Wt::DialogCode::Accepted){
                    messages->DeleteChild(messageTemplate);
                    createMenu();
                }
            });
            doc.SaveFile((xml_folder_path + fileName).c_str());
            dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
            break;
        }
        messageTemplate = messageTemplate->NextSiblingElement("message");
    }
    doc.SaveFile((xml_folder_path + fileName).c_str());
    createMenu();
}

void StylusSidebar::addMessageTemplate(std::string fileName)
{
    auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Message Id ?"));
    dialog->rejectWhenEscapePressed();
    auto input_message_id = dialog->contents()->addWidget(std::make_unique<Wt::WLineEdit>());
    input_message_id->setPlaceholderText("Message Id");
    input_message_id->setFocus();
    input_message_id->setStyleClass("input-style-1 text-md");
    input_message_id->enterPressed().connect([=](){
        if(input_message_id->text().toUTF8() != ""){
            dialog->accept();
        }else {
            input_message_id->addStyleClass("bg-red-100");
            dialog->contents()->addWidget(std::make_unique<Wt::WText>("Please enter a message id"));
            
        }
    });

    dialog->finished().connect([=](){
        if(dialog->result() == Wt::DialogCode::Accepted){
            tinyxml2::XMLDocument doc;
            auto result = doc.LoadFile((xml_folder_path + fileName).c_str());
            if(result != tinyxml2::XML_SUCCESS){
                std::cout << "\n\n error opening document of the message template \n\n";
                auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Error"));
                dialog->rejectWhenEscapePressed();
                dialog->contents()->addWidget(std::make_unique<Wt::WText>("Error opening document of the message template"));
                return;
            }
            auto messages = doc.FirstChildElement("messages");
            auto messageTemplate = messages->FirstChildElement("message");
            while(messageTemplate != nullptr){
                if(messageTemplate->Attribute("id") == input_message_id->text().toUTF8()){
                    auto dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Error"));
                    dialog->rejectWhenEscapePressed();
                    dialog->contents()->addWidget(std::make_unique<Wt::WText>("Message id already exists"));
                    return;
                }
                messageTemplate = messageTemplate->NextSiblingElement("message");
            }
            auto newMessage = messages->InsertNewChildElement("message");
            newMessage->SetAttribute("id", input_message_id->text().toUTF8().c_str());
            auto stylusElement = newMessage->InsertNewChildElement("div");
            stylusElement->SetText("${stylus}");
            doc.SaveFile((xml_folder_path + fileName).c_str());
            createMenu();
        }
    });
    dialog->animateShow(Wt::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::EaseInOut, 200));
}
