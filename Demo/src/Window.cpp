#include "Window.h"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"

#include <cstdio>

Window::Window(std::string title, sf::Vector2u size) {
    this->window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(size.x, size.y), title, sf::Style::Default,
            sf::ContextSettings(0, 0, 8));

    if (!ImGui::SFML::Init(*window)) {
        printf("Initializing ImGui with SFML failed!\n");
        return;
    }

    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void Window::clear(sf::Color color) { window->clear(color); }

void Window::render() {
    ImGui::SFML::Render(*window);
    window->display();
}

Window::~Window() { ImGui::SFML::Shutdown(); }

bool Window::isOpen() { return window->isOpen(); }

void Window::handleEvents() {
    sf::Event event{};

    while (window->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(*window, event);

        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void Window::drawUI() {
    // make the whole window dockable
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(),
                                 ImGuiDockNodeFlags_PassthruCentralNode);

    // metrics window
    ImGui::Begin("Metrics"); // begins a new window with a name
    ImGui::Text("FPS: %.2f",
                ImGui::GetIO().Framerate); // displays the fps as a text
    ImGui::Text("Frame time: %.2f ms",
                1000.0f /
                ImGui::GetIO().Framerate); // displays the frame times as text
    static float values[90] = {0};
    static int values_offset = 0;
    values[values_offset] = 1000.0f / ImGui::GetIO().Framerate;
    values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
    ImGui::PlotLines("Frame\ntimes", values, IM_ARRAYSIZE(values), values_offset,
                     nullptr, 0.0f, 100.0f,
                     ImVec2(0, 80)); // displays the frame times as a chart
    ImGui::End();                    // ends the window

    // example window
    ImGui::Begin("Examples");
    if (ImGui::TreeNode("Basic")) {
        if (ImGui::BeginTable("table1", 2)) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Basic example");
            ImGui::TableSetColumnIndex(1);
            ImGui::SmallButton("Load");
            ImGui::EndTable();
        }

        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Advanced")) {
        if (ImGui::BeginTable("table2", 2)) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Advanced example");
            ImGui::TableSetColumnIndex(1);
            ImGui::SmallButton("Load");
            ImGui::EndTable();
        }

        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Explosions")) {
        if (ImGui::BeginTable("table3", 2)) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Explosions example");
            ImGui::TableSetColumnIndex(1);
            ImGui::SmallButton("Load");
            ImGui::EndTable();
        }

        ImGui::TreePop();
    }
    ImGui::End();

    ImGui::Begin("Physics config");
    ImGui::Text("Physics config");
    ImGui::End();
}

void Window::drawRectangle(fy::Rectangle *rectangle) const {
    sf::VertexArray lines(sf::LinesStrip, 5);
    fy::Mat2x2 rotation(rectangle->rotation);
    fy::Vec2 half(rectangle->width * 0.5f, rectangle->height * 0.5f);

    fy::Vec2 v1 = rectangle->position + rotation * fy::Vec2(-half.x, -half.y);
    fy::Vec2 v2 = rectangle->position + rotation * fy::Vec2(half.x, -half.y);
    fy::Vec2 v3 = rectangle->position + rotation * fy::Vec2(half.x, half.y);
    fy::Vec2 v4 = rectangle->position + rotation * fy::Vec2(-half.x, half.y);

    sf::Vertex rect[5] = {
            sf::Vertex(sf::Vector2f(v1.x, v1.y), colors[6]),
            sf::Vertex(sf::Vector2f(v2.x, v2.y), colors[6]),
            sf::Vertex(sf::Vector2f(v3.x, v3.y), colors[6]),
            sf::Vertex(sf::Vector2f(v4.x, v4.y), colors[6]),
            sf::Vertex(sf::Vector2f(v1.x, v1.y), colors[6])
    };

    window->draw(rect, 5, sf::LineStrip);
}
