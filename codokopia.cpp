#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <ctime>


//  g++ codokopia.cpp -lsfml-graphics -lsfml-window -lsfml-system -o codokopia
// ./codokopia




int tetristhingy[4][4];
int temp[4][4];

const int cell_size = 30;
const int big_columns = 15;
const int big_rows = 20;


int score = 0;
bool over = false;
sf::Font font;
sf::Text text;
int board[big_rows][big_columns] = {0};

std::vector<std::array<std::array<int, 4>, 4>> pieces = {
    {{{0, 0, 0, 0},
      {1, 1, 1, 1},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}},
    {{{1, 1, 0, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}},
    {{{0, 1, 0, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}},
    {{{0, 1, 1, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}},
    {{{1, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}},
    {{{0, 0, 1, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}},
    {{{1, 0, 0, 0},
      {1, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}}}
};

void newpiecebih() {
    int id = rand() % pieces.size();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            tetristhingy[i][j] = pieces[id][i][j];
}

void roundround() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            temp[i][j] = tetristhingy[i][j];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            tetristhingy[i][j] = temp[3 - j][i];
}

bool checkCollision(int newX, int newY, int shape[4][4]) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (shape[y][x]) {
                int gridX = newX + x;
                int gridY = newY + y;
                if (gridX < 0 || gridX >= big_columns || gridY >= big_rows)
                    return true;
                if (gridY >= 0 && board[gridY][gridX])
                    return true;
            }
        }
    }
    return false;
}


void byeline() {
    for (int row = big_rows - 1; row >= 0; row--) {
        bool full = true;
        for (int col = 0; col < big_columns; col++) {
            if (board[row][col] == 0) {
                full = false;
                break;
            }
        }

        if (full) {
            for (int y = row; y > 0; y--)
                for (int x = 0; x < big_columns; x++)
                    board[y][x] = board[y - 1][x];

            for (int x = 0; x < big_columns; x++)
                board[0][x] = 0;

            score += 100;
            row++;
        }
    }
}

int main() {
    srand(time(0));
    newpiecebih();

    font.loadFromFile("sansation.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);

    sf::ContextSettings settings;
    settings.majorVersion = 1;
    settings.minorVersion = 1;

    sf::RenderWindow window(sf::VideoMode(big_columns * cell_size, big_rows * cell_size), "Tetris", sf::Style::Default, settings);

    sf::Clock clock;
    float timer = 0;
    float delay = 0.5f;
    float move_delay = 0.1f;
    float move_timer = 0;

    int x = 3;
    int y = 0;

    while (window.isOpen()) {
        float time = clock.restart().asSeconds();
        timer += time;
        move_timer += time;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!over) {
            text.setString("Score: " + std::to_string(score));

            if (move_timer > move_delay) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !checkCollision(x - 1, y, tetristhingy)) {
                    x--;
                    move_timer = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !checkCollision(x + 1, y, tetristhingy)) {
                    x++;
                    move_timer = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !checkCollision(x, y + 1, tetristhingy)) {
                    y++;
                    move_timer = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    roundround();
                    if (checkCollision(x, y, tetristhingy))
                        for (int i = 0; i < 4; i++)
                            for (int j = 0; j < 4; j++)
                                tetristhingy[i][j] = temp[i][j];
                    move_timer = 0;
                }
            }

            if (timer > delay) {
                if (!checkCollision(x, y + 1, tetristhingy)) {
                    y++;
                } else {
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (tetristhingy[j][i]) {
                                int gridX = x + i;
                                int gridY = y + j;
                                if (gridY >= 0 && gridY < big_rows && gridX >= 0 && gridX < big_columns)
                                    board[gridY][gridX] = 1;
                            }
                        }
                    }
                    byeline();
                    x = 3;
                    y = 0;
                    newpiecebih();

                    if (checkCollision(x, y, tetristhingy))
                        over = true;
                }
                timer = 0;
            }
        }

        window.clear(sf::Color::Black);

        for (int row = 0; row < big_rows; row++) {
            for (int col = 0; col < big_columns; col++) {
                if (board[row][col]) {
                    sf::RectangleShape cell(sf::Vector2f(cell_size - 1, cell_size - 1));
                    cell.setPosition(col * cell_size, row * cell_size);
                    cell.setFillColor(sf::Color::Cyan);
                    window.draw(cell);
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tetristhingy[j][i] == 1) {
                    sf::RectangleShape block(sf::Vector2f(cell_size - 1, cell_size - 1));
                    block.setPosition((x + i) * cell_size, (y + j) * cell_size);
                    block.setFillColor(sf::Color::Red);
                    window.draw(block);
                }
            }
        }

        window.draw(text);

        if (over) {
            sf::Text bye_text;
            bye_text.setFont(font);
            bye_text.setCharacterSize(40);
            bye_text.setFillColor(sf::Color::Red);
            bye_text.setString("Game over bruh");
            bye_text.setPosition(big_columns * cell_size / 4, big_rows * cell_size / 2 - 50);
            window.draw(bye_text);
        }

        window.display();
    }

    return 0;
}
