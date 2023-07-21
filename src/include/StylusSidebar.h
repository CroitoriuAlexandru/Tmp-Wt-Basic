#pragma once
#include <Wt/WDialog.h>
#include <Wt/WTemplate.h>
#include "StylusEdditor.h"

#include <vector>

struct XmlFileData {
    std::string fileName;
    std::vector<std::string> messages;
};
std::unique_ptr<Wt::WPushButton> createEdditor(Wt::WTemplate *parent_template = nullptr, std::string fileName = "", std::string templateName = "");

class StylusSidebar : public Wt::WDialog
{
public:
    StylusSidebar();
    ~StylusSidebar();
private:
    std::string xml_folder_path = "resources/xml/";
    Wt::WTemplate* temp_titlebar_;
    Wt::WTemplate* temp_content_;
    
    void createMenu();
    void createFile();
    void deleteFile(std::string fileName);
    void deleteMessageTemplate(std::string fileName, std::string tempMessageId);
    void addMessageTemplate(std::string fileName);


    std::vector<XmlFileData> getXmlFilesData(const std::string& path);
    std::vector<std::string> getXmlFileMessages(const std::string& path);
    std::vector<XmlFileData> xml_files_data_;

};