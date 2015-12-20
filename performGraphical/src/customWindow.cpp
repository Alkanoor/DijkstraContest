#include "../include/customWindow.hpp"


CustomWindow::CustomWindow(unsigned int width, unsigned int height, const std::string& title) :
    robotRadius(0)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 6;

    window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default, settings));
}

void CustomWindow::setEnvironment(const std::vector<float>& environment)
{
    view = sf::View(sf::FloatRect(0, 0, environment[0], environment[1]));

    robotRadius = environment[2];

    for(unsigned int i=7;i+4<environment.size();i+=5)
    {
        std::shared_ptr<sf::Shape> rectangle(new sf::RectangleShape(sf::Vector2f((environment[i+1]-1)*2,(environment[i+3]-1)*2)));
        rectangle->setOrigin(environment[i+1]-1,environment[i+3]-1);
        rectangle->setRotation(environment[i+4]);
        rectangle->setPosition(environment[i],environment[i+2]);
        rectangle->setFillColor(sf::Color(20, 0, 150));
        rectangle->setOutlineThickness(1);
        rectangle->setOutlineColor(sf::Color::Black);
        shapesToRender.push_back(rectangle);
    }

    std::shared_ptr<sf::Shape> circle1(new sf::CircleShape(environment[2]-1));
    circle1->setOrigin(environment[2]-1,environment[2]-1);
    circle1->setPosition(environment[3],environment[4]);
    circle1->setFillColor(sf::Color(230, 150, 25));
    circle1->setOutlineThickness(1);
    circle1->setOutlineColor(sf::Color::Black);

    std::shared_ptr<sf::Shape> circle2(new sf::CircleShape(environment[2]-1));
    circle2->setOrigin(environment[2]-1,environment[2]-1);
    circle2->setPosition(environment[5],environment[6]);
    circle2->setFillColor(sf::Color(150, 200, 25));
    circle2->setOutlineThickness(1);
    circle2->setOutlineColor(sf::Color::Black);

    shapesToRender.push_back(circle1);
    shapesToRender.push_back(circle2);
}

void CustomWindow::setTrajectory(const std::vector<float>& points)
{
    for(unsigned int i=0;i+3<points.size();i+=2)
    {
        sf::Vector2f v(points[i+2]-points[i],points[i+3]-points[i+1]);
        if(fabs(v.x)<0.00001)
        {
            line1.push_back(sf::Vertex(sf::Vector2f(points[i]+robotRadius, points[i+1]),sf::Color::Red));
            line1.push_back(sf::Vertex(sf::Vector2f(points[i+2]+robotRadius, points[i+3]),sf::Color::Red));
            line2.push_back(sf::Vertex(sf::Vector2f(points[i]-robotRadius, points[i+1]),sf::Color::Red));
            line2.push_back(sf::Vertex(sf::Vector2f(points[i+2]-robotRadius, points[i+3]),sf::Color::Red));
        }
        else
        {
            float angle = atan(v.y/v.x);
            line1.push_back(sf::Vertex(sf::Vector2f(points[i]-robotRadius*sin(angle), points[i+1]+robotRadius*cos(angle)),sf::Color::Red));
            line1.push_back(sf::Vertex(sf::Vector2f(points[i+2]-robotRadius*sin(angle), points[i+3]+robotRadius*cos(angle)),sf::Color::Red));
            line2.push_back(sf::Vertex(sf::Vector2f(points[i]+robotRadius*sin(angle), points[i+1]-robotRadius*cos(angle)),sf::Color::Red));
            line2.push_back(sf::Vertex(sf::Vector2f(points[i+2]+robotRadius*sin(angle), points[i+3]-robotRadius*cos(angle)),sf::Color::Red));
        }
    }
}

void CustomWindow::runUntilQuit()
{
    window->setView(view);
    while(window->isOpen())
    {
        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window->close();
        }

        if(window->isOpen())
            draw();
        sf::sleep(sf::milliseconds(50));
    }
}

void CustomWindow::draw()
{
    window->clear(sf::Color::White);

    for(unsigned int i=0;i<shapesToRender.size();i++)
        window->draw(*(shapesToRender[i]));

    window->draw(&(line1[0]), line1.size(), sf::LinesStrip);
    window->draw(&(line2[0]), line2.size(), sf::LinesStrip);

    window->display();
}
