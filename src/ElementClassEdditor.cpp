#include "include/ElementClassEdditor.h"
#include "include/TailwindRegexp.h"

std::vector<std::string> findAndRemoveMatches(std::regex regex, std::string& str) {
    
    std::regex_iterator<std::string::iterator> it(str.begin(), str.end(), regex);
    std::regex_iterator<std::string::iterator> end;
    std::string result = "";

    std::vector<std::string> matches;

    size_t lastPos = 0;
    while (it != end) {
        result += str.substr(lastPos, it->position() - lastPos);
        matches.push_back(it->str()); // Store deleted value in vector
        lastPos = it->position() + it->length();
        ++it;
    }
    // remove padding classes from classes string
    str = result + str.substr(lastPos, str.length() - lastPos);
    return matches;
}

std::string findAndRemoveMatche(std::regex regex, std::string& str) {
        
        std::regex_iterator<std::string::iterator> it(str.begin(), str.end(), regex);
        std::regex_iterator<std::string::iterator> end;
        std::string result = "";
    
        std::string match = "";
    
        size_t lastPos = 0;
        while (it != end) {
            result += str.substr(lastPos, it->position() - lastPos);
            match = it->str(); // Store deleted value in vector
            lastPos = it->position() + it->length();
            ++it;
        }
        // remove padding classes from classes string
        str = result + str.substr(lastPos, str.length() - lastPos);
        // clean start whitespace from match
        match = std::regex_replace(match, std::regex("^\\s+"), "");
        return match;
}


ElementClassEdditor::ElementClassEdditor(std::string templateName)
    : WTemplate(tr(templateName))
{
    spacingWidget_ = bindWidget("stylus2.spacing.template", std::make_unique<ElementSpacingWidget>());
    sizingWidget_ = bindWidget("stylus2.sizing.template", std::make_unique<ElementSizingWidget>());
    
    spacingWidget_->styleChanged().connect(this, [=](){ styleChanged_.emit(getStyles()); });
    sizingWidget_->styleChanged().connect(this, [=](){ styleChanged_.emit(getStyles()); });
}

void ElementClassEdditor::setStyleClasses(std::string classes)
{
    // clean any multiple whitespaces from the string
    classes = std::regex_replace(classes, std::regex("\\s+"), " ");
    // std::cout << "\n\n classes from Element Class Edditor :" << classes << "\n\n";
    // create vector of classes for spacing
    SpacingData spacing;
    spacing.padding = findAndRemoveMatches(padding_regexp, classes);
    spacing.margin = findAndRemoveMatches(margin_regexp, classes);
    spacing.space = findAndRemoveMatches(space_regexp, classes);

    // create vector of classes for sizing
    SizingData sizing;
    sizing.width = findAndRemoveMatche(width_regexp, classes);
    sizing.minWidth = findAndRemoveMatche(minWidth_regex, classes);
    sizing.maxWidth = findAndRemoveMatche(maxWidth_regex, classes);
    sizing.height = findAndRemoveMatche(height_regexp, classes);
    sizing.minHeight = findAndRemoveMatche(minHeight_regex, classes);
    sizing.maxHeight = findAndRemoveMatche(maxHeight_regex, classes);
    // remove whitespace from start of classes string and store it in notFoundClasses
    notFoundClasses = std::regex_replace(classes, std::regex("^\\s+"), "");


    // console values
    std::cout << "padding classes: <";
    for (auto& paddingClass : spacing.padding) {
        std::cout << paddingClass << ",";
    }
    std::cout << ">\nmargin classes: <";
    for (auto& marginClass : spacing.margin) {
        std::cout << marginClass << ",";
    }
    std::cout << ">\nspacing classes: <";
    for (auto& spacingClass : spacing.space) {
        std::cout << spacingClass << ",";
    }
    std::cout << ">\nwidth: <" << sizing.width << ">\n";
    std::cout << "min width: <" << sizing.minWidth << ">\n";
    std::cout << "max width: <" << sizing.maxWidth << ">\n";
    std::cout << "height: <" << sizing.height << ">\n";
    std::cout << "min height: <" << sizing.minHeight << ">\n";
    std::cout << "max height: <" << sizing.maxHeight << ">\n";
    std::cout << "\n\n";
    std::cout << "\n remaining classes :"<< notFoundClasses << "\n\n -------------------";


    spacingWidget_->setClasses(spacing);
    sizingWidget_->setClasses(sizing);

}

std::string ElementClassEdditor::getStyles()
{
    std::string styles = spacingWidget_->getStyles() + " ";
    styles += sizingWidget_->getStyles() + " ";
    styles += notFoundClasses;
    return styles;
}

void ElementClassEdditor::resetStyles()
{
    sizingWidget_->resetStyles();
    spacingWidget_->resetStyles();
}
