#include "include/Auth.h"
#include <Wt/WLineEdit.h>

Auth::Auth() 
    : Wt::WTemplate(tr("auth"))
{
    // -translate-y-full
	setStyleClass("absolute left-0 right-0 top-0 bottom-0 transform -translate-y-full bg-body h-screen z-50");
    createLogin();
}

void Auth::createLogin()
{
    auto header = bindWidget("header", std::make_unique<Wt::WTemplate>(tr("login-header")));
	auto content = bindWidget("content", std::make_unique<Wt::WTemplate>(tr("login-content")));
    bindEmpty("footer");
    auto eye_btn = content->bindWidget("eye-button", std::make_unique<Wt::WTemplate>(tr("eye-crossed-svg")));
    auto password = content->bindWidget("password", std::make_unique<Wt::WLineEdit>());
    auto password_label = content->bindWidget("password-label", std::make_unique<Wt::WText>("Password"));
    auto email = content->bindWidget("email", std::make_unique<Wt::WLineEdit>());
    auto login_btn  = content->bindWidget("login-button", std::make_unique<Wt::WPushButton>("Login"));
    auto sign_up_btn = content->bindWidget("sign-up-button", std::make_unique<Wt::WPushButton>("Sign Up"));

    content->bindWidget("email-svg", std::make_unique<Wt::WText>(tr("email-svg")));
    content->bindWidget("key-svg", std::make_unique<Wt::WText>(tr("key-svg")));
    email->setPlaceholderText("Enter your email address");
    password->setPlaceholderText("Enter your password");
    password->setEchoMode(Wt::EchoMode::Password);

    eye_btn->clicked().connect(this, [=](){
        if(password->echoMode() == Wt::EchoMode::Password)
        {
            password->setEchoMode(Wt::EchoMode::Normal);
            eye_btn->setTemplateText(tr("eye-svg"));
                }else {
            password->setEchoMode(Wt::EchoMode::Password);
            eye_btn->setTemplateText(tr("eye-crossed-svg"));
        }
    });

    login_btn->clicked().connect(this, [=](){
        user_logged_in_.emit();
    });

    sign_up_btn->clicked().connect(this, [=](){
        createSignUp();
    });
    
}

void Auth::createSignUp() {
    auto header = bindWidget("header", std::make_unique<Wt::WTemplate>(tr("sign-up-header")));
    auto footer = bindWidget("footer", std::make_unique<Wt::WTemplate>(tr("sign-up-footer")));
	bindWidget("content", std::make_unique<Wt::WTemplate>(tr("sign-up-step-1")));
    signUpStep = 1;

	header->bindString("step-num", std::to_string(signUpStep));
    header->bindString("progress", std::to_string((signUpStep-1) * 33));
    header->bindWidget("progress-indicator", std::make_unique<Wt::WText>())->addStyleClass("w-1");
    header->bindString("step-title", "your profile");

	auto prev_btn = footer->bindWidget("prev-btn", std::make_unique<Wt::WPushButton>("Previous Step"));
    auto back_to_login = footer->bindWidget("back-to-login", std::make_unique<Wt::WPushButton>("Back to login"));
    auto next_btn = footer->bindWidget("next-btn", std::make_unique<Wt::WPushButton>("Continue"));
    auto sign_up_btn = footer->bindWidget("sign-up-btn", std::make_unique<Wt::WPushButton>("Sign Up"));

	next_btn->clicked().connect(this, [=](){
		if(signUpStep < 3){
            if(signUpStep == 1){
                prev_btn->removeStyleClass("hidden");
                back_to_login->addStyleClass("hidden");
                header->bindString("step-title", "your password");
                header->bindWidget("progress-indicator", std::make_unique<Wt::WText>())->addStyleClass("w-1/3");   
            }else {
                header->bindString("step-title", "About your profesion");
                header->bindWidget("progress-indicator", std::make_unique<Wt::WText>())->addStyleClass("w-2/3");
                next_btn->addStyleClass("hidden");
                sign_up_btn->removeStyleClass("hidden");
            }
    		bindWidget("content", std::make_unique<Wt::WTemplate>(tr("sign-up-step-" + std::to_string(signUpStep+1))));
			++signUpStep;
	        header->bindString("step-num", std::to_string(signUpStep));
            header->bindString("progress", std::to_string((signUpStep-1) * 33));
		}
	});

	prev_btn->clicked().connect(this, [=](){
		if(signUpStep > 1){
            if(signUpStep == 2){
                prev_btn->addStyleClass("hidden");
                back_to_login->removeStyleClass("hidden");
                header->bindString("step-title", "your profile");
                header->bindWidget("progress-indicator", std::make_unique<Wt::WText>())->addStyleClass("w-1");
            }else {
                header->bindString("step-title", "your password");
                header->bindWidget("progress-indicator", std::make_unique<Wt::WText>())->addStyleClass("w-1/3");
                next_btn->setText("continue");
                next_btn->removeStyleClass("hidden");
                sign_up_btn->addStyleClass("hidden");
            }
			bindWidget("content", std::make_unique<Wt::WTemplate>(tr("sign-up-step-" + std::to_string(signUpStep-1))));
		    --signUpStep;
	        header->bindString("step-num", std::to_string(signUpStep));
        bindString("progress", std::to_string((signUpStep-1) * 33));
		}
	});

    sign_up_btn->clicked().connect(this, [=](){
        user_logged_in_.emit();
        createLogin();
    });

    back_to_login->clicked().connect(this, [=](){
        createLogin();
    });
}