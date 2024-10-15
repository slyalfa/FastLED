#include "slider.h"
#include "ui_manager.h"
#include <sstream>

jsSlider::jsSlider(const std::string& name, float min, float max, float value, float step)
    : jsUI(std::make_shared<jsUiInternal>(name, "slider", 
           [this](const char* jsonStr) { this->updateInternal(jsonStr); })),
      mMin(min), mMax(max), mValue(value), mStep(step) {
    jsUiManager::addComponent(std::weak_ptr<jsUiInternal>(getInternal()));
}

jsSlider::~jsSlider() {
    if (auto internal = getInternal()) {
        jsUiManager::removeComponent(std::weak_ptr<jsUiInternal>(internal));
        std::lock_guard<std::mutex> lock(mMutex);
        internal.reset();
        
    }
}

std::string jsSlider::type() const { 
    return "slider"; 
}

std::string jsSlider::toJsonStr() const {
    std::ostringstream oss;
    oss << "{\"type\":\"" << type() << "\""
        << ",\"name\":\"" << name() << "\""
        << ",\"id\":" << id()
        << ",\"min\":" << mMin
        << ",\"max\":" << mMax
        << ",\"value\":" << mValue
        << ",\"step\":" << mStep
        << "}";
    return oss.str();
}

float jsSlider::value() const { 
    return mValue; 
}

void jsSlider::updateInternal(const char* jsonStr) {
    // TODO: Implement JSON parsing to update slider values
    // For example:
    // rapidjson::Document d;
    // d.Parse(jsonStr);
    // if (d.HasMember("value") && d["value"].IsNumber()) {
    //     mValue = d["value"].GetFloat();
    // }
}

void jsSlider::setValue(float value) {
    mValue = std::max(mMin, std::min(mMax, value));
    // TODO: Notify UI of value change
}

jsSlider::operator float() const { 
    return mValue; 
}
