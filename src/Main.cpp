#include "include/App.h"
#include <Wt/WApplication.h>
#include <Wt/WCssTheme.h>
#include <Wt/WServer.h>
#include <Wt/Dbo/Exception.h>

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment &env)
{
	auto app = std::make_unique<Wt::WApplication>(env);
	app->setTitle("Simple Application Template");
	// add style file from tailwind

	std::cout << "\n\n" << app->instance()->theme()->name() << "\n\n";
	app->useStyleSheet("resources/themes/tailwind/dist/tailwind.css");

	// add mesage resource bundle from templates
	app->messageResourceBundle().use(app->appRoot() + "resources/templates/General");
	app->messageResourceBundle().use(app->appRoot() + "resources/templates/TailwindNavbar");
	app->messageResourceBundle().use(app->appRoot() + "resources/templates/TailwindThemeSwitcher");

	// add custom javascript files
	app->require("resources/Js/Utility.js");

	app->instance()->setInternalPath("/");
	app->instance()->setHtmlClass("min-w-full");
	// add application to root
	app->root()->addWidget(std::make_unique<App>());
	// app->root()->addStyleClass("w-100 h-100");
	app->setBodyClass("m-0 bg-gray-200 dark:bg-slate-900 min-w-full");

	return app;
}

int main(int argc, char **argv)
{
	try
	{
		// Server setup
		Wt::WServer server{argc, argv, WTHTTP_CONFIGURATION};

		server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

		server.run();
	}
	catch (Wt::WServer::Exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (Wt::Dbo::Exception &e)
	{
		std::cerr << "Dbo exception: " << e.what() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "exception: " << e.what() << std::endl;
	}
}