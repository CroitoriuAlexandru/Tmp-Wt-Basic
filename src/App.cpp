#include "include/App.h"
#include "include/PageTwo.h"
#include "include/Buttons.h"
App::App()
	: WContainerWidget()
{
	setStyleClass("static");
	auth_widget_ = addWidget(std::make_unique<Auth>());
	auth_widget_->userLoggedIn().connect(this, &App::userLoggedIn);
	createApp();
	userLoggedIn();
	user_menu_wrapper_->removeStyleClass("hidden");
}

void App::userLoggedIn(){
	std::cout << "\n\n user logged in \n\n";

	// default state of the app
	Wt::WApplication::instance()->setInternalPath("/buttons", true);
	current_menu_index_ = menu_->currentIndex();

	navbar_->removeStyleClass("hidden");
	auth_widget_->addStyleClass("-translate-y-full");

	auto profile = user_menu_->addItem("Profile",  std::make_unique<Wt::WText>("Profile"));
	auto settings = user_menu_->addItem("Settings", std::make_unique<Wt::WText>("Settings"));

	Wt::WString userMenuItemStyles = "bg-body-hover-border block rounded-md text-inherit mb-1 text-basic hover-basic flex items-center px-4 py-2 text-sm";
	profile->setStyleClass(userMenuItemStyles);
	settings->setStyleClass(userMenuItemStyles);
	profile->setIcon("./resources/images/person.svg");
	// profile->anchor()->setText(tr("human-svg") + " Profile");
	// profile->setPathComponent("profile");


	user_menu_wrapper_->bindEmpty("log-in-btn");
	auto log_out = user_menu_wrapper_->bindWidget("log-out-btn", std::make_unique<Wt::WPushButton>("Log Out"));
	log_out->clicked().connect(this, &App::userLoggedOut);
}

void App::userLoggedOut(){
	std::cout << "\n\n user logged out \n\n";

	// default state of the app
	Wt::WApplication::instance()->setInternalPath("buttons", true);
	current_menu_index_ = menu_->currentIndex();
	// menu_->currentItem()->addStyleClass("bg-gray-900");

	// remove user menu_ items
	auto user_menu_items = user_menu_->items();
	for (auto& item : user_menu_items) {
		user_menu_->removeItem(item);
	}
	
	// set login/logout btn
	user_menu_wrapper_->bindEmpty("log-out-btn");
	auto log_in = user_menu_wrapper_->bindWidget("log-in-btn", std::make_unique<Wt::WPushButton>("Log In"));
	log_in->clicked().connect(this, [=](){
		auth_widget_->removeStyleClass("-translate-y-full");
		
	});

	
}

