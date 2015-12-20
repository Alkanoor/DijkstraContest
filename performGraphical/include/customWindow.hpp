#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <cmath>


class CustomWindow
{
    public:
        CustomWindow(unsigned int width, unsigned int height, const std::string& title);

        void setEnvironment(const std::vector<float>& environment);
        void setTrajectory(const std::vector<float>& points);

        void runUntilQuit();

    private:
        std::shared_ptr<sf::RenderWindow> window;
        sf::View view;

        float robotRadius;
        std::vector<std::shared_ptr<sf::Shape> > shapesToRender;
        std::vector<sf::Vertex> line1;
        std::vector<sf::Vertex> line2;

        void draw();
};
