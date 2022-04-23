#include <iostream>
#include <vector>
#include <string>

struct Pixel {
    int x;
    int y;
    std::string color;

    void draw() {
        std::cout << "(" << x << ", " << y << ", " << color << ") ";
    }
 };

class Image {
    std::string filename;
public:
    Image(std::string filename) : filename(filename) {}

    void openFile() {
        std::cout << "Open file " << filename << std::endl;
    }
    virtual void readFile() = 0;

    virtual void draw() = 0;
    void final() {
        std::cout << "Drawing image complete" << std::endl;
    }
    virtual void DrawingImage() final {
        openFile();
        readFile();
        draw();
        final();
    }
};

class BitmapImage : public Image {        // Растровое изображение
private:
    std::vector<Pixel*> pixels;     // это пиксели, которые хранятся в файле
    std::vector<Pixel> buffer;      // это пиксели, которые мы читаем для отображение на экране

    void readFile() {
        for (const auto pixel : pixels) {
            buffer.push_back(*pixel);      // Имитируем чтение пикселей из файла в буфер
        }
    };

    void draw() {
        for (const auto pixel : pixels) {
            pixel->draw();      // Рисуем каждый пиксель из буфера
        }
    }
};

struct Figure {
    int x;
    int y;
    std::string figure;

    void draw() {
        std::cout << "(" << x << ", " << y << ", " << figure << ") ";
    }
};


class VectorImage : public Image {        // Векторное изображение
private:
    std::vector<Figure*> figures;     // это описание фигур, которые хранятся в файле
    std::vector<Figure> buffer;       // это описание фигур, которые мы читаем для отображение на экране

    void readFile() {
        for (const auto figure : figures) {
            buffer.push_back(*figure);        // Имитируем чтение фигур из файла в буфер
        }
    };

    void draw() {
        for (const auto figure : figures) {
            figure->draw();      // Рисуем каждую фигуру из буфера
        }
    }
};



int main(){
    Image* array[] =
    {
       &BitmapImage(), &VectorImage()
    };
    for (int i = 0; i < 2; i++)
    {
        array[i]->DrawingImage();
        std::cout << '\n';
    }

    return 0;
}

