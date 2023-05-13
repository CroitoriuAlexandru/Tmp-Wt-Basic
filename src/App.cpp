#include "include/App.h"
#include "include/PageOne.h"
#include "include/PageTwo.h"
#include "include/TailwindThemeSwitcher.h"
#include "include/TailwindNavbar.h"

#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>

App::App()
	: WContainerWidget()
{
	addStyleClass("bg-gray-200 dark:bg-slate-900 min-w-fit overflow-auto");
	// createNavigation();
	auto tailwindNavbar = addWidget(std::make_unique<TailwindNavbar>());

	auto themeSwitcher = addWidget(std::make_unique<Tailwind::ThemeSwitcher>(false, 6));
	themeSwitcher->addStyleClass("m-2 p-1");
	// createButtonsExample();
}

void App::createNavigation()
{
	navigation_ = addWidget(std::make_unique<Wt::WNavigationBar>());
	navigation_->setObjectName("navigation");

	// navigation->setResponsive(true);
	navigation_->addStyleClass("navbar navbar-dark bg-dark navbar-expand-sm");
	navigation_->setTitle("App Name", Wt::WLink(Wt::LinkType::InternalPath, "/PageOne"));

	contentsStack_ = addWidget(std::make_unique<Wt::WStackedWidget>());
	contentsStack_->setTransitionAnimation(Wt::WAnimation(Wt::AnimationEffect::SlideInFromRight, Wt::TimingFunction::EaseInOut), true);
	contentsStack_->addStyleClass("contents");

	auto mainMenu_ = navigation_->addMenu(std::make_unique<Wt::WMenu>(contentsStack_));
	mainMenu_->setInternalPathEnabled();

	// create pages content
	auto pageOne = std::make_unique<PageOne>();
	auto pageTwo = std::make_unique<PageTwo>();

	// create menu items 
	auto menuItemOne = std::make_unique<Wt::WMenuItem>("Page One", std::move(pageOne));
	auto menuItemTwo = std::make_unique<Wt::WMenuItem>("Page Two", std::move(pageTwo));

	menuItemOne->setPathComponent("page_one");
	menuItemTwo->setPathComponent("page_two");

	// add pages to stack
	mainMenu_->addItem(std::move(menuItemOne));
	mainMenu_->addItem(std::move(menuItemTwo));

	// default starting page
	Wt::WApplication::instance()->setInternalPath("/page_one", true);
}


void App::createButtonsExample()
{
	auto btn_Wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());
	btn_Wrapper->addStyleClass("");

	// DEFAULT
	auto defaultBtn_Wrapper = btn_Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	defaultBtn_Wrapper->addStyleClass("flex");
	defaultBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("light"))->setStyleClass("btn btn-light-default");
	defaultBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("dark"))->setStyleClass("btn btn-dark-default");
	auto default_disabled = defaultBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("disabled"));
	default_disabled->setStyleClass("btn");
	default_disabled->setDisabled(true);
	defaultBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("simple"))->setStyleClass("btn");
	
	// PRIMARY
	auto primaryBtn_Wrapper = btn_Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	primaryBtn_Wrapper->addStyleClass("flex");
	primaryBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("light"))->setStyleClass("btn btn-primary-light");
	primaryBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("dark"))->setStyleClass("btn btn-primary-dark");
	auto primary_disabled = primaryBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("disabled"));
	primary_disabled->setStyleClass("btn btn-primary");
	primary_disabled->setDisabled(true);
	primaryBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("primary"))->setStyleClass("btn btn-primary");


	// SECCONDARY
	auto secondaryBtn_Wrapper = btn_Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	secondaryBtn_Wrapper->addStyleClass("flex");
	secondaryBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("light"))->setStyleClass("btn btn-secondary-light");
	secondaryBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("dark"))->setStyleClass("btn btn-secondary-dark");
	auto seccondary_disabled = secondaryBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("disabled"));
	seccondary_disabled->setStyleClass("btn btn-secondary");
	seccondary_disabled->setDisabled(true);
	secondaryBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("seccondary"))->setStyleClass("btn btn-secondary");

	// SUCCESS
	auto successBtn_Wrapper = btn_Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	successBtn_Wrapper->addStyleClass("flex");
	successBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("light"))->setStyleClass("btn btn-success-light");
	successBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("dark"))->setStyleClass("btn btn-success-dark");
	auto success_disabled = successBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("disabled"));
	success_disabled->setStyleClass("btn btn-success");
	success_disabled->setDisabled(true);
	successBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("success"))->setStyleClass("btn btn-success");

	// DANGER
	auto dangerBtn_Wrapper = btn_Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	dangerBtn_Wrapper->addStyleClass("flex");
	dangerBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("light"))->setStyleClass("btn btn-danger-light");
	dangerBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("dark"))->setStyleClass("btn btn-danger-dark");
	auto danger_disabled = dangerBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("disabled"));
	danger_disabled->setStyleClass("btn btn-danger");
	danger_disabled->setDisabled(true);
	dangerBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("danger"))->setStyleClass("btn btn-danger");

	// WARNING
	auto warningBtn_Wrapper = btn_Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	warningBtn_Wrapper->addStyleClass("flex");
	warningBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("light"))->setStyleClass("btn btn-warning-light");
	warningBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("dark"))->setStyleClass("btn btn-warning-dark");
	auto warning_disabled = warningBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("disabled"));
	warning_disabled->setStyleClass("btn btn-warning");
	warning_disabled->setDisabled(true);
	warningBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("warning"))->setStyleClass("btn btn-warning");

	// INFO
	auto infoBtn_Wrapper = btn_Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	infoBtn_Wrapper->addStyleClass("flex");
	infoBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("light"))->setStyleClass("btn btn-info-light");
	infoBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("dark"))->setStyleClass("btn btn-info-dark");
	auto info_disabled = infoBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("disabled"));
	info_disabled->setStyleClass("btn btn-info");
	info_disabled->setDisabled(true);
	infoBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("info"))->setStyleClass("btn btn-info");

	// DARK
	auto darkBtn_Wrapper = btn_Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
	darkBtn_Wrapper->addStyleClass("flex");
	darkBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("light"))->setStyleClass("btn btn-dark-light");
	darkBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("dark"))->setStyleClass("btn btn-dark-dark");
	auto dark_disabled = darkBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("disabled"));
	dark_disabled->setStyleClass("btn btn-dark");
	dark_disabled->setDisabled(true);
	darkBtn_Wrapper->addWidget(std::make_unique<Wt::WPushButton>("dark"))->setStyleClass("btn btn-dark");
	

}
