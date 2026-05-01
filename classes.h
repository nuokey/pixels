#pragma once
#include <string>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

constexpr int WINDOW_HEIGHT = 1600;
constexpr int WINDOW_WIDTH  = 2560;

int PixelSize = 50;

int randInt(int min, int max) {
    int x = rand() % (max - min + 1) + min;
    return x;
}



// Функции для вирусов
// 1) реализация
// void makeVirus(Pixel& p, std::unordered_set<std::pair<float,float>, PairHash>& virusSet) {
//     if (p.red == 0 && p.blue == 0) return;
//     p.red = 0;
//     p.blue = 0;
//     virusSet.insert({p.x, p.y});
// }
// 2) функция распространения вируса
// void spreadVirus(std::vector<Pixel>& pixels,
//                  std::unordered_set<std::pair<float,float>, PairHash>& virusSet,
//                  float dt, float& timer, float interval) {
//     timer += dt;
//     if (timer < interval) return;
//     timer = 0.f;

//     auto currentViruses = virusSet; // копия, чтобы новые вирусы не влияли на текущий тик
//     for (const auto& virusCoord : currentViruses) {
//         // Найти указатель на пиксель-вирус
//         Pixel* virusPixel = nullptr;
//         for (auto& p : pixels) {
//             if (p.x == virusCoord.first && p.y == virusCoord.second) {
//                 virusPixel = &p;
//                 break;
//             }
//         }
//         if (!virusPixel) continue;

//         // Перебрать все пиксели в поисках соседей
//         for (auto& other : pixels) {
//             if (&other == virusPixel) continue;
//             // Соседство по горизонтали или вертикали (расстояние = PixelSize)
//             bool isNeighbor = (std::fabs(virusPixel->x - other.x) < PixelSize + 1 && std::fabs(virusPixel->y - other.y) < 1) ||
//                               (std::fabs(virusPixel->y - other.y) < PixelSize + 1 && std::fabs(virusPixel->x - other.x) < 1);
//             if (isNeighbor) {
//                 other.red = std::max(0, other.red - 10);
//                 other.blue = std::max(0, other.blue - 10);
//                 if (other.red == 0 && other.blue == 0) {
//                     if (virusSet.find({other.x, other.y}) == virusSet.end()) {
//                         makeVirus(other, virusSet);
//                     }
//                 }
//             }
//         }
//     }
// }
// 3) Вызов распространения вируса в главном цикле
// Распространение вируса
// spreadVirus(pixels, virusSet, dt, virusSpreadTimer, virusSpreadInterval);

// // 4) Вирус не дропает 
// if (pixels[i].red < 0 && pixels[i].green < 0 && pixels[i].blue < 0) {
//     bool isVirus = (virusSet.find({pixels[i].x, pixels[i].y}) != virusSet.end());
//     if (!isVirus) {
//         int capturedGreen = pixels[i].green;
//         int capturedRed   = pixels[i].red;
//         for (int d = 0; d < 3; ++d) {
//             float angle = randInt(0, 360) * M_PI / 180.f;
//             float speed = randInt(50, 150);
//             float vx = std::cos(angle) * speed;
//             float vy = std::sin(angle) * speed;
//             int dropGreen = capturedGreen / 3;
//             int dropRed   = capturedRed / 3;
//             if (d == 2) {
//                 dropGreen = capturedGreen - dropGreen * 2;
//                 dropRed   = capturedRed   - dropRed * 2;
//             }
//             drops.emplace_back(pixels[i].x, pixels[i].y, vx, vy, dropGreen, dropRed);
//         }
//     }
//     // Удалить пиксель из набора вирусов, если он там был
//     virusSet.erase({pixels[i].x, pixels[i].y});
//     pixels.erase(pixels.begin() + i);
// }



// 5) ещё какая-то тема, хз что это
// #include <unordered_set>

// struct PairHash {
//     template <class T1, class T2>
//     std::size_t operator() (const std::pair<T1,T2>& p) const {
//         auto h1 = std::hash<T1>{}(p.first);
//         auto h2 = std::hash<T2>{}(p.second);
//         return h1 ^ (h2 << 1);
//     }
// };

// Вирусная система
// std::unordered_set<std::pair<float,float>, PairHash> virusSet;
// float virusSpreadTimer = 0.f;
// const float virusSpreadInterval = 0.5f;   // интервал распространения (сек)