void App::createApp() {
	// Create navigation
	navbar_ = addWidget(std::make_unique<Wt::WTemplate>(tr("navbar")));
	auto logo = navbar_->bindWidget("logo", std::make_unique<Wt::WImage>("https://tailwindui.com/img/logos/workflow-mark.svg?color=indigo&shade=500"));
	
	// create menu_ and stack_
	stack_ = addWidget(std::make_unique<Wt::WStackedWidget>());

	menu_ = navbar_->bindWidget("menu", std::make_unique<Wt::WMenu>(stack_));
	menu_->setInternalPathEnabled();

	// add menu_ items
	auto btns_page_menu_item = menu_->addItem("Buttons", std::make_unique<Buttons>());
	auto page_two_menu_item = menu_->addItem("Page Two", std::make_unique<PageTwo>());
	btns_page_menu_item->setPathComponent("buttons");
	page_two_menu_item->setPathComponent("page_two");

	// menu_ Item styles
	Wt::WString list_item_styles = "bg-body-hover-border w-4/5 rounded-md sm:rounded-none h-full flex items-center   ";
	btns_page_menu_item->setStyleClass(list_item_styles);
	page_two_menu_item->setStyleClass(list_item_styles);
	Wt::WString menuItemStyles = "sm:!rounded-none px-3 text-inherit !m-0 font-medium ";
	btns_page_menu_item->anchor()->setStyleClass(menuItemStyles);
	page_two_menu_item->anchor()->setStyleClass(menuItemStyles);

	// add bg color to the menu_ item when its selected and remove bg color from the previous one
	menu_->itemSelected().connect(this, &App::onMenuItemSelected);

	// Hamburger Button to toggle menu_ opn mobile
	auto hamburger_btn = navbar_->bindWidget("hamburger-button", std::make_unique<Wt::WPushButton>(tr("hamburger-svg")));
	hamburger_btn->setTextFormat(Wt::TextFormat::XHTML);
	hamburger_btn->clicked().connect(this, [=](){
		if(menu_->hasStyleClass("hidden")){
			menu_->removeStyleClass("hidden");
			hamburger_btn->setText(tr("x-svg"));
		} else {
			menu_->addStyleClass("hidden");
			hamburger_btn->setText(tr("hamburger-svg"));
		}
	});

	// user menu_
	auto user_img = navbar_->bindWidget("user-image", std::make_unique<Wt::WImage>("./resources/images/blank-profile-picture.png"));
	user_menu_wrapper_ = navbar_->bindWidget("user-menu-wrapper", std::make_unique<Wt::WTemplate>(tr("user-menu-wrapper")));
	user_menu_ = user_menu_wrapper_->bindWidget("user-menu", std::make_unique<Wt::WMenu>(stack_));
	user_menu_->setInternalPathEnabled();
	user_menu_->itemSelected().connect(this, &App::onMenuItemSelected);
	user_menu_->setStyleClass("list-none m-0 p-1 text-center");	

	// user menu_ toggle open/closed
	user_img->clicked().connect(this, [=](){
		if(user_menu_wrapper_->hasStyleClass("hidden")){
			user_menu_wrapper_->removeStyleClass("hidden");
		} else {
			user_menu_wrapper_->addStyleClass("hidden");
		}
	});

	// default state of the app is that the user is logged out
	createThemeSwitcher();
	userLoggedOut();
}

void App::createThemeSwitcher(){
	auto theme_switcher = user_menu_wrapper_->bindWidget("theme-switcher", std::make_unique<Wt::WPushButton>(tr("sun-svg")));
    theme_switcher->setTextFormat(Wt::TextFormat::XHTML);
    theme_switcher->setStyleClass("relative w-10 h-5 m-1 mr-2 p-0 bg-white rounded-full shadow border-0");
    theme_switcher->setText(tr("sun-svg"));

	// theme switcher toggle dark/light mode
    theme_switcher->clicked().connect(this, [=](){
        if(Wt::WApplication::instance()->htmlClass() == "dark"){
            theme_switcher->setText(tr("sun-svg"));
            Wt::WApplication::instance()->setHtmlClass("");
         }else {
            theme_switcher->setText(tr("moon-svg"));
            Wt::WApplication::instance()->setHtmlClass("dark");
        }
    });
	
	// theme_switcher->setText(tr("moon-svg"));
	// Wt::WApplication::instance()->setHtmlClass("dark");
}

void App::onMenuItemSelected(Wt::WMenuItem* menu_item) 
{
	auto next_menu_index = stack_->currentIndex();
	menu_item->addStyleClass("bg-body-active");
	
	std::cout << "\ncurrent = " << current_menu_index_ << " \nnext = " << next_menu_index << "\n";
	if(next_menu_index <= 1){
		if(!user_menu_wrapper_->hasStyleClass("hidden")){
			user_menu_wrapper_->addStyleClass("hidden");
		}
	}else {
		// menu_item->anchor()->addStyleClass("active-basic");
		user_menu_wrapper_->addStyleClass("hidden");
	}

	if(current_menu_index_ <= 1){
		// menu_->itemAt(current_menu_index_)->removeStyleClass("bg-gray-900");
		menu_->itemAt(current_menu_index_)->close();
	}else {
		// user_menu_->itemAt(current_menu_index_ -2)->anchor()->removeStyleClass("active-basic");
	}

	current_menu_index_ = next_menu_index;
}