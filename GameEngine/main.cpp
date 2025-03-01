
#include <Windows.h>

#include "MathInclude.h"

#include <fstream>
#include <iostream>

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

  Math::Vector::Vec2 aVec = {1.0f, 5.0f};
  Math::Vector::Vec2 bVec = {2.0f, 5.0f};

  Math::Vector::Vec2 r = aVec * bVec;

  // rをテキストファイルに書き込む
  std::ofstream outFile("output.txt");
  if (outFile.is_open()) {
    outFile << "r: (" << r.x << ", " << r.y << ")" << std::endl;
    outFile.close();
  } else {
    std::cerr << "ファイルを開くことができませんでした。" << std::endl;
  }

  return 0;
}