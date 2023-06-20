#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

std::vector<std::pair<double, double>> create_three_dots(sf::RenderWindow& window) {
    std::pair<int, int> dot1, dot2, dot3;
    dot1.first = window.getSize().x / 2.0;
    dot1.second = 0;
    dot2.first = 0;
    dot2.second = window.getSize().y;
    dot3.first = window.getSize().x;
    dot3.second = window.getSize().y;
    return {dot1, dot2, dot3};
}

void init(sf::RenderWindow& window, sf::RectangleShape& pixel, const std::vector<std::pair<double, double>>& dots) {
    pixel.setFillColor(sf::Color::White);
    pixel.setPosition(dots[0].first, dots[0].second);
    window.draw(pixel);
    pixel.setPosition(dots[1].first, dots[1].second);
    window.draw(pixel);
    pixel.setPosition(dots[2].first, dots[2].second);
    window.draw(pixel);
}

void move(std::pair<double, double>& pos, const std::vector<std::pair<double, double>>& dots) {
    auto dest = dots[rand() % dots.size()];
    double dx = dest.first - pos.first;
    double dy = dest.second - pos.second;
    pos.first += dx / 2.0;
    pos.second += dy / 2.0;
}

int main() {
    srand((unsigned) time(0));
    using vid = sf::VideoMode;
    sf::RenderWindow window(vid(vid::getDesktopMode().width / 1.1, vid::getDesktopMode().height / 1.1), "Sierpinski's Triangle", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width * 0.5 - window.getSize().x * 0.5,
                                    sf::VideoMode::getDesktopMode().height * 0.5 - window.getSize().y * 0.5));

    sf::Event event;
    sf::RectangleShape pixel(sf::Vector2f(1, 1));
    auto dots = create_three_dots(window);
    init(window, pixel, dots);
    std::pair<double, double> pos(window.getSize().x / 2.0, window.getSize().y / 2.0);

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        pixel.setPosition(pos.first, pos.second);
        window.draw(pixel);
        window.display();
        move(pos, dots);
    }

    return 0;
}