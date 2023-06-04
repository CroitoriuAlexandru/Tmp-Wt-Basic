#pragma once
#include "Auth.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WMenu.h>
#include <Wt/WMenuItem.h>
#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include <Wt/WImage.h>
#include <Wt/WIcon.h>
class App : public Wt::WContainerWidget
{
public:
    App();
private:
    Wt::WTemplate* navbar_;
    Wt::WStackedWidget* stack_;
    
    Wt::WMenu* menu_;
    Wt::WMenu* user_menu_;
    Wt::WTemplate* user_menu_wrapper_;

    Auth* auth_widget_;
    
    int current_menu_index_ = 0;

    void onMenuItemSelected(Wt::WMenuItem* menu_item);
    void createApp();
    void userLoggedIn();
    void userLoggedOut();

    void createThemeSwitcher();
};