#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm> 

// Canvas dimensions (in logic pixels, before scaling)
const int WIDTH  = 800;
const int HEIGHT = 600;

// Scaling factor for display (each logical pixel becomes a small square)
const int PIXEL_SIZE = 1;

// Canvas type: 2D vector of SFML colors
using Canvas = std::vector<std::vector<sf::Color>>;
extern std::stack<Canvas> undoStack; 

// ========== Task 3.1 – 3.3 (Basic drawing) ==========
void clearCanvas(Canvas& canvas){
    for (auto &row : canvas){
        std::fill(row.begin(),row.end(),sf::Color::White);
    }
}

void drawPixel(Canvas& canvas, int x, int y, const sf::Color& color){
    if (x>=0 && x<WIDTH && y>=0 && y <HEIGHT){
        canvas[y][x] = color;
    }
}
void drawBrush(Canvas& canvas, int x, int y, const sf::Color& color, int radius){
    if (radius < 0){return;}
    if (radius==0){
        drawPixel(canvas,x,y,color);
        return;
    } 
    
    for (int y1=-radius;y1<=radius;++y1){
        for (int x1=-radius;x1<=radius; ++x1){
            if (y1*y1+x1*x1<=radius*radius){
                drawPixel(canvas,x+x1,y+y1,color);
            }
        }
    }
}
// ========== Task 4.1 – 4.3 (Shapes & Undo) ==========
void drawRectangle(Canvas& canvas, int x1, int y1, int x2, int y2, const sf::Color& color){
    int startX=std::min(x1,x2);
    int startY=std::min(y1,y2);
    int endX=std::max(x1,x2);
    int endY=std::max(y1,y2);

    for (int y=startY;y<=endY;++y){
        for (int x=startX;x<=endX;++x){
            drawPixel(canvas, x, y, color);
        }
    }
}
void drawLine(Canvas& canvas, int x1, int y1, int x2, int y2, const sf::Color& color){
    int dx=std::abs(x2-x1);
    int dy=std::abs(y2-y1);
    int sx = (x1< x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err=dx-dy;
    while(true){
        drawPixel(canvas, x1, y1, color);
        if (x1==x2 && y1==y2){break;}
        int err2=2*err;

        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}
void undo(Canvas& canvas){ // Ctrl+Z
    if (undoStack.size() < 1){  
        return;
    }
    
    canvas = undoStack.top();
    undoStack.pop();
}         
void saveToUndo(const Canvas& canvas){ 
    undoStack.push(canvas);
}  

// ========== Task 5.1 – 5.3 (Filters with STL algorithms) ==========

void applyGrayscale(Canvas& canvas) {
    std::transform(canvas.begin(), canvas.end(), canvas.begin(), [](std::vector<sf::Color>& row) { 
        std::transform(row.begin(), row.end(), row.begin(), [](const sf::Color& pixel) {
            sf::Uint8 gray = static_cast<sf::Uint8>(
                0.299f * pixel.r + 0.587f * pixel.g + 0.114f * pixel.b
            );
            return sf::Color(gray, gray, gray, pixel.a);
        });     
        return row;
    });
}



void applyNegative(Canvas& canvas) {
    std::transform(canvas.begin(), canvas.end(), canvas.begin(), [](std::vector<sf::Color>& row) {
        std::transform(row.begin(), row.end(), row.begin(), [](const sf::Color& pixel) {
            return sf::Color(
                255 - pixel.r,
                255 - pixel.g,
                255 - pixel.b,
                pixel.a
            );
        });
        return row;
    });
}

void applyBlur(Canvas& canvas) {
    Canvas src = canvas;
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int ny = y + ky;
                    int nx = x + kx;

                    if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                        sf::Color neighborColor = src[ny][nx];
                        sumR += neighborColor.r;
                        sumG += neighborColor.g;
                        sumB += neighborColor.b;
                        count++; 
                    }
                }
            }
            canvas[y][x] = sf::Color(
                static_cast<sf::Uint8>(sumR / count),
                static_cast<sf::Uint8>(sumG / count),
                static_cast<sf::Uint8>(sumB / count),
                src[y][x].a
            );
        }
    }
}


// ========== Helper for display ==========
void renderToWindow(sf::RenderWindow& window, const Canvas& canvas) {
    static sf::Texture texture;
    static std::vector<sf::Uint8> pixels;
    static bool isInitialized = false;

    if (!isInitialized) {
        texture.create(WIDTH, HEIGHT);
        pixels.resize(WIDTH * HEIGHT * 4);
        isInitialized = true;
    }

    for (int y = 0; y< HEIGHT; ++y) {
        for (int x =0; x < WIDTH; ++x) {
            int index = (y*WIDTH + x) * 4;
            const sf::Color& color = canvas[y][x];
            
            pixels[index] = color.r;
            pixels[index+1] = color.g;
            pixels[index+2] = color.b;
            pixels[index+3] = color.a;
        }
    }

    texture.update(pixels.data());

    sf::Sprite sprite(texture);
    sprite.setScale(static_cast<float>(PIXEL_SIZE), static_cast<float>(PIXEL_SIZE));

    window.draw(sprite);
}
