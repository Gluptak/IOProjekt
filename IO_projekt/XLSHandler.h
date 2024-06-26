#pragma once
#ifndef XLSHANDLER_H
#define XLSHANDLER_H

#include <string>
#include <vector>
#include <xmllite.h>
#include <windows.h>
#include <shlwapi.h>
#pragma comment(lib, "xmllite.lib")
#pragma comment(lib, "shlwapi.lib")

class XLSHandler {
public:
    std::vector<std::vector<std::string>> wczytaj_dane(const std::string& filePath);
};

#endif 