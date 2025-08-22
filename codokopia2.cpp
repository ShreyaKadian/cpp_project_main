#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

// g++ codokopia2.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o codokopia2
// ./codokopia2


int your_score = 0;
int ai_score = 0;
const int win = 10;


const float ball_r = 10.f;
const float pad_w = 10.f;
const float pad_h = 100.f;
const float pad_speed = 7.f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "PONG BITCH");
    window.setFramerateLimit(60);

    sf::SoundBuffer hit_peddle, hit_score;
    if (!hit_peddle.loadFromFile("hit.wav") || !hit_score.loadFromFile("scoreup.wav")) {
        return -1;
    }

    sf::Sound sound_hit_paddle(hit_peddle);
    sf::Sound sound_score(hit_score);

    sf::RectangleShape pad_player(sf::Vector2f(pad_w, pad_h));
    pad_player.setFillColor(sf::Color::White);
    pad_player.setPosition(50.f, 250.f);

    sf::RectangleShape pad_ai(sf::Vector2f(pad_w, pad_h));
    pad_ai.setFillColor(sf::Color::White);
    pad_ai.setPosition(740.f, 250.f);

    sf::Vector2f ball_v(8.f, 8.f);
    sf::CircleShape ball(ball_r);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(400.f, 300.f);

    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return -1;
    }

    sf::Text score_display;
    score_display.setFont(font);
    score_display.setCharacterSize(30);
    score_display.setFillColor(sf::Color::Red);
    score_display.setPosition(310.f, 20.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && pad_player.getPosition().y > 0)
            pad_player.move(0.f, -pad_speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && pad_player.getPosition().y + pad_h < 600)
            pad_player.move(0.f, pad_speed);

        if (pad_ai.getPosition().y + pad_h / 2 < ball.getPosition().y + ball_r) {
            if (pad_ai.getPosition().y + pad_h < 600)
                pad_ai.move(0.f, pad_speed - 1.f);
        }
        else if (pad_ai.getPosition().y + pad_h / 2 > ball.getPosition().y + ball_r) {
            if (pad_ai.getPosition().y > 0)
                pad_ai.move(0.f, -pad_speed + 1.f);
        }

        ball.move(ball_v);

        if (ball.getPosition().y <= 0 || ball.getPosition().y + ball_r * 2 >= 600)
            ball_v.y *= -1.f;

        if (ball.getPosition().x <= 0) {
            ai_score++;
            sound_score.play();
            ball.setPosition(400.f, 300.f);
            ball_v.x = std::abs(ball_v.x);

            if (ai_score >= win) {
                score_display.setString("Haha loser " + std::to_string(your_score) + "-" + std::to_string(ai_score));
                window.clear();
                window.draw(score_display);
                window.display();
                sf::sleep(sf::seconds(3));
                window.close();
            }
        }

        if (ball.getPosition().x + ball_r * 2 >= 800) {
            your_score++;
            sound_score.play();
            ball.setPosition(400.f, 300.f);
            ball_v.x = -std::abs(ball_v.x);

            if (your_score >= win) {
                score_display.setString("GG u win " + std::to_string(your_score) + "-" + std::to_string(ai_score));
                window.clear();
                window.draw(score_display);
                window.display();
                sf::sleep(sf::seconds(3));
                window.close();
            }
        }

        sf::FloatRect ball_border = ball.getGlobalBounds();
        sf::FloatRect player_border = pad_player.getGlobalBounds();
        sf::FloatRect ai_border = pad_ai.getGlobalBounds();

        if (ball_v.x < 0 && ball_border.intersects(player_border)) {
            ball_v.x = std::abs(ball_v.x);
            sound_hit_paddle.play();
        }
        else if (ball_v.x > 0 && ball_border.intersects(ai_border)) {
            ball_v.x = -std::abs(ball_v.x);
            sound_hit_paddle.play();
        }

        std::stringstream s;
        s << "You - " << your_score << "    Robot - " << ai_score;
        score_display.setString(s.str());

        window.clear();
        window.draw(pad_player);
        window.draw(pad_ai);
        window.draw(ball);
        window.draw(score_display);
        window.display();
    }

    return 0;
}
