#include "include/App.h"
#include "include/Buttons.h"
#include "include/PageTwo.h"

App::App()
	: WContainerWidget()
{
	auto auth_temp = addWidget(std::make_unique<Wt::WTemplate>(tr("auth-temp")));
	auth_temp->setStyleClass("mx-auto max-w-3xl px-4 py-10");
	auth_temp->bindWidget("content", std::make_unique<Wt::WTemplate>(tr("step-1")));
	auto next_btn = auth_temp->bindWidget("next-btn", std::make_unique<Wt::WPushButton>("continue"));
	auto prev_btn = auth_temp->bindWidget("prev-btn", std::make_unique<Wt::WPushButton>("previous")); 
	
	next_btn->clicked().connect(this, [=](){
		if(authStep < 3){
			auth_temp->bindWidget("content", std::make_unique<Wt::WTemplate>(tr("step-" + std::to_string(authStep+1))));
			++authStep;
		}
	});
	prev_btn->clicked().connect(this, [=](){
		if(authStep > 1){
			auth_temp->bindWidget("content", std::make_unique<Wt::WTemplate>(tr("step-" + std::to_string(authStep-1))));
		--authStep;
		}

	});
	// createApp();
}

void App::onMenuItemSelected(Wt::WMenuItem* menuItem) 
{
	auto nextMenuIndex = stack_->currentIndex();	
	std::cout << "\n\n current = " << currentMenuIndex_ << " \nnext = " << nextMenuIndex << "\n\n";
	if(nextMenuIndex <= 1){
		menuItem->addStyleClass("bg-gray-900");	
	}else {
		menuItem->anchor()->addStyleClass("active-basic");
		userMenuWrapper_->addStyleClass("hidden");
	}

	if(currentMenuIndex_ <= 1){
		menu_->itemAt(currentMenuIndex_)->removeStyleClass("bg-gray-900");
		menu_->itemAt(currentMenuIndex_)->close();
	}else {
		userMenu_->itemAt(currentMenuIndex_ -2)->anchor()->removeStyleClass("active-basic");
	}

	currentMenuIndex_ = nextMenuIndex;
}

void App::createApp() {
	addStyleClass("relative");
	// Create navigation
	auto navbar = addWidget(std::make_unique<Wt::WTemplate>(tr("navbar")));
	navbar->bindWidget("logo", std::make_unique<Wt::WImage>("https://tailwindui.com/img/logos/workflow-mark.svg?color=indigo&shade=500"));
	
	// create menu_ and stack_
	stack_ = addWidget(std::make_unique<Wt::WStackedWidget>());
	menu_ = navbar->bindWidget("menu", std::make_unique<Wt::WMenu>(stack_));
	menu_->setInternalPathEnabled();

	// add menu_ items
	auto buttonsMenuItem = menu_->addItem("Buttons", std::make_unique<Buttons>());
	auto pageTwoMenuItem = menu_->addItem("Page Two", std::make_unique<PageTwo>());
	buttonsMenuItem->setPathComponent("buttons");
	pageTwoMenuItem->setPathComponent("page_two");

	// menu_ Item styles
	buttonsMenuItem->setStyleClass("w-4/5 rounded-md");
	pageTwoMenuItem->setStyleClass("w-4/5 rounded-md");
	Wt::WString menuItemStyles = "block rounded-md px-3 py-2 !m-1 text-sm font-medium text-white text-center hover:bg-gray-900";
	buttonsMenuItem->anchor()->setStyleClass(menuItemStyles);
	pageTwoMenuItem->anchor()->setStyleClass(menuItemStyles);

	// add bg color to the menu_ item when its selected and remove bg color from the previous one
	menu_->itemSelected().connect(this, &App::onMenuItemSelected);

	// Hamburger Button to toggle menu_ opn mobile
	auto hamburgerBtn = navbar->bindWidget("hamburger-button", std::make_unique<Wt::WPushButton>(tr("hamburger-svg")));
	hamburgerBtn->setTextFormat(Wt::TextFormat::XHTML);
	hamburgerBtn->clicked().connect(this, [=](){
		if(menu_->hasStyleClass("hidden")){
			menu_->removeStyleClass("hidden");
			hamburgerBtn->setText(tr("x-svg"));
		} else {
			menu_->addStyleClass("hidden");
			hamburgerBtn->setText(tr("hamburger-svg"));
		}
	});

	// user menu_
	auto userImage = navbar->bindWidget("user-image", std::make_unique<Wt::WImage>("./resources/images/blank-profile-picture.png"));
	userMenuWrapper_ = navbar->bindWidget("user-menu-wrapper", std::make_unique<Wt::WTemplate>(tr("user-menu-wrapper")));
	userMenu_ = userMenuWrapper_->bindWidget("user-menu", std::make_unique<Wt::WMenu>(stack_));
	userMenu_->setInternalPathEnabled();
	userMenu_->itemSelected().connect(this, &App::onMenuItemSelected);
	userMenu_->setStyleClass("list-none m-0 p-1 text-center");	

	auto profileContainer = std::make_unique<Wt::WContainerWidget>();
	profileContainer->setStyleClass("bg-yellow-500 p-12 m-12");

	auto profile = userMenu_->addItem("Profile", std::move(profileContainer));
	auto settings = userMenu_->addItem("Settings", std::make_unique<Wt::WText>("Settings"));
	auto signOut = userMenu_->addItem("Sign Out", std::make_unique<Wt::WText>("Sign Out"));

	Wt::WString userMenuItemStyles = "block rounded-md mb-1 text-basic hover-basic px-4 py-2 text-sm ";
	profile->anchor()->setStyleClass(userMenuItemStyles);
	settings->anchor()->setStyleClass(userMenuItemStyles);
	signOut->anchor()->setStyleClass(userMenuItemStyles);

	// user menu_ toggle open/closed
	userImage->clicked().connect(this, [=](){
		if(userMenuWrapper_->hasStyleClass("hidden")){
			userMenuWrapper_->removeStyleClass("hidden");
		} else {
			userMenuWrapper_->addStyleClass("hidden");
		}
	});

	// Theme switcher 
	auto themeSwitcher = userMenuWrapper_->bindWidget("theme-switcher", std::make_unique<Wt::WPushButton>());
    themeSwitcher->setTextFormat(Wt::TextFormat::XHTML);
    themeSwitcher->setStyleClass("relative w-10 h-5 m-1 mr-2 p-0 bg-white rounded-full shadow border-0");
    themeSwitcher->setText(tr("sun-svg"));

	// theme switcher toggle dark/light mode
    themeSwitcher->clicked().connect(this, [=](){
        if(Wt::WApplication::instance()->htmlClass() == "dark"){
            themeSwitcher->setText(tr("sun-svg"));
            Wt::WApplication::instance()->setHtmlClass("");
         }else {
            themeSwitcher->setText(tr("moon-svg"));
            Wt::WApplication::instance()->setHtmlClass("dark");
        }
    });

	// default state of the app
	Wt::WApplication::instance()->setInternalPath("/page_two", true);
	currentMenuIndex_ = menu_->currentIndex();
	menu_->currentItem()->addStyleClass("bg-gray-900");
}