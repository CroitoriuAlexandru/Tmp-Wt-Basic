#pragma once
#include "ElementSpacingWidget.h"
#include "ElementSizingWidget.h"

#include <Wt/WTemplate.h>
#include <Wt/WSignal.h>
#include <regex>

class ElementClassEdditor : public Wt::WTemplate
{
public:
    ElementClassEdditor(std::string templateName = "stylus2.element.edditor");

    void setStyleClasses(std::string classes);
    Wt::Signal<std::string> &styleChanged() { return styleChanged_; }

    void resetStyles();
private:
    ElementSpacingWidget *spacingWidget_;
    ElementSizingWidget *sizingWidget_;

    std::string notFoundClasses = "";

    Wt::Signal<std::string> styleChanged_;

    std::string getStyles();

    // spacing regexp
    std::regex padding_regexp = std::regex("p[x,y,t,r,b,l]?-(?:96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|0|px|[\\[\\S]*\\])");
    std::regex margin_regexp =  std::regex("-?m[x,y,t,r,b,l]?-(?:auto|96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|0|px|[\\[\\S]*\\])");
    std::regex space_regexp = std::regex("space-[x|y]?-(?:reverse|96|80|72|64|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|0|px|[\\[\\S]*\\])");

    // sizing regexp
    std::regex width_regexp = std::regex("(?: |^)w-(?:fit|max|min|screen|full|11\\/12|10\\/12|9\\/12|8\\/12|7\\/12|6\\/12|5\\/12|4\\/12|3\\/12|2\\/12|1\\/12|5\\/6|4\\/6|3\\/6|2\\/6|1\\/6|4\\/5|3\\/5|2\\/5|1\\/5|3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|auto|96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|px|0|\\[\\S*\\])");
    std::regex minWidth_regex = std::regex("min-w-(?:0|full|min|max|fit|\\[[\\S]*\\])");
    std::regex maxWidth_regex = std::regex("max-w-(?:0|none|xs|sm|md|ls|lg|xl|2xl|3xl|4xl|5xl|6xl|7xl|full|min|max|fit|prose|screen-sm|screen-md|screen-lg|screen-xl|screen-2x|\\[[\\S]*\\])");
    
    std::regex height_regexp = std::regex("(?: |^)h-(?:full|screen|min|max|fit|11\\/12|10\\/12|9\\/12|8\\/12|7\\/12|6\\/12|5\\/12|4\\/12|3\\/12|2\\/12|1\\/12|5\\/6|4\\/6|3\\/6|2\\/6|1\\/6|4\\/5|3\\/5|2\\/5|1\\/5|3\\/4|2\\/4|1\\/4|2\\/3|1\\/3|1\\/2|auto|96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3\\.5|3|2\\.5|2|1\\.5|1|0\\.5|px|0|\\[\\S*\\])");
    std::regex minHeight_regex = std::regex("min-h-(?:0|full|screen|min|max|fit|\\[[\\S]*\\])");
    std::regex maxHeight_regex = std::regex("max-h-(?:96|80|72|64|60|56|52|48|44|40|36|32|28|24|20|16|14|12|11|10|9|8|7|6|5|4|3.5|3|2.5|2|1.5|1|0.5|0|px|none|full|screen|min|max|fit|\\[[\\S]*\\])");
};
