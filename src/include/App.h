#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WMenu.h>
#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include <Wt/WImage.h>

class App : public Wt::WContainerWidget
{
public:
    App();
private:
    int currentMenuIndex_ = 0;
    Wt::WStackedWidget* stack_;
    Wt::WMenu* menu_;
    Wt::WMenu* userMenu_;
    void onMenuItemSelected(Wt::WMenuItem* menuItem);
    void createApp();
    Wt::WTemplate* userMenuWrapper_;
};