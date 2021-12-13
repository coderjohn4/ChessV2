// -lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp>
#include <tuple>
#include <iostream>
using namespace std;

class Piece
{
    public:
        std::string type, color;
        sf::Sprite spriteNew;

        void drawPiece(int squareX, int squareY)
        {

            spriteNew.setTexture(*textureptr);
            int cutX = 0;
            int cutY = 0;

            if(type == "rook"  ) cutX = 4;
            if(type == "knight") cutX = 3;
            if(type == "bishop") cutX = 2;
            if(type == "king"  ) cutX = 0;
            if(type == "queen" ) cutX = 1;
            if(type == "pawn"  ) cutX = 5;

            if(color == "white") cutY = 0;
            if(color == "black") cutY = 1;

            spriteNew.setTextureRect(sf::IntRect(spriteWidth*cutX, spriteHeight*cutY, spriteWidth, spriteHeight));            
            spriteNew.setPosition(sf::Vector2f(16+chessSquareWidth*squareX, 6+chessSquareHeight*squareY));
            spriteNew.setScale(0.2f, 0.2f);
            windowptr->draw(spriteNew);
            
        };

        Piece(sf::RenderWindow* window, sf::Texture* texture,  std::string p_color, std::string p_type)
        {    
            windowptr  = window;
            type       = p_type;
            color      = p_color;
            textureptr = texture;
        }

    private:

        sf::RenderWindow* windowptr;
        sf::Texture* textureptr;

        float spriteWidth       = 1280/6;
        float spriteHeight      = 427/2;
        float chessSquareWidth  = (352-16)/7; 
        float chessSquareHeight = (338-6)/7;
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Chess");
    sf::Vector2i windowPos(550,100);
    window.setPosition(windowPos);
    
    sf::Texture chessTexture;
    chessTexture.setSmooth(true);

    sf::Vector2i mousePosition;

    if (!chessTexture.loadFromFile("spritesheet.png")) std::cout << "[ERROR]" << endl;
    
    Piece* chessboard[8][8] = {nullptr};
    
    chessboard[0][0] = new Piece(&window, &chessTexture, "white","rook");
    chessboard[1][0] = new Piece(&window, &chessTexture, "white","knight");
    chessboard[2][0] = new Piece(&window, &chessTexture, "white","bishop");
    chessboard[3][0] = new Piece(&window, &chessTexture, "white","king");
    chessboard[4][0] = new Piece(&window, &chessTexture, "white","queen");
    chessboard[5][0] = new Piece(&window, &chessTexture, "white","bishop");
    chessboard[6][0] = new Piece(&window, &chessTexture, "white","knight");
    chessboard[7][0] = new Piece(&window, &chessTexture, "white","rook");
    for(int i = 0; i < 8; i++) chessboard[i][1] = new Piece(&window, &chessTexture, "white","pawn");

    chessboard[0][7] = new Piece(&window, &chessTexture, "black","rook");
    chessboard[1][7] = new Piece(&window, &chessTexture, "black","knight");
    chessboard[2][7] = new Piece(&window, &chessTexture, "black","bishop");
    chessboard[3][7] = new Piece(&window, &chessTexture, "black","king");
    chessboard[4][7] = new Piece(&window, &chessTexture, "black","queen");
    chessboard[5][7] = new Piece(&window, &chessTexture, "black","bishop");
    chessboard[6][7] = new Piece(&window, &chessTexture, "black","knight");
    chessboard[7][7] = new Piece(&window, &chessTexture, "black","rook");
    for(int i = 0; i < 8; i++) chessboard[i][6] = new Piece(&window, &chessTexture, "black","pawn");

    // cout << chessboard[0][0]->color << chessboard[0][0]->type << endl;

    sf::Texture texture;
    if (!texture.loadFromFile("chessboard.png")) std::cout << "[ERROR]" << endl;
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::RectangleShape* gameGrid[8][8] = {nullptr};
    sf::Vector2f rectSize(47.3f, 47.3f);

    while(window.isOpen())
    {
        sf::Event ev;
        while(window.pollEvent(ev))
        {
            if(ev.type == sf::Event::Closed) window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {   
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                // cout << mousePosition.x << " " <<  mousePosition.y << endl;
                int mouseX = mousePosition.x/50;
                int mouseY = mousePosition.y/50;

                string xycolor;
                string xytype;
                // sf::Sprite spriteNew;

                xycolor = chessboard[mouseX][mouseY]->color;          
                xytype = chessboard[mouseX][mouseY]->type; 

                gameGrid[mouseX][mouseY]->setFillColor(sf::Color::Green);

                // void move()
                // {
                //     int newposx;
                //     int newposy;

                //     chessboard[mouseX][mouseY] = nullptr;
                };
                // Piece* selectedPiece = new Piece(&window, &chessTexture, xycolor, xytype );
                // if(selectedPiece != NULL) cout << selectedPiece->type << " " << selectedPiece->color << endl;
              
            }
        }

        window.clear();
        window.draw(sprite);

        for(int y=0; y<8; y++)
        {
            for(int x = 0; x < 8; x++)
            {   
                if(chessboard[x][y] != nullptr){
                    chessboard[x][y]->drawPiece(x,y);        
                }
            }
        }

        for(int y=0; y<8; y++)
        {
            for(int x = 0; x < 8; x++)
            {   
                gameGrid[x][y] = new sf::RectangleShape;
                gameGrid[x][y]->setSize(rectSize);
                gameGrid[x][y]->setPosition(16+y*rectSize.x, 6+x*rectSize.y);  
                gameGrid[x][y]->setOutlineColor(sf::Color::Red);
                // gameGrid[x][y]->setFillColor(sf::Color::Transparent);
                gameGrid[x][y]->setOutlineThickness(1);
                window.draw(*gameGrid[x][y]);
            }
        }

        
        window.display();
    }

    return 0;

};