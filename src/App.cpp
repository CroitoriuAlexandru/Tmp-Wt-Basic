#include "include/App.h"
#include "include/StylusEdditor2.h"
#include "include/StylusEdditorClass.h"
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/DomElement.h>

#include "include/TailwindTheme.h"
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WBootstrap2Theme.h>
#include <Wt/WTimer.h>

App::App(const Wt::WEnvironment &env)
	: Wt::WApplication(env)
{
	setTitle("Starter Wt Application");

	// auto wtCss = Wt::WLink("resources/themes/default/wt.css");
	auto defStyles = Wt::WLink("resources/themes/someDefaultStyles.css");

	// setCssTheme("polished");setCssFileCheckTimer
	// auto theme = std::make_shared<TailwindTheme>("polished");
	// theme->setCssFileCheckTimer();
	// theme->cssFileChanged().connect([=](){
	// 	Wt::WApplication::instance()->removeStyleSheet(Wt::WLink("resources/themes/tailwind/dist/tailwind.css"));
	// 	Wt::WApplication::instance()->refresh();
	// 	auto addStylesTimer = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WTimer>());
	// 	addStylesTimer->setInterval(std::chrono::milliseconds(3000));
	// 	addStylesTimer->setSingleShot(true);
	// 	addStylesTimer->timeout().connect([=](){
	// 		Wt::WApplication::instance()->useStyleSheet(Wt::WLink("resources/themes/tailwind/dist/tailwind.css"));
	// 		Wt::WApplication::instance()->refresh();
	// 	});
	// 	addStylesTimer->start();
	// });
	setCssTheme("default");
	// setTheme(std::move(theme));
	useStyleSheet(defStyles);
	
	// setTheme(std::make_shared<Wt::WBootstrap2Theme>());
	// removeStyleSheet(cssLink);
	// removeStyleSheet(tailwindCss);
	// useStyleSheet(tailwindCss);

	// add mesage resource bundle from templates
	messageResourceBundle().use(appRoot() + "resources/xml/Elements");
	messageResourceBundle().use(appRoot() + "resources/xml/General");
	messageResourceBundle().use(appRoot() + "resources/xml/Stylus");
	messageResourceBundle().use(appRoot() + "resources/xml/Navbar");
	messageResourceBundle().use(appRoot() + "resources/xml/svg");
	messageResourceBundle().use(appRoot() + "resources/xml/Auth");
	messageResourceBundle().use(appRoot() + "resources/xml/test");

	// add custom javascript files
	require("https://cdn.jsdelivr.net/npm/alpinejs@3.x.x/dist/cdn.min.js");
	require("https://cdn.tailwindcss.com");
	require("resources/Js/Utility.js");
	instance()->setInternalPath("/");
	

	Wt::WTemplate* temp_test = root()->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr("test-btn")));
	auto btn = temp_test->bindWidget("button", std::make_unique<Wt::WPushButton>("Hello World!"));
	auto container = temp_test->bindWidget("container", std::make_unique<Wt::WTemplate>(Wt::WString::tr("container")));
	auto btn_conteiner = container->bindWidget("button", std::make_unique<Wt::WPushButton>("Hello World!"));


	// auto stylus_edditor_class_view = root()->addWidget(std::make_unique<StylusEdditorClass>());
	auto temp = root()->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr("test")));
	auto stylus_edditor = root()->addChild(std::make_unique<StylusEdditor2>("test.xml", "test", temp));
	// (Wt::WString::tr("button"));
	
	// btn->setStyleClass(Wt::WString::tr("button"));

}

