#include "Solar/Modes/Scene/Pipelines/Init/LoadSettings.hpp"
#include "Solar/Config.hpp"

static void __SolarModesScenePipelinesInitLoadSettingsWindowSection(
    Solar::Modes::Scene::Mode* mode,
    Sojson::Node* input
)
{
    Sojson::Node* window_node = Sojson::NodeGet(input, "window");
    Sojson::Node* window_width_node;
    Sojson::Node* window_height_node;
    Sojson::Node* window_title_node;
    Sojson::Node* window_icon_node;

    if(window_node != nullptr)
    {
        const Progator::Types::Specifics::Window::Size width = 
            mode->shared->units.main->window->geometry.width;
        const Progator::Types::Specifics::Window::Size height=
            mode->shared->units.main->window->geometry.height;
        const Sojson::Types::String title = 
            "[" SOLAR_VERSION_FULL "]";
        /* Set the window properties width / height: */
        window_width_node = Sojson::NodeGet(window_node, "width");
        window_height_node= Sojson::NodeGet(window_node, "height");
        auto possibly_window_width = Sojson::CastNode::Integer(window_width_node);
        auto possibly_window_height= Sojson::CastNode::Integer(window_height_node);
        Progator::Base::WindowSetSize(
            mode->shared->units.main->window,
            possibly_window_width.value_or(width),
            possibly_window_height.value_or(height)
        );
        /* Set the title: */
        window_title_node = Sojson::NodeGet(window_node, "title");
        auto possibly_window_title = Sojson::CastNode::String(window_title_node);
        Progator::Base::WindowSetTitle(
            mode->shared->units.main->window,
            possibly_window_title.value_or(title).c_str()
        );
    }

    return;
}

static void __SolarModesScenePipelinesInitLoadSettingsRendererSection(
    Solar::Modes::Scene::Mode* mode,
    Sojson::Node* input
)
{
    return;
}

static void __SolarModesScenePipelinesInitLoadSettingsEngineSection(
    Solar::Modes::Scene::Mode* mode,
    Sojson::Node* input
)
{
    Sojson::Node* engine_node = Sojson::NodeGet(input, "engine");
    Sojson::Node* engine_tick_rate;
    Sojson::Node* engine_draw_rate;
    
    if(engine_node != nullptr)
    {
        const Solar::Types::Basic::U8 current_tick_rate = 
            mode->shared->basics.tick_rate;
        const Solar::Types::Basic::U8 current_draw_rate =
            mode->shared->basics.draw_rate;
        engine_tick_rate = Sojson::NodeGet(engine_node, "tick_rate");
        auto possibly_engine_tick_rate = Sojson::CastNode::Integer(engine_tick_rate);
        engine_draw_rate = Sojson::NodeGet(engine_node, "draw_rate");
        auto possibly_engine_draw_rate = Sojson::CastNode::Integer(engine_draw_rate);
        mode->shared->basics.tick_rate = 
            (Solar::Types::Basic::U8)(possibly_engine_tick_rate.value_or(current_tick_rate));
        mode->shared->basics.draw_rate =
            (Solar::Types::Basic::U8)(possibly_engine_draw_rate.value_or(current_draw_rate));
    }
}

void Solar::Modes::Scene::Pipelines::Init::LoadSettings(
    Solar::Modes::Scene::Mode *mode
)
{
    /* Load the root:Settings DataFile, it will be essential to do what we want: 
     * What exactly we want?
     * 1-) extract the window information (title, size, features ...);
     * 2-) some renderer properties (viewport and more);
     * 3-) some engine properties;
     */
    Sojson::Node* current_node = Solar::Core::Provider::Load::DataFile(
        &mode->shared->warehouse,
        "root:Settings"
    );
    if(current_node)
    {
        /* If there is the file, then proceed to load: */
        __SolarModesScenePipelinesInitLoadSettingsWindowSection(mode, current_node);
        __SolarModesScenePipelinesInitLoadSettingsRendererSection(mode, current_node);
        __SolarModesScenePipelinesInitLoadSettingsEngineSection(mode, current_node);
    }
}