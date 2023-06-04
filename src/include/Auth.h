// #include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WTemplate.h>
#include <Wt/WPushButton.h>
#include <Wt/WSignal.h>
class Auth : public Wt::WTemplate
{
public:
    Auth();

    Wt::Signal<>& userLoggedIn() { return user_logged_in_; }
private:
    void createLogin();
    void createSignUp();
    int signUpStep;

    Wt::Signal<> user_logged_in_;
};
