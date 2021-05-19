/*
    Copyright 2019-2021 natinusala
    Copyright 2019 p-sam
    Copyright 2021 XITRIX

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include <borealis/core/box.hpp>
#include <borealis/core/event.hpp>
#include <borealis/views/applet_frame.hpp>
#include <borealis/views/recycler.hpp>
#include <borealis/views/hint.hpp>
#include <string>

namespace brls
{

// Fired when the user has selected a value
//
// Parameter is either the selected value index
// or -1 if the user cancelled
//
// Assume that the Dropdown is deleted
// as soon as this function is called
typedef Event<int> ValueSelectedEvent;

// Allows the user to select between multiple
// values
// Use Dropdown::open()
class Dropdown : public Box, private RecyclerDataSource
{
  private:
    BRLS_BIND(RecyclerFrame, recycler, "brls/dropdown/recycler");
    BRLS_BIND(Box, header, "brls/dropdown/header");
    BRLS_BIND(Label, title, "brls/dropdown/title_label");
    BRLS_BIND(Box, content, "brls/dropdown/content");
    BRLS_BIND(AppletFrame, applet, "brls/dropdown/applet");
    BRLS_BIND(Hints, hints, "brls/dropdown/hints");
    ValueSelectedEvent::Callback cb;
    std::vector<std::string> values;
    size_t selected;
    Animatable showOffset = 0;

    int numberOfRows(RecyclerFrame* recycler, int section) override;
    RecyclerCell* cellForRow(RecyclerFrame* recycler, IndexPath index) override;
    void didSelectRowAt(RecyclerFrame* recycler, IndexPath index) override;
    
    void offsetTick();

  protected:
    float getShowAnimationDuration(TransitionAnimation animation) override;

  public:
    Dropdown(std::string title, std::vector<std::string> values, ValueSelectedEvent::Callback cb, int selected = 0);

    //    ~Dropdown();

    //    View* getDefaultFocus() override;
    //    virtual bool onCancel();
    void show(std::function<void(void)> cb, bool animate, float animationDuration) override;
    void hide(std::function<void(void)> cb, bool animated, float animationDuration) override;
    //    void willAppear(bool resetState = false) override;
    //    void willDisappear(bool resetState = false) override;
    //
    //    static void open(std::string title, std::vector<std::string> values, ValueSelectedEvent::Callback cb, int selected = -1);

    virtual AppletFrame* getAppletFrame() override;

    bool isTranslucent() override
    {
        return true || View::isTranslucent();
    }
};

} // namespace brls
