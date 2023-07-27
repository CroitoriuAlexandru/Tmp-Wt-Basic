#pragma once
#include <Wt/WTheme.h>
#include <Wt/WSignal.h>
#include <string>
using namespace Wt;

class WT_API TailwindTheme : public WTheme
{
public:
  TailwindTheme(const std::string& name);

  virtual ~TailwindTheme();

  virtual std::string name() const override;

  /*! \brief Returns the stylesheets.
   *
   * Returns wt.css, plus on IE wt_ie.css, plus on IE6 wt_ie6.css. The
   * style sheets are located in the theme directory in the resources
   * folder.
   */
  virtual std::vector<WLinkedCssStyleSheet> styleSheets() const override;

  virtual void apply(WWidget *widget, WWidget *child, int widgetRole) const override;
  virtual void apply(WWidget *widget, DomElement& element, int elementRole)
    const override;

  /*! \brief Returns a generic CSS class name for a disabled element.
   *
   * The CSS class Wt-disabled is applied to disabled classes.
   */
  virtual std::string disabledClass() const override;

  /*! \brief Returns a generic CSS class name for an active element.
   *
   * The CSS class Wt-selected is applied to active classes.
   */
  virtual std::string activeClass() const override;

  virtual std::string utilityCssClass(int utilityCssClassRole) const override;

  /*! \brief Returns whether the theme allows for an anchor to be styled
   *         as a button.
   *
   * Returns false.
   */
  virtual bool canStyleAnchorAsButton() const override;

  virtual void applyValidationStyle(WWidget *widget,
                                    const Wt::WValidator::Result& validation,
                                    WFlags<ValidationStyleFlag> styles) const override;

  virtual bool canBorderBoxElement(const DomElement& element) const override;
private:
  std::string name_;
};
