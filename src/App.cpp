#include "include/App.h"
#include "include/StylusSidebar.h"
#include "include/StylusEdditor2.h"
#include "include/StylusEdditorClass.h"
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/DomElement.h>

#include "include/TailwindTheme.h"
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WBootstrap2Theme.h>

App::App(const Wt::WEnvironment &env)
	: Wt::WApplication(env)
{
	setTitle("Starter Wt Application");

	auto wtCss = Wt::WLink("resources/themes/default/wt.css");
	auto tailwindCss = Wt::WLink("resources/themes/tailwind/dist/tailwind.css");

	// setCssTheme("polished");

	setTheme(std::make_shared<TailwindTheme>("tailwind"));
	
	// setTheme(std::make_shared<Wt::WBootstrap2Theme>());
	// removeStyleSheet(cssLink);
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
	require("resources/Js/Utility.js");
	require("https://cdn.jsdelivr.net/npm/alpinejs@3.x.x/dist/cdn.min.js");

	instance()->setInternalPath("/");

	

	// auto btn = root()->addWidget(std::make_unique<Wt::WPushButton>("Hello World!"));
	// btn->setStyleClass(Wt::WString::tr("button"));
	Wt::WTemplate* temp_test = root()->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr("test-btn")));
	auto btn = temp_test->bindWidget("button", std::make_unique<Wt::WPushButton>("Hello World!"));
	// temp_test->bindString("button", Wt::WString::tr("button"));
	auto container = temp_test->bindWidget("container", std::make_unique<Wt::WTemplate>(Wt::WString::tr("container")));
	auto btn_conteiner = container->bindWidget("button", std::make_unique<Wt::WPushButton>("Hello World!"));
	// root()->addChild(std::make_unique<StylusSidebar>());

	// temp_test->resolveWidget("btn")->setStyleClass(Wt::WString::tr("button"));

	// temp_test->resolveWidget("btn")->setAttributeValue("class", Wt::WString::tr("button"));

	// auto stylus_edditor_class_view = root()->addWidget(std::make_unique<StylusEdditorClass>());
	auto temp = root()->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr("test")));
	auto stylus_edditor = root()->addChild(std::make_unique<StylusEdditor2>("test.xml", "test", temp));
	// (Wt::WString::tr("button"));
	
	// btn->setStyleClass(Wt::WString::tr("button"));

}

