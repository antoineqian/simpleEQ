//
//  RotarySliderWithLabels.cpp
//  Simple EQ - VST3
//
//  Created by Antoine Qian on 7/5/22.
//  Copyright © 2022 Hsian. All rights reserved.
//

#include "RotarySliderWithLabels.hpp"

void RotarySliderWithLabels::paint(juce::Graphics &g){
    using namespace juce;
    auto startAng = degreesToRadians(180.0f + 45.f);
    auto endAng = degreesToRadians(180.f - 45.f) + MathConstants<float>::twoPi;
    auto range = getRange();
    auto sliderBounds = getSliderBounds();
    
    getLookAndFeel().drawRotarySlider(g,
                                      sliderBounds.getX(),
                                      sliderBounds.getY(),
                                      sliderBounds.getWidth(),
                                      sliderBounds.getHeight(),
                                      jmap(getValue(), range.getStart(), range.getEnd(), 0.0, 1.0) ,
                                      startAng,
                                      endAng,
                                      *this);
    auto center = sliderBounds.toFloat().getCentre();
    auto radius = sliderBounds.getWidth() * 0.5f;
    g.setColour(Colour(0u,172u, 1u));
    g.setFont(getTextHeight());
    auto numChoices = labels.size();
    for (int i =0; i< numChoices; ++i){
        auto pos = labels[i].pos;
        jassert(0.f <= pos);
        jassert(pos <= 1.f);
        auto ang = jmap(pos, 0.f, 1.f, startAng, endAng);
        auto c = center.getPointOnCircumference(radius + getTextHeight() * 0.5 + 1, ang);
        Rectangle<float> r;
        
        auto str = labels[i].label;
        r.setSize(g.getCurrentFont().getStringWidth(str), getTextHeight());
        r.setCentre(c);
        r.setY(r.getY() + getTextHeight());
        g.drawFittedText(str, r.toNearestInt(), juce::Justification::centred, 1);
    }
}

juce::Rectangle<int> RotarySliderWithLabels::getSliderBounds() const {
    auto bounds = getLocalBounds();
    auto size = juce::jmin(bounds.getWidth(), bounds.getHeight());
    
    size -= getTextHeight() * 2;
    
    juce::Rectangle<int> r;
    r.setSize(size, size);
    r.setCentre(bounds.getCentreX(), 0);
    r.setY(2);
    return r;
}

juce::String RotarySliderWithLabels::getDisplayString() const {
    if (auto* choiceParam = dynamic_cast<juce::AudioParameterChoice*>(param)){
        return choiceParam->getCurrentChoiceName();
    }
    juce::String str;
    bool addK = false;
    if (auto* choiceParam = dynamic_cast<juce::AudioParameterFloat*>(param)){
        float val = getValue();
        if (val > 999.f){
            val/=1000.f;
            addK = true;
        }
        str = juce::String(val, (addK ? 2: 0));
    } else {
        jassert(false);
    }
    if (suffix.isNotEmpty()){
        str << " ";
        if (addK){
            str <<  "k";
        }
        str << suffix;
    }
    
    return str;
}
