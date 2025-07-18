#pragma once
#include"curl/curl.h"

#include <future>
#include <string>
#include"CLEYERA.h"

namespace ConsoleWrite {

static std::wstring ConvertString(const std::string &s) {

  int len = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), NULL, 0);
  std::wstring ws(len, 0);
  MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), &ws[0], len);
  return ws;
}

static void WriteUTF8(const std::string &s) {
  std::wstring ws = ConvertString(s);

  DWORD _;
  WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), ws.c_str(), (DWORD)ws.size(),
                &_, nullptr);
}
} // namespace ConsoleWrite




// 書き込みコールバック
static size_t WriteCallback(void *c, size_t s, size_t n, void *o) {
  ((std::string *)o)->append((char *)c, s * n);
  return s * n;
}

std::future<std::string> GetAllScoresAsync();


std::future<std::string> PostScoreAsync(int score);
